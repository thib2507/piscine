#include "graph.h"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0, 100000);  // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

   /*  if (id==1)
    {
        m_main_box.add_child(fond);
        fond.set_pic_name("foret1.bmp");

    }

      if (id==2)
    {
        m_main_box.add_child(fond);
        fond.set_pic_name("asie3.bmp");

    }

      if (id==3)
    {
        m_main_box.add_child(fond);
        fond.set_pic_name("savane2.bmp");

    }*/

    m_main_box.set_bg_color(BLANCJAUNE);

    m_top_box.add_child(m_retour);
    m_retour.set_frame(10,180,75,75);
    m_retour.set_bg_color(BLEU);

    m_top_box.add_child(m_ajout);
    m_ajout.set_frame(10,10,75,75);
    m_ajout.set_bg_color(BLEU);

    m_top_box.add_child(m_sup);
    m_sup.set_frame(10,95,75,75);
    m_sup.set_bg_color(BLEU);

    m_top_box.add_child(m_fcon);
    m_fcon.set_frame(10,265,75,75);
    m_fcon.set_bg_color(BLEU);

    m_top_box.add_child(m_kcon);
    m_kcon.set_frame(10,350,75,75);
    m_kcon.set_bg_color(BLEU);

    m_top_box.add_child(m_temps);
    m_temps.set_frame(10,435,75,75);
    m_temps.set_bg_color(BLEU);

    m_ajout.add_child(ajout);
    ajout.set_pic_name("add.bmp");

    m_sup.add_child(sup);
    sup.set_pic_name("supp.bmp");

    m_retour.add_child(retour);
    retour.set_pic_name("menu2.bmp");

    m_fcon.add_child(fcon);
    fcon.set_pic_name("hard.bmp");

    m_kcon.add_child(kcon);
    kcon.set_pic_name("k.bmp");

    m_temps.add_child(temps);
    temps.set_pic_name("time.bmp");




}



/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example(const std::string& nom_fichier)
{
    int nb_vertex;
    int nb_edge;
    int idx;
    int id;
    double value;
    int x,y;
    int idVert1, idVert2;
    double weight;
    int emplacement;
    std::string pic_name;

    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    std::ifstream fichier(nom_fichier.c_str()); //ouverture du fichier
    if(fichier) //si le fichier à bien été ouvert
    {
        fichier >> id;
        if (id==1)
    {
        m_interface->m_main_box.add_child(m_interface->fond);
        m_interface->fond.set_pic_name("foret1.bmp");

    }

      if (id==2)
    {
        m_interface->m_main_box.add_child(m_interface->fond);
        m_interface->fond.set_pic_name("asie3.bmp");

    }

      if (id==3)
    {
        m_interface->m_main_box.add_child(m_interface->fond);
        m_interface->fond.set_pic_name("savane2.bmp");

    }
        m_id = id;

        fichier >> nb_vertex;


        /// Les sommets doivent être définis avant les arcs
        // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...


        for(int i=0; i<nb_vertex; i++)
        {
            fichier >> idx >> value >> x >> y >> emplacement;
            std::getline(fichier,pic_name);

            if(emplacement==1)
                add_interfaced_vertex(idx, value, x, y, pic_name);

            if(emplacement==0)
            {
                add_interfaced_vertex(idx, value, x, y, pic_name);
                supprimer(idx);
            }
        }

        fichier >> nb_edge;



        /// Les arcs doivent être définis entre des sommets qui existent !
        // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...

        for(int i=0; i<nb_edge; i++)
        {
            fichier >> idx >> idVert1 >> idVert2 >> weight;

            add_interfaced_edge(idx,idVert1,idVert2,weight);

        }

    }

    else
    {
        std::cout << "file " << nom_fichier << " could not be found";
    }

}

