#pragma once
#include "DxLib.h"
#include "time.h"
#include"Player.h"
//
#include "map.h"
#include <math.h>
#include <vector>
#include <memory>
#include <random>
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
private:
	std::unique_ptr<Player> player = std::make_unique<Player>();
};