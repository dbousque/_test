

type search_result

val is_solvable : search_result -> bool
val make_moves : Board.t -> search_result -> unit
val print_result : search_result -> unit
val solve_board : Board.t -> (Board.t -> (int * int) array -> int) -> (int * int) array -> search_result