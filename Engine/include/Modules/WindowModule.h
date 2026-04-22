#pragma once

#include <memory>

#include <Core/Module.h>

#include "Maths/Vector2.h"

namespace sf
{
    class RenderWindow;
}

class WindowModule final : public Module
{
public:
    sf::RenderWindow* GetWindow() const
    {
        return window.get();
    }

    void Awake() override;
    void PreRender() override;
    void Present() override;
    void Destroy() override;

    Maths::Vector2u GetSize() const;
    void SetSize(const Maths::Vector2u& _size) const;

    void SetTitle(const std::string& _title) const;

private:
    std::unique_ptr<sf::RenderWindow> window = nullptr;
};
