

let get_string_try = function
	| Try.Success a -> a ^ ""
	| _ -> ""

let print_failures = function
	| Try.Failure e -> print_string "Failure : \"" ; print_string (Printexc.to_string e) ; print_endline "\""
	| _ -> ignore ()

let print_try_int = function
	| Try.Success a ->  begin
							print_string "Success " ;
							print_int a ;
							print_char '\n'
						end
	| Try.Failure e -> print_failures (Try.Failure e)

let print_try_float = function
	| Try.Success a ->  begin
							print_string "Success " ;
							print_float a ;
							print_char '\n'
						end
	| Try.Failure e -> print_failures (Try.Failure e)

let print_try_string = function
	| Try.Success a ->  begin
							print_string "Success \"" ;
							print_string a ;
							print_endline "\""
						end
	| Try.Failure e -> print_failures (Try.Failure e)

let () =
	let a = Try.return "super" in
	let b = Try.return 21 in
	let c = Try.return 42.42 in
	let d = Try.Failure (Failure "failz") in
	let e = Try.return d in
	let f = Try.return (Try.Success 42) in
	let func1 = fun x -> Try.Success (x * 2) in
	let func2 = fun x -> Try.Success (x / 0) in
	let func3 = fun x -> Try.Success (x ^ "cool") in
	let func4 = fun x -> Try.Success "lolz" in
	let binded1 = Try.bind b func1 in
	let binded2 = Try.bind b func2 in
	let binded3 = Try.bind d func1 in
	let binded4 = Try.bind a func3 in
	let binded5 = Try.bind b func4 in
	let recov = fun e -> Try.Success 42 in
	print_endline "a = Success \"super\"" ;
	print_endline "b = Success 21" ;
	print_endline "c = Success 42.42" ;
	print_endline "d = Failure (Failure \"failz\")" ;
	print_endline "e = Success (Failure (Failure \"failz\"))" ;
	print_endline "f = Success (Success 42)" ;
	print_string "call bind a (fun x -> Success (x ^ \"cool\")) : " ;
	print_try_string binded4 ;
	print_string "call bind b (fun x -> Success (x * 2)) : " ;
	print_try_int binded1 ;
	print_string "call bind b (fun x -> Success (x / 0)) : " ;
	print_try_int binded2 ;
	print_string "call bind d (fun x -> Success (x * 2)) : " ;
	print_try_int binded3 ;
	print_string "call bind b (fun x -> Success \"lolz\") : " ;
	print_try_string binded5 ;
	print_string "call recover d (fun x -> Success 42) : " ;
	print_try_int (Try.recover d recov) ;
	print_string "call recover b (fun x -> Success 42) : " ;
	print_try_int (Try.recover b recov) ;
	print_string "call filter d (fun x -> false)) : " ;
	print_try_int (Try.filter d (fun x -> false)) ;
	print_string "call filter d (fun x -> true)) : " ;
	print_try_int (Try.filter d (fun x -> true)) ;
	print_string "call filter c (fun x -> false)) : " ;
	print_try_float (Try.filter c (fun x -> false)) ;
	print_string "call filter c (fun x -> true)) : " ;
	print_try_float (Try.filter c (fun x -> true)) ;
	print_string "call flatten f : " ;
	print_try_int (Try.flatten f) ;
	print_string "call flatten e : " ;
	print_try_int (Try.flatten e)
