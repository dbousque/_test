

open BoardType

type captures = (int * int) list

let make_board n =
	{
		tiles = Array.init n (fun i -> Array.make n Tile.Empty) ;
		heur_value = 0 ;
		blue_taken = 0 ;
		red_taken = 0
	}

let print_board ?(min=false) board =
	let print_func = if min then Tile.print_tile_min else Tile.print_tile in
	let _print_row row =
		Array.iter (fun x -> print_func x ; print_string " ") row ;
		print_endline "" ;
	in
	Array.iter (_print_row) board.tiles

let place_tile_time_var = ref 0.0

let place_tile_raw board y x is_red =
	(*let start = Unix.gettimeofday () in *)
	let tile = if is_red then Tile.Red else Tile.Blue in
	let other_tile = if is_red then Tile.Blue else Tile.Red in
	Array.set board.(y) x tile ;
	let _make_capture y_decal x_decal acc =
		if (y + (y_decal * 3) >= 0 && y + (y_decal * 3) < Array.length board &&
			x + (x_decal * 3) >= 0 && x + (x_decal * 3) < Array.length board &&
			board.(y + (y_decal * 3)).(x + (x_decal * 3)) = tile &&
			board.(y + (y_decal * 1)).(x + (x_decal * 1)) = other_tile &&
			board.(y + (y_decal * 2)).(x + (x_decal * 2)) = other_tile) then (
				board.(y + (y_decal * 1)).(x + (x_decal * 1)) <- Tile.Empty ;
				board.(y + (y_decal * 2)).(x + (x_decal * 2)) <- Tile.Empty ;
				(y_decal, x_decal) :: acc
			)
		else
			acc
	in
	let decals_list = [(0, 1); (0, (-1)); (1, 0); ((-1), 0); (1, 1); ((-1), (-1)); ((-1), 1); (1, (-1))] in
	let res = List.fold_left (fun acc (y_decal, x_decal) -> _make_capture y_decal x_decal acc) [] decals_list in
	(*place_tile_time_var := !place_tile_time_var +. (Unix.gettimeofday () -. start) ; *)
	res

