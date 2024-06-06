#pragma once
#include "Status.h"

class Enemy
{
private:

	//ステータス
	Status status;

	//これをtrueにすると消える
	bool deadFlag;

	//攻撃
	void Attack();

	//防御
	void Block();

	//ブロックフラグ
	bool blockFlag;

	//攻撃判定
	bool isAttack = false;

	//プレイヤーのステータス
	Status playerStatus;

	//ターン
	bool turnChange = false;
public:

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//当たり判定
	void Collision();

	//各種ステータス関係
	void SetHitPoint(size_t hp);
	void SetPower(size_t power);
	void SetSpeed(size_t speed);
	void SetIsAttack(bool isAttack) { this->isAttack = isAttack; }
	void SetPlayerStatus(Status status) { playerStatus = status; }
	void SetTurnChange(bool turnChange_) { turnChange = turnChange_; }
	//ステータスを返す
	Status GetStatus() { return status; }

	//消去フラグ　　　　
	bool GetDeadFlag() { return deadFlag; };
	//攻撃が終わったタイミング
	bool GetIsAttack() { return isAttack; }
	//ターンチェンジ
	bool GetTurnChange() { return turnChange; }
private:
	
};