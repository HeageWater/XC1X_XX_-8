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

	//�������J��
	void Finalize();

private:

	//player����
	std::unique_ptr<Player> player = std::make_unique<Player>();

	//�}�b�v
	std::unique_ptr<Map> map = std::make_unique<Map>();

	//enemy�i�[�p
	std::vector<Enemy> enemies;

	//�t�F�[�Y
	size_t phase;

	//�V�[��
	size_t scene;

	//�G�X�V
	void EnemyUpdate();

	//�e�V�[��
	void PlayScene();
	void TitleScene();
	void GameoverScene();
	void ClearScene();
};