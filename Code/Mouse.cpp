#include "Mouse.h"
#include "DxLib.h"

void Mouse::Update()
{
	//マウス
	// 
	//座標取得
	Int2 getMouse;
	GetMousePoint(&getMouse.x, &getMouse.y);
	mousePos = { (float)getMouse.x,(float)getMouse.y };

	//入力取得
	MouseInput = GetMouseInput();
}

bool Mouse::isMouseTrigger(int MouseButton)
{
	if (((MouseInput & MouseButton) != (PrevMouseInput & MouseButton)) && ((MouseInput & MouseButton) != 0)) {
		return true;
	}
	else {
		return false;
	}
}

bool Mouse::isMouseDown(int MouseButton)
{

	if(MouseInput == MouseButton){
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

bool Mouse::isMouseLeftClickTo2D(Float2 mPos, M2DColData data)
{

	Float2 sizeHarf = { data.size .x / 2 , data.size.y / 2};

	if (mPos.x < data.pos.x + sizeHarf.x && data.pos.x - sizeHarf.x < mPos.x) {
		if (mPos.y < data.pos.y + sizeHarf.y && data.pos.y - sizeHarf.y < mPos.y) {

			//当たってる状態で左クリックした
			if (isMouseTrigger(MOUSE_INPUT_LEFT)) {
				return true;
			}

		}
	}

	return false;
}

//bool Mouse::CollisionMouseToSprite(Float2 mPos, Sprite spite)
//{
//	Int2 spriteSize;
//	GetGraphSize(spite.data, &spriteSize.x, &spriteSize.y);
//
//	if (mPos.x < spite.pos.x + spriteSize.x && spite.pos.x < mPos.x) {
//		if (mPos.y < spite.pos.y + spriteSize.y && spite.pos.y < mPos.y) {
//
//			//当たってる
//			return true;
//
//		}
//	}
//
//	return false;
//}
