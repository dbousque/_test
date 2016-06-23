

let print_testing atom =
    print_endline (atom#to_string)

let rec print_atoms = function
    | [] -> ignore ()
    | h::tl -> print_testing h ; print_atoms tl

let print_bool = function
    | true -> print_string "true"
    | _ -> print_string "false"

let () =
    let atoms = [
        new Bohrium.bohrium ;
        new Cadmium.cadmium ;
        new Carbon.carbon ;
        new Helium.helium ;
        new Hydrogen.hydrogen ;
        new Nitrogen.nitrogen ;
        new Oxygen.oxygen ;
        new Yttrium.yttrium ;
        new Sulphur.sulphur
    ] in
    print_atoms atoms ;
    let carbon1 = new Carbon.carbon in
    let carbon2 = new Carbon.carbon in
    let oxy = new Oxygen.oxygen in
    print_string "testing if carbon = carbon : " ;
    print_bool (carbon1#equals carbon2) ;
    print_string "\ntesting if carbon = oxygen : " ;
    print_bool (carbon1#equals oxy) ;
    print_char '\n'
