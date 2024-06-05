#include "PowerupTrout.h"
#include "DxLib.h"
#include "Input.h"

void PowerupTrout::Initialize()
{
	//仮初期化
	status.hp = 0;
	status.power = 0;
	status.speed = 0;
}

void PowerupTrout::Update()
{
	//試作
	int plus = rand() % 3 + 2;

	//キーに応じてステータスアップ
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
	DrawFormatString(300, 200, 0xaaaaaa, "ZでHP,Xで攻撃力,Cで素早さが一定量上がる");
}
