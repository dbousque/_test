

open BoardType

type captures = (int * int) list

type dir = Horizontal | Vertical | DiagUp | DiagDown

let make_board n =
	{
		tiles = Array.init n (fun i -> Array.make n Tile.Empty) ;
		heur_value = 0 ;
		blue_taken = 0 ;
		red_taken = 0
	}

let place_tile_raw board y x is_red =
	let tile = if is_red then Tile.Red else Tile.Blue in
	let other_tile = if is_red then Tile.Blue else Tile.Red in
	Array.set board.(y) x tile ;
	let _make_capture y_decal x_decal acc =
		if (y + (y_decal * 3) >= 0 && y + (y_decal * 3) < Array.length board &&
			x + (x_decal * 3) >= 0 && x + (x_decal * 3) < Array.length board &&
			board.(y + (y_decal * 1)).(x + (x_decal * 1)) = other_tile &&
			board.(y + (y_decal * 2)).(x + (x_decal * 2)) = other_tile &&
			board.(y + (y_decal * 3)).(x + (x_decal * 3)) = tile) then (
				board.(y + (y_decal * 1)).(x + (x_decal * 1)) <- Tile.Empty ;
				board.(y + (y_decal * 2)).(x + (x_decal * 2)) <- Tile.Empty ;
				(y_decal, x_decal) :: acc
			)
		else
			acc
	in
	let decals_list = [(0, 1); (0, (-1)); (1, 0); ((-1), 0); (1, 1); ((-1), (-1)); ((-1), 1); (1, (-1))] in
	List.fold_left (fun acc (y_decal, x_decal) -> _make_capture y_decal x_decal acc) [] decals_list

let place_tile board y x heur_value_change is_red =
	let capt = place_tile_raw board.tiles y x is_red in
	let gain = List.length capt * 2 in
	(if is_red then
		board.blue_taken <- board.blue_taken + gain
	else
		board.red_taken <- board.red_taken + gain) ;
	board.heur_value <- board.heur_value + heur_value_change ;
	capt

let cancel_move_raw board y x is_red captures =
	let other_tile = if is_red then Tile.Blue else Tile.Red in
	let rec _cancel_captures = function
		| [] -> ()
		| (decal_y, decal_x) :: tl -> (
			board.tiles.(y + (decal_y * 1)).(x + (decal_x * 1)) <- other_tile ;
			board.tiles.(y + (decal_y * 2)).(x + (decal_x * 2)) <- other_tile ;
			_cancel_captures tl
		)
	in
	_cancel_captures captures ;
	board.tiles.(y).(x) <- Tile.Empty

let cancel_move board y x heur_value_change is_red captures =
	cancel_move_raw board y x is_red captures ;
	let loss = List.length captures * 2 in
	(if is_red then
		board.blue_taken <- board.blue_taken - loss
	else
		board.red_taken <- board.red_taken - loss) ;
	board.heur_value <- board.heur_value - heur_value_change

let print_dir = function
	| Horizontal -> print_string "Horizontal"
	| Vertical -> print_string "Vertical"
	| DiagUp -> print_string "DiagUp"
	| DiagDown -> print_string "DiagDown"

let rec print_dirs = function
	| [] -> print_endline ""
	| h::tl -> print_dir h ; print_string " " ; print_dirs tl

let free_threes board y x tile =
	let _check_four_plus_two_free _y _x y_decal x_decal =
		_y - y_decal >= 0 && _y - y_decal < Array.length board &&
		_y + (y_decal * 4) >= 0 && _y + (y_decal * 4) < Array.length board &&
		_x - x_decal >= 0 && _x - x_decal < Array.length board &&
		_x + (x_decal * 4) >= 0 && _x + (x_decal * 4) < Array.length board &&
		board.(_y).(_x) = tile &&
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
	let dirs = [(0, 1, Horizontal); (1, 0, Vertical); (1, 1, DiagDown); ((-1), 1, DiagUp)] in
	List.fold_left _add_to_acc [] dirs

let find_five_alignements board y x =
	let tile = board.tiles.(y).(x) in
	let rec _alignement_helper _y _x y_decal x_decal acc =
		let _y, _x = _y + y_decal, _x + x_decal in
		if _y < 0 || _y >= Array.length board.tiles || _x < 0 || _x >= Array.length board.tiles
		then acc
		else (
			if board.tiles.(_y).(_x) = tile then _alignement_helper _y _x y_decal x_decal (acc + 1)
			else acc
		)
	in
	let _alignement y_decal x_decal =
		_alignement_helper y x y_decal x_decal 0
	in
	let hori = _alignement 0 1 + _alignement 0 (-1) + 1 in
	let verti = _alignement 1 0 + _alignement (-1) 0 + 1 in
	let diagup = _alignement (-1) 1 + _alignement 1 (-1) + 1 in
	let diagdown = _alignement 1 1 + _alignement (-1) (-1) + 1 in
	let alignements = [] in
	let alignements = if hori >= 5 then Horizontal :: alignements else alignements in
	let alignements = if verti >= 5 then Vertical :: alignements else alignements in
	let alignements = if diagup >= 5 then DiagUp :: alignements else alignements in
	let alignements = if diagdown >= 5 then DiagDown :: alignements else alignements in
	alignements

