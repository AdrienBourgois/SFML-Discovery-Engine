#include "Components/RectangleShapeRenderer.h"

#include <iostream>

#include <imgui-SFML.h>

#include "SFML/Graphics/Shape.hpp"
#include "Utils/ImGuiUtilities.h"

RectangleShapeRenderer::RectangleShapeRenderer()
{
    shape = new sf::RectangleShape();
}

RectangleShapeRenderer::~RectangleShapeRenderer()
{
    delete shape;
    shape = nullptr;
}

void RectangleShapeRenderer::Render(sf::RenderWindow* _window)
{
    ARenderedComponent::Render(_window);

    const GameObject* owner = GetOwner();

    const Maths::Vector2<float> position = owner->GetPosition();
    shape->setPosition({position.x, position.y});
    shape->setSize(static_cast<sf::Vector2f>(owner->GetScale() * size));
    shape->setRotation(owner->GetRotation());
    shape->setFillColor(color);

    _window->draw(*shape);
}

void RectangleShapeRenderer::OnDebug()
{
    ARenderedComponent::OnDebug();

    //sf::FloatRect bounds = shape->getGlobalBounds();

    const Maths::Vector2f min = static_cast<Maths::Vector2f>(shape->getPosition());
    const Maths::Vector2f size = static_cast<Maths::Vector2f>(shape->getSize());
    const Maths::Vector2f max = min + size;

    //const ImU32 col = ImGuiUtilities::Red;

    ImGui::GetBackgroundDrawList()->AddRect(static_cast<ImVec2>(min), static_cast<ImVec2>(max), ImU32(0));

    /*	
    ImGui::Begin("RectangleShapeRenderer");
    if (ImGui::Button("Click"))
        std::cout << "COUCOU";
    ImGui::End();

    */
}
