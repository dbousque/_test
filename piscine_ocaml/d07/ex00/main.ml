

let () =
	let obj1 = new People.people "Casimir" in
	let obj2 = new People.people "Hippolyte" in
	print_endline obj1#to_string ;
	print_endline obj2#to_string ;
	obj1#talk ;
	obj2#talk ;
	obj1#die ;
	obj2#die
