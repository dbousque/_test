

let print_hour n =
    print_string "printing hour : " ;
    print_int n ;
    print_char '\n'

let print_sub n m =
    print_string "sub " ;
    print_int n ;
    print_string " " ;
    print_int m ;
    print_string " : " ;
    print_int (Watchtower.sub n m) ;
    print_char '\n'

let print_add n m =
    print_string "add " ;
    print_int n ;
    print_string " " ;
    print_int m ;
    print_string " : " ;
    print_int (Watchtower.add n m) ;
    print_char '\n'

let () =
    let (hour1:Watchtower.hour) = 1 in
    let (hour2:Watchtower.hour) = 12 in
    let (hour3:Watchtower.hour) = 7 in
    let (hour4:Watchtower.hour) = 4 in
    let (hour5:Watchtower.hour) = 9 in
    let (hour6:Watchtower.hour) = 12 in
    let (hour7:Watchtower.hour) = 24 in
    print_hour hour1 ;
    print_hour hour2 ;
    print_hour hour3 ;
    print_hour hour4 ;
    print_sub hour1 hour2 ;
    print_sub hour2 hour1 ;
    print_sub hour3 hour4 ;
    print_sub hour4 hour3 ;
    print_sub hour5 hour4 ;
    print_sub hour5 hour6 ;
    print_sub hour5 hour7 ;
    print_sub hour6 hour5 ;
    print_sub 6 6 ;
    print_add hour1 hour2 ;
    print_add hour2 hour1 ;
    print_add hour3 hour4 ;
    print_add hour4 hour3 ;
    print_add hour5 hour4 ;
    print_add hour5 hour6 ;
    print_add hour5 hour7 ;
    print_add hour6 hour5 ;
    print_add 6 6
