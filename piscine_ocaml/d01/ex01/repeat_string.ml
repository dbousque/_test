

let rec repeat_string ?(str="x") n =
	if n < 0 then "Error"
	else
		if n = 0 then ""
		else str ^ (repeat_string ~str:str (n - 1))

let print_testing str n has_str_arg =
	print_string "testing with ";
	print_int n ;
	if has_str_arg
	then print_string " and string \"" ;
		 print_string str ;
		 print_string "\"" ;
	print_string " : \"" ;
	if has_str_arg then print_string (repeat_string ~str:str n)
	else print_string (repeat_string n) ;
	print_string "\"\n"

let () =
	print_testing "" 0 false ;
	print_testing "" (-1) false ;
	print_testing "" 1 false ;
	print_testing "" 5 false ;
	print_testing "abc" 0 true ;
	print_testing "abc" (-1) true ;
	print_testing "abc" 1 true ;
	print_testing "abc" 5 true 