let can_break_alignements_or_take_ten board y x is_red =
	let tile = if is_red then Tile.Red else Tile.Blue in
	let other_tile = if is_red then Tile.Blue else Tile.Red in
	let could_take_ten =
		if tile = Tile.Red && board.red_taken < 8 then false
		else if tile = Tile.Blue && board.blue_taken < 8 then false
		else true
	in
	let _breaking_alignements () =
		let new_alignements = find_five_alignements board y x in
		List.length new_alignements = 0
	in
	let _capturing_ten captures =
		List.length captures > 0
	in
	let _no_double_threes ori_threes capt _y _x =
		let _in_list lst elt =
			List.exists ((=) elt) lst
		in
		let new_threes = free_threes board.tiles _y _x other_tile in
		let diff = List.filter (fun elt -> not (_in_list ori_threes elt)) new_threes in
		let no_threes = List.length diff < 2 in
		no_threes || List.length capt > 0
	in
	let _ok_move _y _x =
		if not (board.tiles.(_y).(_x) = Tile.Empty) then false
		else (
			let ori_threes = free_threes board.tiles _y _x other_tile in
			let capt = place_tile_raw board.tiles _y _x (not is_red) in
			let no_threes = _no_double_threes ori_threes capt _y _x in
			if not no_threes then (cancel_move_raw board _y _x (not is_red) capt ; false)
			else (
				if could_take_ten && List.length capt > 0 then (cancel_move_raw board _y _x (not is_red) capt ; true)
				else if _breaking_alignements () then (cancel_move_raw board _y _x (not is_red) capt ; true)
				else (cancel_move_raw board _y _x (not is_red) capt ; false)
			)
		)
	in
	let board_len = Array.length board.tiles in
	let lst = Utils.list_init Utils.id_func board_len in
	let _one_ok_in_row acc _y =
		let acc_f = (fun acc _x -> let ok = _ok_move _y _x in if ok then (_y, _x) :: acc else acc) in
		List.fold_left acc_f acc lst
	in
	List.fold_left (fun acc _y -> _one_ok_in_row acc _y) [] lst

let can_place_tile board y x is_red heuristic =
	let tile = if is_red then Tile.Red else Tile.Blue in
	let _is_empty () =
		board.tiles.(y).(x) = Tile.Empty
	in
	let _no_double_threes () =
		let _in_list lst elt =
			List.exists ((=) elt) lst
		in
		let ori_threes = free_threes board.tiles y x tile in
		let capt = place_tile_raw board.tiles y x is_red in
		let new_threes = free_threes board.tiles y x tile in
		let diff = List.filter (fun elt -> not (_in_list ori_threes elt)) new_threes in
		let no_threes = List.length diff < 2 in
		let ok = no_threes || List.length capt > 0 in
		let score = if not ok then (Heuristic.void_score, (false, [])) else (
			let score = match heuristic with
				| Some heur -> (Heuristic.Score (heur board y x capt), (false, []))
				| None -> (Heuristic.void_score, (false, []))
			in
			let score = (
				if is_red && board.blue_taken >= 10 then (Heuristic.Win, (false, []))
				else if not is_red && board.red_taken >= 10 then (Heuristic.Loss, (false, []))
				else (
					let alignements = find_five_alignements board y x in
					if List.length alignements = 0 then score
					else (
						let valid_moves = can_break_alignements_or_take_ten board y x is_red in
						if List.length valid_moves > 0 then (
							match score with
							| score, _ -> (score, (true, valid_moves))
						)
						else ((if is_red then Heuristic.Win else Heuristic.Loss), (false, []))
					)
				)
			) in
			score
		) in
		cancel_move_raw board y x is_red capt ;
		ok, score
	in
	if not (_is_empty ()) then
		false, (Heuristic.void_score, (false, []))
	else
		_no_double_threes ()

let print_board ?(min=false) board =
	let print_func = if min then Tile.print_tile_min else Tile.print_tile in
	let _print_row row =
		Array.iter (fun x -> print_func x ; print_string " ") row ;
		print_endline "" ;
	in
	Array.iter (_print_row) board.tiles

let update_fatal_score is_red fatal_score score y x =
	let _fatal_matches fatal to_match =
		match fatal with
		| Some (to_match, _, _) -> true
		| _ -> false
	in
	match score with
	| (Heuristic.Score _), _ -> fatal_score
	| Heuristic.Win, _ -> (
		if is_red || not (_fatal_matches fatal_score Heuristic.Loss) then Some (Heuristic.Win, y, x)
		else fatal_score
	)
	| Heuristic.Loss, _ -> (
		if not is_red || not (_fatal_matches fatal_score Heuristic.Win) then Some (Heuristic.Loss, y, x)
		else fatal_score
	)

let heuristic_of_moves board ~is_red ~moves ~heuristic =
	let _heuristic_of_move (fatal_score, acc) (y, x) =
		let ok, score = can_place_tile board y x is_red (Some heuristic) in
		if not ok then (fatal_score, acc) else (
			let fatal_score = update_fatal_score is_red fatal_score score y x in
			(fatal_score, (y, x, score) :: acc)
		)
	in
	List.fold_left _heuristic_of_move (None, []) moves

let valid_moves_heuristic_helper board ~is_red ~heuristic =
	let rec _make_columns (fatal_score, acc) y upto = function
		| i when i = upto -> (fatal_score, acc)
		| i -> (
			let ok, score = can_place_tile board y i is_red heuristic in
			let fatal_score = update_fatal_score is_red fatal_score score y i in
			let acc = if ok then (y, i, score) :: acc else acc in
			_make_columns (fatal_score, acc) y upto (i + 1)
		)
	in
	let rec _make_rows acc upto = function
		| i when i = upto -> acc
		| i -> _make_rows (_make_columns acc i upto 0) upto (i + 1)
	in 
	_make_rows (None, []) (Array.length board.tiles) 0

let valid_moves board ~is_red ~heuristic =
	valid_moves_heuristic_helper board ~is_red:is_red ~heuristic:(Some heuristic)

(** let rec print_moves = function
	| [] -> print_endline "" ;
	| (y,x) :: tl -> Printf.printf "(%d, %d) " y x ; print_moves tl **)

