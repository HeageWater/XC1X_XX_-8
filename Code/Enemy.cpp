#include "Enemy.h"
#include "DxLib.h"

void Enemy::Attack()
{
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
	//����
	int a = rand() % 100;

	//�u���b�N�t���O���Z�b�g
	blockFlag = false;

	//75%�ōU��
	if (a < 75)
	{
		Attack();
	}
	else
	{
		Block();
	}

}

void Enemy::Draw()
{

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
