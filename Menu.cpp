#include "main.hpp"

Menu::Menu(Vector2f gDimensionsDesCases, Vector2f gNombreDeCases) : Zone(gDimensionsDesCases, gNombreDeCases)
{
    pPolice = new Font();
    pPolice->loadFromFile("Ressources/cour.ttf");
    pTexte = new Text();
    pTexte->setFont(*pPolice);
    pTexte->setColor(Color::Black);
    pTexte->setCharacterSize(gDimensionsDesCases.x/2);
    pTexte->setString("DYIZ");
    pTexte->setPosition(Vector2f(gDimensionsDesCases.x*gNombreDeCases.x/2-pTexte->getGlobalBounds().width/2, gDimensionsDesCases.y*3/2-pTexte->getGlobalBounds().height/2));

    for (int i = 0; i < 4; i++)
    {
        char gJouerTexte[128] = "";
        sprintf(gJouerTexte, "%d Joueur(s)", i+1);

        pJouerBouton[i] = new RectangleShape();
        pJouerBouton[i]->setOutlineThickness(-1);
        pJouerBouton[i]->setOutlineColor(Color::Black);
        pJouerBouton[i]->setSize(Vector2f(4*gDimensionsDesCases.x, 2*gDimensionsDesCases.y));
        pJouerBouton[i]->setFillColor(Color::White);
        pJouerBouton[i]->setPosition(8*gDimensionsDesCases.x, 3*(i+1)*gDimensionsDesCases.y);
        pJouerTexte[i] = new Text();
        pJouerTexte[i]->setFont(*pPolice);
        pJouerTexte[i]->setColor(Color::Black);
        pJouerTexte[i]->setCharacterSize(gDimensionsDesCases.x/2);
        pJouerTexte[i]->setString(gJouerTexte);
        pJouerTexte[i]->setPosition(pJouerBouton[i]->getPosition().x+pJouerBouton[i]->getSize().x/2-pJouerTexte[i]->getGlobalBounds().width/2, pJouerBouton[i]->getPosition().y+pJouerBouton[i]->getSize().y/2-pJouerTexte[i]->getGlobalBounds().height/2);
        pJouerChronometre[i] = new Chronometre(500000);
    }

    pQuitterBouton = new RectangleShape();
    pQuitterBouton->setOutlineThickness(-1);
    pQuitterBouton->setOutlineColor(Color::Black);
    pQuitterBouton->setSize(Vector2f(4*gDimensionsDesCases.x, 2*gDimensionsDesCases.y));
    pQuitterBouton->setFillColor(Color::White);
    pQuitterBouton->setPosition(8*gDimensionsDesCases.x, 15*gDimensionsDesCases.y);
    pQuitterTexte = new Text();
    pQuitterTexte->setFont(*pPolice);
    pQuitterTexte->setColor(Color::Black);
    pQuitterTexte->setCharacterSize(gDimensionsDesCases.x/2);
    pQuitterTexte->setString("Quitter");
    pQuitterTexte->setPosition(pQuitterBouton->getPosition().x+pQuitterBouton->getSize().x/2-pQuitterTexte->getGlobalBounds().width/2, pQuitterBouton->getPosition().y+pQuitterBouton->getSize().y/2-pQuitterTexte->getGlobalBounds().height/2);
    pQuitterChronometre = new Chronometre(500000);

    pSon = new Music();
    pSon->openFromFile("Ressources/Bouton.wav");
    pMusique = new Music();
    pMusique->openFromFile("Ressources/Musique.wav");
    pMusique->setLoop(true);
    pMusique->play();

    for (int i = 0; i < pNombreDeCases.x; i++)
    {
        for (int j = 0; j < pNombreDeCases.y; j++)
        {
            pDecor->SetT(Vector2f(i, j), new Decor("Ressources/Menu.bmp", gDimensionsDesCases, Vector2f(i, j), this));
        }
    }
}

Menu::~Menu()
{
    delete pPolice;

    delete pTexte;

    for (int i = 0; i < 4; i++)
    {
        delete pJouerBouton[i];
        delete pJouerTexte[i];
        delete pJouerChronometre[i];
    }

    delete pQuitterBouton;
    delete pQuitterTexte;
    delete pQuitterChronometre;

    delete pSon;
    delete pMusique;
}

void Menu::Afficher(RenderWindow *gFenetrePrincipale)
{
    for (int i = 0; i < 4; i++)
    {
        pJouerChronometre[i]->Chronometrer(false);
    }

    pQuitterChronometre->Chronometrer(false);

    Zone::Afficher(gFenetrePrincipale);

    gFenetrePrincipale->draw(*pTexte);

    for (int i = 0; i < 4; i++)
    {
        gFenetrePrincipale->draw(*pJouerBouton[i]);
        gFenetrePrincipale->draw(*pJouerTexte[i]);
    }

    gFenetrePrincipale->draw(*pQuitterBouton);
    gFenetrePrincipale->draw(*pQuitterTexte);

    return;
}

void Menu::Action(Evenement *gEvenement, Zone *gZone, int *gAction)
{
    for (int i = 0; i < 4; i++)
    {
        if (pJouerChronometre[i]->Depasser() == true && gEvenement->GetClicGauche() == true && gEvenement->GetClicPosition().x > pJouerBouton[i]->getGlobalBounds().left+0 && gEvenement->GetClicPosition().x < pJouerBouton[i]->getGlobalBounds().left+pJouerBouton[i]->getGlobalBounds().width+0 && gEvenement->GetClicPosition().y > pJouerBouton[i]->getGlobalBounds().top+0 && gEvenement->GetClicPosition().y < pJouerBouton[i]->getGlobalBounds().top+pJouerBouton[i]->getGlobalBounds().height+0)
        {
            pJouerChronometre[i]->Redemarrer();

            pSon->stop();
            pSon->play();

            gZone->Reinitialiser(i+1);

            *gAction = 2;
        }
    }

    if (pQuitterChronometre->Depasser() == true && gEvenement->GetClicGauche() == true && gEvenement->GetClicPosition().x > pQuitterBouton->getGlobalBounds().left+0 && gEvenement->GetClicPosition().x < pQuitterBouton->getGlobalBounds().left+pQuitterBouton->getGlobalBounds().width+0 && gEvenement->GetClicPosition().y > pQuitterBouton->getGlobalBounds().top+0 && gEvenement->GetClicPosition().y < pQuitterBouton->getGlobalBounds().top+pQuitterBouton->getGlobalBounds().height+0)
    {
        pQuitterChronometre->Redemarrer();

        pSon->stop();
        pSon->play();
        pMusique->stop();

        *gAction = 0;
    }

    return;
}
