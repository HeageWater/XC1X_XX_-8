#include "GameScene.h"
#include "Input.h"
#include "roll.h"

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
}

void GameScene::Update()
{
	//入力更新
	Input::GetInstance()->Update();

	////ロール更新
	//Roll::GetInstance()->Updare();

	//プレイヤー更新
	player->Update();
}

void GameScene::Draw()
{
	////ロール描画
	//Roll::GetInstance()->Draw();

	//プレイヤー描画
	player->Draw();
}
