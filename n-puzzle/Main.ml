

let () =
	let board = Board.rand_board 3 in
	Board.print_board board ;
	let end_positions = Board.make_end_positions board in
	Array.iter (fun (x,y) -> Printf.printf "(%d, %d)" x y) end_positions ;
	print_endline "" ;
	let res = Solve.solve_board board in
	Solve.print_result res ;
	Printf.printf "cost : %d\n" (Board.manhattan_distance board end_positions)