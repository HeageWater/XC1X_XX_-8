#pragma once
#include "Status.h"

class Enemy
{
private:

	//�X�e�[�^�X
	Status status;

	//�����true�ɂ���Ə�����
	bool deadFlag;

	//�U��
	void Attack();

	//�h��
	void Block();

	//�u���b�N�t���O
	bool blockFlag;

public:

	//������
	void Initialize();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�e��X�e�[�^�X�֌W
	void SetHitPoint(size_t hp);
	void SetPower(size_t power);
	void SetSpeed(size_t speed);

	//�X�e�[�^�X��Ԃ�
	Status GetStatus() { return status; }

	//�����t���O�@�@�@�@
	bool GetDeadFlag() { return deadFlag; };
};