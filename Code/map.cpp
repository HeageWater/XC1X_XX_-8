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
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_SPACE))
	{
		//�}�b�v����
		MapCreate();
	}

	//�f�o�b�O�p
	DrawFormatString(20, 20, 0xaaaaaa, "���݉���%d(AD�ő���)",nowPoint[0]);

	//�I��
	//��
	if (Input::GetInstance()->KeyTrigger(KEY_INPUT_A)) 
	{
		if (nowPoint[0] > 0)
		{
			nowPoint[0]--;
		}
	}
	//�E
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
	//�`��
	for (size_t i = 0; i < width_; i++)
	{
		for (size_t j = 0; j < height_; j++)
		{
			//true�Ȃ�`�悷��
			if (load_[i][j])
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

				//�l�p�`��
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
