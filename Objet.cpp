#include "main.hpp"

Objet::Objet(String gNomDuFichierImage, Vector2f gDimensionsDesCases, Vector2f gPosition, Zone *gZone)
{
    pImage = new Image();
    pImage->loadFromFile(gNomDuFichierImage);
    pImage->createMaskFromColor(Color::White);

    pTexture = new Texture();
    pTexture->loadFromImage(*pImage);

    pSprite = new Sprite();
    pSprite->setTexture(*pTexture);
    pSprite->setTextureRect(IntRect(0, 0, gDimensionsDesCases.x, gDimensionsDesCases.y));

    pPosition = gPosition;

    pZone = gZone;

    this->Positionner(pPosition);
}

Objet::~Objet()
{
    delete pImage;
    delete pTexture;
    delete pSprite;
}

void Objet::Afficher(RenderWindow *gFenetrePrincipale)
{
    gFenetrePrincipale->draw(*pSprite);

    return;
}

void Objet::Positionner(Vector2f gPosition)
{
    pZone->GetObjet()->SetT(pPosition, NULL);

    pPosition = gPosition;

    pSprite->setPosition(Vector2f(pPosition.x*pSprite->getTextureRect().width, pPosition.y*pSprite->getTextureRect().height));

    pZone->GetObjet()->SetT(pPosition, this);

    return;
}
