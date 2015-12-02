#include "main.hpp"

Carte::Carte(Vector2f gDimensionsDesCases, Vector2f gNombreDeCases, int gNombreDePersonnages) : Zone(gDimensionsDesCases, gNombreDeCases)
{
    pPause = false;
    pFin = false;

    pNombreDePersonnages = gNombreDePersonnages;

    pBarricade = 100;

    pPolice = new Font();
    pPolice->loadFromFile("Ressources/cour.ttf");

    pFinBouton = new RectangleShape();
    pFinBouton->setOutlineThickness(-1);
    pFinBouton->setOutlineColor(Color::Black);
    pFinBouton->setSize(Vector2f(4*gDimensionsDesCases.x, 2*gDimensionsDesCases.y));
    pFinBouton->setFillColor(Color::White);
    pFinBouton->setPosition(8*gDimensionsDesCases.x, 6*gDimensionsDesCases.y);
    pFinTexte = new Text();
    pFinTexte->setFont(*pPolice);
    pFinTexte->setColor(Color::Black);
    pFinTexte->setCharacterSize(gDimensionsDesCases.x/2);
    pFinTexte->setString("Rejouer");
    pFinTexte->setPosition(pFinBouton->getPosition().x+pFinBouton->getSize().x/2-pFinTexte->getGlobalBounds().width/2, pFinBouton->getPosition().y+pFinBouton->getSize().y/2-pFinTexte->getGlobalBounds().height/2);
    pFinChronometre = new Chronometre(5000000);

    pSon = new Music();

    pPersonnage = new deque <Objet*>();
    pEnnemi = new deque <Objet*>();

    pApparition = new Chronometre(1000000);

    for (int i = 0; i < pNombreDeCases.x; i++)
    {
        for (int j = 0; j < pNombreDeCases.y; j++)
        {
            if (i == 4)
            {
                pDecor->SetT(Vector2f(i, j), new Decor("Ressources/Barricade.bmp", gDimensionsDesCases, Vector2f(i, j), this));
                pDecor->GetT(Vector2f(i, j))->SetBarricade(true);
            }

            else
            {
                pDecor->SetT(Vector2f(i, j), new Decor("Ressources/Herbe.bmp", gDimensionsDesCases, Vector2f(i, j), this));
            }

            pObjet->SetT(Vector2f(i, j), NULL);
        }
    }

    for (int i = 0; i < pNombreDePersonnages; i++)
    {
        pPersonnage->push_back(new Personnage("Ressources/Personnage.bmp", Vector2f(32, 32), Vector2f(i, i), Vector2f(0, 0), this));
    }
}

Carte::~Carte()
{
    delete pPolice;

    delete pFinBouton;
    delete pFinTexte;
    delete pFinChronometre;

    delete pSon;

    delete pPersonnage;
    delete pEnnemi;

    delete pApparition;
}

void Carte::Afficher(RenderWindow *gFenetrePrincipale)
{
    pFinChronometre->Chronometrer(false);

    pApparition->Chronometrer(pPause);

    Zone::Afficher(gFenetrePrincipale);

    for (unsigned int i = 0; i < pPersonnage->size(); i++)
    {
        pPersonnage->at(i)->Afficher(gFenetrePrincipale, pPause);
    }

    for (unsigned int i = 0; i < pEnnemi->size(); i++)
    {
        pEnnemi->at(i)->Afficher(gFenetrePrincipale, pPause);
    }

    if (pFin == true)
    {
        gFenetrePrincipale->draw(*pFinBouton);
        gFenetrePrincipale->draw(*pFinTexte);
    }

    return;
}

