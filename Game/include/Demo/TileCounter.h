#pragma once

#include "Component.h"
#include "Components/TextRenderer.h"

class TileCounter : public Component
{
public:
    void Start() override
    {
        text = GetOwner()->CreateComponent<TextRenderer>("Tile Count : 0");
        text->SetColor(sf::Color::Yellow);
        text->SetText("Tile Count : "+ std::to_string(tileCount));
    }

    void SetTileCount(const int _count)
    {
        tileCount = _count;
        if (text)
            text->SetText("Tile Count : " + std::to_string(tileCount));
    }

private:
    TextRenderer* text = nullptr;
    int tileCount = 0;
};