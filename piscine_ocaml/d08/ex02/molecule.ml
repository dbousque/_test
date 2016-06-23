

class virtual molecule name atoms =
object (self)
    val _name = name
    val _atoms = atoms

    method name:string = _name

    method private sort_atoms atoms =
        let atom_sort a1 a2 =
            let a1_val =
                begin
                    if a1#equals (new Carbon.carbon)
                    then 2
                    else
                        begin
                            if a1#equals (new Hydrogen.hydrogen)
                            then 1
                            else 0
                        end
                end
            in
            let a2_val =
                begin
                    if a2#equals (new Carbon.carbon)
                    then 2
                    else
                        begin
                            if a2#equals (new Hydrogen.hydrogen)
                            then 1
                            else 0
                        end
                end
            in
            if a1_val > 0 || a2_val > 0
            then
                if a1_val >= a2_val
                then (-1)
                else
                    if a1_val = a2_val
                    then 0
                    else 1
            else
                if a2#greater_than_string a1 then (-1)
                else if a1#equals a2 then 0
                else 1
        in
        List.sort atom_sort atoms

    method formula:string =
        let atoms = self#sort_atoms _atoms in
        let nb_atom_to_repr symb nb =
            if nb = 1 then symb
            else symb ^ (string_of_int nb)
        in
        let rec count_symbol current_symbol count = function
            | [] -> if count = 0 then "" else nb_atom_to_repr current_symbol count
            | h::tl when count = 0 || h#symbol = current_symbol -> count_symbol
            h#symbol (count + 1) tl
            | h::tl -> nb_atom_to_repr current_symbol count ^ (count_symbol
            h#symbol 1 tl)
        in
        count_symbol "a" 0 atoms

    method to_string:string = "Molecule " ^ self#name ^ " : " ^ self#formula

    method equals (that:molecule) = self#to_string = that#to_string
end
