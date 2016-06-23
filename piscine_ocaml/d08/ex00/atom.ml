

class virtual atom nam symbol numb =
object (self)
    val _name = nam
    val _symbol = symbol
    val _atomic_number = numb

    method name:string = _name
    method symbol:string = _symbol
    method atomic_number:int = _atomic_number
    method to_string = "Atom " ^ self#name ^ " : {symbol: " ^ self#symbol ^ " ; number : " ^ (string_of_int self#atomic_number) ^ "}"
    method equals (that:atom) = (that#name = self#name && that#symbol = self#symbol
                                && that#atomic_number = self#atomic_number)
    method greater_than (that:atom) =
        if self#atomic_number > that#atomic_number then true
        else false
    method greater_than_string (that:atom) =
        if self#symbol > that#symbol then true
        else false
end
