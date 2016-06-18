
let print_color_list cols =
	let rec print_cols cols func n =
		if n = 0 then print_string "[" ;
		match cols with
			| [] -> print_string "]"
			| col::cols ->
				if n <> 0 then print_string ", " ;
				print_string (func col) ;
				print_cols cols func (n + 1)
	in
	print_cols cols Card.Color.toString 0 ;
	print_char '\n' ;
	print_cols cols Card.Color.toStringVerbose 0 ;
	print_char '\n'

let color_test () =
	print_color_list (Card.Color.all)

let print_card_list cards func =
	let rec print_cards cards func n =
		if n = 0 then print_string "[" ;
		match cards with
			| [] -> print_string "]"
			| card::cards ->
				if n <> 0 then print_string ", " ;
				print_string (func card) ;
				print_cards cards func (n + 1)
	in
	print_cards cards func 0

let rm_first = function
	| [] -> []
	| x::xs -> xs

let rec rm_last = function
	| [] -> []
	| x::xs when xs = [] -> []
	| x::xs -> x::(rm_last xs)

let rec get_nexts = function
	| [] -> []
	| card::cards -> (Card.Value.next card)::(get_nexts cards)

let rec get_previous = function
	| [] -> []
	| card::cards -> (Card.Value.previous card)::(get_previous cards)

let value_test () =
	let nexts = get_nexts (rm_last (Card.Value.all)) in
	let previous = get_previous (rm_first (Card.Value.all)) in
	print_string "all cards : " ;
	print_card_list (Card.Value.all) Card.Value.toString ;
	print_string "\nall cards verbose : " ;
	print_card_list (Card.Value.all) Card.Value.toStringVerbose ;
	print_string "\nall valid nexts : " ;
	print_card_list nexts Card.Value.toString ;
	print_string "\nall valid previous : " ;
	print_card_list previous Card.Value.toString ;
	print_char '\n'

let print_bool = function
    | true -> "true"
    | _ -> "false"

let card_test () =
    let color1 = Card.Color.Spade in
    let value1 = Card.Value.King in
    let card1 = Card.newCard value1 color1 in
    let color2 = Card.Color.Heart in
    let value2 = Card.Value.Queen in
    let card2 = Card.newCard value2 color2 in
    let color3 = Card.Color.Diamond in
    let value3 = Card.Value.King in
    let card3 = Card.newCard value3 color3 in
    print_string ("building card from color " ^ (Card.Color.toStringVerbose
    color1) ^ " and value " ^ (Card.Value.toStringVerbose value1) ^ " : " ^
    (Card.toStringVerbose card1)) ;
    print_char '\n' ;
    print_string "all spades : " ;
    print_card_list (Card.allSpades ) Card.toStringVerbose ;
    print_char '\n' ;
    print_string "all hearts : " ;
    print_card_list (Card.allHearts ) Card.toStringVerbose ;
    print_char '\n' ;
    print_string "all diamonds : " ;
    print_card_list (Card.allDiamonds ) Card.toStringVerbose ;
    print_char '\n' ;
    print_string "all clubs : " ;
    print_card_list (Card.allClubs ) Card.toStringVerbose ;
    print_char '\n' ;
    print_string "\nall cards : " ;
    print_card_list (Card.all ) Card.toString ;
    print_string ("\n\ngetValue of " ^ (Card.toString card1) ^ " : " ^
    (Card.Value.toStringVerbose (Card.getValue card1))) ;
    print_char '\n' ;
    print_string ("getColor of " ^ (Card.toString card1) ^ " : " ^
    (Card.Color.toStringVerbose (Card.getColor card1))) ;
    print_char '\n' ;
    print_string "\n-- comparision tests : \n" ;
    print_endline ("card1 : " ^ (Card.toStringVerbose card1) ^ " ; card2 : " ^
    (Card.toStringVerbose card2) ^ " ; card3 : " ^ (Card.toStringVerbose card3)) ;
    print_string "compare card1 card2 : " ;
    print_int (Card.compare card1 card2) ;
    print_char '\n' ;
    print_string "compare card2 card1 : " ;
    print_int (Card.compare card2 card1) ;
    print_char '\n' ;
    print_string "compare card1 card3 : " ;
    print_int (Card.compare card1 card3) ;
    print_char '\n' ;
    print_string "max card1 card2 : " ;
    print_endline (if Card.max card1 card2 = card1 then "card1" else "card2") ;
    print_string "max card2 card1 : " ;
    print_endline (if Card.max card2 card1 = card1 then "card1" else "card2") ;
    print_string "max card1 card3 : " ;
    print_endline (if Card.max card1 card3 = card1 then "card1" else "card3") ;
    print_string "max card3 card1 : " ;
    print_endline (if Card.max card3 card1 = card1 then "card1" else "card3") ;
    print_string "min card1 card2 : " ;
    print_endline (if Card.min card1 card2 = card1 then "card1" else "card2") ;
    print_string "min card2 card1 : " ;
    print_endline (if Card.min card2 card1 = card1 then "card1" else "card2") ;
    print_string "min card1 card3 : " ;
    print_endline (if Card.min card1 card3 = card1 then "card1" else "card3") ;
    print_string "min card3 card1 : " ;
    print_endline (if Card.min card3 card1 = card1 then "card1" else "card3") ;
    print_string "best of [card1;card2;card3] : " ;
    print_endline (let best = Card.best [card1;card2;card3] in if best = card1
    then "card1" else if best = card2 then "card2" else "card3") ;
    print_string "best of [card2;card3;card1] : " ;
    print_endline (let best = Card.best [card2;card3;card1] in if best = card1
    then "card1" else if best = card2 then "card2" else "card3") ;
    print_endline ("\ncard1 -> isOf Spade : " ^ (print_bool (Card.isOf
    card1 Card.Color.Spade)) ^ " ; isSpade : " ^ (print_bool (Card.isSpade card1)) ^ " ; isHeart : " ^ (print_bool (Card.isHeart card1)) ^ " ; isDiamond : " ^ (print_bool
    (Card.isDiamond card1)) ^ " ; isClub : " ^ (print_bool (Card.isClub card1)))
    ;
    print_endline ("card2 -> isOf Spade : " ^ (print_bool (Card.isOf
    card2 Card.Color.Spade)) ^ " ; isSpade : " ^ (print_bool (Card.isSpade card2)) ^ " ; isHeart : " ^ (print_bool (Card.isHeart card2)) ^ " ; isDiamond : " ^ (print_bool
    (Card.isDiamond card2)) ^ " ; isClub : " ^ (print_bool (Card.isClub card2)))
    ;
    print_endline ("card3 -> isOf Spade : " ^ (print_bool (Card.isOf
    card3 Card.Color.Spade)) ^ " ; isSpade : " ^ (print_bool (Card.isSpade card3)) ^ " ; isHeart : " ^ (print_bool (Card.isHeart card3)) ^ " ; isDiamond : " ^ (print_bool
    (Card.isDiamond card3)) ^ " ; isClub : " ^ (print_bool (Card.isClub card3)))

let () =
    print_string "-- Card.Color test : \n" ;
    color_test () ;
    print_string "\n-- Card.Value test : \n" ;
    value_test () ;
    print_string "\n-- Card module test : \n" ;
    card_test ()
