//-----------------------------------------------------------------
//
// �^�C�g�� (title.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "title.h"
#include "title_bg.h"
#include "titlelogo.h"
#include "texture_set.h"
#include "press_anybutton.h"
#include "sound.h"
#include "setparticle.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "wall.h"
#include "model_set.h"
#include "meshfield.h"
#include "effect.h"

//-----------------------------------------------------------------
// �^�C�g���̏���������
//-----------------------------------------------------------------
HRESULT InitTitle(void)
{
	// �G�t�F�N�g�̏���������
	InitEffect();

	// �e�N�X�`���z�u�̏���������
	InitTextureSet();

	// �{�^���w���̏���������
	InitPressAnyButton();

	// �^�C�g�����S�̏���������
	InitTitlelogo();
	 
	// ���b�V���t�B�[���h�̏���������
	InitMeshField();

	// �ǂ̏���������
	InitWall();

	PlaySound(SOUND_LABEL_TITLE);

	return S_OK;
}

//-----------------------------------------------------------------
// �^�C�g���̏I������
//-----------------------------------------------------------------
void UninitTitle(void)
{
	StopSound();
	// �ǂ̏I������
	UninitWall();

	// ���b�V���t�B�[���h�̏I������
	UninitMeshField();

	// ���f���z�u�̏I������
	UninitModelSet();

	// �^�C�g�����S�̏I������
	UninitTitlelogo();

	// �{�^���w���̏I������
	UninitPressAnyButton();

	// �e�N�X�`���z�u�̏I������
	UninitTextureSet();

	// �G�t�F�N�g�̏I������
	UninitEffect();
}

//-----------------------------------------------------------------
// �^�C�g���̍X�V����
//-----------------------------------------------------------------
void UpdateTitle(void)
{
	// �e�N�X�`���z�u�̍X�V����
	UpdateTextureSet();

	// �{�^���w���̍X�V����
	UpdatePressAnyButton();

	// �^�C�g�����S�̍X�V����
	UpdateTitlelogo();

	// ���b�V���t�B�[���h�̍X�V����
	UpdateMeshField();

	// ���f���z�u�̍X�V����
	UpdateModelSet();

	// �ǂ̍X�V����
	UpdateWall();

	// �G�t�F�N�g�̍X�V����
	UpdateEffect();

	if (GetKeyboardTrigger(KEYINFO_OK) == true)
	{// �L�����Z���N�g��ʂɑJ��
		SetFade(FADE_OUT, MODE_CHARASELECT);
	}

}

//-----------------------------------------------------------------
// �^�C�g���̕`�揈��
//-----------------------------------------------------------------
void DrawTitle(void)
{
	// ���b�V���t�B�[���h�̕`�揈��
	DrawMeshField();

	// ���f���z�u�̕`�揈��
	DrawModelSet();

	// �ǂ̕`�揈��
	DrawWall();

	// �e�N�X�`���z�u�̕`�揈��
	DrawTextureSet();
	
	// �{�^���w���̕`�揈��
	DrawPressAnyButton();

	// �^�C�g�����S�̕`�揈��
	DrawTitlelogo();

	// �G�t�F�N�g�̕`�揈��
	DrawEffect();
}