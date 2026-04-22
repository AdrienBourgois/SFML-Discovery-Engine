#pragma once

#include "Core/Scene.h"
#include "Demo/Player.h"

namespace Demo
{
    class DemoScene final : public Scene
    {
    public:
        DemoScene();

        GameObject* CreateDummyGameObject(const std::string& _name, float _position, sf::Color _color);
    };
}

