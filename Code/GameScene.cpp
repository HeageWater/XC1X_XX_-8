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
	////ロール初期化
	//Roll::GetInstance()->Initialize();

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
				phase = BattlePhase;
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

		break;

	default:

		break;
	}
}
