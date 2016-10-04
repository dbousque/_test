

let is_lower c =
	c >= 'a' && c <= 'z'

let is_upper c =
	c >= 'A' && c <= 'Z'

let is_letter c =
	is_lower c || is_upper c

let rec add_n_neg c n =
	let c_int = int_of_char c in
	let a_min = int_of_char 'a' in
	let a_maj = int_of_char 'A' in
	if (is_lower c && c_int - n >= a_min) || (is_upper c && c_int - n >= a_maj)
	then char_of_int (c_int - n)
	else
		if is_lower c
		then add_n_neg 'z' ((n - (c_int - a_min)) - 1)
		else add_n_neg 'Z' ((n - (c_int - a_maj)) - 1)

let rec add_n_pos c n =
	let c_int = int_of_char c in
	let z_min = int_of_char 'z' in
	let z_maj = int_of_char 'Z' in
	if (is_lower c && c_int + n <= z_min) || (is_upper c && c_int + n <= z_maj)
	then char_of_int (c_int + n)
	else
		if is_lower c
		then add_n_pos 'a' ((n - (z_min - c_int)) - 1)
		else add_n_pos 'A' ((n - (z_maj - c_int)) - 1)

let ft_rot_n n str =
	let rotate c =
		if is_letter c
		then if n >= 0 then add_n_pos c n
					   else add_n_neg c (-n)
		else c
	in
	String.map rotate str



let unrot42 str =
	ft_rot_n (-42) str

let uncaesar n str =
	ft_rot_n (-n) str

let rec ft_uncrypt str funcs =
	match funcs with
		| [] -> str
		| func::funcs2 -> ft_uncrypt (func str) funcs2


let print_testing_rot str =
	print_string "testing unrot42 with \"" ;
	print_string str ;
	print_string "\" : " ;
	print_endline (unrot42 str)

let print_testing_caesar n str =
	print_string "testing uncaesar with " ;
	print_int n ;
	print_string ", \"" ;
	print_string str ;
	print_string "\" : " ;
	print_endline (uncaesar n str)

let uncrypt_tests () =
	let str1 = "string" in
	let str2 = "string" in
	let funcs1 = [uncaesar 0; uncaesar 1] in
	let funcs2 = [uncaesar 5; uncaesar 2] in
	print_string "testing crypt with \"" ;
	print_string str1 ;
	print_string "\" and functions [uncaesar 0; uncaesar 1] : " ;
	print_endline (ft_uncrypt str1 funcs1) ;
	print_string "testing crypt with \"" ;
	print_string str2 ;
	print_string "\" and functions [uncaesar 5; uncaesar 2] : " ;
	print_endline (ft_uncrypt str2 funcs2)
