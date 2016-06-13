

let rec string_all func str ind =
	if ind < String.length str
	then
		if func (String.get str ind)
		then string_all func str (ind + 1)
		else false
	else true

let ft_string_all func str =
	string_all func str 0

let is_digit c = c >= '0' && c <= '9'

let print_testing str =
	print_string "testing is_digit with \"" ;
	print_string str ;
	print_string "\" : " ;
	if ft_string_all is_digit str
	then print_string "true"
	else print_string "false" ;
	print_char '\n'

let main () =
	print_testing "012345" ;
	print_testing "012a45" ;
	print_testing "01234a" ;
	print_testing ""

let () = main ()
