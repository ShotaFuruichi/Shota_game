////////////////////////////////////////////////////////////////////////////////
//
//Contents	: カメラの処理 [camera.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/11/15
//
////////////////////////////////////////////////////////////////////////////////
#include "camera.h"
#include "player.h"
#include "input.h"
#include "xinput_pad.h"

////////////////////////////////////////////////////////////////////////////////
//マクロ定義
////////////////////////////////////////////////////////////////////////////////
#define CAMERA_SPEED (3.0f)
#define ROT_SPEED (0.025f)
#define MOVE_RANGE (-800.0f)
#define CAMERA_HEIGHT (450.0f)
#define CAMERA_DEST (10.0f)

////////////////////////////////////////////////////////////////////////////////
//グローバル変数
////////////////////////////////////////////////////////////////////////////////
CAMERA g_camera;	//カメラの情報
float g_cameraUD;	//注視点上下
float g_fRange = MOVE_RANGE;
float g_fHeight = CAMERA_HEIGHT;

////////////////////////////////////////////////////////////////////////////////
//初期化処理
////////////////////////////////////////////////////////////////////////////////
void InitCamera(void)
{
	D3DXVECTOR3 *posPlayer = GetPosPlayer();
	D3DXVECTOR3 *rotPlayer = GetRotPlayer();

	#if 0
	//一人称
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posR.x = posModel->x - sinf(rotModel->y) * 50.0f;
	g_camera.posR.y = posModel->y;
	g_camera.posR.z = posModel->z - cosf(rotModel->y) * 50.0f;
	g_camera.posV.x = g_camera.posR.x + sinf(rotModel->y) * 50.0f;
	g_camera.posV.y = g_camera.posR.y + sinf(rotModel->x) * 50.0f;
	g_camera.posV.z = g_camera.posR.z + cosf(rotModel->y) * 50.0f;
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	#endif

	#if 1
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posV = D3DXVECTOR3(0.0f, g_fHeight, g_fRange);
	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_fRange;
	g_camera.posR.y = g_camera.posV.y - g_fHeight;
	g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y) * g_fRange;
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	#endif

	////三人称
	//// 変数の初期化
	//g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -CAMERA_HEIGHT);
	//g_camera.posVDest = g_camera.posV;
	//g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_camera.posRDest = g_camera.posR;
	//g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_camera.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_camera.moveV = D3DXVECTOR3(0.0f, 150.0f, 0.0f);
}

////////////////////////////////////////////////////////////////////////////////
//終了処理
////////////////////////////////////////////////////////////////////////////////
void UninitCamera(void)
{

}

////////////////////////////////////////////////////////////////////////////////
//更新処理
////////////////////////////////////////////////////////////////////////////////
void UpdateCamera(void)
{
	MoveCamera();

	// リセット
	if (GetKeyboardTrigger(DIK_N) == true)
	{
		// 変数の初期化
		g_camera.posV = D3DXVECTOR3(0.0f, g_fHeight, -g_fHeight);
		g_camera.posVDest = g_camera.posV;
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.posRDest = g_camera.posR;
		g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_camera.moveV = D3DXVECTOR3(0.0f, 200.0f, 0.0f);
	}

	#if 0
	//一人称
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posR.x = posModel->x - sinf(rotModel->y) * 50.0f;
	g_camera.posR.y = posModel->y + sinf(rotModel->x) * 50.0f;
	g_camera.posR.z = posModel->z - cosf(rotModel->y) * 50.0f;
	g_camera.posV.x = g_camera.posR.x + sinf(rotModel->y) * 50.0f;
	g_camera.posV.y = g_camera.posR.y + sinf(rotModel->x) * 50.0f;
	g_camera.posV.z = g_camera.posR.z + cosf(rotModel->y) * 50.0f;
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	#endif
}

////////////////////////////////////////////////////////////////////////////////
//設定処理
////////////////////////////////////////////////////////////////////////////////
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 5000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView, &g_camera.posV, &g_camera.posR, &g_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

