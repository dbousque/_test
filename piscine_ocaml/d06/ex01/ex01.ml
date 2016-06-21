

module StringHash =
    struct
        type t = string

        let hash str =
            let rec _hash str ind acc =
                match ind with
                | n when n >= String.length str -> acc
                | n -> _hash str (ind + 1) (acc * 33 + int_of_char (String.get str ind))
            in
            _hash str 0 5381

        let equal str1 str2 =
            str1 = str2
    end

module StringHashtbl = Hashtbl.Make (StringHash)

let () =
    let ht = StringHashtbl.create 5 in
    let values = [ "Hello"; "world"; "42"; "Ocaml"; "H" ] in
    let pairs = List.map (fun s -> (s, String.length s)) values in
    List.iter (fun (k,v) -> StringHashtbl.add ht k v) pairs;
    StringHashtbl.iter (fun k v -> Printf.printf "k = \"%s\", v = %d\n" k v) ht
