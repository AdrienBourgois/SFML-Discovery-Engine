#pragma once

/**
 * \class Resource
 * \brief A template class for managing resources with reference counting.
 * 
 * This class provides automatic memory management for resources by using
 * reference counting. It ensures that the resource is properly deleted
 * when no longer in use.
 * 
 * \tparam ResourceType The type of the resource.
 */
template<typename ResourceType>
class Resource
{
public:
	/**
	 * \brief Default constructor.
	 */
	Resource();

	/**
	 * \brief Constructor with a pointer to the data.
	 * \param _data Pointer to the resource data.
	 */
	explicit Resource(ResourceType* _data);

	/**
	 * \brief Copy constructor.
	 * \param _other The other Ressource object to copy from.
	 */
	Resource(const Resource& _other);

	/**
	 * \brief Move constructor.
	 * \param _other The other Ressource object to move from.
	 */
	Resource(Resource&& _other) noexcept;

	/**
	 * \brief Destructor.
	 */
	~Resource();

	/**
	 * \brief Copy assignment operator.
	 * \param _other The other Ressource object to copy from.
	 * \return Reference to this Ressource object.
	 */
	Resource& operator=(const Resource& _other);

	/**
	 * \brief Move assignment operator.
	 * \param _other The other Ressource object to move from.
	 * \return Reference to this Ressource object.
	 */
	Resource& operator=(Resource&& _other) noexcept;

	/**
	 * \brief Gets the data.
	 * \return Pointer to the resource data.
	 */
	ResourceType* GetData() const;

	/**
	 * \brief Gets the reference counter.
	 * \return The reference count.
	 */
	unsigned int GetRefCount() const;

private:
	/**
	 * \brief Increases the reference counter.
	 */
	void IncreaseRefCount() const;

	/**
	 * \brief Decreases the reference counter.
	 */
	void DecreaseRefCount() const;

	/// Pointer to the resource data.
	ResourceType* data;

	/// Pointer to the reference counter.
	unsigned int* refCount;
};

#include "Resource.inl"
