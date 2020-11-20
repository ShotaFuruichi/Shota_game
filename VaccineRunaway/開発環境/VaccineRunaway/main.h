////////////////////////////////////////////////////////////////////////////////
//
//Contents	: シューティングゲーム [main.h]
//Author	: ShotaFuruichi
//Since		: 2020/07/17
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _MAIN_H_
#define _MAIN_H_
#include <windows.h>
#include "d3dx9.h"		//描画処理に必要
#include "player.h"
#include "bg.h"
#define DIRECTINPUT_VERSION (0x0800)
#include "dInput.h"		//入力処理に必要
#include "xaudio2.h"	//サウンド再生に必要

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//拡張ライブラリ
#pragma comment(lib,"dxguid.lib")	//コンポーネント使用に必要
#pragma comment(lib,"dInput8.lib")	//入力処理に必要
#pragma comment(lib,"winmm.lib")	//

//マクロ定義
#define SCREEN_WIDTH (1920)												//スクリーンの幅
#define SCREEN_HEIGHT (1080)											//スクリーンの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//頂点フォーマット

//頂点フォーマットに合わせた構造体
typedef struct
{
	D3DXVECTOR3 pos;	//ポリゴン座標
	float rhw;
	D3DCOLOR col;		//カラー情報
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_2D;

//モードの種類
typedef enum
{
	MODE_TITLE = 0,	//タイトル画面
	MODE_TUTORIAL,	//チュートリアル画面
	MODE_GAME,		//ゲーム画面
	MODE_RESULT,	//リザルト画面
	MODE_MAX
} MODE;

//プロトタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif