

let rec best_move board ~for_red ~heuristic ~depth =
	let moves_score = match depth with
		| 0 -> Board.valid_moves board ~is_red:for_red ~heuristic:heuristic
		| _ -> (
			let moves = Board.valid_moves board ~is_red:for_red ~heuristic:heuristic in
			let get_move_score (y, x, heur_score) =
				let captures = Board.place_tile board y x heur_score for_red in
				let _, _, score = best_move board
						~for_red:(not for_red) ~heuristic:heuristic ~depth:(depth - 1)
				in
				Board.cancel_move board y x heur_score for_red captures ;
				y, x, score
			in
			List.map get_move_score moves
		)
	in
	let _keep_best_score acc (y, x, score) =
		match acc with
		| None -> Some (y, x, score)
		| Some (y_acc, x_acc, score_acc) -> (
			if Heuristic.better_score score_acc score = score_acc then
				acc
			else
				Some (y, x, score)
		)
	in
	List.fold_left _keep_best_score None moves_score