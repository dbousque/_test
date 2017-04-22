

open Lwt
open Cohttp
open Cohttp_lwt_unix

type usermove = {
	board:	int ;
	y:		int ;
	x:		int
} [@@deriving yojson]

let server =
	let games = ref (Hashtbl.create 10) in
	let ident = ref 0 in
	let callback _conn req body =
		let uri = req |> Request.uri |> Uri.to_string in
		let meth = req |> Request.meth |> Code.string_of_method in
		let headers = req |> Request.headers |> Header.to_string in
		if meth = "GET" then (
			let parts = Str.split (Str.regexp "/") uri in
			let filename = List.nth parts ((List.length parts) - 1) in
			let filename = if List.length parts <= 2 then "" else filename in
			if filename = "" then (
				Hashtbl.add !games !ident (Main.make_new_game ()) ;
				incr ident ;
				(*body |> Cohttp_lwt_body.to_string >|= (fun body ->
					(Printf.sprintf "Uri: %s\nMethod: %s\nHeaders\nHeaders: %s\nBody: %s"
						uri meth headers body))
				>>= (fun body -> Server.respond_string ~status:`OK ~body ()) *)
			) ;
			let filename = if filename = "" then "index.html" else filename in
			Lwt_io.printf "file %s\n" filename ;
			Server.respond_file ~fname:filename ()
		)
		else (
			Cohttp_lwt_body.to_string body >>= fun (body) ->
				let result = body |> Yojson.Safe.from_string |> usermove_of_yojson in
				match result with
				| Result.Ok json -> (
					let json = json |> usermove_to_yojson |> Yojson.Safe.to_string in
					Server.respond_string ~status:`OK ~body:json ()
				)
				| Result.Error str -> Server.respond_string ~status:`OK ~body:str ()
		)
	in
	Server.create ~mode:(`TCP (`Port 8000)) (Server.make ~callback ())

let () = ignore (Lwt_main.run server)