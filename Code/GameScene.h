#pragma once
#include "DxLib.h"
#include "time.h"
#include"Player.h"
#include "map.h"
#include <math.h>
#include <vector>
#include <memory>
#include <random>
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

private:

	//player����
	std::unique_ptr<Player> player = std::make_unique<Player>();

	//�}�b�v
	std::unique_ptr<Map> map = std::make_unique<Map>();

	//�t�F�[�Y
	size_t phase;

};