

let rec ackermann m n =
	if m < 0 || n < 0 then -1
	else
		if m = 0 then n + 1
		else
			if n = 0 then ackermann (m - 1) 1
			else ackermann (m - 1) (ackermann m (n - 1))

let print_testing m n =
	print_string "testing with " ;
	print_int m ;
	print_string ", " ;
	print_int n ;
	print_string " : " ;
	print_int (ackermann m n) ;
	print_char '\n'

let () =
	print_testing (-1) 7 ;
	print_testing 0 0;
	print_testing 0 (-1) ;
	print_testing 1 1 ;
	print_testing 1 0 ;
	print_testing 0 1 ;
	print_testing 2 3 ;
	print_testing 4 1
	print_testing (-1) (-1) 
