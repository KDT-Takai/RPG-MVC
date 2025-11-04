#pragma once
#include <vector>
#include "ScreenBase.h"
#include "CharaFactory.h"
#include "BattleController.h"

class Game : public ScreenBase {
private:
    bool isGameOver;    // 無限ループ防ぐ

    std::vector<std::shared_ptr<PoolHandle<CharaBase>>> players;
    std::vector<std::shared_ptr<PoolHandle<CharaBase>>> enemies;

public:
    Game();
    ~Game() = default;
    // Init実装は必要かなと思って一応入れてるだけ
    void Init() override;
    // 更新処理
    void Update() override;
    // 描画処理
    void Render() override;
};