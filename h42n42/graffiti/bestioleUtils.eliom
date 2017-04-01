

[%%client

open BestioleType

let get_elt_coords elt =
	let coords = elt##getBoundingClientRect in
	(int_of_float coords##.left, int_of_float coords##.top)

let get_bestiole_size bestiole =
	Config.std_bestiole_size

let get_bestiole_relative_coords x y =
	let cont_x, cont_y = get_elt_coords (Utils.elt_to_dom_elt ~%(Page.bestiole_container)) in
	(x - cont_x, y - cont_y)

let get_bestiole_absolute_coords x y =
	let cont_x, cont_y = get_elt_coords (Utils.elt_to_dom_elt ~%(Page.bestiole_container)) in
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

]