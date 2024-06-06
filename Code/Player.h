#include "DxLib.h"
#include "Input.h"
#pragma once
#include "DxLib.h"
#include "Input.h"
#include "Status.h"

enum Attack {
	weak,
	medium,
	strong
};

class Player
{
public://�֐�
	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�U��
	void Attack();
	//�U����H�炤
	void Collision();
	//���Z�b�g
	void Reset();
	//�Z�b�^�[
	//�e��X�e�[�^�X�֌W
	void SetHitPoint(size_t hp) { status.hp = hp; };
	void SetPower(size_t power) { status.power = power; };
	void SetSpeed(size_t speed) { status.speed = speed; };
	void SetIsAttack(bool isAttack) { this->isAttack = isAttack; }
	void SetEnemyStatus(Status status) { enemyStatus = status; }
	void SetTurnChange(bool turnChange_) { turnChange = turnChange_; }
	//�Q�b�^�[
	//�X�e�[�^�X��Ԃ�
	Status GetStatus() { return status; }
	//�X�e�[�^�X���Z
	void PlusStatus(Status state);
	//�U�����I������^�C�~���O
	bool GetIsAttack() { return isAttack; }
	//�^�[���`�F���W
	bool GetTurnChange() { return turnChange; }
	//���񂾔���
	bool GetDeadFlag() { return deadFlag; }
private://�ϐ�
	//�X�e�[�^�X
	Status status;
	Status enemyStatus;
	//�㒆���̃A�^�b�N�l
	int weakAttack = 0;
	int mediumAttack = 0;
	int strongAttack = 0;

	//�㒆���̊m���l
	int weakAttackProbability = 0;
	int mediumAttackProbability = 0;
	int strongAttackProbability = 0;

	//�����̃A�^�b�N�l
	int initialWeakAttack = 1;
	int initialMediumAttack = 3;
	int initialStrongttack = 5;

	//�����̊m���l
	int initialWeakAttackProbability = 80;
	int initialMediumAttackProbability = 50;
	int initialStrongAttackProbability = 20;

	//�U���̑I��
	enum Attack first, second, third = Attack::weak;
	enum Attack attackSelect = Attack::weak;
	bool isFirst, isSecond, isThird = false;
	//�U���I���t���O
	bool isAttack = false;

	//�A�^�b�N�̌v�Z�t���O
	bool isAttackProbability = false;

	//�f�X�t���O
	bool deadFlag = false;

	//�^�[���`�F���W
	bool turnChange = false;

	//���\�[�X
	size_t weakPng;
	size_t mediumPng;
	size_t strongPng;
};