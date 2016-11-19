

module type NODE =
sig
	type t

	val zero : t
	val comp : t -> t -> int
end

module type PRIORITYQUEUE =
sig
	type t
	type nodetype

	val make : unit -> t
	val add : t -> nodetype -> int -> t
	val pop : t -> (nodetype * t)
	val size : t -> int
end

module type MAKEPRIORITYQUEUE =
	functor (Node : NODE) ->
        PRIORITYQUEUE with type nodetype = Node.t

module MakePriorityQueue : MAKEPRIORITYQUEUE =
	functor (Node : NODE) ->
		struct
			type t = (Node.t array * int * int)
			type nodetype = Node.t

			let make () =
				(Array.make 32 Node.zero, )
		end