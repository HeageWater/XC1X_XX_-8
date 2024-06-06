#pragma once
#include "MathStructure.h"

struct M2DColData {
	Float2 pos;
	Float2 size;
};

class Mouse
{
public:
	//シングルトン
	static Mouse* GetInstance()
	{
		static Mouse mouse;
		return &mouse;
	}

	//更新
	void Update();

	//前フレーム記録
	void MousePrev();

	//入力取得

	//単押し
	bool isMouseTrigger(int MouseButton);

	//長押し
	bool isMouseDown(int MouseButton);

	//---当たり判定---

	//スプライト用
	//bool CollisionMouseToSprite(Float2 mPos, Sprite spite);

	//2d座標用 mPos マウス座標 data 当たり判定用データ
	bool isMouseLeftClickTo2D(Float2 mPos, M2DColData data);

public:
	//今
	int MouseInput;
	//前
	int PrevMouseInput = 0;

	//座標
	Float2 mousePos;

};

////使用例
//if (Mouse::GetInstance()->isMouseTrigger(MOUSE_INPUT_LEFT)) {
//	DrawFormatString(0, 220, 0xaaaaaa, "左クリック単押し");
//}
//if (Mouse::GetInstance()->isMouseDown(MOUSE_INPUT_LEFT)) {
//	DrawFormatString(0, 240, 0xaaaaaa, "左クリック長押し");
//}
//DrawFormatString(0, 200, 0xaaaaaa, "マウス座標 (%f,%f)", Mouse::GetInstance()->mousePos.x, Mouse::GetInstance()->mousePos.y);
//
////当たり判定用データ
//M2DColData data = {
//	{640 / 2,720 / 2},
//	{100,100}
//};
//if (Mouse::GetInstance()->isMouseLeftClickTo2D(Mouse::GetInstance()->mousePos, data)) {
//	DrawFormatString(0, 260, 0xaaaaaa, "当たってる");
//}