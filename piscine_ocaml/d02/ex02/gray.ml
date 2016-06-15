

let reverse_list elts =
	let rec rev_list elts acc =
		match elts with
			| [] -> acc
			| x::xs -> rev_list xs (x::acc)
	in
	rev_list elts []

let concat lis1 lis2 =
	let rec conc lis1 lis2 =
		match lis2 with
			| [] -> reverse_list lis1
			| x::xs -> x::(conc lis1 xs)
	in
	reverse_list (conc lis1 (reverse_list lis2))

let rec prefix_char lis car =
	match lis with
		| [] -> []
		| x::xs -> (car::x)::(prefix_char xs car)

let rec gray = function
	| x when x <= 0 -> []
	| 1 -> [['0'];['1']]
	| n -> concat (prefix_char (gray (n - 1)) '0') (prefix_char (reverse_list (gray (n - 1))) '1')





let rec print_chars = function
	| [] -> print_string "" ;
	| c::cs -> print_char c ; print_chars cs

let print_gray n =
	let res = gray n in
	let rec print_gr lis ind =
		match lis with
			| [] -> print_string ""
			| x::xs -> if ind <> 0 then print_char ' ' ; print_chars x ; print_gr xs (ind + 1)
	in
	print_gr res 0

let print_testing n =
	print_string "testing with " ;
	print_int  n ;
	print_string " : " ;
	print_gray n ;
	print_char '\n'

let () =
	print_testing 0 ;
	print_testing 1 ;
	print_testing 2 ;
	print_testing 3 
