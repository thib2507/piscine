#include "grman/grman.h"
#include <iostream>

#include "graph.h"
#include "menu.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();
    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;

    menu m;
    //
    m.load_menu();

    while ( m.display(g)!=1 )
    {
        m.display(g);




        grman::mettre_a_jour();
    }

     //g.make_example("graph1.txt");
    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
   while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets

        g.update();


        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }

    g.save_graph();
    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


