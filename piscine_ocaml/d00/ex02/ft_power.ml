

let rec ft_power x y =
	if y = 0
	then 1
	else x * (ft_power x (y - 1))

let print_testing x y =
	print_string "testing with " ;
	print_int x ;
	print_string ", " ;
	print_int y ;
	print_string " : " ;
	print_int (ft_power x y) ;
	print_char '\n'

let main () =
	print_testing 5 1 ;
	print_testing 5 0 ;
	print_testing 5 2 ;
	print_testing 0 5 ;
	print_testing 1 5 ;
	print_testing 2 5

let () = main ()
