#pragma once
#include "Math.h"

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

	//入力取得

	//単押し
	bool isMouseDown(int MouseButton);

	//前フレーム記録
	void MousePrev();

public:
	//今
	int MouseInput;
	//前
	int PrevMouseInput = 0;

	//座標
	Float2 mousePos;

};