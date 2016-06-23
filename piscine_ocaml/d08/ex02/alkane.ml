

class virtual alkane n =
object
    inherit Molecule.molecule
                ((  match n with
                    | 1 -> "meth"
                    | 2 -> "eth"
                    | 3 -> "prop"
                    | 4 -> "but"
                    | 5 -> "pent"
                    | 6 -> "hex"
                    | 7 -> "hept"
                    | 8 -> "oct"
                    | 9 -> "non"
                    | 10 -> "dec"
                    | 11 -> "Undec"
                    | 12 -> "Dodec"
                    | n -> "tronched" ) ^ "ane") 

                ( let rec build_n n (acc:Atom.atom list) =
                    match n with
                    | 0 -> [new Hydrogen.hydrogen] @ [new Hydrogen.hydrogen] @ acc
                    | n -> build_n (n - 1) ([new Hydrogen.hydrogen] @ [new
                    Hydrogen.hydrogen] @ [new Carbon.carbon] @ acc)
                  in
                  build_n n [])
end
