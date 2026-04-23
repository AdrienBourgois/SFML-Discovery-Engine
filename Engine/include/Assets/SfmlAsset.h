#pragma once

#include "Core/Asset.h"

template <typename SfmlType>
class SfmlAsset : public Asset
{
public:
    ~SfmlAsset() override = default;

    virtual const SfmlType& GetSfmlAsset() = 0;

    virtual operator const SfmlType&()
    {
        return GetSfmlAsset();
    }
};
