

type t

type captures

val make_board : int -> t

val place_tile : t -> int -> int -> int -> bool -> captures

val cancel_move : t -> int -> int -> int -> bool -> captures -> unit

val heuristic_of_moves : t -> is_red:bool -> moves:((int * int) list)
			-> heuristic:(t -> int -> int -> ((int * int) list) -> Heuristic.score)
	-> (((Heuristic.score * int * int) option) * ((int * int * (Heuristic.score * (bool * ((int * int) list)))) list))

val valid_moves : t -> is_red:bool -> heuristic:(t -> int -> int -> ((int * int) list) -> Heuristic.score)
	-> (((Heuristic.score * int * int) option) * ((int * int * (Heuristic.score * (bool * ((int * int) list)))) list))

val print_board : ?min:bool -> t -> unit