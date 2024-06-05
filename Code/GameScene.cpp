#include "GameScene.h"
#include "Input.h"
#include "roll.h"

enum Phase
{
	MapPhase,
	BattlePhase,
	ItemPhase,
	PowerupPhase,
};

void GameScene::Run()
{
	//更新
	Update();
}

void GameScene::Initialize()
{

	//初期化
	player->Initialize();

	//マップ初期化
	map->Initialize();

	//最初はマップから
	phase = MapPhase;
}

void GameScene::Update()
{
	//マスの種類格納用
	size_t troutKind;

	//入力更新
	Input::GetInstance()->Update();

	//フェーズ
	switch (phase)
	{
	case MapPhase:

		//マップ更新
		map->Update();

		//spaceでマスに入る
		if (Input::GetInstance()->KeyTrigger(KEY_INPUT_SPACE))
		{
			//マスの種類格納
			troutKind = map->GetTrout();

			//フェーズ移動
			if (troutKind == BATTLE)
			{
				//バトルフェーズへ移行
				phase = BattlePhase;

				//敵生成
				Enemy newEnemy;

				//初期化
				newEnemy.Initialize();

				//格納
				enemies.push_back(newEnemy);
			}
			else if (troutKind == ITEM)
			{
				phase = ItemPhase;
			}
			else if (troutKind == POWERUP)
			{
				phase = PowerupPhase;
			}
		}

		break;

	case BattlePhase:

		//プレイヤー更新
		player->Update();

		//敵更新
		EnemyUpdate();

		break;

	case ItemPhase:

		break;

	case PowerupPhase:

		break;

	default:

		break;
	}

	//O,Pでフェーズ切り替え
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_O))
	{
		phase = MapPhase;
	}
	else if (Input::GetInstance()->KeyTrigger(KEY_INPUT_P))
	{
		phase = BattlePhase;
	}
}

void GameScene::Draw()
{
	//フェーズ
	switch (phase)
	{
	case MapPhase:

		//マップ描画
		map->Draw();

		break;

	case BattlePhase:

		//プレイヤー描画
		player->Draw();

		//敵描画
		//for (size_t i = 0; i < enemies.size(); i++)
		//{
			enemies[0].Draw();
		//}

		break;

	default:

		break;
	}
}

void GameScene::EnemyUpdate()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		//更新
		enemies[i].Update();

		//deadflagがtrueだったら削除
		if (enemies[i].GetDeadFlag())
		{
			//削除
			enemies.erase(enemies.begin() + i);
		}
	}
}
