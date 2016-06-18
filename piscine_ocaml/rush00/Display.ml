

let init () =
    Graphics.open_graph " 800x800"

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

let () =
    draw_square 400 400 200
