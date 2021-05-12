//-----------------------------------------------------------------
//
// �v���C���[�o���h (player_band.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "player_band.h"

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerBand = NULL;				// �v���C���[�o���h�̒��_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePlayerBand[MAX_PLAYERBAND] = {};		// �v���C���[�o���h�̒��_�o�b�t�@�̃|�C���^
PlayerBand g_PlayerBand[DISPLAY_PLAYERBAND];							// �v���C���[�o���h���

//-----------------------------------------------------------------
// �v���C���[�o���h�̏���������
//-----------------------------------------------------------------
HRESULT InitPlayerBand(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n���A������
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/band_1P.png", &g_pTexturePlayerBand[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/band_2P.png", &g_pTexturePlayerBand[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/band_3P.png", &g_pTexturePlayerBand[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/band_4P.png", &g_pTexturePlayerBand[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/band_COM.png", &g_pTexturePlayerBand[4]);

	// �ϐ��̏�����
	for (int nCntPlayerBand = 0; nCntPlayerBand < DISPLAY_PLAYERBAND; nCntPlayerBand++)
	{
		g_PlayerBand[nCntPlayerBand].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		g_PlayerBand[nCntPlayerBand].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_PlayerBand[nCntPlayerBand].fWidth = 0.0f;
		g_PlayerBand[nCntPlayerBand].fHeight = 0.0f;
		g_PlayerBand[nCntPlayerBand].nTexType = nCntPlayerBand;
		g_PlayerBand[nCntPlayerBand].bUse = true;
	}

	// �v���C���[�o���h���̓ǂݍ���
	LoadPlayerBandData();

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * DISPLAY_PLAYERBAND,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayerBand,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayerBand->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPlayerBand = 0; nCntPlayerBand < DISPLAY_PLAYERBAND; nCntPlayerBand++)
	{
		// ���_���W�̐ݒ�
		SetVertexPlayerBand(nCntPlayerBand);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���̍X�V
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayerBand->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �v���C���[�o���h�̏I������
//-----------------------------------------------------------------
void UninitPlayerBand(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPlayerBand != NULL)
	{
		g_pVtxBuffPlayerBand->Release();
		g_pVtxBuffPlayerBand = NULL;
	}

	for (int nCntTexture = 0; nCntTexture < MAX_PLAYERBAND; nCntTexture++)
	{
		if (g_pTexturePlayerBand[nCntTexture] != NULL)
		{
			g_pTexturePlayerBand[nCntTexture]->Release();
			g_pTexturePlayerBand[nCntTexture] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// �v���C���[�o���h�̍X�V����
//-----------------------------------------------------------------
void UpdatePlayerBand(void)
{
	
}

//-----------------------------------------------------------------
// �v���C���[�o���h�̕`�揈��
//-----------------------------------------------------------------
void DrawPlayerBand(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayerBand, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntTexture = 0; nCntTexture < DISPLAY_PLAYERBAND; nCntTexture++)
	{
		if (g_PlayerBand[nCntTexture].bUse == true)
		{
			pDevice->SetTexture(0, g_pTexturePlayerBand[g_PlayerBand[nCntTexture].nTexType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexture * 4, 2);
		}
	}
}

//-----------------------------------------------------------------
// ���_���W�̐ݒ�
//-----------------------------------------------------------------
void SetVertexPlayerBand(int nIdx)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayerBand->Lock(0, 0, (void**)&pVtx, 0);

	// ���Ԗڂ�
	pVtx += nIdx * 4;

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_PlayerBand[nIdx].pos.x - g_PlayerBand[nIdx].fWidth / 2.0f, g_PlayerBand[nIdx].pos.y + g_PlayerBand[nIdx].fHeight / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_PlayerBand[nIdx].pos.x - g_PlayerBand[nIdx].fWidth / 2.0f, g_PlayerBand[nIdx].pos.y - g_PlayerBand[nIdx].fHeight / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_PlayerBand[nIdx].pos.x + g_PlayerBand[nIdx].fWidth / 2.0f, g_PlayerBand[nIdx].pos.y + g_PlayerBand[nIdx].fHeight / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_PlayerBand[nIdx].pos.x + g_PlayerBand[nIdx].fWidth / 2.0f, g_PlayerBand[nIdx].pos.y - g_PlayerBand[nIdx].fHeight / 2.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = g_PlayerBand[nIdx].col;
	pVtx[1].col = g_PlayerBand[nIdx].col;
	pVtx[2].col = g_PlayerBand[nIdx].col;
	pVtx[3].col = g_PlayerBand[nIdx].col;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayerBand->Unlock();
}

//-----------------------------------------------------------------
// �v���C���[�o���h���̎擾
//-----------------------------------------------------------------
PlayerBand *GetPlayerBand(void)
{
	return &g_PlayerBand[0];
}

//-----------------------------------------------------------------
// �v���C���[�o���h���̓ǂݍ���
//-----------------------------------------------------------------
void LoadPlayerBandData(void)
{
	// �v���C���[�o���h���̎擾
	PlayerBand *pPlayerBand = &g_PlayerBand[0];

	// FILE�^�̃|�C���^�֐�
	FILE *pFile;

	// �t�@�C�����J��
	pFile = fopen("data/TEXT/player_band.txt", "r");

	// �ϐ��錾
	bool bGetScript = false;
	bool bPlayerBandSet = false;

	char aLine[128];
	char aText[128];
	int nCntPlayerBand = 0;

	if (pFile != NULL)
	{
		// SCRIPT��T��
		while (fgets(aLine, 128, pFile) != NULL)
		{
			fscanf(pFile, "%s", &aText[0]);

			// SCRIPT���������炻��ȍ~��ǂݍ���
			if (strcmp(&aText[0], "SCRIPT") == 0)
			{
				bGetScript = true;
			}

			if (bGetScript == true)
			{
				// �v���C���[�̃��f�����̓ǂݍ���
				// PLAYERBANDSET����������v���C���[�o���h����ǂݍ��ދ���^����
				if (strcmp(&aText[0], "PLAYERBANDSET") == 0)
				{
					bPlayerBandSet = true;
				}
				if (bPlayerBandSet == true)
				{
					// POS������������W�����i�[
					if (strcmp(&aText[0], "POS") == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aText[0],
							&pPlayerBand->pos.x,
							&pPlayerBand->pos.y,
							&pPlayerBand->pos.z);
					}
					// SIZE����������T�C�Y�����i�[
					if (strcmp(&aText[0], "SIZE") == 0)
					{
						fscanf(pFile, "%s %f %f", &aText[0],
							&pPlayerBand->fWidth,
							&pPlayerBand->fHeight);
					}
					// END_PLAYERBANDSET����������v���C���[�o���h���̓ǂݍ��݂��I����
					if (strcmp(&aText[0], "END_PLAYERBANDSET") == 0)
					{
						bPlayerBandSet = false;

						// ���̍X�V
						pPlayerBand++;
					}
				}
				// END_SCRIPT����������ǂݍ��݂��I����
				if (strcmp(&aText[0], "END_SCRIPT") == 0)
				{
					break;
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
	}
}