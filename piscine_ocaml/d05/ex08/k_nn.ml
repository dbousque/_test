

type radar = (float array * string)


type categ = String of string | NullPoint
type point = {coords: float array; category: categ}
type counter = {label: string; mutable count: int}

(* ------------------------------------ *)
(* EXAMPLE OF FILE IMPLEMENTATION BELOW *)

let add_to_array arr elt =
    let newArr = Array.make ((Array.length arr) + 1) elt in
    for i = 0 to (Array.length arr) - 1 do
        newArr.(i) <- arr.(i)
    done ;
    newArr

let reverse_list arr =
    let rec rev_list acc = function
        | [] -> acc
        | h::tl -> rev_list (h::acc) tl
    in
    rev_list [] arr

let list_to_array l =
    let rec lta acc = function
        | [] -> acc
        | h::tl -> lta (add_to_array acc h) tl
    in
    lta (Array.make 0 (List.hd l)) l

let reverse_string str =
    let res_str = ref "" in
    for i = 0 to (String.length str) - 1 do
        res_str := (String.make 1 (String.get str i)) ^ !res_str
    done ;
    !res_str

let split_string str car =
    let rec split str car ind acc =
        if ind >= String.length str then acc
        else
            let current_car = String.get str ind in
            let car_as_str = String.make 1 current_car in
            if current_car = car
            then split str car (ind + 1) (""::acc)
            else split str car (ind + 1) ((car_as_str ^ (List.hd acc))::(List.tl acc))
    in list_to_array (split (reverse_string str) car 0 [""])

let convert_radar_line arr =
    let res_floats = ref (Array.make 0 0.0) in
    for i = 0 to (Array.length arr) - 2 do
        try
            res_floats := add_to_array !res_floats (float_of_string arr.(i))
        with | _ -> ignore ()
    done ;
    (!res_floats, arr.((Array.length arr) - 1))

let convert_to_radar csv_lines =
    let res_radars = ref [] in
    for i = (Array.length csv_lines) - 1 downto 0 do
        res_radars := (convert_radar_line (Array.get csv_lines i))::(!res_radars)
    done ;
    !res_radars

let interpret_as_csv lines =
    let res_lines = ref (Array.make 0 (Array.make 0 "salut")) in
    for i = 0 to (Array.length lines) - 1 do
        res_lines := (add_to_array !res_lines (split_string (lines.(i)) ','))
    done ;
    !res_lines

let read_lines filename =
    try
        begin
            let tmp_line = ref "salut" in
            let res_lines = ref (Array.make 0 "salut") in
            let ic = open_in filename in
            while (
                try
                    begin
                        tmp_line := input_line ic ;
                        true
                    end
                with
                | _ -> close_in ic ; false
            ) do
                res_lines := add_to_array !res_lines !tmp_line
            done ;
            !res_lines
        end
    with
    | _ -> Array.make 0 "salut"

let print_float_array a =
    print_string "[|" ;
    for i = 0 to (Array.length a) - 1 do
        if i <> 0 then print_string ", " ;
        print_float a.(i) ;
    done ;
    print_string "|]"

let print_string_array a =
    print_string "[|" ;
    for i = 0 to (Array.length a) - 1 do
        if i <> 0 then print_string ", " ;
        print_char '"' ;
        print_string a.(i) ;
        print_char '"'
    done ;
    print_string "|]"

let read_csv filename =
    let lines = read_lines filename in
    let csv_lines = interpret_as_csv lines in
    csv_lines

let print_radar_line line =
    match line with
    | (floats, str) ->
                print_char '(' ;
                print_float_array floats ;
                print_string ", \"" ;
                print_string str ;
                print_string "\")"

let rec list_get lis ind =
    match lis with
    | [] -> failwith "Out of bounds"
    | h::tl -> if ind = 0 then h else list_get tl (ind - 1)

let examples_of_file filename =
    let csv_lines = read_csv filename in
    let radar_lines = convert_to_radar csv_lines in
    radar_lines
    
let print_radars radar_lines =
    for i = 0 to (List.length radar_lines) - 1 do
        print_int (i + 1) ;
        print_string " -> " ;
        print_radar_line (list_get radar_lines i) ;
        print_char '\n'
    done


(* ------------------------------------- *)
(* END OF EXEMPLE OF FILE IMPLEMENTATION *)


let power a b =
    let total = ref 1.0 in
    for i = b downto 1 do
        total := (!total *. a)
    done ;
    !total

let eu_dist a b =
    let total = ref 0.0 in
    for i = 0 to ((Array.length a) - 1) do
        total := !total +. (power ((Array.get a i) -. (Array.get b i)) 2)
    done ;
    sqrt (!total)

let points_distance a b =
	eu_dist a.coords b.coords

let radar_to_point (points, cat) =
	{coords = points ; category = String cat}

let radars_to_points radars =
	let rec rad_to_p = function
		| [] -> []
		| h::tl -> ((radar_to_point h)::(rad_to_p tl))
	in
	rad_to_p radars

let is_null_point = function
	| {coords = _; category = NullPoint} -> true
	| _ -> false

let print_bool = function
	| true -> print_string "true"
	| _ -> print_string "false"

