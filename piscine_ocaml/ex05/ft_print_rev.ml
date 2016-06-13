

let rec print_rev str ind =
	if ind >= 0
	then
		begin
			print_char (String.get str ind) ;
			print_rev str (ind - 1)
		end
	else
		print_char '\n'

let ft_print_rev str =
	print_rev str ((String.length str) - 1)

let print_testing str =
	print_string "testing with \"" ;
	print_string str ;
	print_string "\" : " ;
	ft_print_rev str

let main () =
	print_testing "test1" ;
	print_testing "" ;
	print_testing "\tlolz\t"

let () = main ()
