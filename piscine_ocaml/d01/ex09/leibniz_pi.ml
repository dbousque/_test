

let leibniz_pi delta =
	let real_pi = 4.0 *. (atan 1.0) in
	let delta_reached delta acc = (real_pi -. acc >= 0.0 && real_pi -. acc <= delta) || (acc -. real_pi >= 0.0 && acc -. real_pi <= delta) in
	let incr_acc acc i pos =
		let to_add = (1.0 /. (2.0 *. (float_of_int i) +. 1.0)) in
		if pos then acc +. to_add
		else acc -. to_add
	in
	let rec leib delta i acc pos =
		if i <> 0 && delta_reached delta (4.0 *. acc) then i
		else leib delta (i + 1) (incr_acc acc i pos) (not pos)
	in
	leib delta 0 0.0 true

let () =
	print_int (leibniz_pi 0.0000001) ;
	print_char '\n'
