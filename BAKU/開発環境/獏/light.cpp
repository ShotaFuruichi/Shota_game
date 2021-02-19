////////////////////////////////////////////////////////////////////////////////
//
//Contents	: ライトの処理 [light.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/11/15
//
////////////////////////////////////////////////////////////////////////////////
#include "light.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define MAX_LIGHT (3)

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
D3DLIGHT9 g_aLight[MAX_LIGHT];	//ライトの情報

////////////////////////////////////////////////////////////////////////////////
//初期化処理
////////////////////////////////////////////////////////////////////////////////
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXVECTOR3 vecDir[MAX_LIGHT];				//設定用方向のベクトル

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//ライトをクリアする
		ZeroMemory(&g_aLight[nCntLight], sizeof(D3DLIGHT9));

		//ライトの種類を設定
		g_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;	//平行光源
	}

	//ライトの拡散光を設定
	g_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_aLight[1].Diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
	g_aLight[2].Diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
	

	//ライトの方向を設定
	vecDir[0] = D3DXVECTOR3(0.4f, -0.5f, 0.4f);
	vecDir[1] = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vecDir[2] = D3DXVECTOR3(-0.3f, -0.2f, -0.4f);
	

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);	//正規化する
		g_aLight[nCntLight].Direction = vecDir[nCntLight];

		//ライトを設定する
		pDevice->SetLight(nCntLight, &g_aLight[nCntLight]);
	
		//ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

////////////////////////////////////////////////////////////////////////////////
//終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitLight(void)
{

}

////////////////////////////////////////////////////////////////////////////////
//更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateLight(void)
{

}