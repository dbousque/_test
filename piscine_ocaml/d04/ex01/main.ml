

let print_card_list cards func =
	let rec print_cards cards func n =
		if n = 0 then print_string "[" ;
		match cards with
			| [] -> print_string "]"
			| card::cards ->
				if n <> 0 then print_string ", " ;
				print_string (func card) ;
				print_cards cards func (n + 1)
	in
	print_cards cards func 0

let rm_first = function
	| [] -> []
	| x::xs -> xs

let rec rm_last = function
	| [] -> []
	| x::xs when xs = [] -> []
	| x::xs -> x::(rm_last xs)

let rec get_nexts = function
	| [] -> []
	| card::cards -> (Value.next card)::(get_nexts cards)

let rec get_previous = function
	| [] -> []
	| card::cards -> (Value.previous card)::(get_previous cards)

let () =
	let nexts = get_nexts (rm_last (Value.all)) in
	let previous = get_previous (rm_first (Value.all)) in
	print_string "all cards : " ;
	print_card_list (Value.all) Value.toString ;
	print_string "\nall cards verbose : " ;
	print_card_list (Value.all) Value.toStringVerbose ;
	print_string "\nall valid nexts : " ;
	print_card_list nexts Value.toString ;
	print_string "\nall valid previous : " ;
	print_card_list previous Value.toString ;
	print_char '\n'
