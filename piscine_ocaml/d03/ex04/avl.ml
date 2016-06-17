

type 'a tree = Nil | Node of 'a * 'a tree * 'a tree

let is_bst tree =
    let rec iz_bst tree maxi mini take_maxi take_mini =
        match tree with
        | Nil -> true
        | Node (v, Node (v2,_,_),_) when v2 >= v || (take_mini && v2 < mini) -> false
        | Node (v, _, Node (v2,_,_)) when v2 <= v || (take_maxi && v2 > maxi) -> false
        | Node (v, l, r) -> iz_bst l (v - 1) mini true take_mini && iz_bst r
        maxi (v + 1) take_maxi true
    in
    iz_bst tree 0 0 false false

let rec search_bst value = function
    | n when is_bst n = false -> failwith "Not a bst"
    | Nil -> false
    | Node (v, l, r) -> v = value || (value > v && search_bst value r) || (value
    < v && search_bst value l)

let rec height = function
    | Nil -> 0
    | Node (v, l, r) -> 1 + max (height l) (height r)

let rec is_balanced = function
    | Nil -> true
    | Node (v, l, r) -> is_balanced l && is_balanced r && abs (height l - height r) <= 1

let is_avl tree =
    is_bst tree && is_balanced tree

let rec add_avl value = function
    | Nil -> Node (value, Nil, Nil)
    | Node (v, l, r) when v = value -> failwith "Value already in the avl"
    | Node (v, l, r) -> if value < v then Node (v, add_avl value l, r) else Node
                        (v, l, add_avl value r)

let get_right = function
    | Nil -> Nil
    | Node (v, l, r) -> r

let get_left = function
    | Nil -> Nil
    | Node (v, l, r) -> l

let get_val = function
    | Nil -> 0
    | Node (v, l, r) -> v

let right_rotate z =
    let x = get_left z in
    let y = get_left x in
    let x_val = get_val x in
    let z_val = get_val z in
    let x_r = get_right x in
    let z_r = get_right z in
    Node (x_val, y, Node (z_val, x_r, z_r))

let left_rotate z =
    let y = get_right z in
    let x = get_right y in
    let y_val = get_val y in
    let z_val = get_val z in
    let z_l = get_left z in
    let y_l = get_left y in
    Node (y_val, Node (z_val, z_l, y_l), x)

let greatest_node node1 node2 =
	match node1 with
		| Nil -> node2
		| n -> match node2 with
				| Nil -> node1
				| n2 -> if get_val n2 > get_val n then n2
						else n

let left_or_right node value deletion =
    match node with
        | Nil -> Nil
		| Node (v, l, r) when deletion -> greatest_node l r
        | Node (v, l, r) -> if search_bst value l then l else r

let is_on_left node1 node2 =
    get_val node2 = (get_val (get_left node1))

let build_rebalanced_node z value deletion =
    let y = left_or_right z value deletion in
    let x = left_or_right y value deletion in
    if is_on_left z y && is_on_left y x then right_rotate z
    else if is_on_left z y && is_on_left y x = false then let new_tree
        = left_rotate y in let tmp_res = Node (get_val z, new_tree, get_right z) in right_rotate tmp_res
    else if is_on_left z y = false && is_on_left y x = false then left_rotate z
    else if is_on_left z y = false && is_on_left y x then let new_tree
        = right_rotate y in left_rotate (Node (get_val z, get_left z, new_tree))
    else failwith "Error"

let rec rebalance tree value deletion =
    match tree with
        | Nil -> Nil
        | Node (v, l, r) -> 
                if is_balanced l = false then Node (v, rebalance l value deletion, r)
                else if is_balanced r = false then Node (v, l, rebalance r value deletion)
                else
                    build_rebalanced_node tree value deletion

let insert_avl value = function
    | Nil -> Node (value, Nil, Nil)
    | n when is_avl n = false -> failwith "Not an avl"
    | n -> let new_tree = add_avl value n in
               if is_balanced new_tree then new_tree
               else rebalance new_tree value false

let mini_tree a b c =
    min (min a b) c

let rec min_val = function
    | Nil -> 0
    | Node (v, Nil, Nil) -> v
    | Node (v, l, Nil) -> let mini = min_val l in if mini < v then mini else v
    | Node (v, Nil, r) -> let mini = min_val r in if mini < v then mini else v
    | Node (v, l, r) -> let min1 = min_val l in let min2 = min_val r in
    mini_tree v min1 min2

