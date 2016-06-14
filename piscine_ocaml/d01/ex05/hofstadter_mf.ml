

let rec hfs_f n =
	if n < 0 then -1
	else
		if n = 0 then 1
		else n - (hfs_m (hfs_f (n - 1)))

and hfs_m n =
	if n < 0 then -1
	else
		if n = 0 then 0
		else n - (hfs_f (hfs_m (n - 1)))

let print_testing n =
	print_string "testing with " ;
	print_int n ;
	print_string " : m = " ;
	print_int (hfs_m n) ;
	print_string " ; f = ";
	print_int (hfs_f n) ;
	print_char '\n'

let () =
	print_testing 0 ;
	print_testing 4 ;
	print_testing (-1) ;
