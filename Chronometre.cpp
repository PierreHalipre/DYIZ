#include "main.hpp"

Chronometre::Chronometre(int gTempsLimite)
{
    pTemps = 0;
    pTempsLimite = gTempsLimite;
    pTempsAttente = 0;
    pAttente = false;

    pHorlogeTemps = Clock();
    pHorlogeAttente = Clock();
}

Chronometre::~Chronometre()
{

}

void Chronometre::Chronometrer(bool gAttente)
{
    pAttente = gAttente;

    if (pAttente == true)
    {
        pTemps += pHorlogeTemps.getElapsedTime().asMicroseconds();
        pTempsAttente += pHorlogeAttente.getElapsedTime().asMicroseconds();

        pHorlogeTemps.restart();
        pHorlogeAttente.restart();
    }

    else
    {
        pTemps += pHorlogeTemps.getElapsedTime().asMicroseconds();

        pHorlogeTemps.restart();
        pHorlogeAttente.restart();
    }

    return;
}

void Chronometre::Redemarrer()
{
    pTemps = 0;
    pTempsAttente = 0;
    pAttente = false;

    pHorlogeTemps.restart();
    pHorlogeAttente.restart();

    return;
}

bool Chronometre::Depasser()
{
    if (pTemps-pTempsAttente > pTempsLimite)
    {
        return true;
    }

    else
    {
        return false;
    }
}
