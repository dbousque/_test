

let handle_board heuristic greedy in_place board =
	Board.print_board board ;
	let end_positions = Board.make_end_positions board in
	let res = Solve.solve_board board heuristic greedy end_positions in
	if Solve.is_solvable res = false then
		print_endline "unsolvable"
	else (
		Solve.make_moves ~in_place:in_place board res ;
		Solve.print_result res
	)

let rec handle_files heuristic greedy in_place = function
	| [] -> ()
	| file::rest -> let board = Parse.parse_file file in
					handle_board heuristic greedy in_place board ;
					handle_files heuristic greedy in_place rest

let () =
	let options = Parse.parse_options () in
	let heuristic = match options.Parse.heuristic with
		| "manhattan" -> Board.manhattan_distance
		| "misplaced" -> Board.misplaced
		| "crow" -> Board.as_the_crow_flies_distance
		| _ -> raise (Failure "Unknown heuristic")
	in
	let greedy = options.Parse.greedy in
	let in_place = options.Parse.in_place in
	let n = options.Parse.n in
	let files = options.Parse.files in
	if List.length files = 0 then
		handle_board heuristic greedy in_place (Board.rand_board n)
	else
		handle_files heuristic greedy in_place (List.rev files)