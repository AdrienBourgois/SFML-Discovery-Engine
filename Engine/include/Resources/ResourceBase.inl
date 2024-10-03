#pragma once

template<typename ResourceType>
ResourceBase<ResourceType>::ResourceBase() : AResource(), data(nullptr)
{
}

template<typename ResourceType>
ResourceBase<ResourceType>::ResourceBase(ResourceType* _data) : AResource(), data(_data)
{
}

template<typename ResourceType>
ResourceBase<ResourceType>::ResourceBase(const ResourceBase& _other) : AResource(_other), data(_other.data)
{
}

template<typename ResourceType>
ResourceBase<ResourceType>::ResourceBase(ResourceBase&& _other) noexcept : AResource(std::move(_other)), data(std::move(_other.data))
{
    _other.data = nullptr;
}

template<typename ResourceType>
ResourceBase<ResourceType>::~ResourceBase()
{
}

template<typename ResourceType>
ResourceBase<ResourceType>& ResourceBase<ResourceType>::operator=(const ResourceBase& _other)
{
    if (this != &_other)
    {
        AResource::operator=(_other);
        data = _other.data;
    }
    return *this;
}

template<typename ResourceType>
ResourceBase<ResourceType>& ResourceBase<ResourceType>::operator=(ResourceBase&& _other) noexcept
{
    if (this != &_other)
    {
        AResource::operator=(std::move(_other));
        data = _other.data;
        _other.data = nullptr;
    }
    return *this;
}

template<typename ResourceType>
ResourceType* ResourceBase<ResourceType>::GetData() const
{
    return data;
}

template<typename ResourceType>
ResourceType* ResourceBase<ResourceType>::operator->() const
{
    return GetData();
}