#include "main.hpp"

Personnage::Personnage(String gNomDuFichierImage, Vector2f gDimensionsDesCases, Vector2f gPosition, Vector2f gSens, Zone *gZone) : Objet(gNomDuFichierImage, gDimensionsDesCases, gPosition, gZone)
{
    pType = gPosition.x;

    pSprite->setTextureRect(IntRect(0, 2*pType*gDimensionsDesCases.y, gDimensionsDesCases.x, gDimensionsDesCases.y));

    pDegat = 1;

    pDeplace = false;
    pTire = false;
    pBloque = false;

    pDeplacement = 0;

    pSens = gSens;

    pAnimation = new Chronometre(5000);
    pCadenceDeTir = new Chronometre(500000);
    pBlocage = new Chronometre(2000000);

    char pTypeSon[256] = "";
    sprintf(pTypeSon, "Ressources/Personnage_%d.wav", int(gPosition.x)+1);
    pSon = pTypeSon;

    pTir = new deque <Tir*>();

    this->Positionner(pPosition);
}

Personnage::~Personnage()
{
    delete pAnimation;
    delete pCadenceDeTir;
    delete pBlocage;

    delete pTir;
}

void Personnage::Afficher(RenderWindow *gFenetrePrincipale, bool gPause)
{
    pAnimation->Chronometrer(gPause);
    pCadenceDeTir->Chronometrer(gPause);
    pBlocage->Chronometrer(gPause);

    if (pBlocage->Depasser() == true)
    {
        pBloque = false;
    }

    if (pBloque == false && pTire == true && pZone->GetBarricade() > 0)
    {
        this->Tirer();
    }

    for (unsigned int i = 0; i < pTir->size(); i++)
    {
        if (pTir->at(i) != NULL)
        {
            if (pTir->at(i)->GetDeplace() == true)
            {
                pTir->at(i)->Afficher(gFenetrePrincipale, gPause);
            }

            else
            {
                delete pTir->at(i);

                pTir->erase(pTir->begin()+i);

                i = 0;
            }
        }
    }

    if (pBloque == true)
    {
        pSprite->setTextureRect(IntRect(int(pDeplacement*4/pSprite->getTextureRect().width)*pSprite->getTextureRect().width, 2*pType*pSprite->getTextureRect().height+pSprite->getTextureRect().height, pSprite->getTextureRect().width, pSprite->getTextureRect().height));
    }

    else
    {
        pSprite->setTextureRect(IntRect(int(pDeplacement*4/pSprite->getTextureRect().width)*pSprite->getTextureRect().width, 2*pType*pSprite->getTextureRect().height, pSprite->getTextureRect().width, pSprite->getTextureRect().height));
    }

    if (pBloque == false && pZone->GetBarricade() > 0 && pDeplace == true && pAnimation->Depasser())
    {
        pAnimation->Redemarrer();

        if (pSprite->getPosition().x+pSens.x >= 0 && pSprite->getPosition().x+pSprite->getTextureRect().width*pSens.x < pZone->GetNombreDeCases().x*pZone->GetDimensionsDesCases().x && pSprite->getPosition().y+pSens.y >= 0 && pSprite->getPosition().y+pSprite->getTextureRect().height*pSens.y < pZone->GetNombreDeCases().y*pZone->GetDimensionsDesCases().y)
        {
            Vector2f gSuivante;

            if (pSens.x < 0)
            {
                gSuivante.x = pPosition.x-1;
            }

            else if (pSens.x > 0)
            {
                gSuivante.x = pPosition.x+1;
            }

            else
            {
                gSuivante.x = pPosition.x;
            }

            if (pSens.y < 0)
            {
                gSuivante.y = pPosition.y-1;
            }

            else if (pSens.y > 0)
            {
                gSuivante.y = pPosition.y+1;
            }

            else
            {
                gSuivante.y = pPosition.y;
            }

            if (pZone->GetDecor()->GetT(gSuivante)->GetBarricade() == false && (pZone->GetObjet()->GetT(gSuivante) == this || pZone->GetObjet()->GetT(gSuivante) == NULL))
            {
                if (pDeplacement < pSprite->getTextureRect().width)
                {
                    pZone->GetObjet()->SetT(gSuivante, this);

                    pSprite->move(pSens);

                    pDeplacement++;
                }

                if (pDeplacement == pSprite->getTextureRect().width)
                {
                    this->Positionner(gSuivante);

                    pDeplace = false;

                    pDeplacement = 0;
                }
            }

            pSprite->setTextureRect(IntRect(int(pDeplacement*4/pSprite->getTextureRect().width)*pSprite->getTextureRect().width, 2*pType*pSprite->getTextureRect().height, pSprite->getTextureRect().width, pSprite->getTextureRect().height));
        }
    }

    Objet::Afficher(gFenetrePrincipale);

    return;
}

void Personnage::Deplacer(Vector2f gSens)
{
    pSens = gSens;

    return;
}

void Personnage::Tirer()
{
    pTire = false;

    if (pCadenceDeTir->Depasser())
    {
        pCadenceDeTir->Redemarrer();

        pTir->push_front(new Tir("Ressources/Tir.bmp", Vector2f(pSprite->getGlobalBounds().width, pSprite->getGlobalBounds().height), Vector2f(pSprite->getPosition().x/pSprite->getGlobalBounds().width, pSprite->getPosition().y/pSprite->getGlobalBounds().height), Vector2f(1, 0), pZone));

        pZone->GetObjet()->SetT(pPosition, this);
    }

    return;
}

bool Personnage::Toucher(Objet *gObjet)
{
    bool Condition = false;

    if (gObjet->GetTir()->empty() == false)
    {
        for (unsigned int i = 0; i < gObjet->GetTir()->size(); i++)
        {
            if (gObjet->GetTir()->at(i) != NULL && gObjet->GetTir()->at(i)->GetDeplace() == true && gObjet->GetTir()->at(i)->GetSprite()->getGlobalBounds().intersects(pSprite->getGlobalBounds()) == true)
            {
                pBloque = true;

                pBlocage->Redemarrer();

                delete gObjet->GetTir()->at(i);

                gObjet->GetTir()->erase(gObjet->GetTir()->begin()+i);

                i = 0;

                Condition = true;
            }
        }
    }

    return Condition;
}

void Personnage::Reinitialiser()
{
    pDeplace = false;
    pTire = false;
    pBloque = false;

    pDeplacement = 0;

    pSens = Vector2f(0, 0);

    pAnimation->Redemarrer();
    pCadenceDeTir->Redemarrer();

    return;
}
