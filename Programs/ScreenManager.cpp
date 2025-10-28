#include "ScreenManager.h"
#include "GameScene.h"

ScreenManager::ScreenManager()
{
    screen = std::make_unique<Game>();
}

void ScreenManager::Init()
{
    screen->Init();
}

void ScreenManager::Update()
{
    screen->Update();
    if (changeFlag) {
        screen = std::move(next);
        next.reset();
        changeFlag = false;
    }

}

void ScreenManager::Render()
{
    screen->Render();
}