

type game = {
	board:		BoardType.t ;
	red_turn:	bool ;
	game_state:	string ;
	heuristic:	(BoardType.t -> int -> int -> ((int * int) list) -> int) ;
	depth:		int ;
	valid_next:	(int * int) list option
}

let rec print_moves = function
	| [] -> print_endline "" ;
	| (y, x) :: tl -> Printf.printf "(%d, %d)\n" y x ; print_moves tl

let make_new_game dimensions heuristic depth =
	{
		board = Board.make_board dimensions ;
		red_turn = true ;
		game_state = "playing" ;
		heuristic = heuristic ;
		depth = depth ;
		valid_next = None
	}

let make_actual_move game y x score forced_next valid_next =
	let heur_change, game_state = (
		match score with
		| Heuristic.Win -> Lwt_io.printf "win\n" ; 0, "win"
		| Heuristic.Loss -> Lwt_io.printf "loss\n" ; 0, "loss"
		| Heuristic.Score sc -> Lwt_io.printf "playing %d\n" sc ; sc, "playing"
	) in
	Board.place_tile game.board y x heur_change game.red_turn ;
	let _, next_moves = Board.valid_moves game.board ~is_red:(not game.red_turn) ~heuristic:game.heuristic in
	let game_state = if List.length next_moves = 0 then "draw" else game_state in
	let valid_next = if forced_next then Some valid_next else None in
	{
		board = game.board ;
		red_turn = not game.red_turn ;
		game_state = game_state ;
		heuristic = game.heuristic ;
		depth = game.depth ;
		valid_next = valid_next
	}

let make_move game (y, x) =
	let rec _move_in_valid_next nexts =
		match nexts with
		| [] -> false
		| (_y, _x) :: rest -> if _y = y && _x = x then true else _move_in_valid_next rest
	in
	let continue = (match game.valid_next with
		| None -> true
		| Some nexts -> _move_in_valid_next nexts
	) in
	if not continue then (false, game)
	else (
		let ok, (score, (forced_next, valid_next)) = Board.can_place_tile game.board y x game.red_turn (Some game.heuristic) in
		if not ok then (false, game)
		else (
			let new_game = make_actual_move game y x score forced_next valid_next in
			(true, new_game)
		)
	)

let make_ai_move game =
	let start_time = Unix.gettimeofday () in
	let move = Minimax.best_move game.board
		~for_red:game.red_turn
		~valid_next:game.valid_next
		~heuristic:game.heuristic
		~depth:game.depth
	in
	let end_time = Unix.gettimeofday () in
	match move with
	| None -> (None, game), 0
	| Some (y, x, (_, (forced_next, valid_next))) -> (
		let _, (score, _) = Board.can_place_tile game.board y x game.red_turn (Some game.heuristic) in
		let new_game = make_actual_move game y x score forced_next valid_next in
		(Some (y, x), new_game), (int_of_float ((end_time -. start_time) *. 1000.0))
	)

(*
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
		~depth:4
	in
	match best with
	| None -> Printf.printf "DRAW!!!!\n"
	| Some (y, x, score) -> Printf.printf "best move : %d %d\n" y x
	(**let moves = Board.valid_moves board true in
	print_moves moves**)

*)