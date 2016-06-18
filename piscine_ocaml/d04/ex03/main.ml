
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
	print_cols cols Deck.Card.Color.toString 0 ;
	print_char '\n' ;
	print_cols cols Deck.Card.Color.toStringVerbose 0 ;
	print_char '\n'

let color_test () =
	print_color_list (Deck.Card.Color.all)

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
	| card::cards -> (Deck.Card.Value.next card)::(get_nexts cards)

let rec get_previous = function
	| [] -> []
	| card::cards -> (Deck.Card.Value.previous card)::(get_previous cards)

let value_test () =
	let nexts = get_nexts (rm_last (Deck.Card.Value.all)) in
	let previous = get_previous (rm_first (Deck.Card.Value.all)) in
	print_string "all cards : " ;
	print_card_list (Deck.Card.Value.all) Deck.Card.Value.toString ;
	print_string "\nall cards verbose : " ;
	print_card_list (Deck.Card.Value.all) Deck.Card.Value.toStringVerbose ;
	print_string "\nall valid nexts : " ;
	print_card_list nexts Deck.Card.Value.toString ;
	print_string "\nall valid previous : " ;
	print_card_list previous Deck.Card.Value.toString ;
	print_char '\n'

let print_bool = function
    | true -> "true"
    | _ -> "false"

let card_test () =
    let color1 = Deck.Card.Color.Spade in
    let value1 = Deck.Card.Value.King in
    let card1 = Deck.Card.newCard value1 color1 in
    let color2 = Deck.Card.Color.Heart in
    let value2 = Deck.Card.Value.Queen in
    let card2 = Deck.Card.newCard value2 color2 in
    let color3 = Deck.Card.Color.Diamond in
    let value3 = Deck.Card.Value.King in
    let card3 = Deck.Card.newCard value3 color3 in
    print_string ("building card from color " ^ (Deck.Card.Color.toStringVerbose
    color1) ^ " and value " ^ (Deck.Card.Value.toStringVerbose value1) ^ " : " ^
    (Deck.Card.toStringVerbose card1)) ;
    print_char '\n' ;
    print_string "all spades : " ;
    print_card_list (Deck.Card.allSpades ) Deck.Card.toStringVerbose ;
    print_char '\n' ;
    print_string "all hearts : " ;
    print_card_list (Deck.Card.allHearts ) Deck.Card.toStringVerbose ;
    print_char '\n' ;
    print_string "all diamonds : " ;
    print_card_list (Deck.Card.allDiamonds ) Deck.Card.toStringVerbose ;
    print_char '\n' ;
    print_string "all clubs : " ;
    print_card_list (Deck.Card.allClubs ) Deck.Card.toStringVerbose ;
    print_char '\n' ;
    print_string "\nall cards : " ;
    print_card_list (Deck.Card.all ) Deck.Card.toString ;
    print_string ("\n\ngetValue of " ^ (Deck.Card.toString card1) ^ " : " ^
    (Deck.Card.Value.toStringVerbose (Deck.Card.getValue card1))) ;
    print_char '\n' ;
    print_string ("getColor of " ^ (Deck.Card.toString card1) ^ " : " ^
    (Deck.Card.Color.toStringVerbose (Deck.Card.getColor card1))) ;
    print_char '\n' ;
    print_string "\n-- comparision tests : \n" ;
    print_endline ("card1 : " ^ (Deck.Card.toStringVerbose card1) ^ " ; card2 : " ^
    (Deck.Card.toStringVerbose card2) ^ " ; card3 : " ^ (Deck.Card.toStringVerbose card3)) ;
    print_string "compare card1 card2 : " ;
    print_int (Deck.Card.compare card1 card2) ;
    print_char '\n' ;
    print_string "compare card2 card1 : " ;
    print_int (Deck.Card.compare card2 card1) ;
    print_char '\n' ;
    print_string "compare card1 card3 : " ;
    print_int (Deck.Card.compare card1 card3) ;
    print_char '\n' ;
    print_string "max card1 card2 : " ;
    print_endline (if Deck.Card.max card1 card2 = card1 then "card1" else "card2") ;
    print_string "max card2 card1 : " ;
    print_endline (if Deck.Card.max card2 card1 = card1 then "card1" else "card2") ;
    print_string "max card1 card3 : " ;
    print_endline (if Deck.Card.max card1 card3 = card1 then "card1" else "card3") ;
    print_string "max card3 card1 : " ;
    print_endline (if Deck.Card.max card3 card1 = card1 then "card1" else "card3") ;
    print_string "min card1 card2 : " ;
    print_endline (if Deck.Card.min card1 card2 = card1 then "card1" else "card2") ;
    print_string "min card2 card1 : " ;
    print_endline (if Deck.Card.min card2 card1 = card1 then "card1" else "card2") ;
    print_string "min card1 card3 : " ;
    print_endline (if Deck.Card.min card1 card3 = card1 then "card1" else "card3") ;
    print_string "min card3 card1 : " ;
    print_endline (if Deck.Card.min card3 card1 = card1 then "card1" else "card3") ;
    print_string "best of [card1;card2;card3] : " ;
    print_endline (let best = Deck.Card.best [card1;card2;card3] in if best = card1
    then "card1" else if best = card2 then "card2" else "card3") ;
    print_string "best of [card2;card3;card1] : " ;
    print_endline (let best = Deck.Card.best [card2;card3;card1] in if best = card1
    then "card1" else if best = card2 then "card2" else "card3") ;
    print_endline ("\ncard1 -> isOf Spade : " ^ (print_bool (Deck.Card.isOf
    card1 Deck.Card.Color.Spade)) ^ " ; isSpade : " ^ (print_bool
    (Deck.Card.isSpade card1)) ^ " ; isHeart : " ^ (print_bool (Deck.Card.isHeart card1)) ^ " ; isDiamond : " ^ (print_bool
    (Deck.Card.isDiamond card1)) ^ " ; isClub : " ^ (print_bool (Deck.Card.isClub card1)))
    ;
    print_endline ("card2 -> isOf Spade : " ^ (print_bool (Deck.Card.isOf
    card2 Deck.Card.Color.Spade)) ^ " ; isSpade : " ^ (print_bool
    (Deck.Card.isSpade card2)) ^ " ; isHeart : " ^ (print_bool (Deck.Card.isHeart card2)) ^ " ; isDiamond : " ^ (print_bool
    (Deck.Card.isDiamond card2)) ^ " ; isClub : " ^ (print_bool (Deck.Card.isClub card2)))
    ;
    print_endline ("card3 -> isOf Spade : " ^ (print_bool (Deck.Card.isOf
    card3 Deck.Card.Color.Spade)) ^ " ; isSpade : " ^ (print_bool
    (Deck.Card.isSpade card3)) ^ " ; isHeart : " ^ (print_bool (Deck.Card.isHeart card3)) ^ " ; isDiamond : " ^ (print_bool
    (Deck.Card.isDiamond card3)) ^ " ; isClub : " ^ (print_bool (Deck.Card.isClub card3)))

