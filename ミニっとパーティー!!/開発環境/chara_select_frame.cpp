//-----------------------------------------------------------------
//
// キャラセレクト枠 (chara_select_frame.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "chara_select_frame.h"
#include "chara_select_image.h"
#include "dicision_chara.h"
#include "chara.h"
#include "gamepad.h"
#include "player.h"
#include "sound.h"

//-------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------
#define MAX_CHARAFRAME	(4)						// テクスチャ枚数
#define SCORE_X			(970.0f)				// 中心座標(X)
#define SCORE_Y			(50.0f)					// 中心座標(Y)

#define SCORE_WIDTH		(45.0f)					// スコアの幅
#define SCORE_HEIGHT	(80.0f)					// スコアの高さ
#define WIDTH_X			(40.0f)					// スコアを配置する間隔

#define LANDAM_INTERBAL	(5)					// ランダムのとき表示するキャラの間隔

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCharaSelectFrame = NULL;	// スコアのテクスチャのポインタ
LPDIRECT3DTEXTURE9 g_pTextureCharaSelectFrame[MAX_CHARAFRAME] = {};		// スコアの頂点バッファのポインタ
CharaSelectFrame g_aCharaSelectFrame[MAX_CHARAFRAME];			// 枠の情報
int g_nNumFrame;

