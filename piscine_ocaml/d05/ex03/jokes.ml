

let add_to_array arr elt =
    let newArr = Array.make ((Array.length arr) + 1) elt in
    for i = 0 to (Array.length arr) - 1 do
        newArr.(i) <- arr.(i)
    done ;
    newArr

let read_jokes filename =
    try
        begin
            let arr = Array.make 0 "salut" in
            let res_arr = ref arr in
            let line_ref = ref "salut" in
            let ic = open_in filename in
            while (try
                    begin
                        line_ref := input_line ic ;
                        true
                    end
                  with
                  | _ -> close_in ic ; false ) do
                res_arr := add_to_array !res_arr !line_ref
            done ;
            !res_arr
        end
    with
        | _ -> Array.make 0 "salut"

let () =
    try
        begin
            Random.self_init () ;
            let jokes = read_jokes (Sys.argv).(1) in
            if Array.length jokes > 0
            then
                let ind = Random.int (Array.length jokes) in
                print_endline (jokes.(ind))
        end
    with
        _ -> ignore ()
