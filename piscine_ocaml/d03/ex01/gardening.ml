

type 'a tree = Nil | Node of 'a * 'a tree * 'a tree

let rec size = function
	| Nil -> 0
	| Node (v, l, r) -> 1 + size l + size r

let maxi a b =
	if b > a then b
	else a

let rec height = function
	| Nil -> 0
	| Node (v, l, r) -> (maxi (height l) (height r)) + 1


	

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
	draw_rectangle x y 70 30 ;
	Graphics.moveto (x - 15) (y - 5) ;
	Graphics.draw_string text

let draw_tree node =
	let rec draw_tr node x y decal =
		match node with
		| Nil -> draw_text_in_box "Nil" x y
		| Node (value, l, r) ->
			draw_text_in_box value x y ;
			draw_line (x + 35) y (x + 35 + 100) (y + decal) ;
			draw_line (x + 35) y (x + 35 + 100) (y - decal) ;
			draw_tr r (x + 170) (y + decal) (decal / 2) ;
			draw_tr l (x + 170) (y - decal) (decal / 2)
	in
	draw_tr node 50 300 125



let print_testing tree =
	print_string "size of tree : " ;
	print_endline (string_of_int (size tree)) ;
	print_string "height of tree : " ;
	print_endline (string_of_int (height tree)) ;
	draw_tree tree ;
	ignore (read_line () )

let () =
	Graphics.open_graph " 800x600" ;
	let tree =
		Node ("root", 
			( Node ("left1",
				( Node ("left2", Nil, Nil) ),
				( Node ("right2",
				  	( Node ("left3", Nil, Nil) ),
					Nil
				))
			)),
			( Node ("right1",
			  	Nil,
			  	( Node ("right3", Nil, Nil) )
			))
		)
	in
	print_testing tree
