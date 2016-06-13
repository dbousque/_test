

let rec print_letters c =
	let car = char_of_int c in
	let z_int = int_of_char 'z' in
	if c <= z_int
	then
		begin
			print_char car ;
			print_letters (c + 1)
		end
	else
		begin
			print_char '\n'
		end

let ft_print_alphabet () =
	print_letters (int_of_char 'a')

let main () = ft_print_alphabet ()

let () = main ()
