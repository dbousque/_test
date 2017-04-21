

let rec print_moves = function
	| [] -> print_endline "" ;
	| (y, x) :: tl -> Printf.printf "(%d, %d)\n" y x ; print_moves tl

let () =
	let board = Board.make_board 19 in
	ignore (Board.place_tile board 1 1 0 true) ;
	ignore (Board.place_tile board 2 2 0 true) ;
	ignore (Board.place_tile board 4 5 0 true) ;
	ignore (Board.place_tile board 4 6 0 true) ;
	ignore (Board.place_tile board 4 6 0 false) ;
	ignore (Board.place_tile board 7 6 0 false) ;
	ignore (Board.place_tile board 7 7 0 false) ;
	ignore (Board.place_tile board 8 6 0 false) ;

	ignore (Board.place_tile board 14 10 0 false) ;
	ignore (Board.place_tile board 14 13 0 false) ;
	ignore (Board.place_tile board 14 11 0 false) ;
	Board.print_board ~min:true board ;
	(*for i = 0 to 10000 do
		ignore (Board.valid_moves board ~is_red:true ~heuristic:Heuristic.simple_heuristic)
	done ; *)
	let best = Minimax.best_move board
		~for_red:true
		~valid_next:None
		~heuristic:Heuristic.simple_heuristic
		~depth:3
	in
	match best with
	| None -> Printf.printf "DRAW!!!!\n"
	| Some (y, x, score) -> Printf.printf "best move : %d %d\n" y x
	(**let moves = Board.valid_moves board true in
	print_moves moves**)