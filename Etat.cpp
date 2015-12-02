#include "main.hpp"

Etat::Etat(Vector2f gDimensionsDesCases, Vector2f gNombreDeCases) : Zone(gDimensionsDesCases, gNombreDeCases)
{
    pPolice = new Font();
    pPolice->loadFromFile("Ressources/cour.ttf");

    pTexte = new Text();
    pTexte->setFont(*pPolice);
    pTexte->setColor(Color::Black);
    pTexte->setCharacterSize(gDimensionsDesCases.x/2);
    pTexte->setString("Barricade : \nScore     : ");
    pTexte->setPosition(Vector2f(gDimensionsDesCases.x*gNombreDeCases.x/2-pTexte->getGlobalBounds().width/2, gDimensionsDesCases.y*2/2-pTexte->getGlobalBounds().height/2));

    pPauseBouton = new RectangleShape();
    pPauseBouton->setOutlineThickness(-1);
    pPauseBouton->setOutlineColor(Color::Black);
    pPauseBouton->setSize(Vector2f(4*gDimensionsDesCases.x, 2*gDimensionsDesCases.y));
    pPauseBouton->setFillColor(Color::White);
    pPauseBouton->setPosition(4*gDimensionsDesCases.x, 2*gDimensionsDesCases.y);
    pPauseTexte = new Text();
    pPauseTexte->setFont(*pPolice);
    pPauseTexte->setColor(Color::Black);
    pPauseTexte->setCharacterSize(gDimensionsDesCases.x/2);
    pPauseTexte->setString("Pause");
    pPauseTexte->setPosition(pPauseBouton->getPosition().x+pPauseBouton->getSize().x/2-pPauseTexte->getGlobalBounds().width/2, pPauseBouton->getPosition().y+pPauseBouton->getSize().y/2-pPauseTexte->getGlobalBounds().height/2);
    pPauseChronometre = new Chronometre(500000);

    pQuitterBouton = new RectangleShape();
    pQuitterBouton->setOutlineThickness(-1);
    pQuitterBouton->setOutlineColor(Color::Black);
    pQuitterBouton->setSize(Vector2f(4*gDimensionsDesCases.x, 2*gDimensionsDesCases.y));
    pQuitterBouton->setFillColor(Color::White);
    pQuitterBouton->setPosition(12*gDimensionsDesCases.x, 2*gDimensionsDesCases.y);
    pQuitterTexte = new Text();
    pQuitterTexte->setFont(*pPolice);
    pQuitterTexte->setColor(Color::Black);
    pQuitterTexte->setCharacterSize(gDimensionsDesCases.x/2);
    pQuitterTexte->setString("Quitter");
    pQuitterTexte->setPosition(pQuitterBouton->getPosition().x+pQuitterBouton->getSize().x/2-pQuitterTexte->getGlobalBounds().width/2, pQuitterBouton->getPosition().y+pQuitterBouton->getSize().y/2-pQuitterTexte->getGlobalBounds().height/2);
    pQuitterChronometre = new Chronometre(500000);

    pSon = new Music();
    pSon->openFromFile("Ressources/Bouton.wav");

    pTransformation = new Transform();
    pTransformation->translate(Vector2f(0, 480));
    pEtat = new RenderStates(*pTransformation);

    for (int i = 0; i < pNombreDeCases.x; i++)
    {
        for (int j = 0; j < pNombreDeCases.y; j++)
        {
            pDecor->SetT(Vector2f(i, j), new Decor("Ressources/Etat.bmp", gDimensionsDesCases, Vector2f(i, j), this));
        }
    }
}

Etat::~Etat()
{
    delete pPolice;

    delete pTexte;

    delete pPauseBouton;
    delete pPauseTexte;
    delete pPauseChronometre;

    delete pQuitterBouton;
    delete pQuitterTexte;
    delete pQuitterChronometre;

    delete pSon;

    delete pTransformation;
    delete pEtat;
}

void Etat::Afficher(RenderWindow *gFenetrePrincipale)
{
    pPauseChronometre->Chronometrer(false);

    pQuitterChronometre->Chronometrer(false);

    for (int i = 0; i < pNombreDeCases.x; i++)
    {
        for (int j = 0; j < pNombreDeCases.y; j++)
        {
            gFenetrePrincipale->draw(*pDecor->GetT(Vector2f(i, j))->GetSprite(), *pEtat);
        }
    }

    gFenetrePrincipale->draw(*pTexte, *pEtat);

    gFenetrePrincipale->draw(*pPauseBouton, *pEtat);
    gFenetrePrincipale->draw(*pPauseTexte, *pEtat);

    gFenetrePrincipale->draw(*pQuitterBouton, *pEtat);
    gFenetrePrincipale->draw(*pQuitterTexte, *pEtat);

    return;
}

void Etat::Action(Evenement *gEvenement, Zone *gZone, int *gAction)
{
    char gTexte[128];
    sprintf(gTexte, "Barricade : %d\nScore     : %d", gZone->GetBarricade(), gZone->GetScore());
    pTexte->setString(gTexte);

    if (pPauseChronometre->Depasser() == true && gZone->GetPause() == false && gEvenement->GetClicGauche() == true && gEvenement->GetClicPosition().x > pPauseBouton->getGlobalBounds().left+0 && gEvenement->GetClicPosition().x < pPauseBouton->getGlobalBounds().left+pPauseBouton->getGlobalBounds().width+0 && gEvenement->GetClicPosition().y > pPauseBouton->getGlobalBounds().top+480 && gEvenement->GetClicPosition().y < pPauseBouton->getGlobalBounds().top+pPauseBouton->getGlobalBounds().height+480)
    {
        pPauseChronometre->Redemarrer();

        pSon->stop();
        pSon->play();

        gZone->SetPause(true);
    }

    else if (pPauseChronometre->Depasser() == true && gZone->GetPause() == true && gEvenement->GetClicGauche() == true && gEvenement->GetClicPosition().x > pPauseBouton->getGlobalBounds().left+0 && gEvenement->GetClicPosition().x < pPauseBouton->getGlobalBounds().left+pPauseBouton->getGlobalBounds().width+0 && gEvenement->GetClicPosition().y > pPauseBouton->getGlobalBounds().top+480 && gEvenement->GetClicPosition().y < pPauseBouton->getGlobalBounds().top+pPauseBouton->getGlobalBounds().height+480)
    {
        pPauseChronometre->Redemarrer();

        pSon->stop();
        pSon->play();

        gZone->SetPause(false);
    }

    if (pQuitterChronometre->Depasser() == true && gEvenement->GetClicGauche() == true && gEvenement->GetClicPosition().x > pQuitterBouton->getGlobalBounds().left+0 && gEvenement->GetClicPosition().x < pQuitterBouton->getGlobalBounds().left+pQuitterBouton->getGlobalBounds().width+0 && gEvenement->GetClicPosition().y > pQuitterBouton->getGlobalBounds().top+480 && gEvenement->GetClicPosition().y < pQuitterBouton->getGlobalBounds().top+pQuitterBouton->getGlobalBounds().height+480)
    {
        pQuitterChronometre->Redemarrer();

        pSon->stop();
        pSon->play();

        *gAction = 1;
    }

    return;
}
