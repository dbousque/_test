

make:
	ocamlbuild -use-ocamlfind -pkgs cohttp.lwt,ppx_deriving_yojson,yojson,str,netstring gomoku_server.native

clean:
	rm -Rf _build

fclean: clean
	rm -Rf gomoku_server.native
