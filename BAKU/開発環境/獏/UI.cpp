////////////////////////////////////////////////////////////////////////////////
//
//Contents	: UIの処理 [UI.cpp]
//Author	: ShotaFuruichi
//Since		: 2021/02/17
//
////////////////////////////////////////////////////////////////////////////////
#include "UI.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include <string.h>
#include "xinput_pad.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUI[UI_MAX] = {};			//頂点情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCooldown[SKILL_MAX] = {};	//頂点情報
LPDIRECT3DTEXTURE9 g_pTextureUI[UI_MAX] = {};				//テクスチャ情報
LPD3DXFONT g_pUIFont = NULL;								//フォントへのポインタ

////////////////////////////////////////////////////////////////////////////////
//UIの初期化処理
////////////////////////////////////////////////////////////////////////////////
HRESULT InitUI(void)
{
	//変数宣言
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\HP.png", &g_pTextureUI[UI_HP]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\MP.png", &g_pTextureUI[UI_MP]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\EnemyHP.png", &g_pTextureUI[UI_ENEMYHP]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge.png", &g_pTextureUI[UI_HPGAUGE]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge.png", &g_pTextureUI[UI_MPGAUGE]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gauge.png", &g_pTextureUI[UI_ENEMYHPGAUGE]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\fist.png", &g_pTextureUI[UI_SKILLACTION]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\fire.png", &g_pTextureUI[UI_SKILLBALL]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cross.png", &g_pTextureUI[UI_SKILLHEAL]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\ChantGauge_MAGIC.png", &g_pTextureUI[UI_CHANTMAGIC]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\ChantGauge_HEAL.png", &g_pTextureUI[UI_CHANTHEAL]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\ChantGauge.png", &g_pTextureUI[UI_CHANTGAUGE]);


	for (int nCntUI = 0; nCntUI < UI_MAX; nCntUI++)
	{
		//頂点バッファの生成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffUI[nCntUI], NULL)))
		{
			return E_FAIL;
		}

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffUI[nCntUI]->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		switch (nCntUI)
		{
		case UI_HP:
			SetVertexHP();
			break;

		case UI_MP:
			SetVertexMP();
			break;

		case UI_ENEMYHP:
			SetVertexENEMYHP();
			break;

		case UI_HPGAUGE:
			SetVertexHPGauge();
			break;

		case UI_MPGAUGE:
			SetVertexMPGauge();
			break;

		case UI_ENEMYHPGAUGE:
			SetVertexEnemyHPGauge();
			break;

		case UI_SKILLACTION:
			SetVertexAction();
			break;

		case UI_SKILLBALL:
			SetVertexMagic();
			break;

		case UI_SKILLHEAL:
			SetVertexHeal();
			break;

		case UI_CHANTMAGIC:
			SetVertexChantMagic();
			break;

		case UI_CHANTHEAL:
			SetVertexChantHeal();
			break;

		case UI_CHANTGAUGE:
			SetVertexChant();
			break;

		default:
			break;
		}

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffUI[nCntUI]->Unlock();
	}

	for (int nCntUI = 0; nCntUI < SKILL_MAX; nCntUI++)
	{
		//頂点バッファの生成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffCooldown[nCntUI], NULL)))
		{
			return E_FAIL;
		}

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffCooldown[nCntUI]->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		SetVertexCooldown(nCntUI);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffCooldown[nCntUI]->Unlock();
	}

	//文字表示
	D3DXCreateFont(pDevice, 30, 0, FW_NORMAL, 1, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "ＭＳＰゴシック", &g_pUIFont);

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//UIの終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitUI(void)
{
	for (int nCntUI = 0; nCntUI < UI_MAX; nCntUI++)
	{
		//頂点バッファの開放
		if (g_pVtxBuffUI[nCntUI] != NULL)
		{
			g_pVtxBuffUI[nCntUI]->Release();	//開放
			g_pVtxBuffUI[nCntUI] = NULL;		//初期化
		}
		if (g_pTextureUI[nCntUI] != NULL)
		{
			g_pTextureUI[nCntUI]->Release();	//開放
			g_pTextureUI[nCntUI] = NULL;		//初期化
		}
	}

	for (int nCntUI = 0; nCntUI < SKILL_MAX; nCntUI++)
	{
		//頂点バッファの開放
		if (g_pVtxBuffCooldown[nCntUI] != NULL)
		{
			g_pVtxBuffCooldown[nCntUI]->Release();	//開放
			g_pVtxBuffCooldown[nCntUI] = NULL;		//初期化
		}
	}

	//フォントの開放
	if (g_pUIFont != NULL)
	{
		g_pUIFont->Release();			//開放
		g_pUIFont = NULL;				//初期化
	}
}

