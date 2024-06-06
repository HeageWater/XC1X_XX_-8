#pragma once

// マス
enum
{
	BLANK,	//空白
	BATTLE,//戦闘
	ITEM,//アイテム
	POWERUP,//強化
};

//道
struct Load
{
	//横
	size_t width_ = 5;

	//縦
	size_t height_ = 10;

	//道格納用
	size_t load_[5][10];
};

class Map
{
public:

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//入った場所のマスの種類を返す
	size_t GetTrout();

private:

	//マップ生成
	void MapCreate();

	//横
	size_t width_ = 5;

	//縦
	size_t height_ = 10;

	//道格納用
	size_t load_[5][10];

	//現在地
	size_t nowPoint[2];

	//スクロール用
	size_t scllorY = 0;

	//仮動きよう
	size_t now = 0;
	bool nowF = false;

	//リソース
	size_t battlePng;
	size_t itemPng;
	size_t powerPng;
};