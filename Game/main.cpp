#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/DefaultScene.h"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();

    engine->Init(_argc, _argv);

    SceneModule* scene_module = engine->GetModuleManager()->GetModule<SceneModule>();
    scene_module->SetScene<DefaultScene>();

    engine->Run();

    return 0;
}