///Méthode de sauvegarde du graph
///Méthode de sauvegarde du graph
void Graph::save_graph()
{

    std::stringstream path;

    path << "graph" << m_id << ".txt";

    std::ofstream fichier(path.str(), std::ios::out | std::ios::trunc);

    if(fichier)
    {
        fichier << m_id << std::endl;
        fichier << m_vertices.size() + m_cim.size() << std::endl;

        for (auto it = m_vertices.begin(); it!=m_vertices.end(); ++it)
        {
            fichier << it->first << " " << it->second.m_value << " "
                    << it->second.m_interface->m_top_box.get_posx() + 2 << " " <<
                    it->second.m_interface->m_top_box.get_posy() + 2 << " 1" <<
                    it->second.m_interface->m_img.get_pic_name() << std::endl;

        }

        for (auto it = m_cim.begin(); it!=m_cim.end(); ++it)
        {
            fichier << it->first << " " << it->second.m_value << " "
                    << it->second.m_interface->m_top_box.get_posx() + 2 << " " <<
                    it->second.m_interface->m_top_box.get_posy() + 2 << " 0" <<
                    it->second.m_interface->m_img.get_pic_name() << std::endl;

        }

        fichier << m_edges.size() << std::endl;

        for (auto it = m_edges.begin(); it!=m_edges.end(); ++it)
        {
            fichier << it->first << " " << it->second.m_from << " " << it->second.m_to <<
                    " " << it->second.m_weight << std::endl;

        }





        fichier.close();

    }



}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
int Graph::update()
{
    //if (!m_interface)
    //return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update(); //Si supprime, plus d'affichage

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();


    if(m_interface->m_ajout.clicked())
    {
        bool bon;
        int idx;
        if(m_cim.empty()==false)
        {
            while (bon == false)
            {
                std::cout <<std::endl << "Sommets pouvant etre ajoutes :" << std::endl;
                //on affiche tout les sommets présent dans le cim

                for (auto it = m_cim.begin(); it!=m_cim.end(); ++it)
                {
                    std::cout<<"- " <<it->first<<std::endl;
                }

                std::cout << "--> ";
                std::cin >> idx;

                bon=false;
                for (auto it = m_cim.begin(); it!=m_cim.end(); ++it)
                {
                    if (it->first == idx)
                    {
                        bon=true;
                    }

                }
            }
        }

        ajout(idx);

    }

    if(m_interface->m_sup.clicked())
    {

        int a;
        std::cout<<"rentrer idx sommet à supprimer de type int "<<std::endl;
        std::cin>>a;
        supprimer(a);
        grman::mettre_a_jour();

    }

    if(m_interface->m_fcon.clicked())
    {
        fortement_connexe();
        m_interface->m_top_box.add_child(m_interface->m_supp_couleur);
        m_interface->m_supp_couleur.set_frame(10,630,75,75);
        m_interface->m_supp_couleur.set_bg_color(ROUGECLAIR);
        m_interface->m_supp_couleur.add_child(m_interface->sup_couleur);
        m_interface->sup_couleur.set_pic_name("back.bmp");
    }

    if(m_interface->m_supp_couleur.clicked())
    {
        for (auto it = m_vertices.begin(); it!=m_vertices.end(); it++)
        {
            it->second.m_interface->m_top_box.set_bg_color(-1);

        }

        m_interface->m_top_box.remove_child(m_interface->m_supp_couleur);
    }
    if(m_interface->m_kcon.clicked())
    {
        m_interface->m_top_box.remove_child(m_interface->m_supp_couleur);
        k_connexite();

    }

    if(m_interface->m_temps.clicked())
    {

        calcul();
        m_interface->m_top_box.add_child(m_interface->m_revenir);
        m_interface->m_revenir.set_frame(10,630,75,75);
        m_interface->m_revenir.set_bg_color(ROUGECLAIR);
        m_interface->m_revenir.add_child(m_interface->revenir);
        m_interface->revenir.set_pic_name("back.bmp");

    }

    if(m_interface->m_revenir.clicked())
        {
        m_new();
    m_interface->m_top_box.remove_child(m_interface->m_revenir);
    save_graph();
        }

    if(m_interface->m_retour.clicked())
    {
        return 2;
    }

    else
    {
        return 1;
    }




}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx)
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);

    /// OOOPS ! Prendre en compte l'arc ajouté dans la topologie du graphe !
    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;
    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);
}

void Graph::ajout(int idx)
{

    int nbarete;
    int S1, S2,indice,poids;

    //permet de s'assurrer de ne pas créer un arc avec un sommet détruit
    bool add_edge_ok = false;

    std::stringstream path;

    path << "ref" << m_id << ".txt";




    //on verifie que le cim n'est pas vide
    if(m_cim.empty()==false)
    {


        //on ajoute le sommet
        add_interfaced_vertex(idx,m_cim[idx].m_value,m_cim[idx].m_interface->m_top_box.get_posx()+2,
                              m_cim[idx].m_interface->m_top_box.get_posy()+2,m_cim[idx].m_interface->m_img.get_pic_name());



        //on ouvre le fichier de ref des arcs pour créer les arcs en conséquence
        std::ifstream fichier(path.str()); //ouverture du fichier
        if(fichier) //si le fichier à bien été ouvert
        {
            fichier>>nbarete;

            //on parcours toutes les arêtes du fichier
            for(int i=0; i<nbarete; i++)
            {

                fichier>>S1>>S2>>indice>>poids;

                //si notre sommet est égal à l'un des sommets du fichier
                if(S1==idx)
                {
                    //on s'assure que le second sommet n'est pas dans le cim
                    add_edge_ok=true;
                    for (auto it = m_cim.begin(); it!=m_cim.end(); ++it)
                    {
                        if(it->first == S2)
                            add_edge_ok = false;

                    }

                    //Si le second sommet existe bien, on ajoute l'arc
                    if(add_edge_ok==true)
                        add_interfaced_edge(indice,S1,S2,poids);

                }

                //même démarche que précédement
                if(S2==idx)
                {
                    add_edge_ok=true;
                    for (auto it = m_cim.begin(); it!=m_cim.end(); ++it)
                    {
                        std::cout << it->first << " - " << S1 << std::endl;
                        if(it->first == S1)
                            add_edge_ok = false;
                    }

                    if(add_edge_ok==true)
                        add_interfaced_edge(indice,S1,S2,poids);

                }
            }

            //on efface le sommet du cim
            m_cim.erase(idx);



        }

    }

    else
        std::cout << "  !!AUCUN!!" << std::endl;


}

