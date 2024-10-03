#pragma once

#include <filesystem>

/**
 * \class AResource
 * \brief Base class for managing resources with reference counting.
 * 
 * This class provides basic functionality for resource management,
 * including reference counting and path handling.
 */
class AResource
{
public:
	/**
	 * \brief Default constructor.
	 */
	AResource();

	/**
	 * \brief Copy constructor.
	 * \param _other The other AResource object to copy from.
	 */
	AResource(const AResource& _other);

	/**
	 * \brief Move constructor.
	 * \param _other The other AResource object to move from.
	 */
	AResource(AResource&& _other) noexcept;

	/**
	 * \brief Copy assignment operator.
	 * \param _other The other AResource object to copy from.
	 * \return Reference to this AResource object.
	 */
	AResource& operator=(const AResource& _other);

	/**
	 * \brief Move assignment operator.
	 * \param _other The other AResource object to move from.
	 * \return Reference to this AResource object.
	 */
	AResource& operator=(AResource&& _other) noexcept;

	/// Type alias for filesystem path.
	using Path = std::filesystem::path;

	/// Name of the assets folder.
	static const std::string AssetsFolderName;

	/// Path to the assets folder.
	static const Path AssetsFolderPath;

	/**
	 * \brief Checks if a resource exists.
	 * \param _name The name of the resource.
	 * \return True if the resource exists, false otherwise.
	 */
	static bool Exists(const std::string& _name);

	/**
	 * \brief Destructor.
	 */
	virtual ~AResource();

	/**
	 * \brief Loads the resource from the specified path.
	 * \param _path The path to the resource.
	 * \return True if the resource was loaded successfully, false otherwise.
	 */
	virtual bool Load(const std::string& _path);

	/**
	 * \brief Unloads the resource.
	 */
	virtual void Unload();

	/**
	 * \brief Gets the reference counter.
	 * \return The reference count.
	 */
	unsigned int GetRefCount() const;

private:
	/// Path to the resource.
	Path path;

	/**
	 * \brief Gets the path from the resource name.
	 * \param _name The name of the resource.
	 * \return The path to the resource.
	 */
	static Path GetPathFromName(const std::string& _name);

	/**
	 * \brief Increases the reference counter.
	 */
	void IncreaseRefCount() noexcept;

	/**
	 * \brief Decreases the reference counter.
	 */
	void DecreaseRefCount() noexcept;

	/// Pointer to the reference counter.
	unsigned int* refCount = nullptr;
};
