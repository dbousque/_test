

open BoardType

let free_threes_time_var = ref 0.0

let free_threes_time () =
	!free_threes_time_var

(*let free_threes board y x tile =
	let _check_four_plus_two_free _y _x y_decal x_decal =
		_y - y_decal >= 0 && _y - y_decal < Array.length board &&
		_x - x_decal >= 0 && _x - x_decal < Array.length board &&
		board.(_y).(_x) = tile &&
		_y + (y_decal * 4) >= 0 && _y + (y_decal * 4) < Array.length board &&
		_x + (x_decal * 4) >= 0 && _x + (x_decal * 4) < Array.length board &&
		board.(_y - y_decal).(_x - x_decal) = Tile.Empty &&
		board.(_y + (y_decal * 4)).(_x + (x_decal * 4)) = Tile.Empty &&
		(
			(
				board.(_y + (y_decal * 1)).(_x + (x_decal * 1)) = tile &&
				board.(_y + (y_decal * 2)).(_x + (x_decal * 2)) = tile &&
				board.(_y + (y_decal * 3)).(_x + (x_decal * 3)) = Tile.Empty
			) ||
			(
				board.(_y + (y_decal * 1)).(_x + (x_decal * 1)) = Tile.Empty &&
				board.(_y + (y_decal * 2)).(_x + (x_decal * 2)) = tile &&
				board.(_y + (y_decal * 3)).(_x + (x_decal * 3)) = tile
			) ||
			(
				board.(_y + (y_decal * 1)).(_x + (x_decal * 1)) = tile &&
				board.(_y + (y_decal * 2)).(_x + (x_decal * 2)) = Tile.Empty &&
				board.(_y + (y_decal * 3)).(_x + (x_decal * 3)) = tile
			)
		)
	in
	let _try_positions y_decal x_decal =
		List.exists (fun i -> _check_four_plus_two_free (y - (i * y_decal)) (x - (i * x_decal)) y_decal x_decal) [0; 1; 2; 3]
	in
	let _add_to_acc acc (y_decal, x_decal, dir) =
		if _try_positions y_decal x_decal then
			dir :: acc 
		else
			acc
	in
	let start = Unix.gettimeofday () in
	let dirs = [(0, 1, Horizontal); (1, 0, Vertical); (1, 1, DiagDown); ((-1), 1, DiagUp)] in
	let res = List.fold_left _add_to_acc [] dirs in
	free_threes_time_var := !free_threes_time_var +. (Unix.gettimeofday () -. start) ;
	res *)

