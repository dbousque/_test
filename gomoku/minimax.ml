

let rec best_move board ~for_red ~valid_next ~heuristic ~depth =
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
	let _get_move_score (y, x, (heur_score, (forced_next_move, valid_next))) =
		match heur_score with
		| Heuristic.Score sc -> (
			let captures = Board.place_tile board y x sc for_red in
			let best_move_func = best_move board ~for_red:(not for_red) in
			let best_move_func = if forced_next_move then
					best_move_func ~valid_next:(Some valid_next)
				else
					best_move_func ~valid_next:(None)
			in
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
	let rec _alpha_beta_get_moves moves min max acc =
		match moves with
		| [] -> acc
		| move :: rest -> (
			
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
		| _ -> if depth = 0 then moves else _alpha_beta_get_moves moves Heuristic.Loss Heuristic.Win []
	in
	List.fold_left _keep_best_score None moves