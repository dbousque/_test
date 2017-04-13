

type score =
	| Win
	| Loss
	| Score of int

let better_score score1 score2 =
	match score1 with
	| Win -> Win
	| Loss -> score2
	| Score i1 -> (
			match score2 with
			| Win -> Win
			| Loss -> score1
			| Score i2 -> max i1 i2
		)

let void_score = Loss