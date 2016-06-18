

type t = O | X | E

let voidTab = X

let is_in_bound tab (x,y) =
    if x > 0 && x <= 9 && y > 0 && y <= 9
    then true
    else false

let get tab (x,y) =
    if x > 0 && x <= 9 && y > 0 && y <= 9
    then E
    else O