let place_tile_time () =
	!place_tile_time_var

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
	(*let _no_double_threes ori_threes capt _y _x =
		let _in_list lst elt =
			List.exists ((=) elt) lst
		in
		let new_threes = free_threes board.tiles _y _x other_tile in
		let diff = List.filter (fun elt -> not (_in_list ori_threes elt)) new_threes in
		let no_threes = List.length diff < 2 in
		no_threes || List.length capt > 0
	in *)
	let _ok_move _y _x =
		if not (board.tiles.(_y).(_x) = Tile.Empty) then false
		else (
			(*let ori_threes = free_threes board.tiles _y _x other_tile in
			let capt = place_tile_raw board.tiles _y _x (not is_red) in
			let no_threes = _no_double_threes ori_threes capt _y _x in
			if not no_threes then (cancel_move_raw board _y _x (not is_red) capt ; false)
			else (
				if could_take_ten && List.length capt > 0 then (cancel_move_raw board _y _x (not is_red) capt ; true)
				else if _breaking_alignements () then (cancel_move_raw board _y _x (not is_red) capt ; true)
				else (cancel_move_raw board _y _x (not is_red) capt ; false)
			) *)
			let threes = FreeThrees.free_threes board.tiles _y _x other_tile in
			let capt = place_tile_raw board.tiles _y _x (not is_red) in
			let no_threes = List.length threes < 2 || List.length capt > 0 in
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
	let _valid_coords () =
		y >= 0 && y < Array.length board.tiles
		&& x >= 0 && x < Array.length board.tiles
	in
	let _is_empty () =
		board.tiles.(y).(x) = Tile.Empty
	in
	let _no_double_threes () =
		let _in_list lst elt =
			List.exists ((=) elt) lst
		in
		(*let ori_threes = free_threes board.tiles y x tile in
		let capt = place_tile_raw board.tiles y x is_red in
		let new_threes = free_threes board.tiles y x tile in
		let diff = List.filter (fun elt -> not (_in_list ori_threes elt)) new_threes in
		let no_threes = List.length diff < 2 in *)
		let threes = FreeThrees.free_threes board.tiles y x tile in
		let capt = place_tile_raw board.tiles y x is_red in
		let no_threes = List.length threes < 2 in
		let ok = no_threes || List.length capt > 0 in
		let score = if not ok then (Heuristic.void_score, (false, [])) else (
			let score = match heuristic with
				| Some heur -> (Heuristic.Score (heur board y x capt), (false, []))
				| None -> (Heuristic.void_score, (false, []))
			in
			let score = (
				if is_red && board.blue_taken + (List.length capt * 2) >= 10 then
					(Heuristic.Win, (false, []))
				else if not is_red && board.red_taken + (List.length capt * 2) >= 10 then
					(Heuristic.Loss, (false, []))
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
	if not (_valid_coords ()) || not (_is_empty ()) then
		(false, (Heuristic.void_score, (false, [])))
	else
		_no_double_threes ()

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

let around_placed_tiles_time_var = ref 0.0

(*let around_placed_tiles board y x =
	let start = Unix.gettimeofday () in
	let board_len = Array.length board.tiles in
	let _is_not_empty _y _x =
		board.tiles.(_y).(_x) <> Tile.Empty
	in
	let _check_tile decal_y decal_x =
		let _y = y + decal_y in
		let _x = x + decal_x in
		if _y > 0 && _y < board_len
			&& _x > 0 && _x < board_len
			&& _is_not_empty _y _x then
			true
		else
			false
	in
	let _check_dir decal_y decal_x =
		_check_tile decal_y decal_x
		(*|| _check_tile (decal_y * 2) (decal_x * 2) *)
		|| _check_tile (- decal_y) (- decal_x)
		(*|| _check_tile (- (decal_y * 2)) (- (decal_x * 2)) *)
	in
	let res = (
		if _is_not_empty y x then true
		else if _check_dir 1 0 then true
		else if _check_dir 0 1 then true
		else if _check_dir 1 1 then true
		else if _check_dir (-1) 1 then true
		else false
	) in
	around_placed_tiles_time_var := !around_placed_tiles_time_var +. (Unix.gettimeofday () -. start) ;
	res *)

let valid_moves_time_var = ref 0.0
let can_place_tile_time_var = ref 0.0
let make_rows_time_var = ref 0.0

module IntPairs =
struct
	type t = int * int
	let compare (x0, y0) (x1, y1) =
		match Pervasives.compare x0 x1 with
		| 0 -> Pervasives.compare y0 y1
		| c -> c
end

module PairsSet = Set.Make (IntPairs)

let rec valid_moves_heuristic_helper board ~is_red ~heuristic ~only_around_placed_tiles =
	let rec _merge_scores (y, x) (fatal_score, acc) =
		(*let start_can_place = Unix.gettimeofday () in *)
		let ok, score = can_place_tile board y x is_red heuristic in
		(*can_place_tile_time_var := !can_place_tile_time_var +. (Unix.gettimeofday () -. start_can_place) ; *)
		let fatal_score = if ok then
				update_fatal_score is_red fatal_score score y x
			else
				fatal_score
		in
		let acc = if ok then (y, x, score) :: acc else acc in
		(fatal_score, acc)
	in
	let _add_if_inside y x set =
		if (y >= 0 && y < Array.length board.tiles
			&& x >= 0 && x < Array.length board.tiles) then (
			PairsSet.add (y, x) set
		)
		else
			set
	in
	let rec _make_columns_candidates set y upto = function
		| i when i = upto -> set
		| i -> (
			let set = (
				if board.tiles.(y).(i) <> Tile.Empty then (
					let set = _add_if_inside (y + 1) (i - 1) set in
					let set = _add_if_inside (y - 1) (i - 1) set in
					let set = _add_if_inside (y + 1) i set in
					let set = _add_if_inside (y - 1) i set in
					let set = _add_if_inside (y + 1) (i + 1) set in
					let set = _add_if_inside (y - 1) (i + 1) set in
					let set = _add_if_inside y (i - 1) set in
					let set = _add_if_inside y (i + 1) set in
					set
				)
				else set
			) in
			_make_columns_candidates set y upto (i + 1)
		)
	in
	let rec _make_rows_candidates set upto = function
		| i when i = upto -> set
		| i -> _make_rows_candidates (_make_columns_candidates set i upto 0) upto (i + 1)
	in
	(*let start = Unix.gettimeofday () in *)
	let moves = _make_rows_candidates PairsSet.empty (Array.length board.tiles) 0 in
	(*make_rows_time_var := !make_rows_time_var +. (Unix.gettimeofday () -. start) ; *)
	let fatal_score, moves = PairsSet.fold _merge_scores moves (None, []) in
	(*let fatal_score, moves = _merge_scores (None, []) moves in *)
	if List.length moves = 0 && only_around_placed_tiles then (
		(*valid_moves_time_var := !valid_moves_time_var +. (Unix.gettimeofday () -. start) ; *)
		valid_moves_heuristic_helper board ~is_red ~heuristic ~only_around_placed_tiles:false
	)
	else (
		(*valid_moves_time_var := !valid_moves_time_var +. (Unix.gettimeofday () -. start) ; *)
		fatal_score, moves
	)

let valid_moves_time () =
	!valid_moves_time_var

let can_place_tile_time () =
	!can_place_tile_time_var

let around_placed_tiles_time () =
	!around_placed_tiles_time_var

let make_rows_time () =
	!make_rows_time_var

let valid_moves board ~is_red ~heuristic =
	valid_moves_heuristic_helper board ~is_red:is_red ~heuristic:(Some heuristic) ~only_around_placed_tiles:true

(** let rec print_moves = function
	| [] -> print_endline "" ;
	| (y,x) :: tl -> Printf.printf "(%d, %d) " y x ; print_moves tl **)

