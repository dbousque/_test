

type t = Red | Blue | Empty

let print_tile = function
	| Red -> print_string " Red "
	| Blue -> print_string "Blue "
	| Empty -> print_string "Empty"

let print_tile_min = function
	| Red -> print_string "\027[1;31mo\027[0m"
	| Empty -> print_string "."
	| Blue -> print_string "\027[1;34mo\027[0m"