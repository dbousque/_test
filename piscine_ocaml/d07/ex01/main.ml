

let () =
    let doctor = new Doctor.doctor "Who" 47 (new People.people "Dalek") in
    print_endline doctor#to_string ;
    print_string "doctor talking : " ;
    doctor#talk ;
    print_string "doctor using screwdriver : " ;
    doctor#use_sonic_screwdriver ;
    print_endline doctor#to_string ;
    print_endline "travelling in time from 2016 to 1980" ;
    let doctor = doctor#travel_in_time 2016 1980 in
    print_endline doctor#to_string ;
    print_endline "travelling in time from 1980 to 2016" ;
    let doctor = doctor#travel_in_time 1980 2016 in
    print_endline doctor#to_string ;
    print_endline "travelling in time from 2016 to 1932" ;
    let doctor = doctor#travel_in_time 2016 1932 in
    print_endline doctor#to_string ;
    print_endline "(I know it makes no sense to have a negative age, but so does traveling back in time don't you think ?)"
