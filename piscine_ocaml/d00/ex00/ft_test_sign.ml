

let ft_test_sign x =
	if x < 0
	then print_endline "negative"
	else print_endline "positive"

let print_testing x =
	begin
		print_string "test with ";
		print_int x;
		print_string ": "
	end

let main () =
	begin
		print_testing 42;
		ft_test_sign 42;
		print_testing (-42);
		ft_test_sign (-42);
		print_testing 0;
		ft_test_sign 0;
		print_testing (-1);
		ft_test_sign (-1)
	end

let () = main ()