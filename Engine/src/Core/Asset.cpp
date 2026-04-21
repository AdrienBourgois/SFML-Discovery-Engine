#include "Core/Asset.h"

bool Asset::Load(const std::filesystem::path& _path)
{
    path = _path;
    return true;
}

Asset::Path& Asset::GetPath()
{
    return path;
}
