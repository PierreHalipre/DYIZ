#ifndef DECOR_HPP_INCLUDED
#define DECOR_HPP_INCLUDED

class Decor : public Objet
{
    public :

    Decor(String gNomDuFichierImage, Vector2f gDimensionsDesCases, Vector2f gPosition, Zone *gZone);
    virtual ~Decor();

    virtual void Afficher(RenderWindow *gFenetrePrincipale);
    void Subir(Objet *gObjet);
    bool EstBarricade(Vector2f gPosition);

    bool GetBarricade() {return pBarricade;}
    void SetBarricade(bool gBarricade) {pBarricade = gBarricade;}

    // Personnage

    virtual void Deplacer(Vector2f gSens) {return;}
    virtual bool Toucher(Objet *gObjet) {return false;}
    virtual void Reinitialiser() {return;}

    virtual int GetDegat() {return 0;}
    virtual void SetDegat(int gDegat) {return;}

    virtual bool GetDeplace() {return false;}
    virtual void SetDeplace(bool gDeplace) {return;}
    virtual bool GetTire() {return false;}
    virtual void SetTire(bool gTire) {return;}

    virtual int GetDeplacement() {return 0;}
    virtual void SetDeplacement(int gDeplacement) {return;}

    virtual Vector2f GetSens() {return Vector2f();}
    virtual void SetSens(Vector2f gSens) {return;}

    virtual deque <Tir*>* GetTir() {return NULL;}
    virtual void SetTir(deque <Tir*> *gTir) {return;}

    // Ennemi

    virtual void Afficher(RenderWindow *gFenetrePrincipale, bool gPause) {return;}

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

    protected :

    bool pBarricade;
};

#endif // DECOR_HPP_INCLUDED
