

class people nam =
	object
		val name = nam
		val hp = 100

		initializer print_endline ("People object created with name " ^ nam)

		method to_string = name ^ " : hp=" ^ (string_of_int hp)

		method talk = print_endline ("I'm " ^ name ^ "! Do you know the Doctor?")

		method die = print_endline "Aaaarghh!"
	end