let print_deck deck func = 
    let rec print_d n = function
        | [] -> print_string ""
        | card::cards -> if n <> 0 then print_string ", " ; print_string card ; print_d (n + 1) cards
    in
    print_string "[" ;
    print_d 0 (func deck) ;
    print_string "]"

let draw_cards deck =
    print_string "\ndrawing cards from first deck until exception :\n" ;
    let rec drawz deck =
        let (x,xs) = Deck.drawCard deck in
        print_endline (Deck.Card.toStringVerbose x) ;
        drawz xs
    in
    drawz deck

let deck_test () =
    let deck1 = Deck.newDeck () in
    let deck2 = Deck.newDeck () in
    print_string "first  newDeck : " ;
    print_deck deck1 Deck.toStringList ;
    print_char '\n' ;
    print_string "second newDeck : " ;
    print_deck deck2 Deck.toStringList ;
    print_char '\n' ;
    print_string "first deck verbose : " ;
    print_deck deck1 Deck.toStringListVerbose ;
    print_char '\n' ;
    draw_cards deck1

let () =
    print_string "-- Deck.Card.Color test : \n" ;
    color_test () ;
    print_string "\n-- Deck.Card.Value test : \n" ;
    value_test () ;
    print_string "\n-- Deck.Card module test : \n" ;
    card_test () ;
    print_string "\n-- Deck module test : \n" ;
    deck_test () ;
