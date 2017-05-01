

type t = {
	tiles:					Tile.t array array ;
	mutable heur_value:		int ;
	mutable blue_taken:		int ;
	mutable red_taken:		int
}

type dir = Horizontal | Vertical | DiagUp | DiagDown