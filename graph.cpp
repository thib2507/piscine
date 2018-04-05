#include "graph.h"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les �l�ments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de r�glage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, � adapter...
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


/// Gestion du Vertex avant l'appel � l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donn�e m_value vers le slider associ�
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donn�e m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex apr�s l'appel � l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donn�e m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les �l�ments de l'interface
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

    // Une boite pour englober les widgets de r�glage associ�s
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de r�glage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, � adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel � l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donn�e m_weight vers le slider associ�
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donn�e m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge apr�s l'appel � l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donn�e m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de pr�parer un cadre d'accueil des
/// �l�ments qui seront ensuite ajout�s lors de la mise ne place du Graphe
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

    m_ajout.add_child(ajout);
    ajout.set_message("ajouter");

    m_sup.add_child(sup);
    sup.set_message("supprimer");

    m_retour.add_child(retour);
    retour.set_message("menu");

    m_fcon.add_child(fcon);
    fcon.set_message("forte connexite");

    m_kcon.add_child(kcon);
    kcon.set_message("k-connexite");




}


/// M�thode sp�ciale qui construit un graphe arbitraire (d�mo)
/// Cette m�thode est � enlever et remplacer par un syst�me
/// de chargement de fichiers par exemple.
/// Bien s�r on ne veut pas que vos graphes soient construits
/// "� la main" dans le code comme �a.
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
    std::string pic_name;

    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne pr�c�dente est en gros �quivalente � :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    std::ifstream fichier(nom_fichier.c_str()); //ouverture du fichier
    if(fichier) //si le fichier � bien �t� ouvert
    {
        fichier >> id;
        m_id = id;

        fichier >> nb_vertex;


        /// Les sommets doivent �tre d�finis avant les arcs
        // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...


        for(int i=0; i<nb_vertex; i++)
        {
            fichier >> idx >> value >> x >> y;
            std::getline(fichier,pic_name);

            add_interfaced_vertex(idx, value, x, y, pic_name);
        }

        fichier >> nb_edge;



        /// Les arcs doivent �tre d�finis entre des sommets qui existent !
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

///M�thode de sauvegarde du graph
void Graph::save_graph()
{

    std::stringstream path;

    path << "graphtest" << m_id << ".txt";

    std::ofstream fichier(path.str(), std::ios::out | std::ios::trunc);

    if(fichier)
    {
        fichier << m_id << std::endl;
        fichier << m_vertices.size() << std::endl;

        for (auto it = m_vertices.begin(); it!=m_vertices.end(); ++it)
        {
            fichier << it->first << " " << it->second.m_value << " "
                    << it->second.m_interface->m_top_box.get_posx() + 2 << " " <<
                    it->second.m_interface->m_top_box.get_posy() + 2 <<
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

/// La m�thode update � appeler dans la boucle de jeu pour les graphes avec interface
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

        ajout();

    }

    if(m_interface->m_sup.clicked())
    {

        int a;
        std::cout<<"rentrer idx sommet � supprimer de type int "<<std::endl;
        std::cin>>a;
        supprimer(a);
        grman::mettre_a_jour();

    }

}

/// Aide � l'ajout de sommets interfac�s
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Cr�ation d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide � l'ajout d'arcs interfac�s
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

    /// OOOPS ! Prendre en compte l'arc ajout� dans la topologie du graphe !
    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;
    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);
}

void Graph::ajout()
{
    int idx;
    int nbarete;
    int S1, S2,indice,poids;

    //permet de s'assurrer de ne pas cr�er un arc avec un sommet d�truit
    bool add_edge_ok = false;

    std::stringstream path;

    path << "ref" << m_id << ".txt";


    std::cout << "Sommets pouvant etre ajoutes :" << std::endl;

    //on verifie que le cim n'est pas vide
    if(m_cim.empty()==false)
    {
        //on affiche tout les sommets pr�sent dans le cim
        for (auto it = m_cim.begin(); it!=m_cim.end(); ++it)
        {
            std::cout<<"- " <<it->first<<std::endl;
        }

        std::cout << "--> ";
        std::cin >> idx;

        //on ajoute le sommet
        add_interfaced_vertex(idx,m_cim[idx].m_value,m_cim[idx].m_interface->m_top_box.get_posx()+2,
                              m_cim[idx].m_interface->m_top_box.get_posy()+2,m_cim[idx].m_interface->m_img.get_pic_name());



        //on ouvre le fichier de ref des arcs pour cr�er les arcs en cons�quence
        std::ifstream fichier(path.str()); //ouverture du fichier
        if(fichier) //si le fichier � bien �t� ouvert
        {
            fichier>>nbarete;

            //on parcours toutes les ar�tes du fichier
            for(int i=0; i<nbarete; i++)
            {

                fichier>>S1>>S2>>indice>>poids;

                //si notre sommet est �gal � l'un des sommets du fichier
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

                //m�me d�marche que pr�c�dement
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
    if(fichier) //si le fichier � bien �t� ouvert
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
