#pragma once
#include "CharaBase.h"
#include "BattleView.h"
#include "ObjectPool.h"

class BattleController
{
private:
	
    CharaBase* Player;
	CharaBase* Enemy;
	BattleView* View;

public:

	BattleController(CharaBase* player, CharaBase* enemy, BattleView* view)
        : Player(player), Enemy(enemy), View(view) {}

    BattleController(PoolHandle<CharaBase*> player, PoolHandle<CharaBase*> enemy, BattleView* view)
        : Player(*player), Enemy(*enemy), View(view) {
    }

    void processAttack() {
        std::cout << "processAttack" << std::endl;
        // Modelから攻撃力を取得
        int damage = Player->GetData().atk;
        // Modelにダメージを適用
        Enemy->TakeDamage(damage);

        // Viewに表示
        View->ShowDamge(Enemy->GetData().name, damage);
        View->ShowStatus(Enemy->GetLevel(), Enemy->GetData());
    }
};