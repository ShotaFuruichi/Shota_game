//-----------------------------------------------------------------
//
// ライト (light.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "light.h"
#include "input.h"

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
Light g_Light;			// ライト情報

//-----------------------------------------------------------------
// ライトの初期化処理
//-----------------------------------------------------------------
void InitLight(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;			// デバイスへのポインタ

	// 変数の受け渡し
	pDevice = GetDevice();

	// ライトをクリアする
	for (int nCntLight = 0; nCntLight < g_Light.nNumLight; nCntLight++)
	{
		ZeroMemory(&g_Light.aLightInfo[nCntLight], sizeof(D3DLIGHT9));

		// ライトの種類を設定
		g_Light.aLightInfo[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ライトの色を指定
		g_Light.aLightInfo[nCntLight].Diffuse = g_Light.colDef[nCntLight];

		// ライトの方向を設定
		D3DXVec3Normalize(&g_Light.vecDir[nCntLight], &g_Light.vecDir[nCntLight]);		// 正規化する
		g_Light.aLightInfo[nCntLight].Direction = g_Light.vecDir[nCntLight];

		// ライトを設定
		pDevice->SetLight(nCntLight, &g_Light.aLightInfo[nCntLight]);

		// ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//-----------------------------------------------------------------
// ライトの終了処理
//-----------------------------------------------------------------
void UninitLight(void)
{
	for (int nCntLight = 0; nCntLight < g_Light.nNumLight; nCntLight++)
	{
		g_Light.colDef[nCntLight].a = 0.0f;
		g_Light.colDef[nCntLight].r = 0.0f;
		g_Light.colDef[nCntLight].g = 0.0f;
		g_Light.colDef[nCntLight].b = 0.0f;
		g_Light.vecDir[nCntLight] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	g_Light.nNumLight = 0;											
}

//-----------------------------------------------------------------
// ライトの更新処理
//-----------------------------------------------------------------
void UpdateLight(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;			// デバイスへのポインタ

	// 変数の受け渡し
	pDevice = GetDevice();

	// ライトをクリアする
	for (int nCntLight = 0; nCntLight < g_Light.nNumLight; nCntLight++)
	{
		ZeroMemory(&g_Light.aLightInfo[nCntLight], sizeof(D3DLIGHT9));

		// ライトの種類を設定
		g_Light.aLightInfo[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ライトの色を指定
		g_Light.aLightInfo[nCntLight].Diffuse = g_Light.colDef[nCntLight];

		// ライトの方向を設定
		D3DXVec3Normalize(&g_Light.vecDir[nCntLight], &g_Light.vecDir[nCntLight]);		// 正規化する
		g_Light.aLightInfo[nCntLight].Direction = g_Light.vecDir[nCntLight];

		// ライトを設定
		pDevice->SetLight(nCntLight, &g_Light.aLightInfo[nCntLight]);

		// ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
#if _DEBUG
	if (GetKeyboardTrigger(KEYINFO_MODEL_UP) == true)
	{
		g_Light.nCntLight++;

		if (g_Light.nCntLight >= g_Light.nNumLight)
		{
			g_Light.nCntLight = 0;
		}
	}
	else if (GetKeyboardTrigger(KEYINFO_MODEL_DOWN) == true)
	{
		g_Light.nCntLight--;

		if (g_Light.nCntLight < 0)
		{
			g_Light.nCntLight = g_Light.nNumLight - 1;
		}
	}
	if (GetKeyboardPress(KEYINFO_DIK_1) == true)
	{
		g_Light.colDef[g_Light.nCntLight].r += 0.01f;

		if (g_Light.colDef[g_Light.nCntLight].r > 1.0f)
		{
			g_Light.colDef[g_Light.nCntLight].r = 1.0f;
		}
	}
	if (GetKeyboardPress(KEYINFO_DIK_2) == true)
	{
		g_Light.colDef[g_Light.nCntLight].r -= 0.01f;

		if (g_Light.colDef[g_Light.nCntLight].r < 0.0f)
		{
			g_Light.colDef[g_Light.nCntLight].r = 0.0f;
		}
	}
	if (GetKeyboardPress(KEYINFO_DIK_3) == true)
	{
		g_Light.colDef[g_Light.nCntLight].g += 0.01f;

		if (g_Light.colDef[g_Light.nCntLight].g > 1.0f)
		{
			g_Light.colDef[g_Light.nCntLight].g = 1.0f;
		}
	}
	if (GetKeyboardPress(KEYINFO_DIK_4) == true)
	{
		g_Light.colDef[g_Light.nCntLight].g -= 0.01f;

		if (g_Light.colDef[g_Light.nCntLight].g < 0.0f)
		{
			g_Light.colDef[g_Light.nCntLight].g = 0.0f;
		}
	}
	if (GetKeyboardPress(KEYINFO_DIK_5) == true)
	{
		g_Light.colDef[g_Light.nCntLight].b += 0.01f;

		if (g_Light.colDef[g_Light.nCntLight].b > 1.0f)
		{
			g_Light.colDef[g_Light.nCntLight].b = 1.0f;
		}
	}
	if (GetKeyboardPress(KEYINFO_DIK_6) == true)
	{
		g_Light.colDef[g_Light.nCntLight].b -= 0.01f;

		if (g_Light.colDef[g_Light.nCntLight].b < 0.0f)
		{
			g_Light.colDef[g_Light.nCntLight].b = 0.0f;
		}
	}
#endif
}

//-----------------------------------------------------------------
// ライト情報の取得
//-----------------------------------------------------------------
Light *GetLight(void)
{
	return &g_Light;
}