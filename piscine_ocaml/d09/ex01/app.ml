

type project = string * string * int
let zero : project = ("","",0)
let combine ((n1,s1,g1):project) ((n2,s2,g2):project) : project = let av = (g1 + g2) / 2 in (n1 ^ n2, (if av > 80 then "succeed" else "failed"), av)
let fail ((n,s,g):project) : project = (n, "failed", 0)
let success ((n,s,g):project) : project = (n, "succeed", 80)
