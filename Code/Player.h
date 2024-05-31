#include "DxLib.h"
#include "Input.h"
#pragma once
enum Attack {
	weak,
	medium,
	strong
};

class Player
{
public://関数

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//攻撃
	void Attack();

private://変数

	//弱中強のアタック値
	int weakAttack = 0;
	int mediumAttack = 0;
	int strongAttack = 0;

	//弱中強の確率値
	int weakAttackProbability = 0;
	int mediumAttackProbability = 0;
	int strongAttackProbability = 0;

	//初期のアタック値
	int initialWeakAttack = 1;
	int initialMediumAttack = 3;
	int initialStrongttack = 5;

	//初期の確立値
	int initialWeakAttackProbability = 80;
	int initialMediumAttackProbability = 50;
	int initialStrongAttackProbability = 20;

	//攻撃の選択
	int first, second, third = 0;
	int attackSelect = 0;
	bool isFirst, isSecond, isThird = false;

	//攻撃選択フラグ
	bool isAttack = false;
};