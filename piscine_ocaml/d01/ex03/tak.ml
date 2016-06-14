

let rec tak x y z =
	if y < x
	then tak (tak (x - 1) y z) (tak (y - 1) z x) (tak (z - 1) x y)
	else z

let print_testing x y z =
	print_string "testing with " ;
	print_int x ;
	print_string ", " ;
	print_int y ;
	print_string ", " ;
	print_int z ;
	print_string " : " ;
	print_int (tak x y z) ;
	print_char '\n'

let () =
	print_testing 1 2 3 ;
	print_testing 5 23 7 ;
	print_testing 9 1 0 ;
	print_testing 1 1 1 ;
	print_testing 0 42 0 ;
	print_testing 23498 98734 98776 ;
	print_testing (-1) (-1) (-1)
