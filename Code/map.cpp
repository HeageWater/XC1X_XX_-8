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
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_SPACE))
	{
		//マップ生成
		MapCreate();
	}

	//デバッグ用
	DrawFormatString(20, 20, 0xaaaaaa, "現在改装%d(ADで増減)",nowPoint[0]);

	//選択
	//左
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_A)) 
	{
		if (nowPoint[0] > 0)
		{
			nowPoint[0]--;
		}
	}
	//右
	else if (Input::GetInstance()->KeyTrigger(KEY_INPUT_D)) 
	{
		if (nowPoint[0] < height_ - 1)
		{
			nowPoint[0]++;
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
			if (load_[i][j])
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
				size_t ab = 6;

				if (nowPoint[0] == j)
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

				//四角描画
				DrawBox(
					pointX,
					pointY,
					pointX + size,
					pointY + size,
					0xbb0000, true);
			}
		}
	}
}

void Map::MapCreate()
{
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

			if (a > 60)
			{
				load_[i][0] = true;
				count++;
			}
			else
			{
				load_[i][0] = false;
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

				if (a > 60)
				{
					load_[j][i] = true;
					count++;
				}
				else
				{
					load_[j][i] = false;
				}
			}
		}
	}
}
