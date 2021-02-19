////////////////////////////////////////////////////////////////////////////////
//
// Contents	:Xinput�w�b�_�[ [xinput_pad.h]
// Author	:Shota Furuichi
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _XINPUTPAD_H_
#define _XINPUTPAD_H_
#include "main.h"

////////////////////////////////////////////////////////////////////////////////
// �񋓌^
////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	XINPUTSTATE_SHOOT = 0,
	XINPUTSTATE_MAX,
}XinputState;

////////////////////////////////////////////////////////////////////////////////
// �\���̂̒�`
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	bool bPressUP = false;
	bool bPressDOWN = false;
	bool bPressRIGHT = false;
	bool bPressLEFT = false;
	bool bPressA = false;			// A�{�^����������Ă邩�ǂ���
	bool bPressB = false;			// B�{�^����������Ă邩�ǂ���
	bool bPressX = false;			// X�{�^����������Ă邩�ǂ���
	bool bPressY = false;			// Y�{�^����������Ă邩�ǂ���
	bool bPressStart = false;		//�X�^�[�g�{�^����������Ă��邩�ǂ���
	bool bPressLStick;				// ���X�e�B�b�N���X�������ǂ���
	bool bPressLStickUP;			// ���X�e�B�b�N����ɌX�������ǂ���
	bool bPressLStickDOWN;			// ���X�e�B�b�N�����ɌX�������ǂ���
	bool bPressLStickRIGHT;			// ���X�e�B�b�N���E�ɌX�������ǂ���
	bool bPressLStickLEFT;			// ���X�e�B�b�N�����ɌX�������ǂ���
	float fAngleL;					// ���X�e�B�b�N�̓��͊p�x
	bool bPressRStick;				// �E�X�e�B�b�N���X�������ǂ���
	bool bPressRStickUP;			// �E�X�e�B�b�N����ɌX�������ǂ���
	bool bPressRStickDOWN;			// �E�X�e�B�b�N�����ɌX�������ǂ���
	bool bPressRStickRIGHT;			// �E�X�e�B�b�N���E�ɌX�������ǂ���
	bool bPressRStickLEFT;			// �E�X�e�B�b�N�����ɌX�������ǂ���
	float fAngleR;					// �E�X�e�B�b�N�̓��͊p�x
}XinputGamepad;

////////////////////////////////////////////////////////////////////////////////
// �v���g�^�C�v�錾
////////////////////////////////////////////////////////////////////////////////
void LoadGamepad(void);						// �Q�[���p�b�h���̓ǂݍ���
void XinputButtons(void);					// �{�^������
void XinputSticks(void);					// �X�e�B�b�N����
XinputGamepad *GetXinputGamepad(void);		// �Q�[���p�b�h�����擾
bool GetUseGamepad(void);					//�Q�[���p�b�h�̎g�p�󋵂��擾

#endif
