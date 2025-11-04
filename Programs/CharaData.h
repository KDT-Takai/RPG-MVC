#pragma once
#include <string>

// EntityData Entity‚ªŽ‚Âî•ñ
struct CharaData {
    int id;             // ID
	std::string name;   // –¼‘O
    int hp = 0;         // ƒqƒbƒgƒ|ƒCƒ“ƒg
    int atk = 0;        // UŒ‚—Í
    int def = 0;        // –hŒä—Í

    CharaData() = default;
    
    CharaData(int argId, std::string argName = "none name", int argHp = 1, int argAtk = 1, int argDef = 1) {
        this->id = argId;
        this->name = argName;
        this->hp = argHp;
        this->atk = argAtk;
        this->def = argDef;
    }
};