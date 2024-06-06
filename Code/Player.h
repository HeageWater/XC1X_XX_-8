#include "DxLib.h"
#include "Input.h"
#pragma once
#include "DxLib.h"
#include "Input.h"
#include "Status.h"

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
	//攻撃を食らう
	void Collision();
	//リセット
	void Reset();
	//セッター
	//各種ステータス関係
	void SetHitPoint(size_t hp) { status.hp = hp; };
	void SetPower(size_t power) { status.power = power; };
	void SetSpeed(size_t speed) { status.speed = speed; };
	void SetIsAttack(bool isAttack) { this->isAttack = isAttack; }
	void SetEnemyStatus(Status status) { enemyStatus = status; }
	void SetTurnChange(bool turnChange_) { turnChange = turnChange_; }
	//ゲッター
	//ステータスを返す
	Status GetStatus() { return status; }
	//ステータス加算
	void PlusStatus(Status state);
	//攻撃が終わったタイミング
	bool GetIsAttack() { return isAttack; }
	//ターンチェンジ
	bool GetTurnChange() { return turnChange; }
	//死んだ判定
	bool GetDeadFlag() { return deadFlag; }
private://変数
	//ステータス
	Status status;
	Status enemyStatus;
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
	enum Attack first, second, third = Attack::weak;
	enum Attack attackSelect = Attack::weak;
	bool isFirst, isSecond, isThird = false;
	//攻撃選択フラグ
	bool isAttack = false;

	//アタックの計算フラグ
	bool isAttackProbability = false;

	//デスフラグ
	bool deadFlag = false;

	//ターンチェンジ
	bool turnChange = false;

	//リソース
	size_t weakPng;
	size_t mediumPng;
	size_t strongPng;
};