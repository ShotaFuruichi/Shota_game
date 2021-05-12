//-----------------------------------------------------------------
//
// �Q�[�����C�� (game.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "game.h"
#include "meshfield.h"
#include "player.h"
#include "wall.h"
#include "ui.h"
#include "shadow.h"
#include "model_set.h"
#include "effect.h"
#include "setparticle.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "timer.h"
#include "Bomb.h"
#include "pause.h"
#include "finish_game.h"
#include "sound.h"

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
bool g_bPause = false;
int g_ResultCount;

//-----------------------------------------------------------------
// �x�[�X�̏���������
//-----------------------------------------------------------------
HRESULT InitGame(void)
{
	g_ResultCount = 0;

	// �e�̏���������
	InitShadow();

	// �v���C���[�̏���������
	InitPlayer();

	// ���b�V���t�B�[���h�̏���������
	InitMeshField();

	// �ǂ̏���������
	InitWall();

	// �{���̏���������
	InitBomb();

	// �G�t�F�N�g�̏���������
	InitEffect();

	// UI�̏���������
	InitUi();

	// �|�[�Y��ʂ̏���������
	InitPause();

	PlaySound(SOUND_LABEL_GAME);

	return S_OK;
}

//-----------------------------------------------------------------
// �x�[�X�̏I������
//-----------------------------------------------------------------
void UninitGame(void)
{
	StopSound();
	// �|�[�Y��ʂ̏I������
	UninitPause();

	// UI�̏I������
	UninitUi();

	// �G�t�F�N�g�̏I������
	UninitEffect();

	// �{���̏I������
	UninitBomb();

	// �ǂ̏I������
	UninitWall();

	// ���b�V���t�B�[���h�̏I������
	UninitMeshField();

	// ���f���z�u�̏I������
	UninitModelSet();

	// �e�̏I������
	UninitShadow();

	// �v���C���[�̏I������
	UninitPlayer();
}

//-----------------------------------------------------------------
// �x�[�X�̍X�V����
//-----------------------------------------------------------------
void UpdateGame(void)
{
	// �ϐ��錾
	int nTimer = GetTimer();
	bool bFinish = GetFinishGame();

	if ((GetKeyboardTrigger(KEYINFO_PAUSE) == true || GetJoypadTrigger(PLAYER_1,JPINFO_PAUSE)) && nTimer < 60)
	{
		g_bPause = g_bPause ? false : true;
	}
	if (g_bPause == false)
	{
		// ���b�V���t�B�[���h�̍X�V����
		UpdateMeshField();

		// ���f���z�u�̍X�V����
		UpdateModelSet();

		// �ǂ̍X�V����
		UpdateWall();

		// �v���C���[�̍X�V����
		UpdatePlayer();

		// �e�̍X�V����
		UpdateShadow();

		// �G�t�F�N�g�̍X�V����
		UpdateEffect();

		if (bFinish != true)
		{
			// �{���̍X�V����
			UpdateBomb();
		}
	} 
	else
	{
		// �|�[�Y��ʂ̍X�V����
		UpdatePause();
	}
	if (g_bPause == false)
	{
		// UI�̍X�V����
		UpdateUi();
	}

	if (bFinish == true)
	{
		if (g_ResultCount == 60)
		{
			// ��ʃ��[�h�̏���������
			SetFade(FADE_OUT, MODE_RESULT);
		}
		g_ResultCount++;
	}
}

//-----------------------------------------------------------------
// �x�[�X�̕`�揈��
//-----------------------------------------------------------------
void DrawGame(void)
{
	// ���b�V���t�B�[���h�̕`�揈��
	DrawMeshField();

	// ���f���z�u�̕`�揈��
	DrawModelSet();

	// �v���C���[�̕`�揈��
	DrawPlayer();

	// �ǂ̕`�揈��
	DrawWall();

	// �{���̕`�揈��
	DrawBomb();
	DrawBombWarnMark();

	// �G�t�F�N�g�̕`�揈��
	DrawEffect();

	// �e�̕`�揈��
	DrawShadow();

	// UI�̕`�揈��
	DrawUi();

	if (g_bPause == true)
	{
		// �|�[�Y��ʂ̕`�揈��
		DrawPause();
	}
}

//-------------------------------------------------------------------
// �|�[�Y�̈ڂ�ւ��
//-------------------------------------------------------------------
void SetPause(bool bPause)
{
	g_bPause = bPause;
}