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
	//ロール初期化
	Roll::GetInstance()->Initialize();
}

void GameScene::Update()
{
	//入力更新
	Input::GetInstance()->Update();

	//ロール更新
	Roll::GetInstance()->Updare();
}

void GameScene::Draw()
{
	//ロール描画
	Roll::GetInstance()->Draw();
}
