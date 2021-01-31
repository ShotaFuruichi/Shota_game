////////////////////////////////////////////////////////////////////////////////
//
//Contents	: ゲーム画面の処理 [game.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/10/30
//
////////////////////////////////////////////////////////////////////////////////
#include "game.h"
#include "bg.h"
#include "block.h"
#include "bullet.h"
#include "enemy.h"
#include "input.h"
#include "item.h"
#include "player.h"
#include "fade.h"
#include "pause.h"
#include "time.h"
#include "sound.h"

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
bool g_bPause;
STAGE g_stage = STAGE_0;
int g_EnemyCount;

////////////////////////////////////////////////////////////////////////////////
//ゲーム画面の初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitGame(void)
{
	g_bPause = false;
	g_EnemyCount = 0;
	if (g_stage == STAGE_MAX)
	{
		g_stage = STAGE_0;
	}

	//背景の初期化処理
	InitBg();

	//プレイヤーの初期化処理
	InitPlayer();

	//敵の初期化処理
	InitEnemy();

	//弾の初期化処理
	InitBullet();
	
	//ブロック
	InitBlock();

	//アイテムの初期化
	InitItem();

	//制限時間の初期化
	InitTime();

	//ポーズの初期化
	InitPause();

	//ステージセット
	SetStage();

	//BGM再生
	StopSound();
	PlaySound(SOUND_LABEL_BGM001);

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitGame(void)
{
	//ポーズの終了
	UninitPause();

	//制限時間の終了
	UninitTime();

	//アイテムの終了処理
	UninitItem();

	//ブロック
	UninitBlock();

	//弾の終了処理
	UninitBullet();

	//敵の終了処理
	UninitEnemy();

	//プレイヤーの終了処理
	UninitPlayer();

	//背景の終了処理
	UninitBg();
}

////////////////////////////////////////////////////////////////////////////////
//更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateGame(void)
{
	/*FADE fade;
	fade = GetFade();*/

	//ポーズ処理
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause ? false : true;
	}

	//各更新
	if (g_bPause == true)
	{
		//ポーズの更新
		UpdatePause();
	}
	else
	{
		g_EnemyCount++;
		if (g_EnemyCount % 750 == 0)
		{
			switch (g_stage)
			{
			case STAGE_1:
				SetEnemy(D3DXVECTOR3(1820.0f, 50.0f, 0.0f), D3DXVECTOR3(-2.5f, 0.0f, 0.0f), ENEMYTYPE_SUMMER);
				break;
			}
		}
		

		//背景の更新処理
		UpdateBg();

		//プレイヤーの更新処理
		UpdatePlayer();

		//敵の更新処理
		UpdateEnemy();

		//弾の更新処理
		UpdateBullet();

		//ブロック
		UpdateBlock();

		//アイテムの更新処理
		UpdateItem();

		//制限時間の更新処理
		UpdateTime();
	}
}

////////////////////////////////////////////////////////////////////////////////
//描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawGame(void)
{
	//背景の描画処理
	DrawBg();

	//プレイヤーの描画処理
	DrawPlayer();

	//敵の描画処理
	DrawEnemy();

	//弾の描画処理
	DrawBullet();

	//ブロック
	DrawBlock();

	//アイテムの描画処理
	DrawItem();

	//制限時間の描画
	DrawTime();

	//各更新
	if (g_bPause == true)
	{
		//ポーズの描画
		DrawPause();
	}
}

////////////////////////////////////////////////////////////////////////////////
//ポーズ状態取得
////////////////////////////////////////////////////////////////////////////////
void SetPause(bool bPause)
{
	g_bPause = bPause;
}

