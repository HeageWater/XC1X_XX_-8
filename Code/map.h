#pragma once

// �}�X
enum
{
	BLANK,	//��
	BATTLE,//�퓬
	ITEM,//�A�C�e��
	POWERUP,//����
};

//��
struct Load
{
	//��
	size_t width_ = 5;

	//�c
	size_t height_ = 10;

	//���i�[�p
	size_t load_[5][10];
};

class Map
{
public:

	//������
	void Initialize();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�������ꏊ�̃}�X�̎�ނ�Ԃ�
	size_t GetTrout();

private:

	//�}�b�v����
	void MapCreate();

	//��
	size_t width_ = 5;

	//�c
	size_t height_ = 10;

	//���i�[�p
	size_t load_[5][10];

	//���ݒn
	size_t nowPoint[2];

	//�X�N���[���p
	size_t scllorY = 0;

	//�������悤
	size_t now = 0;
	bool nowF = false;

	//���\�[�X
	size_t battlePng;
	size_t itemPng;
	size_t powerPng;
};