////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �G�t�F�N�g [effect.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/09/07
//
////////////////////////////////////////////////////////////////////////////////
#include "HitEffect.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define HITEFFECT_SIZE (50.0f)			//�G�t�F�N�g�̃T�C�Y
#define ALPHA_DOWN (0.03f)				//���l������

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureHitEffect = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHitEffect = NULL;			//���_�o�b�t�@�ւ̐ݒ�
HITEFFECT g_aHitEffect[MAX_HITEFFECT];							//�G�t�F�N�g�̏��

////////////////////////////////////////////////////////////////////////////////
//�G�t�F�N�g�̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitHitEffect(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_3D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\HitEffect.png", &g_pTextureHitEffect);

	//������
	for (int nCntEffect = 0; nCntEffect < MAX_HITEFFECT; nCntEffect++)
	{
		g_aHitEffect[nCntEffect].pos = D3DXVECTOR3(0, 0, 0.0f);
		g_aHitEffect[nCntEffect].bUse = false;
		g_aHitEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_HITEFFECT, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffHitEffect, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHitEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_HITEFFECT; nCntEffect++)
	{
		//���_���W�̐ݒ�
		SetVertexHitEffect(nCntEffect);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		SetColorHitEffect(nCntEffect);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.143f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.143f, 0.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHitEffect->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�G�t�F�N�g�̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitHitEffect(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffHitEffect != NULL)
	{
		g_pVtxBuffHitEffect->Release();	//�J��
		g_pVtxBuffHitEffect = NULL;		//������
	}
	//�e�N�X�`���̊J��

	if (g_pTextureHitEffect != NULL)
	{
		g_pTextureHitEffect->Release();	//�J��
		g_pTextureHitEffect = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�G�t�F�N�g�̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateHitEffect(void)
{
	//�ϐ��錾
	HITEFFECT *pEffect;
	VERTEX_3D *pVtx;
	static int nCntAnim[MAX_HITEFFECT] = {};
	static int nCnt = 0;
	static float f[MAX_HITEFFECT] = {0.5f};

	pEffect = &g_aHitEffect[0];

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHitEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_HITEFFECT; nCntEffect++, pEffect++)
	{
		if (pEffect->bUse == true)
		{	//�G�t�F�N�g���g�p����Ă���Ƃ�

			//�F�̐ݒ�
			SetColorHitEffect(nCntEffect);


			if (nCntAnim[nCntEffect] < 6)
			{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(nCntAnim[nCntEffect] * (1.0f / 7), f[nCntEffect]);
				pVtx[1].tex = D3DXVECTOR2(nCntAnim[nCntEffect] * (1.0f / 7), (f[nCntEffect] - 0.5f));
				pVtx[2].tex = D3DXVECTOR2((nCntAnim[nCntEffect] + 1) * (1.0f / 7), f[nCntEffect]);
				pVtx[3].tex = D3DXVECTOR2((nCntAnim[nCntEffect] + 1) * (1.0f / 7), (f[nCntEffect] - 0.5f));
			}
			else if (nCntAnim[nCntEffect] >= 6)
			{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2((nCntAnim[nCntEffect] / 2) * (1.0f / 7), f[nCntEffect]);
				pVtx[1].tex = D3DXVECTOR2((nCntAnim[nCntEffect] / 2) * (1.0f / 7), (f[nCntEffect] - 0.5f));
				pVtx[2].tex = D3DXVECTOR2(((nCntAnim[nCntEffect] / 2) + 1) * (1.0f / 7), f[nCntEffect]);
				pVtx[3].tex = D3DXVECTOR2(((nCntAnim[nCntEffect] / 2) + 1) * (1.0f / 7), (f[nCntEffect] - 0.5f));
			}

			nCntAnim[nCntEffect]++;

			if (nCntAnim[nCntEffect] == 6)
			{
				f[nCntEffect] = 1.0f;
			}

			if (nCntAnim[nCntEffect] == 13)
			{
				pEffect->bUse = false;
				f[nCntEffect] = 0.5f;
				nCntAnim[nCntEffect] = 0;
			}
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHitEffect->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�G�t�F�N�g�̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawHitEffect(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	// Z�o�b�t�@��K�p
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���Z������K�p
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���C�e�B���O�̖���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntEffect = 0; nCntEffect < MAX_HITEFFECT; nCntEffect++)
	{
		if (g_aHitEffect[nCntEffect].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aHitEffect[nCntEffect].mtxworld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
#if 0
			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			//�t�s������߂�
			D3DXMatrixInverse(&g_aEffect[nCntEffect].mtxworld, NULL, &mtxView);

			//���s�ړ��̕����͖�������
			g_aEffect[nCntEffect].mtxworld._41 = 0.0f;
			g_aEffect[nCntEffect].mtxworld._42 = 0.0f;
			g_aEffect[nCntEffect].mtxworld._43 = 0.0f;
#endif

#if 1
			g_aHitEffect[nCntEffect].mtxworld._11 = mtxView._11;
			g_aHitEffect[nCntEffect].mtxworld._12 = mtxView._21;
			g_aHitEffect[nCntEffect].mtxworld._13 = mtxView._31;
			g_aHitEffect[nCntEffect].mtxworld._21 = mtxView._12;
			g_aHitEffect[nCntEffect].mtxworld._22 = mtxView._22;
			g_aHitEffect[nCntEffect].mtxworld._23 = mtxView._32;
			g_aHitEffect[nCntEffect].mtxworld._31 = mtxView._13;
			g_aHitEffect[nCntEffect].mtxworld._32 = mtxView._23;
			g_aHitEffect[nCntEffect].mtxworld._33 = mtxView._33;
#endif

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aHitEffect[nCntEffect].pos.x, g_aHitEffect[nCntEffect].pos.y, g_aHitEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_aHitEffect[nCntEffect].mtxworld, &g_aHitEffect[nCntEffect].mtxworld, &mtxTrans);

			//���[���h�}�g���b�N�X
			pDevice->SetTransform(D3DTS_WORLD, &g_aHitEffect[nCntEffect].mtxworld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffHitEffect, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureHitEffect);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}

	//���Z������߂�
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// �f�X�e�B�l�[�V�����̍������@�̐���

																	// Z�o�b�t�@�𖳌�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���C�e�B���O��L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

////////////////////////////////////////////////////////////////////////////////
//�G�t�F�N�g�̃Z�b�g����
////////////////////////////////////////////////////////////////////////////////
void SetHitEffect(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	//�ϐ��錾
	HITEFFECT *pEffect;

	pEffect = &g_aHitEffect[0];

	for (int nCntEffect = 0; nCntEffect < MAX_HITEFFECT; nCntEffect++, pEffect++)
	{
		if (pEffect->bUse == false)
		{	//�G�t�F�N�g���g�p����Ă��Ȃ��Ƃ�

			pEffect->pos = pos;

			pEffect->col = col;

			//�e���g�p����
			pEffect->bUse = true;

			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�G�t�F�N�g�̒��_���W�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetVertexHitEffect(int nIdx)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHitEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aHitEffect[nIdx].pos.x - HITEFFECT_SIZE, g_aHitEffect[nIdx].pos.y - HITEFFECT_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aHitEffect[nIdx].pos.x - HITEFFECT_SIZE, g_aHitEffect[nIdx].pos.y + HITEFFECT_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aHitEffect[nIdx].pos.x + HITEFFECT_SIZE, g_aHitEffect[nIdx].pos.y - HITEFFECT_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aHitEffect[nIdx].pos.x + HITEFFECT_SIZE, g_aHitEffect[nIdx].pos.y + HITEFFECT_SIZE, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHitEffect->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�F�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetColorHitEffect(int nIdx)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHitEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_aHitEffect[nIdx].col;
	pVtx[1].col = g_aHitEffect[nIdx].col;
	pVtx[2].col = g_aHitEffect[nIdx].col;
	pVtx[3].col = g_aHitEffect[nIdx].col;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHitEffect->Unlock();
}