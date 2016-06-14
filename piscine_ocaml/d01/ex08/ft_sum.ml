

let ft_sum ori_f ori_low ori_up =
	let rec msum f low up acc =
		if up < low then nan
		else
			if low = up then acc +. f low
			else msum f (low + 1) up (acc +. f low)
	in
	msum ori_f ori_low ori_up 0.0

let print_testing low up =
	let func i = float_of_int (i * i) in
	begin
		print_string "testing with low=" ;
		print_int low ;
		print_string " ; up=" ;
		print_int up ;
		print_string " : " ;
		print_float (ft_sum func low up) ;
		print_char '\n'
	end

let () =
	print_testing 1 10 ;
	print_testing 10 10 ;
	print_testing 0 0 ;
	print_testing 1 0 ;
	print_testing (-2) 0 ;
	print_testing 4 6
