

[%%client

open Eliom_content.Html.D
open Eliom_content.Html
open Lwt
open BestioleType

let is_ill bestiole =
	match bestiole.state with
	| StdIll false -> false
	| StdIll true -> true
	| Beserk -> true
	| Naughty -> true

let cure_bestiole bestiole =
	bestiole.state <- StdIll false

let make_bestiole_ill bestiole =
	let n = Random.int 10 in
	match n with
	| 0 -> bestiole.state <- Beserk
	| 1 -> bestiole.state <- Naughty
	| _ -> bestiole.state <- StdIll true

let update_speed bestiole =
	let multiplier = match bestiole.state with
		| StdIll true -> 0.85
		| StdIll false -> 1.0
		| Beserk -> 0.85
		| Naughty -> 1.15
	in
	let time_speedup = (Unix.gettimeofday () -. bestiole.start_time) /. 120.0 in
	let time_speedup = 1.0 +. time_speedup in
	bestiole.speed <- Config.std_bestiole_speed *. time_speedup *. multiplier 

let next_coords bestiole =
	let deg_to_rad deg =
		0.01745329252 *. float_of_int deg
	in
	match bestiole.updated_at with
	| None -> (bestiole.x, bestiole.y)
	| Some updated_at -> (
		let nb_pixels_decal = bestiole.speed *. (Unix.gettimeofday () -. updated_at) in
		let x = nb_pixels_decal *. cos (deg_to_rad bestiole.rotation) in
		let y = nb_pixels_decal *. sin (deg_to_rad bestiole.rotation) in
		(bestiole.x +. x, bestiole.y +. y)
	)

let update_rotation bestiole new_rot =
	bestiole.rotation <- new_rot mod 360 ;
	let rotation = "rotate(" ^ (string_of_int (bestiole.rotation + 90)) ^ "deg)" in
	bestiole.dom_elt##.style##.transform := Js.string rotation

let move_bestiole_bounce bestiole x y =
	let b_size = BestioleUtils.get_bestiole_size bestiole in
	( if x <= 0.0 then
		update_rotation bestiole (180 + (360 - bestiole.rotation))
	) ;
	( if x +. b_size >= float_of_int Config.board_width then
		update_rotation bestiole (180 - bestiole.rotation)
	) ;
	( if y <= 0.0 then
		update_rotation bestiole (360 - bestiole.rotation)
	) ;
	( if y +. b_size >= float_of_int Config.board_height then
		update_rotation bestiole (360 - bestiole.rotation)
	) ;
	let x, y = BestioleUtils.get_bestiole_absolute_coords x y in
	BestioleUtils.move_bestiole bestiole x y

let change_rotation_if_ok bestiole =
	if Unix.gettimeofday () >= bestiole.change_rotation_at then (
		update_rotation bestiole (Utils.random_rotation ()) ;
		bestiole.change_rotation_at <- Utils.random_forward_time ()
	)

let rec bestiole_thread bestiole =
  Lwt_js.sleep 0.01 >>= fun () ->
  	match bestiole.currently_dragged with
  	| true -> ( bestiole.updated_at <- Some (Unix.gettimeofday ()) ;
  				bestiole_thread bestiole )
  	| false -> (
  		Lwt.return (change_rotation_if_ok bestiole) >>= fun () ->
	    Lwt.return (update_speed bestiole) >>= fun () ->
	      Lwt.return (next_coords bestiole) >>= fun (x, y) ->
	        Lwt.return (move_bestiole_bounce bestiole x y) >>= fun () ->
	          bestiole_thread bestiole
	)

let handle_bestiole_dragend bestiole =
  let bottom_y = bestiole.y +. float_of_int Config.std_bestiole_size in
  let hospital_start = Config.board_height - Config.extremes_height in
  let hospital_start = float_of_int hospital_start in
  if bottom_y >= hospital_start then cure_bestiole bestiole ;
  update_rotation bestiole (Utils.random_rotation ()) ;
  bestiole.change_rotation_at <- Utils.random_forward_time ()

let make_bestiole start_time dragging_handler =
  let image = img
      ~alt:""
      ~a:[a_width Config.std_bestiole_size ; a_class ["bestiole"]]
      ~src:(make_uri (Eliom_service.static_dir ()) ["images" ; "bestiole.png"]) ()
  in
  let bestiole = {
    elt = image ;
    dom_elt = Utils.elt_to_dom_elt image ;
    x = 0.0 ;
    y = 0.0 ;
    rotation = 0 ;
    start_time = start_time ;
    speed = Config.std_bestiole_speed ;
    state = StdIll false ;
    change_rotation_at = Utils.random_forward_time () ;
    updated_at = None ;
    currently_dragged = false
  } in
  let rand_x = Random.float (float_of_int Config.board_width) in
  let rand_y = Random.float (float_of_int Config.board_height) in
  let rand_x, rand_y = BestioleUtils.get_bestiole_absolute_coords rand_x rand_y in
  update_rotation bestiole (Utils.random_rotation ()) ;
  BestioleUtils.move_bestiole bestiole rand_x rand_y ;
  Dragging.make_draggable dragging_handler bestiole ;
  bestiole

let make_bestioles start_time dragging_handler n =
  let rec _make_bestioles acc = function
    | 0 -> acc
    | n -> _make_bestioles (make_bestiole start_time dragging_handler::acc) (n - 1)
  in
  _make_bestioles [] n

let make_bestioles_and_attach start_time dragging_handler parent n =
  let bestioles = make_bestioles start_time dragging_handler n in
  List.iter (fun b -> Dom.appendChild parent b.dom_elt) bestioles ;
  bestioles

]