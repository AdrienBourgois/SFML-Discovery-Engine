#pragma once

#include <filesystem>
#include <span>

/**
 * \class Asset
 * \brief Base class for managing resources with reference counting.
 *
 * This class provides basic functionality for resource management,
 * including reference counting and path handling.
 */
class Asset
{
public:
    /// Type alias for filesystem paths.
    using Path = std::filesystem::path;

    /**
     * \brief Destructor.
     */
    virtual ~Asset() = default;

    /**
     * \brief Loads the resource from the specified path.
     * \warning Derived classes must implement this method and call the base class implementation.
     * \param _path The path to the resource.
     * \return True, if the resource was loaded successfully, false otherwise.
     */
    virtual bool Load(const std::filesystem::path& _path);

    /**
     * \brief Unloads the resource.
     */
    virtual bool Unload() = 0;

    Path& GetPath();

protected:
    /// Absolute path to the resource.
    Path path;
};

template <typename AssetType>
concept IsAsset = std::is_base_of_v<Asset, AssetType>;
