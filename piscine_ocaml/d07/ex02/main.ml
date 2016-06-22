

let () =
    let dalek = new Dalek.dalek in
	let human = new People.people "human" in
	let doctor = new Doctor.doctor "Who" 87 human in
	let doctor = doctor#travel_in_time 2016 1964 in
	print_endline "Introducing contestants : " ;
	print_endline human#to_string ;
	print_endline doctor#to_string ;
	print_endline dalek#to_string ;
	dalek#talk ;
	human#talk ;
	doctor#talk ;
	dalek#talk ;
	dalek#talk ;
	doctor#use_sonic_screwdriver ;
	dalek#talk ;
	dalek#exterminate human ;
	print_endline "\nRemaining contestants : " ;
	print_endline doctor#to_string ;
	print_endline dalek#to_string ;
	dalek#talk ;
	doctor#use_sonic_screwdriver ;
	dalek#die
