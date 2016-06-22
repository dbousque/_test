

class ['a] army =
	object
		val _soldiers : 'a list = []

		method add sold =
			let rec push_back elt = function
				| [] -> [elt]
				| h::tl -> h::(push_back elt tl)
			in
			{< _soldiers = push_back sold _soldiers >}

		method delete =
			match _soldiers with
			| [] -> {< _soldiers = [] >}
			| h::tl -> {< _soldiers = tl >}

		method print =
			print_string "Printing army : [" ;
			let rec print_rec ind = function
				| [] -> ignore ()
				| h::tl -> if ind <> 0 then print_string ", " ; print_string h#to_string ; print_rec (ind + 1) tl
			in
			print_rec 0 _soldiers ;
			print_endline "]"
	end
