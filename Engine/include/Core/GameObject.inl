#pragma once

template <typename ComponentType, typename... Args> requires IsComponent<ComponentType>
ComponentType* GameObject::CreateComponent(Args&&... _args)
{
    auto componentUP = std::make_unique<ComponentType>(std::forward<Args>(_args)...);
    ComponentType* component = componentUP.get();

    component->SetOwner(this);

    component->Awake();
    component->OnEnable();
    component->Start();

    components.push_back(std::move(componentUP));
    return component;
}

template <typename ComponentType> requires IsComponent<ComponentType>
ComponentType* GameObject::GetComponent()
{
    for (const auto& componentUP : components)
    {
        ComponentType* result = dynamic_cast<ComponentType*>(componentUP.get());
        if (result != nullptr)
            return result;
    }

    return nullptr;
}
