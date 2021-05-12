//-------------------------------------------------------------------
//
// �L�����w�b�_�[ (chara.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _CHARA_H_
#define _CHARA_H_

#include "main.h"
#include "motion.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define MAX_CHARA		(5)		// �L�����̍ő吔
#define MAX_FILENAME	(64)		// X�t�@�C���l�[���̍ő啶����

//-------------------------------------------------------------------
// �\���̂̒�`
//-------------------------------------------------------------------
typedef struct
{
	LPD3DXMESH pMesh;				// ���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;			// �}�e���A��(�ގ����)�ւ̃|�C���^
	DWORD nNumMat = 0;				// �}�e���A���̐�
	LPDIRECT3DTEXTURE9 pTexture[16] = {};	// �e�N�X�`���ւ̃|�C���^
	char aFileName[MAX_FILENAME];	// �t�@�C���̖��O
	D3DXVECTOR3 pos;				// ���S���W
	D3DXVECTOR3 rot;				// ��]�p
	D3DXMATRIX mtxWorld;			// ���[���h�}�g���b�N�X
	int nIdxModelParent;			// �e���f���̃C���f�b�N�X
	D3DXVECTOR3 minVecModel;		// ���_�̍ŏ��l
	D3DXVECTOR3 maxVecModel;		// ���_�̍ő�l
}CharacterModel;

typedef struct
{
	D3DXVECTOR3 pos;							// ���S���W
	D3DXVECTOR3 posOld;							// �O�̒��S���W
	D3DXVECTOR3 rot;							// ���݂̌���
	D3DXVECTOR3 rotDest;						// �ړI�̌���
	D3DXMATRIX mtxWorld;						// ���[���h�}�g���b�N�X
	CharacterModel aModel[20];					// ���f��
	int nNumModel;								// ���f����
	D3DXVECTOR3 minVecPlayer;					// ���_�̍ŏ��l
	D3DXVECTOR3 maxVecPlayer;					// ���_�̍ő�l
	float fHeight;								// �����蔻��̍���
	float fRadius;								// �����蔻��̔��a
	int nIdx;									// ���Ԗڂ̉e��
	MOTION_INFO aMotionInfo[MOTYONTYPE_MAX];	// ���[�V�������
	int nNumMotion;								// ���[�V������
	MOTIONTYPE MotionType;						// ���[�V�����^�C�v
	bool bLoopMotion;							// ���[�v���邩�ǂ���
	int nNumKey;								// �L�[��
	int nKey;									// �L�[No.
	int nCounterMotion;							// ���[�V�����J�E���^
	bool bFall;									// ���������ǂ���
}CharacterInfo;

typedef struct
{
	CharacterInfo characterInfo[MAX_CHARA];		// �L�����N�^�[���
	int nNumCharacter;							// ����ǂݍ��ރL�����N�^�[�̑���
	char aTextName[MAX_CHARA][256];				// �e�L�X�g�l�[���ǂݍ��ݗp
}Character;

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
HRESULT InitCharacter(void);				// �L�����̏���������
void UninitCharacter(void);					// �L�����̏I������
void UpdateCharacter(void);					// �L�����̍X�V����
void DrawCharacter(void);					// �L�����̕`�揈��

Character *GetCharacter(void);				// �L�������̎擾

void CharacterMotion(int Character);			// �v���C�����[�V�����̐ݒ�
void SetCharaMotion(int Character, MOTIONTYPE motiontype, bool bBlend, int nFrameBlend);	// ���[�V�����̐ݒ�

#endif