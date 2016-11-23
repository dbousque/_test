

type parse_result = {
	heuristic: string ;
	greedy: bool ;
	in_place: bool ;
	n: int ;
	files: string list
}

val parse_options : unit -> parse_result
val parse_file : string -> Board.t