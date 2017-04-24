

let id_func p = p

let list_init f i =
	if i < 0 then raise (Failure "invalid integer under 0") ;
	let rec _list_init acc = function
		| 0 -> acc
		| i -> _list_init ((f (i - 1)) :: acc) (i - 1)
	in
	_list_init [] i

let sublist lst _start _end =
	let rec _sublist lst acc i =
		match lst with
		| [] -> acc
		| fst :: rest -> (
			if i >= _end then acc
			else (
				let acc = if i >= _start then fst :: acc else acc in
				_sublist rest acc (i + 1)
			)
		)
	in
	List.rev (_sublist lst [] 0)