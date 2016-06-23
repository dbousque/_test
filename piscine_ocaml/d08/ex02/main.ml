

let () =
    let methane = new Methane.methane in
    let ethane = new Ethane.ethane in
    let octane = new Octane.octane in
    print_endline methane#to_string ;
    print_endline ethane#to_string ;
    print_endline octane#to_string
