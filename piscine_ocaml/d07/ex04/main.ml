

let () =
	let dalek_army = new Army.army in
	let doctor_army = new Army.army in
	let people_army = new Army.army in

	print_endline "--People's army" ;
	print_endline "Adding two people to the people's army" ;
	let people_army = people_army#add (new People.people "dodo") in
	let people_army = people_army#add (new People.people "human") in
	people_army#print ;
	print_endline "Calling remove on the people's army" ;
	let people_army = people_army#delete in
	people_army#print ;
	print_endline "Removing second people" ;
	let people_army = people_army#delete in
	people_army#print ;

	print_endline "\n-- Doctors' army" ;
	print_endline "Adding two doctors to the doctors' army" ;
	let doctor_army = doctor_army#add (new Doctor.doctor "Who" 58 (new People.people "pet1")) in
	let doctor_army = doctor_army#add (new Doctor.doctor "Bean" 36 (new People.people "pet2")) in
	doctor_army#print ;
	print_endline "Calling remove on the doctors' army" ;
	let doctor_army = doctor_army#delete in
	doctor_army#print ;
	print_endline "Removing second doctor" ;
	let doctor_army = doctor_army#delete in
	doctor_army#print ;

	print_endline "\n-- Daleks' army" ;
	print_endline "Adding two daleks to the daleks' army" ;
	let dalek_army = dalek_army#add (new Dalek.dalek) in
	let dalek_army = dalek_army#add (new Dalek.dalek) in
	dalek_army#print ;
	print_endline "Calling remove on the daleks' army" ;
	let dalek_army = dalek_army#delete in
	dalek_army#print ;
	print_endline "Removing second dalek" ;
	let dalek_army = dalek_army#delete in
	dalek_army#print
