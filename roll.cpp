#include "roll.h"
#include "Input.h"
#include "DxLib.h"

void Roll::Initialize()
{
	//������
	for (size_t i = 0; i < size; i++)
	{
		ans[i] = false;
	}
}

void Roll::Act()
{
	//����
	int a = rand() % 100;

	//space�������Ƃ����I�J�n
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_SPACE))
	{
		//�A��
		for (size_t i = 0; i < size; i++)
		{
			if (i < forcas)
			{
				ans[i] = 2;
				continue;
			}

			a = rand() % 100;

			//70�ȏ�Ŏ��s
			if (a < 70)
			{
				ans[i] = true;
			}
			else
			{
				ans[i] = false;
			}
		}
		forcas = 0;
	}
}

void Roll::Number()
{
	if (size < maxsize)
		size += Input::GetInstance()->KeyTrigger(KEY_INPUT_D);

	if (size > 0)
		size -= Input::GetInstance()->KeyTrigger(KEY_INPUT_A);

	if (forcas < size)
		forcas += Input::GetInstance()->KeyTrigger(KEY_INPUT_W);

	if (forcas > 0)
		forcas -= Input::GetInstance()->KeyTrigger(KEY_INPUT_S);

	if (forcas > size)
		forcas--;
}

void Roll::Updare()
{
	//AD�Ő��l����
	Number();

	//Space�Ŏ��s
	Act();
}

void Roll::Draw()
{
	//���݂̉�
	DrawFormatString(50, 100, 0xaaaaaa, "���݂̉�:%d(D,A�ő���)", size);
	DrawFormatString(50, 116, 0xaaaaaa, "Space�Œ��I", size);
	DrawFormatString(50, 132, 0xaaaaaa, "���݂̃t�H�[�J�X:%d(W,S�ő���)", forcas);

	//����
	for (size_t i = 0; i < size; i++)
	{
		int hen = 16;
		if (ans[i] == true)
		{
			DrawFormatString(640 / 2, 320 / 3 + (i * hen), 0xaaaaaa, "����");
		}
		else if (ans[i] == 2)
		{
			DrawFormatString(640 / 2, 320 / 3 + (i * hen), 0xaaaaaa, "�m�萬��");
		}
		else
		{
			DrawFormatString(640 / 2, 320 / 3 + (i * hen), 0xaaaaaa, "���s");
		}

	}
}
