#ifndef ZONE_HPP_INCLUDED
#define ZONE_HPP_INCLUDED

class Zone
{
    public :

    Zone();
    Zone(Vector2f gDimensionsDesCases, Vector2f gNombreDeCases);
    virtual ~Zone();

    virtual void Afficher(RenderWindow *gFenetrePrincipale);
    virtual void Action();

    Vector2f GetDimensionsDesCases() {return pDimensionsDesCases;}
    void SetDimensionsDesCases(Vector2f gDimensionsDesCases) {pDimensionsDesCases = gDimensionsDesCases;}
    Vector2f GetNombreDeCases() {return pNombreDeCases;}
    void SetNombreDeCases(Vector2f gNombreDeCases) {pNombreDeCases = gNombreDeCases;}

    Grille <Objet*>* GetDecor() {return pDecor;}
    void SetDecor(Grille <Objet*> *gDecor) {pDecor = gDecor;}
    Grille <Objet*>* GetObjet() {return pObjet;}
    void SetObjet(Grille <Objet*> *gObjet) {pObjet = gObjet;}

    // Carte

    virtual void Subir(Objet *gObjet) = 0;
    virtual void Reinitialiser(int gNombreDePersonnages) = 0;

    virtual bool GetPause() = 0;
    virtual void SetPause(bool gPause) = 0;
    virtual bool GetFin() = 0;
    virtual void SetFin(bool gFin) = 0;

    virtual int GetNombreDePersonnages() = 0;
    virtual void SetNombreDePersonnages(int gNombreDePersonnages) = 0;

    virtual int GetBarricade() = 0;
    virtual void SetBarricade(int gBarricade) = 0;
    virtual int GetScore() = 0;
    virtual void SetScore(int gScore) = 0;

    protected :

    Vector2f pDimensionsDesCases;
    Vector2f pNombreDeCases;

    Grille <Objet*> *pDecor;
    Grille <Objet*> *pObjet;
};

#endif // ZONE_HPP_INCLUDED
