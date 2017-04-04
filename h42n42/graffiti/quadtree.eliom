

[%%shared

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

module type MakeSig =
	functor (Leaftype : Leaf) ->
		Quadtree with type leaftype = Leaftype.t

(**
type leaftype = Leaftype.t and
			type tree = (
				Node of (leaftype * leaftype * leaftype * leaftype * leaftype list)
				| Leaf of leaftype list
			) and
			type t = (float * float * tree)

**)

module Make : MakeSig =
	functor (Leaftype : Leaf) ->
		struct
			type leaftype = Leaftype.t
			type tree = Node of (tree * tree * tree * tree * leaftype list) | Leaf of leaftype list
			type t = (float * float * tree)
			type newleaf = {
				t: leaftype ;
				x: float ;
				y: float
			}

			let make width height =
				(width, height, Leaf [])

			let get_rect_nb width height (x, y) =
				let nb_x = if x <= width /. 2.0 then 0 else 1 in
				let nb_y = if y <= height /. 2.0 then 0 else 2 in
				nb_x + nb_y

			let rec fill_tree width height leaf tl tr bl br lst =
				let half_width, half_height = width /. 2.0, height /. 2.0 in
				let leaf_width, leaf_height = Leaftype.get_size leaf in
				let leaf_max_x, leaf_max_y = leaf.x +. leaf_width, leaf.y +. leaf_height in
				let tl_rect_nb = get_rect_nb width height (leaf.x, leaf.y) in
				let br_rect_nb = get_rect_nb width height (leaf_max_x, leaf_max_y) in
				if tl_rect_nb <> br_rect_nb then
					Node (tl, tr, bl, br, leaf :: lst)
				else (
					let sub_x = if tl_rect_nb mod 2 = 1 then half_width else 0.0 in
					let sub_y = if tl_rect_nb >= 2 then half_height else 0.0 in
					let leaf = {
						t = leaf.t ;
						x = leaf.x -. sub_x ;
						y = leaf.y -. sub_y
					} in
					match tl_rect_nb with
					| 0 -> (let tl = add2 half_width half_height tl leaf in
							Node (tl, tr, bl, br, lst))
					| 1 -> (let tr = add2 half_width half_height tr leaf in
							Node (tl, tr, bl, br, lst)
						)
					| 2 -> (
							let bl = add2 half_width half_height bl leaf in
							Node (tl, tr, bl, br, lst)
						)
					| 3 -> (
							let br = add2 half_width half_height br leaf in
							Node (tl, tr, bl, br, lst)
						)
				)

			and add2 width height node leaf =
				let leaf_width, leaf_height = Leaftype.get_size leaf in
				let leaf_max_x = leaf.x + leaf_width in
				let leaf_max_y = leaf.y + leaf_height in
				let _add node leaf x y width height =
					match node with
					| Node (tl, tr, bl, br, lst) -> (
						match 
					)
					| Leaf lst -> (
						if List.length lst >= 5 then

					)Leaf (leaf :: lst)
				in
				(width, height, _add node leaf 0.0 0.0 width height)

			let add (width, height, node) leaf =
				let leaf_x, leaf_y = Leaftype.get_coords leaf in
				let leaf = {
					t = leaf ;
					x = leaf_x ;
					y = leaf_y
				} in
				add2 width height node leaf

			let collision_pred tree leaf pred =
				true
		end

]