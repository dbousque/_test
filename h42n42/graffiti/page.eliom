

open Eliom_content.Html.D
open Eliom_content.Html
open Lwt

let wave_images =
	let _make_wave_image cls =
		img
			~alt:""
			~a:[a_class ["wave" ; cls]]
			~src:(make_uri (Eliom_service.static_dir ()) ["images" ; "wave.png"]) ()
	in
	let rec _make_wave_images acc current_height =
		let new_image = _make_wave_image "wave2" in
		if current_height + 22 > Config.extremes_height then acc
		else _make_wave_images (new_image::acc) (current_height + 21)
	in
	let first_image = _make_wave_image "wave1" in
	first_image::_make_wave_images [] 25

let river =
	div ~a:[
		a_class ["extreme" ; "river"] ;
		a_style ("height:" ^ string_of_int Config.extremes_height ^ "px;")
	] wave_images

let hospital_images =
	let _make_hospital_image () =
		img
			~alt:""
			~a:[a_class ["center-vertical" ; "hospital-image"]]
			~src:(make_uri (Eliom_service.static_dir ()) ["images" ; "hospital.png"]) ()
	in
	let nb_hospital_images =
		if Config.extremes_height > 305 then 1
		else if Config.extremes_height > 120 then 2
		else 3
	in
	let rec _make_hospital_images = function
		| 0 -> []
		| n -> (_make_hospital_image ())::(_make_hospital_images (n - 1))
	in
	_make_hospital_images nb_hospital_images

let hospital =
	div ~a:[
		a_class ["extreme" ; "hospital"] ;
		a_style ("height:" ^ string_of_int Config.extremes_height ^ "px;" ^
							"margin-top:" ^ string_of_int (Config.board_height - Config.extremes_height * 2) ^ "px;")
	] [
		div ~a:[a_class ["center-vertical" ; "center-horizontal"]]
			hospital_images
	]

let bestiole_container =
	div ~a:[
		a_class ["bestiole-container"] ;
		a_style ("width:" ^ string_of_int Config.board_width ^ "px;" ^
							"height:" ^ string_of_int Config.board_height ^ "px;")
	] [
		river ;
		hospital
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

let make () =
	html
		(head (title (pcdata "Graffiti"))
				[css_link ~uri:(make_uri (Eliom_service.static_dir ()) ["css" ; "h42n42.css"])
		()])
		(body [h1 [pcdata "Graffiti"] ; board_container ])