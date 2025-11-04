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
	void ShowDamage(std::string name, int damage, bool isPlayer) {
		// プレイヤーの場合青、敵の場合赤
		std::string color = isPlayer ? "\033[34m" : "\033[31m";  // 青はプレイヤー、赤は敵
		std::cout << color << name << "\033[0mに" << "\033[33m" << damage << "ダメージ！\033[0m" << std::endl;
	}
	// メッセージ表示
	void ShowMassage(std::string msg) {
		std::cout << msg << std::endl;
	}
};