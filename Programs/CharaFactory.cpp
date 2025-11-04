#include "CharaFactory.h"

// プレイヤーデータ
const CharaData CharacterFactory::PlayerBaseState[] = {
    {0,"勇者",100,50,10},
    {1,"魔術師",100,50,10},
    {2,"ナイトメア",100,50,10},
    {3,"マリオネスト",100,50,10},
    {4,"ウォーリアー",100,50,10},
};
// エネミーデータ
const CharaData CharacterFactory::EnemyBaseState[] = {
    {0,"ゴブリン",100,50,10},
    {1,"スライム",100,50,10},
    {2,"ワイバーン",100,50,10},
    {3,"ガーゴイル",100,50,10},
    {4,"スケルトン",100,50,10},
};
// データサイズ
const int CharacterFactory::PlayerTableSize = sizeof(PlayerBaseState) / sizeof(CharaData);
const int CharacterFactory::EnemyTableSize = sizeof(EnemyBaseState) / sizeof(CharaData);
// プレイヤー生成
PoolHandle<CharaBase> CharacterFactory::CreatePlayer(int ID, int level) {
    // IDが見つからない場合
    if (ID < 0 || ID >= PlayerTableSize) {
        std::cerr << "Failure: CharacterFactory::CreatePlayer - invalid ID\n";
    }

    auto player = playerPool.Acquire();
    player->Init(PlayerBaseState[ID], level);
    return player;
}
// エネミー生成
PoolHandle<CharaBase> CharacterFactory::CreateEnemy(int ID, int level) {
    // IDが見つからない場合
    if (ID < 0 || ID >= EnemyTableSize) {
        std::cerr << "Failure: CharacterFactory::CreateEnemy - invalid ID\n";
    }
    
    auto enemy = enemyPool.Acquire();
    enemy->Init(EnemyBaseState[ID], level);
    return enemy;
}
