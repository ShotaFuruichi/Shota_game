//-----------------------------------------------------------------
//
// カメラ (camera.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "camera.h"
#include "chara.h"
#include "input.h"
#include "gamepad.h"

//-----------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------
#define MOVE_CAMERA			(3.0f)
#define LENGTH				(500.0f)
#define ROT					(0.03f)
#define PI_QUARTER			(D3DX_PI / 4.0f)

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
Camera g_camera;			// カメラ情報

//-----------------------------------------------------------------
// カメラの初期化処理
//-----------------------------------------------------------------
void InitCamera(void)
{
	// 変数の初期化
	// 固定カメラ
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		g_camera.CameraInfo[nCntCamera].posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].posVDest = g_camera.CameraInfo[nCntCamera].posV;
		g_camera.CameraInfo[nCntCamera].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].posRDest = g_camera.CameraInfo[nCntCamera].posR;
		g_camera.CameraInfo[nCntCamera].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].moveV = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].viewport.X = 0;
		g_camera.CameraInfo[nCntCamera].viewport.Y = 0;
		g_camera.CameraInfo[nCntCamera].viewport.Width = SCREEN_WIDTH;
		g_camera.CameraInfo[nCntCamera].viewport.Height = SCREEN_HEIGHT;
		g_camera.CameraInfo[nCntCamera].viewport.MinZ = 0.0f;
		g_camera.CameraInfo[nCntCamera].viewport.MaxZ = 1.0f;
	}
}

//-----------------------------------------------------------------
// カメラの終了処理
//-----------------------------------------------------------------
void UninitCamera(void)
{
	// 変数の初期化
	// 固定カメラ
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		g_camera.CameraInfo[nCntCamera].posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].posVDest = g_camera.CameraInfo[nCntCamera].posV;
		g_camera.CameraInfo[nCntCamera].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].posRDest = g_camera.CameraInfo[nCntCamera].posR;
		g_camera.CameraInfo[nCntCamera].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].moveV = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.CameraInfo[nCntCamera].viewport.X = 0;
		g_camera.CameraInfo[nCntCamera].viewport.Y = 0;
		g_camera.CameraInfo[nCntCamera].viewport.Width = SCREEN_WIDTH;
		g_camera.CameraInfo[nCntCamera].viewport.Height = SCREEN_HEIGHT;
		g_camera.CameraInfo[nCntCamera].viewport.MinZ = 0.0f;
		g_camera.CameraInfo[nCntCamera].viewport.MaxZ = 1.0f;
	}
	g_camera.nNumCamera = 0;
}

//-----------------------------------------------------------------
// カメラの更新処理
//-----------------------------------------------------------------
void UpdateCamera(void)
{
	// 追従
	KeyboradFollow();
}

//-----------------------------------------------------------------
// カメラの設置
//-----------------------------------------------------------------
void SetCamera(int nIdx)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;	// デバイスへのポインタ

	// 変数の受け渡し
	pDevice = GetDevice();

	// ビューポートの設定
	pDevice->SetViewport(&g_camera.CameraInfo[nIdx].viewport);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.CameraInfo[nIdx].mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_camera.CameraInfo[nIdx].mtxProjection,
		D3DXToRadian(45.0f),
		(float)g_camera.CameraInfo[nIdx].viewport.Width / (float)g_camera.CameraInfo[nIdx].viewport.Height,
		10.0f,
		3000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.CameraInfo[nIdx].mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.CameraInfo[nIdx].mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.CameraInfo[nIdx].mtxView,
		&g_camera.CameraInfo[nIdx].posV,
		&g_camera.CameraInfo[nIdx].posR,
		&g_camera.CameraInfo[nIdx].vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.CameraInfo[nIdx].mtxView);
}

