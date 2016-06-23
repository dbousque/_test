

class galifrey =
	object (self)
		val _daleks : Dalek.dalek list = []
		val _doctors : Doctor.doctor list = []
		val _people : People.people list = []

        method add_dalek sold =
            let rec push_back elt = function
				| [] -> [elt]
				| h::tl -> h::(push_back elt tl)
			in
            {< _daleks = push_back sold _daleks ; _doctors = _doctors ; _people
            = _people >}

        method add_doctor sold =
            let rec push_back elt = function
				| [] -> [elt]
				| h::tl -> h::(push_back elt tl)
			in
            {< _daleks = _daleks ; _doctors = push_back sold _doctors ; _people
            = _people >}

        method add_people sold =
            let rec push_back elt = function
				| [] -> [elt]
				| h::tl -> h::(push_back elt tl)
			in
            {< _daleks = _daleks ; _doctors = _doctors ; _people = push_back
            sold _people >}

        method delete typ =
            match typ with
            | "dalek" -> {< _daleks = List.tl _daleks ; _doctors = _doctors ;
            _people = _people >}
            | "doctor" -> {< _daleks = _daleks ; _doctors = List.tl _doctors ; _people = _people >}
            | _ -> {< _daleks = _daleks ; _doctors = _doctors ; _people =
                List.tl _people >}

        method private how_many_left = function
            | "dalek" -> List.length _daleks
            | "doctor" -> List.length _doctors
            | _ -> List.length _people

        method make_dalek_talk () =
            if List.length _daleks <= 0 then ignore ()
            else
                let dalek = List.hd _daleks in
                dalek#talk

        method make_doctor_talk () =
            if List.length _doctors <= 0 then ignore ()
            else
                let doctor = List.hd _doctors in
                doctor#talk

        method make_people_talk () =
            if List.length _people <= 0 then ignore ()
            else
                let people = List.hd _people in
                people#talk

        method get_doc () =
            List.hd _doctors

        method get_people () =
            List.hd _people

        method get_dalek () =
            List.hd _daleks

        method make_qulbutoke () =
            print_endline "Qulbutoké !"

        method print_left () =
            print_string "-- Remaining troops :\n" ;
            print_string "Daleks : " ;
            print_int (self#how_many_left "dalek") ;
            print_string "\nDoctors : " ;
            print_int (self#how_many_left "doctor") ;
            print_string "\nPeople : " ;
            print_int (self#how_many_left "people") ;
            print_char '\n'

		method do_time_war =
			print_endline "Get ready for an amazing war experience, featuring useless people, dumb daleks and clueless doctors.\n" ;
            print_endline "Building people's army" ;
            let p1 = (new People.people "Superman") in
            let p2 = (new People.people "Machine gun") in
            let p3 = (new People.people "Qulbutoké") in
            let self = self#add_people p1 in
            let self = self#add_people p2 in
            let self = self#add_people p3 in
            print_endline "Building doctors' army" ;
            let self = self#add_doctor (new Doctor.doctor "Gadget" 32 p1) in
            let self = self#add_doctor (new Doctor.doctor "Hippocrate" 536 p2) in
            let self = self#add_doctor (new Doctor.doctor "Who" 47 p3) in
            print_endline "Building daleks' army" ;
            let self = self#add_dalek (new Dalek.dalek) in
            let self = self#add_dalek (new Dalek.dalek) in
            let self = self#add_dalek (new Dalek.dalek) in
            self#print_left () ;
            self#make_dalek_talk () ;
            self#make_dalek_talk () ;
            self#make_people_talk () ;
            self#make_doctor_talk () ;
            self#make_people_talk () ;
            self#make_doctor_talk () ;
            self#make_dalek_talk () ;
            self#make_dalek_talk () ;
            self#make_dalek_talk () ;
            self#make_doctor_talk () ;
            print_endline "After warm welcome, daleks start attacking..." ;
            let p = self#get_people () in
            let dalek = self#get_dalek () in
            dalek#exterminate p ;
            let self = self#delete "people" in
            let p = self#get_people () in
            dalek#exterminate p ;
            let self = self#delete "people" in
            self#print_left () ;
            print_endline "Only Qulbutoké is remaining !" ;
            self#make_qulbutoke () ;
            self#make_qulbutoke () ;
            self#make_qulbutoke () ;
            self#make_qulbutoke () ;
            self#make_qulbutoke () ;
            self#make_qulbutoke () ;
            self#make_qulbutoke () ;
            print_endline "Doctors start attacking also..." ;
            let p = self#get_people () in
            p#die ;
            let self = self#delete "people" in
            print_endline "Well, he was kind of annoying...\nDaleks and doctors start realising they get along quite well" ;
            self#make_doctor_talk () ;
            print_endline "..." ;
            self#make_doctor_talk () ;
            self#make_dalek_talk () ;
            self#make_dalek_talk () ;
            print_endline "..." ;
            print_endline "Well, they are quite weird but the doctors like them.\nThey end up making a barbecue, telling jokes and eating marshmallows.\nI guess you can say it went well" ;
            self#print_left ()

	end
