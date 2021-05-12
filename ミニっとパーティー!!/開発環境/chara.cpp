//-----------------------------------------------------------------
//
// �v���C���[ (player.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "chara.h"
#include "motion.h"
#include "camera.h"
#include "input.h"
#include "gamepad.h"
#include "sound.h"
#include "chara_select_frame.h"
#include "player.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MOVE_MODEL			(2.0f)
#define JUMP_PLAYER			(11.0f)
#define PI_QUARTER			(D3DX_PI / 4.0f)
#define GRAVITY				(0.5f)		// �d��

#define LENGTH				(8.0f)
#define MAX_DISPLAY_CHARA	(4)				// �v���C���[�̑���

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
Character g_chara;						// �L�������

//-----------------------------------------------------------------
// �L�����̏���������
//-----------------------------------------------------------------
HRESULT InitCharacter(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntChara = 0; nCntChara < MAX_CHARA; nCntChara++)
	{
		// �v���C���[���̏�����
		g_chara.characterInfo[nCntChara].pos = D3DXVECTOR3(0.0, 0.0f, 0.0f);
		g_chara.characterInfo[nCntChara].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_chara.characterInfo[nCntChara].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_chara.characterInfo[nCntChara].MotionType = MOTIONTYPE_NEUTRAL;
		g_chara.characterInfo[nCntChara].nCounterMotion = 1;
		g_chara.characterInfo[nCntChara].nKey = 0;
		g_chara.characterInfo[nCntChara].bLoopMotion = g_chara.characterInfo[nCntChara].aMotionInfo[g_chara.characterInfo[nCntChara].MotionType].bLoop;
		g_chara.characterInfo[nCntChara].nNumKey = g_chara.characterInfo[nCntChara].aMotionInfo[g_chara.characterInfo[nCntChara].MotionType].nNumKey;

		// �v���C���[�̃p�[�c�ݒ�
		for (int nCntModel = 0; nCntModel < g_chara.characterInfo[nCntChara].nNumModel; nCntModel++)
		{
			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(g_chara.characterInfo[nCntChara].aModel[nCntModel].aFileName,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_chara.characterInfo[nCntChara].aModel[nCntModel].pBuffMat,
				NULL,
				&g_chara.characterInfo[nCntChara].aModel[nCntModel].nNumMat,
				&g_chara.characterInfo[nCntChara].aModel[nCntModel].pMesh)))
			{
				return E_FAIL;
			}

			// �ϐ��錾
			D3DXMATERIAL *pMat;		// �}�e���A���f�[�^�ւ̃|�C���^
			LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�ւ̃|�C���^

			// �ϐ��̎󂯓n��
			pDevice = GetDevice();

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_chara.characterInfo[nCntChara].aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_chara.characterInfo[nCntChara].aModel[nCntModel].nNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					// �e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_chara.characterInfo[nCntChara].aModel[nCntModel].pTexture[nCntMat]);
				}
			}
		}
	}

	return S_OK;
}

//-----------------------------------------------------------------
// �L�����̏I������
//-----------------------------------------------------------------
void UninitCharacter(void)
{
	for (int nCntChara = 0; nCntChara < MAX_CHARA; nCntChara++)
	{
		for (int nCntModel = 0; nCntModel < g_chara.characterInfo[nCntChara].nNumModel; nCntModel++)
		{
			// �}�e���A�����̊J��
			if (g_chara.characterInfo[nCntChara].aModel[nCntModel].pBuffMat != NULL)
			{
				g_chara.characterInfo[nCntChara].aModel[nCntModel].pBuffMat->Release();
				g_chara.characterInfo[nCntChara].aModel[nCntModel].pBuffMat = NULL;
			}

			// ���b�V�����̊J��
			if (g_chara.characterInfo[nCntChara].aModel[nCntModel].pMesh != NULL)
			{
				g_chara.characterInfo[nCntChara].aModel[nCntModel].pMesh->Release();
				g_chara.characterInfo[nCntChara].aModel[nCntModel].pMesh = NULL;
			}
		}
	}
}

//-----------------------------------------------------------------
// �L�����̍X�V����
//-----------------------------------------------------------------
void UpdateCharacter(void)
{
	for (int nCntChara = 0; nCntChara < MAX_CHARA; nCntChara++)
	{
		// �v���C���[���[�V����
		CharacterMotion(nCntChara);
	}
}

