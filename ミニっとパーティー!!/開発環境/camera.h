//-------------------------------------------------------------------
//
// カメラヘッダー (camera.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//-----------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------
#define MAX_CAMERA			(5)

//-------------------------------------------------------------------
// カメラの種類(列挙型)
//-------------------------------------------------------------------
typedef enum
{
	CAMERATYPE_FIXED = 0,				// 固定カメラ
	CAMERATYPE_MAX,
}CAMERATYPE;

//-------------------------------------------------------------------
// 構造体の定義
//-------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 posV;			// 視点
	D3DXVECTOR3 posVDest;		// 目的の視点
	D3DXVECTOR3 posR;			// 注視点
	D3DXVECTOR3 posRDest;		// 目的の注視点
	D3DXVECTOR3 vecU;			// 上方向ベクトル
	D3DXVECTOR3 rot;			// 向き
	D3DXVECTOR3 move;			// 移動量
	D3DXVECTOR3 moveV;			// 視点の移動量
	D3DXVECTOR3 moveR;			// 注視点の移動量
	D3DXMATRIX mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX mtxView;			// ビューマトリックス
	D3DVIEWPORT9 viewport;		// ビューポート
	float fLenge;				// どれだけ離れているか
}Camera_Info;

typedef struct
{
	Camera_Info CameraInfo[MAX_CAMERA];
	int nNumCamera;
}Camera;

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
void InitCamera(void);			// カメラの初期化処理
void UninitCamera(void);		// カメラの終了処理
void UpdateCamera(void);		// カメラの更新処理
void SetCamera(int nIdx);		// カメラの配置

void KeyboradFollow(void);		// カメラのキーボード操作(追従)

void InitGameCamera(void);		// ゲーム画面のカメラ初期化

Camera *GetCamera(void);		// カメラ情報の取得

#endif