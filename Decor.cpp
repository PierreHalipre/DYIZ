#include "main.hpp"

Decor::Decor(String gNomDuFichierImage, Vector2f gDimensionsDesCases, Vector2f gPosition, Zone *gZone) : Objet(gNomDuFichierImage, gDimensionsDesCases, gPosition, gZone)
{
    pBarricade = false;

    this->Positionner(pPosition);
}

Decor::~Decor()
{

}

void Decor::Afficher(RenderWindow *gFenetrePrincipale)
{
    Objet::Afficher(gFenetrePrincipale);

    return;
}

void Decor::Subir(Objet *gObjet)
{
    pZone->Subir(gObjet);

    return;
}

bool Decor::EstBarricade(Vector2f gPosition)
{
    if (pBarricade == true)
    {
        return true;
    }

    else
    {
        return false;
    }
}
