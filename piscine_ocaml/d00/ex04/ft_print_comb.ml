

let print_numbers x y z n =
	if n <> 0 then print_string ", " ;
	print_int x ;
	print_int y ;
	print_int z

let rec print_comb x y z n =
	print_numbers x y z n ;
	if z <> 9
	then print_comb x y (z + 1) (n + 1)
	else
		if y <> 8
		then print_comb x (y + 1) (y + 2) (n + 1)
		else
			if x <> 7
			then print_comb (x + 1) (x + 2) (x + 3) (n + 1)
			else print_string "\n"

let ft_print_comb () =
	print_comb 0 1 2 0

let main () = ft_print_comb ()

let () = main ()
