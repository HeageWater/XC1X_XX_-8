#include "Enemy.h"
#include "DxLib.h"

void Enemy::Attack()
{
	//ターンチェンジ
	turnChange = true;
	isAttack = false;
}

void Enemy::Block()
{
	blockFlag = true;
}

void Enemy::Initialize()
{
	//
	deadFlag = false;

	//
	status.hp = 10;

	//
	status.power = 1;

	//
	status.speed = 5;

}

void Enemy::Update()
{

	//デスフラグ
	if (status.hp == 0) {
		deadFlag = true;
	}
	//ランダム
	int a = rand() % 100;

	//ブロックフラグリセット
	blockFlag = false;
	//攻撃をくらって攻撃し返す(α版用の行動)
	if (isAttack) {
		Attack();
	}

	////75%で攻撃
	//if (a < 75)
	//{
	//	Attack();
	//}
	//else
	//{
	//	Block();
	//}
	
	
}

void Enemy::Draw()
{
	//体力
	DrawFormatString(450, 100, 0xaaaaaa, "EnemyHP:%d", status.hp);
}

void Enemy::Collision()
{
	//オーバー火力の時(体力がマイナスに行くとき)
	if (status.hp <= playerStatus.power) {
		status.hp = 0;
	}
	else {
		status.hp -= playerStatus.power;
	}
}

void Enemy::SetHitPoint(size_t hp)
{
	status.hp = hp;
}

void Enemy::SetPower(size_t power)
{
	status.power = power;
}

void Enemy::SetSpeed(size_t speed)
{
	status.speed = speed;
}
