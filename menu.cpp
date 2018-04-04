#include "menu.h"
#include "grman/widget.h"
#include "grman/grman.h"
#include "graph.h"

menu::menu(){
}
menu::~menu(){
}
void menu::load_menu(){


    m_top_box.set_frame(0, 0,1000 , 770);
    m_top_box.set_bg_color(GRIS);



m_top_box.add_child( m_image );
    m_image.set_pic_name("menu.png");
    m_image.set_gravity_x(grman::GravityX::Left);

 m_top_box.add_child( m_bouton1 );
    m_bouton1.set_frame(400,350,200,250);
    m_bouton1.set_bg_color(BLANC);

m_top_box.add_child(m_bouton2);
 m_bouton2.set_frame(410,355,180,55);
    m_bouton2.set_bg_color(BLANCJAUNE);

    m_top_box.add_child(m_bouton3);
 m_bouton3.set_frame(410,415,180,55);
    m_bouton3.set_bg_color(BLANCJAUNE);

    m_top_box.add_child(m_bouton4);
 m_bouton4.set_frame(410,475,180,55);
    m_bouton4.set_bg_color(BLANCJAUNE);

    m_top_box.add_child(m_bouton5);
 m_bouton5.set_frame(410,535,180,55);
    m_bouton5.set_bg_color(BLANCJAUNE);

    m_bouton2.add_child(m_b1);
    m_b1.set_message("choisir graphe 1");

    m_bouton3.add_child(m_b2);
    m_b2.set_message("choisir graphe 2");

    m_bouton4.add_child(m_b3);
    m_b3.set_message("choisir graphe 3");

    m_bouton5.add_child(m_b4);
    m_b4.set_message("quitter");


page=load_bitmap("menu.bmp",NULL);
screenbis = create_bitmap(SCREEN_W,SCREEN_H);



}

int menu::display(Graph g)
{

   //blit(page,screen,0,0,0,0, SCREEN_W,SCREEN_H);
//blit(screenbis,screen,0,0,0,0,SCREEN_W,SCREEN_H);
 m_top_box.update();

  if ( m_bouton5.clicked() ){
    exit(0);
    return 0;
  }

   if ( m_bouton2.clicked() ){

g.make_example();
g.update();
return 1;
  }


}




