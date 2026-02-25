#include "Engine.h"
#include "SceneModule.h"
#include "Scenes/DefaultScene.h"

int main()
{
    const Engine* engine = Engine::GetInstance();

    engine->Init();

    SceneModule* scene_module = engine->GetModuleManager()->GetModule<SceneModule>();
    scene_module->SetScene<DefaultScene>();

    engine->Run();

    return 0;
}
