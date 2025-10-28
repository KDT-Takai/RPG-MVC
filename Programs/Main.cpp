#include <iostream>
#include "ObjectPool.h"

#include "ScreenManager.h"

int main() {
	ScreenManager::Instance().Init();
	while (true) {
		ScreenManager::Instance().Update();
		ScreenManager::Instance().Render();
	}
	return 0;
}

// -------------------------------
// メモ
// -------------------------------
/*

// CharacterBase
Player
Enemy

// ファクトリーパターン
CharacterFactory
// 生成
// シングルトン 絶対シングルトンじゃなくていい
static CharacterBase* CreatePlayer(int id)
static CharacterBase* CreateEnemy(int id)
// データテーブル(CharacterFactory.cpp)

Pool
// オブジェクトプール
// Acquire()で生成する際に
// キャラクタの作成をしたい

Main
// 有限状態機械



一旦プールを使用せずにやるべき？
ファクトリー内部でプールを使って生成するのか
↑returnでいったん返す


*/