

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

let rec height = function
    | Nil -> 0
    | Node (v, l, r) -> 1 + max (height l) (height r)

let rec is_perfect = function
    | n when is_bst n = false -> false
    | Nil -> true
    | Node (v, Nil, Nil) -> true
    | Node (v, Node (a,b,c), Node (x,y,z)) -> is_perfect (Node (a,b,c)) &&
                is_perfect (Node (x,y,z)) && height (Node (a,b,c)) = height (Node (x,y,z))
    | _ -> false

let rec is_balanced = function
    | Nil -> true
    | Node (v, l, r) -> is_balanced l && is_balanced r && abs (height l - height r) <= 1

let rec search_bst value = function
    | n when is_bst n = false -> failwith "Not a bst"
    | Nil -> false
    | Node (v, l, r) -> v = value || (value > v && search_bst value r) || (value
    < v && search_bst value l)

let rec add_bst value = function
    | n when is_bst n = false -> failwith "Not a bst"
    | Nil -> Node (value, Nil, Nil)
    | Node (v, l, r) when v = value -> failwith "Value already in the bst"
    | Node (v, l, r) -> if value < v then Node (v, add_bst value l, r) else Node
                        (v, l, add_bst value r)

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




let print_bool = function
    | true -> print_string "true"
    | _ -> print_string "false"

let print_testing tree n =
    print_int n ;
    print_string " -> is_bst : " ;
    print_bool (is_bst tree) ;
    print_string ", is_perfect : " ;
    print_bool (is_perfect tree) ;
    print_string ", is_balanced : " ;
    print_bool (is_balanced tree) ;
    if is_bst tree then (
        print_string ", search_bst 10 : " ;
        print_bool (search_bst 10 tree) 
    ) ;
    print_char '\n'

let print_insert tree n =
    if is_bst tree then
        begin
            print_int n ;
            print_string " -> height : " ;
            print_int (height tree) ;
            print_string " ; search_bst 42 : " ;
            print_bool (search_bst 42 tree) ;
            print_string " ; inserting 42 ; search_bst 42 : " ;
            let new_tree = add_bst 42 tree in
            print_bool (search_bst 42 new_tree) ;
            print_string " ; height : " ;
            print_int (height new_tree) ;
            print_char '\n'
        end
let print_remove tree n =
    if is_bst tree && search_bst 10 tree then
        begin
            print_int n ;
            print_string " -> height : " ;
            print_int (height tree) ;
            print_string " ; search_bst 10 : " ;
            print_bool (search_bst 10 tree) ;
            print_string " ; removing 10 ; search_bst 10 : " ;
            let new_tree = delete_bst 10 tree in
            print_bool (search_bst 10 new_tree) ;
            print_string " ; height : " ;
            print_int (height new_tree) ;
            print_char '\n'
        end

let () =
    let tree1 =
		Node (10, 
			( Node (4,
				( Node (2, Nil, Nil) ),
				( Node (6,
				  	( Node (5, Nil, Nil) ),
					Nil
				))
			)),
			( Node (17,
			  	Nil,
			  	( Node (22, Nil, Nil) )
			))
		)
	in
    let tree2 = Nil in
    let tree3 = Node (10, Nil, Nil) in
    let tree4 = Node (10, Node (5, Nil, Nil), Nil) in
    let tree5 = Node (10, Node (15, Nil, Nil), Nil) in
    let tree6 =
		Node (10, 
			( Node (4,
				( Node (2, Nil, Nil) ),
				( Node (6,
				  	( Node (1, Nil, Nil) ),
					Nil
				))
			)),
			( Node (17,
			  	Nil,
			  	( Node (22, Nil, Nil) )
			))
		)
	in
    let tree7 = Node (10,
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
    let tree8 = Node (10,
                    ( Node (9,
                        (Node (10, Nil, Nil)),
                        Nil)
                    ),
                    Nil
                )
    in
    print_testing tree1 1 ;
    print_testing tree2 2 ;
    print_testing tree3 3 ;
    print_testing tree4 4 ;
    print_testing tree5 5 ;
    print_testing tree6 6 ;
    print_testing tree7 7 ;
    print_testing tree8 8 ;
    print_string "\n-- insert tests : \n" ;
    print_insert tree1 1 ;
    print_insert tree2 2 ;
    print_insert tree3 3 ;
    print_insert tree4 4 ;
    print_insert tree5 5 ;
    print_insert tree6 6 ;
    print_insert tree7 7 ;
    print_insert tree8 8 ;
    print_string "\n-- remove tests : \n" ;
    print_remove tree1 1 ;
    print_remove tree2 2 ;
    print_remove tree3 3 ;
    print_remove tree4 4 ;
    print_remove tree5 5 ;
    print_remove tree6 6 ;
    print_remove tree7 7 ;
    print_remove tree8 8
