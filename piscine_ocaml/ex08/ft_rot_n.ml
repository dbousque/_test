

let is_lower c =
	c >= 'a' && c <= 'z'

let is_upper c =
	c >= 'A' && c <= 'Z'

let is_letter c =
	is_lower c || is_upper c

let rec add_n c n =
	let c_int = int_of_char c in
	let z_min = int_of_char 'z' in
	let z_maj = int_of_char 'Z' in
	if (is_lower c && c_int + n <= z_min) || (is_upper c && c_int + n <= z_maj)
	then char_of_int (c_int + n)
	else
		if is_lower c
		then add_n 'a' ((n - (z_min - c_int)) - 1)
		else add_n 'A' ((n - (z_maj - c_int)) - 1)

let ft_rot_n n str =
	let rotate c =
		if is_letter c
		then add_n c n
		else c
	in
	String.map rotate str

let print_testing n str =
	print_string "testing with " ;
	print_int n ;
	print_string ", \"" ;
	print_string str ;
	print_string "\" : " ;
	print_string (ft_rot_n n str) ;
	print_char '\n'

let main () =
	print_testing 0 "abcdefghijklmnopqrstuvwxyz" ;
	print_testing 1 "abcdefghijklmnopqrstuvwxyz" ;
	print_testing 26 "abcdefghijklmnopqrstuvwxyz" ;
	print_testing 27 "abcdefghijklmnopqrstuvwxyz" ;
	print_testing 1 "NBzlk qnbjr !" ;
	print_testing 1 "zyOI2EAS67B9ab"

let () = main ()
