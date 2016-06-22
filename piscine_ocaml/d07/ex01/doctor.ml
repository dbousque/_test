

class doctor nam ag (sidekic:people) =
	object
		val name = nam
		val age = ag
		val sidekick = sidekic
		val hp = 100

		initializer print_endline ("Object doctor created with name=" ^ nam)

		method to_string = name ^ " : age=" ^ (string_of_int age) ^ " sidekick=(" ^ sidekick#to_string ^ ") hp=" ^ (string_of_int hp)

		method talk = print_endline "Hi! I’m the Doctor!"

		method travel_in_time =
			print_endline "_______(_@_)_______"
			print_endline "| POLICE      BOX |"
			print_endline "|_________________|"
			print_endline " | _____ | _____ |"
			print_endline " | |###| | |###| |"
			print_endline " | |###| | |###| |" 
			print_endline " | _____ | _____ |"
			print_endline " | || || | || || |"
			print_endline " | ||_|| | ||_|| |"
			print_endline " | _____ |$_____ |"
			print_endline " | || || | || || |"
			print_endline " | ||_|| | ||_|| |"
			print_endline " | _____ | _____ |"
			print_endline " | || || | || || |" 
			print_endline " | ||_|| | ||_|| |" 
			print_endline " |       |       |" 

	end