//-----------------------------------------------------------------
// キャラセレクト枠の初期化処理
//-----------------------------------------------------------------
HRESULT InitCharaSelectFrame(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// キャラセレクトイメージ情報の取得
	CharaSelectImage *pCharaSelectImage = GetCharaSelectImage();

	g_nNumFrame = 2;

	// テクスチャの読み込み	
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_select_frame1.png", &g_pTextureCharaSelectFrame[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_select_frame2.png", &g_pTextureCharaSelectFrame[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_select_frame3.png", &g_pTextureCharaSelectFrame[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_select_frame4.png", &g_pTextureCharaSelectFrame[3]);

	// 変数の初期化
	for (int nCntFrame = 0; nCntFrame < MAX_CHARAFRAME; nCntFrame++, pCharaSelectImage++)
	{
		g_aCharaSelectFrame[nCntFrame].pos = D3DXVECTOR3(pCharaSelectImage->pos.x, pCharaSelectImage->pos.y, 0.0f);
		g_aCharaSelectFrame[nCntFrame].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_aCharaSelectFrame[nCntFrame].fWidth = 165.0f;
		g_aCharaSelectFrame[nCntFrame].fHeight = 165.0f;
		g_aCharaSelectFrame[nCntFrame].nNumChara = nCntFrame;
		g_aCharaSelectFrame[nCntFrame].nIdxChara = nCntFrame;
		g_aCharaSelectFrame[nCntFrame].bSelect = false;
	}

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * MAX_CHARAFRAME, // 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffCharaSelectFrame,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCharaSelectFrame->Lock(0, 0, (void**)&pVtx, 0);

	// 初期化
	for (int nCntFrame = 0; nCntFrame < MAX_CHARAFRAME; nCntFrame++)
	{
		// 頂点座標の設定
		SetVertexCharaSelectFrame(nCntFrame);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定
		pVtx[0].col = g_aCharaSelectFrame[nCntFrame].col;
		pVtx[1].col = g_aCharaSelectFrame[nCntFrame].col;
		pVtx[2].col = g_aCharaSelectFrame[nCntFrame].col;
		pVtx[3].col = g_aCharaSelectFrame[nCntFrame].col;

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// スコアの情報を次にうつす
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffCharaSelectFrame->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// キャラセレクト枠の終了処理
//-----------------------------------------------------------------
void UninitCharaSelectFrame(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffCharaSelectFrame != NULL)
	{
		g_pVtxBuffCharaSelectFrame->Release();
		g_pVtxBuffCharaSelectFrame = NULL;
	}

	// テクスチャの開放
	for (int nCntTexture = 0 ; nCntTexture < MAX_CHARAFRAME; nCntTexture++)
	{
		if (g_pTextureCharaSelectFrame[nCntTexture] != NULL)
		{
			g_pTextureCharaSelectFrame[nCntTexture] ->Release();
			g_pTextureCharaSelectFrame[nCntTexture]  = NULL;
		}
	}
}

//-----------------------------------------------------------------
// キャラセレクト枠の更新処理
//-----------------------------------------------------------------
void UpdateCharaSelectFrame(void)
{
	// 繋がれているコントローラーの数を取得
	int nCntController = GetnCntController();

	// 繋がれたコントローラーの数だけ回す
	for (int nCntPlayer = 0; nCntPlayer < nCntController ; nCntPlayer++)
	{// 選択された人数だけ回す
		if (nCntPlayer < g_nNumFrame)
		{
			// ゲームパッド情報の取得
			bool *pStickTrigger = GetStickTrigger(nCntPlayer);
			bool *pCrossKeyTrigger = GetCrossKeyTrigger(nCntPlayer);

			// キャラセレクトイメージ情報の取得
			CharaSelectImage *pCharaSelectImage = GetCharaSelectImage();

			if (g_aCharaSelectFrame[nCntPlayer].bSelect == false)
			{
				// プレイヤーの移動
				if (pStickTrigger[STICKTRIGGER_RIGHT] == true || pCrossKeyTrigger[CROSSKEYTRIGGER_RIGHT] == true)
				{// 右移動
					g_aCharaSelectFrame[nCntPlayer].nIdxChara++;

					if (g_aCharaSelectFrame[nCntPlayer].nIdxChara >= MAX_CHARAIMAGE)
					{
						g_aCharaSelectFrame[nCntPlayer].nIdxChara = 0;
					}
					// 位置の確定
					pCharaSelectImage += g_aCharaSelectFrame[nCntPlayer].nIdxChara;		// 何番目の情報を使うか
					g_aCharaSelectFrame[nCntPlayer].pos.x = pCharaSelectImage->pos.x;
					PlaySound(SOUND_LABEL_SE_CURSOR);
				}
				else if (pStickTrigger[STICKTRIGGER_LEFT] == true || pCrossKeyTrigger[CROSSKEYTRIGGER_LEFT] == true)
				{// 左移動
					g_aCharaSelectFrame[nCntPlayer].nIdxChara--;

					if (g_aCharaSelectFrame[nCntPlayer].nIdxChara < 0)
					{
						g_aCharaSelectFrame[nCntPlayer].nIdxChara = MAX_CHARAIMAGE - 1;
					}
					// 位置の確定
					pCharaSelectImage += g_aCharaSelectFrame[nCntPlayer].nIdxChara;		// 何番目の情報を使うか
					g_aCharaSelectFrame[nCntPlayer].pos.x = pCharaSelectImage->pos.x;
					PlaySound(SOUND_LABEL_SE_CURSOR);
				}
				// 何番目のキャラを選択しているかフレームの場所から参照
				if (g_aCharaSelectFrame[nCntPlayer].nIdxChara == 4)
				{
					// ランダム選択時キャラを順番に出す
					if (0 == (g_aCharaSelectFrame[nCntPlayer].nCounterLandam % LANDAM_INTERBAL))
					{
						g_aCharaSelectFrame[nCntPlayer].nNumChara++;

						if (g_aCharaSelectFrame[nCntPlayer].nNumChara >= MAX_CHARAIMAGE - 1)
						{
							g_aCharaSelectFrame[nCntPlayer].nNumChara = 0;
						}
					}
					g_aCharaSelectFrame[nCntPlayer].nCounterLandam++;
				}
				else
				{
					// ランダム以外の時
					g_aCharaSelectFrame[nCntPlayer].nNumChara = g_aCharaSelectFrame[nCntPlayer].nIdxChara;
				}
				// Aボタンを押したら決定状態にする
				if (GetJoypadTrigger(nCntPlayer, JPINFO_OKorJUMP) == true)
				{
					g_aCharaSelectFrame[nCntPlayer].bSelect = true;
					SetDicisionChara(true, nCntPlayer);
					PlaySound(SOUND_LABEL_SE_DICIDE);
					// 隠しキャラにするかどうか
					if (SecretChara(nCntPlayer, g_aCharaSelectFrame[nCntPlayer].nIdxChara))
					{
						g_aCharaSelectFrame[nCntPlayer].nNumChara = 4;
					}
				}
			}
			else
			{
				// Bボタンを押したらキャンセル状態にする
				if (GetJoypadTrigger(nCntPlayer, JPINFO_CANCEL) == true)
				{
					g_aCharaSelectFrame[nCntPlayer].bSelect = false;
					SetDicisionChara(false, nCntPlayer);
					PlaySound(SOUND_LABEL_SE_CANSEL);
				}
			}
			// 頂点座標の更新
			SetVertexCharaSelectFrame(nCntPlayer);
		}
	}
	if (GetJoypadTrigger(PLAYER_1, JPINFO_RIGHT_TURN) == true)
	{
		g_nNumFrame++;

		if (g_nNumFrame >= MAX_CHARAFRAME)
		{
			g_nNumFrame = MAX_CHARAFRAME;
		}
	}
	else if (GetJoypadTrigger(PLAYER_1, JPINFO_LEFT_TURN) == true)
	{
		g_nNumFrame--;

		if (g_nNumFrame < 2)
		{
			g_nNumFrame = 2;
		}
	}
}

//-----------------------------------------------------------------
// キャラセレクト枠の描画処理
//-----------------------------------------------------------------
void DrawCharaSelectFrame(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffCharaSelectFrame, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// 選択されたモードに応じて描画
	for (int nCntFrame = 0; nCntFrame < g_nNumFrame; nCntFrame++)
	{
		pDevice->SetTexture(0, g_pTextureCharaSelectFrame[nCntFrame]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntFrame * 4, 2);
	}
}

//-----------------------------------------------------------------
// キャラセレクトフレームの頂点座標の設定
//-----------------------------------------------------------------
void SetVertexCharaSelectFrame(int nIdx)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCharaSelectFrame->Lock(0, 0, (void**)&pVtx, 0);

	// 何番目か
	pVtx += nIdx * 4;

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aCharaSelectFrame[nIdx].pos.x - g_aCharaSelectFrame[nIdx].fWidth / 2.0f, g_aCharaSelectFrame[nIdx].pos.y + g_aCharaSelectFrame[nIdx].fHeight / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aCharaSelectFrame[nIdx].pos.x - g_aCharaSelectFrame[nIdx].fWidth / 2.0f, g_aCharaSelectFrame[nIdx].pos.y - g_aCharaSelectFrame[nIdx].fHeight / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aCharaSelectFrame[nIdx].pos.x + g_aCharaSelectFrame[nIdx].fWidth / 2.0f, g_aCharaSelectFrame[nIdx].pos.y + g_aCharaSelectFrame[nIdx].fHeight / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aCharaSelectFrame[nIdx].pos.x + g_aCharaSelectFrame[nIdx].fWidth / 2.0f, g_aCharaSelectFrame[nIdx].pos.y - g_aCharaSelectFrame[nIdx].fHeight / 2.0f, 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffCharaSelectFrame->Unlock();
}

