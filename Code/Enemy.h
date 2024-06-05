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

public:

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//各種ステータス関係
	void SetHitPoint(size_t hp);
	void SetPower(size_t power);
	void SetSpeed(size_t speed);

	//ステータスを返す
	Status GetStatus() { return status; }

	//消去フラグ　　　　
	bool GetDeadFlag() { return deadFlag; };
};