#ifndef TIR_HPP_INCLUDED
#define TIR_HPP_INCLUDED

class Tir : public Objet
{
    public :

    Tir(String gNomDuFichierImage, Vector2f gDimensionsDesCases, Vector2f gPosition, Vector2f gSens, Zone *gZone);
    virtual ~Tir();

    virtual void Afficher(RenderWindow *gFenetrePrincipale, bool gPause);
    void Deplacer();

    bool GetDeplace() {return pDeplace;}
    void SetDeplace(bool gDeplace) {pDeplace = gDeplace;}

    int GetDeplacement() {return pDeplacement;}
    void SetDeplacement(int gDeplacement) {pDeplacement = gDeplacement;}

    Vector2f GetSens() {return pSens;}
    void SetSens(Vector2f gSens) {pSens = gSens;}

    // Personnage

    virtual void Deplacer(Vector2f gSens) {return;}
    virtual bool Toucher(Objet *gObjet) {return false;}
    virtual void Reinitialiser() {return;}

    virtual int GetDegat() {return 0;}
    virtual void SetDegat(int gDegat) {return;}

    virtual bool GetTire() {return false;}
    virtual void SetTire(bool gTire) {return;}

    virtual deque <Tir*>* GetTir() {return NULL;}
    virtual void SetTir(deque <Tir*> *gTir) {return;}

    // Ennemi

    virtual void Subir(Objet *gObjet) {return;}

    virtual bool GetAttaque() {return false;}
    virtual void SetAttaque(bool gAttaque) {return;}

    virtual int GetType() {return 0;}
    virtual void SetType(int gType) {return;}

    virtual int GetVie() {return 0;}
    virtual void SetVie(int gVie) {return;}

    virtual String GetSon() {return String();}
    virtual void SetSon(String gSon) {return;}

    virtual deque <Vector2f>* GetChemin() {return NULL;}
    virtual void SetChemin(deque <Vector2f> *gChemin) {return;}

    // Decor

    virtual bool GetBarricade() {return false;}
    virtual void SetBarricade(bool gBarricade) {return;}

    protected :

    bool pDeplace;

    int pDeplacement;

    Vector2f pSens;

    Chronometre *pAnimation;
};

#endif // TIR_HPP_INCLUDED
