
let rec ft_countdown x =
	if x <= 0
	then
		begin
			print_int 0 ;
			print_char '\n'
		end
	else
		begin
			print_int x ;
			print_char '\n' ;
			ft_countdown (x - 1)
		end
	
let print_testing x =
	print_string "testing with " ;
	print_int x ;
	print_endline " :"

let main () =
	print_testing 5 ;
	ft_countdown 5 ;
	print_testing 1 ;
	ft_countdown 1 ;
	print_testing (-1) ;
	ft_countdown (-1)

let () = main ()
