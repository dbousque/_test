

module Calc_int = Arithmetic.Calc(Arithmetic.INT)
module Calc_float = Arithmetic.Calc(Arithmetic.FLOAT)

let () =
    print_endline (string_of_int (Calc_int.power 3 3));
    print_endline (string_of_float (Calc_float.power 3.0 3));
    print_endline (string_of_int (Calc_int.mul (Calc_int.add 20 1) 2));
    print_endline (string_of_float (Calc_float.mul (Calc_float.add 20.0 1.0)
    2.0)) ;
	print_string "power 3 0 : " ;
    print_endline (string_of_int (Calc_int.power 3 0)) ;
	print_string "power 3 1 : " ;
    print_endline (string_of_int (Calc_int.power 3 1)) ;
	print_string "power 3.0 0 : " ;
    print_endline (string_of_float (Calc_float.power 3.0 0)) ;
	print_string "power 3.0 1 : " ;
    print_endline (string_of_float (Calc_float.power 3.0 1)) ;
	print_string "fact 3 : " ;
    print_endline (string_of_int (Calc_int.fact 3)) ;
	print_string "fact 0 : " ;
    print_endline (string_of_int (Calc_int.fact 0)) ;
	print_string "fact 1 : " ;
    print_endline (string_of_int (Calc_int.fact 1)) ;
	print_string "fact 5 : " ;
    print_endline (string_of_int (Calc_int.fact 5)) ;
	print_string "fact 3.0 : " ;
    print_endline (string_of_float (Calc_float.fact 3.0)) ;
	print_string "fact 0.0 : " ;
    print_endline (string_of_float (Calc_float.fact 0.0)) ;
	print_string "fact 1.0 : " ;
    print_endline (string_of_float (Calc_float.fact 1.0)) ;
	print_string "fact 5.0 : " ;
    print_endline (string_of_float (Calc_float.fact 5.0)) ;
	print_string "fact 0.5 : " ;
	print_endline (string_of_float (Calc_float.fact 0.5)) ;
	print_string "fact 1.5 : " ;
	print_endline (string_of_float (Calc_float.fact 1.5)) ;
	print_string "fact 1.1 : " ;
	print_endline (string_of_float (Calc_float.fact 1.1))
