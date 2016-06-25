

let print_set set =
    let rec _print_set n = function
        | [] -> ignore ()
        | h::tl -> if n <> 0 then print_string ", " ; print_int h ; _print_set
        (n + 1) tl
    in
    print_string "Set (" ;
    ( match set with
    | My_set.Set.Set s -> _print_set 0 s ) ;
    print_char ')'

let print_set_string set =
    let rec _print_set n = function
        | [] -> ignore ()
        | h::tl -> if n <> 0 then print_string ", " ; print_char '"' ; print_string h ;
        print_string "\"" ; _print_set
        (n + 1) tl
    in
    print_string "Set (" ;
    ( match set with
    | My_set.Set.Set s -> _print_set 0 s ) ;
    print_char ')'

let print_bool = function
    | true -> print_string "true"
    | _ -> print_string "false"

let () =
    let set1 = My_set.Set.Set [5; 6; 1; 2; 3; 4; 9; 8; 0] in
    let set2 = My_set.Set.Set [13; 17; 18; 19; 25] in
    let set3 = My_set.Set.Set [13; 5; 6; 1; 2; 19; 119] in
    let set4 = My_set.Set.Set [] in
    let set5 = My_set.Set.bind set1 (fun x -> x + 2) in
    let set6 = My_set.Set.bind set1 (fun x -> string_of_int (x + 2)) in
    print_string "set1 = " ;
    print_set set1 ;
    print_char '\n' ;
    print_string "set2 = " ;
    print_set set2 ;
    print_char '\n' ;
    print_string "set3 = " ;
    print_set set3 ;
    print_char '\n' ;
    print_string "set4 (empty set) = " ;
    print_set set4 ;
    print_char '\n' ;
    print_string "\ncalling return on 10 : " ;
    print_set (My_set.Set.return 10) ;
    print_char '\n' ;
    print_string "calling bind set1 (fun x -> x + 2) : " ;
    print_set set5 ;
    print_char '\n' ;
    print_string "calling bind set1 (fun x -> string_of_int (x + 2)) : " ;
    print_set_string set6 ;
    print_char '\n' ;
    print_string "calling union on set1 set2 : " ;
    print_set (My_set.Set.union set1 set2) ;
    print_char '\n' ;
    print_string "calling union on set2 set3 : " ;
    print_set (My_set.Set.union set2 set3) ;
    print_char '\n' ;
    print_string "calling union on set3 set4 : " ;
    print_set (My_set.Set.union set3 set4) ;
    print_char '\n' ;
    print_string "calling inter on set1 set2 : " ;
    print_set (My_set.Set.inter set1 set2) ;
    print_char '\n' ;
    print_string "calling inter on set2 set3 : " ;
    print_set (My_set.Set.inter set2 set3) ;
    print_char '\n' ;
    print_string "calling inter on set3 set4 : " ;
    print_set (My_set.Set.inter set3 set4) ;
    print_char '\n' ;
    print_string "calling diff on set1 set2 : " ;
    print_set (My_set.Set.diff set1 set2) ;
    print_char '\n' ;
    print_string "calling diff on set2 set3 : " ;
    print_set (My_set.Set.diff set2 set3) ;
    print_char '\n' ;
    print_string "calling diff on set3 set2 : " ;
    print_set (My_set.Set.diff set3 set2) ;
    print_char '\n' ;
    print_string "calling diff on set3 set4 : " ;
    print_set (My_set.Set.diff set3 set4) ;
    print_char '\n' ;
    print_string "calling diff on set4 set2 : " ;
    print_set (My_set.Set.diff set4 set2) ;
    print_char '\n' ;
    print_string "calling filter set1 (fun x -> false) : " ;
    print_set (My_set.Set.filter set1 (fun x -> false)) ;
    print_char '\n' ;
    print_string "calling filter set1 (fun x -> true) : " ;
    print_set (My_set.Set.filter set1 (fun x -> true)) ;
    print_char '\n' ;
    print_string "calling filter set1 (fun x -> x > 7) : " ;
    print_set (My_set.Set.filter set1 (fun x -> x > 7)) ;
    print_char '\n' ;
    print_string "calling filter (union set1 set2) (fun x -> x > 7) : " ;
    print_set (My_set.Set.filter (My_set.Set.union set1 set2) (fun x -> x > 7)) ;
    print_char '\n' ;
    print_string "calling foreach set1 (fun x -> print_int x ; print_char '\\n') : " ;
    print_char '\n' ;
    My_set.Set.foreach set1 (fun x -> print_int x ; print_char '\n') ;
    print_string "calling for_all set1 (fun x -> x > 5) : " ;
    print_bool (My_set.Set.for_all set1 (fun x -> x > 5)) ;
    print_char '\n' ;
    print_string "calling for_all set1 (fun x -> x >= 0) : " ;
    print_bool (My_set.Set.for_all set1 (fun x -> x >= 0)) ;
    print_char '\n' ;
    print_string "calling for_all set4 (fun x -> true) : " ;
    print_bool (My_set.Set.for_all set4 (fun x -> true)) ;
    print_char '\n' ;
    print_string "calling exists set1 (fun x -> x > 9) : " ;
    print_bool (My_set.Set.exists set1 (fun x -> x > 9)) ;
    print_char '\n' ;
    print_string "calling exists set1 (fun x -> x > 8) : " ;
    print_bool (My_set.Set.exists set1 (fun x -> x > 8)) ;
    print_char '\n' ;
    print_string "calling exists set4 (fun x -> true) : " ;
    print_bool (My_set.Set.exists set4 (fun x -> true)) ;
    print_char '\n'
