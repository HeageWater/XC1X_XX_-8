#include "Mouse.h"
#include "DxLib.h"

void Mouse::Update()
{
	//�}�E�X
	// 
	//���W�擾
	Int2 getMouse;
	GetMousePoint(&getMouse.x, &getMouse.y);
	mousePos = { (float)getMouse.x,(float)getMouse.y };

	//���͎擾
	MouseInput = GetMouseInput();
}

bool Mouse::isMouseDown(int MouseButton)
{
	if (((MouseInput & MouseButton) != (PrevMouseInput & MouseButton)) && ((MouseInput & MouseButton) != 0)) {
		return true;
	}
	else {
		return false;
	}
}

void Mouse::MousePrev()
{
	PrevMouseInput = MouseInput;
}
