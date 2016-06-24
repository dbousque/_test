

let print_proj (proj:App.project) =
    match proj with
    | (n,s,g) -> print_string "(name=" ; print_string n ; print_string " ; status=" ; print_string s ; print_string " ; grade=" ; print_int g ; print_string ")"

let () =
    let proj1:App.project = ("get_next_line", "failed", 32) in
    let proj2:App.project = ("fillit", "succeed", 87) in
    let proj3:App.project = ("piscine ocaml", "succeed", 126) in
    print_proj proj1 ;
    print_char '\n' ;
    print_proj proj2 ;
    print_char '\n' ;
    print_proj proj3 ;
    print_char '\n' ;
    print_string "calling fail on piscine ocaml : " ;
    print_proj (App.fail proj3) ;
    print_char '\n' ;
    print_string "calling success on get_next_line : " ;
    print_proj (App.success proj1) ;
    print_char '\n' ;
    print_string "combining get_next_line and piscine ocaml : " ;
    print_proj (App.combine proj1 proj3) ;
    print_char '\n' ;
    print_string "combining fillit and piscine ocaml : " ;
    print_proj (App.combine proj2 proj3) ;
    print_char '\n' ;
    print_string "zero project : " ;
    print_proj (App.zero) ;
    print_char '\n'
