#include "main.hpp"

Tir::Tir(String gNomDuFichierImage, Vector2f gDimensionsDesCases, Vector2f gPosition, Vector2f gSens, Zone *gZone) : Objet(gNomDuFichierImage, gDimensionsDesCases, gPosition, gZone)
{
    pDeplace = true;

    pDeplacement = 0;

    pSens = gSens;

    pAnimation = new Chronometre(500);

    pZone->GetObjet()->SetT(pPosition, NULL);
}

Tir::~Tir()
{
    delete pAnimation;
}

void Tir::Afficher(RenderWindow *gFenetrePrincipale, bool gPause)
{
    pAnimation->Chronometrer(gPause);

    this->Deplacer();

    if (pDeplace == true)
    {
        Objet::Afficher(gFenetrePrincipale);
    }

    return;
}

void Tir::Deplacer()
{
    if (pZone->GetBarricade() > 0 && pDeplace == true && pAnimation->Depasser())
    {
        pAnimation->Redemarrer();

        pSprite->move(pSens);

        if (pSprite->getPosition().x < 0 || pSprite->getPosition().x >= 640)
        {
            pDeplace = false;
        }
    }

    return;
}
