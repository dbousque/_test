

let reverse_list elts =
	let rec rev_list elts acc =
		match elts with
			| [] -> acc
			| x::xs -> rev_list xs (x::acc)
	in
	rev_list elts []

let incr_last res =
	match res with
		| (nb, elt)::xs -> (nb + 1, elt)::xs
		| _ -> res

let add_to_last x res =
	match res with
		| (nb, elt)::xs when elt = x -> true
		| _ -> false

let encode lis =
	let rec enco elts res =
		match elts with
			| [] -> res
			| x::xs when add_to_last x res -> enco xs (incr_last res)
			| x::xs -> enco xs ((1, x)::res)
	in
	reverse_list (enco lis [])

let rec my_print_list = function
	| [] -> print_char '\n'
	| (nb, elt)::xs -> print_int nb ; print_char elt ; my_print_list xs

let print_char_list chars =
	let rec print_chars chars n =
		match chars with
			| [] -> print_string ""
			| c::cs when n <> 0 -> print_string ", '" ; print_char c ; print_char '\'' ; print_chars cs (n + 1)
			| c::cs -> print_char '\'' ; print_char c ; print_char '\'' ; print_chars cs (n + 1)
	in
	print_char '[' ;
	print_chars chars 0 ;
	print_char ']'

let print_testing elts =
	print_string "testing with " ;
	print_char_list elts ;
	print_string " : " ;
	my_print_list (encode elts)

let () =
	print_testing ['a';'a';'a';'a';'b';'b';'b'] ;
	print_testing [] ;
	print_testing ['a'] ;
	print_testing ['a';'b';'c';'d';'a';'b'] ;
	print_testing ['a';'a';'a';'a';'a']