////////////////////////////////////////////////////////////////////////////////
//カメラ追従
////////////////////////////////////////////////////////////////////////////////
void MoveCamera(void)
{
	D3DXVECTOR3 *posPlayer = GetPosPlayer();
	D3DXVECTOR3 *rotPlayer = GetRotPlayer();
	XinputGamepad *pXinput = GetXinputGamepad();

	//if (GetKeyboardPress(DIK_UPARROW) == true)
	//{// カメラの上移動
	//	g_camera.move.x += CAMERA_SPEED * sinf(g_camera.rot.y);			// X軸移動量の決定
	//	g_camera.move.z += CAMERA_SPEED * cosf(g_camera.rot.y);			// Z軸移動量の決定
	//}
	//if (GetKeyboardPress(DIK_DOWNARROW) == true)
	//{// カメラの下移動
	//	g_camera.move.x -= CAMERA_SPEED * sinf(g_camera.rot.y);			// X軸移動量の決定
	//	g_camera.move.z -= CAMERA_SPEED * cosf(g_camera.rot.y);			// Z軸移動量の決定
	//}
	//if (GetKeyboardPress(DIK_RIGHTARROW) == true)
	//{// カメラの右移動
	//	g_camera.move.x += CAMERA_SPEED * cosf(g_camera.rot.y);			// X軸移動量の決定
	//	g_camera.move.z -= CAMERA_SPEED * sinf(g_camera.rot.y);			// Z軸移動量の決定
	//}
	//if (GetKeyboardPress(DIK_LEFTARROW) == true)
	//{// カメラの左移動
	//	g_camera.move.x -= CAMERA_SPEED * cosf(g_camera.rot.y);			// X軸移動量の決定
	//	g_camera.move.z += CAMERA_SPEED * sinf(g_camera.rot.y);			// Z軸移動量の決定
	//}

	//三人称
	g_camera.posR.x = posPlayer->x - sinf(rotPlayer->y) * CAMERA_DEST;
	g_camera.posR.y = posPlayer->y;
	g_camera.posR.z = posPlayer->z - cosf(rotPlayer->y) * CAMERA_DEST;
	g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_fRange;
	g_camera.posV.y = g_camera.posR.y + g_fHeight;
	g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_fRange;
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//視点旋回
	if (GetKeyboardPress(DIK_RIGHTARROW) == TRUE || pXinput->bPressRStickRIGHT == true)
	{
		g_camera.rot.y += ROT_SPEED;
		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_fRange;
		g_camera.posV.y = g_camera.posR.y + g_fHeight;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_fRange;
	}
	if (GetKeyboardPress(DIK_LEFTARROW) == TRUE || pXinput->bPressRStickLEFT == true)
	{
		g_camera.rot.y -= ROT_SPEED;
		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_fRange;
		g_camera.posV.y = g_camera.posR.y + g_fHeight;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_fRange;
	}
	if (GetKeyboardPress(DIK_DOWNARROW) == TRUE || pXinput->bPressRStickDOWN == true)
	{
		if (g_fHeight < (CAMERA_HEIGHT * 2.0f))
		{
			g_fHeight += CAMERA_SPEED;
			g_fRange -= CAMERA_SPEED;
		}
	}
	if (GetKeyboardPress(DIK_UPARROW) == TRUE || pXinput->bPressRStickUP == true)
	{
		if (g_fHeight > (CAMERA_HEIGHT / 2.0f))
		{
			g_fHeight -= CAMERA_SPEED;
			g_fRange += CAMERA_SPEED;
		}
	}

	if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y += D3DX_PI * 2.0f;
	}
	else if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= D3DX_PI * 2.0f;
	}
}

////////////////////////////////////////////////////////////////////////////////
//カメラの情報を取得
////////////////////////////////////////////////////////////////////////////////
CAMERA *GetCamera(void)
{
	return &g_camera;
}