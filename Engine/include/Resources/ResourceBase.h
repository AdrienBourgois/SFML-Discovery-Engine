#pragma once

#include "Resources/AResource.h"

/**
 * \class ResourceBase
 * \brief A template class for managing resources with reference counting.
 * 
 * This class provides automatic memory management for resources by using
 * reference counting. It ensures that the resource is properly deleted
 * when no longer in use.
 * 
 * \tparam ResourceType The type of the resource.
 */
template<typename ResourceType>
class ResourceBase : public AResource
{
public:
	/**
	 * \brief Default constructor.
	 */
	ResourceBase();

	/**
	 * \brief Constructor with a pointer to the data.
	 * This constructor initializes the ResourceBase with a pointer to the resource data.
	 * \param _data Pointer to the resource data.
	 */
	explicit ResourceBase(ResourceType* _data);

	/**
	 * \brief Copy constructor.
	 * \param _other The other Resource object to copy from.
	 */
	ResourceBase(const ResourceBase& _other);

	/**
	 * \brief Move constructor.
	 * \param _other The other Resource object to move from.
	 */
	ResourceBase(ResourceBase&& _other) noexcept;

	/**
	 * \brief Destructor.
	 */
	~ResourceBase() override;

	/**
	 * \brief Copy assignment operator.
	 * \param _other The other Resource object to copy from.
	 * \return Reference to this Resource object.
	 */
	ResourceBase& operator=(const ResourceBase& _other);

	/**
	 * \brief Move assignment operator.
	 * \param _other The other Resource object to move from.
	 * \return Reference to this Resource object.
	 */
	ResourceBase& operator=(ResourceBase&& _other) noexcept;

	/**
	 * \brief Gets the data.
	 * \return Pointer to the resource data.
	 */
	ResourceType* GetData() const;

	/**
	 * \brief Overloaded arrow operator.
	 * Provides access to the resource data.
	 * \return Pointer to the resource data.
	 */
	ResourceType* operator->() const;

	/**
	 * \brief Implicit cast operator to ResourceType.
	 * \return Reference to the resource data as ResourceType.
	 */
	operator ResourceType&() const
	{
		return *data;
	}

protected:
	/// Pointer to the resource data.
	ResourceType* data = nullptr;
};

#include "ResourceBase.inl"
