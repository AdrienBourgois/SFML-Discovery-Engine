#pragma once

#include "Engine.h"

template <typename ComponentType>
concept IsComponent = std::derived_from<ComponentType, Component>;

template <class T> requires IsModule<T>
T* Component::GetModule()
{
    return Engine::GetInstance()->GetModuleManager()->GetModule<T>();
}