let free_threes board y x tile =
	let board_len = Array.length board in
	let _invalid_coords y x =
		y < 0 || y >= board_len || x < 0 || x >= board_len
	in
	let _valid_coords y x =
		not (_invalid_coords y x)
	in
	let _check_dir y_decal x_decal =
		if _invalid_coords (y - y_decal) (x - x_decal) then false
		else if _invalid_coords (y + y_decal) (x + x_decal) then false
		else if board.(y - y_decal).(x - x_decal) = Tile.Empty then (
			if board.(y + y_decal).(x + x_decal) = Tile.Empty then (
				if
					_valid_coords (y + (y_decal * 4)) (x + (x_decal * 4)) &&
					board.(y + (y_decal * 2)).(x + (x_decal * 2)) = tile &&
					board.(y + (y_decal * 3)).(x + (x_decal * 3)) = tile &&
					board.(y + (y_decal * 4)).(x + (x_decal * 4)) = Tile.Empty
					then true
				else if
					_valid_coords (y - (y_decal * 4)) (x - (x_decal * 4)) &&
					board.(y - (y_decal * 2)).(x - (x_decal * 2)) = tile &&
					board.(y - (y_decal * 3)).(x - (x_decal * 3)) = tile &&
					board.(y - (y_decal * 4)).(x - (x_decal * 4)) = Tile.Empty
					then true
				else false
			)
			else if board.(y + y_decal).(x + x_decal) = tile then (
				if
					_valid_coords (y + (y_decal * 3)) (x + (x_decal * 3)) &&
					board.(y + (y_decal * 2)).(x + (x_decal * 2)) = tile &&
					board.(y + (y_decal * 3)).(x + (x_decal * 3)) = Tile.Empty &&
					(
						(
							_valid_coords (y - (y_decal * 2)) (x - (x_decal * 2)) &&
							board.(y - (y_decal * 2)).(x - (x_decal * 2)) = Tile.Empty
						) ||
						(
							_valid_coords (y + (y_decal * 4)) (x + (x_decal * 4)) &&
							board.(y + (y_decal * 4)).(x + (x_decal * 4)) = Tile.Empty
						)
					)
					then true
				else if
					_valid_coords (y + (y_decal * 2)) (x + (x_decal * 2)) &&
					_valid_coords (y - (y_decal * 3)) (x - (x_decal * 3)) &&
					board.(y + (y_decal * 2)).(x + (x_decal * 2)) = Tile.Empty &&
					board.(y - (y_decal * 2)).(x - (x_decal * 2)) = tile &&
					board.(y - (y_decal * 3)).(x - (x_decal * 3)) = Tile.Empty
					then true
				else if
					_valid_coords (y + (y_decal * 4)) (x + (x_decal * 4)) &&
					board.(y + (y_decal * 2)).(x + (x_decal * 2)) = Tile.Empty &&
					board.(y + (y_decal * 3)).(x + (x_decal * 3)) = tile &&
					board.(y + (y_decal * 4)).(x + (x_decal * 4)) = Tile.Empty
					then true
				else false
			)
			else false
		)
		else if board.(y - y_decal).(x - x_decal) = tile then (
			if board.(y + y_decal).(x + x_decal) = Tile.Empty then (
				if
					_valid_coords (y + (y_decal * 3)) (x + (x_decal * 3)) &&
					_valid_coords (y - (y_decal * 2)) (x - (x_decal * 2)) &&
					board.(y + (y_decal * 2)).(x + (x_decal * 2)) = tile &&
					board.(y - (y_decal * 2)).(x - (x_decal * 2)) = Tile.Empty &&
					board.(y + (y_decal * 3)).(x + (x_decal * 3)) = Tile.Empty
					then true
				else if
					_valid_coords (y - (y_decal * 4)) (x - (x_decal * 4)) &&
					board.(y - (y_decal * 2)).(x - (x_decal * 2)) = Tile.Empty &&
					board.(y - (y_decal * 3)).(x - (x_decal * 3)) = tile &&
					board.(y - (y_decal * 4)).(x - (x_decal * 4)) = Tile.Empty
					then true
				else if
					_valid_coords (y - (y_decal * 3)) (x - (x_decal * 3)) &&
					board.(y - (y_decal * 2)).(x - (x_decal * 2)) = tile &&
					board.(y - (y_decal * 3)).(x - (x_decal * 3)) = Tile.Empty &&
					(
						(
							_valid_coords (y - (y_decal * 4)) (x - (x_decal * 4)) &&
							board.(y - (y_decal * 4)).(x - (x_decal * 4)) = Tile.Empty
						) ||
						(
							_valid_coords (y + (y_decal * 2)) (x + (x_decal * 2)) &&
							board.(y + (y_decal * 2)).(x + (x_decal * 2)) = Tile.Empty
						)
					)
					then true
				else false
			)
			else if board.(y + y_decal).(x + x_decal) = tile then (
				if
					_valid_coords (y + (y_decal * 2)) (x + (x_decal * 2)) &&
					_valid_coords (y - (y_decal * 2)) (x - (x_decal * 2)) &&
					board.(y - (y_decal * 2)).(x - (x_decal * 2)) = Tile.Empty &&
					board.(y + (y_decal * 2)).(x + (x_decal * 2)) = Tile.Empty &&
					(
						(
							_valid_coords (y - (y_decal * 3)) (x - (x_decal * 3)) &&
							board.(y - (y_decal * 3)).(x - (x_decal * 3)) = Tile.Empty
						) ||
						(
							_valid_coords (y + (y_decal * 3)) (x + (x_decal * 3)) &&
							board.(y + (y_decal * 3)).(x + (x_decal * 3)) = Tile.Empty
						)
					)
					then true
				else false
			)
			else false
		)
		else false
	in
	(*let start = Unix.gettimeofday () in *)
	let dirs = [(0, 1, Horizontal); (1, 0, Vertical); (1, 1, DiagDown); ((-1), 1, DiagUp)] in
	let _add_to_acc acc (y_decal, x_decal, dir) =
		if _check_dir y_decal x_decal then dir :: acc else acc
	in
	let res = List.fold_left _add_to_acc [] dirs in
	(*free_threes_time_var := !free_threes_time_var +. (Unix.gettimeofday () -. start) ; *)
	res

(*let test_free_threes () =
	let rec _print_dirs = function
		| [] -> Printf.printf "\n"
		| fst :: rest -> (
			( match fst with
			| Horizontal -> Printf.printf "Horizontal, "
			| Vertical -> Printf.printf "Vertical, "
			| DiagUp -> Printf.printf "DiagUp, "
			| DiagDown -> Printf.printf "DiagDown, " ) ;
			_print_dirs rest
		)
	in
	let board = make_board 19 in
	ignore (place_tile board 10 10 0 true) ;
	ignore (place_tile board 10 11 0 true) ;
	ignore (place_tile board 8 7 0 true) ;
	ignore (place_tile board 7 6 0 true) ;
	print_board ~min:true board ;
	let threes = free_threes board.tiles 10 9 Tile.Red in
	match threes with
	| [] -> Printf.printf "EMPTY!\n"
	| dirs -> _print_dirs dirs*)