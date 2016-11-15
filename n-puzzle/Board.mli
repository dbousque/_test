

type t = {
	tiles: int list list ;
	empty_cell: int * int ;
	size: int
}

val rand_board : int -> t
val print_board : t -> unit