void Carte::Action(Evenement *gEvenement, int *gAction)
{
    if (pPause == false && pBarricade > 0)
    {
        Vector2f gSens[4];

        if (pNombreDePersonnages >= 1 && gEvenement->Deplacement1() == true)
        {
            pPersonnage->at(0)->SetDeplace(true);

            if (gEvenement->GetZ() == true && gEvenement->GetS() == true)
            {
                gSens[0].y = 0;
            }

            else if (gEvenement->GetZ() == true)
            {
                gSens[0].y = -1;
            }

            else if (gEvenement->GetS() == true)
            {
                gSens[0].y = 1;
            }

            if (gEvenement->GetD() == true && gEvenement->GetQ() == true)
            {
                gSens[0].x = 0;
            }

            else if (gEvenement->GetD() == true)
            {
                gSens[0].x = 1;
            }

            else if (gEvenement->GetQ() == true)
            {
                gSens[0].x = -1;
            }
        }

        if (pNombreDePersonnages >= 2 && gEvenement->Deplacement2() == true)
        {
            pPersonnage->at(1)->SetDeplace(true);

            if (gEvenement->GetT() == true && gEvenement->GetG() == true)
            {
                gSens[1].y = 0;
            }

            else if (gEvenement->GetT() == true)
            {
                gSens[1].y = -1;
            }

            else if (gEvenement->GetG() == true)
            {
                gSens[1].y = 1;
            }

            if (gEvenement->GetH() == true && gEvenement->GetF() == true)
            {
                gSens[1].x = 0;
            }

            else if (gEvenement->GetH() == true)
            {
                gSens[1].x = 1;
            }

            else if (gEvenement->GetF() == true)
            {
                gSens[1].x = -1;
            }
        }

        if (pNombreDePersonnages >= 3 && gEvenement->Deplacement3() == true)
        {
            pPersonnage->at(2)->SetDeplace(true);

            if (gEvenement->GetI() == true && gEvenement->GetK() == true)
            {
                gSens[2].y = 0;
            }

            else if (gEvenement->GetI() == true)
            {
                gSens[2].y = -1;
            }

            else if (gEvenement->GetK() == true)
            {
                gSens[2].y = 1;
            }

            if (gEvenement->GetL() == true && gEvenement->GetJ() == true)
            {
                gSens[2].x = 0;
            }

            else if (gEvenement->GetL() == true)
            {
                gSens[2].x = 1;
            }

            else if (gEvenement->GetJ() == true)
            {
                gSens[2].x = -1;
            }
        }

        if (pNombreDePersonnages >= 4 && gEvenement->Deplacement4() == true)
        {
            pPersonnage->at(3)->SetDeplace(true);

            if (gEvenement->Get8() == true && gEvenement->Get5() == true)
            {
                gSens[3].y = 0;
            }

            else if (gEvenement->Get8() == true)
            {
                gSens[3].y = -1;
            }

            else if (gEvenement->Get5() == true)
            {
                gSens[3].y = 1;
            }

            if (gEvenement->Get6() == true && gEvenement->Get4() == true)
            {
                gSens[3].x = 0;
            }

            else if (gEvenement->Get6() == true)
            {
                gSens[3].x = 1;
            }

            else if (gEvenement->Get4() == true)
            {
                gSens[3].x = -1;
            }
        }

        if (pNombreDePersonnages >= 1 && gEvenement->Tir1() == true)
        {
            pPersonnage->at(0)->SetTire(true);
        }

        if (pNombreDePersonnages >= 2 && gEvenement->Tir2() == true)
        {
            pPersonnage->at(1)->SetTire(true);
        }

        if (pNombreDePersonnages >= 3 && gEvenement->Tir3() == true)
        {
            pPersonnage->at(2)->SetTire(true);
        }

        if (pNombreDePersonnages >= 4 && gEvenement->Tir4() == true)
        {
            pPersonnage->at(3)->SetTire(true);
        }

        if (pNombreDePersonnages >= 1 && pPersonnage->at(0)->GetDeplace() == true && pPersonnage->at(0)->GetDeplacement() == 0)
        {
            pPersonnage->at(0)->Deplacer(gSens[0]);
        }

        if (pNombreDePersonnages >= 2 && pPersonnage->at(1)->GetDeplace() == true && pPersonnage->at(1)->GetDeplacement() == 0)
        {
            pPersonnage->at(1)->Deplacer(gSens[1]);
        }

        if (pNombreDePersonnages >= 3 && pPersonnage->at(2)->GetDeplace() == true && pPersonnage->at(2)->GetDeplacement() == 0)
        {
            pPersonnage->at(2)->Deplacer(gSens[2]);
        }

        if (pNombreDePersonnages >= 4 && pPersonnage->at(3)->GetDeplace() == true && pPersonnage->at(3)->GetDeplacement() == 0)
        {
            pPersonnage->at(3)->Deplacer(gSens[3]);
        }

        gSens[0].x = 0;
        gSens[0].y = 0;
        gSens[1].x = 0;
        gSens[1].y = 0;
        gSens[2].x = 0;
        gSens[2].y = 0;
        gSens[3].x = 0;
        gSens[3].y = 0;
    }

    if (pApparition->Depasser() && pBarricade > 0)
    {
        pApparition->Redemarrer();

        pEnnemi->push_front(new Ennemi("Ressources/Ennemi.bmp", Vector2f(32, 32), Vector2f(pNombreDeCases.x-1, rand()%int(pNombreDeCases.y)), this));
    }

    for (unsigned int i = 0; i < pPersonnage->size(); i++)
    {
        for (unsigned int j = 0; j < pPersonnage->size(); j++)
        {
            if (i != j)
            {
                if(pPersonnage->at(i)->Toucher(pPersonnage->at(j)) == true)
                {
                    pSon->openFromFile(pPersonnage->at(i)->GetSon());
                    pSon->stop();
                    pSon->play();
                }
            }
        }
    }

    for (unsigned int i = 0; i < pEnnemi->size(); i++)
    {
        for (unsigned int j = 0; j < pPersonnage->size(); j++)
        {
            pEnnemi->at(i)->Subir(pPersonnage->at(j));
        }

        if (pEnnemi->at(i)->GetVie() <= 0)
        {
            pScore += pEnnemi->at(i)->GetType()+1;

            pObjet->SetT(pEnnemi->at(i)->GetPosition(), NULL);

            if (pEnnemi->at(i)->GetChemin()->empty() == false && pEnnemi->at(i)->GetDeplace() == true)
            {
                pObjet->SetT(pEnnemi->at(i)->GetChemin()->front(), NULL);
            }

            pSon->openFromFile(pEnnemi->at(i)->GetSon());
            pSon->stop();
            pSon->play();

            delete pEnnemi->at(i);

            pEnnemi->erase(pEnnemi->begin()+i);

            i = 0;
        }

        else if (pEnnemi->at(i)->GetChemin()->empty() == true && pBarricade > 0)
        {
            pEnnemi->at(i)->Deplacer(Vector2f(4, rand()%int(pNombreDeCases.y)));
        }
    }

    if (pBarricade <= 0)
    {
        pPause = true;
        pFin = true;
    }

    if (pFin == true && pFinChronometre->Depasser() == true && gEvenement->GetClicGauche() == true && gEvenement->GetClicPosition().x > pFinBouton->getGlobalBounds().left+0 && gEvenement->GetClicPosition().x < pFinBouton->getGlobalBounds().left+pFinBouton->getGlobalBounds().width+0 && gEvenement->GetClicPosition().y > pFinBouton->getGlobalBounds().top+0 && gEvenement->GetClicPosition().y < pFinBouton->getGlobalBounds().top+pFinBouton->getGlobalBounds().height+0)
    {
        pFin = false;

        pSon->openFromFile("Ressources/Bouton.wav");
        pSon->stop();
        pSon->play();

        this->Reinitialiser(pNombreDePersonnages);
    }

    return;
}

