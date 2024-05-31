#include "GameScene.h"
#include <math.h>
#include <vector>
#include <memory>
#include <random>

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "試作";

// ウィンドウ横幅
const int WIN_WIDTH = 640;

// ウィンドウ縦幅
const int WIN_HEIGHT = 320;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x33, 0x33, 0x33);

	// DXlibの初期化 
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み

	// ゲームループで使う変数の宣言

	//ゲームシーン
	std::unique_ptr<GameScene> gameScene = std::make_unique<GameScene>();

	////map
	//std::vector<Map> maps_;

	//初期化
	gameScene->Initialize();

	// ゲームループ
	while (1)
	{
		srand(time(NULL));

		// 画面クリア
		ClearDrawScreen();

		//---------  ここからプログラムを記述  ----------//

		// 更新処理

		//ゲームループ
		gameScene->Run();

		// 描画処理

		//描画
		gameScene->Draw();

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}

	InitGraph();
	InitSoundMem();

	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}