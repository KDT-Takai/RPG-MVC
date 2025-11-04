#pragma once
#include <iostream>
#include "CharaData.h"	// EntityData Entityが持つ情報 名前,hpなど

class CharaBase {
protected:
	int level;				// レベル
	CharaData charaData;	// データ

	// レベルによって加算用の定数
	const int LevelUpHpBonus = 10;	// HPの加算用
	const int LevelUpAtkBonus = 2;	// Atkの加算用
	const int LevelUpDefBonus = 2;	// Defの加算用
public:
	virtual ~CharaBase() = default;
	// 初期化処理
	void Init(const CharaData& base, int level) {
		this->level = level;
		this->charaData.id = base.id;
		this->charaData.name = base.name;
		this->charaData.hp = base.hp + level * LevelUpHpBonus;
		this->charaData.atk = base.atk + level * LevelUpAtkBonus;
		this->charaData.def = base.def + level * LevelUpDefBonus;
	}
	// 死亡判定
	bool IsDead() const { return charaData.hp <= 0; }
	// 情報アクセス
	const CharaData& GetData() { return charaData; }
	// レベル
	int GetLevel() { return level; }
	// HPのセッター
	void SetHP(int hp) { charaData.hp = hp; }
	// ダメージを受ける
	void TakeDamage(int dmg) {
		charaData.hp -= dmg;
		if (charaData.hp < 0) {
			charaData.hp = 0;
		}
	}
};