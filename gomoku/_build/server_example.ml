

open Lwt
open Cohttp
open Cohttp_lwt_unix
open BoardType

type usermove = {
	game_id:	int ;
	y:			int ;
	x:			int
} [@@deriving yojson]

type aimove = {
	game_id:	int
} [@@deriving yojson]

type makeboard = {
	dimensions:			int ;
	replace_existing:	bool ;
	existing_id:		int
} [@@deriving yojson]

type usermove_response = {
	ok:				bool ;
	valid_next:		int list list ;
	game_state:		string ;
	tiles:			int list list ;
	black_taken:	int ;
	white_taken:	int
} [@@deriving yojson]

type aimove_response = {
	ok:			bool ;
	y:			int ;
	x:			int ;
	time_taken:	int ;
	valid_next:	int list list ;
	game_state:	string ;
	tiles:		int list list ;
	black_taken:	int ;
	white_taken:	int
} [@@deriving yojson]

let make_tiles_to_front game =
	let tiles = Array.map (Array.map Tile.to_int) Main.(game.board.tiles) in
	Array.map Array.to_list tiles |> Array.to_list

let create_new_board body games ident heuristic =
	let options = body |> Yojson.Safe.from_string |> makeboard_of_yojson in
	match options with
	| Result.Error str -> str
	| Result.Ok options -> (
		let replace_ok =
			options.replace_existing && (
			try
				(Hashtbl.find !games options.existing_id ; true)
			with
				| Not_found -> false
			)
		in
		let new_ident =
			if replace_ok then (
				Hashtbl.remove !games options.existing_id ;
				options.existing_id
			)
			else (
				let to_ret = !ident in
				incr ident ;
				to_ret
			)
		in
		let dimensions = options.dimensions in
		let dimensions = if dimensions < 5 then 5 else dimensions in
		let dimensions = if dimensions > 19 then 19 else dimensions in
		Hashtbl.add !games new_ident (Main.make_new_game dimensions heuristic 4) ;
		"ok" ^ (string_of_int new_ident)
	)

let coords_list_to_front lst =
	let rec _coords_list_to_front_helper lst acc =
		match lst with
		| [] -> []
		| (y, x) :: rest -> _coords_list_to_front_helper rest ([y; x] :: acc)
	in
	match lst with
	| None -> []
	| Some lst -> _coords_list_to_front_helper lst []

let make_usermove body games =
	let error_resp = {
		ok = false ;
		valid_next = [] ;
		game_state = "" ;
		tiles = [] ;
		black_taken = 0 ;
		white_taken = 0
	} in
	let move = body |> Yojson.Safe.from_string |> usermove_of_yojson in
	let response = (
		match move with
		| Result.Error str -> error_resp
		| Result.Ok move -> (
			try (
				let game = Hashtbl.find !games move.game_id in
				if Main.(game.game_state) <> "playing" then error_resp
				else (
					let ok, game = Main.make_move game (move.y, move.x) in
					Lwt_io.printf "ok : %B\n" ok ;
					Hashtbl.remove !games move.game_id ;
					Hashtbl.add !games move.game_id game ;
					let valid_next = coords_list_to_front Main.(game.valid_next) in
					let tiles = make_tiles_to_front game in
					{
						ok = ok ;
						valid_next = valid_next ;
						game_state = Main.(game.game_state) ;
						tiles = tiles ;
						black_taken = Main.(game.board.red_taken) ;
						white_taken = Main.(game.board.blue_taken)
					}
				)
			) with
			| Not_found -> error_resp
		)
	) in
	response |> usermove_response_to_yojson |> Yojson.Safe.to_string

let make_ai_move body games =
	let error_resp = {
		ok = false ;
		y = 0 ;
		x = 0 ;
		time_taken = 0 ;
		valid_next = [] ;
		game_state = "" ;
		tiles = [] ;
		black_taken = 0 ;
		white_taken = 0
	} in
	let info = body |> Yojson.Safe.from_string |> aimove_of_yojson in
	let response = (
		match info with
		| Result.Error str -> error_resp
		| Result.Ok info -> (
			try (
				let game = Hashtbl.find !games info.game_id in
				if Main.(game.game_state) <> "playing" then error_resp
				else (
					let (move, game), time_taken = Main.make_ai_move game in
					Hashtbl.remove !games info.game_id ;
					Hashtbl.add !games info.game_id game ;
					match move with
					| None -> error_resp
					| Some (y, x) -> (
						let valid_next = coords_list_to_front Main.(game.valid_next) in
						let tiles = make_tiles_to_front game in
						{
							ok = true ;
							y = y ;
							x = x ;
							time_taken = time_taken ;
							valid_next = valid_next ;
							game_state = Main.(game.game_state) ;
							tiles = tiles ;
							black_taken = Main.(game.board.red_taken) ;
							white_taken = Main.(game.board.blue_taken)
						}
					)
				)
			) with
			| Not_found -> error_resp
		)
	) in
	response |> aimove_response_to_yojson |> Yojson.Safe.to_string

let make_args address =
	let ori_args = Str.split (Str.regexp "?") address in
	if List.length ori_args <= 1 then (address, "") else (
		let args = List.nth ori_args (List.length ori_args - 1) in
		if String.length args < 5 then (List.nth ori_args 0, "")
		else if String.sub args 0 5 <> "args=" then (List.nth ori_args 0, "")
		else (
			let args = String.sub args 5 (String.length args - 5) in
			let args = Netencoding.Url.decode args in
			(List.nth ori_args 0, args)
		)
	)

let server =
	let heuristic = Heuristic.simple_heuristic in
	let games = ref (Hashtbl.create 10) in
	let ident = ref 0 in
	let callback _conn req body =
		let uri = req |> Request.uri |> Uri.to_string in
		let meth = req |> Request.meth |> Code.string_of_method in
		let headers = req |> Request.headers |> Header.to_string in
		let parts = Str.split (Str.regexp "/") uri in
		let address = List.nth parts ((List.length parts) - 1) in
		let address = if List.length parts <= 2 then "" else address in
		let address, args = make_args address in
		match address with
		| "makeboard" -> (
			Cohttp_lwt_body.to_string body >>= fun (body) ->
				let res_str = create_new_board args games ident heuristic in
				Server.respond_string ~status:`OK ~body:res_str ()
		)
		| "usermove" -> (
			Cohttp_lwt_body.to_string body >>= fun (body) ->
				let res_str = make_usermove args games in
				Server.respond_string ~status:`OK ~body:res_str ()
		)
		| "makeaimove" -> (
			Cohttp_lwt_body.to_string body >>= fun (body) ->
				let res_str = make_ai_move args games in
				Server.respond_string ~status:`OK ~body:res_str ()
		)
		| _ -> (
			let filename = address in
			let filename = if filename = "" then "index.html" else filename in
			Lwt_io.printf "file %s\n" filename ;
			Server.respond_file ~fname:filename ()
		)
	in
	Server.create ~mode:(`TCP (`Port 8000)) (Server.make ~callback ())

let () = ignore (Lwt_main.run server)