let rec delete_bst value = function
    | n when is_bst n = false -> failwith "Not a bst"
    | Nil -> failwith "Value not in the bst"
    | Node (v, Nil, Nil) when v = value -> Nil
    | Node (v, l, Nil) when v = value -> l
    | Node (v, Nil, r) when v = value -> r
    | Node (v, l, r) when v = value -> let mini = min_val r in Node (mini, l,
    delete_bst mini r)
    | Node (v, l, r) -> if value < v then Node (v, delete_bst value l, r) else
        Node (v, l, delete_bst value r)

let delete_avl value = function
    | Nil -> failwith "Value not in avl"
    | n when is_avl n = false -> failwith "Not an avl"
    | n -> let new_tree = delete_bst value n in
            if is_balanced new_tree then new_tree
            else rebalance new_tree value true



let print_bool = function
    | true -> print_string "true"
    | _ -> print_string "false"

let print_testing tree n =
    print_int n ;
    print_string " ->                search_bst 42 : " ;
    print_bool (search_bst 42 tree) ;
    print_string " ; height : " ;
    print_int (height tree) ;
    print_string " ; left branch of root height : " ;
    print_int (height (get_left tree)) ;
    print_string " ; right branch of root height : " ;
    print_int (height (get_right tree)) ;
    print_string "\n  -- inserting 42 " ;
    let tree = insert_avl 42 tree in
    print_string " ; search_bst 42 : " ;
    print_bool (search_bst 42 tree) ;
    print_string " ; height : " ;
    print_int (height tree) ;
    print_string " ; left branch of root height : " ;
    print_int (height (get_left tree)) ;
    print_string " ; right branch of root height : " ;
    print_int (height (get_right tree)) ;
    print_string "\n  -- inserting 75 " ;
    let tree = insert_avl 75 tree in
    print_string " ; search_bst 75 : " ;
    print_bool (search_bst 75 tree) ;
    print_string " ; height : " ;
    print_int (height tree) ;
    print_string " ; left branch of root height : " ;
    print_int (height (get_left tree)) ;
    print_string " ; right branch of root height : " ;
    print_int (height (get_right tree)) ;
    print_string "\n  -- inserting 95 " ;
    let tree = insert_avl 95 tree in
    print_string " ; search_bst 95 : " ;
    print_bool (search_bst 95 tree) ;
    print_string " ; height : " ;
    print_int (height tree) ;
    print_string " ; left branch of root height : " ;
    print_int (height (get_left tree)) ;
    print_string " ; right branch of root height : " ;
    print_int (height (get_right tree)) ;
    print_string "\n  -- removing  42 " ;
    let tree = delete_avl 42 tree in
    print_string " ; search_bst 42 : " ;
    print_bool (search_bst 42 tree) ;
    print_string " ; height : " ;
    print_int (height tree) ;
    print_string " ; left branch of root height : " ;
    print_int (height (get_left tree)) ;
    print_string " ; right branch of root height : " ;
    print_int (height (get_right tree)) ;
    print_string "\n  -- removing  75 " ;
    let tree = delete_avl 75 tree in
    print_string " ; search_bst 75 : " ;
    print_bool (search_bst 75 tree) ;
    print_string " ; height : " ;
    print_int (height tree) ;
    print_string " ; left branch of root height : " ;
    print_int (height (get_left tree)) ;
    print_string " ; right branch of root height : " ;
    print_int (height (get_right tree)) ;
    print_string "\n  -- removing  95 " ;
    let tree = delete_avl 95 tree in
    print_string " ; search_bst 95 : " ;
    print_bool (search_bst 95 tree) ;
    print_string " ; height : " ;
    print_int (height tree) ;
    print_string " ; left branch of root height : " ;
    print_int (height (get_left tree)) ;
    print_string " ; right branch of root height : " ;
    print_int (height (get_right tree)) ;
    print_string "\n\n"

 
let () =
	Graphics.open_graph " 800x600" ;
    let tree1 = Node (10,
                    ( Node (5,
                        ( Node (3, Nil, Nil)),
                        ( Node (6, Nil, Nil)))
                    ),
                    ( Node (15,
                        ( Node (11, Nil, Nil)),
                        ( Node (16, Nil, Nil)))
                    )
                )
    in
    let tree2 = Nil in
    let tree3 = Node (10,
                    Nil,
                    Node (15, Nil, Nil)
                )
    in
    print_testing tree1 1 ;
    print_testing tree2 2 ;
    print_testing tree3 3
