#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GameScene.h"
#include "Text.h"

Game::Game() {
    // ランダム？たしかこれ　うろ覚え
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    // フラグ
    isGameOver = false;
    // プレイヤー生成
    players.push_back(std::make_unique<PoolHandle<CharaBase>>(CharacterFactory::Instance().CreatePlayer(0, 1)));
    players.push_back(std::make_unique<PoolHandle<CharaBase>>(CharacterFactory::Instance().CreatePlayer(1, 1)));
    // エネミー生成
    enemies.push_back(std::make_unique<PoolHandle<CharaBase>>(CharacterFactory::Instance().CreateEnemy(0, 2)));
    enemies.push_back(std::make_unique<PoolHandle<CharaBase>>(CharacterFactory::Instance().CreateEnemy(3, 4)));
}

void Game::Init() {}

void Game::Update() {
    if (isGameOver)  return;// 無限ループ防ぐ
    Text::Instance().Line();
    // --- プレイヤーターン ---
    for (auto it = players.begin(); it != players.end(); ++it) {    // プレイヤーの数だけ
        if (enemies.empty()) break;

        PoolHandle<CharaBase>& p = **it; // unique_ptrの中身にアクセス
        // 描画
        std::cout << p->GetData().name << " のターン。攻撃を選択してください : 0~" << enemies.size() - 1 << "): ";
        int choice;     // 誰を選択したかの表示
        std::cin >> choice;
        // 攻撃処理
        if (choice >= 0 && choice < (int)enemies.size()) {
            PoolHandle<CharaBase>& targetEnemy = *enemies[choice];
            
            BattleView battleView;  // View
            BattleController battleController(p.operator->(), enemies[choice]->operator->(), &battleView);
            battleController.processAttack();

        }
    }
    // 確認
    if (enemies.empty()) {
        std::cout << "プレイヤーの勝利です！\n";
        isGameOver = true;
        return;
    }

    // --- 敵ターン ---
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        if (players.empty()) break;

        PoolHandle<CharaBase>& e = **it;
        int targetIndex = std::rand() % players.size();

        BattleView battleView;  // View
        BattleController battleController(e.operator->(), players[targetIndex]->operator->(), &battleView);
        battleController.processAttack();

    }

    // 確認
    if (players.empty()) {
        std::cout << "敵の勝利です！\n";
        isGameOver = true;
        return;
    }
}

void Game::Render() {
    if (isGameOver)  return; // 無限ループ防ぐ
    Text::Instance().Line();
}