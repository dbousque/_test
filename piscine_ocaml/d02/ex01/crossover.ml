

let rec is_in elt lis =
    match lis with
        | [] -> false
        | x::xs -> x = elt || is_in elt xs

let crossover lis1 lis2 =
    let rec cross lis1 lis2 acc =
        match lis2 with
            | [] -> acc
            | x::xs when is_in x lis1 -> cross lis1 xs (x::acc)
            | x::xs -> cross lis1 xs acc
    in
    cross lis1 lis2 []





let print_bool = function
    | true -> print_string "true"
    | _ -> print_string "false"

let my_print_string x =
    print_char '"' ;
    print_string x ;
    print_char '"'

let print_list_string lis =
    print_char '[' ;
    let rec print_list_rec lis n =
        match lis with
            | x::xs ->
            begin
                if n <> 0 then print_string ", " ;
                my_print_string x ;
                print_list_rec xs (n + 1)
            end
            | _ -> print_string "" ;
    in
    print_list_rec lis 0 ;
    print_char ']'

let print_list_int lis =
    print_char '[' ;
    let rec print_list_rec lis n =
        match lis with
            | x::xs ->
            begin
                if n <> 0 then print_string ", " ;
                print_int x ;
                print_list_rec xs (n + 1)
            end
            | _ -> print_string "" ;
    in
    print_list_rec lis 0 ;
    print_char ']'

let print_list_bool lis =
    print_char '[' ;
    let rec print_list_rec lis n =
        match lis with
            | x::xs ->
            begin
                if n <> 0 then print_string ", " ;
                print_bool x ;
                print_list_rec xs (n + 1)
            end
            | _ -> print_string "" ;
    in
    print_list_rec lis 0 ;
    print_char ']'

let print_testing_string lis1 lis2 =
    print_string "testing with " ;
    print_list_string lis1 ;
    print_string ", " ;
    print_list_string lis2 ;
    print_string " : " ;
    print_list_string (crossover lis1 lis2) ;
    print_char '\n'

let print_testing_int lis1 lis2 =
    print_string "testing with " ;
    print_list_int lis1 ;
    print_string ", " ;
    print_list_int lis2 ;
    print_string " : " ;
    print_list_int (crossover lis1 lis2) ;
    print_char '\n'

let print_testing_bool lis1 lis2 =
    print_string "testing with " ;
    print_list_bool lis1 ;
    print_string ", " ;
    print_list_bool lis2 ;
    print_string " : " ;
    print_list_bool (crossover lis1 lis2) ;
    print_char '\n'

let () =
    print_testing_int [1;2;3;4;5] [3;4;5;6;7] ;
    print_testing_bool [true;true;true] [false;false;false] ;
    print_testing_string ["lol";"un";"peu"] ["un";"grand";"lol"]
