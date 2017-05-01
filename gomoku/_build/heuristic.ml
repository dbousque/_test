

open BoardType

type score =
	| Win
	| Loss
	| Score of int

let better_score_red score1 score2 =
	match score1 with
	| Win -> Win
	| Loss -> score2
	| Score i1 -> (
		match score2 with
		| Win -> Win
		| Loss -> score1
		| Score i2 -> Score (max i1 i2)
	)

let better_score_blue score1 score2 =
	match score1 with
	| Win -> score2
	| Loss -> Loss
	| Score i1 -> (
		match score2 with
		| Win -> score1
		| Loss -> Loss
		| Score i2 -> Score (min i1 i2)
	)

let void_score = Loss

let zero_heuristic board y x captures valid_next =
	0

let random_heuristic board y x captures valid_next =
	(Random.int 20) - 10

let simple_heuristic_time_var = ref 0.0

let simple_heuristic_time () =
	!simple_heuristic_time_var

let simple_heuristic board y x captures valid_next =
	(*let start = Unix.gettimeofday () in *)
	let tile = board.tiles.(y).(x) in
	let rec _count_on_line _y _x y_decal x_decal miss acc =
		let _y = _y + y_decal in
		let _x = _x + x_decal in
		if _y < 0 || _y >= Array.length board.tiles || _x < 0 || _x >= Array.length board.tiles then
			acc
		else (
			if board.tiles.(_y).(_x) = Tile.Empty then (
				if miss >= 1 then acc
				else _count_on_line _y _x y_decal x_decal (miss + 1) acc
			)
			else (
				if board.tiles.(_y).(_x) = tile then (
					_count_on_line _y _x y_decal x_decal miss (acc + 1)
				)
				else acc
			)
		)
	in
	let dirs = [
		(0, 1); (1, 0); (1, 1); ((-1), 1);
		(0, (-1)); ((-1), 0); ((-1), (-1)); (1, (-1))
	] in
	let _acc_helper acc (y_decal, x_decal) =
		let on_line = _count_on_line y x y_decal x_decal 0 0 in
		acc + (if on_line > 0 then on_line + 1 else on_line)
	in
	let score = List.fold_left _acc_helper 0 dirs in
	let score = score + (List.length captures * 4) in
	(*simple_heuristic_time_var := !simple_heuristic_time_var +. (Unix.gettimeofday () -. start) ; *)
	if tile = Tile.Red then score else (- score)