void Graph::supprimer(int idx)
{

    m_cim.insert(std::pair <int,Vertex> (idx,m_vertices[idx]));
    m_interface->m_main_box.remove_child(m_vertices[idx].m_interface->m_top_box);
    m_vertices.erase(idx);

    int nbarete;
    int S1, S2,indice,poids;

    std::stringstream path;

    path << "ref" << m_id << ".txt";

    std::ifstream fichier(path.str()); //ouverture du fichier
    if(fichier) //si le fichier à bien été ouvert
    {
        fichier>>nbarete;

        for(int i=0; i<nbarete; i++)
        {

            fichier>>S1>>S2>>indice>>poids;
            if(S1==idx || S2==idx )
            {
                std::cout<<S1<<"    "<<S2<<std::endl;
                m_interface->m_main_box.remove_child(m_edges[indice].m_interface->m_top_edge);
                m_interface->m_main_box.remove_child(m_edges[indice].m_interface->m_box_edge);
                m_edges.erase(indice);

            }

        }

    }

}

void Graph::empty_edges()
{
    if(!m_edges.empty())
    m_edges.clear();
}

void Graph::empty_vertice()
{
    if(!m_vertices.empty())
    m_vertices.clear();
}

void Graph::empty_cim()
{
        if(!m_cim.empty())
            m_cim.clear();
}

void Graph::clear_interface()
{
    m_interface.reset();
}

int Graph::check_voisins(int idx, std::vector<int> marque)
{
    std::vector<int> sommets_potentiels;
    int nbarete;
    int S1, S2,indice,poids;
    bool est_present;

    //permet de s'assurrer de ne pas créer un arc avec un sommet détruit
    bool add_edge_ok = false;

    std::stringstream path;

    path << "ref" << m_id << ".txt";

    std::ifstream fichier(path.str()); //ouverture du fichier
    if(fichier) //si le fichier à bien été ouvert
    {
        fichier>>nbarete;

        //on parcours toutes les arêtes du fichier
        for(int i=0; i<nbarete; i++)
        {
            fichier>>S1>>S2>>indice>>poids;

            if(S1==idx)
            {
                sommets_potentiels.push_back(S2);
            }

        }

        if(sommets_potentiels.size() == 0)
            return -1;

        if(sommets_potentiels.size() != 0)
        {


            for(int i=0; i<sommets_potentiels.size(); i++)
            {
                est_present=false;

                for(int j=0; j<marque.size(); j++)
                {
                    //std::cout << "marque : " << marque[j] << " et sommet potentiel : " << sommets_potentiels[i] << std::endl;
                    if(sommets_potentiels[i] == marque[j])
                        est_present=true;
                }


                for (auto it = m_cim.begin(); it!=m_cim.end(); ++it)
                {
                    if(sommets_potentiels[i] == it-> first)
                        est_present=true;
                }

                if(!est_present)
                    return sommets_potentiels[i];
            }
        }



    }


    else
    {
        std::cout << "file " << path.str() << " could not be found";
    }

    fichier.close();

    return -1;


}

int Graph::check_voisin_inverse(int idx, std::vector<int> marque)
{
    std::vector<int> sommets_potentiels;
    int nbarete;
    int S1, S2,indice,poids;
    bool est_present;

    //permet de s'assurrer de ne pas créer un arc avec un sommet détruit
    bool add_edge_ok = false;

    std::stringstream path;

    path << "ref" << m_id << ".txt";

    std::ifstream fichier(path.str()); //ouverture du fichier
    if(fichier) //si le fichier à bien été ouvert
    {
        fichier>>nbarete;

        //on parcours toutes les arêtes du fichier
        for(int i=0; i<nbarete; i++)
        {
            fichier>>S1>>S2>>indice>>poids;

            if(S2==idx)
            {
                sommets_potentiels.push_back(S1);
            }

        }

        if(sommets_potentiels.size() == 0)
            return -1;

        if(sommets_potentiels.size() != 0)
        {


            for(int i=0; i<sommets_potentiels.size(); i++)
            {
                est_present=false;

                for(int j=0; j<marque.size(); j++)
                {
                    //std::cout << "marque : " << marque[j] << " et sommet potentiel : " << sommets_potentiels[i] << std::endl;
                    if(sommets_potentiels[i] == marque[j])
                        est_present=true;
                }

                for (auto it = m_cim.begin(); it!=m_cim.end(); ++it)
                {
                    if(sommets_potentiels[i] == it-> first)
                        est_present=true;
                }

                if(!est_present)
                    return sommets_potentiels[i];
            }
        }



    }


    else
    {
        std::cout << "file " << path.str() << " could not be found";
    }

    fichier.close();

    return -1;


}

