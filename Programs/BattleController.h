#pragma once
#include "CharaBase.h"
#include "BattleView.h"
#include "ObjectPool.h"
#include <iostream>

class BattleController {
private:
	
    // それぞれを持つ
    CharaBase* Owner;   // 攻撃するオーナー
	CharaBase* Target;  // ターゲット
	BattleView* View;   // 描画

public:
    
    BattleController() = default;

    BattleController(CharaBase* owner, CharaBase* target, BattleView* view)
        : Owner(owner), Target(target), View(view) {
    }

    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="owner">攻撃するキャラ</param>
    /// <param name="target">ターゲットキャラ</param>
    void SetActors(CharaBase* owner, CharaBase* target) {
        Owner = owner;
        Target = target;
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