#include "Input.h"
#include "DxLib.h"

void Input::Update()
{
	for (int i = 0; i < 256; ++i)
	{
		oldkeys[i] = keys[i];
	}

	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
}

bool Input::KeyPush(size_t key)
{
	return keys[key];
}

bool Input::KeyTrigger(size_t key)
{
	return keys[key] && !oldkeys[key];
}

bool Input::KeyRelease(size_t key)
{
	return !keys[key] && oldkeys[key];
}
