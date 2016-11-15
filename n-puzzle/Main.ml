

let () =
	let board = Board.rand_board 4 in
	Board.print_board board ;
	let res = Solve.solve_board board in
	Solve.print_result res