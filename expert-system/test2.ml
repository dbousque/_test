

type status = True | False | Undetermined

type fact = string * status * bool * int list

type expression =
    Implies of expression * expression
    | And of expression * expression
    | Or of expression * expression
    | Xor of expression * expression
    | Not of expression
    | Factind of int

let str_of_status = function
    | True -> "[True]"
    | False -> "[False]"
    | Undetermined -> "[Undetermined]"

let make_fact_from_i i =
    ((String.make 1 (Char.chr (i + (Char.code 'A')))), False, false, [])

let print_fact = function
    | (str, stat, encountered) -> print_endline ("Fact \"" ^ str ^ "\" : " ^ (str_of_status
    stat) ^ ", encountered : " ^ (string_of_bool encountered))

let resolve_expr expr facts =
    match expr with
    | Implies (expr1, expr2) -> 

let rec solve_for facts index hashtbl =
    let fact = facts.(index) in
    let rules_list = match fact with | (str, status, encoundered, r_l) -> r_l in
    

let () =
    let facts = Array.init 26 (make_fact_from_i) in
    let expr = Implies (Factind 0, Factind 1) in
    let ret = resolve_expr expr facts in
    Array.iter print_fact facts
