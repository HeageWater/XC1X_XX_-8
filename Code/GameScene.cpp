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
	//�X�V
	Update();
}

void GameScene::Initialize()
{
	////���[��������
	//Roll::GetInstance()->Initialize();

	//������
	player->Initialize();

	//�}�b�v������
	map->Initialize();

	//�ŏ��̓}�b�v����
	phase = MapPhase;
}

void GameScene::Update()
{
	//�}�X�̎�ފi�[�p
	size_t troutKind;

	//���͍X�V
	Input::GetInstance()->Update();

	//�t�F�[�Y
	switch (phase)
	{
	case MapPhase:

		//�}�b�v�X�V
		map->Update();

		//space�Ń}�X�ɓ���
		if (Input::GetInstance()->KeyTrigger(KEY_INPUT_SPACE))
		{
			//�}�X�̎�ފi�[
			troutKind = map->GetTrout();

			//�t�F�[�Y�ړ�
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

		//�v���C���[�X�V
		player->Update();

		break;

	case ItemPhase:

		break;

	case PowerupPhase:

		break;

	default:

		break;
	}

	//O,P�Ńt�F�[�Y�؂�ւ�
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
	//�t�F�[�Y
	switch (phase)
	{
	case MapPhase:

		//�}�b�v�`��
		map->Draw();

		break;

	case BattlePhase:

		//�v���C���[�`��
		player->Draw();

		break;

	default:

		break;
	}
}
