#ifndef ASTAR_HPP_INCLUDED
#define ASTAR_HPP_INCLUDED

class Objet;

class AStar
{
    public :

    AStar(Vector2f gNombreDeCases, Vector2f gDestination);
    ~AStar();

    void Chercher(Objet *gObjet, Grille <Objet*> *gOccupationObjet);

    protected :

    Vector2f pNombreDeCases;
    Vector2f pDestination;

    Grille <Objet*> *pOccupation;
    Grille <bool> *pListeOuverte;
    Grille <bool> *pListeFermee;
    Grille <int> *pDistanceF;
    Grille <int> *pDistanceG;
    Grille <int> *pDistanceH;
    Grille <Vector2f> *pCoordonneesParents;
};

#endif // ASTAR_HPP_INCLUDED