void Graph::fortement_connexe()
{
    int nb_etapes=1;
    int actuel;
    int next, stock;
    int tour=0;
    bool ok;
    std::map<int,int> denominateur;
    std::map<int,int> numerateur;
    std::stack<int> predecesseur;
    std::stack<int> stack_dfs;
    std::queue<int> file_priorite;
    std::vector<int> marque_e1;
    std::vector<int> marque_e2;

    //initialisation de la map numérateur
    for(auto it=m_vertices.begin(); it!=m_vertices.end(); it++)
    {
        numerateur.insert(std::pair <int,int> (it->first,0));

    }


    ///DEBUT ETAPE 1 ----------------------------------------------------------------------------///

    predecesseur.push(m_vertices.begin()->first);
    actuel=m_vertices.begin()->first;
    marque_e1.push_back(actuel);
    numerateur.at(actuel) = nb_etapes;
    nb_etapes++;

    while(nb_etapes <=((m_vertices.size()*2)))
    {
        while(check_voisins(actuel,marque_e1)!=-1)
        {
            std::cout<<"actuel"<<actuel<<std::endl;

            /* for(int i=0; i<marque_e1.size();i++)
             {
                 std::cout << "marques : " << marque_e1[i] << std::endl;
             }*/

            next=check_voisins(actuel,marque_e1);
            std::cout << "next"<<next << std::endl;
            predecesseur.push(next);
            marque_e1.push_back(next);
            actuel=next;
            numerateur.at(actuel) = nb_etapes;
            nb_etapes++;

        }

        std::cout << "fuck" << std::endl;


        while(check_voisins(actuel,marque_e1)==-1 && nb_etapes <=((m_vertices.size()*2)))
        {
            if(numerateur.at(actuel)==0)
            {
                numerateur.at(actuel) = nb_etapes;
                nb_etapes++;
                denominateur.insert(std::pair<int,int> (actuel,nb_etapes));
                nb_etapes++;
            }

            if(numerateur.at(actuel)!=0)
            {
                denominateur.insert(std::pair<int,int> (actuel,nb_etapes));
                nb_etapes++;
            }

            predecesseur.pop();
//std::cout<<"actuel"<<actuel<<std::endl;
            if(predecesseur.empty()!=true)
                actuel=predecesseur.top();


            if(predecesseur.empty())
            {
                actuel = chercher_nouveau_sommet(marque_e1);
                marque_e1.push_back(actuel);
                predecesseur.push(actuel);
                numerateur.at(actuel) = nb_etapes;
                nb_etapes++;
            }

        }

    }

    std::cout << "----------------LISTE DES DENOMINATEURS :" << std::endl;
    for (auto it = denominateur.begin(); it!=denominateur.end(); ++it)
    {
        std::cout <<  it->second << "      " << it->first << std::endl;


    }

    ///FIN ETAPE 1 ----------------------------------------------------------------------------///


    ///DEBUT ETAPE 2 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!///

    while(!denominateur.empty())
    {

        ///DEBUT TRI PAR ORDRE DECROISSANT DES DENOMINATEURS-----------------------------------------
        stock=0;

        for (auto it = denominateur.begin(); it!=denominateur.end(); ++it)
        {
            if(it->second >= stock)
                stock = it->second;

        }

        for (auto it = denominateur.begin(); it!=denominateur.end(); ++it)
        {
            if(it->second == stock)
            {
                file_priorite.push(it->first);
                denominateur.erase(it);
            }
        }
    }

    /*   std::cout << std::endl<< std::endl << "----------------FILE PRIORITE :" << std::endl;
          int j = file_priorite.size();
          for(int i=0; i< j; i++)
          {
              std::cout << file_priorite.front() << std::endl;
              file_priorite.pop();
          }*/

    ///FIN TRI PAR ORDRE DECROISSANT DES DENOMINATEURS---------------------------------


    while(marque_e2.size() != m_vertices.size())
    {
        // std::cout << "check voisin : " << check_voisin_inverse(3,marque_e2) <<std::endl <<std::endl<<std::endl<<std::endl;

        ok = true;

        //On verifie que le sommet défilé n'est pas déjà marqué
        for(int i=0; i<marque_e2.size(); i++)
        {
            //std::cout << "file de priorite : " << file_priorite.front() << "    marque e2 :  " << marque_e2[i] << std::endl;
            if(file_priorite.front() == marque_e2[i])
                ok = false;
        }

        if(ok == true)
        {
            actuel = file_priorite.front();
            stack_dfs.push(actuel);
            file_priorite.pop();
            marque_e2.push_back(actuel);
            colorer(actuel,tour);

            while(!stack_dfs.empty())
            {
                actuel = stack_dfs.top();
                std::cout << "actuel : " << actuel<< std::endl;

                stack_dfs.pop();
                next = check_voisin_inverse(actuel,marque_e2);
                std::cout << "next : " << next<< std::endl;

                if(next != -1)
                {
                    marque_e2.push_back(next);
                    stack_dfs.push(next);
                }


                colorer(actuel,tour);
            }

            tour++;

            std::cout << std::endl << std::endl << std::endl << std::endl;
        }



        if(ok==false)
            file_priorite.pop();

    }

    ///FIN ETAPE 2 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!///


}

