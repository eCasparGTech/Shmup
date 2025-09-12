#pragma once
#include "UI.h"

class GameManager;

class AMMO : public UI
{
public:
    AMMO();
    virtual ~AMMO() {}
    void start() override;
    void setAmmo(int ammo);
    void setMaxAmmo(int maxAmmo);

private:
    struct AmmoBar {
        Sprite* background;  // Barre de fond
        Sprite* fill;        // Barre de remplissage
        Sprite* border;      // Bordure
        float maxWidth;      // Largeur maximale de la barre
        int maxAmmoInBar;    // Nombre max d'ammos dans cette barre
    };

    sf::Vector2f uiPosition = {4.0f, 0.0f};
    float m_barHeight = 6.0f;
    float m_barSpacing = 8.0f; // Espacement entre les barres
    std::vector<AmmoBar> m_ammoBars;
    int m_currentAmmo = -1;
    int m_maxAmmo = 0;
    int m_maxAmmoPerBar = 0; // Ammos par barre (équivalent à l'ancienne ligne)
};