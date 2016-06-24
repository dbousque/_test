

type hour = int
let zero:hour = 12
let add (a1:hour) (a2:hour) : hour =
    let res = (a1 + a2) mod zero in if res = 0 then zero else res
let sub (a1:hour) (a2:hour) : hour =
    let h = (a1 - a2) mod zero in if h < 0 then zero + h else (if h = 0 then 12
    else h )
