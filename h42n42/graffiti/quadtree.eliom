

module type Leaf = sig
	type t
	val get_coords : t -> (float * float)
	val get_size : t -> (float * float)
end

module type Quadtree = sig
	type t
	type tree
	type leaftype
	val make : float -> float -> t
	val add : t -> leaftype -> t
	val collision_pred : t -> leaftype -> (leaftype -> leaftype -> bool) -> bool
end

module type MakeQuadtreeSig =
	functor (Leaftype : Leaf) ->
		Quadtree

(**
type leaftype = Leaftype.t and
			type tree = (
				Node of (leaftype * leaftype * leaftype * leaftype * leaftype list)
				| Leaf of leaftype list
			) and
			type t = (float * float * tree)

**)

module MakeQuadtree : MakeQuadtreeSig =
	functor (Leaftype : Leaf) ->
		struct
			type leaftype = Leaftype.t
			type tree = Node of (tree * tree * tree * tree * leaftype list) | Leaf of leaftype list
			type t = (float * float * tree)

			let make width height =
				(width, height, Leaf [])

			let add (width, height, node) leaf =
				let _add node leaf x y width height =
					match node with
					| Node (tl, tr, bl, br, lst) -> Leaf []
					| Leaf lst -> Leaf (leaf :: lst)
				in
				(width, height, _add node leaf 0.0 0.0 width height)

			let collision_pred tree leaf pred =
				true
		end