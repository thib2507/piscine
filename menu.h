#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "grman/grman.h"
#include "grman/widget.h"
#include "graph.h"

class menu
{

public:
    menu();
    ~menu();
    void load_menu();
    int display(Graph g);
private:
///partie a retirer
    grman::WidgetBox m_top_box;
    grman::WidgetBox m_boite_boutons;    // Sera la boite à boutons en haut à droite
    grman::WidgetButton m_bouton1;       // Sera le bouton avec le texte NEW
    grman::WidgetButton m_bouton2;
    grman::WidgetButton m_bouton3;
    grman::WidgetButton m_bouton4;
    grman::WidgetButton m_bouton5;
    grman::WidgetImage m_image;
    grman::WidgetText m_b1;
    grman::WidgetText m_b2;
    grman::WidgetText m_b3;
    grman::WidgetText m_b4;
    ///jusqu'a la



    BITMAP* page;
    BITMAP* screenbis;


};


#endif // MENU_H_INCLUDED
