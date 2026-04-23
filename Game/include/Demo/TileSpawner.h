#pragma once

#include "Component.h"

namespace Demo
{
    class TileSpawner : public Component
    {
    public :
        void Start() override;
        void Update(float _delta_time) override;

        void SpawnTile();

        static int RandomInt(int _min, int _max);

    private :
        int minSize = 100;
        int maxSize = 300;
    };
}
