#pragma once

#include "Engine.h"

template <class T> requires IsModule<T>
T* Component::GetModule()
{
    return Engine::GetInstance()->GetModuleManager()->GetModule<T>();
}
