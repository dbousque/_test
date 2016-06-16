

type phosphate = string

type deoxyribose = string

type nucleobase = A | T | C | G | None

type nucleotide = {
    phos : phosphate ;
    deox : deoxyribose ;
    nucl : nucleobase
}

type helix = nucleotide list

let generate_nucleotide nucl =
    {phos = "phosphate"; deox = "deoxyribose"; nucl =
            match nucl with
                | 'A' -> A
                | 'T' -> T
                | 'C' -> C
                | 'G' -> G
                | _ -> None
    }

let random_nucl () =
    generate_nucleotide ( match Random.int 4 with
        | 0 -> 'A'
        | 1 -> 'T'
        | 2 -> 'C'
        | 3 -> 'G'
        | _ -> ' ' )

let rec generate_helix n : helix =
    Random.self_init ();
    if n <= 0 then []
    else (random_nucl ()::(generate_helix (n - 1)))

let compl_nucl = function
    | {nucl; _} when nucl = A -> generate_nucleotide 'T'
    | {nucl; _} when nucl = T -> generate_nucleotide 'A'
    | {nucl; _} when nucl = C -> generate_nucleotide 'G'
    | {nucl; _} when nucl = G -> generate_nucleotide 'C'
    | _ -> generate_nucleotide ' '

let rec complementary_helix (hel:helix) : helix =
    match hel with
        | [] -> []
        | nucl::nucls -> (compl_nucl nucl)::(complementary_helix nucls)



let nucl_to_string nucl =
    "{\n\tphosphate = " ^
    nucl.phos ^
    "\n\tdeoxyribose = " ^
    nucl.deox ^
    "\n\tnucleobase = " ^
    (match nucl.nucl with
        | A -> "A"
        | T -> "T"
        | C -> "C"
        | G -> "G"
        | None -> "None" ) ^
    "\n}"

let rec helix_to_string (hel:helix) =
    match hel with
        | [] -> ""
        | nucl::nucls -> let nexts = (helix_to_string nucls) in
                         let fst = (nucl_to_string nucl) in
                         if nexts = "" then fst ^ "\n"
                         else fst ^ "\n  ⇩\n" ^ nexts

let print_testing n =
    let ori_helix = generate_helix n in
    let comp_helix = complementary_helix ori_helix in
    print_string " -- testing with " ;
    print_int n ;
    print_string " : \noriginal helix :\n" ;
    print_endline (helix_to_string ori_helix) ;
    print_string "complementary helix :\n" ;
    print_endline (helix_to_string comp_helix)

let () =
    print_testing 0 ;
    print_testing (-1) ;
    print_testing 1 ;
    print_testing 3
