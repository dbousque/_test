

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
					   else add_n_neg c n
		else c
	in
	String.map rotate str



let rot42 str =
	ft_rot_n 42 str

let caesar n str =
	ft_rot_n n str

let xor key str =
	let xor_key c =
		char_of_int ((int_of_char c) lxor key)
	in
	if key < 0 then str
	else String.map xor_key str

let rec ft_crypt str funcs =
	match funcs with
		| [] -> str
		| func::funcs2 -> ft_crypt (func str) funcs2



let print_testing_rot str =
	print_string "testing rot42 with \"" ;
	print_string str ;
	print_string "\" : " ;
	print_endline (rot42 str)

let print_testing_caesar n str =
	print_string "testing caesar with " ;
	print_int n ;
	print_string ", \"" ;
	print_string str ;
	print_string "\" : " ;
	print_endline (caesar n str)

let print_testing_xor str key =
	print_string "testing xor with key=" ;
	print_int key ;
	print_string " str=\"" ;
	print_string str ;
	print_string "\" : " ;
	print_endline (xor key str)

let crypt_tests () =
	let str1 = "string" in
	let str2 = "uclwt" in
	let funcs1 = [caesar 1; xor 1] in
	let funcs2 = [xor 1; Uncipher.uncaesar 1] in
	print_string "testing crypt with \"" ;
	print_string str1 ;
	print_string "\" and functions [caesar 1; xor 1] : " ;
	print_endline (ft_crypt str1 funcs1) ;
	print_string "testing crypt with \"" ;
	print_string str2 ;
	print_string "\" and functions [xor 1; uncaesar 1] : " ;
	print_endline (ft_crypt str2 funcs2)

let () =
	print_testing_rot "radar" ;
	print_testing_rot "string" ;
	print_testing_rot "salu" ;
	print_testing_rot "" ;
	print_testing_rot "a" ;
	print_testing_rot "bknkb" ;
	print_testing_rot "ckved" ;
	print_testing_caesar 42 "ckved" ;
	print_testing_caesar 1 "string" ;
	print_testing_caesar 0 "string" ;
	print_testing_xor "string" 0 ;
	print_testing_xor "string" 5 ;
	print_testing_xor "vdipq" 5 ;
	crypt_tests () ;
	print_endline "-- uncipher :" ;
	Uncipher.print_testing_rot "radar" ;
	Uncipher.print_testing_rot "string" ;
	Uncipher.print_testing_rot "salu" ;
	Uncipher.print_testing_rot "" ;
	Uncipher.print_testing_rot "a" ;
	Uncipher.print_testing_rot "hqtqh" ;
	Uncipher.print_testing_rot "iqbkj" ;
	Uncipher.print_testing_caesar 42 "iqbkj" ;
	Uncipher.print_testing_caesar 1 "string" ;
	Uncipher.print_testing_caesar 0 "string" ;
	Uncipher.uncrypt_tests ()
