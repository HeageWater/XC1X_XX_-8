#include "DxLib.h"
#include "main.h"
#include "time.h"

//��`�̓����蔻�蒆�S�łƂ�
bool BoxCollision(int a_x, int a_y, int a_w, int a_h, int b_x, int b_y, int b_w, int b_h)
{
	if (b_x - b_w <= a_x + a_w &&
		b_x + b_w >= a_x - a_w &&
		b_y - b_h <= a_y + a_h &&
		b_y + b_h >= a_y - a_h)
	{
		return true;
	}
	return false;
}

void Player_Damage(int direction)
{

	player_y -= 3;
	suku_y -= 3;

	if (direction == 1)
	{
		player_x -= 3;
		suku_x -= 3;
		return;
	}

	player_x += 3;
	suku_x += 3;

}

//�}�b�v�`�F���W
void MapChenge()
{
	mapcount += 1;

	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (mapcount == 1)
			{
				map[i][j] = map0[i][j];
			}
			if (mapcount == 2)
			{
				map[i][j] = map1[i][j];
			}
			if (mapcount == 3)
			{
				map[i][j] = map2[i][j];
			}
			if (mapcount == 4)
			{
				mode = Clear;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		suraimu_x[i] = -128;
		suraimu_y[i] = -128;
		suraimu_flg[i] = 0;
		suraimu_animation[i] = { 0 };
	}
}

//������
void InitGame()
{
	player_x = 336;
	player_y = 656;

	suku_x = 150;
	suku_y = 100;

	player_heart = 5;
	player_invincibility = 0;
}

//���@�̍��W�C��
void PlayerCoordinate()
{
	right_x = player_x + player_r;
	left_x = player_x - player_r;
	up_y = player_y - player_r;
	down_y = player_y + player_r;
}

//�v���C���[�̕\��
void PrintPlayer()
{
	DrawBox(left_x, up_y, right_x, down_y, GetColor(200, 0, 0), true);
}

//�ړ�
void MovePlayer()
{
	direction = (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) == 1;

	direction = CheckHitKey(KEY_INPUT_RIGHT) == true;

	if (((mapCountX - 2) * block_size) - (WIN_WIDTH / 2) > suku_x + player_x &&
		WIN_WIDTH / 2 < suku_x + player_x)
	{
		suku_x += move_x;
		return;
	}

	player_x += move_x;

	PlayerCoordinate();
}

//�E�̓����蔻��
void HitRight()
{
	if (map[(up_y + suku_y) / block_size][(right_x + suku_x) / block_size] > 1 ||
		map[(suku_y + down_y) / block_size][(right_x + suku_x) / block_size] > 1)
	{
		while (map[(up_y + suku_y) / block_size][(right_x + suku_x) / block_size] > 1 ||
			map[(suku_y + down_y) / block_size][(right_x + suku_x) / block_size] > 1)
		{
			if (((mapCountX - 2) * block_size) - (WIN_WIDTH / 2) > suku_x + player_x &&
				WIN_WIDTH / 2 < suku_x + player_x)
			{
				suku_x -= 1;
			}
			else
			{
				player_x -= 1;
			}

			PlayerCoordinate();
		}
	}
}

