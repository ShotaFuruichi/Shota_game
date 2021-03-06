////////////////////////////////////////////////////////////////////////////////
//
// Contents	:Xinput (xinput_pad.cpp)
// Author	:Shota Furuichi
//
////////////////////////////////////////////////////////////////////////////////
#include "input.h"
#include "xinput_pad.h"

////////////////////////////////////////////////////////////////////////////////
// グローバル変数
////////////////////////////////////////////////////////////////////////////////
XINPUT_STATE g_state;					// Xinputコントローラーの状態
XinputGamepad g_XinputGamepad;			// ゲームパッド情報
bool g_bUseGamepad = false;				//ゲームパッドを使用しているか

////////////////////////////////////////////////////////////////////////////////
// ゲームパッド情報の読み込み
////////////////////////////////////////////////////////////////////////////////
void LoadGamepad(void)
{
	// 変数の初期化
	g_XinputGamepad.bPressUP = false;
	g_XinputGamepad.bPressDOWN = false;
	g_XinputGamepad.bPressRIGHT = false;
	g_XinputGamepad.bPressLEFT = false;
	g_XinputGamepad.bPressA = false;
	g_XinputGamepad.bPressB = false;
	g_XinputGamepad.bPressX = false;
	g_XinputGamepad.bPressY = false;
	g_XinputGamepad.bPressStart = false;
	g_XinputGamepad.bPressLStick = false;
	g_XinputGamepad.bPressLStickUP = false;
	g_XinputGamepad.bPressLStickDOWN = false;
	g_XinputGamepad.bPressLStickRIGHT = false;
	g_XinputGamepad.bPressLStickLEFT = false;
	g_XinputGamepad.bPressRStick = false;
	g_XinputGamepad.bPressRStickUP = false;
	g_XinputGamepad.bPressRStickDOWN = false;
	g_XinputGamepad.bPressRStickRIGHT = false;
	g_XinputGamepad.bPressRStickLEFT = false;

	// 情報の初期化
	ZeroMemory(&g_state, sizeof(XINPUT_STATE));

	// コントローラーの状態を取得.
	DWORD dwResult = XInputGetState(0, &g_state);

	if (dwResult == ERROR_SUCCESS)
	{
		// ボタンがおされているかどうか
		XinputButtons();

		// スティック処理
		XinputSticks();

		//ゲームパッド使用
		g_bUseGamepad = true;
	}
	else
	{
		g_bUseGamepad = false;
	}
}

////////////////////////////////////////////////////////////////////////////////
// ボタン処理
////////////////////////////////////////////////////////////////////////////////
void XinputButtons(void)
{
	XINPUT_KEYSTROKE Key;

	XInputGetKeystroke(0, NULL, &Key);

	if (Key.VirtualKey == VK_PAD_DPAD_UP && Key.Flags == XINPUT_KEYSTROKE_KEYDOWN)
	{
		g_XinputGamepad.bPressUP = true;
	}
	if (Key.VirtualKey == VK_PAD_DPAD_DOWN && Key.Flags == XINPUT_KEYSTROKE_KEYDOWN)
	{
		g_XinputGamepad.bPressDOWN = true;
	}
	if (Key.VirtualKey == VK_PAD_DPAD_RIGHT && Key.Flags == XINPUT_KEYSTROKE_KEYDOWN)
	{
		g_XinputGamepad.bPressRIGHT = true;
	}
	if (Key.VirtualKey == VK_PAD_DPAD_LEFT && Key.Flags == XINPUT_KEYSTROKE_KEYDOWN)
	{
		g_XinputGamepad.bPressLEFT = true;
	}
	if (Key.VirtualKey == VK_PAD_A && Key.Flags == XINPUT_KEYSTROKE_KEYDOWN)
	{
		g_XinputGamepad.bPressA = true;
	}
	if (Key.VirtualKey == VK_PAD_B && Key.Flags == XINPUT_KEYSTROKE_KEYDOWN)
	{
		g_XinputGamepad.bPressB = true;
	}
	if (Key.VirtualKey == VK_PAD_X && Key.Flags == XINPUT_KEYSTROKE_KEYDOWN)
	{
		g_XinputGamepad.bPressX = true;
	}
	if (Key.VirtualKey == VK_PAD_Y && Key.Flags == XINPUT_KEYSTROKE_KEYDOWN)
	{
		g_XinputGamepad.bPressY = true;
	}
	if (Key.VirtualKey == VK_PAD_START && Key.Flags == XINPUT_KEYSTROKE_KEYDOWN)
	{
		g_XinputGamepad.bPressStart = true;
	}
	//if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
	//{// 十字上ボタンが押されたらtrueに設定
	//	g_XinputGamepad.bPressUP = true;
	//}
	//if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
	//{// 十字下ボタンが押されたらtrueに設定
	//	g_XinputGamepad.bPressDOWN = true;
	//}
	//if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
	//{// 十字右ボタンが押されたらtrueに設定
	//	g_XinputGamepad.bPressRIGHT = true;
	//}
	//if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
	//{// 十字左ボタンが押されたらtrueに設定
	//	g_XinputGamepad.bPressLEFT = true;
	//}
	//if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	//{// Aボタンが押されたらtrueに設定
	//	g_XinputGamepad.bPressA = true;
	//}
	//if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
	//{// Bボタンが押されたらtrueに設定
	//	g_XinputGamepad.bPressB = true;
	//}
	//if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
	//{// Xボタンが押されたらtrueに設定
	//	g_XinputGamepad.bPressX = true;
	//}
	//if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
	//{// Yボタンが押されたらtrueに設定
	//	g_XinputGamepad.bPressY = true;
	//}
	//if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
	//{// スタートボタンが押されたらtrueに設定
	//	g_XinputGamepad.bPressStart = true;
	//}
}

