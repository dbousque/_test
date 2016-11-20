

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

module MakePriorityQueue : MAKEPRIORITYQUEUE =
	functor (Node : NODE) ->
		struct
			type t = ((Node.t * int) array * int * int)
			type nodetype = Node.t

			let make () =
				(Array.make 32 (Node.zero, 0), 0, 32)

			let rec rise (elts, last, size) = function
				| 1 -> (elts, last, size)
				| n ->  let current_node, current_prio = elts.(n) in
						let parent_node, parent_prio = elts.((n + 1) / 2) in
						if parent_prio > current_prio then (
							Array.set elts ((n + 1) / 2) (current_node, current_prio) ;
							Array.set elts n (parent_node, parent_prio) ;
							rise (elts, last, size) ((n + 1) / 2)
						)
						else
							(elts, last, size)

			let rec sink (elts, last, size) = function
				| n when n * 2 >= last -> (elts, last, size)
				| n when n * 2 + 1 >= last -> (
						let current_node, current_prio = elts.(n) in
						let left_node, left_prio = elts.(n * 2) in
						if current_prio <= left_prio then
							(elts, last, size)
						else (
							Array.set elts (n * 2) (current_node, current_prio) ;
							Array.set elts n (left_node, left_prio) ;
							sink (elts, last, size) (n * 2)
						)
					)
				| n ->  let current_node, current_prio = elts.(n) in
						let left_node, left_prio = elts.(n * 2) in
						let right_node, right_prio = elts.(n * 2 + 1) in
						if current_prio <= left_prio && current_prio <= right_prio then
							(elts, last, size)
						else if min left_prio right_prio = left_prio then (
							Array.set elts (n * 2) (current_node, current_prio) ;
							Array.set elts n (left_node, left_prio) ;
							sink (elts, last, size) (n * 2)
						)
						else (
							Array.set elts (n * 2 + 1) (current_node, current_prio) ;
							Array.set elts n (right_node, right_prio) ;
							sink (elts, last, size) (n * 2 + 1)
						)

			let add (elts, last, size) node priority =
				let _double_array_size arr size =
					Array.init (size * 2) (fun x -> if x >= size then (Node.zero, 0) else arr.(x))
				in
				let last = last + 1 in
				let elts, size = if last = size then
					(_double_array_size elts size, size * 2)
				else
					(elts, size)
				in
				Array.set elts last (node, priority) ;
				rise (elts, last, size) last

			let pop (elts, last, size) =
				let top_node, top_prio = elts.(1) in
				Array.set elts 1 (elts.(last)) ;
				let last = last - 1 in
				let (elts, last, size) = sink (elts, last, size) 1 in
				(top_node, (elts, last, size))

			let size (elts, last, size) =
				last

		end