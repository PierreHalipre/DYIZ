#ifndef ETAT_HPP_INCLUDED
#define ETAT_HPP_INCLUDED

class Etat : public Zone
{
    public :

    Etat(Vector2f gDimensionsDesCases, Vector2f gNombreDeCases);
    ~Etat();

    void Afficher(RenderWindow *gFenetrePrincipale);
    void Action(Evenement *gEvenement, Zone *pZone, int *gAction);

    // Carte

    virtual void Subir(Objet *gObjet) {return;}
    virtual void Reinitialiser(int gNombreDePersonnages) {return;}

    virtual bool GetPause() {return false;}
    virtual void SetPause(bool gPause) {return;}
    virtual bool GetFin() {return false;}
    virtual void SetFin(bool gFin) {return;}

    virtual int GetNombreDePersonnages() {return 0;}
    virtual void SetNombreDePersonnages(int gNombreDePersonnages) {return;}

    virtual int GetBarricade() {return 0;}
    virtual void SetBarricade(int gBarricade) {return;}
    virtual int GetScore() {return 0;}
    virtual void SetScore(int gScore) {return;}

    protected :

    Font *pPolice;

    Text *pTexte;

    RectangleShape *pPauseBouton;
    Text *pPauseTexte;
    Chronometre *pPauseChronometre;

    RectangleShape *pQuitterBouton;
    Text *pQuitterTexte;
    Chronometre *pQuitterChronometre;

    Music *pSon;

    Transform *pTransformation;
    RenderStates *pEtat;
};

#endif // ETAT_HPP_INCLUDED
