#include "map.h"
#include "DxLib.h"
#include "Input.h"

void Map::Initialize()
{
	//�z�񏉊���
	for (size_t i = 0; i < width_; i++)
	{
		for (size_t j = 0; j < height_; j++)
		{
			load_[i][j] = 0;
		}
	}

	//�}�b�v����
	MapCreate();

	//���ݒn������
	nowPoint[0] = 0;
	nowPoint[1] = 0;

	//�������悤
	now = 0;
	nowF = false;
}

void Map::Update()
{
	//�}�b�v�Đ���
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_L))
	{
		//�}�b�v����
		MapCreate();
	}

	//�f�o�b�O�p
	DrawFormatString(20, 20, 0xaaaaaa, "���݉���%d(AD�ő���)", nowPoint[0]);
	DrawFormatString(20, 40, 0xaaaaaa, "���݉���%d(WS�ő���)", nowPoint[1]);

	//�I��
	//��
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_W))
	{
		if (nowPoint[0] > 0)
		{
			nowPoint[0]--;
		}
	}
	//�E
	else if (Input::GetInstance()->KeyTrigger(KEY_INPUT_S))
	{
		if (nowPoint[0] < height_ - 1)
		{
			nowPoint[0]++;
		}
	}

	//��
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_A))
	{
		if (nowPoint[1] > 0)
		{
			nowPoint[1]--;
		}
	}
	//�E
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
	//�`��
	for (size_t i = 0; i < width_; i++)
	{
		for (size_t j = 0; j < height_; j++)
		{
			//true�Ȃ�`�悷��
			if (load_[i][j] != BLANK)
			{
				//�T�C�Y
				size_t size = 32;

				//���o
				size_t heage = 56;

				//�����ʒu
				size_t startPoint = 120;

				//�l�p�̏ꏊ
				size_t pointX = i * heage + startPoint;
				size_t pointY = j * heage + (startPoint / 2);

				//
				size_t ab = 5;

				//�F
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

				//�l�p�`��
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
	//���݂̏ꏊ��Ԃ�
	return load_[nowPoint[0]][nowPoint[1]];
}

void Map::MapCreate()
{
	//���ݒn������
	nowPoint[0] = 0;
	nowPoint[1] = 0;

	//����
	int a = rand() % 100;

	//�i�ޓ��J�E���g
	size_t count = 0;

	//��̗�̍Œᐔ
	size_t line = 3;

	//�ŏ��̏ꏊ���Œ�3�ȏ�
	while (count < line)
	{
		//�J�E���g��0��
		count = 0;

		for (size_t i = 0; i < width_; i++)
		{
			//����
			a = rand() % 100;

			//���ɖ߂�
			load_[i][0] = false;

			if (a < 60)
			{
				//�R��
				size_t b = rand() % 3;

				if (b == 0)
				{
					//�o�g���}�X
					load_[i][0] = BATTLE;
				}
				else if (b == 1)
				{
					//�A�C�e���}�X
					load_[i][0] = ITEM;
				}
				else
				{
					//�p���[�A�b�v�}�X
					load_[i][0] = POWERUP;
				}

				//�J�E���g�v���X
				count++;
			}
			else
			{
				//�󔒃}�X
				load_[i][0] = BLANK;
			}
		}
	}

	//�J�E���g���Z�b�g
	count = 0;

	//���̌�̓�����
	for (size_t i = 1; i < height_; i++)
	{
		//�J�E���g��0��
		count = 0;

		//�ŏ��̏ꏊ���Œ�3�ȏ�
		while (count < line)
		{
			//�J�E���g��0��
			count = 0;

			for (size_t j = 0; j < width_; j++)
			{
				//����
				a = rand() % 100;

				//���ɖ߂�
				load_[j][i] = false;

				if (a < 60)
				{
					//�R��
					size_t b = rand() % 3;

					if (b == 0)
					{
						//�o�g���}�X
						load_[j][i] = BATTLE;
					}
					else if (b == 1)
					{
						//�A�C�e���}�X
						load_[j][i] = ITEM;
					}
					else
					{
						//�p���[�A�b�v�}�X
						load_[j][i] = POWERUP;
					}

					//�J�E���g�v���X
					count++;
				}
				else
				{
					//�󔒃}�X
					load_[j][i] = BLANK;
				}
			}
		}
	}
}