//-----------------------------------------------------------------
// キャラセレクトフレーム情報の取得
//-----------------------------------------------------------------
CharaSelectFrame *GetCharaSelectFrame(void)
{
	return &g_aCharaSelectFrame[0];
}

//-----------------------------------------------------------------
// 隠しキャラを出すか処理
//-----------------------------------------------------------------
bool SecretChara(int nCntPlayer,int nNumChara)
{
	// コマンド情報の取得
	int *pSaveCommand = &g_aCharaSelectFrame[nCntPlayer].nSaveCommand[0];

	// 変数宣言
	int nAnswerCommand[MAX_COMMAND] = {4,3,2,1,0};	// 正解のコマンド

	// コマンドの更新
	for (int nCntCommandTop = MAX_COMMAND - 1; nCntCommandTop >= 0; nCntCommandTop--)
	{
		if (nCntCommandTop == 0)
		{
			// コマンドセーブ用の変数に保存
			pSaveCommand[nCntCommandTop] = nNumChara;
		}
		else
		{
			pSaveCommand[nCntCommandTop] = pSaveCommand[nCntCommandTop - 1];
		}
	}

	// コマンドの比較
	for (int nCntCommand = 0; nCntCommand < MAX_COMMAND; nCntCommand++)
	{
		if (pSaveCommand[nCntCommand] != nAnswerCommand[nCntCommand])
		{
			return false;
		}
	}
	return true;
}

//-----------------------------------------------------------------
// フレーム数の取得
//-----------------------------------------------------------------
int GetFrame(void)
{
	return g_nNumFrame;
}