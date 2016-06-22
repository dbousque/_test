

class dalek =
    object (self)
        val name = Random.self_init () ; "Dalek" ^ String.make 1 (char_of_int ((Random.int 95)
        + 32)) ^ String.make 1 (char_of_int ((Random.int 95) + 32)) ^ String.make 1 (char_of_int ((Random.int 95)
        + 32))
        val hp = 100
        val mutable shield = true

        method to_string = name ^ " : hp=" ^ (string_of_int hp) ^ " shield=" (if shield then "true" else "false")

    end

let () =
    let dalek = new dalek in
