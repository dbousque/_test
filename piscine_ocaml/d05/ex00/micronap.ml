

let my_sleep () = Unix.sleep 1

let micronap seconds =
    for i = 0 to (seconds - 1) do
        my_sleep ()
    done

let () =
    let args = Sys.argv in
    try let seconds = int_of_string (args.(1)) in
        micronap seconds
    with
        | Invalid_argument _ -> ignore ()
        | Failure _ -> ignore ()
        | _ -> ignore ()
