

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

type aminoacid = Stop | Ala | Arg | Asn | Asp | Cys | Gln | Glu | Gly | His |
Ile | Leu | Lys | Met | Phe | Pro | Ser | Thr | Trp | Tyr | Val

type protein = aminoacid list

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

let rec generate_bases_triplets (rna:rna) =
    match rna with
        | fst::scd::thrd::rest -> (fst,scd,thrd)::(generate_bases_triplets rest)
        | _ -> []

let decode_arn (rna:rna) : protein =
    let triplets = generate_bases_triplets rna in
    let rec prot_from_triplets triplets =
    match triplets with
        | a::b::c::d::e::f::rest when a = (A,G,A) -> (Arg)::(prot_from_triplets rest)
        | a::b::c::d::e::f::rest when a = (C,U,A) -> (Leu)::(prot_from_triplets rest)
        | a::b::c::d::e::f::rest when a = (U,C,A) -> (Ser)::(prot_from_triplets rest)
        | a::b::c::d::rest when a = (G,C,A) -> (Ala)::(prot_from_triplets rest)
        | a::b::c::d::rest when a = (G,G,A) -> (Gly)::(prot_from_triplets rest)
        | a::b::c::d::rest when a = (C,C,C) -> (Pro)::(prot_from_triplets rest)
        | a::b::c::d::rest when a = (A,C,A) -> (Thr)::(prot_from_triplets rest)
        | a::b::c::d::rest when a = (G,U,A) -> (Val)::(prot_from_triplets rest)
        | a::b::c::rest when a = (U,A,A) -> [Stop]
        | a::b::c::rest when a = (A,U,A) -> (Ile)::(prot_from_triplets rest)
        | a::b::rest when a = (A,A,C) -> (Asn)::(prot_from_triplets rest)
        | a::b::rest when a = (G,A,C) -> (Asp)::(prot_from_triplets rest)
        | a::b::rest when a = (U,G,C) -> (Cys)::(prot_from_triplets rest)
        | a::b::rest when a = (C,A,A) -> (Gln)::(prot_from_triplets rest)
        | a::b::rest when a = (G,A,A) -> (Glu)::(prot_from_triplets rest)
        | a::b::rest when a = (C,A,C) -> (His)::(prot_from_triplets rest)
        | a::b::rest when a = (A,A,A) -> (Lys)::(prot_from_triplets rest)
        | a::b::rest when a = (U,U,C) -> (Phe)::(prot_from_triplets rest)
        | a::b::rest when a = (U,A,C) -> (Tyr)::(prot_from_triplets rest)
        | a::rest when a = (A,U,G) -> (Met)::(prot_from_triplets rest)
        | a::rest when a = (U,G,G) -> (Trp)::(prot_from_triplets rest)
        | _ -> []
    in
    prot_from_triplets triplets



let nucleobase_to_string = function
    | A -> "A"
    | T -> "T"
    | C -> "C"
    | G -> "G"
    | U -> "U"
    | None -> "None"

let nucl_to_string nucl =
    "{\n\tphosphate = " ^
    nucl.phos ^
    "\n\tdeoxyribose = " ^
    nucl.deox ^
    "\n\tnucleobase = " ^
    nucleobase_to_string nucl.nucl ^
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

let rec print_triplets = function
    | [] -> print_string "\n"
    | (a,b,c)::rest ->  print_char '(' ; print_string (nucleobase_to_string a) ;
                        print_char ',' ; print_string (nucleobase_to_string b) ;
                        print_char ',' ; print_string (nucleobase_to_string c) ;
                        print_string ")\n" ; print_triplets rest

let string_of_protein (prot:protein) =
    let get_str amino =
        match amino with
        | Stop -> "Stop"
        | Ala -> "Ala"
        | Arg -> "Arg"
        | Asn -> "Asn"
        | Asp -> "Asp"
        | Cys -> "Cys"
        | Gln -> "Gln"
        | Glu -> "Glu"
        | Gly -> "Gly"
        | His -> "His"
        | Ile -> "Ile"
        | Leu -> "Leu"
        | Lys -> "Lys"
        | Met -> "Met"
        | Phe -> "Phe"
        | Pro -> "Pro"
        | Ser -> "Ser"
        | Thr -> "Thr"
        | Trp -> "Trp"
        | Tyr -> "Tyr"
        | Val -> "Val"
    in
    let rec build_prot_str prot n =
        match prot with
            | [] -> ""
            | ami::amis -> (if n <> 0 then ", " else "") ^ (get_str ami) ^
            build_prot_str amis (n + 1)
    in
    "[" ^ build_prot_str prot 0 ^ "]"

let print_testing n =
    let rna = generate_rna (generate_helix n) in
    print_string "RNA (" ;
    print_int n ;
    print_string " nucleobases) : " ;
    print_rna rna ;
    print_char '\n' ;
    print_triplets (generate_bases_triplets rna)

let print_testing_decode n =
    let rna =
        [A;G;A;A;G;G;C;G;A;C;G;C;C;G;G;C;G;U;A;A;C;A;A;U;G;A;C;G;A;U;U;A;A;U;A;G;U;G;A]
    in
    print_string "triplets : \n" ;
    print_triplets (generate_bases_triplets rna) ;
    print_string "\nprotein : " ;
    print_endline (string_of_protein (decode_arn rna))

let rec helix_from_str str ind : helix =
    if ind >= String.length str then []
    else
        (generate_nucleotide (String.get str ind))::(helix_from_str str (ind + 1))

let life str =
    print_string "input : " ;
    print_endline str ;
    let helix = helix_from_str str 0 in
    print_string "helix : " ;
    print_string (helix_to_string helix) ;
    let rna = generate_rna helix in
    print_string "\nrna : " ;
    print_rna rna ;
    let triplets = generate_bases_triplets rna in
    print_string "\n\ntriplets :\n" ;
    print_triplets triplets ;
    print_string "protein : " ;
    print_endline (string_of_protein (decode_arn rna)) ;
    print_char '\n'

let () =
    life "TCTTCCGCTGCGGCCGCATTGTTACTGCTAATTATCACT"