int Graph::chercher_nouveau_sommet(std::vector<int> marque)
{

    std::vector<int> sommets_potentiels;
    bool est_present;

    for (auto it = m_vertices.begin(); it!=m_vertices.end(); it++)
    {

        est_present=false;

        for(int j=0; j<marque.size(); j++)
        {
            //std::cout << "marque : " << marque[j] << " et sommet potentiel : " << it->first << std::endl;
            if(it->first == marque[j])
                est_present=true;
        }

        if(!est_present)
            sommets_potentiels.push_back(it->first);

    }

    if(sommets_potentiels.size()!=0)
        return sommets_potentiels.front();




    /*for(auto it = m_vertices.begin(); it!=m_vertices.end(); ++it)
                {
                    for (int i =0; i < marque_e1.size(); i++)
                    {
                        if(it->first != marque_e1[i])
                        {
                            actuel = it->first;
                            std::cout<<"test"<<actuel<<std::endl;
                        }
                        //std::cout << actuel << std::endl;


                    }

                }

                marque_e1.push_back(actuel);*/
}

void Graph::colorer(int idx, int tour)
{
    if(tour==0)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(BLANCBLEU);

    if(tour==1)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(FUCHSIA);

    if(tour==2)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(BLANCROSE);

    if(tour==3)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(FUCHSIACLAIR);

    if(tour==4)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(MARRONCLAIR);

    if(tour==5)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(VERTCLAIR);

    if(tour==6)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(CYAN);

    if(tour==7)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(KAKI);

    if(tour==8)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(ROUGECLAIR);

    if(tour==9)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(ORANGECLAIR);

    if(tour==10)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(BLANCBLEU);

    if(tour==11)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(SABLE);

    if(tour==12)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(JAUNESOMBRE);

    if(tour==13)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(CYANSOMBRE);

    if(tour==14)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(VERTFLUOCLAIR);

    if(tour==15)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(VIOLETCLAIR);

    if(tour==16)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(ROSESOMBRE);

    if(tour==17)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(BLEUSOMBRE);

    if(tour==18)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(KAKISOMBRE);

    if(tour==19)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(GRISSOMBRE);

    if(tour==20)
        m_vertices[idx].m_interface->m_top_box.set_bg_color(VIOLETSOMBRE);


}

int Graph::k_connexite()
{

    int k=0;
    for(int i=0; i<m_vertices.size(); i++)
    {

        supprimer(i);
        std::cout<<"verif connexite"<<verif_connexite(m_vertices.begin()->first)<<std::endl;
        std::cout<<m_cim.size()<<"size cim apres supp"<<std::endl;
        if(verif_connexite(m_vertices.begin()->first)==0)
        {
            std::cout<<"le graphe est : "<<k<<"-connexe"<<std::endl;
            ajout(i);
            return 0;
        }
        else
        {

            ajout(i);

        }

    }

    k++;

    for(int i=0; i<m_vertices.size(); i++)
    {
        for(int j=0; j<m_vertices.size(); j++)
        {
            supprimer(i);
            supprimer(j);
            if(verif_connexite(m_vertices.begin()->first)==0)
            {
                std::cout<<"le graphe est : "<<k<<"-connexe"<<std::endl;
                ajout(i);
                ajout(j);
                return 0;

            }
            else
            {
                ajout(i);
                ajout(j);
            }
        }
    }
    k++;




}

