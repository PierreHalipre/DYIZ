#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

class Menu : public Zone
{
    public :

    Menu(Vector2f gDimensionsDesCases, Vector2f gNombreDeCases);
    ~Menu();

    void Afficher(RenderWindow *gFenetrePrincipale);
    void Action(Evenement *gEvenement, Zone *gZone, int *gAction);

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

    RectangleShape *pJouerBouton[4];
    Text *pJouerTexte[4];
    Chronometre *pJouerChronometre[4];

    RectangleShape *pQuitterBouton;
    Text *pQuitterTexte;
    Chronometre *pQuitterChronometre;

    Music *pSon;
    Music *pMusique;
};

#endif // MENU_HPP_INCLUDED
