

let rec print_moves = function
	| [] -> print_endline "" ;
	| (y, x) :: tl -> Printf.printf "(%d, %d)\n" y x ; print_moves tl

let () =
	let board = Board.make_board 19 in
	ignore (Board.place_tile board 1 1 true) ;
	ignore (Board.place_tile board 2 2 true) ;
	ignore (Board.place_tile board 4 5 true) ;
	ignore (Board.place_tile board 4 6 true) ;
	ignore (Board.place_tile board 4 6 false) ;
	ignore (Board.place_tile board 7 6 false) ;
	ignore (Board.place_tile board 7 7 false) ;
	ignore (Board.place_tile board 8 6 false) ;

	ignore (Board.place_tile board 14 10 false) ;
	ignore (Board.place_tile board 14 13 false) ;
	ignore (Board.place_tile board 14 11 false) ;
	Board.print_board ~min:true board ;
	let moves = Board.valid_moves board true in
	print_moves moves