#include "main.hpp"

Ennemi::Ennemi(String gNomDuFichierImage, Vector2f gDimensionsDesCases, Vector2f gPosition, Zone *gZone) : Objet(gNomDuFichierImage, gDimensionsDesCases, gPosition, gZone)
{
    pAttaque = false;
    pDeplace = false;

    pType = rand()%4;

    pVie = pType+1;
    pVieInitiale = pVie;
    pDegat = pType+1;
    pVitesse = (pType+1)*10000;

    pSprite->setTextureRect(IntRect(0, 2*pType*gDimensionsDesCases.y, gDimensionsDesCases.x, gDimensionsDesCases.y));

    pDeplacement = 0;

    pRectangleVieContour.setOutlineColor(Color::Black);
    pRectangleVieContour.setOutlineThickness(-1);
    pRectangleVieContour.setPosition(Vector2f(gPosition.x*gDimensionsDesCases.x, gPosition.y*gDimensionsDesCases.y));
    pRectangleVieContour.setSize(Vector2f(gDimensionsDesCases.x, gDimensionsDesCases.y/10));
    pRectangleVieContour.setFillColor(Color::Red);
    pRectangleVie.setFillColor(Color::Transparent);
    pRectangleVie.setOutlineColor(Color::Black);
    pRectangleVie.setOutlineThickness(-1);
    pRectangleVie.setPosition(Vector2f(gPosition.x*gDimensionsDesCases.x, gPosition.y*gDimensionsDesCases.y));
    pRectangleVie.setSize(Vector2f(gDimensionsDesCases.x, gDimensionsDesCases.y/10));
    pRectangleVie.setFillColor(Color::Green);

    char pTypeSon[256] = "";
    sprintf(pTypeSon, "Ressources/Ennemi_%d.wav", pType+1);
    pSon = pTypeSon;

    pChemin = new deque <Vector2f>();

    pAnimation = new Chronometre(pVitesse);

    this->Positionner(pPosition);
}

Ennemi::~Ennemi()
{
    delete pChemin;

    delete pAnimation;
}

void Ennemi::Afficher(RenderWindow *gFenetrePrincipale, bool gPause)
{
    pAnimation->Chronometrer(gPause);

    if (pZone->GetBarricade() > 0 && pAnimation->Depasser() == true)
    {
        pAnimation->Redemarrer();

        if (pAttaque == true)
        {
            if (pDeplacement < pSprite->getTextureRect().width)
            {
                pDeplacement++;
            }

            if (pDeplacement == pSprite->getTextureRect().width)
            {
                pZone->GetDecor()->GetT(pChemin->front())->Subir(this);

                pAttaque = false;

                pDeplacement = 0;
            }

            pSprite->setTextureRect(IntRect(int(pDeplacement*4/pSprite->getTextureRect().width)*pSprite->getTextureRect().width, (2*pType+1)*pSprite->getTextureRect().height, pSprite->getTextureRect().width, pSprite->getTextureRect().height));
        }

        else if (pDeplace == true)
        {
            if (pDeplacement < pSprite->getTextureRect().width)
            {
                pZone->GetObjet()->SetT(pChemin->front(), this);

                Vector2f gSens = Vector2f((pChemin->front().x-pPosition.x)/abs(pChemin->front().x-pPosition.x), (pChemin->front().y-pPosition.y)/abs(pChemin->front().y-pPosition.y));

                if (isnan(gSens.x) == true)
                {
                    gSens.x = 0;
                }

                if (isnan(gSens.y) == true)
                {
                    gSens.y = 0;
                }

                pSprite->move(gSens);
                pRectangleVieContour.move(gSens);
                pRectangleVie.move(gSens);

                pDeplacement++;
            }

            if (pDeplacement == pSprite->getTextureRect().width)
            {
                this->Positionner(pChemin->front());

                pChemin->pop_front();

                pDeplace = false;

                pDeplacement = 0;
            }

            pSprite->setTextureRect(IntRect(int(pDeplacement*4/pSprite->getTextureRect().width)*pSprite->getTextureRect().width, pSprite->getTextureRect().top, pSprite->getTextureRect().width, pSprite->getTextureRect().height));
        }

        else if (pZone->GetObjet()->GetT(pChemin->front()) != NULL && pDeplacement == 0)
        {
            this->Deplacer(pChemin->back());
        }

        else if (pZone->GetDecor()->GetT(pChemin->front())->GetBarricade() == false)
        {
            pDeplace = true;
        }

        else if (pZone->GetDecor()->GetT(pChemin->front())->GetBarricade() == true)
        {
            pAttaque = true;
        }
    }

    Objet::Afficher(gFenetrePrincipale);

    gFenetrePrincipale->draw(pRectangleVieContour);
    gFenetrePrincipale->draw(pRectangleVie);

    return;
}

void Ennemi::Subir(Objet *gObjet)
{
    if (gObjet->GetTir()->empty() == false)
    {
        for (unsigned int i = 0; i < gObjet->GetTir()->size(); i++)
        {
            if (gObjet->GetTir()->at(i) != NULL && gObjet->GetTir()->at(i)->GetDeplace() == true && gObjet->GetTir()->at(i)->GetSprite()->getGlobalBounds().intersects(pSprite->getGlobalBounds()) == true)
            {
                pVie -= gObjet->GetDegat();

                pRectangleVie.setSize(Vector2f(pRectangleVieContour.getSize().x*pVie/pVieInitiale, pRectangleVie.getSize().y));

                delete gObjet->GetTir()->at(i);

                gObjet->GetTir()->erase(gObjet->GetTir()->begin()+i);

                i = 0;
            }
        }
    }

    return;
}

void Ennemi::Deplacer(Vector2f gDestination)
{
    if (pDeplacement == 0)
    {
        AStar *gAStar = new AStar(pZone->GetNombreDeCases(), gDestination);
        gAStar->Chercher(this, pZone->GetObjet());
    }

    return;
}