let closer_point point p1 p2 =
	match p2 with
		| p when is_null_point p -> true
		| p2 -> begin
					match p1 with
					| p when is_null_point p -> false
					| p1 -> points_distance point p1 <= points_distance point p2
				end

let insert_point_to_closests p point closests k =
	let ind = ref (k - 1) in
	while !ind >= 0 && closer_point point p closests.(!ind) do
		if !ind <> k - 1 then closests.(!ind + 1) <- closests.(!ind) ;
		closests.(!ind) <- p ;
		ind := !ind - 1 ;
	done

let find_k_closests points point closests k =
	let rec find_clos points point closests k =
		match points with
		| [] -> ignore ()
		| (h::tl) ->
			begin 
				insert_point_to_closests h point closests k ;
				find_clos tl point closests k 
			end
	in
	find_clos points point closests k

let getCateg = function
	| NullPoint -> "Error"
	| String str -> str

let most_frequent_category closests k =
	let rec update_labels closests ind labels =
		let categ = getCateg closests.(ind).category in
		match labels with
		| [] -> [{label = categ ; count = 1}]
		| h::tl when categ = h.label ->
					begin
						h.count <- h.count + 1 ;
						(h::tl)
					end
		| h::tl -> (h::(update_labels closests ind tl))
	in
	let label_cmp lab1 lab2 =
        if lab1.count = lab2.count then (
            if Random.int 2 = 0 then 1 else -1 )
        else compare lab2.count lab1.count
	in
	let rec most_freq closests ind k labels =
		if ind >= k then 
			begin
				let sorted_lab = List.sort label_cmp labels in
				match sorted_lab with
				| h::tl -> h.label
				| _ -> "Error"
			end
		else
			let labels = update_labels closests ind labels in
			most_freq closests (ind + 1) k labels
	in
	most_freq closests 0 k []		

let print_point point ori_point =
    print_string "  Point (categ : \"" ;
    print_string (
        match point.category with
        | String str -> str
        | _ -> "" ) ;
    print_string "\" ; distance : " ;
    print_float (points_distance point ori_point) ;
    print_string ")"

let print_closests closests k ori_point =
    print_endline "Closests points :" ;
    for i = 0 to k - 1 do
        print_point closests.(i) ori_point ;
        print_char '\n'
    done

let k_nn radars radar k print =
	if k <= 0 then ignore () ;
	let null_point = {coords = Array.make 0 0.; category = NullPoint} in
	let points = radars_to_points radars in
	let point = radar_to_point radar in
	let closests = Array.make k null_point in
    find_k_closests points point closests k ;
    if print then
        begin
            print_string (  match point.category with
                    | String str -> "Category of point : \"" ^ str ^ "\"\n"
                    | _ -> "Error\n" ) ;
            print_closests closests k point
        end ;
	let best_cat = most_frequent_category closests k in
    best_cat

let rec remove_n elts n =
    match elts with
    | [] -> []
    | h::tl when n = 0 -> tl
    | h::tl -> remove_n tl (n - 1)

let rec take_n elts n =
    match elts with
    | h::tl when n = 0 -> h
    | h::tl -> take_n tl (n - 1)
    | [] -> failwith "out of bounds"

let print_testing filename n k =
    print_string "\nLaunching test with file \"" ;
    print_string filename ;
    print_string "\", point number " ;
    print_int n ;
    print_string " and k=" ;
    print_int k ;
    print_endline " : \n-----------------------------------------------" ;
    let raw_radars = examples_of_file filename in
	let radars = remove_n raw_radars n in
	let radar = take_n raw_radars n in
    let best_cat = k_nn radars radar k true in
    print_string " -> Found category : \"" ;
    print_string best_cat ;
    print_endline "\""

let get_radar_category = function
    | (arr, str) -> str

let test_error_rate filename k =
    print_string "\nTesting error rate with k=" ;
    print_int k ;
    print_endline " : " ;
    let right = ref 0 in
    let wrong = ref 0 in
    let raw_radars = examples_of_file filename in
    for i = 0 to (List.length raw_radars) - 1 do
        let tmp_rads = remove_n raw_radars i in
        let rad = take_n raw_radars i in
        let rad_cat = get_radar_category rad in
        let cat = k_nn tmp_rads rad k false in
        if rad_cat = cat then right := !right + 1 else wrong := !wrong + 1 ;
    done ;
    print_int (List.length raw_radars) ;
    print_string " tests performed : " ;
    print_int !right ;
    print_string " (" ;
    print_int ((!right * 100) / List.length raw_radars) ;
    print_string "%) right, " ;
    print_int !wrong ;
    print_string " (" ;
    print_int ((!wrong * 100) / List.length raw_radars) ;
    print_endline "%) wrong."

let () =
	let filename1 = "ionosphere.train.csv" in
    let filename2 = "ionosphere.test.csv" in
    print_testing filename1 0 5 ;
    print_testing filename1 3 20 ;
    print_testing filename2 5 3 ;
    test_error_rate filename1 1 ;
    test_error_rate filename1 2 ;
    test_error_rate filename1 5 ;
    test_error_rate filename1 8 ;
    test_error_rate filename1 13 ;
    test_error_rate filename1 20 ;
