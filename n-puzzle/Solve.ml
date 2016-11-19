

type move = Left | Right | Up | Down

type searchnode = {
	board: Board.t ;
	done_moves: move list
}

type search_result = {
	nb_states_selected: int ;
	max_nb_states_in_mem: int ;
	moves: move list ;
	solvable: bool
}

let rec print_moves = function
	| [] -> print_endline ""
	| h::tl -> let repr = match h with
				| Left -> "Left"
				| Right -> "Right"
				| Up -> "Up"
				| Down -> "Down" in
				print_string (repr ^ " ") ;
				print_moves tl

let print_result result =
	match result with
	| {
		nb_states_selected = nb_selected ;
		max_nb_states_in_mem = max_in_mem ;
		moves = moves
	  } -> Printf.printf "Number of states selected : %d\nMaximum number of states in memory : %d\n" nb_selected max_in_mem ; print_moves moves

let get_available_moves board =
	let left_ok = snd board.Board.empty_cell > 0 in
	let right_ok = snd board.Board.empty_cell < (board.Board.size - 1) in
	let up_ok = fst board.Board.empty_cell > 0 in
	let down_ok = fst board.Board.empty_cell < (board.Board.size - 1) in
	let ret = [] in
	let ret = if left_ok then Left::ret else ret in
	let ret = if right_ok then Right::ret else ret in
	let ret = if up_ok then Up::ret else ret in
	let ret = if down_ok then Down::ret else ret in
	ret

let make_move board move =
	let _apply_move board = function
		| Left -> Board.make_move board (-1) 0
		| Right -> Board.make_move board 1 0
		| Up -> Board.make_move board 0 (-1)
		| Down -> Board.make_move board 0 1
	in
	match board with
	| { board = board ; done_moves = done_moves } -> {board = _apply_move board move ; done_moves = move::done_moves}

let rec already_considered considered board =
	List.exists (fun x -> x = board) considered

let rec add_new_boards nodes considered new_boards scores =
	match new_boards with
	| [] -> nodes
	| board::rest -> let nodes = if already_considered considered board.board then nodes else
						PriorityQueue.add nodes board (hd scores) in
					 add_new_boards nodes considered rest (tl scores)

let rec solve_board_rec nodes considered score_func end_positions nb_selected nb_max =
	if PriorityQueue.size nodes = 0 then
		{
			nb_states_selected = nb_selected ;
			max_nb_states_in_mem = nb_max ;
			moves = [] ;
			solvable = false
		}
	let nb_max = if nb_max > PriorityQueue.size nodes + nb_selected then nb_max else PriorityQueue.size + nb_selected in
	let nb_selected = nb_selected + 1 in
	let best_board, nodes = PriorityQueue.pop nodes in
	if score_func best_board.board end_positions = 0 then
		{
			nb_states_selected = nb_selected ;
			max_nb_states_in_mem = nb_max ;
			moves = best_board.done_moves ;
			solvable = true
		}
	else solve_board_rec2 nodes considered best_board score_func end_positions nb_selected nb_max

and solve_board_rec2 nodes considered best_board score_func end_positions nb_selected nb_max =
	let available_moves = get_available_moves best_board.board in
	let new_boards = List.map (make_move best_board) available_moves in
	let scores = List.map (fun x -> score_func x.board end_positions) new_boards in
	let nodes = add_new_boards nodes considered new_boards scores in
	let considered = best_board.board::considered in
	solve_board_rec nodes considered score_func end_positions nb_selected nb_max

let solve_board board score_func end_positions =
	let priority_queue = PriorityQueue.make () in
	let priority_queue = PriorityQueue.add priority_queue ({ board = board ; done_moves = [] }) 0 in
	solve_board_rec priority_queue [] score_func end_positions 0 0