////////////////////////////////////////////////////////////////////////////////
//UIの更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateUI(void)
{
	SetVertexHP();
	SetVertexMP();
	SetVertexENEMYHP();
	SetVertexHPGauge();
	SetVertexMPGauge();
	SetVertexEnemyHPGauge();
	SetVertexChant();
	for (int nCntUI = 0; nCntUI < SKILL_MAX; nCntUI++)
	{
		SetVertexCooldown(nCntUI);
	}

}

////////////////////////////////////////////////////////////////////////////////
//UIの描画処理
////////////////////////////////////////////////////////////////////////////////
void DrawUI(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();
	bool bUsePad = GetUseGamepad();

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntUI = 0; nCntUI < UI_MAX; nCntUI++)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffUI[nCntUI], 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureUI[nCntUI]);

		//ポリゴンの描画
		if (nCntUI == UI_CHANTGAUGE || nCntUI == UI_CHANTMAGIC || nCntUI == UI_CHANTHEAL)
		{
			if (nCntUI != UI_CHANTHEAL)
			{
				if (player->skill == SKILL_MAGICBALL)
				{
					pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
				}
			}
			if (nCntUI != UI_CHANTMAGIC)
			{
				if (player->skill == SKILL_HEAL)
				{
					pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
				}
			}
		}
		else
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}


	for (int nCntUI = 0; nCntUI < SKILL_MAX; nCntUI++)
	{
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffCooldown[nCntUI], 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	RECT rect = {450, 840, 1920, 950};    // 表示したい範囲

	char aStr[256];
	wsprintf(&aStr[0], "HP:%d                                               MP:%d", player->nLife, player->nMP);

	//テキストの描画
	g_pUIFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

	rect = { 680, 25, 1920, 100 };    // 表示したい範囲

	wsprintf(&aStr[0], "[BOSS] HP:%d\n", enemy->nLife);

	//テキストの描画
	g_pUIFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

	rect = { 690, 980, 1920, 1080 };    // 表示したい範囲

	if (bUsePad == true)
	{
		wsprintf(&aStr[0], "B                           Y                           X");
	}
	else
	{
		wsprintf(&aStr[0], "1                            2                           3");
	}

	//テキストの描画
	g_pUIFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

////////////////////////////////////////////////////////////////////////////////
//HPゲージの枠の頂点座標
////////////////////////////////////////////////////////////////////////////////
void SetVertexHPGauge(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUI[UI_HPGAUGE]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(430, 845, 0);
	pVtx[1].pos = D3DXVECTOR3(430, 800, 0);
	pVtx[2].pos = D3DXVECTOR3(950, 845, 0);
	pVtx[3].pos = D3DXVECTOR3(950, 800, 0);

	//頂点バッファをアンロックする
	g_pVtxBuffUI[UI_HPGAUGE]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//MPゲージの枠の頂点座標
////////////////////////////////////////////////////////////////////////////////
void SetVertexMPGauge(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUI[UI_MPGAUGE]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(970, 845, 0);
	pVtx[1].pos = D3DXVECTOR3(970, 800, 0);
	pVtx[2].pos = D3DXVECTOR3(1490, 845, 0);
	pVtx[3].pos = D3DXVECTOR3(1490, 800, 0);

	//頂点バッファをアンロックする
	g_pVtxBuffUI[UI_MPGAUGE]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//敵のHPゲージの枠の頂点座標
////////////////////////////////////////////////////////////////////////////////
void SetVertexEnemyHPGauge(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUI[UI_ENEMYHPGAUGE]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(660, 95, 0);
	pVtx[1].pos = D3DXVECTOR3(660, 50, 0);
	pVtx[2].pos = D3DXVECTOR3(1280, 95, 0);
	pVtx[3].pos = D3DXVECTOR3(1280, 50, 0);

	//頂点バッファをアンロックする
	g_pVtxBuffUI[UI_ENEMYHPGAUGE]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//HPの頂点座標
////////////////////////////////////////////////////////////////////////////////
void SetVertexHP(void)
{
	//変数宣言
	VERTEX_2D *pVtx;
	PLAYER *player = GetPlayer();
 	float fHP;

	fHP = (float)(player->nLife / (LIFE_PLAYER / 100));
	fHP = fHP * 5;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUI[UI_HP]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(440, 850, 0);
	pVtx[1].pos = D3DXVECTOR3(440, 800, 0);
	pVtx[2].pos = D3DXVECTOR3(440 + fHP, 850, 0);
	pVtx[3].pos = D3DXVECTOR3(440 + fHP, 800, 0);

	//頂点バッファをアンロックする
	g_pVtxBuffUI[UI_HP]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//MPの頂点座標
////////////////////////////////////////////////////////////////////////////////
void SetVertexMP(void)
{
	//変数宣言
	VERTEX_2D *pVtx;
	PLAYER *player = GetPlayer();
	float fMP;

	fMP = (float)(player->nMP / (MP_PLAYER / 100));
	fMP = fMP * 5;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUI[UI_MP]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(980, 850, 0);
	pVtx[1].pos = D3DXVECTOR3(980, 800, 0);
	pVtx[2].pos = D3DXVECTOR3(980 + fMP, 850, 0);
	pVtx[3].pos = D3DXVECTOR3(980 + fMP, 800, 0);

	//頂点バッファをアンロックする
	g_pVtxBuffUI[UI_MP]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//敵のHPの頂点座標
////////////////////////////////////////////////////////////////////////////////
void SetVertexENEMYHP(void)
{
	//変数宣言
	VERTEX_2D *pVtx;
	ENEMY *enemy = GetEnemy();
	float fEneHP;

	fEneHP = (float)(enemy->nLife / (LIFE_ENEMY / 100));
	fEneHP = fEneHP * 6;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUI[UI_ENEMYHP]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(670, 93, 0);
	pVtx[1].pos = D3DXVECTOR3(670, 50, 0);
	pVtx[2].pos = D3DXVECTOR3(670 + fEneHP, 93, 0);
	pVtx[3].pos = D3DXVECTOR3(670 + fEneHP, 50, 0);

	//頂点バッファをアンロックする
	g_pVtxBuffUI[UI_ENEMYHP]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//アクションスキルの頂点座標
////////////////////////////////////////////////////////////////////////////////
void SetVertexAction(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUI[UI_SKILLACTION]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(650, 980, 0);
	pVtx[1].pos = D3DXVECTOR3(650, 880, 0);
	pVtx[2].pos = D3DXVECTOR3(750, 980, 0);
	pVtx[3].pos = D3DXVECTOR3(750, 880, 0);

	//頂点バッファをアンロックする
	g_pVtxBuffUI[UI_SKILLACTION]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//攻撃魔法スキルの頂点座標
////////////////////////////////////////////////////////////////////////////////
void SetVertexMagic(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUI[UI_SKILLBALL]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(910, 980, 0);
	pVtx[1].pos = D3DXVECTOR3(910, 880, 0);
	pVtx[2].pos = D3DXVECTOR3(1010, 980, 0);
	pVtx[3].pos = D3DXVECTOR3(1010, 880, 0);

	//頂点バッファをアンロックする
	g_pVtxBuffUI[UI_SKILLBALL]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//回復魔法スキルの頂点座標
////////////////////////////////////////////////////////////////////////////////
void SetVertexHeal(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUI[UI_SKILLHEAL]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(1170, 980, 0);
	pVtx[1].pos = D3DXVECTOR3(1170, 880, 0);
	pVtx[2].pos = D3DXVECTOR3(1270, 980, 0);
	pVtx[3].pos = D3DXVECTOR3(1270, 880, 0);

	//頂点バッファをアンロックする
	g_pVtxBuffUI[UI_SKILLHEAL]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//クールダウンの頂点座標
////////////////////////////////////////////////////////////////////////////////
void SetVertexCooldown(int nIdx)
{
	//変数宣言
	VERTEX_2D *pVtx;
	PLAYER *player = GetPlayer();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffCooldown[nIdx]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	switch (nIdx)
	{
	case 0:
		pVtx[0].pos = D3DXVECTOR3(660, 972, 0);
		pVtx[1].pos = D3DXVECTOR3(660, 890, 0);
		pVtx[2].pos = D3DXVECTOR3(742, 972, 0);
		pVtx[3].pos = D3DXVECTOR3(742, 890, 0);
		break;

	case 1:
		pVtx[0].pos = D3DXVECTOR3(920, 972, 0);
		pVtx[1].pos = D3DXVECTOR3(920, 890, 0);
		pVtx[2].pos = D3DXVECTOR3(1002, 972, 0);
		pVtx[3].pos = D3DXVECTOR3(1002, 890, 0);
		break;

	case 2:
		pVtx[0].pos = D3DXVECTOR3(1180, 972, 0);
		pVtx[1].pos = D3DXVECTOR3(1180, 890, 0);
		pVtx[2].pos = D3DXVECTOR3(1262, 972, 0);
		pVtx[3].pos = D3DXVECTOR3(1262, 890, 0);
		break;

	default:
		pVtx[0].pos = D3DXVECTOR3(10000, 980, 0);
		pVtx[1].pos = D3DXVECTOR3(10000, 880, 0);
		pVtx[2].pos = D3DXVECTOR3(10000, 980, 0);
		pVtx[3].pos = D3DXVECTOR3(10000, 880, 0);
		break;
	}

	float fCooldown = ((float)player->nCooldown / (float)MAX_COOLDOWN);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, fCooldown);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, fCooldown);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, fCooldown);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, fCooldown);

	//頂点バッファをアンロックする
	g_pVtxBuffCooldown[nIdx]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//攻撃魔法詠唱時のゲージの枠の頂点座標
////////////////////////////////////////////////////////////////////////////////
void SetVertexChantMagic(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUI[UI_CHANTMAGIC]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(425, 800, 0);
	pVtx[1].pos = D3DXVECTOR3(425, 700, 0);
	pVtx[2].pos = D3DXVECTOR3(835, 800, 0);
	pVtx[3].pos = D3DXVECTOR3(835, 700, 0);

	//頂点バッファをアンロックする
	g_pVtxBuffUI[UI_CHANTMAGIC]->Unlock();
}

///////////////////////////////////////////////////////////////////////////////
//回復魔法詠唱時のゲージの枠の頂点座標
////////////////////////////////////////////////////////////////////////////////
void SetVertexChantHeal(void)
{
	//変数宣言
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUI[UI_CHANTHEAL]->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(425, 800, 0);
	pVtx[1].pos = D3DXVECTOR3(425, 700, 0);
	pVtx[2].pos = D3DXVECTOR3(835, 800, 0);
	pVtx[3].pos = D3DXVECTOR3(835, 700, 0);

	//頂点バッファをアンロックする
	g_pVtxBuffUI[UI_CHANTHEAL]->Unlock();
}

///////////////////////////////////////////////////////////////////////////////
//魔法詠唱時のゲージの頂点座標
////////////////////////////////////////////////////////////////////////////////
void SetVertexChant(void)
{
	//変数宣言
	VERTEX_2D *pVtx;
	PLAYER *player = GetPlayer();
	float fMagic = (((float)player->nChantCounter / (float)CHANT_TIMEMAGIC) * 400.0f);
	float fHeal = (((float)player->nChantCounter / (float)CHANT_TIMEHEAL) * 400.0f);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffUI[UI_CHANTGAUGE]->Lock(0, 0, (void**)&pVtx, 0);

	if (player->skill == SKILL_MAGICBALL)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(430, 790, 0);
		pVtx[1].pos = D3DXVECTOR3(430, 770, 0);
		pVtx[2].pos = D3DXVECTOR3(830 - fMagic, 790, 0);
		pVtx[3].pos = D3DXVECTOR3(830 - fMagic, 770, 0);
	}
	else if (player->skill == SKILL_HEAL)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(430, 790, 0);
		pVtx[1].pos = D3DXVECTOR3(430, 770, 0);
		pVtx[2].pos = D3DXVECTOR3(830 - fHeal, 790, 0);
		pVtx[3].pos = D3DXVECTOR3(830 - fHeal, 770, 0);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffUI[UI_CHANTGAUGE]->Unlock();
}