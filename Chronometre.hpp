#ifndef CHRONOMETRE_HPP_INCLUDED
#define CHRONOMETRE_HPP_INCLUDED

#include "main.hpp"

class Chronometre
{
    public :

    Chronometre(int gTempsLimite);
    ~Chronometre();

    void Chronometrer(bool gAttente);
    void Demarrer(bool gDemarre);
    void Redemarrer();
    bool Depasser();

    int GetTemps() {return pTemps;}
    void SetTemps(int gTemps) {pTemps = gTemps;}
    int GetTempsLimite() {return pTempsLimite;}
    void SetTempsLimite(int gTempsLimite) {pTempsLimite = gTempsLimite;}
    int GetTempsAttente() {return pTempsAttente;}
    void SetTempsAttente(int gTempsAttente) {pTempsAttente = gTempsAttente;}
    bool GetAttente() {return pAttente;}
    void SetAttente(bool gAttente) {pAttente = gAttente;}

    Clock* GetHorlogeTemps() {return &pHorlogeTemps;}
    void SetHorlogeTemps(Clock gHorlogeTemps) {pHorlogeTemps = gHorlogeTemps;}
    Clock* GetHorlogeAttente() {return &pHorlogeAttente;}
    void SetHorlogeAttente(Clock gHorlogeAttente) {pHorlogeAttente = gHorlogeAttente;}

    protected :

    int pTemps;
    int pTempsLimite;
    int pTempsAttente;
    bool pAttente;

    Clock pHorlogeTemps;
    Clock pHorlogeAttente;
};

#endif // CHRONOMETRE_HPP_INCLUDED
