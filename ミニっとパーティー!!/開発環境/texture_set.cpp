//-----------------------------------------------------------------
//
// �e�N�X�`���z�u (texture_set.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "texture_set.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define RATE					(0.05f)						// �������[�g�̑�����
#define MOVE_RATE				(0.001f)					// �������[�g�̑�����

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTextureSet = NULL;				// �w�i�̒��_�o�b�t�@�̃|�C���^
TextureSet g_TextureSet;											// �e�N�X�`���z�u���

//-----------------------------------------------------------------
// �w�i�̏���������
//-----------------------------------------------------------------
HRESULT InitTextureSet(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n���A������
	pDevice = GetDevice();

	// �ϐ��̏�����
	for (int nCntTextureSet = 0; nCntTextureSet < MAX_TEXTURE_SET; nCntTextureSet++)
	{
		g_TextureSet.textureSetInfo[nCntTextureSet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TextureSet.textureSetInfo[nCntTextureSet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TextureSet.textureSetInfo[nCntTextureSet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_TextureSet.textureSetInfo[nCntTextureSet].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
		g_TextureSet.textureSetInfo[nCntTextureSet].fRemoveAlpha = 0.0f;
		g_TextureSet.textureSetInfo[nCntTextureSet].fWidthDest = 0.0f;
		g_TextureSet.textureSetInfo[nCntTextureSet].fHeightDest = 0.0f;
		g_TextureSet.textureSetInfo[nCntTextureSet].fRateWidth = RATE;
		g_TextureSet.textureSetInfo[nCntTextureSet].fRateHeight = RATE;
		g_TextureSet.textureSetInfo[nCntTextureSet].fMoveRateWidth = RATE;
		g_TextureSet.textureSetInfo[nCntTextureSet].fMoveRateHeight = RATE;
		g_TextureSet.textureSetInfo[nCntTextureSet].fWidth = 0.0f;
		g_TextureSet.textureSetInfo[nCntTextureSet].fHeight = 0.0f;
		g_TextureSet.textureSetInfo[nCntTextureSet].fAngle = 0.0f;
		g_TextureSet.textureSetInfo[nCntTextureSet].fLength = 0.0f;
		g_TextureSet.textureSetInfo[nCntTextureSet].bMaxSize = false;
		g_TextureSet.textureSetInfo[nCntTextureSet].bNormalSize = false;
		g_TextureSet.textureSetInfo[nCntTextureSet].nType = -1;
		g_TextureSet.textureSetInfo[nCntTextureSet].nTexType = -1;
		g_TextureSet.textureSetInfo[nCntTextureSet].bUse = false;
	}

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * MAX_TEXTURE_SET,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffTextureSet,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTextureSet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE_SET; nCntTexture++)
	{
		// ���_���W�̐ݒ�
		SetVertexTextureSet(nCntTexture);

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
	g_pVtxBuffTextureSet->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �w�i�̏I������
//-----------------------------------------------------------------
void UninitTextureSet(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTextureSet != NULL)
	{
		g_pVtxBuffTextureSet->Release();
		g_pVtxBuffTextureSet = NULL;
	}
}

//-----------------------------------------------------------------
// �w�i�̍X�V����
//-----------------------------------------------------------------
void UpdateTextureSet(void)
{
	// �e�N�X�`���ݒu���̎擾
	TextureSetInfo *pTextureSetInfo = &g_TextureSet.textureSetInfo[0];

	for (int nCntTextureSet = 0; nCntTextureSet < MAX_TEXTURE_SET; nCntTextureSet++, pTextureSetInfo++)
	{
		if (pTextureSetInfo->bUse == true)
		{
			if (pTextureSetInfo->nType == 0)
			{
				if (pTextureSetInfo->bNormalSize == false)
				{
					if (pTextureSetInfo->bMaxSize == false)
					{
						// �T�C�Y�����̊����X�V
						pTextureSetInfo->fRateWidth -= MOVE_RATE;
						pTextureSetInfo->fRateHeight -= MOVE_RATE;

						// �T�C�Y�����ʍX�V
						pTextureSetInfo->fMoveRateWidth += pTextureSetInfo->fRateWidth;
						pTextureSetInfo->fMoveRateHeight += pTextureSetInfo->fRateHeight;

						// �T�C�Y�X�V
						pTextureSetInfo->fWidth = pTextureSetInfo->fWidthDest * pTextureSetInfo->fMoveRateWidth;
						pTextureSetInfo->fHeight = pTextureSetInfo->fHeightDest * pTextureSetInfo->fMoveRateHeight;

						// 
						if ((pTextureSetInfo->fWidth >= pTextureSetInfo->fWidthDest) && (pTextureSetInfo->fHeight >= pTextureSetInfo->fHeightDest))
						{
							pTextureSetInfo->bMaxSize = true;
						}
					}
					else
					{
						// �T�C�Y�����̊����X�V
						pTextureSetInfo->fRateWidth -= RATE / 30.0f;
						pTextureSetInfo->fRateHeight -= RATE / 30.0f;

						// �T�C�Y�����ʍX�V
						pTextureSetInfo->fMoveRateWidth += pTextureSetInfo->fRateWidth;
						pTextureSetInfo->fMoveRateHeight += pTextureSetInfo->fRateHeight;

						// �T�C�Y�X�V
						pTextureSetInfo->fWidth = pTextureSetInfo->fWidthDest * pTextureSetInfo->fMoveRateWidth;
						pTextureSetInfo->fHeight = pTextureSetInfo->fHeightDest * pTextureSetInfo->fMoveRateHeight;

						if ((pTextureSetInfo->fWidth <= pTextureSetInfo->fWidthDest) && (pTextureSetInfo->fHeight <= pTextureSetInfo->fHeightDest))
						{
							pTextureSetInfo->bNormalSize = true;
						}
					}
				}
			}
			// �p�x�ƑΊp���̒������v�Z
			pTextureSetInfo->fAngle = atan2f(pTextureSetInfo->fWidth / 2.0f, pTextureSetInfo->fHeight / 2.0f);
			pTextureSetInfo->fLength = sqrtf((pTextureSetInfo->fWidth / 2.0f) * (pTextureSetInfo->fWidth / 2.0f) + (pTextureSetInfo->fHeight / 2.0f) * (pTextureSetInfo->fHeight / 2.0f));

			// ���l�̌���
			pTextureSetInfo->col.a -= pTextureSetInfo->fRemoveAlpha;

			// ���l��0.0f��菬�����Ȃ�����g�p��Ԃ�false�ɂ��ă��l������������
			if (pTextureSetInfo->col.a < 0.0f)
			{
				pTextureSetInfo->bUse = false;
				pTextureSetInfo->col.a = 1.0f;
			}
			// ���_���W�̍X�V
			SetVertexTextureSet(nCntTextureSet);
		}
	}
}

//-----------------------------------------------------------------
// �w�i�̕`�揈��
//-----------------------------------------------------------------
void DrawTextureSet(void)
{
	// �e�N�X�`���ݒu���̎擾
	Texture *pTexture = GetUITexture();;

	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTextureSet, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE_SET; nCntTexture++)
	{
		if (g_TextureSet.textureSetInfo[nCntTexture].bUse == true)
		{
			pDevice->SetTexture(0, pTexture->TextureInfo[g_TextureSet.textureSetInfo[nCntTexture].nTexType].pTexture);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexture * 4, 2);
		}
	}
}

//-----------------------------------------------------------------
// ���_���W�̐ݒ�
//-----------------------------------------------------------------
void SetVertexTextureSet(int nCnt)
{
	// �e�N�X�`���z�u���̎擾
	TextureSetInfo *pTextureSetInfo = &g_TextureSet.textureSetInfo[0];

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTextureSet->Lock(0, 0, (void**)&pVtx, 0);

	// ���Ԗڂ�
	pVtx += nCnt * 4;
	pTextureSetInfo += nCnt;

	// ���_���W�̍X�V
	pVtx[0].pos.x = pTextureSetInfo->pos.x + sinf(pTextureSetInfo->rot.z + (D3DX_PI * 0.00f - pTextureSetInfo->fAngle)) * pTextureSetInfo->fLength;
	pVtx[0].pos.y = pTextureSetInfo->pos.y + cosf(pTextureSetInfo->rot.z + (D3DX_PI * 0.00f - pTextureSetInfo->fAngle)) * pTextureSetInfo->fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = pTextureSetInfo->pos.x + sinf(pTextureSetInfo->rot.z + (pTextureSetInfo->fAngle + D3DX_PI * 1.00f)) * pTextureSetInfo->fLength;
	pVtx[1].pos.y = pTextureSetInfo->pos.y + cosf(pTextureSetInfo->rot.z + (pTextureSetInfo->fAngle + D3DX_PI * 1.00f)) * pTextureSetInfo->fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = pTextureSetInfo->pos.x + sinf(pTextureSetInfo->rot.z + (pTextureSetInfo->fAngle + D3DX_PI * 0.00f)) * pTextureSetInfo->fLength;
	pVtx[2].pos.y = pTextureSetInfo->pos.y + cosf(pTextureSetInfo->rot.z + (pTextureSetInfo->fAngle + D3DX_PI * 0.00f)) * pTextureSetInfo->fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = pTextureSetInfo->pos.x + sinf(pTextureSetInfo->rot.z + (D3DX_PI * 1.00f - pTextureSetInfo->fAngle)) * pTextureSetInfo->fLength;
	pVtx[3].pos.y = pTextureSetInfo->pos.y + cosf(pTextureSetInfo->rot.z + (D3DX_PI * 1.00f - pTextureSetInfo->fAngle)) * pTextureSetInfo->fLength;
	pVtx[3].pos.z = 0.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = pTextureSetInfo->col;
	pVtx[1].col = pTextureSetInfo->col;
	pVtx[2].col = pTextureSetInfo->col;
	pVtx[3].col = pTextureSetInfo->col;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTextureSet->Unlock();
}

//-----------------------------------------------------------------
// �e�N�X�`���̐ݒu
//-----------------------------------------------------------------
void SetTexture(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, D3DXCOLOR col,float fRemoveAlpha, 
	float fWidth, float fHeight, float fWidthDest, float fHeightDest ,int type, int textype)
{
	// �e�N�X�`���z�u���̎擾
	TextureSetInfo *pTextureSetInfo = &g_TextureSet.textureSetInfo[0];

	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE_SET; nCntTexture++,pTextureSetInfo++)
	{
		if (pTextureSetInfo->bUse == false)
		{
			// �ʒu���̐ݒ�
			pTextureSetInfo->pos = pos;

			// �����̐ݒ�
			pTextureSetInfo->rot = rot;

			// �ړ��ʂ̐ݒ�
			pTextureSetInfo->move = move;

			// �F�̐ݒ�
			pTextureSetInfo->col = col;

			// ���l�̌����ʂ̐ݒ�
			pTextureSetInfo->fRemoveAlpha = fRemoveAlpha;

			// �ړI�̕��̐ݒ�
			pTextureSetInfo->fWidth = fWidth;

			// �ړI�̍����̐ݒ�
			pTextureSetInfo->fHeight = fHeight;

			// �p�x�ƑΊp���̒������v�Z
			pTextureSetInfo->fAngle = atan2f(pTextureSetInfo->fWidth / 2.0f, pTextureSetInfo->fHeight / 2.0f);
			pTextureSetInfo->fLength = sqrtf((pTextureSetInfo->fWidth / 2.0f) * (pTextureSetInfo->fWidth / 2.0f) + (pTextureSetInfo->fHeight / 2.0f) * (pTextureSetInfo->fHeight / 2.0f));

			// �ړI�̕��̐ݒ�
			pTextureSetInfo->fWidthDest = fWidthDest;

			// �ړI�̍����̐ݒ�
			pTextureSetInfo->fHeightDest = fHeightDest;

			// �G�t�F�N�g�^�C�v�̐ݒ�
			pTextureSetInfo->nType = type;

			// �e�N�X�`���^�C�v�̐ݒ�
			pTextureSetInfo->nTexType = textype;

			// �g�p��Ԃ�true�ɂ���
			pTextureSetInfo->bUse = true;

			break;
		}
	}
}

//-----------------------------------------------------------------
// �e�N�X�`���z�u���̎擾
//-----------------------------------------------------------------
TextureSet *GetTextureSet(void)
{
	return &g_TextureSet;
}