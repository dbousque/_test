

[%%client

open Eliom_content.Html.D
open Eliom_content.Html
open Lwt

type bestiole = {
	elt:						Html_types.img D.elt ;
	dom_elt:					Dom_html.element Js.t ;
	mutable x:					int ;
	mutable y:					int ;
	mutable currently_dragged:  bool
}

]