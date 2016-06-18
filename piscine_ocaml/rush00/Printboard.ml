

let rec power n x =
	match x with
		| x when x <= 0 -> 1
		| 1 -> n
		| _ -> n * (power n (x - 1))

let rec print_n_char car = function
	| n when n <= 0 -> ignore ()
	| n -> print_char car ; print_n_char car (n - 1)

let nb_chars_on_line line_width nb_sq =
	line_width * 2 + (((line_width / nb_sq) - 1) * 2)

let print_lines line_width nb_sq =
	let rec printl line_width nb_sq ind =
		if ind <> 0 && ind mod nb_sq = 0
		then print_string "| " ;
		print_string "- " ;
		if ind + 1< line_width
		then printl line_width nb_sq (ind + 1)
		else print_char '\n'
	in
	let rec printl_vert line_width nb_sq ind =
		if ind <> 0 && ind < line_width && ind mod nb_sq = 0
		then 	(let nb_dashes = nb_chars_on_line line_width nb_sq in
				print_n_char '-' nb_dashes ;
				print_char '\n' ) ;
		if ind < line_width
		then ( printl line_width nb_sq 0 ; printl_vert line_width nb_sq (ind + 1) )
		else print_char '\n'
	in
	printl_vert line_width nb_sq 0

let print_board depth nb_sq =
	let line_width = power nb_sq depth in
	print_lines line_width nb_sq

let () =
	let depth = 2 in
	let nb_sq = 3 in
	ignore (print_board depth nb_sq)
