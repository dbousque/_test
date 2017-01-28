

type t = Red | Blue | Empty

let print_place = function
	| Red -> print_string " Red "
	| Blue -> print_string "Blue "
	| Empty -> print_string "Empty"