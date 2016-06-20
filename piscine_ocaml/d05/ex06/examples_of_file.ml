

let add_to_array arr elt =
    let newArr = Array.make ((Array.length arr) + 1) elt in
    for i = 0 to (Array.length arr) - 1 do
        newArr.(i) <- arr.(i)
    done ;
    newArr

let reverse_list arr =
    let rec rev_list acc = function
        | [] -> acc
        | h::tl -> rev_list (h::acc) tl
    in
    rev_list [] arr

let list_to_array l =
    let rec lta acc = function
        | [] -> acc
        | h::tl -> lta (add_to_array acc h) tl
    in
    lta (Array.make 0 (List.hd l)) l

let reverse_string str =
    let res_str = ref "" in
    for i = 0 to (String.length str) - 1 do
        res_str := (String.make 1 (String.get str i)) ^ !res_str
    done ;
    !res_str

let split_string str car =
    let rec split str car ind acc =
        if ind >= String.length str then acc
        else
            let current_car = String.get str ind in
            let car_as_str = String.make 1 current_car in
            if current_car = car
            then split str car (ind + 1) (""::acc)
            else split str car (ind + 1) ((car_as_str ^ (List.hd acc))::(List.tl acc))
    in list_to_array (split (reverse_string str) car 0 [""])

let convert_radar_line arr =
    let res_floats = ref (Array.make 0 0.0) in
    for i = 0 to (Array.length arr) - 2 do
        try
            res_floats := add_to_array !res_floats (float_of_string arr.(i))
        with | _ -> ignore ()
    done ;
    (!res_floats, arr.((Array.length arr) - 1))

let convert_to_radar csv_lines =
    let res_radars = ref [] in
    for i = (Array.length csv_lines) - 1 downto 0 do
        res_radars := (convert_radar_line (Array.get csv_lines i))::(!res_radars)
    done ;
    !res_radars

let interpret_as_csv lines =
    let res_lines = ref (Array.make 0 (Array.make 0 "salut")) in
    for i = 0 to (Array.length lines) - 1 do
        res_lines := (add_to_array !res_lines (split_string (lines.(i)) ','))
    done ;
    !res_lines

let read_lines filename =
    try
        begin
            let tmp_line = ref "salut" in
            let res_lines = ref (Array.make 0 "salut") in
            let ic = open_in filename in
            while (
                try
                    begin
                        tmp_line := input_line ic ;
                        true
                    end
                with
                | _ -> close_in ic ; false
            ) do
                res_lines := add_to_array !res_lines !tmp_line
            done ;
            !res_lines
        end
    with
    | _ -> Array.make 0 "salut"

let print_float_array a =
    print_string "[|" ;
    for i = 0 to (Array.length a) - 1 do
        if i <> 0 then print_string ", " ;
        print_float a.(i) ;
    done ;
    print_string "|]"

let print_string_array a =
    print_string "[|" ;
    for i = 0 to (Array.length a) - 1 do
        if i <> 0 then print_string ", " ;
        print_char '"' ;
        print_string a.(i) ;
        print_char '"'
    done ;
    print_string "|]"

let read_csv filename =
    let lines = read_lines filename in
    let csv_lines = interpret_as_csv lines in
    csv_lines

let print_radar_line line =
    match line with
    | (floats, str) ->
                print_char '(' ;
                print_float_array floats ;
                print_string ", \"" ;
                print_string str ;
                print_string "\")"

let rec list_get lis ind =
    match lis with
    | [] -> failwith "Out of bounds"
    | h::tl -> if ind = 0 then h else list_get tl (ind - 1)

let examples_of_file filename =
    let csv_lines = read_csv filename in
    let radar_lines = convert_to_radar csv_lines in
    radar_lines
    
let print_radars radar_lines =
    for i = 0 to (List.length radar_lines) - 1 do
        print_int (i + 1) ;
        print_string " -> " ;
        print_radar_line (list_get radar_lines i) ;
        print_char '\n'
    done

let print_testing filename =
    print_string "TESTING WITH \"" ;
    print_string filename ;
    print_endline "\" : \n" ;
    let ex = examples_of_file filename in
    print_radars ex ;
    print_endline "\nEND OF TESTING"

let () =
    print_testing "ionosphere.test_small.csv" ;
    print_testing "lolz" ;
    print_testing ""