//-----------------------------------------------------------------
// カメラのキーボード操作(追従)
//-----------------------------------------------------------------
void KeyboradFollow(void)
{
	// プレイヤー情報の取得
	Character *pCharacter = GetCharacter();
#if _DEBUG

	if (GetKeyboardPress(KEYINFO_UP) == true)
	{
		// モデル上移動
		g_camera.CameraInfo[0].moveR.x -= 10.0f * sinf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveR.z += 10.0f * cosf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveV.x -= 10.0f * sinf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveV.z += 10.0f * cosf(-g_camera.CameraInfo[0].rot.y);
		
	}
	if (GetKeyboardPress(KEYINFO_DOWN) == true)
	{
		// モデル下移動
		g_camera.CameraInfo[0].moveR.x += 10.0f * sinf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveR.z -= 10.0f * cosf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveV.x += 10.0f * sinf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveV.z -= 10.0f * cosf(-g_camera.CameraInfo[0].rot.y);
	}
	if (GetKeyboardPress(KEYINFO_RIGHT) == true)
	{// モデル右移動
		g_camera.CameraInfo[0].moveR.x += 10.0f * cosf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveR.z += 10.0f * sinf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveV.x += 10.0f * cosf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveV.z += 10.0f * sinf(-g_camera.CameraInfo[0].rot.y);

	}
	if (GetKeyboardPress(KEYINFO_LEFT) == true)
	{// モデル左移動
		g_camera.CameraInfo[0].moveR.x -= 10.0f * cosf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveR.z -= 10.0f * sinf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveV.x -= 10.0f * cosf(-g_camera.CameraInfo[0].rot.y);
		g_camera.CameraInfo[0].moveV.z -= 10.0f * sinf(-g_camera.CameraInfo[0].rot.y);
	}
	if (GetKeyboardPress(KEYINFO_ROT_LEFT) == true)
	{// 視点の左回転
		g_camera.CameraInfo[CAMERATYPE_FIXED].rot.y -= ROT;						// 回転量

		if (g_camera.CameraInfo[CAMERATYPE_FIXED].rot.y < -D3DX_PI)
		{// 3.14fより大きくなったとき値を-3.14fにする
			g_camera.CameraInfo[CAMERATYPE_FIXED].rot.y += D3DX_PI * 2.0f;
		}
	}
	else if (GetKeyboardPress(KEYINFO_ROT_RIGHT) == true)
	{// 視点の右回転
		g_camera.CameraInfo[CAMERATYPE_FIXED].rot.y += ROT;						// 回転量

		if (g_camera.CameraInfo[CAMERATYPE_FIXED].rot.y > D3DX_PI)
		{// -3.14fより小さくなったとき値を3.14fにする
			g_camera.CameraInfo[CAMERATYPE_FIXED].rot.y -= D3DX_PI * 2.0f;
		}
	}
	if (GetKeyboardPress(KEYINFO_ROT_UP) == true)
	{// 視点の左回転
		g_camera.CameraInfo[0].moveV.y += 2.0f;						// 回転量
	}
	if (GetKeyboardPress(KEYINFO_ROT_DOWN) == true)
	{// 視点の右回転
		g_camera.CameraInfo[0].moveV.y -= 2.0f;						// 回転量
	}
	if (GetKeyboardPress(KEYINFO_ROT_CAMERA_UP) == true)
	{// 視点の左回転
		g_camera.CameraInfo[0].moveR.y += 2.0f;						// 回転量
	}
	if (GetKeyboardPress(KEYINFO_ROT_CAMERA_DOWN) == true)
	{// 視点の右回転
		g_camera.CameraInfo[0].moveR.y -= 2.0f;						// 回転量
	}

#endif
	for (int nCntCamera = 0; nCntCamera < g_camera.nNumCamera; nCntCamera++)
	{
		// 目的の注視点
		g_camera.CameraInfo[nCntCamera].posRDest.x = g_camera.CameraInfo[nCntCamera].moveR.x;		// 目的の注視点のX軸座標の決定
		g_camera.CameraInfo[nCntCamera].posRDest.z = g_camera.CameraInfo[nCntCamera].moveR.z;		// 目的の注視点のZ軸座標の決定
		g_camera.CameraInfo[nCntCamera].posRDest.y = g_camera.CameraInfo[nCntCamera].moveR.y;

		// 目的の視点
		g_camera.CameraInfo[nCntCamera].posVDest.x =  sinf(g_camera.CameraInfo[nCntCamera].rot.y) * -g_camera.CameraInfo[nCntCamera].fLenge + g_camera.CameraInfo[nCntCamera].moveV.x;	// 目的の視点のX軸座標の決定
		g_camera.CameraInfo[nCntCamera].posVDest.z =  cosf(g_camera.CameraInfo[nCntCamera].rot.y) * -g_camera.CameraInfo[nCntCamera].fLenge + g_camera.CameraInfo[nCntCamera].moveV.z;	// 目的の視点のZ軸座標の決定
		g_camera.CameraInfo[nCntCamera].posVDest.y =  g_camera.CameraInfo[nCntCamera].moveV.y;

		// 注視点の更新
		g_camera.CameraInfo[nCntCamera].posR.x += (g_camera.CameraInfo[nCntCamera].posRDest.x - g_camera.CameraInfo[nCntCamera].posR.x) * 1.0f;	// 注視点のX軸座標の決定
		g_camera.CameraInfo[nCntCamera].posR.z += (g_camera.CameraInfo[nCntCamera].posRDest.z - g_camera.CameraInfo[nCntCamera].posR.z) * 1.0f;	// 注視点のZ軸座標の決定
		g_camera.CameraInfo[nCntCamera].posR.y += (g_camera.CameraInfo[nCntCamera].posRDest.y - g_camera.CameraInfo[nCntCamera].posR.y) * 1.0f;	// 注視点のY軸座標の決定

		// 視点の更新
		g_camera.CameraInfo[nCntCamera].posV.x += (g_camera.CameraInfo[nCntCamera].posVDest.x - g_camera.CameraInfo[nCntCamera].posV.x) * 1.0f;	// 視点のX軸座標の決定
		g_camera.CameraInfo[nCntCamera].posV.z += (g_camera.CameraInfo[nCntCamera].posVDest.z - g_camera.CameraInfo[nCntCamera].posV.z) * 1.0f;	// 視点のZ軸座標の決定
		g_camera.CameraInfo[nCntCamera].posV.y += (g_camera.CameraInfo[nCntCamera].posVDest.y - g_camera.CameraInfo[nCntCamera].posV.y) * 1.0f;
	}
}

//-----------------------------------------------------------------
// ゲーム画面のカメラ初期化
//-----------------------------------------------------------------
void InitGameCamera(void)
{

}


//-----------------------------------------------------------------
// カメラ情報の取得
//-----------------------------------------------------------------
Camera *GetCamera(void)
{
	return &g_camera;
}