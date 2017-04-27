

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

val valid_moves_time : unit -> float

val can_place_tile_time : unit -> float

val around_placed_tiles_time : unit -> float

val make_rows_time : unit -> float

val place_tile_time : unit -> float

val print_board : ?min:bool -> BoardType.t -> unit