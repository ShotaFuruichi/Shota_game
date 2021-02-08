////////////////////////////////////////////////////////////////////////////////
//
// Contents	:Xinput (xinput_pad.cpp)
// Author	:Shota Furuichi
//
////////////////////////////////////////////////////////////////////////////////
#include "input.h"
#include "xinput_pad.h"

////////////////////////////////////////////////////////////////////////////////
// �O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
XINPUT_STATE g_state;					// Xinput�R���g���[���[�̏��
XinputGamepad g_XinputGamepad;			// �Q�[���p�b�h���

////////////////////////////////////////////////////////////////////////////////
// �Q�[���p�b�h���̓ǂݍ���
////////////////////////////////////////////////////////////////////////////////
void LoadGamepad(void)
{
	// �ϐ��̏�����
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

	// ���̏�����
	ZeroMemory(&g_state, sizeof(XINPUT_STATE));

	// �R���g���[���[�̏�Ԃ��擾.
	DWORD dwResult = XInputGetState(0, &g_state);

	if (dwResult == ERROR_SUCCESS)
	{
		// �{�^����������Ă��邩�ǂ���
		XinputButtons();

		// �X�e�B�b�N����
		XinputSticks();
	}
	else
	{
	}
}

////////////////////////////////////////////////////////////////////////////////
// �{�^������
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
	/*if (Key.VirtualKey == VK_PAD_B && Key.Flags == XINPUT_KEYSTROKE_REPEAT)
	{
		g_XinputGamepad.bPressB = true;
	}*/
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
	//{// �\����{�^���������ꂽ��true�ɐݒ�
	//	g_XinputGamepad.bPressUP = true;
	//}
	//if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
	//{// �\�����{�^���������ꂽ��true�ɐݒ�
	//	g_XinputGamepad.bPressDOWN = true;
	//}
	//if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
	//{// �\���E�{�^���������ꂽ��true�ɐݒ�
	//	g_XinputGamepad.bPressRIGHT = true;
	//}
	//if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
	//{// �\�����{�^���������ꂽ��true�ɐݒ�
	//	g_XinputGamepad.bPressLEFT = true;
	//}
	//if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	//{// A�{�^���������ꂽ��true�ɐݒ�
	//	g_XinputGamepad.bPressA = true;
	//}
	if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
	{// B�{�^���������ꂽ��true�ɐݒ�
		g_XinputGamepad.bPressB = true;
	}
	//if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
	//{// X�{�^���������ꂽ��true�ɐݒ�
	//	g_XinputGamepad.bPressX = true;
	//}
	//if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
	//{// Y�{�^���������ꂽ��true�ɐݒ�
	//	g_XinputGamepad.bPressY = true;
	//}
	//if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
	//{// �X�^�[�g�{�^���������ꂽ��true�ɐݒ�
	//	g_XinputGamepad.bPressStart = true;
	//}
}

////////////////////////////////////////////////////////////////////////////////
// �X�e�B�b�N����
////////////////////////////////////////////////////////////////////////////////
void XinputSticks(void)
{
	// �f�b�h�]�[���̐ݒ�
	if ((g_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		g_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(g_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		g_state.Gamepad.sThumbLX = 0;
		g_state.Gamepad.sThumbLY = 0;
	}

	//if (g_state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	//{// Y�{�^���������ꂽ��true�ɐݒ�
	//	g_XinputGamepad.bPressLStickUP = true;
	//}
	//if (g_state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	//{// Y�{�^���������ꂽ��true�ɐݒ�
	//	g_XinputGamepad.bPressLStickDOWN = true;
	//}
	//if (g_state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	//{// Y�{�^���������ꂽ��true�ɐݒ�
	//	g_XinputGamepad.bPressLStickRIGHT = true;
	//}
	//if (g_state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	//{// Y�{�^���������ꂽ��true�ɐݒ�
	//	g_XinputGamepad.bPressLStickLEFT = true;
	//}

	// JOYPAD�̃X�e�B�b�N����
	if (g_state.Gamepad.sThumbLX != 0 || g_state.Gamepad.sThumbLY != 0)
	{// �X�e�B�b�N�̓��͊p�x
		g_XinputGamepad.fAngle = atan2f((float)g_state.Gamepad.sThumbLX * -1, (float)g_state.Gamepad.sThumbLY);

		// �X�e�B�b�N���X�������Ƃ�`����
		g_XinputGamepad.bPressLStick = true;
	}
}

////////////////////////////////////////////////////////////////////////////////
// �{�^���������ꂽ���ǂ����擾
////////////////////////////////////////////////////////////////////////////////
XinputGamepad *GetXinputGamepad(void)
{
	return &g_XinputGamepad;
}

