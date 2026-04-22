#pragma once

template <typename ComponentType, typename... Args> requires IsComponent<ComponentType>
ComponentType* GameObject::CreateComponent(Args&&... _args)
{
    ComponentType* component = new ComponentType(std::forward<Args>(_args)...);

    component->SetOwner(this);

    components.push_back(component);
    return component;
}

template <typename ComponentType> requires IsComponent<ComponentType>
ComponentType* GameObject::GetComponent()
{
    for (Component* component : components)
    {
        ComponentType* result = dynamic_cast<ComponentType*>(component);
        if (result != nullptr)
            return result;
    }

    return nullptr;
}
