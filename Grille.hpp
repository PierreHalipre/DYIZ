#ifndef GRILLE_HPP_INCLUDED
#define GRILLE_HPP_INCLUDED

#include "main.hpp"

template <typename T>

class Grille
{
    public :

    Grille(Vector2f gNombreDeCases);
    ~Grille();

    Vector2f GetNombreDeCases() {return pNombreDeCases;}
    void SetNombreDeCases(Vector2f gNombreDeCases) {pNombreDeCases = gNombreDeCases;}

    T GetT(Vector2f gPosition) {return pT[int(gPosition.x)][int(gPosition.y)];}
    void SetT(Vector2f gPosition, T gT) {pT[int(gPosition.x)][int(gPosition.y)] = gT;}

    protected :

    Vector2f pNombreDeCases;

    T **pT;
};

template <typename T>

Grille<T>::Grille(Vector2f gNombreDeCases)
{
    pNombreDeCases = gNombreDeCases;

    pT = new T*[int(pNombreDeCases.x)];

    for (unsigned int X = 0; X < pNombreDeCases.x; X++)
    {
        pT[X] = new T[int(pNombreDeCases.y)];

        for (unsigned int Y = 0; Y < pNombreDeCases.y; Y++)
        {
            pT[X][Y] = T();
        }
    }
}

template <typename T>

Grille<T>::~Grille()
{
    for (unsigned int X = 0; X < pNombreDeCases.x; X++)
    {
        delete[] pT[X];
    }

    delete[] pT;
}

#endif // GRILLE_HPP_INCLUDED
