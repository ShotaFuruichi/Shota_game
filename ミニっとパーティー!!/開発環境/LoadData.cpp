//-----------------------------------------------------------------
//
//	�e�N�X�`���̓ǂݍ��� (texture.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "LoadData.h"
#include "LoadCharacterData.h"
#include "LoadSceneData.h"
#include "LoadUIData.h"
#include "texture.h"
#include "texture_set.h"
#include "chara.h"

//-----------------------------------------------------------------
// ���̓ǂݍ���
//-----------------------------------------------------------------
void InitLoadData(void)
{
	// �V�[�����̓ǂݍ���
	LoadSceneInfoText();

	// �L�������̓ǂݍ���
	LoadCharacterData();

	// �L�����̏���������
	InitCharacter();
}

//-----------------------------------------------------------------
// �V�[�����̍X�V
//-----------------------------------------------------------------
void UpdateData(void)
{
	// �e�V�[���̂Ł[���ǂݍ���
	LoadSceneData();

	// UI�f�[�^�̓ǂݍ���
	LoadUISetData();

	// �e�N�X�`���̓ǂݍ���
	LoadTexture();
}

//-----------------------------------------------------------------
// �f�[�^�̉��
//-----------------------------------------------------------------
void ReleaseData(void)
{
	// �e�N�X�`���̉��
	ReleaseTexture();
}