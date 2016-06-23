

let print_bool = function
    | true -> print_string "true"
    | _ -> print_string "false"

let () =
    let carbon_dioxyde = new Carbon_dioxyde.carbon_dioxyde in
    let water = new Water.water in
    let tnt = new Trinitrotoluene.trinitrotoluene in
    let biotin = new Biotin.biotin in
    let leucine = new Leucine.leucine in
    print_endline carbon_dioxyde#to_string ;
    print_endline water#to_string ;
    print_endline tnt#to_string ;
    print_endline biotin#to_string ;
    print_endline leucine#to_string ;
    print_string "is carbon_dioxyde = water : " ;
    print_bool (carbon_dioxyde#equals water) ;
    print_string "\nis water = water : " ;
    print_bool (water#equals water) ;
    print_char '\n' 
