

let () =
	let heuristic = Board.misplaced in
	let greedy = true in
	let board = Board.rand_board 4 in
	Board.print_board board ;
	let end_positions = Board.make_end_positions board in
	let res = Solve.solve_board board heuristic greedy end_positions in
	if Solve.is_solvable res = false then
		print_endline "unsolvable"
	else (
		Solve.make_moves ~in_place:false board res ;
		Solve.print_result res
	)