//-----------------------------------------------------------------
// �L�����̕`�揈��
//-----------------------------------------------------------------
void DrawCharacter(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				// �}�e���A���f�[�^�ւ̃|�C���^

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();
	Camera *pCamera = GetCamera();

	// �L�����Z���N�g�C���[�W���̎擾
	CharaSelectFrame *pCharaSelectFrame = GetCharaSelectFrame();

	for (int nCntChara = 0; nCntChara < MAX_DISPLAY_CHARA; nCntChara++,pCharaSelectFrame++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_chara.characterInfo[pCharaSelectFrame->nNumChara].mtxWorld);

		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_chara.characterInfo[pCharaSelectFrame->nNumChara].rot.y, g_chara.characterInfo[pCharaSelectFrame->nNumChara].rot.x, g_chara.characterInfo[pCharaSelectFrame->nNumChara].rot.z);
		D3DXMatrixMultiply(&g_chara.characterInfo[pCharaSelectFrame->nNumChara].mtxWorld, &g_chara.characterInfo[pCharaSelectFrame->nNumChara].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, pCamera->CameraInfo[nCntChara].posV.x, g_chara.characterInfo[pCharaSelectFrame->nNumChara].pos.y, g_chara.characterInfo[pCharaSelectFrame->nNumChara].pos.z);
		D3DXMatrixMultiply(&g_chara.characterInfo[pCharaSelectFrame->nNumChara].mtxWorld, &g_chara.characterInfo[pCharaSelectFrame->nNumChara].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_chara.characterInfo[pCharaSelectFrame->nNumChara].mtxWorld);

		for (int nCntModel = 0; nCntModel < g_chara.characterInfo[pCharaSelectFrame->nNumChara].nNumModel; nCntModel++)
		{
			// �ϐ��錾
			D3DXMATRIX mtxRotModel, mtxTransModel;		// �v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent;						// �e�̃}�g���b�N�X

			// �e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].mtxWorld);

			// �e�p�[�c�̌���
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].rot.y, g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].rot.x, g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].mtxWorld, &g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].mtxWorld, &mtxRotModel);

			// �e�p�[�c�̈ʒu
			D3DXMatrixTranslation(&mtxTransModel, g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].pos.x, g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].pos.y, g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].mtxWorld, &g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].mtxWorld, &mtxTransModel);

			// �e�p�[�c�̐e�̃}�g���b�N�X��ݒ�
			if (g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].nIdxModelParent != -1)
			{
				mtxParent = g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{
				mtxParent = g_chara.characterInfo[pCharaSelectFrame->nNumChara].mtxWorld;
			}
			// �Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].mtxWorld,
				&g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].mtxWorld,
				&mtxParent);

			// �e�p�[�c�̃}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].pTexture[nCntMat]);

				// ���f��(�p�[�c)�̕`��
				g_chara.characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}
			// �ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//-----------------------------------------------------------------
// �L�������̎擾
//-----------------------------------------------------------------
Character *GetCharacter(void)
{
	return &g_chara;
}

