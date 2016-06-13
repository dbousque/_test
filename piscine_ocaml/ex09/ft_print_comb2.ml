

let print_number x =
	if x < 10
	then print_char '0' ;
	print_int x

let print_numbers x y n =
	if n <> 0
	then print_char ',' ; print_char ' ' ;
	print_number x ;
	print_char ' ' ;
	print_number y

let rec print_comb2 x y n =
	print_numbers x y n ;
	if y <> 99
	then print_comb2 x (y + 1) (n + 1)
	else
		if x <> 98
		then print_comb2 (x + 1) (x + 2) (n + 1)
		else print_char '\n'

let ft_print_comb2 () =
	print_comb2 0 1 0

let main () =
	ft_print_comb2 ()

let () = main ()
