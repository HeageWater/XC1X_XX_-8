#pragma once

class Input
{
private:	
	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

public:
	//シングルトン
	static Input* GetInstance()
	{
		static Input input;
		return &input;
	}

	//更新
	void Update();

	///押してる間
	bool KeyPush(size_t key);

	//押した瞬間
	bool KeyTrigger(size_t key);

	//離した瞬間
	bool KeyRelease(size_t key);
};