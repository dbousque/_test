

type 'a t = Success of 'a | Failure of exn

let return a = Success a

let bind elt func =
	match elt with
	| Failure e -> Failure e
	| Success a -> 
		try func a with
		| e -> Failure e

let recover elt func =
	match elt with
	| Success _ -> elt
	| Failure e -> func e

let filter elt pred =
	match elt with
	| Failure _ -> elt
	| Success a when pred a -> elt
	| _ -> Failure (Failure "argument does not satisfy predicate")

let flatten (nest:'a t t) =
	match nest with
	| Success (Success a) -> Success a
	| Success (Failure e) -> Failure e
	| Failure e -> Failure e
