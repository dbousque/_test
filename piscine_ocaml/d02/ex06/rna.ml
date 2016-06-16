

type phosphate = string

type deoxyribose = string

type nucleobase = A | T | C | G | U | None

type nucleotide = {
    phos : phosphate ;
    deox : deoxyribose ;
    nucl : nucleobase
}

type helix = nucleotide list

type rna = nucleobase list

let generate_nucleotide nucl =
    {phos = "phosphate"; deox = "deoxyribose"; nucl =
            match nucl with
                | 'A' -> A
                | 'T' -> T
                | 'C' -> C
                | 'G' -> G
                | 'U' -> U
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

let compl_nucleobase = function
    | A -> U
    | T -> A
    | G -> C
    | C -> G
    | _ -> None

let generate_rna (hel:helix) : rna =
    let rec gen_rna = function
        | [] -> []
        | nucl::nucls -> (compl_nucleobase nucl.nucl)::(gen_rna nucls)
    in
    gen_rna hel



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
        | U -> "U"
        | None -> "None" ) ^
    "\n}"

let rec helix_to_string (hel:helix) =
    match hel with
        | [] -> ""
        | nucl::nucls -> let nexts = (helix_to_string nucls) in
                         let fst = (nucl_to_string nucl) in
                         if nexts = "" then fst ^ "\n"
                         else fst ^ "\n  ⇩\n" ^ nexts


let rec print_rna = function
    | [] -> print_string ""
    | nucl::nucls -> 
        begin
            match nucl with
                | A -> print_char 'A'
                | U -> print_char 'U'
                | G -> print_char 'G'
                | C -> print_char 'C'
                | _ -> print_string ""
        end ;
        print_rna nucls

let print_testing n =
    let hel = generate_helix n in
    print_string "testing with a helix of " ;
    print_int n ;
    print_string " nucleotides :\nhelix :\n" ;
    print_string (helix_to_string hel) ;
    print_string " --> RNA : " ;
    print_rna (generate_rna hel) ;
    print_char '\n'

let () =
    print_testing 0 ;
    print_testing 6
