//-----------------------------------------------------------------
//
// �`���[�g���A�� (tutorial.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "tutorial.h"
#include "tutorial_bg.h"
#include "loadscreen.h"
#include "sound.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "wall.h"
#include "model_set.h"
#include "meshfield.h"

//-----------------------------------------------------------------
// �`���[�g���A���̏���������
//-----------------------------------------------------------------
HRESULT InitTutorial(void)
{
	// �`���[�g���A����ʔw�i�̏���������
	InitTutorialBg();

	// ���b�V���t�B�[���h�̏���������
	InitMeshField();

	// �ǂ̏���������
	InitWall();

	InitLoadScreen();

	return S_OK;
}

//-----------------------------------------------------------------
// �`���[�g���A���̏I������
//-----------------------------------------------------------------
void UninitTutorial(void)
{
	UninitLoadScreen();

	// �ǂ̏I������
	UninitWall();

	// ���b�V���t�B�[���h�̏I������
	UninitMeshField();

	// ���f���z�u�̏I������
	UninitModelSet();

	// �`���[�g���A����ʔw�i�̏I������
	UninitTutorialBg();
}

//-----------------------------------------------------------------
// �`���[�g���A���̍X�V����
//-----------------------------------------------------------------
void UpdateTutorial(void)
{
	// �`���[�g���A����ʔw�i�̍X�V����
	UpdateTutorialBg();

	// ���b�V���t�B�[���h�̍X�V����
	UpdateMeshField();

	// ���f���z�u�̍X�V����
	UpdateModelSet();

	// �ǂ̍X�V����
	UpdateWall();

	UpdateLoadScreen();

	if (GetKeyboardTrigger(KEYINFO_OK) == true)
	{// �Q�[����ʂɑJ��
		SetFade(FADE_OUT, MODE_GAME);
	}
}

//-----------------------------------------------------------------
// �`���[�g���A���̕`�揈��
//-----------------------------------------------------------------
void DrawTutorial(void)
{
	// �`���[�g���A����ʔw�i�̕`�揈��
	DrawTutorialBg();

	// ���b�V���t�B�[���h�̕`�揈��
	DrawMeshField();

	// ���f���z�u�̕`�揈��
	DrawModelSet();

	// �ǂ̕`�揈��
	DrawWall();

	DrawLoadScreen();
}