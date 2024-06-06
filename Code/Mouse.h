#pragma once
#include "MathStructure.h"

struct M2DColData {
	Float2 pos;
	Float2 size;
};

class Mouse
{
public:
	//�V���O���g��
	static Mouse* GetInstance()
	{
		static Mouse mouse;
		return &mouse;
	}

	//�X�V
	void Update();

	//�O�t���[���L�^
	void MousePrev();

	//���͎擾

	//�P����
	bool isMouseTrigger(int MouseButton);

	//������
	bool isMouseDown(int MouseButton);

	//---�����蔻��---

	//�X�v���C�g�p
	//bool CollisionMouseToSprite(Float2 mPos, Sprite spite);

	//2d���W�p mPos �}�E�X���W data �����蔻��p�f�[�^
	bool isMouseLeftClickTo2D(Float2 mPos, M2DColData data);

public:
	//��
	int MouseInput;
	//�O
	int PrevMouseInput = 0;

	//���W
	Float2 mousePos;

};

////�g�p��
//if (Mouse::GetInstance()->isMouseTrigger(MOUSE_INPUT_LEFT)) {
//	DrawFormatString(0, 220, 0xaaaaaa, "���N���b�N�P����");
//}
//if (Mouse::GetInstance()->isMouseDown(MOUSE_INPUT_LEFT)) {
//	DrawFormatString(0, 240, 0xaaaaaa, "���N���b�N������");
//}
//DrawFormatString(0, 200, 0xaaaaaa, "�}�E�X���W (%f,%f)", Mouse::GetInstance()->mousePos.x, Mouse::GetInstance()->mousePos.y);
//
////�����蔻��p�f�[�^
//M2DColData data = {
//	{640 / 2,720 / 2},
//	{100,100}
//};
//if (Mouse::GetInstance()->isMouseLeftClickTo2D(Mouse::GetInstance()->mousePos, data)) {
//	DrawFormatString(0, 260, 0xaaaaaa, "�������Ă�");
//}