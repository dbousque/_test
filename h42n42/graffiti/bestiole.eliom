

[%%client

open Eliom_content.Html.D
open Eliom_content.Html
open Lwt
open BestioleType

let handle_bestiole_dragend bestiole =
  ()

let make_bestiole dragging_handler =
  let image = img
      ~alt:""
      ~a:[a_width Config.std_bestiole_size ; a_class ["bestiole"]]
      ~src:(make_uri (Eliom_service.static_dir ()) ["images" ; "bestiole.png"]) ()
  in
  let bestiole = {
    elt = image ;
    dom_elt = Utils.elt_to_dom_elt image ;
    x = 0 ;
    y = 0 ;
    currently_dragged = false
  } in
  let rand_x = Random.int Config.board_width in
  let rand_y = Random.int Config.board_height in
  let rand_x, rand_y = BestioleUtils.get_bestiole_absolute_coords rand_x rand_y in
  BestioleUtils.move_bestiole bestiole rand_x rand_y ;
  Dragging.make_draggable dragging_handler bestiole ;
  bestiole

let make_bestioles dragging_handler n =
  let rec _make_bestioles acc = function
    | 0 -> acc
    | n -> _make_bestioles (make_bestiole dragging_handler::acc) (n - 1)
  in
  _make_bestioles [] n

let attach_bestioles_to_container dragging_handler parent n =
  let bestioles = make_bestioles dragging_handler n in
  List.iter (fun b -> Dom.appendChild parent b.dom_elt) bestioles

]