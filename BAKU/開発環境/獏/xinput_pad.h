////////////////////////////////////////////////////////////////////////////////
//
// Contents	:Xinputヘッダー [xinput_pad.h]
// Author	:Shota Furuichi
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _XINPUTPAD_H_
#define _XINPUTPAD_H_
#include "main.h"

////////////////////////////////////////////////////////////////////////////////
// 列挙型
////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	XINPUTSTATE_SHOOT = 0,
	XINPUTSTATE_MAX,
}XinputState;

////////////////////////////////////////////////////////////////////////////////
// 構造体の定義
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	bool bPressUP = false;
	bool bPressDOWN = false;
	bool bPressRIGHT = false;
	bool bPressLEFT = false;
	bool bPressA = false;			// Aボタンが押されてるかどうか
	bool bPressB = false;			// Bボタンが押されてるかどうか
	bool bPressX = false;			// Xボタンが押されてるかどうか
	bool bPressY = false;			// Yボタンが押されてるかどうか
	bool bPressStart = false;		//スタートボタンが押されているかどうか
	bool bPressLStick;				// 左スティックを傾けたかどうか
	bool bPressLStickUP;			// 左スティックを上に傾けたかどうか
	bool bPressLStickDOWN;			// 左スティックを下に傾けたかどうか
	bool bPressLStickRIGHT;			// 左スティックを右に傾けたかどうか
	bool bPressLStickLEFT;			// 左スティックを左に傾けたかどうか
	float fAngleL;					// 左スティックの入力角度
	bool bPressRStick;				// 右スティックを傾けたかどうか
	bool bPressRStickUP;			// 右スティックを上に傾けたかどうか
	bool bPressRStickDOWN;			// 右スティックを下に傾けたかどうか
	bool bPressRStickRIGHT;			// 右スティックを右に傾けたかどうか
	bool bPressRStickLEFT;			// 右スティックを左に傾けたかどうか
	float fAngleR;					// 右スティックの入力角度
}XinputGamepad;

////////////////////////////////////////////////////////////////////////////////
// プロトタイプ宣言
////////////////////////////////////////////////////////////////////////////////
void LoadGamepad(void);						// ゲームパッド情報の読み込み
void XinputButtons(void);					// ボタン処理
void XinputSticks(void);					// スティック処理
XinputGamepad *GetXinputGamepad(void);		// ゲームパッド情報を取得
bool GetUseGamepad(void);					//ゲームパッドの使用状況を取得

#endif
