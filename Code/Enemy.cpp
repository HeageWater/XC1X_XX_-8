#include "Enemy.h"
#include "DxLib.h"

void Enemy::Attack()
{
	//�^�[���`�F���W
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

	//�f�X�t���O
	if (status.hp == 0) {
		deadFlag = true;
	}
	//�����_��
	int a = rand() % 100;

	//�u���b�N�t���O���Z�b�g
	blockFlag = false;
	//�U����������čU�����Ԃ�(���ŗp�̍s��)
	if (isAttack) {
		Attack();
	}

	////75%�ōU��
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
	//�̗�
	DrawFormatString(450, 100, 0xaaaaaa, "EnemyHP:%d", status.hp);
}

void Enemy::Collision()
{
	//�I�[�o�[�Η͂̎�(�̗͂��}�C�i�X�ɍs���Ƃ�)
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
