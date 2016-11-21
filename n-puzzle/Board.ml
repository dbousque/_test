

type t = {
	tiles: int list list ;
	empty_cell: int * int ;
	size: int
}

let index_of lst elt =
	let rec _index_of i = function
		| [] -> (-1)
		| h::tl -> if h = elt then i else _index_of (i + 1) tl
	in
	_index_of 0 lst

let third (_, _, elt) = elt

let index_of_list lst elt =
	let _tmp lst list_ind =
		let ind = index_of lst elt in
		if ind <> (-1) then (list_ind, ind, 0) else ((-1), (-1), list_ind + 1)
	in
	let acc_func (x,y,i) elt = if x <> (-1) then (x,y,i) else _tmp elt i in
	let res = List.fold_left acc_func ((-1), (-1), 0) lst in
	match res with
	| (x, y, _) -> (x, y)

let shuffle_list lst =
	let clone = List.map (fun x -> (x, Random.bits ())) lst in
	let clone_sorted = List.sort (fun (_,rand1) (_,rand2) -> rand1 - rand2) clone in
	List.map fst clone_sorted

let shuffle_square_list_list lst =
	let rec _split_list acc lst n = function
		| 0 -> acc
		| i -> let new_acc = 
			       if i mod n = 0 then (([(List.hd lst)])::acc) else (((List.hd lst)::(List.hd acc))::(List.tl acc)) in
			       _split_list new_acc (List.tl lst) n (i - 1)
	in
	let size = List.length lst in
	let flat = List.flatten lst in
	let shuffled = shuffle_list flat in
	_split_list [[]] shuffled size (size * size)

let make_list func n =
	let rec _make_list func acc = function
		| i when i < 0 -> acc
		| i -> _make_list func ((func i)::acc) (i - 1)
	in
	_make_list func [] (n - 1)

(* build a list list, shuffle it, and replace the highest number by the empty cell *)
let rand_board size =
	Random.self_init () ;
	let tiles = make_list (fun row -> make_list (fun column -> row * size + column) size) size in
	let tiles = shuffle_square_list_list tiles in
	let empty = index_of_list tiles 0 in
	{
		tiles = tiles ;
		empty_cell = empty ;
		size = size
	}

(*1  2  3  4
12 13 14 5
11 16 15 6
10 9  8  7

4 4 4 3 3 2 2

1  2  3  4  5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9

5 5 5 4 4 3 3 2 2
5 4 4 3 3 2 2 1 1

1  2  3  4  5  6
20 21 22 23 24 7
19 32 33 34 25 8
18 31 36 35 26 9
17 30 29 28 27 10
16 15 14 13 12 11

6 6 6 5 5 4 4 3 3 2 2

6 5 5 4 4 3 3 2 2 1 1

5 + 4 + 3
sig 5
5!

n * (n + 1) / 2

horizon / vertical = mod 2
decal x = / 4*)

let make_move board dx dy =
	let y = fst board.empty_cell in
	let x = snd board.empty_cell in
	let arr = Array.of_list (List.map Array.of_list board.tiles) in
	let tmp = arr.(y).(x) in
	Array.set arr.(y) x (arr.(y + dy).(x + dx)) ;
	Array.set arr.(y + dy) (x + dx) tmp ;
	{
		tiles = Array.to_list (Array.map Array.to_list arr) ;
		empty_cell = (y + dy, x + dx) ;
		size = board.size
	}

let make_end_positions board =
	let end_positions = Array.make (board.size * board.size) (0,0) in
	let _make_step x y direction =
		match direction with
			| d when d mod 4 = 0 -> (x + 1, y)
			| d when d mod 4 = 1 -> (x, y + 1)
			| d when d mod 4 = 2 -> (x - 1, y)
			| _ -> (x, y - 1)
	in
	let rec _fill start_val x y direction n =
		Array.set end_positions start_val (x, y) ;
		match n with
		| 1 -> _make_step x y (direction + 1)
		| _ ->  let new_x, new_y = _make_step x y direction in
				_fill (start_val + 1) new_x new_y direction (n - 1)
	in
	let rec _fill_until_full start_val x y direction n =
		let x, y = _fill start_val x y direction n in
		let start_val = start_val + n in
		let direction = direction + 1 in
		match n with
		| 1 -> _fill 0 x y direction 1
		| _ ->  let x, y = _fill start_val x y direction n in
				let start_val = start_val + n in
				let direction = direction + 1 in
				_fill_until_full start_val x y direction (n - 1)
	in
	let x, y = _fill 1 0 0 0 board.size in
	ignore (_fill_until_full (board.size + 1) x y 1 (board.size - 1)) ;
	end_positions

let manhattan_distance board end_positions =
	let _distance value x y =
		abs ((fst end_positions.(value)) - x) + abs ((snd end_positions.(value)) - y)
	in
	let _distance_row y row =
		let total, i = List.fold_left (fun acc value -> (fst acc + _distance value (snd acc) y, snd acc + 1)) (0, 0) row in
		total
	in
	let total, i = List.fold_left (fun acc row -> (fst acc + _distance_row (snd acc) row, snd acc + 1)) (0, 0) board.tiles in
	total

let misplaced board end_positions =
	let rec _misplaced_row y x = function
		| [] -> 0
		| tile::rest -> let exp_x, exp_y = end_positions.(tile) in
						let to_add = if exp_y <> y || exp_x <> x then 1 else 0 in
						to_add + _misplaced_row y (x + 1) rest
	in
	let rec _misplaced_board y = function
		| [] -> 0
		| row::rest -> (_misplaced_row y 0 row) + (_misplaced_board (y + 1) rest)
	in
	_misplaced_board 0 board.tiles

let print_raw_board board =
	let max_nb = (board.size * board.size - 1) in
	let nb_max_width = String.length (string_of_int max_nb) in
	let _print_row row =
		List.iter (Printf.printf "%*d " (nb_max_width + 1)) row ;
		print_endline ""
	in
	List.iter _print_row board.tiles

let print_board board =
	print_endline ("Board of size " ^ (string_of_int board.size) ^ " :") ;
	print_raw_board board ;
	Printf.printf "Empty cell : (%d, %d)\n" (fst board.empty_cell) (snd board.empty_cell)