void Graph::vecteur_voisins(int idx, std::stack<int>& pile, std::map<int,int>& indice_connexite, std::vector<int>& marque)
{
    std::vector<int> sommets_potentiels;
    std::vector<int> sommets_voisins;
    int nbarete;
    int S1, S2,indice,poids;
    bool est_present;

    //permet de s'assurrer de ne pas créer un arc avec un sommet détruit
    bool add_edge_ok = false;

    std::stringstream path;

    path << "ref" << m_id << ".txt";

    std::ifstream fichier(path.str()); //ouverture du fichier
    if(fichier) //si le fichier à bien été ouvert
    {
        fichier>>nbarete;

        //on parcours toutes les arêtes du fichier
        for(int i=0; i<nbarete; i++)
        {
            fichier>>S1>>S2>>indice>>poids;

            if(S1==idx)
            {
                sommets_potentiels.push_back(S2);
            }

            if(S2==idx)
            {
                sommets_potentiels.push_back(S1);
            }

        }

        std::cout << "liste sommets potentiels : "<< std::endl;

        /*for(int i=0; i<sommets_potentiels.size();i++)
            std::cout << sommets_potentiels[i] << std::endl;*/

        /*   if(sommets_potentiels.size() == 0)
               return -1;*/

        if(sommets_potentiels.size() != 0)
        {


            for(int i=0; i<sommets_potentiels.size(); i++)
            {
                est_present=false;

                for(int j=0; j<marque.size(); j++)
                {
                    //std::cout << "marque : " << marque[j] << " et sommet potentiel : " << sommets_potentiels[i] << std::endl;
                    if(sommets_potentiels[i] == marque[j])
                        est_present=true;
                }

                for (auto it = m_cim.begin(); it!=m_cim.end(); ++it)
                {
                    if(sommets_potentiels[i] == it->first)
                        est_present=true;


                }


                if(!est_present)
                {
                    sommets_voisins.push_back(sommets_potentiels[i]);
                }
            }

            for(int i=0; i<sommets_voisins.size(); i++)
            {
                marque.push_back(sommets_voisins[i]);
                pile.push(sommets_voisins[i]);

                indice_connexite.at(sommets_voisins[i])=indice_connexite.at(idx);
            }
        }


        std::cout<<"MAP ------------------------------------- "  << std::endl<< std::endl<< std::endl;

        for (auto it = indice_connexite.begin(); it!=indice_connexite.end(); it++)
        {


            std::cout<<"indice sommet : "<< it->first << "    indice connexite : " << it->second << std::endl;


        }



    }


    else
    {
        std::cout << "file " << path.str() << " could not be found";
    }

    fichier.close();

}


int Graph::verif_connexite(int actuel)
{
    std::vector<int> marque;
    std::stack<int> pile;
    int indice;
    std::map<int, int> connexite;
    for(auto it=m_vertices.begin(); it!=m_vertices.end(); it++)
    {
        connexite.insert(std::pair <int,int> (it->first,it->first));

    }
    marque.push_back(actuel);
    pile.push(actuel);
    while(!pile.empty())
    {
        actuel=pile.top();
        pile.pop();
        vecteur_voisins(actuel,pile,connexite,marque);
    }
    indice=connexite.begin()->second;
    for (auto it = connexite.begin(); it!=connexite.end(); it++)
    {
        if(it->second!=indice)
        {
            std::cout<<"pas connexe"<<std::endl;
            return 0;
        }
    }
    std::cout<<"connexe"<<std::endl;
    return 1;
}

int Graph::sucesseur(int sommet)
{
    std::map<int,int> sommets_potentiels;
    std::stringstream path;
    std::vector<int> a_supprimer;
    bool estpresent;
    int nbarete;
    int S1, S2,indice,poids;

    float k=0.0001;

    path << "ref" << m_id << ".txt";

    std::ifstream fichier(path.str()); //ouverture du fichier
    if(fichier) //si le fichier à bien été ouvert
    {
        fichier>>nbarete;

        //on parcours toutes les arêtes du fichier
        for(int i=0; i<nbarete; i++)
        {
            fichier>>S1>>S2>>indice>>poids;

            if(S1==sommet)
            {
                sommets_potentiels.insert(std::pair<int,int> (S2,poids));
            }

        }
    }


    if(sommets_potentiels.size()!=0)
    {


        for(auto it=sommets_potentiels.begin(); it!=sommets_potentiels.end(); it++)
        {
            estpresent=false;
            for(auto it1=m_cim.begin(); it1!=m_cim.end(); it1++)
            {
                if(it->first==it1->first)
                    estpresent=true;


            }
            if(estpresent==true)
            {
                a_supprimer.push_back(it->first);
            }
        }

        for(int i=0; i<a_supprimer.size();i++)
                            sommets_potentiels.erase(a_supprimer[i]);


    }

    for(auto it=sommets_potentiels.begin(); it!=sommets_potentiels.end(); it++)
    {

        k=k+((m_vertices[it->first].m_value)/20);
    }
    if(m_vertices[sommet].m_value<k)
            m_vertices[sommet].m_value=0;

    return k;
}


