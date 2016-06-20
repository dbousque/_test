

let power a b =
    let total = ref 1.0 in
    for i = b downto 1 do
        total := (!total *. a)
    done ;
    !total

let eu_dist a b =
    let total = ref 0.0 in
    for i = 0 to ((Array.length a) - 1) do
        total := !total +. (power ((Array.get a i) -. (Array.get b i)) 2)
    done ;
    sqrt (!total)



let print_float_array a =
    print_char '[' ;
    for i = 0 to (Array.length a) - 1 do
        if i <> 0 then print_string ", " ;
        print_float a.(i) ;
    done ;
    print_char ']'

let print_testing a b =
    print_string "testing with " ;
    print_float_array a ;
    print_string " and " ;
    print_float_array b ;
    print_string " : " ;
    print_float (eu_dist a b) ;
    print_char '\n'

let () =
    let a1 = [|0.0; 0.0; 0.0; 0.0; 0.0|] in
    let a2 = [|1.0; 1.0; 1.0; 1.0; 1.0|] in
    let a3 = [|1.0; (-1.0); 1.0; (-1.0); 1.0|] in
    let a4 = [|(-2.0); (-2.0); 0.0; 2.0; 2.0|] in
    print_testing a1 a1 ;
    print_testing a1 a2 ;
    print_testing a1 a3 ;
    print_testing a2 a3 ;
    print_testing a1 a4
