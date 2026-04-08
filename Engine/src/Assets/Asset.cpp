#include "Assets/Asset.h"

Asset::~Asset()
{
}

bool Asset::Load(const std::filesystem::path& _path) {
    path = _path;
    return true;
}
