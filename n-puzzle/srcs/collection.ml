

let make =
	functor (Collec) ->
	struct
		type t = Collec.t
		let validate = Collec.validate
	end