////////////////////////////////////////////////////////////////////////////////
//ステージの配置
////////////////////////////////////////////////////////////////////////////////
void SetStage(void)
{
#if 0
	FILE *pFile;
	pFile = fopen("data\\MAP\\map.csv", "r");

	if (pFile != NULL)
	{
		int nCntX = 0;
		int nCntY = 0;
		char aLine[256];
		while (fgets(aLine, 256, pFile) != NULL)
		{
			nCntX = 0;
			char *pToken = strtok(aLine, ",");
			while (pToken != NULL)
			{
				int nNum = atoi(pToken);
				g_aMapData[nCntX][nCntY] = nNum;
				pToken = strtok(NULL, ",");
				nCntX++;
			}
			nCntY++;
		}
	}
	fclose(pFile);

	for (int nCntY = 0; nCntY < 18; nCntY++)
	{
		for (int nCntX = 0; nCntX < 32; nCntX++)
		{
			if (g_aMapData[nCntX][nCntY] != 0)
			{
				D3DXVECTOR3 pos = D3DXVECTOR3((float)(nCntX * BLOCK_SIZE), (float)(nCntY * BLOCK_SIZE), 0.0f);
				SetBlock(pos, BLOCK_SIZE, BLOCK_SIZE, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 1, (BLOCKTYPE)g_aMapData[nCntX][nCntY]);
				/*	SetBlock(pos, BLOCK_SIZE * 32, BLOCK_SIZE, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 32, 1, (BLOCKTYPE)g_aMapData[nCntX][nCntY]);*/
			}
		}
	}
#endif
	switch (g_stage)
	{
	case STAGE_0:
		SetEnemy(D3DXVECTOR3(800.0f, 900.0f, 0.0f), D3DXVECTOR3(-2.5f, 0.0f, 0.0f), ENEMYTYPE_SPRING);
		SetItem(D3DXVECTOR3(1820.0f, 600.0f, 0.0f), 40.0f, 40.0f);

		//地面
		SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - BLOCK_SIZE, 0.0f), SCREEN_WIDTH, BLOCK_SIZE, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 32, 1, BLOCKTYPE_SNOWGROUND);

		SetBlock(D3DXVECTOR3((BLOCK_SIZE * 4), SCREEN_HEIGHT - (BLOCK_SIZE * 2), 0.0f), BLOCK_SIZE * 28, BLOCK_SIZE, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 28, 1, BLOCKTYPE_GROUND);
		SetBlock(D3DXVECTOR3((BLOCK_SIZE * 3), SCREEN_HEIGHT - (BLOCK_SIZE * 1), 0.0f), BLOCK_SIZE * 29, BLOCK_SIZE, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 29, 1, BLOCKTYPE_GROUND);
		SetBlock(D3DXVECTOR3((BLOCK_SIZE * 3), SCREEN_HEIGHT - (BLOCK_SIZE * 2), 0.0f), BLOCK_SIZE * 1, BLOCK_SIZE, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 1, BLOCKTYPE_SNOWGROUND);
		SetBlock(D3DXVECTOR3((BLOCK_SIZE * 4), SCREEN_HEIGHT - (BLOCK_SIZE * 3), 0.0f), BLOCK_SIZE * 28, BLOCK_SIZE, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 28, 1, BLOCKTYPE_SNOWGROUND);
		SetBlock(D3DXVECTOR3((BLOCK_SIZE * 5), SCREEN_HEIGHT - (BLOCK_SIZE * 3), 0.0f), BLOCK_SIZE * 1, BLOCK_SIZE, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 1, BLOCKTYPE_GROUND);
		SetBlock(D3DXVECTOR3((BLOCK_SIZE * 5), SCREEN_HEIGHT - (BLOCK_SIZE * 4), 0.0f), BLOCK_SIZE * 1, BLOCK_SIZE, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 1, BLOCKTYPE_SNOWGROUND);
		SetBlock(D3DXVECTOR3((BLOCK_SIZE * 27), SCREEN_HEIGHT - (BLOCK_SIZE * 6), 0.0f), BLOCK_SIZE * 5, BLOCK_SIZE * 5, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5, 5, BLOCKTYPE_SNOWGROUND);
		SetBlock(D3DXVECTOR3((BLOCK_SIZE * 27), SCREEN_HEIGHT - (BLOCK_SIZE * 5), 0.0f), BLOCK_SIZE * 5, BLOCK_SIZE * 4, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5, 4, BLOCKTYPE_GROUND);
		break;

	case STAGE_1:
		SetEnemy(D3DXVECTOR3(500.0f, 830.0f, 0.0f), D3DXVECTOR3(-2.5f, 0.0f, 0.0f), ENEMYTYPE_SPRING);
		SetEnemy(D3DXVECTOR3(1500.0f, 700.0f, 0.0f), D3DXVECTOR3(-2.5f, 0.0f, 0.0f), ENEMYTYPE_SUMMER);
		SetEnemy(D3DXVECTOR3(1500.0f, 200.0f, 0.0f), D3DXVECTOR3(-2.5f, 0.0f, 0.0f), ENEMYTYPE_SUMMER);
		SetItem(D3DXVECTOR3(1820.0f, 100.0f, 0.0f), 40.0f, 40.0f);
		SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - BLOCK_SIZE, 0.0f), SCREEN_WIDTH, BLOCK_SIZE, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 32, 1, BLOCKTYPE_GRASSGROUND);
		SetBlock(D3DXVECTOR3((BLOCK_SIZE * 28), SCREEN_HEIGHT - (BLOCK_SIZE * 3), 0.0f), BLOCK_SIZE * 4, BLOCK_SIZE * 2, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4, 2, BLOCKTYPE_GRASSGROUND);
		SetBlock(D3DXVECTOR3((BLOCK_SIZE * 28), SCREEN_HEIGHT - (BLOCK_SIZE * 2), 0.0f), BLOCK_SIZE * 4, BLOCK_SIZE * 2, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4, 2, BLOCKTYPE_GROUND);
		SetBlock(D3DXVECTOR3((BLOCK_SIZE * 12), SCREEN_HEIGHT - (BLOCK_SIZE * 6), 0.0f), BLOCK_SIZE * 14, BLOCK_SIZE * 1, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 14, 1, BLOCKTYPE_GRASSGROUND);
		SetBlock(D3DXVECTOR3((BLOCK_SIZE * 0), SCREEN_HEIGHT - (BLOCK_SIZE * 9), 0.0f), BLOCK_SIZE * 13, BLOCK_SIZE * 1, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 13, 1, BLOCKTYPE_GRASSGROUND);
		SetBlock(D3DXVECTOR3((BLOCK_SIZE * 12), SCREEN_HEIGHT - (BLOCK_SIZE * 8), 0.0f), BLOCK_SIZE * 1, BLOCK_SIZE * 3, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 3, BLOCKTYPE_GROUND);
		SetBlock(D3DXVECTOR3((BLOCK_SIZE * 8), SCREEN_HEIGHT - (BLOCK_SIZE * 4), 0.0f), BLOCK_SIZE * 2, BLOCK_SIZE * 3, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 3, BLOCKTYPE_GRASSGROUND);
		SetBlock(D3DXVECTOR3((BLOCK_SIZE * 8), SCREEN_HEIGHT - (BLOCK_SIZE * 3), 0.0f), BLOCK_SIZE * 2, BLOCK_SIZE * 3, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 3, BLOCKTYPE_GROUND);
		SetBlock(D3DXVECTOR3((BLOCK_SIZE * 15), SCREEN_HEIGHT - (BLOCK_SIZE * 12), 0.0f), BLOCK_SIZE * 17, BLOCK_SIZE * 1, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 17, 1, BLOCKTYPE_GRASSGROUND);
		SetBlock(D3DXVECTOR3((BLOCK_SIZE * 27), SCREEN_HEIGHT - (BLOCK_SIZE * 15), 0.0f), BLOCK_SIZE * 5, BLOCK_SIZE * 3, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5, 3, BLOCKTYPE_GRASSGROUND);
		SetBlock(D3DXVECTOR3((BLOCK_SIZE * 27), SCREEN_HEIGHT - (BLOCK_SIZE * 14), 0.0f), BLOCK_SIZE * 5, BLOCK_SIZE * 3, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5, 3, BLOCKTYPE_GROUND);

		break;

	//case STAGE_2:
	//	SetItem(D3DXVECTOR3(1820.0f, 900.0f, 0.0f), 40.0f, 40.0f);
	//	SetBlock(D3DXVECTOR3(0.0f, SCREEN_HEIGHT - BLOCK_SIZE, 0.0f), SCREEN_WIDTH, BLOCK_SIZE, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 32, 1, BLOCKTYPE_GROUND);
	//	SetBlock(D3DXVECTOR3((BLOCK_SIZE * 3), SCREEN_HEIGHT - (BLOCK_SIZE * 2), 0.0f), BLOCK_SIZE * 29, BLOCK_SIZE, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 29, 1, BLOCKTYPE_NORMAL);
	//	break;

	//case STAGE_3:
	//	SetItem(D3DXVECTOR3(1820.0f, 900.0f, 0.0f), 40.0f, 40.0f);
	//	/*SetBlock(D3DXVECTOR3((BLOCK_SIZE * 4), SCREEN_HEIGHT - (BLOCK_SIZE * 3), 0.0f), BLOCK_SIZE * 28, BLOCK_SIZE, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 28, 1, BLOCKTYPE_NORMAL);
	//	SetBlock(D3DXVECTOR3((BLOCK_SIZE * 5), SCREEN_HEIGHT - (BLOCK_SIZE * 4), 0.0f), BLOCK_SIZE * 1, BLOCK_SIZE, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 1, BLOCKTYPE_NORMAL);
	//	SetBlock(D3DXVECTOR3((BLOCK_SIZE * 27), SCREEN_HEIGHT - (BLOCK_SIZE * 6), 0.0f), BLOCK_SIZE * 5, BLOCK_SIZE * 5, true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5, 5, BLOCKTYPE_NORMAL);*/
	//	break;
	}
}

////////////////////////////////////////////////////////////////////////////////
//ステージセット
////////////////////////////////////////////////////////////////////////////////
void SetStageMode(STAGE stage)
{
	if (g_stage != STAGE_MAX)
	{
		SetFade(FADE_OUT, MODE_GAME);
	}
	g_stage = stage;
}

////////////////////////////////////////////////////////////////////////////////
//現在のステージの情報を取得
////////////////////////////////////////////////////////////////////////////////
STAGE GetStage(void)
{
	return g_stage;
}