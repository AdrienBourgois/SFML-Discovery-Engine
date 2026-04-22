#pragma once

template <typename SfmlType>
class SfmlAsset
{
public:
    virtual ~SfmlAsset() = default;

    virtual const SfmlType& GetSfmlAsset() = 0;

    virtual operator const SfmlType&()
    {
        return GetSfmlAsset();
    }
};
