#include "Player.h"

void Player::Initialize()
{
	//�A�^�b�N�l�̏�����
	weakAttack = initialWeakAttack;
	mediumAttack = initialMediumAttack;
	strongAttack = initialStrongttack;

	//�m���l�̏�����
	weakAttackProbability = initialWeakAttackProbability;
	mediumAttackProbability = initialMediumAttackProbability;
	strongAttackProbability = initialStrongAttackProbability;
}

void Player::Update()
{
	//�U���̑I��
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_RETURN)) {
		isAttack = true;
	}
	//�U��
	if (isAttack == true) {
		Attack();
	}
}

void Player::Draw()
{
	//�U����I��ł��Ȃ���
	if (!isAttack) {
		DrawFormatString(50, 100, 0xaaaaaa, "�U��:ENTER");
	}
	//�I�񂾎�
	else if (isAttack) {
		//�I����
		DrawFormatString(50, 200, 0xaaaaaa, "��");
		DrawFormatString(100, 200, 0xaaaaaa, "��");
		DrawFormatString(150, 200, 0xaaaaaa, "��");
		//����I�񂾂�
		DrawFormatString(50, 100, 0xaaaaaa, "1:%s",first);
		DrawFormatString(100, 100, 0xaaaaaa, "2:%s", second);
		DrawFormatString(150, 100, 0xaaaaaa, "3:%s", third);
		//���ǂ��I�����Ă��邩
		if (attackSelect==weak) {
			DrawFormatString(50, 150, 0xaaaaaa, "weak��I��:space");
		}
		else if (attackSelect==medium) {
			DrawFormatString(50, 150, 0xaaaaaa, "medium��I��:space");
		}
		else if (attackSelect == strong) {
			DrawFormatString(50, 150, 0xaaaaaa, "strong��I��:space");
		}
	}
}

void Player::Attack()
{
	//�I��
	//��
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_A)) {
		if (attackSelect == weak) {
			attackSelect = strong;
		}
		else {
			attackSelect--;
		}
	}
	//�E
	else if (Input::GetInstance()->KeyTrigger(KEY_INPUT_D)) {
		if (attackSelect == strong) {
			attackSelect = weak;
		}
		else {
			attackSelect++;
		}
	}
	//����
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_SPACE)) {
		//��Ԗ�
		if (isFirst==false) {
			first = attackSelect;
			isFirst = true;
		}
		//��Ԗ�
		else if (isSecond==false) {
			second = attackSelect;
			isSecond = true;
		}
		//�O�Ԗ�
		else if (isThird==false) {
			third = attackSelect;
			isThird = true;
		}
	}
	//�A�^�b�N�̏I��
	if (isThird) {
		isFirst = false;
		isSecond = false;
		isThird = false;
		isAttack = false;
	}
}