void Graph::calcul()
{
    int s;
    int p;
    float r;
    int i=0;
    int nt1;
    bool il_faut_supp=false;

    while(i<7)
    {
        for(auto it=m_vertices.begin(); it!=m_vertices.end(); it++)
        {
           rest(2000);
            r=valeur_r(it->first);
            p=predecesseurs(it->first);
            s=sucesseur(it->first);
            colorer(it->first,i);
            nt1=int(m_vertices[it->first].m_value+(r*m_vertices[it->first].m_value*(1 -((m_vertices[it->first].m_value)/p)))-s);
            if(r==-42){
                nt1=m_vertices[it->first].m_value;
                std::cout<<"r=-42 sa valeur nt1 est : "<<nt1<<std::endl;
            }
           /*if(p==m_vertices[it->first].m_value && r!=-42){
                nt1=m_vertices[it->first].m_value*0,50;
            }
                if(nt1<m_vertices[it->first].m_value*0,90)
                        nt1=m_vertices[it->first].m_value*0,95;
                if(nt1>m_vertices[it->first].m_value*1,10)
                        nt1=m_vertices[it->first].m_value*1,05;*/

            if (nt1>0 && nt1<100000)///boucle de variation dans le temps de la population
            {
               if(int(m_vertices[it->first].m_value)<nt1){
                            for(int i=0;i<(nt1-m_vertices[it->first].m_value);i++)
                        m_vertices[it->first].m_value=int(m_vertices[it->first].m_value)+1;
                    }
                    if(int(m_vertices[it->first].m_value)>nt1){
                              for(int i=0;i<(m_vertices[it->first].m_value-nt1);i++)
                        m_vertices[it->first].m_value=int(m_vertices[it->first].m_value)-1;
                    }


                grman::mettre_a_jour();
                    update();


            }

             if(nt1>100000)
            {
                nt1=100000;

                    if(int(m_vertices[it->first].m_value)<nt1){
                            for(int i=0;i<(nt1-m_vertices[it->first].m_value);i++)
                        m_vertices[it->first].m_value=int(m_vertices[it->first].m_value)+1;
                    }
                    if(int(m_vertices[it->first].m_value)>nt1){
                              for(int i=0;i<(m_vertices[it->first].m_value-nt1);i++)
                        m_vertices[it->first].m_value=int(m_vertices[it->first].m_value)-1;
                    }

                    grman::mettre_a_jour();
                    update();
            }

           if(nt1<=0)
            {
                m_vertices[it->first].m_value=0;
               //supprimer(it->first);
                //save_graph();
               grman::mettre_a_jour();
               update();

            }
 std::cout<<it->first<<"  : indice du sommet"<<std::endl;
  std::cout<<nt1<<"  : nt1"<<std::endl;


        }

        i++;
    }
     save_graph();
}

float Graph::valeur_r(int idx)
{
    std::stringstream path;
    int nbsom;
    int indice;
    float r;
    path << "reprod" << m_id << ".txt";

    std::ifstream fichier(path.str()); //ouverture du fichier
    if(fichier) //si le fichier à bien été ouvert
    {
        fichier>>nbsom;

        //on parcours toutes les sommets du fichier
        for(int i=0; i<nbsom; i++)
        {
            fichier>>indice>>r;


            if(indice==idx)
            {
                return r;
            }

        }
    }

}


