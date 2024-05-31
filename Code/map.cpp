#include "map.h"
#include "DxLib.h"
#include "Input.h"

void Map::Initialize()
{
	//配列初期化
	for (size_t i = 0; i < width_; i++)
	{
		for (size_t j = 0; j < height_; j++)
		{
			load_[i][j] = 0;
		}
	}

	//マップ生成
	MapCreate();

	//現在地初期化
	nowPoint[0] = 0;
	nowPoint[1] = 0;

	//仮動きよう
	now = 0;
	nowF = false;
}

void Map::Update()
{
	//マップ再生成
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_L))
	{
		//マップ生成
		MapCreate();
	}

	//デバッグ用
	DrawFormatString(20, 20, 0xaaaaaa, "現在改装%d(ADで増減)", nowPoint[0]);
	DrawFormatString(20, 40, 0xaaaaaa, "現在改装%d(WSで増減)", nowPoint[1]);

	//選択
	//左
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_W))
	{
		if (nowPoint[0] > 0)
		{
			nowPoint[0]--;
		}
	}
	//右
	else if (Input::GetInstance()->KeyTrigger(KEY_INPUT_S))
	{
		if (nowPoint[0] < height_ - 1)
		{
			nowPoint[0]++;
		}
	}

	//左
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_A))
	{
		if (nowPoint[1] > 0)
		{
			nowPoint[1]--;
		}
	}
	//右
	else if (Input::GetInstance()->KeyTrigger(KEY_INPUT_D))
	{
		if (nowPoint[1] < width_ - 1)
		{
			nowPoint[1]++;
		}
	}
}

void Map::Draw()
{
	//描画
	for (size_t i = 0; i < width_; i++)
	{
		for (size_t j = 0; j < height_; j++)
		{
			//trueなら描画する
			if (load_[i][j] != BLANK)
			{
				//サイズ
				size_t size = 32;

				//感覚
				size_t heage = 56;

				//初期位置
				size_t startPoint = 120;

				//四角の場所
				size_t pointX = i * heage + startPoint;
				size_t pointY = j * heage + (startPoint / 2);

				//
				size_t ab = 5;

				//色
				size_t color = 0xbb0000;

				if (nowPoint[0] == j)
				{
					if (nowPoint[1] == i)
					{
						if (nowF == false)
						{
							now++;

							if (now > 15 * ab)
							{
								nowF = true;
							}
						}
						else if (nowF == true)
						{
							now--;

							if (now < 1 * ab)
							{
								nowF = false;
							}
						}

						size += now / ab;
						pointX -= now / ab / 2;
					}
				}

				size_t spriteSize = size / 4;

				if (load_[i][j] == BATTLE)
				{
					color = 0xbb0000;
					DrawFormatString(pointX, pointY + spriteSize, color, "BATTLE");
				}
				else if (load_[i][j] == ITEM)
				{
					color = 0x00bb00;
					DrawFormatString(pointX, pointY + spriteSize, color, "ITEM");
				}
				else if (load_[i][j] == POWERUP)
				{
					color = 0xbbbb00;
					DrawFormatString(pointX, pointY + spriteSize, color, "POWERUP");
				}

				//四角描画
				DrawBox(
					pointX,
					pointY,
					pointX + size,
					pointY + size,
					color, false);
			}
		}
	}
}

size_t Map::GetTrout()
{
	//現在の場所を返す
	return load_[nowPoint[0]][nowPoint[1]];
}

void Map::MapCreate()
{
	//現在地初期化
	nowPoint[0] = 0;
	nowPoint[1] = 0;

	//試作
	int a = rand() % 100;

	//進む道カウント
	size_t count = 0;

	//一つの列の最低数
	size_t line = 3;

	//最初の場所が最低3つ以上
	while (count < line)
	{
		//カウントを0に
		count = 0;

		for (size_t i = 0; i < width_; i++)
		{
			//乱数
			a = rand() % 100;

			//元に戻す
			load_[i][0] = false;

			if (a < 60)
			{
				//３択
				size_t b = rand() % 3;

				if (b == 0)
				{
					//バトルマス
					load_[i][0] = BATTLE;
				}
				else if (b == 1)
				{
					//アイテムマス
					load_[i][0] = ITEM;
				}
				else
				{
					//パワーアップマス
					load_[i][0] = POWERUP;
				}

				//カウントプラス
				count++;
			}
			else
			{
				//空白マス
				load_[i][0] = BLANK;
			}
		}
	}

	//カウントリセット
	count = 0;

	//その後の道生成
	for (size_t i = 1; i < height_; i++)
	{
		//カウントを0に
		count = 0;

		//最初の場所が最低3つ以上
		while (count < line)
		{
			//カウントを0に
			count = 0;

			for (size_t j = 0; j < width_; j++)
			{
				//乱数
				a = rand() % 100;

				//元に戻す
				load_[j][i] = false;

				if (a < 60)
				{
					//３択
					size_t b = rand() % 3;

					if (b == 0)
					{
						//バトルマス
						load_[j][i] = BATTLE;
					}
					else if (b == 1)
					{
						//アイテムマス
						load_[j][i] = ITEM;
					}
					else
					{
						//パワーアップマス
						load_[j][i] = POWERUP;
					}

					//カウントプラス
					count++;
				}
				else
				{
					//空白マス
					load_[j][i] = BLANK;
				}
			}
		}
	}
}
