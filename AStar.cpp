#include "main.hpp"

AStar::AStar(Vector2f gNombreDeCases, Vector2f gDestination)
{
    pNombreDeCases = gNombreDeCases;
    pDestination = gDestination;

    pOccupation = new Grille <Objet*>(pNombreDeCases);
    pListeOuverte = new Grille <bool>(pNombreDeCases);
    pListeFermee = new Grille <bool>(pNombreDeCases);
    pDistanceF = new Grille <int>(pNombreDeCases);
    pDistanceG = new Grille <int>(pNombreDeCases);
    pDistanceH = new Grille <int>(pNombreDeCases);
    pCoordonneesParents = new Grille <Vector2f>(pNombreDeCases);

    for (int X = 0; X < pNombreDeCases.x; X++)
    {
        for (int Y = 0; Y < pNombreDeCases.y; Y++)
        {
            pOccupation->SetT(Vector2f(X, Y), NULL);
            pListeOuverte->SetT(Vector2f(X, Y), false);
            pListeFermee->SetT(Vector2f(X, Y), false);
            pDistanceF->SetT(Vector2f(X, Y), 0);
            pDistanceG->SetT(Vector2f(X, Y), 0);
            pDistanceH->SetT(Vector2f(X, Y), 0);
            pCoordonneesParents->SetT(Vector2f(X, Y), Vector2f(0, 0));
        }
    }
}

AStar::~AStar()
{
    delete pOccupation;
    delete pListeOuverte;
    delete pListeFermee;
    delete pDistanceF;
    delete pDistanceG;
    delete pDistanceH;
    delete pCoordonneesParents;
}

void AStar::Chercher(Objet *gObjet, Grille <Objet*> *gOccupationObjet)
{
    gObjet->GetChemin()->clear();

    Vector2f gMeilleure = gObjet->GetPosition();
    Vector2f gMeilleureDestination = gObjet->GetPosition();

    pListeOuverte->SetT(gMeilleure, true);
    pListeFermee->SetT(gMeilleure, false);
    pDistanceG->SetT(gMeilleure, false);
    pDistanceH->SetT(gMeilleure, pow(pDestination.x-gMeilleure.x, 2)+pow(pDestination.y-gMeilleure.y, 2));
    pDistanceF->SetT(gMeilleure, pDistanceG->GetT(gMeilleure)+pDistanceH->GetT(gMeilleure));
    pCoordonneesParents->SetT(gMeilleure, gMeilleure);

    int gMeilleureDistanceH = 2147483647;

    while (gMeilleure != pDestination)
    {
        pListeOuverte->SetT(gMeilleure, false);
        pListeFermee->SetT(gMeilleure, true);

        for (int X = gMeilleure.x-1; X <= gMeilleure.x+1; X++)
        {
            for (int Y = gMeilleure.y-1; Y <= gMeilleure.y+1; Y++)
            {
                if (X >= 0 && X < pNombreDeCases.x && Y >= 0 && Y < pNombreDeCases.y && !(X == gMeilleure.x && Y == gMeilleure.y) && !(X == gMeilleure.x-1 && Y == gMeilleure.y-1) && !(X == gMeilleure.x-1 && Y == gMeilleure.y+1) && !(X == gMeilleure.x+1 && Y == gMeilleure.y-1) && !(X == gMeilleure.x+1 && Y == gMeilleure.y+1))
                {
                    if (gOccupationObjet->GetT(Vector2f(X, Y)) == NULL)
                    {
                        if (pListeOuverte->GetT(Vector2f(X, Y)) == false && pListeFermee->GetT(Vector2f(X, Y)) == false)
                        {
                            pListeOuverte->SetT(Vector2f(X, Y), true);

                            pDistanceG->SetT(Vector2f(X, Y), pDistanceG->GetT(gMeilleure)+pow(gMeilleure.x-Vector2f(X, Y).x, 2)+pow(gMeilleure.y-Vector2f(X, Y).y, 2));
                            pDistanceH->SetT(Vector2f(X, Y), pow(pDestination.x-Vector2f(X, Y).x, 2)+pow(pDestination.y-Vector2f(X, Y).y, 2));
                            pDistanceF->SetT(Vector2f(X, Y), pDistanceG->GetT(Vector2f(X, Y))+pDistanceH->GetT(Vector2f(X, Y)));
                            pCoordonneesParents->SetT(Vector2f(X, Y), gMeilleure);

                            if (pDistanceH->GetT(Vector2f(X, Y)) < gMeilleureDistanceH)
                            {
                                gMeilleureDistanceH = pDistanceH->GetT(Vector2f(X, Y));

                                gMeilleureDestination = Vector2f(X, Y);
                            }
                        }
                    }
                }
            }
        }

        int gMeilleureDistanceF = 2147483647;

        for (int X = 0; X < pNombreDeCases.x; X++)
        {
            for (int Y = 0; Y < pNombreDeCases.y; Y++)
            {
                if (pListeOuverte->GetT(Vector2f(X, Y)) == true && pDistanceF->GetT(Vector2f(X, Y)) < gMeilleureDistanceF)
                {
                    gMeilleureDistanceF = pDistanceF->GetT(Vector2f(X, Y));

                    gMeilleure = Vector2f(X, Y);
                }
            }
        }

        if (gMeilleureDistanceF == 2147483647)
        {
            gMeilleure = gMeilleureDestination;
            pDestination = gMeilleureDestination;
        }
    }

    while (gMeilleure != gObjet->GetPosition())
    {
        gObjet->GetChemin()->push_front(gMeilleure);

        gMeilleure = pCoordonneesParents->GetT(gMeilleure);
    }

    return;
}
