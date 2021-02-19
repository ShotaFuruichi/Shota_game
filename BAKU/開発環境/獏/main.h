////////////////////////////////////////////////////////////////////////////////
//
//Contents	: アクションゲーム [main.h]
//Author	: ShotaFuruichi
//Since		: 2020/10/13
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _MAIN_H_
#define _MAIN_H_
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "d3dx9.h"		//描画処理に必要
#define DIRECTINPUT_VERSION (0x0800)
#include "dInput.h"		//入力処理に必要
#include "xaudio2.h"	//サウンド再生に必要
#include "XInput.h"		//xinputに必要
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)


//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//拡張ライブラリ
#pragma comment(lib,"dxguid.lib")	//コンポーネント使用に必要
#pragma comment(lib,"dInput8.lib")	//入力処理に必要
#pragma comment(lib,"winmm.lib")	//
#pragma comment(lib,"xinput.lib")	//xinoutに必要

//マクロ定義
#define SCREEN_WIDTH (1920)												//スクリーンの幅
#define SCREEN_HEIGHT (1080)											//スクリーンの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//頂点フォーマット

//頂点フォーマットに合わせた構造体
typedef struct
{
	D3DXVECTOR3 pos;	//ポリゴン座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR col;		//カラー情報
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_3D;

typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_2D;

//モード列挙型
typedef enum
{
	MODE_TITLE = 0,
	MODE_TUTORIAL,
	MODE_GAME,
	MODE_RESULT,
	MODE_RANKING,
	MODE_MAX
} MODE;

//プロトタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);
void DrawFPS(void);
void DrawText(void);
void SetMode(MODE mode);
HWND GethWnd(void);
#endif
