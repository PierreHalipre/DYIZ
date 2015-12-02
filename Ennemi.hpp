#ifndef ENNEMI_HPP_INCLUDED
#define ENNEMI_HPP_INCLUDED

class Ennemi : public Objet
{
    public :

    Ennemi(String gNomDuFichierImage, Vector2f gDimensionsDesCases, Vector2f gPosition, Zone *gZone);
    virtual ~Ennemi();

    virtual void Afficher(RenderWindow *gFenetrePrincipale, bool gPause);
    void Subir(Objet *gObjet);
    void Deplacer(Vector2f gDestination);

    bool GetDeplace() {return pDeplace;}
    void SetDeplace(bool gDeplace) {pDeplace = gDeplace;}
    bool GetAttaque() {return pAttaque;}
    void SetAttaque(bool gAttaque) {pAttaque = gAttaque;}

    int GetType() {return pType;}
    void SetType(int gType) {pType = gType;}

    int GetVie() {return pVie;}
    void SetVie(int gVie) {pVie = gVie;}
    int GetDegat() {return pDegat;}
    void SetDegat(int gDegat) {pDegat = gDegat;}
    int GetVitesse() {return pVitesse;}
    void SetVitesse(int gVitesse) {pVitesse = gVitesse;}

    int GetDeplacement() {return pDeplacement;}
    void SetDeplacement(int gDeplacement) {pDeplacement = gDeplacement;}

    String GetSon() {return pSon;}
    void SetSon(String gSon) {pSon = gSon;}

    deque <Vector2f>* GetChemin() {return pChemin;}
    void SetChemin(deque <Vector2f> *gChemin) {pChemin = gChemin;}

    // Personnage

    virtual bool Toucher(Objet *gObjet) {return false;}
    virtual void Reinitialiser() {return;}

    virtual bool GetTire() {return false;}
    virtual void SetTire(bool gTire) {return;}

    virtual Vector2f GetSens() {return Vector2f();}
    virtual void SetSens(Vector2f gSens) {return;}

    virtual deque <Tir*>* GetTir() {return NULL;}
    virtual void SetTir(deque <Tir*> *gTir) {return;}

    // Decor

    virtual bool GetBarricade() {return false;}
    virtual void SetBarricade(bool gBarricade) {return;}

    protected :

    bool pAttaque;
    bool pDeplace;

    int pType;

    int pVie;
    int pVieInitiale;
    int pDegat;
    int pVitesse;

    int pDeplacement;

    RectangleShape pRectangleVieContour;
    RectangleShape pRectangleVie;

    String pSon;

    deque <Vector2f> *pChemin;

    Chronometre *pAnimation;
};

#endif // ENNEMI_HPP_INCLUDED
