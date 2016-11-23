

type move = Left | Right | Up | Down

type searchnode = {
	board: Board.t ;
	done_moves: move list ;
	nb_moves: int
}

type boardtree = Tiles of (int, boardtree) Hashtbl.t

module NPuzzleNode : PriorityQueue.NODE with type t = searchnode =
struct
    type t = searchnode
    let zero = { board = Board.rand_board 3 ; done_moves = [] ; nb_moves = 0 }
end

module NodesPriorityQueue : (PriorityQueue.PRIORITYQUEUE with type nodetype = searchnode) =
	PriorityQueue.MakePriorityQueue (NPuzzleNode)

type search_result = {
	nb_states_selected: int ;
	max_nb_states_in_mem: int ;
	nodes: NodesPriorityQueue.t ;
	considered: boardtree ;
	moves: move list ;
	solvable: bool
}

let is_solvable ({nb_states_selected = _ ; max_nb_states_in_mem = _ ; nodes = _ ; considered = _ ; moves = _ ; solvable = solvable}) =
	solvable

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
	  } -> Printf.printf "Number of states selected : %d\nMaximum number of states in memory : %d\nNumber of moves : %d\n" nb_selected max_in_mem (List.length moves) ;
	  print_string "Moves : " ;
	  print_moves (List.rev moves)

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
	| { board = board ; done_moves = done_moves ; nb_moves = nb_moves } -> {board = _apply_move board move ; done_moves = move::done_moves ; nb_moves = nb_moves + 1}

let add_considered_board considered board =
	let _add_tile (Tiles current_ht) tile =
		try Hashtbl.find current_ht tile with
		| Not_found ->  let new_ht = Tiles (Hashtbl.create (board.Board.size)) in
						Hashtbl.add current_ht tile new_ht ;
						new_ht
	in
	let rec _add_row current_ht = function
		| [] -> current_ht
		| tile::rest -> _add_row (_add_tile current_ht tile) rest
	in
	let rec _add_board considered = function
		| [] -> ()
		| row::rest -> _add_board (_add_row considered row) rest
	in
	_add_board considered board.Board.tiles

let rec already_considered considered board =
	let _has_tile (Tiles current_ht) tile =
		Hashtbl.mem current_ht tile
	in
	let rec _has_row (Tiles current_ht) = function
		| [] -> (true, Tiles current_ht)
		| tile::rest ->  if _has_tile (Tiles current_ht) tile = false then
							(false, Tiles current_ht)
						 else
						 	_has_row (Hashtbl.find current_ht tile) rest
	in
	let rec _has_board considered = function
		| [] -> true
		| row::rest ->  let has_row, considered = _has_row considered row in
						if has_row = false then false else _has_board considered rest
	in
	_has_board considered board.Board.tiles

let rec add_new_boards nodes considered new_boards scores =
	match new_boards with
	| [] -> nodes
	| board::rest -> let nodes = if already_considered considered board.board then nodes else
						NodesPriorityQueue.add nodes board (List.hd scores) in
					 add_new_boards nodes considered rest (List.tl scores)

let rec solve_board_rec nodes considered greedy score_func end_positions nb_selected nb_max counter =
	if NodesPriorityQueue.size nodes = 0 || counter = 0 then
		{
			nb_states_selected = nb_selected ;
			max_nb_states_in_mem = nb_max ;
			nodes = nodes ;
			considered = considered ;
			moves = [] ;
			solvable = false
		}
	else (
		let nb_max = if nb_max > NodesPriorityQueue.size nodes then nb_max else NodesPriorityQueue.size nodes in
		let nb_selected = nb_selected + 1 in
		let best_board, nodes = NodesPriorityQueue.pop nodes in
		add_considered_board considered best_board.board ;
		if score_func best_board.board end_positions = 0 then
			{
				nb_states_selected = nb_selected ;
				max_nb_states_in_mem = nb_max ;
				nodes = nodes ;
				considered = considered ;
				moves = best_board.done_moves ;
				solvable = true
			}
		else solve_board_rec2 nodes considered greedy best_board score_func end_positions nb_selected nb_max counter
	)

