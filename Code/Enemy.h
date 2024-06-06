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

	//�U������
	bool isAttack = false;

	//�v���C���[�̃X�e�[�^�X
	Status playerStatus;

	//�^�[��
	bool turnChange = false;
public:

	//������
	void Initialize();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�����蔻��
	void Collision();

	//�e��X�e�[�^�X�֌W
	void SetHitPoint(size_t hp);
	void SetPower(size_t power);
	void SetSpeed(size_t speed);
	void SetIsAttack(bool isAttack) { this->isAttack = isAttack; }
	void SetPlayerStatus(Status status) { playerStatus = status; }
	void SetTurnChange(bool turnChange_) { turnChange = turnChange_; }
	//�X�e�[�^�X��Ԃ�
	Status GetStatus() { return status; }

	//�����t���O�@�@�@�@
	bool GetDeadFlag() { return deadFlag; };
	//�U�����I������^�C�~���O
	bool GetIsAttack() { return isAttack; }
	//�^�[���`�F���W
	bool GetTurnChange() { return turnChange; }
private:
	
};