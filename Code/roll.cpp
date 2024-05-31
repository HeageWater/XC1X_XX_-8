#include "roll.h"
#include "Input.h"
#include "DxLib.h"

void Roll::Initialize()
{
	//初期化
	for (size_t i = 0; i < size; i++)
	{
		ans[i] = false;
	}
}

void Roll::Act()
{
	//試作
	int a = rand() % 100;

	//space押したとき抽選開始
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_SPACE))
	{
		//連続
		for (size_t i = 0; i < size; i++)
		{
			if (i < forcas)
			{
				ans[i] = 2;
				continue;
			}

			a = rand() % 100;

			//70以上で失敗
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
	//ADで数値調整
	Number();

	//Spaceで実行
	Act();
}

void Roll::Draw()
{
	//現在の回数
	DrawFormatString(50, 100, 0xaaaaaa, "現在の回数:%d(D,Aで増減)", size);
	DrawFormatString(50, 116, 0xaaaaaa, "Spaceで抽選", size);
	DrawFormatString(50, 132, 0xaaaaaa, "現在のフォーカス:%d(W,Sで増減)", forcas);

	//結果
	for (size_t i = 0; i < size; i++)
	{
		int hen = 16;
		if (ans[i] == true)
		{
			DrawFormatString(640 / 2, 320 / 3 + (i * hen), 0xaaaaaa, "成功");
		}
		else if (ans[i] == 2)
		{
			DrawFormatString(640 / 2, 320 / 3 + (i * hen), 0xaaaaaa, "確定成功");
		}
		else
		{
			DrawFormatString(640 / 2, 320 / 3 + (i * hen), 0xaaaaaa, "失敗");
		}

	}
}
