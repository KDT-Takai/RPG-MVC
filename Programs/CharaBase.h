#pragma once
#include <iostream>
#include "CharaData.h"	// EntityData Entityが持つ情報 名前,hpなど

class CharaBase {
protected:

	int level;				// レベル
	CharaData charaData;	// データ

public:

//	CharaBase() = default;
	virtual ~CharaBase() = default;
	// 初期化処理
	void Init(const CharaData& base, int level) {
		this->level = level;
		charaData.id = base.id;
		charaData.name = base.name;
		charaData.hp = base.hp + level * 10;
		charaData.atk = base.atk + level * 2;
		charaData.def = base.def + level * 2;
	}
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
		if (charaData.hp < 0) charaData.hp = 0;
	}
};