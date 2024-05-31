#include "GameScene.h"
#include "Input.h"
#include "roll.h"

void GameScene::Run()
{
	//�X�V
	Update();
}

void GameScene::Initialize()
{
	//���[��������
	Roll::GetInstance()->Initialize();
}

void GameScene::Update()
{
	//���͍X�V
	Input::GetInstance()->Update();

	//���[���X�V
	Roll::GetInstance()->Updare();
}

void GameScene::Draw()
{
	//���[���`��
	Roll::GetInstance()->Draw();
}
