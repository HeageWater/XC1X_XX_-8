#pragma once

class Roll
{

public:

	//初期化
	void Initialize();

	//調整
	void Updare();

	//描画
	void Draw();

	//シングルトン
	static Roll* GetInstance()
	{
		static Roll roll;
		return &roll;
	}

private:

	//実行
	void Act();

	//数値調整
	void Number();

	//結果保存
	size_t ans[10];

	//ランダム回数
	size_t size = 5;
	size_t maxsize = 10;
	size_t forcas = 0;

};