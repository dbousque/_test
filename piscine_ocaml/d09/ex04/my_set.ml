

module Set =
struct

    type 'a t = Set of 'a list

    let return a = Set [a]

    let bind a func =
	    match a with
	    | Set lst ->
		    let rec _bind lst func =
			    match lst with
			    | [] -> []
			    | h::tl -> ((func h)::(_bind tl func))
		    in
		    Set (_bind lst func)

    let rec is_in_set vl set =
	    match set with
	    | [] -> false
	    | h::tl -> if h = vl then true else is_in_set vl tl

    let union set1 set2 =
	    let rec _union set1 set2 =
		    match set2 with
		    | [] -> set1
		    | h::tl ->	if is_in_set h set1
					    then _union set1 tl
					    else _union (h::set1) tl
	    in
	    match set1 with
	    | Set s1 -> begin
					    match set2 with
					    | Set s2 -> Set (_union s1 s2)
				    end

    let inter set1 set2 =
	    let rec _inter set1 set2 =
		    match set2 with
		    | [] -> []
		    | h::tl ->	if is_in_set h set1
					    then (h::(_inter set1 tl))
					    else _inter set1 tl
	    in
	    match set1 with
	    | Set s1 -> begin
					    match set2 with
					    | Set s2 -> Set (_inter s1 s2)
				    end

    let diff set1 set2 =
	    let rec _diff set1 set2 =
		    match set1 with
		    | [] -> []
		    | h::tl ->	if is_in_set h set2
					    then _diff tl set2
					    else (h::(_diff tl set2))
	    in
	    match set1 with
	    | Set s1 -> begin
					    match set2 with
					    | Set s2 -> Set (_diff s1 s2)
				    end

    let filter set cond =
	    let rec _filter set cond =
		    match set with
		    | [] -> []
		    | h::tl ->	if cond h
					    then (h::(_filter tl cond))
					    else _filter tl cond
	    in
	    match set with
	    | Set s -> Set (_filter s cond)

    let foreach set (func:'a -> unit) =
	    let rec exec set func =
		    match set with
		    | [] -> ignore ()
		    | h::tl -> (func h) ; exec tl func
	    in
	    match set with
	    | Set s -> exec s func

    let for_all set cond =
	    let rec _for_all set cond =
		    match set with
		    | [] -> true
		    | h::tl -> if cond h then _for_all tl cond else false
	    in
	    match set with
	    | Set s -> _for_all s cond

    let exists set cond =
	    let rec _exists set cond =
	    	match set with
		    | [] -> false
		    | h::tl -> if cond h then true else _exists tl cond
	    in
	    match set with
	    | Set s -> _exists s cond

end
