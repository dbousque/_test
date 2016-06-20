

let sum a b =
    a +. b

let print_testing a b =
    print_string "testing with " ;
    print_float a ;
    print_string " and " ;
    print_float b ;
    print_string " : " ;
    print_float (sum a b) ;
    print_char '\n'

let () =
    print_testing 42.0 42.0 ;
    print_testing 0.0 0.0 ;
    print_testing (-1.0) 0.0 ;
    print_testing 10000000000000000.0 (-2.0) ;
    print_testing (-42.424424242424242424242442424242424242424242424242424242424242424)
        21.424424242424242424242442424242424242424242424242424242424242424
