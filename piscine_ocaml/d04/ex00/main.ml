

let print_color_list cols =
	let rec print_cols cols func n =
		if n = 0 then print_string "[" ;
		match cols with
			| [] -> print_string "]"
			| col::cols ->
				if n <> 0 then print_string ", " ;
				print_string (func col) ;
				print_cols cols func (n + 1)
	in
	print_cols cols Color.toString 0 ;
	print_char '\n' ;
	print_cols cols Color.toStringVerbose 0 ;
	print_char '\n'

let () =
	print_color_list (Color.all)
