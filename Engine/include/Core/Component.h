#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Engine.h"
#include "GameObject.h"
#include "Module.h"

class GameObject;

class Component
{
public:
    virtual ~Component() = default;

    virtual void Awake()
    {
    }

    virtual void Start()
    {
    }

    virtual void Update(float _delta_time)
    {
    }

    virtual void PreRender()
    {
    }

    virtual void Render(sf::RenderWindow* _window)
    {
    }

    virtual void OnGUI()
    {
    }

    virtual void PostRender()
    {
    }

    virtual void OnDebug()
    {
    }

    virtual void OnDebugSelected()
    {
    }

    virtual void Present()
    {
    }

    virtual void OnEnable()
    {
    }

    virtual void OnDisable()
    {
    }

    virtual void Destroy()
    {
    }

    virtual void Finalize()
    {
    }

    GameObject* GetOwner() const
    {
        return owner;
    }

    void SetOwner(GameObject* _owner)
    {
        owner = _owner;
    }

    template <class T> requires IsModule<T>
    static T* GetModule();

private:
    GameObject* owner = nullptr;
};

#include "Component.inl"
