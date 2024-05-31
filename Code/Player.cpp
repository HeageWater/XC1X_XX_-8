#include "Player.h"

void Player::Initialize()
{
	//アタック値の初期化
	weakAttack = initialWeakAttack;
	mediumAttack = initialMediumAttack;
	strongAttack = initialStrongttack;

	//確率値の初期化
	weakAttackProbability = initialWeakAttackProbability;
	mediumAttackProbability = initialMediumAttackProbability;
	strongAttackProbability = initialStrongAttackProbability;
}

void Player::Update()
{
	//攻撃の選択
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_RETURN)) {
		isAttack = true;
	}
	//攻撃
	if (isAttack == true) {
		Attack();
	}
}

void Player::Draw()
{
	//攻撃を選んでいない時
	if (!isAttack) {
		DrawFormatString(50, 100, 0xaaaaaa, "攻撃:ENTER");
	}
	//選んだ時
	else if (isAttack) {
		//選択肢
		DrawFormatString(50, 200, 0xaaaaaa, "弱");
		DrawFormatString(100, 200, 0xaaaaaa, "中");
		DrawFormatString(150, 200, 0xaaaaaa, "強");
		//操作方法
		DrawFormatString(300, 200, 0xaaaaaa, "A,Dで選択:Spaceで決定");
		//何を選んだか
		////一番目
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
		////二番目
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
		////三番目
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

		//今どれを選択しているか
		if (attackSelect==weak) {
			DrawFormatString(50, 150, 0xaaaaaa, "weakを選択");
		}
		else if (attackSelect==medium) {
			DrawFormatString(50, 150, 0xaaaaaa, "mediumを選択");
		}
		else if (attackSelect == strong) {
			DrawFormatString(50, 150, 0xaaaaaa, "strongを選択");
		}
	}
}

void Player::Attack()
{
	//選択
	//左
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_A)) {
		if (attackSelect == weak) {
			attackSelect = strong;
		}
		else {
			attackSelect--;
		}
	}
	//右
	else if (Input::GetInstance()->KeyTrigger(KEY_INPUT_D)) {
		if (attackSelect == strong) {
			attackSelect = weak;
		}
		else {
			attackSelect++;
		}
	}
	//決定
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_SPACE)) {
		//一番目
		if (isFirst==false) {
			first = attackSelect;
			isFirst = true;
		}
		//二番目
		else if (isSecond==false) {
			second = attackSelect;
			isSecond = true;
		}
		//三番目
		else if (isThird==false) {
			third = attackSelect;
			isThird = true;
			WaitKey();
		}
	}
	//アタックの終了
	if (isThird) {
		isFirst = false;
		isSecond = false;
		isThird = false;
		isAttack = false;
	}
}
