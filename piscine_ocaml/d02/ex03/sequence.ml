

let reverse_list elts =
	let rec rev_list elts acc =
		match elts with
			| [] -> acc
			| x::xs -> rev_list xs (x::acc)
	in
	rev_list elts []

let rec ints_to_string = function
	| [] -> ""
	| x::xs -> (string_of_int x) ^ (ints_to_string xs)

let count_ns prev =
	let rec count prev last n acc =
		match prev with
			| [] 	->	if n <> 0 then last::n::acc
						else acc
			| x::xs ->	if n = 0 || x = last
						then count xs x (n + 1) acc
						else count xs x 1 (last::n::acc)
	in
	reverse_list (count prev 0 0 [])

let rec seq = function
	| n when n < 0 -> []
	| 1 -> [1]
	| n ->
		let prev = seq (n - 1) in
		count_ns prev

let sequence n =
	ints_to_string (seq n)

let print_testing n =
	print_string "testing with " ;
	print_int n ;
	print_string " : " ;
	print_endline (sequence n)

let () =
	print_testing (-1) ;
	print_testing 0 ;
	print_testing 1 ;
	print_testing 2 ;
	print_testing 3 ;
	print_testing 4 ;
	print_testing 5 ;
	print_testing 6 ;
	print_testing 7 ;
