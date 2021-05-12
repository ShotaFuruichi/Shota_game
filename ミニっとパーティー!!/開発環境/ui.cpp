//-----------------------------------------------------------------
//
// UI�w�i (ui.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "ui.h"
#include "timer.h"
#include "timer_bg.h"
#include "player_marker.h"
#include "count_down.h"
#include "finish_game.h"

//-----------------------------------------------------------------
// UI�̏���������
//-----------------------------------------------------------------
void InitUi(void)
{
	// �^�C�}�[�̏���������
	InitTimer();

	// �^�C�}�[�w�i�̏���������
	InitTimerBg();

	// �v���C���[�}�[�J�[�̏���������
	InitPlayerMarker();

	// �J�E���g�_�E���̏���������
	InitCountDown();

	// �t�B�j�b�V���Q�[���̏���������
	InitFinishGame();
}

//-----------------------------------------------------------------
// UI�̏I������
//-----------------------------------------------------------------
void UninitUi(void)
{
	// �t�B�j�b�V���Q�[���̏I������
	UninitFinishGame();

	// �J�E���g�_�E���̏I������
	UninitCountDown();

	// �v���C���[�}�[�J�[�̏I������
	UninitPlayerMarker();

	// �^�C�}�[�w�i�̏I������
	UninitTimerBg();

	// �^�C�}�[�̏I������
	UninitTimer();
}

//-----------------------------------------------------------------
// UI�̍X�V����
//-----------------------------------------------------------------
void UpdateUi(void)
{
	// �ϐ��錾
	int nCountDown = GetCountDown();
	bool bFinish = GetFinishGame();

	if (nCountDown == 0 && bFinish == false)
	{
		// �^�C�}�[�̍X�V����
		UpdateTimer();
	}

	// �^�C�}�[�w�i�̍X�V����
	UpdateTimerBg();

	// �v���C���[�}�[�J�[�̍X�V����
	UpdatePlayerMarker();

	// �J�E���g�_�E���̍X�V����
	UpdateCountDown();

	// �t�B�j�b�V���Q�[���̍X�V����
	UpdateFinishGame();
}


//-----------------------------------------------------------------
// UI�̕`�揈��
//-----------------------------------------------------------------
void DrawUi(void)
{
	// �v���C���[�}�[�J�[�̕`�揈��
	DrawPlayerMarker();

	// �^�C�}�[�w�i�̕`�揈��
	DrawTimerBg();

	// �^�C�}�[�̕`�揈��
	DrawTimer();

	// �J�E���g�_�E���̕`�揈��
	DrawCountDown();

	// �t�B�j�b�V���Q�[���̕`�揈��
	DrawFinishGame();
}