int Graph::predecesseurs(int idx)
{
    int nb_vertex;
    int nb_edge;
    int id;
    int z;
    double value;
    int x,y;
    int stock=0;
    int idVert1, idVert2;
    double weight;
    int emplacement;
    std::string pic_name;
    std::stringstream path;
    int k=0;
    int all_dead;

    std::map<int,int> poids_a_deplacer;
    std::map<int,int> sommets_potentiels;
    std::map <int,int> indice_aretes;
    std::vector<int> a_suprimer;

    path << "graph" << m_id << ".txt";

    std::ifstream fichier(path.str()); //ouverture du fichier
    if(fichier) //si le fichier à bien été ouvert
    {
        fichier >> id;
        fichier >> nb_vertex;


        for(int i=0; i<nb_vertex; i++)
        {
            fichier >> z >> value >> x >> y >> emplacement;
            std::getline(fichier,pic_name);
        }

        fichier >> nb_edge;

        for(int i=0; i<nb_edge; i++)
        {
            fichier >> z >> idVert1 >> idVert2 >> weight;

            if(idVert2==idx)
            {
                sommets_potentiels.insert(std::pair<int,int> (idVert1,weight));
                indice_aretes.insert(std::pair<int,int> (idVert1,z));
            }

        }

    }


    /*   for(auto it=sommets_potentiels.begin(); it!=sommets_potentiels.end(); it++)
           {
               std::cout << it->first << std::endl;
           }*/


    std::cout << sommets_potentiels.size() << std::endl;
    //Si on a pas de prédécesseurs
    if(sommets_potentiels.size() == 0)
    {

        k=m_vertices[idx].m_value;
        //std::cout << " k pas de pred: " << k << std::endl;

        return k;
    }


    //Si on a des predecesseurs
    if(sommets_potentiels.size() != 0)
    {


        /*     //On verifie si les predecesseurs potentiels sont dans le graph
             for(auto it=sommets_potentiels.begin(); it!=sommets_potentiels.end(); it++)
             {
                 est_present=false;

                 for (auto itBis = m_cim.begin(); itBis!=m_cim.end(); ++itBis)
                 {

                     if( it->first == itBis->first)
                         est_present=true;

                 }

                 //Si oui, on le supprime
                 if(est_present)
                     sommets_potentiels.erase(it->first);
             }*/


        //Variable pour verifier si tout les sommets sont morts
        all_dead = sommets_potentiels.size();
        //std::cout << "alldead : " << all_dead << std::endl;

        //On deplace les sommets qui sont morts par le predateur dans une nouvelle map
        for(auto it=sommets_potentiels.begin(); it!=sommets_potentiels.end(); it++)
        {
            if(it->second >= m_vertices[it->first].m_value)
            {
                poids_a_deplacer.insert(std::pair<int,int> (it->first,it->second));
                indice_aretes.erase(it->first);
                a_suprimer.push_back(it->first);
            }

        }

        for(int i=0; i<a_suprimer.size();i++)
                sommets_potentiels.erase(a_suprimer[i]);


        //std::cout << "poid a deplacer : " << poids_a_deplacer.size() << std::endl;


        //Si tout les sommets sont morts, en renvoie la somme des population qu'il restait
        if(all_dead==poids_a_deplacer.size())
        {
            for(auto it=poids_a_deplacer.begin(); it!=poids_a_deplacer.end(); it++)
            {
                k = k+ m_vertices[it->first].m_value;
                if(valeur_r(it->first)!=-42)
                supprimer(it->first);
                save_graph();
            }

            //std::cout << " k all dead : " << k << std::endl;

            return k;

        }

        //Si pas tous supprimés mais il y en a a deplacer
        if(all_dead!=poids_a_deplacer.size() &&  poids_a_deplacer.size()>0)
        {

            for(auto it=poids_a_deplacer.begin(); it!=poids_a_deplacer.end(); it++)
            {
                k = k+m_vertices[it->first].m_value;
                stock= stock+ it->second;
                supprimer(it->first);
                m_vertices[idx].m_value=m_vertices[idx].m_value*1,20;
                save_graph();
            }

            //m_edges[indice_aretes.begin()->second].m_weight = m_edges[indice_aretes.begin()->second].m_weight + stock;
            //grman::mettre_a_jour();
            //update();
            // m_vertices[sommets_potentiels.begin()->first].m_value =  m_vertices[sommets_potentiels.begin()->first].m_value + k;
                stock=0;

            for(auto it=sommets_potentiels.begin(); it!=sommets_potentiels.end(); it++)
            {

                stock = (stock + it->second)*m_vertices[it->first].m_value;
                k=k+stock;
                stock=0;
            }

            //std::cout << " k : " << k << std::endl;
            return k;

        }

        if(poids_a_deplacer.empty())
        {

            for(auto it=sommets_potentiels.begin(); it!=sommets_potentiels.end(); it++)
            {
               stock = (stock + it->second)*m_vertices[it->first].m_value;
                k=k+stock;
                stock=0;
                //std::cout << " k : " << k << std::endl;

                //std::cout << " it second : " << it->second<< std::endl;

            }

            //std::cout << " k : " << k << std::endl;
            return k;
        }

        //std::cout << " k fin: " << k << std::endl;


    }


    else
    {
        std::cout << "file " << path.str() << " could not be found";
    }

    fichier.close();



}

void Graph::m_new(){

std::vector<int> ajouter;
for(auto it=m_cim.begin();it!=m_cim.end();it++)
    {
    ajouter.push_back(it->first);

    }

for(int i=0;i<ajouter.size();i++){

    std::cout << " cim index : " << ajouter[i] << std::endl;
}
for(int i=0;i<ajouter.size();i++){

    ajout(ajouter[i]);
}
grman::mettre_a_jour();
    update();
}
