

type score =
	| Win
	| Loss
	| Score of int

let better_score score1 score2 =
	match score1 with
	| Win -> Win
	| Loss -> score2
	| Score i1 -> (
		match score2 with
		| Win -> Win
		| Loss -> score1
		| Score i2 -> Score (max i1 i2)
	)

let void_score = Loss

let simple_heuristic board y x captures =
	let tile = board.(y).(x) in
	let rec _count_on_line _y _x y_decal x_decal miss acc =
		let _y = _y + y_decal in
		let _x = _x + x_decal in
		if board.(_y).(_x) = Tile.Empty then (
			if miss >= 1 then acc
			else _count_on_line _y _x y_decal x_decal (miss + 1) acc
		)
		else (
			if board.(_y).(_x) = tile then (
				_count_on_line _y _x y_decal x_decal miss (acc + 1)
			)
			else acc
		)
	in
	let dirs = [
		(0, 1); (1, 0); (1, 1); ((-1), 1);
		(0, (-1)); ((-1), 0); ((-1), (-1)); (1, (-1))
	] in
	let _acc_helper acc (y_decal, x_decal) =
		acc + _count_on_line y x y_decal x_decal 0 0
	in
	let score = List.fold_left _acc_helper 0 dirs in
	let score = score + (List.length captures * 2) in
	if tile = Tile.Red then score else (- score)