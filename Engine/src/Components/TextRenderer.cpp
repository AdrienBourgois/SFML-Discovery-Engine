#include "Components/TextRenderer.h"

#include "SFML/Graphics/Text.hpp"

#include "Modules/AssetsModule.h"

TextRenderer::TextRenderer(const std::string& _text)
{
    font = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>()->GetDefaultFont();
    text = _text;
    sfmlText = std::make_unique<sf::Text>(font->GetSfmlAsset(), text);

    SetColor(color);
}

TextRenderer::TextRenderer(const std::string& _text, Font* _font)
{
    text = _text;
    font = _font;
}

void TextRenderer::Render(sf::RenderWindow* _window)
{
    sfmlText->setPosition(static_cast<sf::Vector2f>(GetOwner()->GetPosition()));
    sfmlText->setRotation(GetOwner()->GetRotation());
    sfmlText->setScale(static_cast<sf::Vector2f>(GetOwner()->GetScale()));
    sfmlText->setOrigin(static_cast<sf::Vector2f>(GetPivot()));

    _window->draw(*sfmlText);
}

std::string TextRenderer::GetText() const
{
    return text;
}

void TextRenderer::SetText(const std::string& _text)
{
    text = _text;
    sfmlText->setString(text);
}

Font* TextRenderer::GetFont() const
{
    return font;
}

void TextRenderer::SetFont(Font* _font)
{
    font = _font;
    sfmlText->setFont(*font);
}

sf::Color TextRenderer::GetColor() const
{
    return color;
}

void TextRenderer::SetColor(const sf::Color _color)
{
    color = _color;
    sfmlText->setFillColor(color);
}

int TextRenderer::GetCharacterSize() const
{
    return sfmlText->getCharacterSize();
}

void TextRenderer::SetCharacterSize(const int _size)
{
    sfmlText->setCharacterSize(_size);
}
