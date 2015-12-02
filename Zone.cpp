#include "main.hpp"

Zone::Zone(Vector2f gDimensionsDesCases, Vector2f gNombreDeCases)
{
    pDimensionsDesCases = gDimensionsDesCases;
    pNombreDeCases = gNombreDeCases;

    pDecor = new Grille <Objet*>(pNombreDeCases);
    pObjet = new Grille <Objet*>(pNombreDeCases);
}

Zone::~Zone()
{
    delete pDecor;
    delete pObjet;
}

void Zone::Afficher(RenderWindow *gFenetrePrincipale)
{
    for (int i = 0; i < pNombreDeCases.x; i++)
    {
        for (int j = 0; j < pNombreDeCases.y; j++)
        {
            pDecor->GetT(Vector2f(i, j))->Afficher(gFenetrePrincipale);
        }
    }

    return;
}

void Zone::Action()
{
    return;
}
