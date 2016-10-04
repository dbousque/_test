

let rec is_palindrome str fst lst =
	if lst <= fst 
	then true
	else
		let fst_car = String.get str fst in
		let lst_car = String.get str lst in
		if fst_car <> lst_car
		then false
		else is_palindrome str (fst + 1) (lst - 1)

let ft_is_palindrome str =
	let ind_last = ((String.length str) - 1) in
	is_palindrome str 0 ind_last

let print_testing str =
	print_string "testing with \"" ;
	print_string str ;
	print_string "\" : " ;
	let to_print =
		if ft_is_palindrome str
		then "true"
		else "false"
	in
	print_string to_print ;
	print_char '\n'

let main () =
	print_testing "bob" ;
	print_testing "" ;
	print_testing "string" ;
	print_testing "radar" ;
	print_testing " ok " ;
	print_testing "beeb"

let () = main ()
