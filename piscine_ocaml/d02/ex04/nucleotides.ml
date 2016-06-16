

type phosphate = string

type deoxyribose = string

type nucleobase = A | T | C | G | None

type nucleotide = {
    phos : phosphate ;
    deox : deoxyribose ;
    nucl : nucleobase
}

let generate_nucleotide nucl =
    {phos = "phosphate"; deox = "deoxyribose"; nucl =
            match nucl with
                | 'A' -> A
                | 'T' -> T
                | 'C' -> C
                | 'G' -> G
                | _ -> None
    }



let print_nucl nucl =
    print_string "{\n\tphosphate = " ;
    print_string nucl.phos ;
    print_string "\n\tdeoxyribose = " ;
    print_string nucl.deox ;
    print_string "\n\tnucleobase = " ;
    print_string (match nucl.nucl with
        | A -> "A"
        | T -> "T"
        | C -> "C"
        | G -> "G"
        | None -> "None" ) ;
    print_string "\n}"

let print_testing c =
    print_string "testing with : " ;
    print_char c ;
    print_string " : \n" ;
    print_nucl (generate_nucleotide c) ;
    print_char '\n'

let () =
    print_testing 'A' ;
    print_testing 'G' ;
    print_testing 'a' ;
    print_testing ' '
