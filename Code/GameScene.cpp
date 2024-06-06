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
				//�o�g���t�F�[�Y�ֈڍs
				phase = BattlePhase;

				//�v���C���[�̃^�[������
				player->SetIsAttack(true);

				//�G����
				Enemy newEnemy;

				//������
				newEnemy.Initialize();

				//�i�[
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

		//�v���C���[�X�V
		player->Update();

		//�G�X�V
		EnemyUpdate();

		//�^�[���`�F���W
		TurnChange();

		//�G��|������
		for (size_t i = 0; i < enemies.size(); i++)
		{
			if (enemies[i].GetDeadFlag()) {
				//�폜
				enemies.erase(enemies.begin() + i);
				//�{���͕�V�����ǃ��ł͂��̂܂ܖ߂�
				phase = MapPhase;
			}
		}
		//�������Ƃ�
		if (player->GetDeadFlag()) {
			//�����ŃQ�[���I�[�o�[
			//���ŗp
			player->Reset();
			phase = MapPhase;
			//�G�̍폜
			for (size_t i = 0; i < enemies.size(); i++)
			{
				//�폜
				enemies.erase(enemies.begin() + i);
			}
		}

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

		//�G�`��
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].Draw();
		}

		break;

	default:

		break;
	}
}

void GameScene::TurnChange()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		//�v���C���[�̃^�[���`�F���W�t���O
		if (player->GetTurnChange()) {
			//�v���C���[�̍U����������
			enemies[i].SetIsAttack(true);
			enemies[i].SetPlayerStatus(player->GetStatus());
			enemies[i].Collision();
			player->SetTurnChange(false);
		}

		//�G�̃^�[���`�F���W�t���O
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

		//�X�V
		enemies[i].Update();
		////�G�̍U������
		//if (enemies[i].GetIsAttack()) {
		//	enemies[i].SetIsAttack(false);
		//	player->SetIsAttack(true);
		//	player->SetEnemyStatus(enemies[i].GetStatus());
		//	player->Collision();
		//}

		////�v���C���[�̍U����������
		//if (player->GetIsAttack()) {
		//	player->SetIsAttack(false);
		//	enemies[i].SetIsAttack(true);
		//	enemies[i].SetPlayerStatus(player->GetStatus());
		//}

		////deadflag��true��������폜
		//if (enemies[i].GetDeadFlag())
		//{
		//	//�폜
		//	enemies.erase(enemies.begin() + i);
		//}

	}
}
