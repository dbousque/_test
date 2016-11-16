

type move = Left | Right | Up | Down

type search_result = {
	nb_states_selected: int ;
	max_nb_states_in_mem: int ;
	moves: move list
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
	  } -> Printf.printf "Number of states selected : %d\nMaximum number of states in memory : %d\n" ; print_moves moves

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

let solve_board board =
	let available_moves = get_available_moves board in
	{
		nb_states_selected = 1 ;
		max_nb_states_in_mem = 4 ;
		moves = available_moves
	}