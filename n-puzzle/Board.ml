

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
		| i when i <= 0 -> acc
		| i -> _make_list func ((func i)::acc) (i - 1)
	in
	_make_list func [] n

(* build a list list, shuffle it, and replace the highest number by the empty cell *)
let rand_board size =
	Random.self_init () ;
	let tiles = make_list (fun row -> make_list (fun column -> if row = size - 1 && column = size - 1 then 0 else (row - 1) * size + column) size) size in
	let tiles = shuffle_square_list_list tiles in
	let empty = index_of_list tiles 0 in
	{
		tiles = tiles ;
		empty_cell = empty ;
		size = size
	}

let manhattan_distance board =
	let _distance val x y =
		let res_x = 

let print_board board =
	let max_nb = (board.size * board.size - 1) in
	let nb_max_width = String.length (string_of_int max_nb) in
	let _print_row row =
		List.iter (Printf.printf "%*d " (nb_max_width + 1)) row ;
		print_endline ""
	in
	print_endline ("Board of size " ^ (string_of_int board.size) ^ " :") ;
	List.iter _print_row board.tiles ;
	Printf.printf "Empty cell : (%d, %d)\n" (fst board.empty_cell) (snd board.empty_cell)