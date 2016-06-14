

let fibonacci n =
	if n < 0 then -1
	else
		let rec fibo n i fst scd =
			if n <= 1 then n
			else
				if n = i then fst + scd
				else fibo n (i + 1) scd (fst + scd)
		in
		fibo n 2 0 1

let print_testing n =
	print_string "testing with " ;
	print_int n ;
	print_string " : " ;
	print_int (fibonacci n) ;
	print_char '\n'

let () =
	print_testing (-1) ;
	print_testing 0 ;
	print_testing 1 ;
	print_testing 2 ;
	print_testing 3 ;
	print_testing 4 ;
	print_testing 5 ;
	print_testing 6
