//-------------------------------------------------------------------
//
// セットパーティクル (setparticle.cpp)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#include "setparticle.h"
#include "effect.h"

//-------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------
#define Appear		(2)				// 出現量
#define MOVE		(2)				// 移動量
#define HEIGHT		(2)				// 高さ
#define RCOL		(1.0f)			// R成分
#define GCOL		(1.0f)			// G成分
#define BCOL		(1.0f)			// B成分
#define RANDIUS		(5)				// 半径
#define ALPHA		(0.01f)			// α値の減少量
#define GRAVITY		(0.0f)			// 重力

//-------------------------------------------------------------------
// グローバル変数
//-------------------------------------------------------------------
int g_nCnt = 0;

//-------------------------------------------------------------------
// テスト
//-------------------------------------------------------------------
void SetParticle(void)
{
	g_nCnt++;

	if (g_nCnt % 10 == 0)
	{
		for (int nCnt = 0; nCnt < Appear; nCnt++)
		{// 角度の設定
			float fAngle = ((float)(rand() % 628 - 314)) / 100.0f;
			float fmove = (float)(rand() % MOVE + 1);

			// エフェクトの設定
			SetEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(sinf(fAngle) * fmove, HEIGHT, cosf(fAngle) * fmove),
				D3DXCOLOR(RCOL, GCOL, BCOL, 1.0f),
				1.0f,
				(float)(rand() % 10 + RANDIUS),
				ALPHA,
				GRAVITY);
		}
	}
}

//-------------------------------------------------------------------
// 弾の軌道
//-------------------------------------------------------------------
void SetOrbitBullet(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		// エフェクトの設定
		SetEffect(pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXCOLOR(0.9f, 0.7f, 0.2f, 1.0f),
			1.0f,
			10.0f,
			0.07f,
			0.0f);
	}
}