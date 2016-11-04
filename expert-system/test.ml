

type status = True | False | Undetermined

type fact = string * status

type expression =
    Implies of expression * expression
    | And of expression * expression
    | Or of expression * expression
    | Xor of expression * expression
    | Not of expression
    | Exprval of status

let or_status stat1 stat2 =
    match stat1 with
    | True -> True
    | False -> ( match stat2 with
               | True -> True
               | False -> False
               | Undetermined -> Undetermined )
    | Undetermined -> ( match stat2 with
                      | True -> True
                      | _ -> Undetermined )

let xor_status stat1 stat2 =
    if stat1 = True && stat2 = False then True
    else if stat1 = False && stat2 = True then True
    else if stat1 != Undetermined && stat2 != Undetermined then False
    else Undetermined

let and_status stat1 stat2 =
    if stat1 = True && stat2 = True then True
    else if stat1 != Undetermined && stat2 != Undetermined then False
    else Undetermined

let not_status stat =
    if stat = True then False
    else if stat = False then True
    else Undetermined

let rec resolve_expr = function
    | Implies (expr1, expr2) -> resolve_expr (Or (Exprval (not_status (resolve_expr expr1)), expr2))
    | Not expr -> not_status (resolve_expr expr)
    | Xor (expr1, expr2) -> xor_status (resolve_expr expr1) (resolve_expr expr2)
    | And (expr1, expr2) -> and_status (resolve_expr expr1) (resolve_expr expr2)
    | Or (expr1, expr2) -> or_status (resolve_expr expr1) (resolve_expr expr2)
    | Exprval stat -> stat

let str_of_status = function
    | True -> "[True]"
    | False -> "[False]"
    | Undetermined -> "[Undetermined]"

type ex = expression list * fact list

A
A => B v C


A
C

A => B
C and B => D


[Not ((Or (Not True) ('b' Undetermined))), (Implies (And C B) D)  ] * ['b'
Undetermined, 'd' Undetermined]




let () =
    let expr = Implies (Exprval True, Exprval Undetermined) in
    let res = resolve_expr expr in
    print_endline (str_of_status res)
