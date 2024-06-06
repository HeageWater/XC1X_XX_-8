#pragma once
#include "Math.h"

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

	//���͎擾

	//�P����
	bool isMouseDown(int MouseButton);

	//�O�t���[���L�^
	void MousePrev();

public:
	//��
	int MouseInput;
	//�O
	int PrevMouseInput = 0;

	//���W
	Float2 mousePos;

};