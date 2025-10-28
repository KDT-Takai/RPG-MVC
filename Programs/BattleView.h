#pragma once
#include <iostream>
#include "CharaData.h"

// 戦闘画面の表示
class BattleView {
public:
	// ステータス表示
	void ShowStatus(int lvl, CharaData data) {
		std::cout << "LEVEL" << lvl << "ID:" << data.id << "NAME:" << data.name << " HP:" << data.hp << " ATK:" << data.atk
			<< "DEF:" << data.def << std::endl;
	}
	// ダメージ表示
	void ShowDamge(std::string name, int damage) {
		std::cout << name << "に" << damage << "ダメージ！" << std::endl;
	}
	// メッセージ表示
	void ShowMassage(std::string msg) {
		std::cout << msg << std::endl;
	}
};