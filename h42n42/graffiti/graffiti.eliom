

[%%shared

open Eliom_content.Html.D
open Eliom_content.Html
open Lwt
open BestioleType

]

module Graffiti_app =
  Eliom_registration.App (
    struct
      let application_name = "graffiti"
      let global_data_path = None
    end)

[%%client

module BestioleLeaf : (Quadtree.Leaf with type t = bestiole) = struct
  type t = bestiole
  let get_coords bestiole =
    (bestiole.x, bestiole.y)
  let get_size bestiole =
    (bestiole.size, bestiole.size)
end
module BestioleQuadtree = Quadtree.Make (BestioleLeaf)


let you_lost_class = "you-lost-animation"

let add_lost_css dom_elt =
  let classes = Js.to_string dom_elt##.className in
  dom_elt##.className := Js.string (classes ^ " " ^ you_lost_class)

let remove_lost_css dom_elt =
  let classes = Js.to_string dom_elt##.className in
  if String.length classes > 30 then (
    let ind = String.length classes - String.length (" " ^ you_lost_class) in
    let new_classes = String.sub classes 0 ind in
    dom_elt##.className := Js.string new_classes
  )

let clear_game_board container =
  remove_lost_css container ;
  let you_lost = Utils.elt_to_dom_elt ~%(Page.you_lost) in
  you_lost##.style##.display := (Js.string "none")

let update_config_val inp =
  let value = inp##getAttribute (Js.string "value") in
  let ident = inp##getAttribute (Js.string "id") in
  let value = Js.Opt.get value (fun _ -> assert false) in
  let ident = Js.Opt.get ident (fun _ -> assert false) in
  let value = Js.to_string value in
  let ident = Js.to_string ident in
  let value = try int_of_string value with | _ -> 10 in
  let value = if value <= 0 then 10 else value in
  Printf.printf "val %s %d\n" ident value ;
  Config.set_val ident value

let update_config () =
  Js.Unsafe.eval_string "setVals()" ;
  let body = Utils.elt_to_dom_elt ~%(Page.body_html) in
  let inps = body##querySelectorAll (Js.string ".rangeparent > input") in
  List.iter update_config_val (Dom.list_of_nodeList inps)

let replace_range_tagname range =
  let d = Dom_html.createP Dom_html.document in
  d##.innerHTML := range##.innerHTML ;
  d##.className := Js.string "range-field rangeparent" ;
  let title = range##.title in
  let parent = ( match Js.to_string title with
    | "fst-parent" -> Utils.elt_to_dom_elt ~%(Page.first_input_parent)
    | "snd-parent" -> Utils.elt_to_dom_elt ~%(Page.second_input_parent)
    | _ -> Utils.elt_to_dom_elt ~%(Page.third_input_parent)
  ) in
  Dom.replaceChild parent d range ;
  let inp = Dom.list_of_nodeList (d##querySelectorAll (Js.string "input")) in
  match inp with
  | [] -> ()
  | hd :: rest -> (
      let value, min, max = Hashtbl.find Config.vals (Js.to_string hd##.id) in
      hd##setAttribute (Js.string "min") (Js.string (string_of_int min)) ;
      hd##setAttribute (Js.string "max") (Js.string (string_of_int max)) ;
      hd##setAttribute (Js.string "value") (Js.string (string_of_int value))
    )

let change_naughty_rotation bestiole existing_bestioles =
  let rad_to_deg rad =
    rad *. (180.0 /. 3.14159265)
  in
  let closer_bestiole acc b =
    if b.state <> StdIll false then acc
    else ( match acc with
      | None -> Some b
      | Some a -> (
        let distance1 = sqrt ((b.x -. bestiole.x) ** 2.0 +. (b.y -. bestiole.y) ** 2.0) in
        let distance2 = sqrt ((a.x -. bestiole.x) ** 2.0 +. (a.y -. bestiole.y) ** 2.0) in
        if distance1 < distance2 then Some b
        else Some a
      )
    )
  in
  if bestiole.state = Naughty then (
    match List.fold_left closer_bestiole None existing_bestioles with
    | None -> ()
    | Some b -> (
      let x = b.x -. bestiole.x in
      let y = b.y -. bestiole.y in
      let deg = rad_to_deg (atan2 y x) in
      Bestiole.update_rotation bestiole (int_of_float deg)
    )
  )

let rec check_for_collisions_thread existing_bestioles =
  Lwt_js.sleep 0.1 >>= fun () ->
    let width = float_of_int Config.board_width in
    let height = float_of_int Config.board_height in
    let quadtree = BestioleQuadtree.make width height in
    let quadtree = List.fold_left (fun acc b -> BestioleQuadtree.add acc b) quadtree existing_bestioles in
    let make_ill_if_collision bestiole =
      let other_bestiole_ill = (fun x _ -> not x.currently_dragged && Bestiole.is_ill x) in
      if not (Bestiole.is_ill bestiole) && not bestiole.currently_dragged
        && BestioleQuadtree.collision_pred quadtree bestiole other_bestiole_ill then (
        match Random.int 10 with
        | 0 -> Bestiole.make_bestiole_ill bestiole
        | _ -> ()
      )
    in
    Lwt.return (List.iter make_ill_if_collision existing_bestioles) >>= fun () ->
      Lwt.return (List.iter (fun x -> change_naughty_rotation x existing_bestioles) existing_bestioles) >>= fun () ->
        check_for_collisions_thread existing_bestioles

let rec wait_for_threads beginned_at threads existing_bestioles attach_n_bestioles =
  Lwt.choose threads >>= fun () ->
    Lwt.return (List.filter (fun x -> Lwt.state x = Lwt.Sleep) threads) >>= fun threads ->
      let threads = (match threads with | [] -> [] | hd :: rest -> Lwt.cancel hd ; rest) in
      Lwt.return (List.filter (fun b -> not b.dead) existing_bestioles) >>= fun existing_bestioles ->
        if List.length existing_bestioles = 0 then exit_game () else (
          let new_b_every = float_of_int (Config.get_val "new-bestiole-every") in
          if (Unix.gettimeofday ()) -. beginned_at >= new_b_every then (
            make_bestioles_loop false 1 threads existing_bestioles attach_n_bestioles
          ) else (
            let wait_n_sec = new_b_every -. ((Unix.gettimeofday ()) -. beginned_at) in
            let threads = (Lwt_js.sleep wait_n_sec) :: threads in
            let collisions = check_for_collisions_thread existing_bestioles in
            let threads = collisions :: threads in
            wait_for_threads beginned_at threads existing_bestioles attach_n_bestioles 
          )
        )

and make_bestioles_loop start nb threads existing_bestioles attach_n_bestioles =
  let at_least_one_healthy = List.exists (fun b -> b.state = StdIll false) existing_bestioles in
  let nb = if start || at_least_one_healthy then nb else 0 in
  let new_bestioles = attach_n_bestioles (not start) nb in
  let existing_bestioles = List.fold_left (fun acc b -> b::acc) existing_bestioles new_bestioles in
  let threads = List.fold_left (fun acc b -> (Bestiole.bestiole_thread b)::acc) threads new_bestioles in
  let new_b_every = float_of_int (Config.get_val "new-bestiole-every") in
  let threads = (Lwt_js.sleep new_b_every) :: threads in
  let collisions = check_for_collisions_thread existing_bestioles in
  let threads = collisions :: threads in
  wait_for_threads (Unix.gettimeofday ()) threads existing_bestioles attach_n_bestioles

and start_game () =
  let container = Utils.elt_to_dom_elt ~%(Page.bestiole_container) in
  clear_game_board container ;
  update_config () ;
  let start_time = Unix.gettimeofday () in
  let events_cbs = Dragging.{
    dragstart = (fun _ -> ()) ;
    dragend = Bestiole.handle_bestiole_dragend
  } in
  let move bestiole x y =
    let x = x -. (BestioleUtils.get_bestiole_size bestiole /. 2.0) in
    let y = y -. (BestioleUtils.get_bestiole_size bestiole /. 2.0) in
    BestioleUtils.move_bestiole bestiole x y
  in
  let set_dragging_status bestiole status =
    bestiole.currently_dragged <- status
  in
  let get_dom_elt bestiole =
    bestiole.dom_elt
  in
  let dragging_handler = Dragging.make_handler events_cbs move set_dragging_status get_dom_elt in
  let attach_n_bestioles = Bestiole.make_bestioles_and_attach start_time dragging_handler container in
  let nb_bestioles = (Config.get_val "starting-nb-bestioles") in
  make_bestioles_loop true nb_bestioles [] [] attach_n_bestioles

and init_client restart =
  Random.self_init () ;
  Config.set_std_vals () ;
  let body = Utils.elt_to_dom_elt ~%(Page.body_html) in
  let ranges = body##querySelectorAll (Js.string "span.rangeparent") in
  List.iter replace_range_tagname (Dom.list_of_nodeList ranges) ;
  let start_button = Utils.elt_to_dom_elt ~%(Page.start_button) in
  Lwt_js_events.mousedowns start_button (fun _ _ -> start_game ())

and exit_game () =
  let container = Utils.elt_to_dom_elt ~%(Page.bestiole_container) in
  add_lost_css container ;
  Lwt_js.sleep 1.0 >>= fun () ->
    let you_lost = Utils.elt_to_dom_elt ~%(Page.you_lost) in
    let classes = Js.to_string you_lost##.className in
    you_lost##.className := Js.string (classes ^ " " ^ "appear") ;
    you_lost##.style##.display := (Js.string "inherit") ;
    Lwt.return ()

(**let () =
  ( Lwt_js.sleep 0.5 >>= fun () ->
    init_client false ) ;
  () **)

]

let main_service =
  Graffiti_app.create
    ~path:(Eliom_service.Path [""])
    ~meth:(Eliom_service.Get Eliom_parameter.unit)
    (fun () () ->
      let _ = [%client (init_client false : unit Lwt.t) ] in
      Lwt.return (Page.make ()))