and solve_board_rec2 nodes considered greedy best_board score_func end_positions nb_selected nb_max counter =
	let node_score node =
		let start = if greedy = false then node.nb_moves else 0 in
		start + (score_func node.board end_positions)
	in
	let available_moves = get_available_moves best_board.board in
	let new_boards = List.map (make_move best_board) available_moves in
	let scores = List.map node_score new_boards in
	let nodes = add_new_boards nodes considered new_boards scores in
	solve_board_rec nodes considered greedy score_func end_positions nb_selected nb_max (counter - 1)

let solve_board board score_func greedy end_positions =
	let _change_solvability board =
		let first = List.nth (List.nth board.Board.tiles 0) 0 in
		let second = List.nth (List.nth board.Board.tiles 0) 1 in
		let row = if first = 0 || second = 0 then 1 else 0 in
		let arr_board = Array.of_list (List.map Array.of_list board.Board.tiles) in
		let tmp = arr_board.(row).(0) in
		Array.set arr_board.(row) 0 (arr_board.(row).(1)) ;
		Array.set arr_board.(row) 1 tmp ;
		{
			Board.tiles = Array.to_list (Array.map Array.to_list arr_board) ;
			Board.empty_cell = board.Board.empty_cell ;
			Board.size = board.Board.size
		}
	in
	let rec _solve_board priority_queue1 priority_queue2 considered1 considered2 nb_selected1 nb_selected2 nb_max1 nb_max2 =
		let ret1 = solve_board_rec priority_queue1 considered1 greedy score_func end_positions nb_selected1 nb_max1 1000 in
		if ret1.solvable then ret1
		else (
			let ret2 = solve_board_rec priority_queue2 considered2 greedy score_func end_positions nb_selected2 nb_max2 1000 in
			if ret2.solvable then ret1
			else _solve_board ret1.nodes ret2.nodes ret1.considered ret2.considered ret1.nb_states_selected ret2.nb_states_selected ret1.max_nb_states_in_mem ret2.max_nb_states_in_mem
		)
	in
	let priority_queue1 = NodesPriorityQueue.make () in
	let priority_queue1 = NodesPriorityQueue.add priority_queue1 ({ board = board ; done_moves = [] ; nb_moves = 0 }) 0 in
	let priority_queue2 = NodesPriorityQueue.make () in
	let priority_queue2 = NodesPriorityQueue.add priority_queue2 ({ board = (_change_solvability board) ; done_moves = [] ; nb_moves = 0 }) 0 in
	let void_boardtree1 = Tiles (Hashtbl.create (board.Board.size)) in
	let void_boardtree2 = Tiles (Hashtbl.create (board.Board.size)) in
	_solve_board priority_queue1 priority_queue2 void_boardtree1 void_boardtree2 0 0 0 0

let make_moves ?(in_place=false) board search_res =
	if in_place then ignore (Unix.system "tput civis") ;
	let rec _n_times_str str = function
		| n when n <= 0 -> ""
		| n -> str ^ (_n_times_str str (n - 1))
	in
	let rec _print_moves board = function
		| [] -> ()
		| move::rest -> let board = { board = board ; done_moves = [] ; nb_moves = 0} in
						let board = make_move board move in
						let board = match board with | { board = board ; done_moves = mvs ; nb_moves = n} -> board in
						let move_str = (match move with
							| Left -> "Left"
							| Right -> "Right"
							| Up -> "Up"
							| Down -> "Down"
						) in
						print_endline ("Making move : " ^ move_str) ;
						Board.print_raw_board board ;
						if in_place && List.length rest > 0 then (Unix.sleepf 0.7 ; ignore (Unix.system ((_n_times_str "tput cuu1 && tput el && " (board.Board.size + 2)) ^ "echo \"\""))) ;
						_print_moves board rest
	in
	_print_moves board (List.rev search_res.moves) ;
	if in_place then ignore (Unix.system "tput cnorm")
