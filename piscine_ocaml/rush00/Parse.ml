

let rec parse tab str =
    let illegal tab =
        print_endline "Illegal move" ; get_input tab
    in
    let incorrect tab =
        print_endline "Incorrect format." ; get_input tab
    in
    let rec count_char str car ind acc =
        if String.length str <= ind then acc
        else
            let count = if String.get str ind = car then acc + 1
            else acc in
            count_char str car (ind + 1) count
    in
    let is_digit car = int_of_char car <= int_of_char '9' && int_of_char car
    >= int_of_char '0'
    in
    let rec only_digits str start en =
        if start >= en then true else
        let car = String.get str start in
        if is_digit car = false then false
        else only_digits str (start + 1) en
    in
    let rec ind str car from =
        let len = String.length str in
        if from >= len then (-1)
        else
            if String.get str from = car then from
            else ind str car (from + 1)
    in
    match (count_char str ' ' 0 0) with
        | 1 ->  let space_ind = ind str ' ' 0 in
                let len = String.length str in
                if space_ind < (len - 1) && space_ind > 0 && only_digits str 0
                space_ind && only_digits str (space_ind + 1) len
                then let str1 = String.sub str 0 space_ind in
                     let str2 = String.sub str (space_ind + 1) (len - space_ind - 1) in
                     if space_ind > 5 || (len - space_ind - 1) > 5 then illegal tab
                     else (int_of_string str1, int_of_string str2)
                else incorrect tab
        | _ -> incorrect tab

and get_input tab =
    let inp = read_line () in
    let (x,y) = parse tab inp in
    if Grid.is_in_bound tab (x,y) && Grid.get tab (x,y) = Grid.E then (x,y)
    else (print_endline "Illegal move" ; get_input tab)

let () =
    let tab = Grid.voidTab in
    let (x,y) = get_input tab in
    print_string "(x : " ;
    print_int x ;
    print_string ", y : " ;
    print_int y ;
    print_endline ")"
