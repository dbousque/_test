

let rec best_move_helper board ~for_red ~valid_next ~alpha ~beta ~heuristic ~depth =
	let _keep_best_score acc (y, x, score) =
		let better_score = if for_red then
				Heuristic.better_score_red
			else
				Heuristic.better_score_blue
		in
		match acc with
		| None -> Some (y, x, score)
		| Some (y_acc, x_acc, score_acc) -> (
			let sc, _ = score in
			let sc_acc, _ = score_acc in
			if better_score sc_acc sc = sc_acc then
				acc
			else
				Some (y, x, score)
		)
	in
	let _get_move_score alpha beta (y, x, (heur_score, (forced_next_move, valid_next))) =
		match heur_score with
		| Heuristic.Score sc -> (
			let captures = Board.place_tile board y x sc for_red in
			let best_move_func = best_move_helper board ~for_red:(not for_red) in
			let best_move_func = if forced_next_move then
					best_move_func ~valid_next:(Some valid_next)
				else
					best_move_func ~valid_next:(None)
			in
			let best_move_func = best_move_func ~alpha:alpha ~beta:beta in
			let best = best_move_func ~heuristic:heuristic ~depth:(depth - 1) in
			Board.cancel_move board y x sc for_red captures ;
			match best with
			| None -> (y, x, (Heuristic.Score 0, (false, [])))
			| Some (_, _, score) -> (
				let score = match score with
					| (Heuristic.Score new_sc, _) -> (Heuristic.Score (sc + new_sc), (forced_next_move, valid_next))
					| (s, _) -> (s, (forced_next_move, valid_next))
				in
				(y, x, score)
			)
		)
		| Heuristic.Win -> (y, x, (Heuristic.Win, (false, [])))
		| Heuristic.Loss -> (y, x, (Heuristic.Loss, (false, [])))
	in
	let rec _alpha_beta_get_moves moves alpha beta acc =
		match moves with
		| [] -> acc
		| move :: rest -> (
			let (y, x, (score, f)) = _get_move_score alpha beta move in
			let alpha = if not for_red then alpha else Heuristic.better_score_red alpha score in
			let beta = if for_red then beta else Heuristic.better_score_blue beta score in
			let acc = (y, x, (score, f)) :: acc in
			if Heuristic.better_score_red alpha beta = alpha then acc
			else _alpha_beta_get_moves rest alpha beta acc
		)
	in
	let fatal_move, moves = match valid_next with
		| None -> Board.valid_moves board ~is_red:for_red ~heuristic:heuristic
		| Some valid_next -> Board.heuristic_of_moves board ~is_red:for_red ~moves:valid_next ~heuristic:heuristic
	in
	let moves = 
		match for_red, fatal_move with
		| true, Some (Heuristic.Win, y, x) -> [(y, x, (Heuristic.Win, (false, [])))]
		| false, Some (Heuristic.Loss, y, x) -> [(y, x, (Heuristic.Loss, (false, [])))]
		| _ -> (
			if depth = 0 then moves
			else (
				let _better_score_sort (_, _, (heur_score1, _)) (_, _, (heur_score2, _)) =
					if heur_score1 = heur_score2 then 0
					else if for_red && Heuristic.better_score_red heur_score1 heur_score2 = heur_score1 then (-1)
					else if not for_red && Heuristic.better_score_blue heur_score1 heur_score2 = heur_score1 then (-1)
					else 1
				in
				let moves = List.sort _better_score_sort moves in
				_alpha_beta_get_moves moves alpha beta []
			)
		)
	in
	List.fold_left _keep_best_score None moves

let best_move board ~for_red ~heuristic ~depth =
	best_move_helper board
		~for_red:for_red
		~valid_next:None
		~alpha:Heuristic.Loss
		~beta:Heuristic.Win
		~heuristic:heuristic
		~depth:depth