//���̓����蔻��
void HitLeft()
{
	if (map[(up_y + suku_y) / block_size][(left_x + suku_x - 1) / block_size] > 1 ||
		map[(suku_y + down_y) / block_size][(left_x + suku_x - 1) / block_size] > 1)
	{
		while (map[(up_y + suku_y) / block_size][(left_x + suku_x) / block_size] > 1 ||
			map[(suku_y + down_y) / block_size][(left_x + suku_x) / block_size] > 1)
		{
			if (((mapCountX - 2) * block_size) - (WIN_WIDTH / 2) > suku_x + player_x &&
				WIN_WIDTH / 2 < suku_x + player_x)
			{
				suku_x += 1;
			}
			else
			{
				player_x += 1;
			}

			PlayerCoordinate();
		}
	}
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//�t�H���g�T�C�Y
	SetFontSize(30);

	//�E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	//�t���X�N���[�����[�h�ɐݒ�
	ChangeWindowMode(FALSE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, TRUE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	srand(time(NULL));

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���

	//���y//

	//�a��
	int ZAN = LoadSoundMem("music//zan.mp3");
	ChangeVolumeSoundMem(100, ZAN);

	//����
	int STAGE1 = LoadSoundMem("music//stage1.mp3");
	ChangeVolumeSoundMem(50, STAGE1);

	//�����SE
	int ENTER = LoadSoundMem("music//kettei.mp3");
	ChangeVolumeSoundMem(100, ENTER);

	//�㉺��SE
	int UPDOWN = LoadSoundMem("music//jouge.mp3");
	ChangeVolumeSoundMem(100, UPDOWN);

	//�X���C����SE
	int SURAIMU = LoadSoundMem("music//suraimu.mp3");
	ChangeVolumeSoundMem(100, SURAIMU);

	//������SE
	int BOM = LoadSoundMem("music//bomb.mp3");
	ChangeVolumeSoundMem(80, BOM);

	//�h�A�ɓ��鉹
	int DOOR = LoadSoundMem("music//door.mp3");
	ChangeVolumeSoundMem(100, DOOR);

	//�v���C���[�̔�e
	int DAMAGE = LoadSoundMem("music//damage.mp3");
	ChangeVolumeSoundMem(120, DAMAGE);

	//�{�XBGM
	int BOSS_BGM = LoadSoundMem("music//boss_bgm.mp3");
	ChangeVolumeSoundMem(70, BOSS_BGM);

	//�{�X��e
	int BOSS_DAMAGE = LoadSoundMem("music//bossdamage.mp3");
	ChangeVolumeSoundMem(120, BOSS_DAMAGE);

	//�{�X���j
	int DESTROY = LoadSoundMem("music//destroy.mp3");
	ChangeVolumeSoundMem(120, DESTROY);

	//�C���X�g//

	//��
	int sord = LoadGraph("graph//ken.png");

	//���
	int mark = LoadGraph("graph//mark.png");

	//GAME OVER
	int over = LoadGraph("graph//gameover.png");

	//GAME CLEAR
	int clear = LoadGraph("graph//clear.png");

	//�^�C�g���G
	int title = LoadGraph("graph//title.png");

	//����
	int start = LoadGraph("graph//start.png");
	int end = LoadGraph("graph//end.png");

	//�O�p
	int triangle = LoadGraph("graph//triangle.png");

	//�w�i
	int background = LoadGraph("graph//background.png");

	//�{�X�̌�
	int boss_sord = LoadGraph("graph//enemy_sord.png");

	//�X�y�[�X
	int space = LoadGraph("graph//space.png");

	//�A���[�L�[
	int arrow = LoadGraph("graph//arrow.png");

	//�v���C���\
	int chara[7];
	LoadDivGraph("graph//player.png", 7, 4, 3, 128, 128, chara);
	//0�ҋ@1����2��3����4����5�K�[�h6�W�����v

	//�}�b�v�`�b�v
	int block[4];
	LoadDivGraph("graph//mapcip2.png", 4, 4, 1, 128, 128, block);

	//�{�^��
	int button[4];
	LoadDivGraph("graph//button.png", 4, 4, 1, 128, 128, button);

	//�A�i���O�X�e�B�b�N
	int anarogu[4];
	LoadDivGraph("graph//anarogu.png", 3, 3, 1, 128, 128, anarogu);

	//�{�X
	int boss[3];
	LoadDivGraph("graph//boss.png", 3, 3, 1, 128, 128, boss);

	//��
	int landing[4];
	LoadDivGraph("graph//smoke_anime.png", 4, 4, 1, 128, 128, landing);

	//�X���C��
	int suraimu[8];
	LoadDivGraph("graph//suratou.png", 8, 8, 1, 128, 128, suraimu);

	//�n�[�g
	int heart[2];
	LoadDivGraph("graph//heart.png", 2, 2, 1, 128, 128, heart);

	//�L�������S��
	int death[3];
	LoadDivGraph("graph//die.png", 3, 3, 1, 128, 128, death);

	//�ϐ��̐錾//

	int i = GetJoypadNum();

	XINPUT_STATE input;

	// �Q�[�����[�v
	while (1)
	{
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();

		//---------  ��������v���O�������L�q  ----------//

		// �X�V����

		//�^�C�g��
		if (mode == Title)
		{
			//BGM
			if (CheckSoundMem(STAGE1) == false)
			{
				PlaySoundMem(STAGE1, DX_PLAYTYPE_BACK, true);
			}

			if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != false &&
				oldpad[0] == 0 ||
				keys[KEY_INPUT_UP] == true &&
				oldkeys[KEY_INPUT_UP] == false)
			{
				plessbutton = 1;
				PlaySoundMem(UPDOWN, DX_PLAYTYPE_BACK, true);
			}

			if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != false &&
				oldpad[2] == 0 ||
				keys[KEY_INPUT_DOWN] == true &&
				oldkeys[KEY_INPUT_DOWN] == false)
			{
				plessbutton = 2;
				PlaySoundMem(UPDOWN, DX_PLAYTYPE_BACK, true);
			}

			if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != false ||
				keys[KEY_INPUT_SPACE] == true &&
				oldkeys[KEY_INPUT_SPACE] == false
				)
			{
				if (plessbutton == 1)
				{
					PlaySoundMem(ENTER, DX_PLAYTYPE_BACK, true);
					mode = 1;
					InitGame();
				}
				else
				{
					PlaySoundMem(ENTER, DX_PLAYTYPE_BACK, true);
					break;
				}
			}

			oldpad[0] = GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP;
			oldpad[2] = GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN;
		}

		//�v���C��
		if (mode == Play)
		{
			//BGM
			if (CheckSoundMem(STAGE1) == 0 && mapcount != 4)
			{
				PlaySoundMem(STAGE1, DX_PLAYTYPE_BACK, true);
			}

			//���G����
			if (player_invincibility == 1)
			{
				player_invincibility_count += 1;

				if (player_invincibility_count == 50)
				{
					player_invincibility = 0;
					player_invincibility_count = 0;
				}
			}

			//�E�ړ�
			if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != false ||
				CheckHitKey(KEY_INPUT_RIGHT) != false &&
				CheckHitKey(KEY_INPUT_LEFT) != true)
			{
				MovePlayer();

				if (move_x < player_move_max)
				{
					move_x += (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT);
					move_x += CheckHitKey(KEY_INPUT_RIGHT) != false;
				}

				direction = RIGHT;
				PlayerCoordinate();

				HitRight();
			}

			//���ړ�
			if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != false ||
				CheckHitKey(KEY_INPUT_LEFT) != false &&
				CheckHitKey(KEY_INPUT_RIGHT) != true)
			{
				//�X�N���[��
				MovePlayer();

				if (move_x > -player_move_max)
				{
					move_x -= (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT);
					move_x -= CheckHitKey(KEY_INPUT_LEFT) != false;
				}

				direction = LEFT;
				PlayerCoordinate();

				HitLeft();
			}

			//���E�����蔻��
			HitLeft();
			HitRight();

			player_count += 1;

			if (player_count == 20)
			{
				player_count = 0;
			}

			//�v���C���[�A�j���[�V����
			if (player_count / 10 == 0)
			{
				player_graph = chara[0];
			}
			else
			{
				player_graph = chara[3];
			}

			//�~�܂��Ă���Ƃ�
			if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) == false &&
				(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) == false &&
				CheckHitKey(KEY_INPUT_LEFT) == CheckHitKey(KEY_INPUT_RIGHT))
			{
				player_graph = chara[1];
				move_x = 0;
			}

			//�X�y�[�X�W�����v
			if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0 && jump_flg == 0 ||
				keys[KEY_INPUT_Z] == true)
			{
				PlayerCoordinate();

				if (map[(down_y + suku_y + 1) / block_size][(left_x + suku_x) / block_size] > 1 ||
					map[(down_y + suku_y + 1) / block_size][(right_x + suku_x) / block_size] > 1)	//���ɑ��ꂪ����Ƃ�
				{
					jump_flg = 1;
					jump = 20;

					landing_flg = 1;
					landing_anime = 0;
					landing_x = left_x;
					landing_y = up_y;
					PlayerCoordinate();
				}
			}

			if (jump_flg == 0 &&
				map[(down_y + suku_y + 1) / block_size][(left_x + suku_x) / block_size] < 2 &&
				jump_flg == 0 &&
				map[(down_y + suku_y + 1) / block_size][(right_x + suku_x) / block_size] < 2)
			{
				player_graph = chara[4];
			}

			if (jump_flg == 1)
			{
				player_graph = chara[6];

				player_y -= jump;

				if (map[(up_y + suku_y + 1) / block_size][(left_x + suku_x) / block_size] < 2 &&
					map[(up_y + suku_y + 1) / block_size][(right_x + suku_x) / block_size] < 2 &&
					suku_y > 0)
				{
					landing_y += 2 * jump;
					suku_y -= 2 * jump;
				}

				jump -= 1;

				PlayerCoordinate();
			}

			if (jump == 0 ||
				map[(up_y + suku_y) / block_size][(left_x + suku_x) / block_size] > 1 ||
				map[(up_y + suku_y) / block_size][(right_x + suku_x) / block_size] > 1)
			{
				PlayerCoordinate();

				while (map[(up_y + suku_y + 1) / block_size][(left_x + suku_x) / block_size] > 1 ||
					map[(up_y + suku_y + 1) / block_size][(right_x + suku_x) / block_size] > 1)
				{
					player_y += 1;
					PlayerCoordinate();
				}

				jump_flg = 0;
			}

			//�d��
			if (map[(down_y + 1 + suku_y) / block_size][(left_x + suku_x) / block_size] < 2 &&
				map[(down_y + 1 + suku_y) / block_size][(right_x + suku_x) / block_size] < 2 &&
				jump_flg == 0)
			{
				player_y += down_idou;

				suku_y += 2 * down_idou;

				if (down_idou < 15)
				{
					down_idou += 1;
				}

				PlayerCoordinate();
			}

			//���܂��Ă�Ƃ���Ɉړ�
			if (jump_flg == 0 &&
				map[(down_y + 1 + suku_y) / block_size][(left_x + suku_x) / block_size] > 1 ||
				jump_flg == 0 &&
				map[(down_y + 1 + suku_y) / block_size][(right_x + suku_x) / block_size] > 1)
			{
				while (map[(down_y + suku_y) / block_size][(left_x + suku_x) / block_size] > 1 ||
					map[(down_y + suku_y) / block_size][(right_x + suku_x) / block_size] > 1)
				{
					suku_y -= 1;

					PlayerCoordinate();
				}
				down_idou = 1;
			}


			//�U��
			if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0 && attack_flg == 0 && oldpad[1] == 0 ||
				keys[KEY_INPUT_SPACE] == true &&
				oldkeys[KEY_INPUT_SPACE] == false &&
				attack_flg == 0)
				//&& player_hit_flg == 1)
			{
				attack_flg = 1;
				attack_rote = 0;
				direction_save = direction;
				PlaySoundMem(ZAN, DX_PLAYTYPE_BACK, true);
			}

			//�U���{�^��
			oldpad[1] = GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1;

			PlayerCoordinate();

			//�K�[�h
			GetJoypadXInputState(DX_INPUT_PAD1, &input);

			L = input.LeftTrigger;

			player_hit_flg = 1;

			if (L > 50 ||
				keys[(KEY_INPUT_X)] == true)
			{
				player_graph = chara[5];
				player_hit_flg = 0;

				if ((mapCountX * block_size) - WIN_WIDTH / 2 > suku_x + player_x &&
					WIN_WIDTH / 2 < suku_x + player_x)
				{
					suku_x -= move_x;
				}
				else
				{
					player_x -= move_x;
				}
			}
		}

		//GAMEOVER
		if (mode == GameOver)
		{
			StopSoundMem(STAGE1);
			StopSoundMem(BOSS_BGM);

			DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT - 400, over, true);

			DrawExtendGraph(WIN_WIDTH / 2 - 192, WIN_HEIGHT - (WIN_HEIGHT / 4),
				WIN_WIDTH / 2 + 192, WIN_HEIGHT - (WIN_HEIGHT / 4) + 372, button[1], true);

			if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3 ||
				keys[(KEY_INPUT_X)] == true)
			{
				break;
			}
		}

		// �`�揈��

		//�^�C�g��
		if (mode == Title)
		{
			DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, background, true);

			DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, title, true);

			if (i != 0)
			{
				DrawExtendGraph(1200, 1200, 1458, 1456, button[1], true);
			}
			else
			{
				DrawExtendGraph(1200, 1200, 1458, 1326, space, true);
			}

			if (plessbutton == 1)
			{
				DrawExtendGraph(600, 1000, 1000, 1200, start, true);

				DrawExtendGraph(400, 1000, 600, 1200, triangle, true);

				DrawExtendGraph(400, 1300, 800, 1500, end, true);
			}
			else
			{
				DrawExtendGraph(400, 1000, 800, 1200, start, true);

				DrawExtendGraph(400, 1300, 600, 1500, triangle, true);

				DrawExtendGraph(600, 1300, 1000, 1500, end, true);
			}
		}

		//�v���C��
		if (mode == Play)
		{
			//�w�i
			DrawExtendGraph(0 - suku_x, 0, WIN_WIDTH * 3 - suku_x, WIN_HEIGHT, background, true);

			//�}�b�v�`�b�v�`��
			for (int i = 0; i < 25; i++)
			{
				for (int j = 0; j < 40; j++)
				{

					if ((j + 1) * block_size - suku_x > 0 &&
						j * block_size - suku_x < WIN_WIDTH &&
						(i + 1) * block_size - suku_y > 0 &&
						i * block_size - suku_y < WIN_HEIGHT) //��ʈȊO��`�悵�Ȃ�
					{
						if (map[i][j] == 1)
						{
							if (BoxCollision(player_x + suku_x, player_y + suku_y, player_r, player_r,
								j * block_size + block_r, i * block_size + block_r, block_r, block_r))
							{
								if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP ||
									keys[KEY_INPUT_UP] == true)
								{
									if (map[(down_y + 2 + suku_y) / block_size][(left_x + suku_x) / block_size] > 1 ||
										map[(down_y + 2 + suku_y) / block_size][(right_x + suku_x) / block_size] > 1)
									{
										PlaySoundMem(DOOR, DX_PLAYTYPE_BACK, true);

										InitGame();

										MapChenge();
									}
								}
							}
						}

						if (map[i][j] > 3 && map[i][j] < 8)
						{
							suraimu_flg[map[i][j] - 4] = 1;
							suraimu_y[map[i][j] - 4] = i * 128;
							suraimu_x[map[i][j] - 4] = j * 128;

							map[i][j] = 0;

							DrawGraph((j * block_size) - suku_x, (i * block_size) - suku_y, block[3], true);
						}

						DrawGraph((j * block_size) - suku_x, (i * block_size) - suku_y, block[map[i][j]], true);
					}


				}
			}

			if (mapcount == 0)
			{
				count += 1;

				if (count == 30)
				{
					count = 0;
				}

				if (i != 0)
				{
					DrawExtendGraph(600 - suku_x, 2000 - suku_y, 856 - suku_x, 2256 - suku_y, anarogu[count / 10], true);

					DrawExtendGraph(1800 - suku_x, 2000 - suku_y, 2056 - suku_x, 2256 - suku_y, button[1], true);

					DrawExtendGraph(2800 - suku_x, 2000 - suku_y, 3056 - suku_x, 2256 - suku_y, button[0], true);

					DrawExtendGraph(3100 - suku_x, 2000 - suku_y, 3356 - suku_x, 2256 - suku_y, button[2], true);

					DrawExtendGraph(4372 - suku_x, 2000 - suku_y, 4628 - suku_x, 2256 - suku_y, mark, true);
				}
				else
				{
					DrawExtendGraph(600 - suku_x, 2000 - suku_y, 856 - suku_x, 2256 - suku_y, arrow, true);

					DrawExtendGraph(1800 - suku_x, 2000 - suku_y, 2056 - suku_x, 2256 - suku_y, button[3], true);

					DrawExtendGraph(2800 - suku_x, 2000 - suku_y, 3056 - suku_x, 2256 - suku_y, button[1], true);

					DrawExtendGraph(3100 - suku_x, 2000 - suku_y, 3356 - suku_x, 2256 - suku_y, space, true);

					DrawExtendGraph(4372 - suku_x, 2000 - suku_y, 4628 - suku_x, 2256 - suku_y, mark, true);
				}
			}

			if (mapcount == 3)
			{
				if (suku_x > 1000 && boss_flg == 0)
				{
					boss_flg = 1;
					boss_hit_flg = 1;
					boss_hp = 15;
					mode = Movie;
				}

				if (boss_flg == 1)
				{
					if (CheckSoundMem(STAGE1) == true)
					{
						StopSoundMem(STAGE1);
					}

					if (boss_move == 0)
					{
						if (boss_hit_flg == 1 && boss_flg == 1)
						{
							if (boss_direction == LEFT)
							{
								DrawExtendGraph(boss_x - suku_x, boss_y - suku_y,
									boss_x + boss_r - suku_x, boss_y + boss_r - suku_y, boss[0], true);
							}

							if (boss_direction == RIGHT)
							{
								DrawExtendGraph(boss_x - suku_x + boss_r, boss_y - suku_y,
									boss_x - suku_x, boss_y + boss_r - suku_y, boss[0], true);
							}
						}

						if (boss_hit_flg == 0 && boss_flg == 1)
						{
							if (boss_invincibility_count % 2 == 0)
							{
								if (boss_direction == LEFT)
								{
									DrawExtendGraph(boss_x - suku_x, boss_y - suku_y,
										boss_x + boss_r - suku_x, boss_y + boss_r - suku_y, boss[0], true);
								}

								if (boss_direction == RIGHT)
								{
									DrawExtendGraph(boss_x - suku_x + boss_r, boss_y - suku_y,
										boss_x - suku_x, boss_y + boss_r - suku_y, boss[0], true);
								}
							}
						}
					}

					if (boss_hit_flg == 0 && boss_flg == 1)
					{
						boss_invincibility_count += 1;
						if (boss_invincibility_count >= 30)
						{
							boss_invincibility_count = 0;
							boss_hit_flg = 1;
						}
					}

					if (player_x < boss_x + (boss_r / 2) - suku_x)
					{
						boss_direction = LEFT;
					}
					else
					{
						boss_direction = RIGHT;
					}

					count += 1;

					if (count % 30 > 15)
					{
						boss_y += 2;
					}
					else
					{
						boss_y -= 2;
					}

					if (count == 500)
					{
						boss_move = 1;
						boss_direction_save = boss_direction;

						if (boss_move == 1)
						{
							boss_sord_x = boss_x;
							boss_sord_y = boss_y - boss_sord_h;
						}
					}

					if (boss_move == 1)
					{
						count += 1;

						if (count < 450)
						{
							if (boss_hit_flg == 1 && boss_flg == 1)
							{
								if (boss_direction_save == LEFT)
								{
									DrawExtendGraph(
										boss_x + boss_r - suku_x, boss_y + boss_r - suku_y,
										boss_x - suku_x, boss_y - suku_y,
										boss[1], true);
								}

								if (boss_direction_save == RIGHT)
								{
									DrawExtendGraph(
										boss_x - suku_x + boss_r, boss_y - suku_y,
										boss_x - suku_x, boss_y + boss_r - suku_y,
										boss[1], true);
								}
							}

							if (boss_hit_flg == 0 && boss_flg == 1)
							{
								if (boss_invincibility_count % 2 == 0)
								{
									if (boss_direction_save == LEFT)
									{
										DrawExtendGraph(
											boss_x + boss_r - suku_x, boss_y + boss_r - suku_y,
											boss_x - suku_x, boss_y - suku_y,
											boss[1], true);
									}

									if (boss_direction_save == RIGHT)
									{
										DrawExtendGraph(
											boss_x - suku_x + boss_r, boss_y - suku_y,
											boss_x - suku_x, boss_y + boss_r - suku_y,
											boss[1], true);
									}
								}
							}
						}
						else
						{
							if (boss_direction_save == LEFT)
							{
								if (boss_hit_flg == 1 && boss_flg == 1)
								{
									DrawExtendGraph(boss_x - suku_x, boss_y - suku_y,
										boss_x + boss_r - suku_x, boss_y + boss_r - suku_y, boss[2], true);
								}

								if (boss_hit_flg == 0 && boss_flg == 1)
								{
									if (boss_invincibility_count % 2 == 0)
									{
										DrawExtendGraph(boss_x - suku_x, boss_y - suku_y,
											boss_x + boss_r - suku_x, boss_y + boss_r - suku_y, boss[2], true);
									}
								}

								if (count <= 650)
								{
									for (int i = 0; i < 3; i++)
									{
										DrawExtendGraph(
											boss_sord_x - (boss_r * i) - suku_x, boss_sord_y - suku_y,
											boss_sord_x - boss_sord_w - (boss_r * i) - suku_x, boss_sord_y - boss_sord_w - suku_y,
											boss_sord, TRUE);

										if (BoxCollision(
											boss_sord_x - (boss_r * i) - suku_x - (boss_sord_w / 2),
											boss_sord_y - suku_y - (boss_sord_h / 2),
											boss_sord_w / 2, boss_sord_h / 2,
											player_x, player_y, player_r, player_r) == true)
										{
											if (player_invincibility == 0)
											{
												player_heart -= 1;
												player_invincibility = 1;
												PlaySoundMem(DAMAGE, DX_PLAYTYPE_BACK, true);
											}
										}
									}
									boss_sord_y += 20;
								}

							}

							if (boss_direction_save == RIGHT)
							{
								if (boss_hit_flg == 1 && boss_flg == 1)
								{
									DrawExtendGraph(boss_x - suku_x + boss_r, boss_y - suku_y,
										boss_x - suku_x, boss_y + boss_r - suku_y, boss[2], true);
								}

								if (boss_hit_flg == 0 && boss_flg == 1)
								{
									if (boss_invincibility_count % 2 == 0)
									{
										DrawExtendGraph(boss_x - suku_x + boss_r, boss_y - suku_y,
											boss_x - suku_x, boss_y + boss_r - suku_y, boss[2], true);
									}
								}

								if (count <= 650)
								{
									for (int i = 0; i < 3; i++)
									{
										DrawExtendGraph(
											boss_sord_x + (boss_r * i) - suku_x, boss_sord_y - suku_y,
											boss_sord_x + boss_sord_w + (boss_r * i) - suku_x, boss_sord_y - boss_sord_w - suku_y,
											boss_sord, TRUE);

										if (BoxCollision(
											boss_sord_x + (boss_r * i) - suku_x + (boss_sord_w / 2),
											boss_sord_y - suku_y - (boss_sord_h / 2),
											boss_sord_w / 2, boss_sord_h / 2,
											player_x, player_y, player_r, player_r) == true)
										{
											if (player_invincibility == 0)
											{
												player_heart -= 1;
												player_invincibility = 1;
												PlaySoundMem(DAMAGE, DX_PLAYTYPE_BACK, true);
											}
										}
									}
									boss_sord_y += 20;
								}
							}
						}

						if (count >= 700)
						{
							boss_move = 5;
						}
					}

					if (boss_move == 5)
					{
						count = 400;
						boss_move = 0;
					}

					if (boss_hp < 1)
					{
						boss_flg = 2;
						count = 1000;
						StopSoundMem(BOSS_BGM);
						PlaySoundMem(DESTROY, DX_PLAYTYPE_BACK, true);
					}
				}

				if (boss_flg == 2)
				{
					count += 1;

					if (count == 1100)
					{
						map[18][18] = 1;
					}
				}
			}

			//�X���C��
			for (int i = 0; i < 4; i++)
			{
				if (suraimu_flg[i] == 1)
				{
					suraimu_animation[i] += 1;

					if (suraimu_animation[i] > 40)
					{
						suraimu_animation[i] = 0;
					}

					if (suraimu_x[i] < player_x + suku_x)
					{
						suraimu_x[i] += 1;

						DrawExtendGraph(suraimu_x[i] - suku_x,
							suraimu_y[i] - suku_y,
							suraimu_x[i] + suraimu_r - suku_x,
							suraimu_y[i] + suraimu_r - suku_y, suraimu[suraimu_animation[i] / 8], true);
					}
					else
					{
						suraimu_x[i] -= 1;

						DrawExtendGraph(
							suraimu_x[i] + suraimu_r - suku_x,
							suraimu_y[i] - suku_y,
							suraimu_x[i] - suku_x,
							suraimu_y[i] + suraimu_r - suku_y, suraimu[suraimu_animation[i] / 8], true);
					}

					if (suraimu_animation[i] == 20)
					{
						PlaySoundMem(SURAIMU, DX_PLAYTYPE_BACK, true);
					}

					if (BoxCollision(
						player_x, player_y, player_r, player_r,
						suraimu_x[i] + suraimu_r / 2 - suku_x, suraimu_y[i] + suraimu_r / 2 - suku_y, suraimu_r / 2, suraimu_r / 2) == true &&
						player_invincibility == 0)
					{
						if (suraimu_x[i] < player_x + suku_x)
						{
							for (int i = 0; i < 20; i++)
							{
								Player_Damage(LEFT);
							}
						}
						else
						{
							for (int i = 0; i < 20; i++)
							{
								Player_Damage(RIGHT);
							}
						}

						player_heart -= 1;
						player_invincibility = 1;
						PlaySoundMem(DAMAGE, DX_PLAYTYPE_BACK, true);
					}
				}

				if (suraimu_flg[i] == 2)
				{
					DrawExtendGraph(
						suraimu_x[i] + suraimu_r - suku_x,
						suraimu_y[i] - suku_y,
						suraimu_x[i] - suku_x,
						suraimu_y[i] + suraimu_r - suku_y, death[suraimu_animation[i] / 3], true);

					if (suraimu_animation[i] < 9)
					{
						suraimu_animation[i] += 1;
					}
					else if (suraimu_animation[i] == 9)
					{
						suraimu_flg[i] = 0;
						suraimu_x[i] = -128;
						suraimu_y[i] = -128;
					}
				}
			}

			//�n�[�g�̕\��
			for (int i = 0; i < 5; i++)
			{
				if (i < player_heart)
				{
					DrawGraph(i * 128, 0, heart[1], true);
				}
				else
				{
					DrawGraph(i * 128, 0, heart[0], true);
				}
			}

			//���̃A�j���[�V����
			if (landing_flg == 1)
			{
				if (((mapCountX - 2) * block_size) - WIN_WIDTH / 2 > suku_x + player_x &&
					WIN_WIDTH / 2 < suku_x + player_x)
				{
					landing_x -= move_x;
				}

				DrawGraph(landing_x, landing_y, landing[landing_anime / 4], true);
				landing_anime += 1;

				if (landing_anime == 16)
				{
					landing_flg = 0;
				}
			}

			//���̍U�����[�V����
			if (attack_flg == 1)
			{
				player_graph = chara[2];

				if (direction_save == RIGHT)
				{
					DrawRotaGraph2(right_x, player_y + 5, 32, 120, 1.5f, attack_rote, sord, TRUE);
					attack_rote += 0.3;

					attack_x = right_x + player_r;

					if (attack_rote >= 3)
					{
						attack_flg = 0;
					}
				}
				else if (direction_save == LEFT)
				{
					DrawRotaGraph2(left_x, player_y + 5, 32, 120, 1.5f, attack_rote, sord, TRUE);
					attack_rote -= 0.3;

					attack_x = left_x - player_r;

					if (attack_rote <= -3)
					{
						attack_flg = 0;
					}
				}

				attack_y = player_y;

				for (int i = 0; i < 4; i++)
				{
					if (BoxCollision(
						attack_x, attack_y, attack_w, attack_h,
						suraimu_x[i] + suraimu_r / 2 - suku_x,
						suraimu_y[i] + suraimu_r / 2 - suku_y,
						suraimu_r / 2, suraimu_r / 2) == true)
					{
						suraimu_flg[i] = 2;
						suraimu_animation[i] = 0;
					}
				}

				if (BoxCollision(
					attack_x, attack_y, attack_w, attack_h,
					boss_x + boss_r / 2 - suku_x,
					boss_y + boss_r / 2 - suku_y,
					boss_r / 2, boss_r / 2) == true)
				{
					if (boss_hit_flg == 1)
					{
						boss_hp -= 1;
						boss_hit_flg = 0;
						boss_invincibility_count = 0;
						PlaySoundMem(BOSS_DAMAGE, DX_PLAYTYPE_BACK, true);
					}
				}
			}

			//�v���C���[�\��
			PrintPlayer();

			//�Q�[���I�[�o�[���ǂ���
			if (player_heart <= 0)
			{
				mode = GameOver;
			}
		}

		//���[�r�[
		if (mode == Movie)
		{
			count += 1;

			//�d��
			if (map[(down_y + 1 + suku_y) / block_size][(left_x + suku_x) / block_size] < 2 ||
				map[(down_y + 1 + suku_y) / block_size][(right_x + suku_x) / block_size] < 2)
			{
				player_y += down_idou;

				suku_y += 3 * down_idou;

				if (down_idou < 15)
				{
					down_idou += 1;
				}

				PlayerCoordinate();
			}

			//���܂��Ă�Ƃ���Ɉړ�
			if (map[(down_y + 1 + suku_y) / block_size][(left_x + suku_x) / block_size] > 1 ||
				map[(down_y + 1 + suku_y) / block_size][(right_x + suku_x) / block_size] > 1)
			{
				player_graph = chara[0];
				down_idou = 1;
				suku_y -= 3;

				while (map[(down_y + 1 + suku_y) / block_size][(left_x + suku_x) / block_size] > 1 ||
					map[(down_y + 1 + suku_y) / block_size][(right_x + suku_x) / block_size] > 1)
				{
					player_y -= down_idou;

					PlayerCoordinate();
				}
			}

			if (CheckSoundMem(STAGE1) == true)
			{
				StopSoundMem(STAGE1);
			}

			DrawExtendGraph(0 - suku_x, 0, WIN_WIDTH * 3 - suku_x, WIN_HEIGHT, background, true);

			for (int i = 0; i < 25; i++)
			{
				for (int j = 0; j < 40; j++)
				{
					if ((j + 1) * block_size - suku_x > 0 &&
						j * block_size - suku_x < WIN_WIDTH)
					{
						DrawGraph((j * block_size) - suku_x, (i * block_size) - suku_y, block[map[i][j]], true);
					}
				}
			}

			DrawBox(0, 0, WIN_WIDTH, 200, GetColor(0, 0, 0), true);
			DrawBox(0, WIN_HEIGHT - (2 * block_size), WIN_WIDTH, WIN_HEIGHT, GetColor(0, 0, 0), true);

			PrintPlayer();

			if (count == 50)
			{
				map[18][18] = 0;

				PlaySoundMem(BOM, DX_PLAYTYPE_BACK, true);

				for (int i = 0; i < 20; i++)
				{
					Player_Damage(LEFT);
				}
			}

			if (count > 60 && count < 80 ||
				count > 90 && count < 110)
			{
				direction = LEFT;
			}
			else if (count < 130)
			{
				direction = RIGHT;
			}

			if (count == 130)
			{
				PlaySoundMem(BOSS_BGM, DX_PLAYTYPE_BACK, true);
				boss_flg = 1;
				boss_x = WIN_WIDTH * 2;
				boss_y = WIN_HEIGHT + boss_r - boss_r;
				count = 200;
			}

			if (boss_flg == 1)
			{
				DrawExtendGraph(boss_x - suku_x, boss_y - suku_y,
					boss_x + boss_r - suku_x, boss_y + boss_r - suku_y, boss[0], true);

				if (boss_x > 1200)
				{
					boss_x -= 10;
				}

				if (count % 30 > 15)
				{
					boss_y += 2;
				}
				else
				{
					boss_y -= 2;
				}

				if (count == 400)
				{
					mode = Play;
				}
			}
		}

		//�N���A
		if (mode == Clear)
		{
			StopSoundMem(STAGE1);

			DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT - (WIN_HEIGHT / 4), clear, true);

			DrawExtendGraph(WIN_WIDTH / 2 - 192, WIN_HEIGHT - (WIN_HEIGHT / 4),
				WIN_WIDTH / 2 + 192, WIN_HEIGHT - (WIN_HEIGHT / 4) + 372, button[1], true);

			if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3 ||
				keys[(KEY_INPUT_X)] == true)
			{
				break;
			}
		}


		DrawFormatString(0, 0, GetColor(200, 0, 0), "%d", direction);
		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}

	InitSoundMem();
	InitGraph();

	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
