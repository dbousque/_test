

type fact = Fact of string

type condition =
    And of condition * condition
    | Or of condition * condition
    | Xor of condition * condition
    | Not of condition * condition
    | Fact

let () =
    let f1 = Fact "A" in
    let f2 = Fact "B" in
    let cond = And of (f1, f2) in
    print_endline "A"
