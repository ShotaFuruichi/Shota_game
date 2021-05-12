//-----------------------------------------------------------------
//
// ���U���g (result.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "result.h"
#include "result_logo.h"
#include "meshfield.h"
#include "player.h"
#include "wall.h"
#include "shadow.h"
#include "model_set.h"
#include "setparticle.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "sound.h"
#include "select_mode.h"

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
int g_nSkipCnt;					// ���U���g����^�C�g���ɑJ�ڂł���܂ł̃J�E���g

//-----------------------------------------------------------------
// ���U���g�̏���������
//-----------------------------------------------------------------
HRESULT InitResult(void)
{
	// ���b�V���t�B�[���h�̏���������
	InitMeshField();

	// �ǂ̏���������
	InitWall();

	// �v���C���[�̏���������
	InitPlayer();

	// ���U���g���S�̏���������
	InitResultLogo();

	// �Z���N�g���[�h�̏���������
	InitSelectMode();

	PlaySound(SOUND_LABEL_RESULT);
	return S_OK;
}

//-----------------------------------------------------------------
// ���U���g�̏I������
//-----------------------------------------------------------------
void UninitResult(void)
{
	StopSound();
	// �Z���N�g���[�h�̏I������
	UninitSelectMode();

	// ���U���g���S�̏I������
	UninitResultLogo();

	// �v���C���[�̏I������
	UninitPlayer();

	// �ǂ̏I������
	UninitWall();

	// ���b�V���t�B�[���h�̏I������
	UninitMeshField();

	// ���f���z�u�̏I������
	UninitModelSet();
}

//-----------------------------------------------------------------
// ���U���g�̍X�V����
//-----------------------------------------------------------------
void UpdateResult(void)
{
	// ���b�V���t�B�[���h�̍X�V����
	UpdateMeshField();

	// ���f���z�u�̍X�V����
	UpdateModelSet();

	// �ǂ̍X�V����
	UpdateWall();

	// �v���C���[�̍X�V����
	UpdatePlayer();

	// ���U���g���S�̍X�V����
	UpdateResultLogo();

	// �Z���N�g���[�h�̍X�V����
	UpdateSelectMode();
}

//-----------------------------------------------------------------
// ���U���g�̕`�揈��
//-----------------------------------------------------------------
void DrawResult(void)
{
	// ���b�V���t�B�[���h�̕`�揈��
	DrawMeshField();

	// ���f���z�u�̕`�揈��
	DrawModelSet();

	// �ǂ̕`�揈��
	DrawWall();

	// �v���C���[�̕`�揈��
	DrawPlayer();

	// ���U���g���S�̕`�揈��
	DrawResultLogo();

	// �Z���N�g���[�h�̕`�揈��
	DrawSelectMode();
}