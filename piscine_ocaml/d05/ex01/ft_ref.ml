

type 'a ft_ref = {mutable value: 'a}

let return elt =
    {value = elt}

let get (ref:'a ft_ref) =
    ref.value

let set (ref:'a ft_ref) elt =
    ref.value <- elt

let bind (ref:'a ft_ref) func =
    func ref.value



let print_bool = function
    | true -> print_string "true"
    | _ -> print_string "false"

let () =
    print_endline "Creating a = ft_ref 42 with return" ;
    print_endline "Creating b = ft_ref 12.0 with return" ;
    let a = return 42 in
    let b = return 12.0 in
    print_string "Asserting that get a = 42 : " ;
    print_bool (get a = 42) ;
    print_string "\nAsserting that get b = 12.0 : " ;
    print_bool (get b = 12.0) ;
    print_string "\nSetting a to 24\nSetting b to 42.42\n" ;
    set a 24 ;
    set b 42.42 ;
    print_string "Asserting that get a = 24 : " ;
    print_bool (get a = 24) ;
    print_string "\nAsserting that get b = 42.42 : " ;
    print_bool (get b = 42.42) ;
    print_string "\nTest the result of get (bind b (fun x -> return (int_of_float x))) = 42 : " ;
    print_bool (get (bind b (fun x -> return (int_of_float x))) = 42) ;
    print_char '\n'