////////////////////////////////////////////////////////////////////////////////
// スティック処理
////////////////////////////////////////////////////////////////////////////////
void XinputSticks(void)
{
	////////////////////////////////////////////////////////////////////////////
	//左
	////////////////////////////////////////////////////////////////////////////
	// デッドゾーンの設定
	if ((g_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		g_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(g_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		g_state.Gamepad.sThumbLX = 0;
		g_state.Gamepad.sThumbLY = 0;
	}

	if (g_state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{// Yボタンが押されたらtrueに設定
		g_XinputGamepad.bPressLStickUP = true;
	}
	if (g_state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{// Yボタンが押されたらtrueに設定
		g_XinputGamepad.bPressLStickDOWN = true;
	}
	if (g_state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{// Yボタンが押されたらtrueに設定
		g_XinputGamepad.bPressLStickRIGHT = true;
	}
	if (g_state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{// Yボタンが押されたらtrueに設定
		g_XinputGamepad.bPressLStickLEFT = true;
	}

	// JOYPADのスティック入力
	if (g_state.Gamepad.sThumbLX != 0 || g_state.Gamepad.sThumbLY != 0)
	{// スティックの入力角度
		g_XinputGamepad.fAngleL = atan2f((float)g_state.Gamepad.sThumbLX, (float)g_state.Gamepad.sThumbLY * -1);

		// スティックを傾けたことを伝える
		g_XinputGamepad.bPressLStick = true;
	}

	////////////////////////////////////////////////////////////////////////////
	//右
	////////////////////////////////////////////////////////////////////////////
	// デッドゾーンの設定
	if ((g_state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		g_state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(g_state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			g_state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		g_state.Gamepad.sThumbRX = 0;
		g_state.Gamepad.sThumbRY = 0;
	}

	if (g_state.Gamepad.sThumbRY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{// Yボタンが押されたらtrueに設定
		g_XinputGamepad.bPressRStickUP = true;
	}
	if (g_state.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{// Yボタンが押されたらtrueに設定
		g_XinputGamepad.bPressRStickDOWN = true;
	}
	if (g_state.Gamepad.sThumbRX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{// Yボタンが押されたらtrueに設定
		g_XinputGamepad.bPressRStickRIGHT = true;
	}
	if (g_state.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{// Yボタンが押されたらtrueに設定
		g_XinputGamepad.bPressRStickLEFT = true;
	}

	// JOYPADのスティック入力
	if (g_state.Gamepad.sThumbRX != 0 || g_state.Gamepad.sThumbRY != 0)
	{// スティックの入力角度
		g_XinputGamepad.fAngleR = atan2f((float)g_state.Gamepad.sThumbRX, (float)g_state.Gamepad.sThumbRY * -1);

		// スティックを傾けたことを伝える
		g_XinputGamepad.bPressRStick = true;
	}
}

////////////////////////////////////////////////////////////////////////////////
// ボタンが押されたかどうか取得
////////////////////////////////////////////////////////////////////////////////
XinputGamepad *GetXinputGamepad(void)
{
	return &g_XinputGamepad;
}

////////////////////////////////////////////////////////////////////////////////
// ボタンが押されたかどうか取得
////////////////////////////////////////////////////////////////////////////////
bool GetUseGamepad(void)
{
	return g_bUseGamepad;
}

