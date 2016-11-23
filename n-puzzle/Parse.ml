

type parse_result = {
	heuristic: string ;
	greedy: bool ;
	in_place: bool ;
	n: int ;
	files: string list
}

let parse_options () =
	let usage = "-h [mahattan|misplaced|crow] -greedy [true|false] -fancy_out [true|false]" in
	let heuristic = ref "manhattan" in
	let greedy = ref true in
	let in_place = ref false in
	let n = ref 3 in
	let files = ref [] in
	let valid_heur heur =
		if heur = "manhattan" || heur = "misplaced" || heur = "crow" then
			heuristic := heur
		else
			raise (Arg.Bad "Unknown heuristic")
	in
	let options = [
		("-h", Arg.String valid_heur, "Heuristic to use to guide the search") ;
		("-greedy", Arg.Bool (fun x -> greedy := x), "Greedy or uniform-cost search") ;
		("-fancy_out", Arg.Bool (fun x -> in_place := x), "Step by step visualization of the moves made") ;
		("-n", Arg.Int (fun x -> if x < 2 then raise (Arg.Bad "n too small") else n := x), "Width of the board")
	] in
	let anon_args file =
		files := file::(!files)
	in
	Arg.parse options anon_args usage ;
	{
		heuristic = !heuristic ;
		greedy = !greedy ;
		in_place = !in_place ;
		n = !n ;
		files = !files
	}

let get_line chan =
	try input_line chan with End_of_file -> raise (Failure "Unexpected end of file")

let parse_int str line_nb =
	let str = String.trim str in
	( if String.length str = 0 || (String.length str != 1 && String.get str 0 == '0') then
		raise (Failure ("Bad int format at line " ^ (string_of_int line_nb))) ) ;
	let only_digits = ref true in
	String.iter (fun c -> if Char.code c < Char.code '0' || Char.code c > Char.code '9' then only_digits := false) str ;
	( if !only_digits = false then raise (Failure ("Not only digits in expected int at line " ^ (string_of_int line_nb))) ) ;
	int_of_string str

let is_digit c =
	Char.code c >= Char.code '0' && Char.code c <= Char.code '9'

let get_start_int line =
	let ind = ref 0 in
	let len = String.length line in
	while !ind < len && is_digit line.[!ind] do
		ind := !ind + 1 ;
	done ;
	(String.sub line 0 !ind, String.sub line !ind (len - !ind))

let assert_valid_tiles tiles size =
	let width_ok = List.fold_left (fun acc row -> acc && List.length row = size) true tiles in
	( if width_ok = false then raise (Failure ("A row doesn't have " ^ (string_of_int size) ^ " tiles.")) ) ;
	( if List.length tiles <> size then raise (Failure ("Not " ^ (string_of_int size) ^ " rows.")) ) ;
	let ht = Hashtbl.create size in
	let add_to_ht value =
		Hashtbl.add ht value 1
	in
	List.iter (fun row -> List.iter add_to_ht row) tiles ;
	for i = 0 to (size * size - 1) do
		if Hashtbl.mem ht i = false then raise (Failure ("Missing value " ^ string_of_int i))
	done

let ignore_comment_lines chan =
	let rec _ignore_comment_lines i =
		let line = get_line chan in
		let line = String.trim line in
		if String.length line > 0 && line.[0] = '#' then _ignore_comment_lines (i + 1) else (line, i)
	in
	_ignore_comment_lines 1

let get_tiles_from_file chan =
	let line, nb_read = ignore_comment_lines chan in
	let size = parse_int line nb_read in
	let rec _read_line line_nb line =
		let line = String.trim line in
		if String.length line = 0 || line.[0] = '#' then
			[]
		else (
			let int_str,rest = get_start_int line in
			let value = parse_int int_str line_nb in
			value::(_read_line line_nb rest)
		)
	in
	let rec _read_lines line_nb lines =
		match List.length lines with
		| l when l = size -> lines
		| _ ->  let in_line, nb_read = ignore_comment_lines chan in
				_read_lines (line_nb + nb_read) ((_read_line (line_nb + nb_read) in_line)::lines)
	in
	let lines = _read_lines nb_read [] in
	assert_valid_tiles lines size ;
	(List.rev lines)

let parse_file file =
	let chan = try open_in file with | _ -> raise (Failure ("No such file : " ^ file)) in
	let tiles = get_tiles_from_file chan in
	Board.board_from_tiles (List.length tiles) tiles