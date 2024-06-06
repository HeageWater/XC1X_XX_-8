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

	//ステータス
	status.hp = 10;
	status.power = 0;
	status.speed = 1;
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
	//デスフラグ
	if (status.hp <= 0) {
		deadFlag = true;
	}
}

void Player::Draw()
{
	//攻撃を選んでいない時
	if (!isAttack) {
		DrawFormatString(280, 360, 0xaaaaaa, "攻撃:ENTER");
	}
	//選んだ時
	else if (isAttack) {
		//合計値の算出
		if (isAttackProbability == false && isThird == true) {
			DrawFormatString(280, 360, 0xaaaaaa, "攻撃値:%d  ENTER", status.power);
		}
			//選択肢
			DrawFormatString(100, 600, GetColor(0, 0, 255), "弱");
			DrawFormatString(200, 600, GetColor(0, 255, 0), "中");
			DrawFormatString(300, 600, GetColor(255, 0, 0), "強");
			//確率表示
			DrawFormatString(0, 650, 0xaaaaaa, "確率");
			DrawFormatString(100, 650, 0xaaaaaa, "%d%%", weakAttackProbability);
			DrawFormatString(200, 650, 0xaaaaaa, "%d%%", mediumAttackProbability);
			DrawFormatString(300, 650, 0xaaaaaa, "%d%%", strongAttackProbability);
			//攻撃力表示
			DrawFormatString(0, 700, 0xaaaaaa, "攻撃力");
			DrawFormatString(100, 700, 0xaaaaaa, "%d", weakAttack);
			DrawFormatString(200, 700, 0xaaaaaa, "%d", mediumAttack);
			DrawFormatString(300, 700, 0xaaaaaa, "%d", strongAttack);
			//操作方法
			DrawFormatString(450, 600, 0xaaaaaa, "三回攻撃方法を選択");
			DrawFormatString(450, 650, 0xaaaaaa, "A,Dで選択:Spaceで決定");
			//体力
			DrawFormatString(450, 700, 0xaaaaaa, "PlayerHP:%d",status.hp);


			//何を選んだか
			////一番目
			if (isFirst) {
				DrawFormatString(100, 550, 0xaaaaaa, "1:");
				if (first == weak) {
					DrawFormatString(120, 550, GetColor(0, 0, 255), "弱");
				}
				else if (first == medium) {
					DrawFormatString(120, 550, GetColor(0, 255, 0), "中");
				}
				else if (first == strong) {
					DrawFormatString(120, 550, GetColor(255, 0, 0), "強");
				}
			}
			////二番目
			if (isSecond) {
				DrawFormatString(200, 550, 0xaaaaaa, "2:");
				if (second == weak) {
					DrawFormatString(220, 550, GetColor(0, 0, 255), "弱");
				}
				else if (second == medium) {
					DrawFormatString(220, 550, GetColor(0, 255, 0), "中");
				}
				else if (second == strong) {
					DrawFormatString(220, 550, GetColor(255, 0, 0), "強");
				}
			}
			////三番目
			if (isThird) {
				DrawFormatString(300, 550, 0xaaaaaa, "3:");
				if (third == weak) {
					DrawFormatString(320, 550, GetColor(0, 0, 255), "弱");
				}
				else if (third == medium) {
					DrawFormatString(320, 550, GetColor(0, 255, 0), "中");
				}
				else if (third == strong) {
					DrawFormatString(320, 550, GetColor(255, 0, 0), "強");
				}
			}

			//今どれを選択しているか
			if (attackSelect == weak) {
				DrawFormatString(50, 500, 0xaaaaaa, "弱を選択");
			}
			else if (attackSelect == medium) {
				DrawFormatString(50, 500, 0xaaaaaa, "中を選択");
			}
			else if (attackSelect == strong) {
				DrawFormatString(50, 500, 0xaaaaaa, "強を選択");
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
		else if(attackSelect==strong){
			attackSelect=medium;
		}
		else if (attackSelect == medium) {
			attackSelect = weak;
		}
	}
	//右
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
			isAttackProbability = true;
		}
	}
	//アタックの計算
	if (isAttackProbability) {
		status.power = 0;
		//アタックの確率
		int firstProbability = (rand() % 100)+1;
		int secondProbability = (rand() % 100) + 1;
		int thirdProbability = (rand() % 100) + 1;

		////一個目////
		//弱
		if (first==weak) {
			if (weakAttackProbability >= firstProbability) {
				status.power += weakAttack;
			}
		}
		//中
		else if (first == medium) {
			if (mediumAttackProbability >= firstProbability) {
				status.power += mediumAttack;
			}
		}
		//強
		else if (first == strong) {
			if (strongAttackProbability >= firstProbability) {
				status.power += strongAttack;
			}
		}

		////二個目////
		//弱
		if (second == weak) {
			if (weakAttackProbability >= secondProbability) {
				status.power += weakAttack;
			}
		}
		//中
		else if (second == medium) {
			if (mediumAttackProbability >= secondProbability) {
				status.power += mediumAttack;
			}
		}
		//強
		else if (second == strong) {
			if (strongAttackProbability >= secondProbability) {
				status.power += strongAttack;
			}
		}

		////三個目////
		//弱
		if (third == weak) {
			if (weakAttackProbability >= thirdProbability) {
				status.power += weakAttack;
			}
		}
		//中
		else if (third == medium) {
			if (mediumAttackProbability >= thirdProbability) {
				status.power += mediumAttack;
			}
		}
		//強
		else if (third == strong) {
			if (strongAttackProbability >= thirdProbability) {
				status.power += strongAttack;
			}
		}
		isAttackProbability = false;
	}

	//アタックの終わり
	if (isAttackProbability == false && isThird == true) {
		if(Input::GetInstance()->KeyTrigger(KEY_INPUT_RETURN)) {
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
	//ステータス
	status.hp = 10;
	status.power = 0;
	status.speed = 1;
	//アタック値の初期化
	weakAttack = initialWeakAttack;
	mediumAttack = initialMediumAttack;
	strongAttack = initialStrongttack;

	//確率値の初期化
	weakAttackProbability = initialWeakAttackProbability;
	mediumAttackProbability = initialMediumAttackProbability;
	strongAttackProbability = initialStrongAttackProbability;

	//死んだ判定の初期化
	deadFlag = false;
}
