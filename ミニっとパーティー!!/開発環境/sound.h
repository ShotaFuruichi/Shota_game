//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_TITLE = 0,		// タイトル
	SOUND_LABEL_TUTORIAL,				// チュートリアル
	SOUND_LABEL_CHARASELECT,			// バトル
	SOUND_LABEL_GAME,			// リザルトBGM
	SOUND_LABEL_RESULT,		// ランキング
	SOUND_LABEL_SE_COUNTDOWN,		// ジャンプ音
	SOUND_LABEL_SE_START,		// 踏む音
	SOUND_LABEL_SE_CURSOR,		// 敵に当たったとき
	SOUND_LABEL_SE_DICIDE,		// ダメージを受けたとき
	SOUND_LABEL_SE_FINISH,		// コイン獲得
	SOUND_LABEL_SE_PAUSE,		// 選択(下)
	SOUND_LABEL_SE_RESULT_IN,			// 選択(上)
	SOUND_LABEL_SE_CANSEL,	// ポーズ画面(入)
	SOUND_LABEL_SE_BOMB,
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
