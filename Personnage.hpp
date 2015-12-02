#ifndef PERSONNAGE_HPP_INCLUDED
#define PERSONNAGE_HPP_INCLUDED

class Personnage : public Objet
{
    public :

    Personnage(String gNomDuFichierImage, Vector2f gDimensionsDesCases, Vector2f gPosition, Vector2f gSens, Zone *gZone);
    virtual ~Personnage();

    virtual void Afficher(RenderWindow *gFenetrePrincipale, bool gPause);
    void Deplacer(Vector2f gSens);
    void Tirer();
    bool Toucher(Objet *gObjet);
    void Reinitialiser();

    int GetDegat() {return pDegat;}
    void SetDegat(int gDegat) {pDegat = gDegat;}

    bool GetDeplace() {return pDeplace;}
    void SetDeplace(bool gDeplace) {pDeplace = gDeplace;}
    bool GetTire() {return pTire;}
    void SetTire(bool gTire) {pTire = gTire;}

    int GetDeplacement() {return pDeplacement;}
    void SetDeplacement(int gDeplacement) {pDeplacement = gDeplacement;}

    Vector2f GetSens() {return pSens;}
    void SetSens(Vector2f gSens) {pSens = gSens;}

    String GetSon() {return pSon;}
    void SetSon(String gSon) {pSon = gSon;}

    deque <Tir*>* GetTir() {return pTir;}
    void SetTir(deque <Tir*> *gTir) {pTir = gTir;}

    // Ennemi

    virtual int GetType() {return 0;}
    virtual void SetType(int gType) {return;}

    virtual int GetVie() {return 0;}
    virtual void SetVie(int gVie) {return;}

    virtual bool GetAttaque() {return false;}
    virtual void SetAttaque(bool gAttaque) {return;}

    virtual deque <Vector2f>* GetChemin() {return NULL;}
    virtual void SetChemin(deque <Vector2f> *gChemin) {return;}

    // Decor

    virtual void Subir(Objet *gObjet) {return;}

    virtual bool GetBarricade() {return false;}
    virtual void SetBarricade(bool gBarricade) {return;}

    protected :

    int pType;

    int pDegat;

    bool pDeplace;
    bool pTire;
    bool pBloque;

    int pDeplacement;

    Vector2f pSens;

    Chronometre *pAnimation;
    Chronometre *pCadenceDeTir;
    Chronometre *pBlocage;

    String pSon;

    deque <Tir*> *pTir;
};

#endif // PERSONNAGE_HPP_INCLUDED
