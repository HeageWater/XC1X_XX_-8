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

	//�^�C�g��
	scene = Title;

	//���\�[�X�ǂݍ���
	titlePng = LoadGraph("Resource//title.png");
	gameoverPng = LoadGraph("Resource//gameover.png");
	clearPng= LoadGraph("Resource//clear.png");
	mapBackGroundPng= LoadGraph("Resource//mapBackGround.png");
	playBackGroundPng = LoadGraph("Resource//gameBackGround.png");
}

void GameScene::Update()
{
	//���͍X�V
	Input::GetInstance()->Update();

	//�t�F�[�Y
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
	//�t�F�[�Y
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

void GameScene::Finalize()
{
	//�G�������J��
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies.erase(enemies.begin() + i);
	}

	//�摜�������J��
	InitGraph();

	//�T�E���h�������J��
	InitSoundMem();
}
void GameScene::PlayScene()
{
	//�}�X�̎�ފi�[�p
	size_t troutKind;

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
				//�A�C�e���t�F�[�Y�ֈڍs
				phase = ItemPhase;
			}
			else if (troutKind == POWERUP)
			{
				//�p���[�A�b�v�t�F�[�Y�ֈڍs
				phase = PowerupPhase;

				//�G����
				PowerupTrout newPower;

				//������
				newPower.Initialize();

				//�i�[
				powerups.push_back(newPower);

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

		for (size_t i = 0; i < powerups.size(); i++)
		{
			//�X�V
			powerups[i].Update();

			//�L�[�ɉ����ăX�e�[�^�X�A�b�v
			if (Input::GetInstance()->KeyTrigger(KEY_INPUT_Z) || Input::GetInstance()->KeyTrigger(KEY_INPUT_X) || Input::GetInstance()->KeyTrigger(KEY_INPUT_C))
			{
				//�v���C���[����
				player->PlusStatus(powerups[i].GetStatus());

				//�}�b�v�t�F�[�Y��
				phase = MapPhase;
			}

			//����
			if (powerups[i].GetDeleteFlag())
			{
				powerups.erase(powerups.begin() + i);
			}
		}

	default:

		break;
	}

	//��ŏ���
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

void GameScene::TitleScene()
{
	//play��
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
	//�t�F�[�Y
	switch (phase)
	{
	case MapPhase:

		//�w�i
		DrawGraph(0, 0, mapBackGroundPng, 0);
		//�}�b�v�`��
		map->Draw();

		//player�X�e�[�^�X�\��
		DrawFormatString(480, 510, 0xaaaaaa, "�v���C���[�X�e�[�^�X");
		DrawFormatString(480, 540, 0xaaaaaa, "�v���C���[ HP :%d", player->GetStatus().hp);
		DrawFormatString(480, 570, 0xaaaaaa, "�v���C���[ POWER :%d", player->GetStatus().power);
		DrawFormatString(480, 600, 0xaaaaaa, "�v���C���[ SPEED :%d", player->GetStatus().speed);

		break;

	case BattlePhase:

		//�w�i
		DrawGraph(0, 0, playBackGroundPng, 0);

		//�v���C���[�`��
		player->Draw();

		//�G�`��
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].Draw();
		}

		//player�X�e�[�^�X�\��
		DrawFormatString(480, 510, 0xaaaaaa, "�v���C���[�X�e�[�^�X");
		DrawFormatString(480, 540, 0xaaaaaa, "�v���C���[ HP :%d", player->GetStatus().hp);
		DrawFormatString(480, 570, 0xaaaaaa, "�v���C���[ POWER :%d", player->GetStatus().power);
		DrawFormatString(480, 600, 0xaaaaaa, "�v���C���[ SPEED :%d", player->GetStatus().speed);

		break;

	default:

		break;
	}
}

void GameScene::TitleDraw()
{
	//�^�C�g��
	DrawGraph(0, 0, titlePng, 0);
}

void GameScene::GameoverDraw()
{
	//�Q�[���I�[�o�[
	DrawGraph(0, 0, gameoverPng, 0);
}

void GameScene::ClearDraw()
{
	//�N���A
	DrawGraph(0, 0, clearPng, 0);
}
