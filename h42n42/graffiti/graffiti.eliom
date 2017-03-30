

[%%shared
  (* Modules opened in the shared-section are available in client-
     and server-code *)
  open Eliom_content.Html.D
  open Eliom_content.Html
  open Lwt
]

module Graffiti_app =
  Eliom_registration.App (
    struct
      let application_name = "graffiti"
      let global_data_path = None
    end)

let bestiole_container =
  div ~a:[
    a_class ["bestiole-container"] ;
    a_style ("width:" ^ string_of_int Config.board_width ^ "px;" ^
              "height:" ^ string_of_int Config.board_height ^ "px;")
  ] []

[%%client

type img = {
  elt:            Html_types.img D.elt ;
  dom_elt:        Dom_html.element Js.t ;
  mutable x:      int ;
  mutable y:      int
}

type dragging_handler = {
  mutable currently_dragging:   img option
}

let elt_to_dom_elt = To_dom.of_element

let get_elt_coords elt =
  let coords = elt##getBoundingClientRect in
  (int_of_float coords##.left, int_of_float coords##.top)

let get_bestiole_size bestiole =
  Config.std_bestiole_size

let get_bestiole_relative_coords x y =
  let cont_x, cont_y = get_elt_coords (elt_to_dom_elt ~%bestiole_container) in
  (x - cont_x, y - cont_y)

let get_bestiole_absolute_coords x y =
  let cont_x, cont_y = get_elt_coords (elt_to_dom_elt ~%bestiole_container) in
  (cont_x + x, cont_y + y)

let actual_move_bestiole bestiole x_int y_int =
  let x = Js.string (string_of_int x_int ^ "px") in
  let y = Js.string (string_of_int y_int ^ "px") in
  bestiole.dom_elt##.style##.left := x ;
  bestiole.dom_elt##.style##.top := y ;
  let x, y = get_bestiole_relative_coords x_int y_int in
  bestiole.x <- x ;
  bestiole.y <- y

let move_bestiole bestiole new_x new_y =
  let _limit_by_borders value low high =
    if value < low then low
    else if value > high then high
    else value
  in
  let x, y = get_bestiole_relative_coords new_x new_y in
  let offset = get_bestiole_size bestiole in
  let x = _limit_by_borders x 0 (Config.board_width - offset) in
  let y = _limit_by_borders y 0 (Config.board_height - offset) in
  let x, y = get_bestiole_absolute_coords x y in
  actual_move_bestiole bestiole x y

let add_selected dom_elt =
  let classes = Js.to_string dom_elt##.className in
  dom_elt##.className := Js.string (classes ^ " selected-bestiole")

let remove_selected dom_elt =
  let classes = Js.to_string dom_elt##.className in
  let ind = String.length classes - String.length " selected-bestiole" in
  let new_classes = String.sub classes 0 ind in
  dom_elt##.className := Js.string new_classes

let deselect_bestiole handle_dragging =
  match handle_dragging.currently_dragging with
  | None -> ()
  | Some bestiole -> remove_selected bestiole.dom_elt

let select_bestiole handle_dragging = 
  match handle_dragging.currently_dragging with
  | None -> ()
  | Some bestiole -> add_selected bestiole.dom_elt

let stop_dragging handle_dragging =
  deselect_bestiole handle_dragging ;
  handle_dragging.currently_dragging <- None

let change_dragging_elt handle_dragging bestiole =
  deselect_bestiole handle_dragging ;
  handle_dragging.currently_dragging <- Some bestiole ;
  select_bestiole handle_dragging

let make_bestiole handle_dragging =
  let image = img
      ~alt:""
      ~a:[a_width Config.std_bestiole_size ; a_class ["bestiole"]]
      ~src:(make_uri (Eliom_service.static_dir ()) ["images" ; "bestiole.png"]) ()
  in
  let bestiole = { elt = image ; dom_elt = elt_to_dom_elt image ; x = 0 ; y = 0 } in
  Lwt.async (fun () ->
    Lwt_js_events.mousedowns bestiole.dom_elt
      ( fun ev _ ->
          Dom.preventDefault ev ;
          change_dragging_elt handle_dragging bestiole ;
          Lwt.return ()
      ) ;
  ) ;
  bestiole

let make_bestioles handle_dragging n =
  let rec _make_bestioles acc = function
    | 0 -> acc
    | n -> _make_bestioles (make_bestiole handle_dragging::acc) (n - 1)
  in
  _make_bestioles n

let attach_bestioles_to_container handle_dragging parent n =
  let bestioles = make_bestioles handle_dragging n in
  bestioles

]

let board_container =
  div ~a:[
    a_class ["board-container"] ;
    a_style ("width:" ^ string_of_int (Config.board_width + 40) ^ "px;" ^
              "height:" ^ string_of_int (Config.board_height + 40) ^ "px;")
  ] [
    div ~a:[
      a_class ["hide-border" ; "top-bottom-border"]
    ] [] ;
    div ~a:[
      a_class ["hide-border" ; "left-right-border"] ;
      a_style ("height:" ^ string_of_int Config.board_height ^ "px;")
    ] [] ;
    bestiole_container ;
    div ~a:[
      a_class ["hide-border" ; "left-right-border"] ;
      a_style ("height:" ^ string_of_int Config.board_height ^ "px;")
    ] [] ;
    div ~a:[
      a_class ["hide-border" ; "top-bottom-border"] ;
      a_style ("margin-top:" ^ string_of_int Config.board_height ^ "px;")
    ] []
  ]

let page () =
  html
     (head (title (pcdata "Graffiti"))
        [css_link ~uri:(make_uri (Eliom_service.static_dir ()) ["css" ; "graffiti.css"])
     ()])
     (body [h1 [pcdata "Graffiti"] ; board_container ])

let%client init_client () =

  let handle_dragging = {
    currently_dragging = None
  } in

  Lwt_js_events.mouseups Dom_html.document
    ( fun ev _ ->
        stop_dragging handle_dragging ;
        Lwt.return ()
    ) ;
  Lwt_js_events.mousemoves Dom_html.document
    ( fun ev _ ->
        ( match handle_dragging.currently_dragging with
        | None -> ()
        | Some bestiole -> (
              let x = ev##.clientX - (get_bestiole_size bestiole / 2) in
              let y = ev##.clientY - (get_bestiole_size bestiole / 2) in
              move_bestiole bestiole x y
            )
          ) ;
        Lwt.return ()
    ) ;

  let container = elt_to_dom_elt ~%bestiole_container in
  let child = make_bestiole handle_dragging in
  let child = child.dom_elt in
  Dom.appendChild container child ;
  let child = make_bestiole handle_dragging in
  let child = child.dom_elt in
  Dom.appendChild container child

let main_service =
  Graffiti_app.create
    ~path:(Eliom_service.Path [""])
    ~meth:(Eliom_service.Get Eliom_parameter.unit)
    (fun () () ->
       (* Cf. section "Client side side-effects on the server" *)
       let _ = [%client (init_client () : unit) ] in
       Lwt.return (page ()))