void Carte::Subir(Objet *gObjet)
{
    pBarricade -= gObjet->GetDegat();

    pSon->openFromFile("Ressources/Attaque.wav");
    pSon->stop();
    pSon->play();

    if (pBarricade < 0)
    {
        pBarricade = 0;
    }

    return;
}

void Carte::Reinitialiser(int gNombreDePersonnages)
{
    pPause = false;
    pFin = false;

    pNombreDePersonnages = gNombreDePersonnages;

    pBarricade = 100;
    pScore = 0;

    for (unsigned int i = 0; i < pPersonnage->size(); i++)
    {
        for (unsigned int j = 0; j < pPersonnage->at(i)->GetTir()->size(); j++)
        {
            delete pPersonnage->at(i)->GetTir()->at(j);
        }

        pPersonnage->at(i)->GetTir()->clear();

        pObjet->SetT(pPersonnage->at(i)->GetPosition(), NULL);

        Vector2f gSuivante;

        if (pPersonnage->at(i)->GetSens().x < 0)
        {
            gSuivante.x = pPersonnage->at(i)->GetPosition().x-1;
        }

        else if (pPersonnage->at(i)->GetSens().x > 0)
        {
            gSuivante.x = pPersonnage->at(i)->GetPosition().x+1;
        }

        else
        {
            gSuivante.x = pPersonnage->at(i)->GetPosition().x;
        }

        if (pPersonnage->at(i)->GetSens().y < 0)
        {
            gSuivante.y = pPersonnage->at(i)->GetPosition().y-1;
        }

        else if (pPersonnage->at(i)->GetSens().y > 0)
        {
            gSuivante.y = pPersonnage->at(i)->GetPosition().y+1;
        }

        else
        {
            gSuivante.y = pPersonnage->at(i)->GetPosition().y;
        }

        if (gSuivante != Vector2f(0, 0) && pPersonnage->at(i)->GetDeplace() == true)
        {
            pObjet->SetT(gSuivante, NULL);
        }

        delete pPersonnage->at(i);
    }

    pPersonnage->clear();

    for (int i = 0; i < pNombreDePersonnages; i++)
    {
        pPersonnage->push_back(new Personnage("Ressources/Personnage.bmp", Vector2f(32, 32), Vector2f(i, i), Vector2f(0, 0), this));
    }

    for (unsigned int i = 0; i < pEnnemi->size(); i++)
    {
        pObjet->SetT(pEnnemi->at(i)->GetPosition(), NULL);

        if (pEnnemi->at(i)->GetChemin()->empty() == false && pEnnemi->at(i)->GetDeplace() == true)
        {
            pObjet->SetT(pEnnemi->at(i)->GetChemin()->front(), NULL);
        }

        delete pEnnemi->at(i);
    }

    pEnnemi->clear();

    pApparition->Redemarrer();

    return;
}
