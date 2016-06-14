

let rec iter f x n =
	if n < 0 then -1
	else
		if n = 0 then x
		else f (iter f x (n - 1))

let print_testing f x n =
	print_string "testing with " ;
	print_int x ;
	print_string ", " ;
	print_int n ;
	print_string " : " ;
	print_int (iter f x n) ;
	print_char '\n'

let () =
	let func = (fun x -> x + 2) in
	begin
		print_testing func 0 0 ;
		print_testing func 0 1 ;
		print_testing func 0 2 ;
		print_testing func (-2) 3
	end ;
	print_char '\n' ;
	let func = (fun x -> x * x) in
	begin
		print_testing func 2 4
	end
