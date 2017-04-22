

let id_func p = p

let list_init f i =
	if i < 0 then raise (Failure "invalid integer under 0") ;
	let rec _list_init acc = function
		| 0 -> acc
		| i -> _list_init ((f (i - 1)) :: acc) (i - 1)
	in
	_list_init [] i