//-----------------------------------------------------------------
// �L�������[�V�����̐ݒ�
//-----------------------------------------------------------------
void CharacterMotion(int nCntCharacter)
{
	// �ϐ��錾
	CharacterInfo *pCharacterInfo = &g_chara.characterInfo[0];
	pCharacterInfo += nCntCharacter;	// ���Ԗڂ̃v���C���[��
	KEY *pKey;				// �L�[���
	KEY *pKeyNext;			// ���̃L�[���
	float fPosX;
	float fPosY;
	float fPosZ;
	float fRotX;
	float fRotY;
	float fRotZ;

	for (int nCntModel = 0; nCntModel < pCharacterInfo->nNumModel; nCntModel++)
	{
		// �L�[�̊m��
		pKey = &pCharacterInfo->aMotionInfo[pCharacterInfo->MotionType].aKeyInfo[pCharacterInfo->nKey].aKey[nCntModel];
		pKeyNext = &pCharacterInfo->aMotionInfo[pCharacterInfo->MotionType].aKeyInfo[(pCharacterInfo->nKey + 1) % pCharacterInfo->nNumKey].aKey[nCntModel];

		// �����̊m��
		float fDiffMoitonPosX = pKeyNext->fPosX - pKey->fPosX;
		float fDiffMoitonPosY = pKeyNext->fPosY - pKey->fPosY;
		float fDiffMoitonPosZ = pKeyNext->fPosZ - pKey->fPosZ;
		float fDiffMoitonRotX = pKeyNext->fRotX - pKey->fRotX;
		float fDiffMoitonRotY = pKeyNext->fRotY - pKey->fRotY;
		float fDiffMoitonRotZ = pKeyNext->fRotZ - pKey->fRotZ;

		// �p�x�̐���
		D3DXVECTOR3(fDiffMoitonRotX, fDiffMoitonRotY, fDiffMoitonRotZ) = AngleCorrection(fDiffMoitonRotX, fDiffMoitonRotY, fDiffMoitonRotZ);

		// ���Βl�̊m��
		float fRateMotion = (float)pCharacterInfo->nCounterMotion / (float)pCharacterInfo->aMotionInfo[pCharacterInfo->MotionType].aKeyInfo[pCharacterInfo->nKey].nFrame;

		// ���[�V�����̈ʒu�ƌ����̊m��
		fPosX = pKey->fPosX + (fDiffMoitonPosX * fRateMotion);
		fPosY = pKey->fPosY + (fDiffMoitonPosY * fRateMotion);
		fPosZ = pKey->fPosZ + (fDiffMoitonPosZ * fRateMotion);
		fRotX = pKey->fRotX + (fDiffMoitonRotX * fRateMotion);
		fRotY = pKey->fRotY + (fDiffMoitonRotY * fRateMotion);
		fRotZ = pKey->fRotZ + (fDiffMoitonRotZ * fRateMotion);

		// �p�x�̐���
		D3DXVECTOR3(fRotX, fRotY, fRotZ) = AngleCorrection(fRotX, fRotY, fRotZ);

		if ((pCharacterInfo->nKey) == (pCharacterInfo->nNumKey - 1) && pCharacterInfo->bLoopMotion == false)
		{
			break;
		}

		// �ʒu�ƌ����̐ݒ�
		pCharacterInfo->aModel[nCntModel].pos.x = fPosX;
		pCharacterInfo->aModel[nCntModel].pos.y = fPosY;
		pCharacterInfo->aModel[nCntModel].pos.z = fPosZ;
		pCharacterInfo->aModel[nCntModel].rot.x = fRotX;
		pCharacterInfo->aModel[nCntModel].rot.y = fRotY;
		pCharacterInfo->aModel[nCntModel].rot.z = fRotZ;
	}

	if (pCharacterInfo->nCounterMotion > pCharacterInfo->aMotionInfo[pCharacterInfo->MotionType].aKeyInfo[pCharacterInfo->nKey].nFrame)
	{
		// ���[�V�����J�E���^�̏�����
		pCharacterInfo->nCounterMotion = 0;

		// �L�[�̍X�V
		pCharacterInfo->nKey++;

		// �L�[�̊m��
		pCharacterInfo->nKey = pCharacterInfo->nKey % pCharacterInfo->nNumKey;
	}
	// ���[�V�����J�E���^�̍X�V
	pCharacterInfo->nCounterMotion++;
}

//-----------------------------------------------------------------
// ���[�V�����̐ݒ�
//-----------------------------------------------------------------
void SetCharaMotion(int nCntCharacter, MOTIONTYPE motiontype, bool bBlend, int nFrameBlend)
{
	if (bBlend == false && g_chara.characterInfo[nCntCharacter].MotionType != motiontype)
	{
		// ���[�V�����̊m��
		g_chara.characterInfo[nCntCharacter].MotionType = motiontype;

		// ���[�V�����J�E���^��������
		g_chara.characterInfo[nCntCharacter].nCounterMotion = 0;

		// ���݂̃L�[��������
		g_chara.characterInfo[nCntCharacter].nKey = 0;

		// ���[�v���邩�ǂ���
		g_chara.characterInfo[nCntCharacter].bLoopMotion = g_chara.characterInfo[nCntCharacter].aMotionInfo[g_chara.characterInfo[nCntCharacter].MotionType].bLoop;

		// �L�[���̊m��
		g_chara.characterInfo[nCntCharacter].nNumKey = g_chara.characterInfo[nCntCharacter].aMotionInfo[g_chara.characterInfo[nCntCharacter].MotionType].nNumKey;
	}
}