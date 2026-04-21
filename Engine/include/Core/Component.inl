#pragma once

template <typename ComponentType>
concept IsComponent = std::is_base_of_v<Component, ComponentType>;

template <class T> requires IsModule<T>
T* Component::GetModule()
{
    return Engine::GetInstance()->GetModuleManager()->GetModule<T>();
}
