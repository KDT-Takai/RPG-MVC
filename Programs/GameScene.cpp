#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GameScene.h"
#include "Text.h"

Game::Game() {
    // ランダム
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    // フラグ
    isGame = false;
    // プレイヤー生成
    players.push_back(std::make_unique<PoolHandle<CharaBase>>(CharacterFactory::Instance().CreatePlayer(0, 1)));
    players.push_back(std::make_unique<PoolHandle<CharaBase>>(CharacterFactory::Instance().CreatePlayer(1, 1)));
    // エネミー生成
    enemies.push_back(std::make_unique<PoolHandle<CharaBase>>(CharacterFactory::Instance().CreateEnemy(0, 2)));
    enemies.push_back(std::make_unique<PoolHandle<CharaBase>>(CharacterFactory::Instance().CreateEnemy(3, 4)));
}

void Game::Init() {}

void Game::Update() {
    if (isGame) return; // 無限ループ防止

    // 線の描画（ただただ見やすくするため）
    Text::Instance().Line();

    // --- プレイヤーターン ---
    for (auto& playerPtr : players) {
        if (enemies.empty()) break; // 敵がいない場合終了
        auto& player = *playerPtr;  // プレイヤー参照
        if (player->IsDead()) continue; // プレイヤーが死んでる場合終了
        std::cout << player->GetData().name << " のターン。攻撃を選択してください (0~"
            << enemies.size() - 1 << "): ";

        // 敵選択
        int choice = -1;
        std::cin >> choice; // 入力待ち
        if (choice < 0 || choice >= static_cast<int>(enemies.size())) continue;

        // 選択されたエネミー
        auto& enemy = *enemies[choice];

        // 戦闘画面の文字表示
        BattleController battleController(player.operator->(), enemy.operator->(), &battleView);
        battleController.processAttack(false);  // エネミーが攻撃受けるので赤

        // HPが0になった場合
        if (enemy->IsDead()) {
            std::cout <<"\033[31m" << enemy->GetData().name << "\033[0m" << " は倒れた！\n";
            enemies.erase(enemies.begin() + choice);
        }
    }

    // --- 勝利判定 ---
    if (enemies.empty()) {
        std::cout << "\033[34m" << "プレイヤーの勝利です！\n" << "\033[0m";
        isGame = true;
        return;
    }

    // --- 敵ターン ---
    for (auto& enemyPtr : enemies) {
        if (players.empty()) break; // プレイヤーがいない場合終了
        auto& enemy = *enemyPtr;    // エネミー参照
        if (enemy->IsDead()) continue;  // エネミーが死んでいる場合

        // 敵選択(ランダム)
        int targetIndex = std::rand() % players.size();
        auto& player = *players[targetIndex];

        // 戦闘画面の文字表示
        BattleController battleController(enemy.operator->(), player.operator->(), &battleView);
        battleController.processAttack(true);   // プレイヤーが攻撃受けるので青
        
        // HPが0になった場合
        if (player->IsDead()) {
            std::cout << "\033[34m" << player->GetData().name << "\033[0m" <<" は倒れた！\n";
            players.erase(players.begin() + targetIndex);
        }
    }

    // --- 敗北判定 ---
    if (players.empty()) {
        std::cout << "\033[31m" << "敵の勝利です！\n" << "\033[0m";
        isGame = true;
    }
}


void Game::Render() {
    if (isGame)  return; // 無限ループ防ぐ
    Text::Instance().Line();
}