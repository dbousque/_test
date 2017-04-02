

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

let%client init_client () =
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
  let bestioles = Bestiole.make_bestioles_and_attach
                      start_time
                      dragging_handler
                      container
                      Config.starting_nb_bestioles
  in
  Lwt.join (List.map Bestiole.bestiole_thread bestioles) >>= Lwt.return ;
  ()

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
       let _ = [%client (init_client () : unit) ] in
       Lwt.return (Page.make ()))