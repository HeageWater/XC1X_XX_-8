#include "DxLib.h"
#include "Input.h"
#pragma once
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

private://�ϐ�

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
	int first, second, third = 0;
	int attackSelect = 0;
	bool isFirst, isSecond, isThird = false;

	//�U���I���t���O
	bool isAttack = false;
};