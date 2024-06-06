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
	status.power = 1;
	status.speed = 1;

	//リソース
	weakPng = LoadGraph("Resource//weak.png");
	mediumPng = LoadGraph("Resource//mid.png");
	strongPng = LoadGraph("Resource//strong.png");

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
		//リソース
		//選択肢
		DrawGraph(100, 550, weakPng, 0);
		DrawGraph(200, 550, mediumPng, 0);
		DrawGraph(300, 550, strongPng, 0);
		
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
		DrawFormatString(450, 400, 0xaaaaaa, "三回攻撃方法を選択");
		DrawFormatString(450, 450, 0xaaaaaa, "A,Dで選択:Spaceで決定");
		//体力
		DrawFormatString(450, 700, 0xaaaaaa, "PlayerHP:%d", status.hp);


		//何を選んだか
		////一番目
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
		////二番目
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
		////三番目
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

		//今どれを選択しているか
		if (attackSelect == weak) {
			DrawFormatString(50, 500, 0xaaaaaa, "弱を選択");
			//確率表示
			DrawFormatString(140, 500, 0xaaaaaa, "確率:");
			DrawFormatString(180, 500, 0xaaaaaa, "%d%%", weakAttackProbability);
			//攻撃力表示
			DrawFormatString(220, 500, 0xaaaaaa, "攻撃力:");
			DrawFormatString(280, 500, 0xaaaaaa, "%d", weakAttack);
		}
		else if (attackSelect == medium) {
			DrawFormatString(50, 500, 0xaaaaaa, "中を選択");
			//確率表示
			DrawFormatString(140, 500, 0xaaaaaa, "確率:");
			DrawFormatString(180, 500, 0xaaaaaa, "%d%%", mediumAttackProbability);
			//攻撃力表示
			DrawFormatString(220, 500, 0xaaaaaa, "攻撃力:");
			DrawFormatString(280, 500, 0xaaaaaa, "%d", mediumAttack);
		}
		else if (attackSelect == strong) {
			DrawFormatString(50, 500, 0xaaaaaa, "強を選択");
			//確率表示
			DrawFormatString(140, 500, 0xaaaaaa, "確率:");
			DrawFormatString(180, 500, 0xaaaaaa, "%d%%", strongAttackProbability);
			//攻撃力表示
			DrawFormatString(220, 500, 0xaaaaaa, "攻撃力:");
			DrawFormatString(280, 500, 0xaaaaaa, "%d", strongAttack);
			
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
		else if (attackSelect == strong) {
			attackSelect = medium;
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
		if (isFirst == false) {
			first = attackSelect;
			isFirst = true;
		}
		//二番目
		else if (isSecond == false) {
			second = attackSelect;
			isSecond = true;
		}
		//三番目
		else if (isThird == false) {
			third = attackSelect;
			isThird = true;
			isAttackProbability = true;
		}
	}
	//アタックの計算
	if (isAttackProbability) {
		status.power = 0;
		//アタックの確率
		int firstProbability = (rand() % 100) + 1;
		int secondProbability = (rand() % 100) + 1;
		int thirdProbability = (rand() % 100) + 1;

		////一個目////
		//弱
		if (first == weak) {
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
	//ステータス
	status.hp = 10;
	status.power = 1;
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

void Player::PlusStatus(Status state)
{
	status.hp += state.hp;
	status.power += state.power;
	status.speed += state.speed;
}
