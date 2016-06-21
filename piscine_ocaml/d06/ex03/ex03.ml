

module type FRACTIONNAL_BITS =
    sig
        val bits : int
    end

module type FIXED = sig
    type t
    val of_float : float -> t
    val of_int : int -> t
    val to_float : t -> float
    val to_int : t -> int
    val to_string : t -> string
    val zero : t
    val one : t
    val succ : t -> t
    val pred : t -> t
    val min : t -> t -> t
    val max : t -> t -> t
    val gth : t -> t -> bool
    val lth : t -> t -> bool
    val gte : t -> t -> bool
    val lte : t -> t -> bool
    val eqp : t -> t -> bool (** physical equality *)
    val eqs : t -> t -> bool (** structural equality *)
    val add : t -> t -> t
    val sub : t -> t -> t
    val mul : t -> t -> t
    val div : t -> t -> t
    val foreach : t -> t -> (t -> unit) -> unit
end

module type MAKE =
    functor (Frac : FRACTIONNAL_BITS) ->
        FIXED

module Make : MAKE =
    functor (Frac : FRACTIONNAL_BITS) ->
        struct
            type t = int

            let of_float i =
                let round v = if (ceil v) -. v < v -. (floor v) then ceil v else floor v in
                int_of_float (round (i *. (float_of_int (1 lsl Frac.bits))))
            let of_int i = i lsl Frac.bits
            let to_float e = (float_of_int e) /. float_of_int (1 lsl Frac.bits)
            let to_int e = e lsl Frac.bits
            let to_string e = string_of_float (to_float e)
            let zero = 0
            let one = of_int 1
            let succ e = e + 1
            let pred e = e - 1
            let min e1 e2 = if e1 <= e2 then e1 else e2
            let max e1 e2 = if e1 >= e2 then e1 else e2
            let gth e1 e2 = e1 > e2
            let lth e1 e2 = e1 < e2
            let gte e1 e2 = e1 >= e2
            let lte e1 e2 = e1 <= e2
            let eqp e1 e2 = e1 = e2
            let eqs e1 e2 = e1 == e2
            let add e1 e2 = e1 + e2
            let sub e1 e2 = e1 - e2
            let mul e1 e2 = (e1 * e2 + (1 lsl (Frac.bits - 1))) lsr Frac.bits
            let div e1 e2 = ((e1 lsl Frac.bits) + (e2 / 2)) / e2
            let rec foreach e1 e2 func = if lte e1 e2 then (func e1 ; foreach (succ e1) e2 func)
        end

module Fixed4 : FIXED = Make (struct let bits = 4 end)
module Fixed8 : FIXED = Make (struct let bits = 8 end)
let () =
    let x8 = Fixed8.of_float 21.10 in
    let y8 = Fixed8.of_float 21.32 in
    let r8 = Fixed8.add x8 y8 in
    print_endline (Fixed8.to_string r8);
    Fixed4.foreach (Fixed4.zero) (Fixed4.one) (fun f -> print_endline
    (Fixed4.to_string f))
