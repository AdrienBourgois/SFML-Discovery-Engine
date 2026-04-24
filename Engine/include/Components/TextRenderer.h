#pragma once

#include <SFML/Graphics/Text.hpp>

#include "Assets/Font.h"

#include "Components/ARenderedComponent.h"
// Note: Core/Component.h is already included transitively via ARenderedComponent.h

class TextRenderer : public ARenderedComponent
{
public:
    explicit TextRenderer(const std::string& _text);
    TextRenderer(const std::string& _text, Font* _font);

    void Render(sf::RenderWindow* _window) override;

    std::string GetText() const;
    void SetText(const std::string& _text);

    Font* GetFont() const;
    void SetFont(Font* _font);

    sf::Color GetColor() const;
    void SetColor(sf::Color _color);

    int GetCharacterSize() const;
    void SetCharacterSize(int _size);

private:
    std::unique_ptr<sf::Text> sfmlText;

    std::string text;
    Font* font;
    sf::Color color = sf::Color::Black;

};