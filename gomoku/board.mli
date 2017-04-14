

type t

type captures

val make_board : int -> t

val place_tile : t -> int -> int -> int -> bool -> captures

val cancel_move : t -> int -> int -> int -> bool -> captures -> unit

val valid_moves : t -> is_red:bool -> heuristic:(t -> Heuristic.score)
												-> (int * int * Heuristic.score) list

val print_board : ?min:bool -> t -> unit