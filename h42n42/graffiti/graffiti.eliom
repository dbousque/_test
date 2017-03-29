

[%%shared
  (* Modules opened in the shared-section are available in client-
     and server-code *)
  open Eliom_content.Html.D
  open Lwt
]

module Graffiti_app =
  Eliom_registration.App (
    struct
      let application_name = "graffiti"
      let global_data_path = None
    end)

let%shared width  = 700
let%shared height = 400

let%client draw ctx ((r, g, b), size, (x1, y1), (x2, y2)) =
  let color = CSS.Color.string_of_t (CSS.Color.rgb r g b) in
  ctx##.strokeStyle := (Js.string color);
  ctx##.lineWidth := float size;
  ctx##beginPath;
  ctx##(moveTo (float x1) (float y1));
  ctx##(lineTo (float x2) (float y2));
  ctx##stroke

[%%client
  Printf.printf "lol : %d\n" Mymodule.i
]

let canvas_elt =
  canvas ~a:[a_width width; a_height height]
    [pcdata "your browser doesn't support canvas"]

[%%client
let make_bestiole_image () =
  let image = div ~a:[a_style "background-image:url('./images/bestiole.png');width:40px;height:40px;position:absolute"] [
   (** img ~alt:"lol"
      ~a:[a_width 40 ;
        a_class ["bestiole"] ;
      ]
      ~src:(make_uri (Eliom_service.static_dir ()) ["images" ; "bestiole.png"]) ()
  **)
  ] in
  Lwt.async (fun () ->
    let dom_image = Eliom_content.Html.To_dom.of_element image in
    Lwt_js_events.mousedowns dom_image
      ( fun ev _ ->
          let x = ev##.clientX in
          let y = ev##.clientY in
          let x = Js.string (string_of_int x ^ "px") in
          let y = Js.string (string_of_int y ^ "px") in
          dom_image##.style##.left := x ;
          dom_image##.style##.top := y ;
          Lwt.return ()
      )
  ) ;
  image

let make_bestiole_images n =
  let rec _make_bestiole_images acc = function
    | 0 -> acc
    | n -> _make_bestiole_images (make_bestiole_image ()::acc) (n - 1)
  in
  _make_bestiole_images n

let attach_bestioles_to_container parent n =
  let bestioles = make_bestiole_images n in
  bestioles

]

let bestiole_container =
  div ~a:[a_class ["bestiole_container"]] []

let page () =
  html
     (head (title (pcdata "Graffiti"))
        [css_link ~uri:(make_uri (Eliom_service.static_dir ()) ["css" ; "graffiti.css"])
     ()])
     (body [h1 [pcdata "Graffiti"] ; bestiole_container ])

let%client init_client () =

  let container = Eliom_content.Html.To_dom.of_element ~%bestiole_container in
  let child = make_bestiole_image () in
  let child = Eliom_content.Html.To_dom.of_element child in
  Dom.appendChild container child ;
  let child = make_bestiole_image () in
  let child = Eliom_content.Html.To_dom.of_element child in
  Dom.appendChild container child ;

  let canvas = Eliom_content.Html.To_dom.of_canvas ~%canvas_elt in
  let ctx = canvas##(getContext (Dom_html._2d_)) in
  ctx##.lineCap := Js.string "round";

  let x = ref 0 and y = ref 0 in

  let set_coord ev =
    let x0, y0 = Dom_html.elementClientPosition canvas in
    x := ev##.clientX - x0 + 10; y := ev##.clientY - y0
  in

  let compute_line ev =
    let oldx = !x and oldy = !y in
    set_coord ev;
    ((255, 0, 0), 2, (oldx, oldy), (!x, !y))
  in

  let line ev = draw ctx (compute_line ev); Lwt.return () in

  Lwt.async (fun () ->
    let open Lwt_js_events in
    mousedowns canvas
      (fun ev _ ->
         set_coord ev; line ev >>= fun () ->
           Lwt.pick
             [mousemoves Dom_html.document (fun x _ -> line x);
        mouseup Dom_html.document >>= line]))

let main_service =
  Graffiti_app.create
    ~path:(Eliom_service.Path [""])
    ~meth:(Eliom_service.Get Eliom_parameter.unit)
    (fun () () ->
       (* Cf. section "Client side side-effects on the server" *)
       let _ = [%client (init_client () : unit) ] in
       Lwt.return (page ()))