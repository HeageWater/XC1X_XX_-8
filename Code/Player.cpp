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

	//�X�e�[�^�X
	status.hp = 10;
	status.power = 1;
	status.speed = 1;

	//���\�[�X
	weakPng = LoadGraph("Resource//weak.png");
	mediumPng = LoadGraph("Resource//mid.png");
	strongPng = LoadGraph("Resource//strong.png");

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
	//�f�X�t���O
	if (status.hp <= 0) {
		deadFlag = true;
	}
}

void Player::Draw()
{
	//�U����I��ł��Ȃ���
	if (!isAttack) {
		DrawFormatString(280, 360, 0xaaaaaa, "�U��:ENTER");
	}
	//�I�񂾎�
	else if (isAttack) {
		//���v�l�̎Z�o
		if (isAttackProbability == false && isThird == true) {
			DrawFormatString(280, 360, 0xaaaaaa, "�U���l:%d  ENTER", status.power);
		}
		//���\�[�X
		//�I����
		DrawGraph(100, 550, weakPng, 0);
		DrawGraph(200, 550, mediumPng, 0);
		DrawGraph(300, 550, strongPng, 0);
		
		//�m���\��
		DrawFormatString(0, 650, 0xaaaaaa, "�m��");
		DrawFormatString(100, 650, 0xaaaaaa, "%d%%", weakAttackProbability);
		DrawFormatString(200, 650, 0xaaaaaa, "%d%%", mediumAttackProbability);
		DrawFormatString(300, 650, 0xaaaaaa, "%d%%", strongAttackProbability);
		//�U���͕\��
		DrawFormatString(0, 700, 0xaaaaaa, "�U����");
		DrawFormatString(100, 700, 0xaaaaaa, "%d", weakAttack);
		DrawFormatString(200, 700, 0xaaaaaa, "%d", mediumAttack);
		DrawFormatString(300, 700, 0xaaaaaa, "%d", strongAttack);
		//������@
		DrawFormatString(450, 400, 0xaaaaaa, "�O��U�����@��I��");
		DrawFormatString(450, 450, 0xaaaaaa, "A,D�őI��:Space�Ō���");
		//�̗�
		DrawFormatString(450, 700, 0xaaaaaa, "PlayerHP:%d", status.hp);


		//����I�񂾂�
		////��Ԗ�
		if (isFirst) {
			DrawFormatString(100, 400, 0xaaaaaa, "1:");
			if (first == weak) {
				DrawGraph(120, 400, weakPng, 0);
			}
			else if (first == medium) {
				DrawGraph(120, 400, mediumPng, 0);
			}
			else if (first == strong) {
				DrawGraph(120, 400, strongPng, 0);
				
			}
		}
		////��Ԗ�
		if (isSecond) {
			DrawFormatString(200, 400, 0xaaaaaa, "2:");
			if (second == weak) {
				DrawGraph(220, 400, weakPng, 0);
			}
			else if (second == medium) {
				DrawGraph(220, 400, mediumPng, 0);
			}
			else if (second == strong) {
				DrawGraph(220, 400, strongPng, 0);
			}
		}
		////�O�Ԗ�
		if (isThird) {
			DrawFormatString(300, 400, 0xaaaaaa, "3:");
			if (third == weak) {
				DrawGraph(320, 400, weakPng, 0);
			}
			else if (third == medium) {
				DrawGraph(320, 400, mediumPng, 0);
			}
			else if (third == strong) {
				DrawGraph(320, 400, strongPng, 0);
			}
		}

		//���ǂ��I�����Ă��邩
		if (attackSelect == weak) {
			DrawFormatString(50, 500, 0xaaaaaa, "���I��");
			//�m���\��
			DrawFormatString(140, 500, 0xaaaaaa, "�m��:");
			DrawFormatString(180, 500, 0xaaaaaa, "%d%%", weakAttackProbability);
			//�U���͕\��
			DrawFormatString(220, 500, 0xaaaaaa, "�U����:");
			DrawFormatString(280, 500, 0xaaaaaa, "%d", weakAttack);
		}
		else if (attackSelect == medium) {
			DrawFormatString(50, 500, 0xaaaaaa, "����I��");
			//�m���\��
			DrawFormatString(140, 500, 0xaaaaaa, "�m��:");
			DrawFormatString(180, 500, 0xaaaaaa, "%d%%", mediumAttackProbability);
			//�U���͕\��
			DrawFormatString(220, 500, 0xaaaaaa, "�U����:");
			DrawFormatString(280, 500, 0xaaaaaa, "%d", mediumAttack);
		}
		else if (attackSelect == strong) {
			DrawFormatString(50, 500, 0xaaaaaa, "����I��");
			//�m���\��
			DrawFormatString(140, 500, 0xaaaaaa, "�m��:");
			DrawFormatString(180, 500, 0xaaaaaa, "%d%%", strongAttackProbability);
			//�U���͕\��
			DrawFormatString(220, 500, 0xaaaaaa, "�U����:");
			DrawFormatString(280, 500, 0xaaaaaa, "%d", strongAttack);
			
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
		else if (attackSelect == strong) {
			attackSelect = medium;
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
		if (isFirst == false) {
			first = attackSelect;
			isFirst = true;
		}
		//��Ԗ�
		else if (isSecond == false) {
			second = attackSelect;
			isSecond = true;
		}
		//�O�Ԗ�
		else if (isThird == false) {
			third = attackSelect;
			isThird = true;
			isAttackProbability = true;
		}
	}
	//�A�^�b�N�̌v�Z
	if (isAttackProbability) {
		status.power = 0;
		//�A�^�b�N�̊m��
		int firstProbability = (rand() % 100) + 1;
		int secondProbability = (rand() % 100) + 1;
		int thirdProbability = (rand() % 100) + 1;

		////���////
		//��
		if (first == weak) {
			if (weakAttackProbability >= firstProbability) {
				status.power += weakAttack;
			}
		}
		//��
		else if (first == medium) {
			if (mediumAttackProbability >= firstProbability) {
				status.power += mediumAttack;
			}
		}
		//��
		else if (first == strong) {
			if (strongAttackProbability >= firstProbability) {
				status.power += strongAttack;
			}
		}

		////���////
		//��
		if (second == weak) {
			if (weakAttackProbability >= secondProbability) {
				status.power += weakAttack;
			}
		}
		//��
		else if (second == medium) {
			if (mediumAttackProbability >= secondProbability) {
				status.power += mediumAttack;
			}
		}
		//��
		else if (second == strong) {
			if (strongAttackProbability >= secondProbability) {
				status.power += strongAttack;
			}
		}

		////�O��////
		//��
		if (third == weak) {
			if (weakAttackProbability >= thirdProbability) {
				status.power += weakAttack;
			}
		}
		//��
		else if (third == medium) {
			if (mediumAttackProbability >= thirdProbability) {
				status.power += mediumAttack;
			}
		}
		//��
		else if (third == strong) {
			if (strongAttackProbability >= thirdProbability) {
				status.power += strongAttack;
			}
		}
		isAttackProbability = false;
	}

	//�A�^�b�N�̏I���
	if (isAttackProbability == false && isThird == true) {
		if (Input::GetInstance()->KeyTrigger(KEY_INPUT_RETURN)) {
			isFirst = false;
			isSecond = false;
			isThird = false;
			isAttackProbability = false;
			isAttack = false;
			turnChange = true;
		}
	}

}

void Player::Collision()
{
	status.hp -= enemyStatus.power;
}

void Player::Reset()
{
	//�X�e�[�^�X
	status.hp = 10;
	status.power = 1;
	status.speed = 1;
	//�A�^�b�N�l�̏�����
	weakAttack = initialWeakAttack;
	mediumAttack = initialMediumAttack;
	strongAttack = initialStrongttack;

	//�m���l�̏�����
	weakAttackProbability = initialWeakAttackProbability;
	mediumAttackProbability = initialMediumAttackProbability;
	strongAttackProbability = initialStrongAttackProbability;

	//���񂾔���̏�����
	deadFlag = false;
}

void Player::PlusStatus(Status state)
{
	status.hp += state.hp;
	status.power += state.power;
	status.speed += state.speed;
}
