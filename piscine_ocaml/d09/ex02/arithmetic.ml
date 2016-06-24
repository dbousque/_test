

module type MONOID =
sig
    type element
    val zero1 : element
    val zero2 : element
    val mul : element -> element -> element
    val add : element -> element -> element
    val div : element -> element -> element
    val sub : element -> element -> element
end

module Calc =
    functor (M : MONOID) ->
        struct
            let add = M.add
            let sub = M.sub
            let mul = M.mul
            let div = M.div
            let rec power a = function
                | n when n <= 0 -> M.zero2
                | n -> mul a (power a (n - 1))
            let rec fact = function
                | n when n <= M.zero1 -> M.zero2
                | n -> mul n (fact (sub n M.zero2))
        end

module INT : MONOID with type element = int =
struct
    type element = int
    let zero1 = 0
    let zero2 = 1
    let mul = ( * )
    let add = ( + )
    let div = ( / )
    let sub = ( - )
end

module FLOAT : MONOID with type element = float =
struct
    type element = float
    let zero1 = 0.0
    let zero2 = 1.0
    let mul = ( *. )
    let add = ( +. )
    let div = ( /. )
    let sub = ( -. )
end
