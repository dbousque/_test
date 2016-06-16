

type 'a tree = Nil | Node of 'a * 'a tree * 'a tree

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

let draw_text_in_box text x y =
	draw_rectangle x y 70 50 ;
	Graphics.moveto (x - 15) (y - 5) ;
	Graphics.draw_string text

let draw_tree_node node =
	let rec draw_tree node x y =
		match node with
		| Nil -> draw_text_in_box "Nil" x y
		| Node (value, l, r) ->
			draw_text_in_box value x y ;
			draw_line (x + 35) y (x + 35 + 100) (y + 50) ;
			draw_line (x + 35) y (x + 35 + 100) (y - 50) ;
			draw_tree r (x + 170) (y + 50) ;
			draw_tree l (x + 170) (y - 50)
	in
	draw_tree node 100 300

let () =
	Graphics.open_graph " 800x600" ;
	draw_square 70 70 100 ;
	draw_tree_node (Node ("salut", Nil, Nil)) ;
	ignore (read_line ())
