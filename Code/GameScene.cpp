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

enum Scene
{
	Title,
	Play,
	Clear,
	Over,
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

	//タイトル
	scene = Title;

	//リソース読み込み
	titlePng = LoadGraph("Resource//title.png");
	gameoverPng = LoadGraph("Resource//gameover.png");
	clearPng= LoadGraph("Resource//clear.png");
	mapBackGroundPng= LoadGraph("Resource//mapBackGround.png");
	playBackGroundPng = LoadGraph("Resource//gameBackGround.png");
}

void GameScene::Update()
{
	//入力更新
	Input::GetInstance()->Update();

	//フェーズ
	switch (scene)
	{
	case Title:

		TitleScene();

		break;

	case Play:

		PlayScene();

		break;

	case Clear:

		ClearScene();

		break;

	case Over:

		GameoverScene();

		break;

	default:
		break;
	}
}

void GameScene::Draw()
{
	//フェーズ
	switch (scene)
	{
	case Title:

		TitleDraw();

		break;

	case Play:

		PlayDraw();

		break;

	case Clear:

		ClearDraw();

		break;

	case Over:

		GameoverDraw();

		break;

	default:
		break;
	}
}

void GameScene::TurnChange()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		//プレイヤーのターンチェンジフラグ
		if (player->GetTurnChange()) {
			//プレイヤーの攻撃処理判定
			enemies[i].SetIsAttack(true);
			enemies[i].SetPlayerStatus(player->GetStatus());
			enemies[i].Collision();
			player->SetTurnChange(false);
		}

		//敵のターンチェンジフラグ
		if (enemies[i].GetTurnChange()) {
			player->SetIsAttack(true);
			player->SetEnemyStatus(enemies[i].GetStatus());
			player->Collision();
			enemies[i].SetTurnChange(false);
		}
	}
}

void GameScene::EnemyUpdate()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		//更新
		enemies[i].Update();
		////敵の攻撃判定
		//if (enemies[i].GetIsAttack()) {
		//	enemies[i].SetIsAttack(false);
		//	player->SetIsAttack(true);
		//	player->SetEnemyStatus(enemies[i].GetStatus());
		//	player->Collision();
		//}

		////プレイヤーの攻撃処理判定
		//if (player->GetIsAttack()) {
		//	player->SetIsAttack(false);
		//	enemies[i].SetIsAttack(true);
		//	enemies[i].SetPlayerStatus(player->GetStatus());
		//}

		////deadflagがtrueだったら削除
		//if (enemies[i].GetDeadFlag())
		//{
		//	//削除
		//	enemies.erase(enemies.begin() + i);
		//}

	}
}

void GameScene::Finalize()
{
	//敵メモリ開放
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies.erase(enemies.begin() + i);
	}

	//画像メモリ開放
	InitGraph();

	//サウンドメモリ開放
	InitSoundMem();
}
void GameScene::PlayScene()
{
	//マスの種類格納用
	size_t troutKind;

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

				//プレイヤーのターンから
				player->SetIsAttack(true);

				//敵生成
				Enemy newEnemy;

				//初期化
				newEnemy.Initialize();

				//格納
				enemies.push_back(newEnemy);

			}
			else if (troutKind == ITEM)
			{
				//アイテムフェーズへ移行
				phase = ItemPhase;
			}
			else if (troutKind == POWERUP)
			{
				//パワーアップフェーズへ移行
				phase = PowerupPhase;

				//敵生成
				PowerupTrout newPower;

				//初期化
				newPower.Initialize();

				//格納
				powerups.push_back(newPower);

			}
		}

		break;

	case BattlePhase:

		//プレイヤー更新
		player->Update();

		//敵更新
		EnemyUpdate();

		//ターンチェンジ
		TurnChange();

		//敵を倒した時
		for (size_t i = 0; i < enemies.size(); i++)
		{
			if (enemies[i].GetDeadFlag()) {
				//削除
				enemies.erase(enemies.begin() + i);
				//本来は報酬だけどα版はそのまま戻る
				phase = MapPhase;
			}
		}
		//負けたとき
		if (player->GetDeadFlag()) {
			//ここでゲームオーバー
			//α版用
			player->Reset();
			phase = MapPhase;
			//敵の削除
			for (size_t i = 0; i < enemies.size(); i++)
			{
				//削除
				enemies.erase(enemies.begin() + i);
			}
		}


		break;

	case ItemPhase:

		break;

	case PowerupPhase:

		for (size_t i = 0; i < powerups.size(); i++)
		{
			//更新
			powerups[i].Update();

			//キーに応じてステータスアップ
			if (Input::GetInstance()->KeyTrigger(KEY_INPUT_Z) || Input::GetInstance()->KeyTrigger(KEY_INPUT_X) || Input::GetInstance()->KeyTrigger(KEY_INPUT_C))
			{
				//プレイヤー強化
				player->PlusStatus(powerups[i].GetStatus());

				//マップフェーズへ
				phase = MapPhase;
			}

			//消去
			if (powerups[i].GetDeleteFlag())
			{
				powerups.erase(powerups.begin() + i);
			}
		}

	default:

		break;
	}

	//後で消す
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

void GameScene::TitleScene()
{
	//playへ
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_SPACE))
	{
		scene = Play;
	}
}

void GameScene::GameoverScene()
{
}

void GameScene::ClearScene()
{
}

void GameScene::PlayDraw()
{
	//フェーズ
	switch (phase)
	{
	case MapPhase:

		//背景
		DrawGraph(0, 0, mapBackGroundPng, 0);
		//マップ描画
		map->Draw();

		//playerステータス表示
		DrawFormatString(480, 510, 0xaaaaaa, "プレイヤーステータス");
		DrawFormatString(480, 540, 0xaaaaaa, "プレイヤー HP :%d", player->GetStatus().hp);
		DrawFormatString(480, 570, 0xaaaaaa, "プレイヤー POWER :%d", player->GetStatus().power);
		DrawFormatString(480, 600, 0xaaaaaa, "プレイヤー SPEED :%d", player->GetStatus().speed);

		break;

	case BattlePhase:

		//背景
		DrawGraph(0, 0, playBackGroundPng, 0);

		//プレイヤー描画
		player->Draw();

		//敵描画
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].Draw();
		}

		//playerステータス表示
		DrawFormatString(480, 510, 0xaaaaaa, "プレイヤーステータス");
		DrawFormatString(480, 540, 0xaaaaaa, "プレイヤー HP :%d", player->GetStatus().hp);
		DrawFormatString(480, 570, 0xaaaaaa, "プレイヤー POWER :%d", player->GetStatus().power);
		DrawFormatString(480, 600, 0xaaaaaa, "プレイヤー SPEED :%d", player->GetStatus().speed);

		break;

	default:

		break;
	}
}

void GameScene::TitleDraw()
{
	//タイトル
	DrawGraph(0, 0, titlePng, 0);
}

void GameScene::GameoverDraw()
{
	//ゲームオーバー
	DrawGraph(0, 0, gameoverPng, 0);
}

void GameScene::ClearDraw()
{
	//クリア
	DrawGraph(0, 0, clearPng, 0);
}
