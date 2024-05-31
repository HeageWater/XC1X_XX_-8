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
	////���[��������
	//Roll::GetInstance()->Initialize();

	//������
	player->Initialize();
}

void GameScene::Update()
{
	//���͍X�V
	Input::GetInstance()->Update();

	////���[���X�V
	//Roll::GetInstance()->Updare();

	//�v���C���[�X�V
	player->Update();
}

void GameScene::Draw()
{
	////���[���`��
	//Roll::GetInstance()->Draw();

	//�v���C���[�`��
	player->Draw();
}
