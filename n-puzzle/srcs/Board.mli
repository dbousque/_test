

type t = {
	tiles: int list list ;
	empty_cell: int * int ;
	size: int
}

val board_from_tiles : int -> int list list -> t
val rand_board : int -> t
val print_board : t -> unit
val print_raw_board : t -> unit
val make_move : t -> int -> int -> t
val make_end_positions : t -> (int * int) array
val manhattan_distance : t -> (int * int) array -> int
val as_the_crow_flies_distance : t -> (int * int) array -> int
val misplaced : t -> (int * int) array -> int