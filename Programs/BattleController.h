#pragma once
#include "CharaBase.h"
#include "BattleView.h"
#include "ObjectPool.h"
#include <iostream>

class BattleController
{
private:
	
    // それぞれを持つ
    CharaBase* Owner;   // 攻撃するオーナー
	CharaBase* Target;  // ターゲット
	BattleView* View;   // 描画

public:

	BattleController(CharaBase* owner, CharaBase* target, BattleView* view)
        : Owner(owner), Target(target), View(view) {}

    BattleController(PoolHandle<CharaBase*> owner, PoolHandle<CharaBase*> target, BattleView* view)
        : Owner(*owner), Target(*target), View(view) {
    }

    /// <summary>
    /// 攻撃処理
    /// </summary>
    /// <param name="isPlayerAttacker">FALSE : RED, TRUE : BLUE</param>
    void processAttack(bool isPlayerAttacker) {
        // Modelから攻撃力を取得
        int damage = Owner->GetData().atk;
        // Modelにダメージを適用
        Target->TakeDamage(damage);
        
        // Viewに表示
        View->ShowDamage(Target->GetData().name, damage, isPlayerAttacker);
        View->ShowStatus(Target->GetLevel(), Target->GetData());
    }
};