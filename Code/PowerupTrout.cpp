#include "PowerupTrout.h"
#include "DxLib.h"
#include "Input.h"

void PowerupTrout::Initialize()
{
	//��������
	status.hp = 0;
	status.power = 0;
	status.speed = 0;
}

void PowerupTrout::Update()
{
	//����
	int plus = rand() % 3 + 2;

	//�L�[�ɉ����ăX�e�[�^�X�A�b�v
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_Z))
	{
		status.hp += plus;
	}
	else if (Input::GetInstance()->KeyTrigger(KEY_INPUT_X))
	{
		status.power += plus;
	}
	else if (Input::GetInstance()->KeyTrigger(KEY_INPUT_C))
	{
		status.speed += plus;
	}
}

void PowerupTrout::Draw()
{
	DrawFormatString(300, 200, 0xaaaaaa, "Z��HP,X�ōU����,C�őf���������ʏオ��");
}
