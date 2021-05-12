//-----------------------------------------------------------------
//
// �L�����Z���N�g (chara_select.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "chara_select.h"
#include "chara_select_frame.h"
#include "chara_select_Image.h"
#include "chara_select_bg.h"
#include "chara_select_none.h"
#include "dicision_chara.h"
#include "chara.h"
#include "player_band.h"
#include "wall.h"
#include "model_set.h"
#include "meshfield.h"
#include "sound.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "LoadSceneData.h"
#include "texture.h"
#include "texture_set.h"

//-----------------------------------------------------------------
// �L�����Z���N�g�̏���������
//-----------------------------------------------------------------
HRESULT InitCharaSelect(void)
{	
	// ���b�V���t�B�[���h�̏���������
	InitMeshField();

	// �ǂ̏���������
	InitWall();

	// �e�N�X�`���z�u�̏���������
	InitTextureSet();

	// �L�����̏���������
	InitCharacter();

	// �L�����Z���N�g�w�i�̏���������
	InitCharaSelectBg();

	// �L�����Z���N�g�m�[���̏���������
	InitCharaSelectNone();

	// �L�����Z���N�g�C���[�W�̏���������
	InitCharaSelectImage();

	// �L�����Z���N�g�g�̏���������
	InitCharaSelectFrame();

	// �v���C���[�o���h�̏���������
	InitPlayerBand();

	// �L��������̏���������
	InitDicisionChara();

	PlaySound(SOUND_LABEL_CHARASELECT);
	return S_OK;
}

//-----------------------------------------------------------------
// �L�����Z���N�g�̏I������
//-----------------------------------------------------------------
void UninitCharaSelect(void)
{
	StopSound();
	// �L��������̏I������
	UninitDicisionChara();

	// �v���C���[�o���h�̏I������
	UninitPlayerBand();

	// �L�����Z���N�g�g�̏I������
	UninitCharaSelectFrame();

	// �L�����Z���N�g�}�[�J�[�̏I������
	UninitCharaSelectImage();

	// �L�����Z���N�g�w�i�̏I������
	UninitCharaSelectNone();

	// �L�����Z���N�g�m�[���̏I������
	UninitCharaSelectBg();

	// �e�N�X�`���z�u�̏I������
	UninitTextureSet();

	// �ǂ̏I������
	UninitWall();

	// ���b�V���t�B�[���h�̏I������
	UninitMeshField();

	// ���f���z�u�̏I������
	UninitModelSet();
}

//-----------------------------------------------------------------
// �L�����Z���N�g�̍X�V����
//-----------------------------------------------------------------
void UpdateCharaSelect(void)
{
	// ���b�V���t�B�[���h�̍X�V����
	UpdateMeshField();

	// ���f���z�u�̍X�V����
	UpdateModelSet();

	// �ǂ̍X�V����
	UpdateWall();

	// �e�N�X�`���z�u�̍X�V����
	UpdateTextureSet();

	// �L�����̍X�V����
	UpdateCharacter();

	// �L�����Z���N�g�w�i�̍X�V����
	UpdateCharaSelectBg();

	// �L�����Z���N�g�m�[���̍X�V����
	UpdateCharaSelectNone();

	// �L�����Z���N�g�}�[�J�[�̍X�V����
	UpdateCharaSelectImage();

	// �L�����Z���N�g�g�̍X�V����
	UpdateCharaSelectFrame();

	// �v���C���[�o���h�̍X�V����
	UpdatePlayerBand();

	// �L��������̍X�V����
	UpdateDicisionChara();
}

//-----------------------------------------------------------------
// �L�����Z���N�g�̕`�揈��
//-----------------------------------------------------------------
void DrawCharaSelect(void)
{
	// ���b�V���t�B�[���h�̕`�揈��
	DrawMeshField();

	// ���f���z�u�̕`�揈��
	DrawModelSet();

	// �ǂ̕`�揈��
	DrawWall();

	// �L�����̕`�揈��
	DrawCharacter();

	// �L�����Z���N�g�w�i�̕`�揈��
	DrawCharaSelectBg();

	// �v���C���[�o���h�̕`�揈��
	DrawPlayerBand();

	// �L�����Z���N�g�m�[���̕`�揈��
	DrawCharaSelectNone();

	// �e�N�X�`���z�u�̕`�揈��
	DrawTextureSet();

	// �L�����Z���N�g�C���[�W�̕`�揈��
	DrawCharaSelectImage();

	// �L�����Z���N�g�g�̕`�揈��
	DrawCharaSelectFrame();

	// �L��������̕`�揈��
	DrawDicisionChara();
}