#pragma once
#include "DxLib.h"
#include "time.h"
#include <math.h>
#include <vector>
#include <memory>
#include <random>

#include "map.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerupTrout.h"

class GameScene
{
public:

	//ゲーム中に起動
	void Run();

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//ターンチェンジ
	void TurnChange();

private:

	//player生成
	std::unique_ptr<Player> player = std::make_unique<Player>();

	//マップ
	std::unique_ptr<Map> map = std::make_unique<Map>();

	//enemy格納用
	std::vector<Enemy> enemies;

	//
	std::vector<PowerupTrout> powerups;

	//フェーズ
	size_t phase;

	//ターン
	int turn = 0;

	//敵更新
	void EnemyUpdate();
};