let f _ () =
	Lwt.return "<html><head><title>Hello world</title></head><body>Welcome</body></html>"

let main_service =
	Eliom_registration.Html_text.create
		~path:(Eliom_service.Path ["aaa"; "bbb"])
		~meth:(Eliom_service.Get Eliom_parameter.any)
		f