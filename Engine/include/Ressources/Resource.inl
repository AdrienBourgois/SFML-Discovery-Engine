#pragma once

template<typename T>
Resource<T>::Resource(): data(nullptr), refCount(nullptr)
{
	
}

template<typename T>
Resource<T>::Resource(T* _data): data(_data), refCount(new unsigned int(1))
{
	
}

template<typename T>
Resource<T>::Resource(const Resource& _other): data(_other.data), refCount(_other.refCount)
{
	IncreaseRefCount();
}

template<typename T>
Resource<T>::Resource(Resource&& _other) noexcept: data(_other.data), refCount(_other.refCount)
{
	_other.data = nullptr;
	_other.refCount = nullptr;
}

template<typename T>
Resource<T>::~Resource()
{
	DecreaseRefCount();
}

template<typename T>
Resource<T>& Resource<T>::operator=(const Resource& _other)
{
	if (this != &_other)
	{
		DecreaseRefCount();
		data = _other.data;
		refCount = _other.refCount;
		IncreaseRefCount();
	}
	return *this;
}

template<typename T>
Resource<T>& Resource<T>::operator=(Resource&& _other) noexcept
{
	if (this != &_other)
	{
		DecreaseRefCount();
		data = _other.data;
		refCount = _other.refCount;
		_other.data = nullptr;
		_other.refCount = nullptr;
	}
	return *this;
}

template<typename T>
T* Resource<T>::GetData() const
{
	return data;
}

template<typename T>
unsigned int Resource<T>::GetRefCount() const
{
	return *refCount;
}

template<typename T>
void Resource<T>::IncreaseRefCount() const
{
	if (refCount)
		++(*refCount);
}

template<typename T>
void Resource<T>::DecreaseRefCount() const
{
	if (refCount && --(*refCount) == 0)
	{
		delete data;
		delete refCount;
	}
}
