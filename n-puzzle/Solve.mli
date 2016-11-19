

type search_result

val print_result : search_result -> unit
val solve_board : Board.t -> (Board.t -> int) -> (int * int) array -> search_result