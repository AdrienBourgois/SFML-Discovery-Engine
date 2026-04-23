#pragma once

template <typename ComponentType, typename... Args> requires IsComponent<ComponentType>
ComponentType* GameObject::CreateComponent(Args&&... _args)
{
    auto component = std::make_unique<ComponentType>(std::forward<Args>(_args)...);

    component->SetOwner(this);

    component->Awake();
    component->OnEnable();

    ComponentType* raw_ptr = component.get();

    pendingComponents.push_back(std::move(component));
    return raw_ptr;
}

template <typename ComponentType> requires IsComponent<ComponentType>
ComponentType* GameObject::GetComponent()
{
    for (const auto& component : components)
    {
        ComponentType* result = dynamic_cast<ComponentType*>(component.get());
        if (result != nullptr)
            return result;
    }

    for (const auto& component : pendingComponents)
    {
        ComponentType* result = dynamic_cast<ComponentType*>(component.get());
        if (result != nullptr)
            return result;
    }

    return nullptr;
}
