

let rec best_move board ~for_red ~heuristic ~depth =
	let moves_score = match depth with
		| 0 -> Board.valid_moves_heuristic board ~is_red:for_red ~heuristic:heuristic
		| _ -> (
				let moves = Board.valid_moves board ~is_red:for_red in
				let get_move_score (y, x, _) =
					let captures = Board.place_tile board y x for_red in
					let _, _, score = best_move board
							~for_red:(not for_red) ~heuristic:heuristic ~depth:(depth - 1)
					in
					Board.cancel_move board y x for_red captures ;
					y, x, score
				in
				List.map get_move_score moves
			)
	in
	let _keep_best_score (y_acc, x_acc, score_acc) (y, x, score) =
		if Heuristic.better_score score_acc score = score_acc then
			(y_acc, x_acc, score_acc)
		else
			(y, x, score)
	in
	List.fold_left _keep_best_score Heuristic.better_score Heuristic.Lost moves_score