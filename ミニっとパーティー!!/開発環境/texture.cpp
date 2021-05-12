//-----------------------------------------------------------------
//
//	�e�N�X�`���̓ǂݍ��� (texture.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "texture.h"

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
Texture g_Texture;			// �e�N�X�`�����
Texture g_UITexture;			// UI�e�N�X�`�����

//-----------------------------------------------------------------
//�e�N�X�`���̓ǂݍ���
//-----------------------------------------------------------------
void LoadTexture(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n���A������
	pDevice = GetDevice();

	for (int nCntTexture = 0; nCntTexture < g_Texture.nNumTexture; nCntTexture++)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, &g_Texture.TextureInfo[nCntTexture].aTexcharName[0], &g_Texture.TextureInfo[nCntTexture].pTexture);
	}

	for (int nCntUITexture = 0; nCntUITexture < g_UITexture.nNumTexture; nCntUITexture++)
	{
		// UI�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, &g_UITexture.TextureInfo[nCntUITexture].aTexcharName[0], &g_UITexture.TextureInfo[nCntUITexture].pTexture);
	}
}

//-----------------------------------------------------------------
//�e�N�X�`���̉��
//-----------------------------------------------------------------
void ReleaseTexture(void)
{
	// �e�N�X�`���̉��
	for (int nCntTexture = 0; nCntTexture < g_Texture.nNumTexture; nCntTexture++)
	{
		if (g_Texture.TextureInfo[nCntTexture].pTexture != NULL)
		{
			g_Texture.TextureInfo[nCntTexture].pTexture->Release();
			g_Texture.TextureInfo[nCntTexture].pTexture = NULL;
		}
	}

	// UI�e�N�X�`���̉��
	for (int nCntUITexture = 0; nCntUITexture < g_UITexture.nNumTexture; nCntUITexture++)
	{
		if (g_UITexture.TextureInfo[nCntUITexture].pTexture != NULL)
		{
			g_UITexture.TextureInfo[nCntUITexture].pTexture->Release();
			g_UITexture.TextureInfo[nCntUITexture].pTexture = NULL;
		}
	}
}

//-----------------------------------------------------------------
// �e�N�X�`�����̎擾
//-----------------------------------------------------------------
Texture *GetTexture(void)
{
	return &g_Texture;
}

//-----------------------------------------------------------------
// �e�N�X�`�����̎擾
//-----------------------------------------------------------------
Texture *GetUITexture(void)
{
	return &g_UITexture;
}