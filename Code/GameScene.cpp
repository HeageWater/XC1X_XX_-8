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
}

void GameScene::Update()
{
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

void GameScene::EnemyUpdate()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		//�X�V
		enemies[i].Update();

		//deadflag��true��������폜
		if (enemies[i].GetDeadFlag())
		{
			//�폜
			enemies.erase(enemies.begin() + i);
		}
	}
}

void GameScene::PlayScene()
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
			}
		}

		break;

	case BattlePhase:

		//�v���C���[�X�V
		player->Update();

		//�G�X�V
		EnemyUpdate();

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

void GameScene::TitleDraw()
{
}

void GameScene::GameoverDraw()
{
}

void GameScene::ClearDraw()
{
}
