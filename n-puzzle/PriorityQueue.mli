

module type NODE =
sig
	type t

	val zero : t
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
        PRIORITYQUEUE with type t = ((Node.t * int) array * int * int) and type nodetype = Node.t

module MakePriorityQueue : MAKEPRIORITYQUEUE