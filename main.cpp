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
    int escape=0;

    menu m;
    //
    m.load_menu();

    while ( escape !=42 )
    {
        switch(escape)
        {
        case 0:
            escape = m.display(g);
            grman::mettre_a_jour();
            break;

        case 1:
            escape = g.update();
            grman::mettre_a_jour();
            break;

        case 2:
            g.save_graph();
            g.empty_edges();
            g.empty_cim();
            g.empty_vertice();
            g.clear_interface();
            escape = 0;
            break;
        }


    }

     g.make_example("graph1.txt");
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


