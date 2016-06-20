

let () =
    Random.self_init () ;
    let jokes = [|"Quel legume va tres vite et rigole dans les virages ? Reponse : le chou marreur";
    "Qui est le frere d'Albert Einstein ? Reponse : Franck";
    "Qu'est-ce qui fait 999 fois \"TIC\" et 1 fois \"TOC\" ? Reponse : Un mille pattes avec une jambe de bois";
    "Comment amuser une blonde toute la journee ? Il faut lui donner une feuille avec la phrase \"Retournez la feuille\" des deux cotes";
    "C'est un gars qui rentre dans un cafe et plouf."|]
    in
    let ind = Random.int 5 in
    print_endline (jokes.(ind))
