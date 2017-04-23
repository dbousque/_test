

type captures

val make_board : int -> BoardType.t

val place_tile : BoardType.t -> int -> int -> int -> bool -> captures

val can_place_tile : BoardType.t -> int -> int -> bool
		-> (BoardType.t -> int -> int -> ((int * int) list) -> int) option
		->bool * (Heuristic.score * (bool * ((int * int) list)))

val cancel_move : BoardType.t -> int -> int -> int -> bool -> captures -> unit

val heuristic_of_moves : BoardType.t -> is_red:bool -> moves:((int * int) list)
			-> heuristic:(BoardType.t -> int -> int -> ((int * int) list) -> int)
	-> (((Heuristic.score * int * int) option) * ((int * int * (Heuristic.score * (bool * ((int * int) list)))) list))

val valid_moves : BoardType.t -> is_red:bool -> heuristic:(BoardType.t -> int -> int -> ((int * int) list) -> int)
	-> (((Heuristic.score * int * int) option) * ((int * int * (Heuristic.score * (bool * ((int * int) list)))) list))

val print_board : ?min:bool -> BoardType.t -> unit