

let test_match options1 options2 =
	let game = Main.make_new_game 19 options1 options2 in
	let rec _play_game game time_red time_blue =
		let red_turn = Main.(game.red_turn) in
		let (_, game), time_taken = Main.make_ai_move game in
		let time_red = if red_turn then time_red + time_taken else time_red in
		let time_blue = if not red_turn then time_blue + time_taken else time_blue in
		if Main.(game.game_state) <> "playing" then (game, time_red, time_blue)
		else _play_game game time_red time_blue
	in
	let game, time_red, time_blue = _play_game game 0 0 in
	let nb_moves = Main.(game.nb_moves) in
	let nb_blue_moves = nb_moves / 2 in
	let nb_red_moves = nb_moves - nb_blue_moves in
	let time_red = time_red / nb_red_moves in
	let time_blue = time_blue / nb_blue_moves in
	Main.(game.game_state), nb_moves, time_red, time_blue

let test_options ~nb_games options1 options2 =
	let _test_options options1 options2 =
		let rec __test_options ori_nb_games (wins, losses, draws) (nb_moves, times_red, times_blue) nb_games =
			match nb_games with
			| 0 -> (
				let nb_moves = nb_moves / ori_nb_games in
				let av_time_red = (List.fold_left (+) 0 times_red) / List.length times_red in
				let av_time_blue = (List.fold_left (+) 0 times_blue) / List.length times_blue in
				let sort_int = fun a b -> a - b in
				let times_red = List.sort sort_int times_red in
				let times_blue = List.sort sort_int times_blue in
				let top_time_red = List.nth times_red ((List.length times_red) * 4 / 5) in
				let top_time_blue = List.nth times_blue ((List.length times_blue) * 4 / 5) in
				(wins, losses, draws), (nb_moves, av_time_red, av_time_blue, top_time_red, top_time_blue)
			)
			| _ -> (
				let result, _nb_moves, _time_red, _time_blue = test_match options1 options2 in
				let wins, losses, draws = (
					match result with
					| "win" -> wins + 1, losses, draws
					| "loss" -> wins, losses + 1, draws
					| "draw" -> wins, losses, draws + 1
					| _ -> raise (Failure "should not happen")
				) in
				let nb_moves = nb_moves + _nb_moves in
				let times_red = _time_red :: times_red in
				let times_blue = _time_blue :: times_blue in
				__test_options ori_nb_games (wins, losses, draws) (nb_moves, times_red, times_blue) (nb_games - 1)
			)
		in
		__test_options nb_games (0, 0, 0) (0, [], []) nb_games
	in
	let (wins, losses, draws), (nb_moves, av_time_red, av_time_blue, top_time_red, top_time_blue) = _test_options options1 options2 in
	let (_wins, _losses, _draws), (_nb_moves, _av_time_red, _av_time_blue, _top_time_red, _top_time_blue) = _test_options options2 options1 in
	let (wins, losses, draws) = (wins + _losses, losses + _wins, draws + _draws) in
	let nb_moves = (nb_moves + _nb_moves) / 2 in
	let av_time_red = (av_time_red + _av_time_blue) / 2 in
	let av_time_blue = (av_time_blue + _av_time_red) / 2 in
	let top_time_red = (top_time_red + _top_time_blue) / 2 in
	let top_time_blue = (top_time_blue + _top_time_red) / 2 in
	(wins, losses, draws), (nb_moves, av_time_red, av_time_blue, top_time_red, top_time_blue)

let make_test ~nb_games options1 options2 =
	let (wins, losses, draws), (nb_moves, av_time_red, av_time_blue, top_time_red, top_time_blue) = test_options ~nb_games options1 options2 in
	let wins = (float_of_int wins) /. (float_of_int (nb_games * 2)) *. 100.0 in
	let losses = (float_of_int losses) /. (float_of_int (nb_games * 2)) *. 100.0 in
	let draws = (float_of_int draws) /. (float_of_int (nb_games * 2)) *. 100.0 in
	Printf.printf "1 won : %.2f%%\n2 won : %.2f%%\ndraws : %.2f%%\nnb_moves : %d\n1 av. time : %d ms\n2 av. time : %d ms\n1 4/5th time : %d ms\n2 4/5th time : %d ms \n" wins losses draws nb_moves av_time_red av_time_blue top_time_red top_time_blue

let () =
	let options1 = (Heuristic.standard_heuristic, 4, 30) in
	let options2 = (Heuristic.simple_heuristic, 4, 30) in
	let nb_games = 100 in
	make_test ~nb_games options1 options2 ;
	let valid_moves_time = Board.valid_moves_time () in
	let can_place_tile_time = Board.can_place_tile_time () in
	let around_placed_tiles_time = Board.around_placed_tiles_time () in
	let make_rows_time = Board.make_rows_time () in
	let simple_heuristic_time = Heuristic.simple_heuristic_time () in
	let place_tile_time = Board.place_tile_time () in
	let free_threes_time = FreeThrees.free_threes_time () in
	Printf.printf "valid_moves         : %.2f s\ncan_place_tile      : %.2f s\naround_placed_tiles : %.2f s\nmake_rows           : %.2f s\nsimple_heuristic    : %.2f s\nplace_tile          : %.2f s\nfree_threes         : %.2f s\n" valid_moves_time can_place_tile_time around_placed_tiles_time make_rows_time simple_heuristic_time place_tile_time free_threes_time

(*let () =
	Board.test_free_threes () *)