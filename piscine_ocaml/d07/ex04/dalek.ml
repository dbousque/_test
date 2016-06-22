

class dalek =
    object (self)
        val name = Random.self_init () ; "Dalek" ^ String.make 1 (char_of_int ((Random.int 95)
        + 32)) ^ String.make 1 (char_of_int ((Random.int 95) + 32)) ^ String.make 1 (char_of_int ((Random.int 95)
        + 32))
        val hp = 100
        val mutable shield = true

        method to_string = name ^ " : hp=" ^ (string_of_int hp) ^ " shield=" ^ (if shield then "true" else "false")

		method talk =
			print_endline (
				match Random.int 4 with
				| 0 -> "Explain! Explain!"
				| 1 -> "Exterminate! Exterminate!"
				| 2 -> "I obey!"
				| _ -> "You are the Doctor! You are the enemy of the Daleks!"
			)

		method exterminate (person:People.people) =
			shield <- shield = false ;
			person#die

		method die =
			print_endline "Emergency Temporal Shift!"

    end
