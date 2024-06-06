#pragma once
#include "DxLib.h"
#include "time.h"
#include <math.h>
#include <vector>
#include <memory>
#include <random>

#include "map.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerupTrout.h"

class GameScene
{
public:

	//�Q�[�����ɋN��
	void Run();

	//������
	void Initialize();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�^�[���`�F���W
	void TurnChange();

private:

	//player����
	std::unique_ptr<Player> player = std::make_unique<Player>();

	//�}�b�v
	std::unique_ptr<Map> map = std::make_unique<Map>();

	//enemy�i�[�p
	std::vector<Enemy> enemies;

	//
	std::vector<PowerupTrout> powerups;

	//�t�F�[�Y
	size_t phase;

	//�^�[��
	int turn = 0;

	//�G�X�V
	void EnemyUpdate();
};