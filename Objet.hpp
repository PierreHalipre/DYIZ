#ifndef OBJET_HPP_INCLUDED
#define OBJET_HPP_INCLUDED

class Tir;
class Zone;

class Objet
{
    public :

    Objet(String gNomDuFichierImage, Vector2f gDimensionsDesCases, Vector2f gPosition, Zone *gZone);
    virtual ~Objet();

    virtual void Afficher(RenderWindow *gFenetrePrincipale);
    void Positionner(Vector2f gPosition);

    Sprite* GetSprite() {return pSprite;}
    void SetSprite(Sprite *gSprite) {pSprite = gSprite;}
    Vector2f GetPosition() {return pPosition;}
    void SetPosition(Vector2f gPosition) {pPosition = gPosition;}

    Zone* GetZone() {return pZone;}
    void SetCarte(Zone *gZone) {pZone = gZone;}

    // Personnage

    virtual void Deplacer(Vector2f gSens) = 0;
    virtual bool Toucher(Objet *gObjet) = 0;
    virtual void Reinitialiser() = 0;

    virtual int GetDegat() = 0;
    virtual void SetDegat(int gDegat) = 0;

    virtual bool GetDeplace() = 0;
    virtual void SetDeplace(bool gDeplace) = 0;
    virtual bool GetTire() = 0;
    virtual void SetTire(bool gTire) = 0;

    virtual int GetDeplacement() = 0;
    virtual void SetDeplacement(int gDeplacement) = 0;

    virtual Vector2f GetSens() = 0;
    virtual void SetSens(Vector2f gSens) = 0;

    virtual deque <Tir*>* GetTir() = 0;
    virtual void SetTir(deque <Tir*> *gTir) = 0;

    // Ennemi

    virtual void Afficher(RenderWindow *gFenetrePrincipale, bool gPause) = 0;
    virtual void Subir(Objet *gObjet) = 0;

    virtual bool GetAttaque() = 0;
    virtual void SetAttaque(bool gAttaque) = 0;

    virtual int GetType() = 0;
    virtual void SetType(int gType) = 0;

    virtual int GetVie() = 0;
    virtual void SetVie(int gVie) = 0;

    virtual String GetSon() = 0;
    virtual void SetSon(String gSon) = 0;

    virtual deque <Vector2f>* GetChemin() = 0;
    virtual void SetChemin(deque <Vector2f> *gChemin) = 0;

    // Decor

    virtual bool GetBarricade() = 0;
    virtual void SetBarricade(bool gBarricade) = 0;

    protected :

    Image *pImage;
    Texture *pTexture;
    Sprite *pSprite;

    Vector2f pPosition;

    Zone *pZone;
};

#endif // OBJET_HPP_INCLUDED
