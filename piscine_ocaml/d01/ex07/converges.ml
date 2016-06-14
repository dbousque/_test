

let rec converges f x n =
	if n < 0 then false
	else
		if n = 0 then x == f x
		else converges f (f x) (n - 1)

let my_print_bool x =
	if x then print_endline "true"
	else print_endline "false"

let () =
	my_print_bool (converges (( * ) 2) 2 5 );
	my_print_bool (converges (fun x -> x / 2) 2 3) ;
	my_print_bool (converges (fun x -> x / 2) 2 2)
