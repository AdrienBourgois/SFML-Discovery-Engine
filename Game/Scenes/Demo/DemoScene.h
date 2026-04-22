#pragma once

#include "Core/Scene.h"

namespace Demo
{
    class DemoScene final : public Scene
    {
    public:
        DemoScene();

        void CreateRandomTile();

        int minSize = 100;
        int maxSize = 300;
    };
}

