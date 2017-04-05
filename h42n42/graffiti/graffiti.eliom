

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

let rec check_for_collisions_thread existing_bestioles =
  Lwt_js.sleep 0.1 >>= fun () ->
    let width = float_of_int Config.board_width in
    let height = float_of_int Config.board_height in
    let quadtree = BestioleQuadtree.make width height in
    let quadtree = List.fold_left (fun acc b -> BestioleQuadtree.add acc b) quadtree existing_bestioles in
    let make_ill_if_collision bestiole =
      let other_bestiole_ill = (fun x _ -> Bestiole.is_ill x) in
      if not (Bestiole.is_ill bestiole) && not bestiole.currently_dragged
        && BestioleQuadtree.collision_pred quadtree bestiole other_bestiole_ill then
        Bestiole.make_bestiole_ill bestiole
    in
    Lwt.return (List.iter make_ill_if_collision existing_bestioles) >>= fun () ->
      check_for_collisions_thread existing_bestioles

let rec wait_for_threads beginned_at threads existing_bestioles attach_n_bestioles =
  Lwt.choose threads >>= fun () ->
    Printf.printf "here\n" ;
    Lwt.return (List.filter (fun x -> Lwt.state x = Lwt.Sleep) threads) >>= fun threads ->
      Printf.printf "nb_threads : %d\n" (List.length threads) ;
      Printf.printf "first is sleep : %s\n" (match Lwt.state (List.hd threads) with | Lwt.Sleep -> "yes" | _ -> "no") ;
      if List.length threads = 0 then init_client () else (
        Lwt.return (List.filter (fun b -> not b.dead) existing_bestioles) >>= fun existing_bestioles ->
          if (Unix.gettimeofday ()) -. beginned_at >= Config.new_bestiole_every then (
            let threads = (match threads with | [] -> [] | hd :: rest -> Lwt.cancel hd ; rest) in
            make_bestioles_loop false 1 threads existing_bestioles attach_n_bestioles
          ) else (
            let wait_n_sec = Config.new_bestiole_every -. ((Unix.gettimeofday ()) -. beginned_at) in
            let threads = (Lwt_js.sleep wait_n_sec) :: threads in
            wait_for_threads beginned_at threads existing_bestioles attach_n_bestioles 
          )
      )

and make_bestioles_loop start nb threads existing_bestioles attach_n_bestioles =
  let at_least_one_healthy = List.exists (fun b -> b.state = StdIll false) existing_bestioles in
  let nb = if start || at_least_one_healthy then nb else 0 in
  let new_bestioles = attach_n_bestioles (not start) nb in
  let existing_bestioles = List.fold_left (fun acc b -> b::acc) existing_bestioles new_bestioles in
  let threads = List.fold_left (fun acc b -> (Bestiole.bestiole_thread b)::acc) threads new_bestioles in
  let threads = (Lwt_js.sleep Config.new_bestiole_every) :: threads in
  let waiter, wakener = Lwt.task () in
  let collisions = check_for_collisions_thread existing_bestioles in
  let threads = collisions :: threads in
  wait_for_threads (Unix.gettimeofday ()) threads existing_bestioles attach_n_bestioles

and init_client () =
  Random.self_init () ;
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
  let container = Utils.elt_to_dom_elt ~%(Page.bestiole_container) in
  let attach_n_bestioles = Bestiole.make_bestioles_and_attach start_time dragging_handler container in
  make_bestioles_loop true Config.starting_nb_bestioles [] [] attach_n_bestioles

]

let main_service =
  Graffiti_app.create
    ~path:(Eliom_service.Path [""])
    ~meth:(Eliom_service.Get Eliom_parameter.unit)
    (fun () () ->
       let lol = Lwt_unix.sleep 3.0 >>= fun () -> Lwt_io.printf "salut222\n" in
       Lwt.join [
          (Lwt_unix.sleep 3.0 >>= fun () -> Lwt_io.printf "salut\n") ;
          (Lwt_unix.sleep 3.0 >>= fun () -> Lwt_io.printf "salut\n") ;
          (Lwt_unix.sleep 3.0 >>= fun () -> Lwt_io.printf "salut\n")
        ] >>= (fun () -> Lwt.return ()) ;
       (* Cf. section "Client side side-effects on the server" *)
       let _ = [%client (init_client () : unit Lwt.t) ] in
       Lwt.return (Page.make ()))