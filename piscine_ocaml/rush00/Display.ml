

let width = 800
let height = 800
let repr = " 800x800"

let init () =
    Graphics.open_graph repr

let std_pencil () =
	Graphics.set_line_width 3

let large_pencil () =
	Graphics.set_line_width 5

let pick_color = function
	| n when n mod 5 = 0 -> Graphics.black
	| n when n mod 5 = 1 -> Graphics.red
	| n when n mod 5 = 2 -> Graphics.blue
	| n when n mod 5 = 3 -> Graphics.green
	| _ -> Graphics.cyan

let draw_rectangle x y w h =
	let up_l_x = x - (w / 2) in
	let up_l_y = y - (h / 2) in
	let up_r_x = x + (w / 2) in
	let up_r_y = y - (h / 2) in
	let lo_l_x = x - (w / 2) in
	let lo_l_y = y + (h / 2) in
	let lo_r_x = x + (w / 2) in
	let lo_r_y = y + (h / 2) in
	Graphics.moveto up_l_x up_l_y ;
	Graphics.lineto lo_l_x lo_l_y ;
	Graphics.moveto lo_l_x lo_l_y ;
	Graphics.lineto lo_r_x lo_r_y ;
	Graphics.moveto lo_r_x lo_r_y ;
	Graphics.lineto up_r_x up_r_y ;
	Graphics.moveto up_r_x up_r_y ;
	Graphics.lineto up_l_x up_l_y

let draw_square x y z =
	draw_rectangle x y z z

let draw_line x1 y1 x2 y2 =
	Graphics.moveto x1 y1 ;
	Graphics.lineto x2 y2

let rec draw_vert_line_of_sq n center_x center_y width =
	match n with
		| n when n > 0 -> 
			draw_square center_x center_y width ;
			draw_vert_line_of_sq (n - 1) center_x (center_y - width) width
		| _ -> ignore ()

let rec draw_hor_line_of_sq n center_x center_y width =
	match n with
		| n when n > 0 ->
			draw_square center_x center_y width ;
			draw_hor_line_of_sq (n - 1) (center_x + width) center_y width
		| _ -> ignore ()

let rec draw_n_squares n cent_x cent_y width =
	if n > 0 then
		let decal = width / 2 * n in
		let up_right_x = cent_x - decal in
		let up_right_y = cent_y + decal in
		let start_x = up_right_x + width / 2 in
		let start_y = up_right_y - width / 2 in
		let new_cent_x = cent_x + width / 2 in
		let new_cent_y = cent_y - width / 2 in
		draw_vert_line_of_sq n start_x start_y width ;
		draw_hor_line_of_sq n start_x start_y width ;
		draw_n_squares (n - 1) new_cent_x new_cent_y width

let rec power n x =
	match x with
		| x when x <= 0 -> 1
		| 1 -> n
		| _ -> n * (power n (x - 1))

let rec draw_borders depth nb_sq center_x center_y width =
	large_pencil () ;
	Graphics.set_color (pick_color depth);
	match depth with
		| n when n <= 0 -> ignore ()
		| 1 -> draw_n_squares nb_sq center_x center_y (width * nb_sq)
		| _ -> let pow_nb = (power nb_sq (depth - 1)) in
				draw_n_squares nb_sq center_x center_y (width * pow_nb) ;
				draw_borders (depth - 1) nb_sq center_x center_y width

let draw_n_n_squares depth nb_sq center_x center_y width =
	match depth with
		| n when n > 0 ->
			let tot_nb_sq = power nb_sq depth in
			std_pencil () ;
			draw_n_squares tot_nb_sq center_x center_y width ;
			draw_borders depth nb_sq center_x center_y width
		| _ -> ignore ()

let draw_tic_tac_toe tab =
	draw_n_n_squares 3 2 (width / 2) (height / 2) 60

let () =
	init () ;
    draw_tic_tac_toe "salut" ;
	ignore (read_line () )
