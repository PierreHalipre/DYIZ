#include "main.hpp"

int main()
{
    RenderWindow *gFenetrePrincipale = new RenderWindow(VideoMode(640, 640), "DYIZ");
    gFenetrePrincipale->setKeyRepeatEnabled(false);

    Carte gCarte = Carte(Vector2f(32, 32), Vector2f(20, 15), 4);
    Etat gEtat = Etat(Vector2f(32, 32), Vector2f(20, 5));
    Menu gMenu = Menu(Vector2f(32, 32), Vector2f(20, 20));

    int gAction = 1;

    Evenement gEvenement = Evenement();

    while (gFenetrePrincipale->isOpen() == true)
    {
        while (gFenetrePrincipale->pollEvent(gEvenement))
        {
            gEvenement.MiseAJour();

            if (gEvenement.type == Event::Closed)
            {
                gFenetrePrincipale->close();
            }
        }

        gFenetrePrincipale->clear();

        if (gAction == 0)
        {
            gFenetrePrincipale->close();
        }

        else if (gAction == 1)
        {
            gMenu.Action(&gEvenement, &gCarte, &gAction);

            gMenu.Afficher(gFenetrePrincipale);
        }

        else if (gAction == 2)
        {
            gCarte.Action(&gEvenement, &gAction);
            gEtat.Action(&gEvenement, &gCarte, &gAction);

            gCarte.Afficher(gFenetrePrincipale);
            gEtat.Afficher(gFenetrePrincipale);
        }

        gFenetrePrincipale->display();
    }

    return 0;
}