let common_standard board y x captures valid_next ~second_version =
	let tile = board.tiles.(y).(x) in
	let other_tile = if tile = Tile.Red then Tile.Blue else Tile.Red in
	let board_len = Array.length board.tiles in
	let _valid_coords _y _x =
		_y >= 0 && _y < board_len && _x >= 0 && _x < board_len
	in
	let _free_to_become_five () =
		(*
		let _free_to_win_dir y_decal x_decal =
			let _ok_at _y _x =
				_valid_coords _y _x &&
				(board.tiles.(_y).(_x) = tile || board.tiles.(_y).(_x) = Tile.Empty)
			in
			let rec __free_to_win_dir _y _x _y_decal _x_decal acc =
				if acc >= 5 then acc
				else (
					if _ok_at _y _x then
						__free_to_win_dir (_y + _y_decal) (_x + _x_decal) _y_decal _x_decal (acc + 1)
					else
						acc
				)
			in
			let fst = __free_to_win_dir (y + y_decal) (x + x_decal) y_decal x_decal 0 in
			let snd = __free_to_win_dir (y - y_decal) (x - x_decal) (- y_decal) (- x_decal) 0 in
			let tot = fst + snd in
			if tot >= 5 then 2 else if tot >= 4 then 1 else 0
		in
		*)
		let _free_to_win_dir y_decal x_decal =
			let _ok_at _y _x =
				_valid_coords _y _x &&
				(board.tiles.(_y).(_x) = tile || board.tiles.(_y).(_x) = Tile.Empty)
			in
			let _six_free () =
				_ok_at (y + y_decal * 3) (x + x_decal * 3) ||
				_ok_at (y - y_decal * 3) (x - x_decal * 3)
			in
			let free =
				_ok_at (y + y_decal * 1) (x + x_decal * 1) &&
				_ok_at (y + y_decal * 2) (x + x_decal * 2) &&
				_ok_at (y - y_decal * 1) (x - x_decal * 1) &&
				_ok_at (y - y_decal * 2) (x - x_decal * 2)
			in
			if free then (if _six_free () then 2 else 1) else 0
		in
		let scores = [
			_free_to_win_dir 1 0 ;
			_free_to_win_dir 0 1 ;
			_free_to_win_dir 1 1 ;
			_free_to_win_dir (-1) 1
		] in
		let scores = List.sort (fun a b -> b - a) scores in
		match scores with
		| fst :: snd :: _ -> fst + snd
		| _ -> failwith "error"
	in
	let dirs_decals = [0, 1; 0, (-1); 1, 0; (-1), 0; 1, 1; (-1), (-1); (-1), 1; 1, (-1)] in
	let _sum_for_all_dirs func =
		List.fold_left (fun acc (y_decal, x_decal) -> acc + func y_decal x_decal) 0 dirs_decals
	in
	let _score_alignements () =
		let _score_dir y_decal x_decal =
			let rec __score_dir _y _x acc empty_seen =
				if not (_valid_coords _y _x) then acc
				else (
					let next_y, next_x = (_y + y_decal), (_x + x_decal) in
					match board.tiles.(_y).(_x) with
					| Tile.Empty -> if empty_seen >= 1 then acc else __score_dir next_y next_x acc (empty_seen + 1)
					| t -> if t = tile then __score_dir next_y next_x (acc + 1) empty_seen else acc
				)
			in
			__score_dir (y + y_decal) (x + x_decal) 0 0
		in
		_sum_for_all_dirs _score_dir
	in
	let _can_make_captures () =
		let _can_make_captures_dir y_decal x_decal =
			if not (_valid_coords (y + y_decal * 3) (x + x_decal * 3)) then 0
			else (
				if
					board.tiles.(y + y_decal * 1).(x + x_decal * 1) = other_tile &&
					board.tiles.(y + y_decal * 2).(x + x_decal * 2) = other_tile &&
					board.tiles.(y + y_decal * 3).(x + x_decal * 3) = Tile.Empty
				then 1
				else 0
			)
		in
		_sum_for_all_dirs _can_make_captures_dir
	in
	let _makes_other_capture_possible () =
		let _makes_other_capture_possible_dir y_decal x_decal =
			if
				_valid_coords (y - y_decal * 2) (x - x_decal * 2) &&
				_valid_coords (y + y_decal * 1) (x + x_decal * 1) &&
				board.tiles.(y - y_decal * 1).(x - x_decal * 1) = tile &&
				(
					(
						board.tiles.(y + y_decal * 1).(x + x_decal * 1) = Tile.Empty &&
						board.tiles.(y - y_decal * 2).(x - x_decal * 2) = other_tile
					) ||
					(
						board.tiles.(y - y_decal * 2).(x - x_decal * 2) = Tile.Empty &&
						board.tiles.(y + y_decal * 1).(x + x_decal * 1) = other_tile
					)
				)
				then (- 2)
			else 0
		in
		_sum_for_all_dirs _makes_other_capture_possible_dir
	in
	let _makes_free_threes () =
		let threes = FreeThrees.free_threes board.tiles y x tile in
		List.length threes * 3
	in
	let _makes_free_fours _y _x tile =
		let _makes_free_fours_dir y_decal x_decal =
			let rec __makes_free_fours _y _x _y_decal _x_decal acc =
				let _y, _x = _y + _y_decal, _x + _x_decal in
				if not (_valid_coords _y _x) then acc, false
				else (
					let is_empty = board.tiles.(_y).(_x) = Tile.Empty in
					if acc >= 3 then 3, is_empty
					else (
						if board.tiles.(_y).(_x) = tile then __makes_free_fours _y _x _y_decal _x_decal (acc + 1)
						else acc, is_empty
					)
				)
			in
			if board.tiles.(_y).(_x) <> tile then 0
			else (
				let fst, empty1 = __makes_free_fours y x y_decal x_decal 0 in
				let snd, empty2 = __makes_free_fours y x (- y_decal) (- x_decal) 0 in
				let empty = empty1 && empty2 in
				if fst + snd >= 3 && empty then 1000 else 0
			)
		in
		_makes_free_fours_dir 0 1 +
		_makes_free_fours_dir 1 0 +
		_makes_free_fours_dir 1 1 +
		_makes_free_fours_dir (-1) 1
	in
	let _stops_other_free_threes () =
		let _stops_other_free_threes_dir y_decal x_decal =
			let _y, _x = y + y_decal, x + x_decal in
			if not (_valid_coords _y _x) || board.tiles.(_y).(_x) <> other_tile then 0
			else (
				let threes = FreeThrees.free_threes board.tiles _y _x other_tile in
				List.length threes * 3
			)
		in
		let _stops_other_free_threes_dir_not_made y_decal x_decal =
			let _y, _x = y + y_decal, x + x_decal in
			if not (_valid_coords _y _x) || board.tiles.(_y).(_x) <> other_tile then 0
			else (
				let threes = FreeThrees.free_threes board.tiles _y _x other_tile in
				List.length threes * 1
			)
		in
		board.tiles.(y).(x) <- Tile.Empty ;
		let res = _sum_for_all_dirs _stops_other_free_threes_dir in
		board.tiles.(y).(x) <- other_tile ;
		let res = res + _sum_for_all_dirs _stops_other_free_threes_dir_not_made in
		board.tiles.(y).(x) <- tile ;
		res
	in
	let _stops_other_free_fours () =
		0
	in
	let score = (List.length captures * 4) in
	let score = score + _free_to_become_five () in
	let score = score + _score_alignements () in
	let score = score + _makes_other_capture_possible () in
	let score = score + _makes_free_threes () in
	let score = score + _makes_free_fours y x tile in
	(*let score = if second_version then score + _stops_other_free_threes () else score in*)
	let score = if second_version then score + _stops_other_free_fours () else score in
	let score = if second_version then score + (if List.length valid_next > 0 then 1000 else 0) else score in
	if tile = Tile.Red then score else (- score)

let standard_heuristic board y x captures valid_next =
	common_standard board y x captures valid_next ~second_version:false

let standard_heuristic2 board y x captures valid_next =
	common_standard board y x captures valid_next ~second_version:true