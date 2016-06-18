

module Value =
struct

	type t = T2 | T3 | T4 | T5 | T6 | T7 | T8 | T9 | T10 | Jack | Queen | King | As

	let all () =
		[T2;T3;T4;T5;T6;T7;T8;T9;T10;Jack;Queen;King;As]

	let toInt = function
		| T2 -> 1
		| T3 -> 2
		| T4 -> 3
		| T5 -> 4
		| T6 -> 5
		| T7 -> 6
		| T8 -> 7
		| T9 -> 8
		| T10 -> 9
		| Jack -> 10
		| Queen -> 11
		| King -> 12
		| As -> 13

	let toString = function
		| T2 -> "2"
		| T3 -> "3"
		| T4 -> "4"
		| T5 -> "5"
		| T6 -> "6"
		| T7 -> "7"
		| T8 -> "8"
		| T9 -> "9"
		| T10 -> "10"
		| Jack -> "J"
		| Queen -> "Q"
		| King -> "K"
		| As -> "A"

	let toStringVerbose = function
		| T2 -> "2"
		| T3 -> "3"
		| T4 -> "4"
		| T5 -> "5"
		| T6 -> "6"
		| T7 -> "7"
		| T8 -> "8"
		| T9 -> "9"
		| T10 -> "10"
		| Jack -> "Jack"
		| Queen -> "Queen"
		| King -> "King"
		| As -> "As"

end

module Color =
struct

	type t = Spade | Heart | Diamond | Club

	let all () =
		[Spade; Heart; Diamond; Club]

	let toString = function
		| Spade -> "S"
		| Heart -> "H"
		| Diamond -> "D"
		| Club -> "C"

	let toStringVerbose = function
		| Spade -> "Spade"
		| Heart -> "Heart"
		| Diamond -> "Diamond"
		| Club -> "Club"

end

type t = {color:Color.t; value:Value.t}

let newCard value col =
	{color = col;
	 value = value}

let rec newCardList values color =
	match values with
		| [] -> []
		| value::values -> (newCard value color)::(newCardList values color)

let allSpades () =
	newCardList ( Value.all () ) Color.Spade

let allHearts () =
	newCardList ( Value.all () ) Color.Heart

let allDiamonds () =
	newCardList ( Value.all () ) Color.Diamond

let allClubs () =
	newCardList ( Value.all () ) Color.Club

let all () =
	let rec get_all = function
		| [] -> []
		| value::values -> (newCard value Color.Spade)::(newCard value Color.Heart)::(newCard value Color.Diamond)::(newCard value Color.Club)::(get_all values)
	in
	get_all (Value.all () )

let getValue card =
	card.value

let getColor card =
	card.color

let toString = function
	| {color = col; value = valu} -> ( Value.toString valu ) ^ ( Color.toString col )

let toStringVerbose = function
	| {color = col; value = valu} -> "Card(" ^ (Value.toStringVerbose valu ) ^ ", " ^ ( Color.toStringVerbose col ) ^ ")"

let compare_values val1 val2 =
	let index lis value =
		let rec ind lis value n =
			match lis with
				| [] -> (-1)
				| x::xs when x = value -> n
				| x::xs -> ind xs value (n + 1)
		in
		ind lis value 0
	in
	let ind1 = index (Value.all ()) val1 in
	let ind2 = index (Value.all ()) val2 in
	ind1 - ind2

let compare {color = col1; value = val1} {color = col2; value = val2} =
	compare_values val1 val2

let max card1 card2 =
	if compare card1 card2 < 0 then card2
	else card1

let min card1 card2 =
	if compare card1 card2 > 0 then card2
	else card1

let best cards =
	match cards with
		| [] -> invalid_arg "Empty card list"
		| cards ->
			let rec best_cards cards current_best n =
				match cards with
				| [] -> current_best
				| card::cards ->
					let new_best = if n = 0 then card else max card current_best in
					best_cards cards new_best (n + 1)
			in
			best_cards cards {color=Color.Spade;value=Value.T2} 0

let isOf card col =
	match card with
		| {color = card_col;_} -> col = card_col

let isSpade card =
	isOf card Color.Spade

let isHeart card =
	isOf card Color.Heart

let isDiamond card =
	isOf card Color.Diamond

let isClub card =
	isOf card Color.Club
