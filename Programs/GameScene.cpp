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
    if (isGameOver) return; // 無限ループ防止

    Text::Instance().Line();

    // --- プレイヤーターン ---
    for (auto& playerPtr : players) {
        if (enemies.empty()) break;
        auto& player = *playerPtr;
        if (player->IsDead()) continue;
        std::cout << player->GetData().name << " のターン。攻撃を選択してください (0~"
            << enemies.size() - 1 << "): ";

        // 敵選択
        int choice = -1;
        std::cin >> choice;

        if (choice < 0 || choice >= static_cast<int>(enemies.size())) continue;

        // 選択されたエネミー
        auto& enemy = *enemies[choice];

        BattleView battleView;
        BattleController battleController(player.operator->(), enemy.operator->(), &battleView);
        battleController.processAttack();

        // HPが0になった場合
        if (enemy->IsDead()) {
            std::cout << enemy->GetData().name << " は倒れた！\n";
            enemies.erase(enemies.begin() + choice);
        }
    }

    // --- 勝利判定 ---
    if (enemies.empty()) {
        std::cout << "プレイヤーの勝利です！\n";
        isGameOver = true;
        return;
    }

    // --- 敵ターン ---
    for (auto& enemyPtr : enemies) {
        if (players.empty()) break;

        auto& enemy = *enemyPtr;
        if (enemy->IsDead()) continue;

        int targetIndex = std::rand() % players.size();
        auto& player = *players[targetIndex];

        BattleView battleView;
        BattleController battleController(enemy.operator->(), player.operator->(), &battleView);
        battleController.processAttack();

        if (player->IsDead()) {
            std::cout << player->GetData().name << " は倒れた！\n";
            players.erase(players.begin() + targetIndex);
        }
    }

    // --- 敗北判定 ---
    if (players.empty()) {
        std::cout << "敵の勝利です！\n";
        isGameOver = true;
    }
}


void Game::Render() {
    if (isGameOver)  return; // 無限ループ防ぐ
    Text::Instance().Line();
}