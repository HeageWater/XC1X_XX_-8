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

		//���v�l�̎Z�o
		if (isAttackProbability == false && isThird == true) {
			DrawFormatString(320, 160, 0xaaaaaa, "�U���l:%d", attackTotal);
		}
		else {
			//�I����
			DrawFormatString(50, 200, 0xaaaaaa, "��");
			DrawFormatString(100, 200, 0xaaaaaa, "��");
			DrawFormatString(150, 200, 0xaaaaaa, "��");
			//������@
			DrawFormatString(300, 200, 0xaaaaaa, "A,D�őI��:Space�Ō���");
			//����I�񂾂�
			////��Ԗ�
			if (isFirst) {
				if (first == weak) {
					DrawFormatString(50, 100, 0xaaaaaa, "1:weak");
				}
				else if (first == medium) {
					DrawFormatString(50, 100, 0xaaaaaa, "1:medium");
				}
				else if (first == strong) {
					DrawFormatString(50, 100, 0xaaaaaa, "1:strong");
				}
			}
			////��Ԗ�
			if (isSecond) {
				if (second == weak) {
					DrawFormatString(150, 100, 0xaaaaaa, "2:weak");
				}
				else if (second == medium) {
					DrawFormatString(150, 100, 0xaaaaaa, "2:medium");
				}
				else if (second == strong) {
					DrawFormatString(150, 100, 0xaaaaaa, "2:strong");
				}
			}
			////�O�Ԗ�
			if (isThird) {
				if (third == weak) {
					DrawFormatString(250, 100, 0xaaaaaa, "3:weak");
				}
				else if (third == medium) {
					DrawFormatString(250, 100, 0xaaaaaa, "3:medium");
				}
				else if (third == strong) {
					DrawFormatString(250, 100, 0xaaaaaa, "3:strong");
				}
			}

			//���ǂ��I�����Ă��邩
			if (attackSelect == weak) {
				DrawFormatString(50, 150, 0xaaaaaa, "weak��I��");
			}
			else if (attackSelect == medium) {
				DrawFormatString(50, 150, 0xaaaaaa, "medium��I��");
			}
			else if (attackSelect == strong) {
				DrawFormatString(50, 150, 0xaaaaaa, "strong��I��");
			}
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
		else if(attackSelect==strong){
			attackSelect=medium;
		}
		else if (attackSelect == medium) {
			attackSelect = weak;
		}
	}
	//�E
	else if (Input::GetInstance()->KeyTrigger(KEY_INPUT_D)) {
		if (attackSelect == strong) {
			attackSelect = weak;
		}
		else if (attackSelect == medium) {
			attackSelect = strong;
		}
		else if (attackSelect == weak) {
			attackSelect = medium;
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
			isAttackProbability = true;
		}
	}
	//�A�^�b�N�̌v�Z
	if (isAttackProbability) {
		//�A�^�b�N�̊m��
		int firstProbability = (rand() % 100)+1;
		int secondProbability = (rand() % 100) + 1;
		int thirdProbability = (rand() % 100) + 1;

		////���////
		//��
		if (first==weak) {
			if (weakAttackProbability >= firstProbability) {
				attackTotal += weakAttack;
			}
		}
		//��
		else if (first == medium) {
			if (mediumAttackProbability >= firstProbability) {
				attackTotal += mediumAttack;
			}
		}
		//��
		else if (first == strong) {
			if (strongAttackProbability >= firstProbability) {
				attackTotal += strongAttack;
			}
		}

		////���////
		//��
		if (second == weak) {
			if (weakAttackProbability >= secondProbability) {
				attackTotal += weakAttack;
			}
		}
		//��
		else if (second == medium) {
			if (mediumAttackProbability >= secondProbability) {
				attackTotal += mediumAttack;
			}
		}
		//��
		else if (second == strong) {
			if (strongAttackProbability >= secondProbability) {
				attackTotal += strongAttack;
			}
		}

		////�O��////
		//��
		if (third == weak) {
			if (weakAttackProbability >= thirdProbability) {
				attackTotal += weakAttack;
			}
		}
		//��
		else if (third == medium) {
			if (mediumAttackProbability >= thirdProbability) {
				attackTotal += mediumAttack;
			}
		}
		//��
		else if (third == strong) {
			if (strongAttackProbability >= thirdProbability) {
				attackTotal += strongAttack;
			}
		}
		isAttackProbability = false;
	}

	//�A�^�b�N�̏I���
	if (isAttackProbability == false && isThird == true) {
		if(Input::GetInstance()->KeyTrigger(KEY_INPUT_RETURN)) {
			isAttack = false;
			isFirst = false;
			isSecond = false;
			isThird = false;
			isAttackProbability = false;
			attackTotal = 0;
		}
	}

}
