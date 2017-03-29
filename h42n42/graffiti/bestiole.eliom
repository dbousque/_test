

[%%client

open Eliom_content.Html.D
open Lwt

let make_bestiole_image () =
  let image =
    img ~alt:""
      ~a:[a_width 40 ;
        a_class ["bestiole"] ;
        a_draggable true ;
      ]
      ~src:(make_uri (Eliom_service.static_dir ()) ["images" ; "bestiole.png"]) ()
  in
  Lwt.async (fun () ->
    let dom_image = Eliom_content.Html.To_dom.of_element image in
    Lwt_js_events.drags dom_image
      ( fun ev _ ->
          let x = ev##.clientX in
          let y = ev##.clientY in
          let x = Js.string (string_of_int x ^ "px") in
          let y = Js.string (string_of_int y ^ "px") in
          dom_image##.style##.left := x ;
          dom_image##.style##.top := y ;
          Lwt.return ()
      )
  ) ;
  image

]