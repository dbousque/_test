

let rec repeat_x n =
	if n < 0 then "Error"
	else
		if n = 0 then ""
		else "x" ^ repeat_x (n - 1)

let print_testing n =
	print_string "testing with ";
	print_int n ;
	print_string " : \"" ;
	print_string (repeat_x n) ;
	print_string "\"\n"

let () =
	print_testing 0 ;
	print_testing (-1) ;
	print_testing 1 ;
	print_testing 5
