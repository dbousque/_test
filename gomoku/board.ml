

type t = {
	tiles:					Tile.t array array ;
	mutable blue_taken:		int ;
	mutable red_taken:		int
}

type captures = (int * int) list

type dir = Horizontal | Vertical | DiagUp | DiagDown

let make_board n =
	{
		tiles = Array.init n (fun i -> Array.make n Tile.Empty) ;
		blue_taken = 0 ;
		red_taken = 0
	}

let place_tile_ret_capt board y x is_red =
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

let place_tile board y x is_red =
	let capt = place_tile_ret_capt board.tiles y x is_red in
	let gain = List.length capt * 2 in
	if is_red then
		board.blue_taken <- board.blue_taken + gain
	else
		board.red_taken <- board.red_taken + gain
	capt

let cancel_move board y x is_red captures =
	let other_tile = if is_red then Tile.Blue else Tile.Red in
	let rec _cancel_captures = function
		| [] -> ()
		| (decal_y, decal_x) :: tl -> (
				board.tiles.(y + (decal_y * 1)).(x + (decal_x * 1)) <- other_tile ;
				board.tiles.(y + (decal_y * 2)).(x + (decal_x * 2)) <- other_tile ;
				_cancel_captures tl
			)
	in
	_cancel_captures board y x is_red captures ;
	board.(y).(x) <- Tile.Empty

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

let can_place_tile board y x is_red heuristic =
	let tile = if is_red then Tile.Red else Tile.Blue in
	let other_tile = if is_red then Tile.Blue else Tile.Red in
	let _is_empty () =
		board.tiles.(y).(x) = Tile.Empty
	in
	let _no_double_threes () =
		let _in_list lst elt =
			List.exists ((=) elt) lst
		in
		let ori_threes = free_threes board.tiles y x tile in
		let capt = place_tile_ret_capt board.tiles y x is_red in
		let new_threes = free_threes board.tiles y x tile in
		let diff = List.filter (fun elt -> not (_in_list ori_threes elt)) new_threes in
		let no_threes = List.length diff < 2 in
		let score = match heuristic with
			| Some heur -> heur board
			| None -> Heuristic.void_score
		in
		cancel_move board y x is_red capt ;
		no_threes, score
	in
	if not (_is_empty ()) then
		false, Heuristic.void_score
	else
		_no_double_threes ()

let print_board ?(min=false) board =
	let print_func = if min then Tile.print_tile_min else Tile.print_tile in
	let _print_row row =
		Array.iter (fun x -> print_func x ; print_string " ") row ;
		print_endline "" ;
	in
	Array.iter (_print_row) board.tiles

let valid_moves_heuristic_helper board ~is_red ~heuristic =
	let rec _make_columns acc y upto = function
		| i when i = upto -> acc
		| i -> (
				let ok, score = can_place_tile boardy i is_red heuristic in
				let acc = if ok then (y, i, score) :: acc else acc in
				_make_columns acc y upto (i + 1)
			)
	in
	let rec _make_rows acc upto = function
		| i when i = upto -> acc
		| i -> _make_rows (_make_columns acc i upto 0) upto (i + 1)
	in 
	_make_rows [] 19 0

let valid_moves_heuristic board ~is_red ~heuristic =
	valid_moves_heuristic board ~is_red:is_red ~heuristic:(Some heuristic)

let valid_moves board ~is_red =
	let moves = valid_moves_heuristic_helper board ~is_red:is_red ~heuristic:None in
	List.map (fun (y, x, score) -> (y, x)) moves

(** let rec print_moves = function
	| [] -> print_endline "" ;
	| (y,x) :: tl -> Printf.printf "(%d, %d) " y x ; print_moves tl **)

