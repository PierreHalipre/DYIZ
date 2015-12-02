#ifndef CARTE_HPP_INCLUDED
#define CARTE_HPP_INCLUDED

class Carte : public Zone
{
    public :

    Carte(Vector2f gDimensionsDesCases, Vector2f gNombreDeCases, int gNombreDePersonnages);
    ~Carte();

    void Afficher(RenderWindow *gFenetrePrincipale);
    void Action(Evenement *gEvenement, int *gAction);
    void Subir(Objet *gObjet);
    void Reinitialiser(int gNombreDeJoueurs);

    bool GetPause() {return pPause;}
    void SetPause(bool gPause) {pPause = gPause;}
    bool GetFin() {return pFin;}
    void SetFin(bool gFin) {pFin = gFin;}

    int GetNombreDePersonnages() {return pNombreDePersonnages;}
    void SetNombreDePersonnages(int gNombreDePersonnages) {pNombreDePersonnages = gNombreDePersonnages;}

    int GetBarricade() {return pBarricade;}
    void SetBarricade(int gBarricade) {pBarricade = gBarricade;}
    int GetScore() {return pScore;}
    void SetScore(int gScore) {pScore = gScore;}

    deque <Objet*>* GetPersonnage() {return pPersonnage;}
    void SetPersonnage(deque <Objet*> *gPersonnage) {pPersonnage = gPersonnage;}

    protected :

    bool pPause;
    bool pFin;

    int pNombreDePersonnages;

    int pBarricade;
    int pScore;

    Font *pPolice;

    RectangleShape *pFinBouton;
    Text *pFinTexte;
    Chronometre *pFinChronometre;

    Music *pSon;

    deque <Objet*> *pPersonnage;
    deque <Objet*> *pEnnemi;

    Chronometre *pApparition;
};

#endif // CARTE_HPP_INCLUDED
