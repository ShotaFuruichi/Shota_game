////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �G�t�F�N�g [effect.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/09/07
//
////////////////////////////////////////////////////////////////////////////////
#include "effect.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define EFFECT_SIZE (100.0f)			//�G�t�F�N�g�̃T�C�Y
#define ALPHA_DOWN (0.03f)				//���l������

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;		//���_�o�b�t�@�ւ̐ݒ�
EFFECT g_aEffect[MAX_EFFECT];							//�G�t�F�N�g�̏��

////////////////////////////////////////////////////////////////////////////////
//�G�t�F�N�g�̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitEffect(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_3D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effect000.jpg", &g_pTextureEffect);

	//������
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0, 0, 0.0f);
		g_aEffect[nCntEffect].bUse = false;
		g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffEffect, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���_���W�̐ݒ�
		SetVertexEffect(nCntEffect);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		SetColorEffect(nCntEffect);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffEffect->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�G�t�F�N�g�̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitEffect(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();	//�J��
		g_pVtxBuffEffect = NULL;		//������
	}
	//�e�N�X�`���̊J��

	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();	//�J��
		g_pTextureEffect = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�G�t�F�N�g�̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateEffect(void)
{
	//�ϐ��錾
	EFFECT *pEffect;

	pEffect = &g_aEffect[0];

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		//�F�̐ݒ�
		SetColorEffect(nCntEffect);

		if (pEffect->bUse == true)
		{	//�G�t�F�N�g���g�p����Ă���Ƃ�

			//���l����
			if (pEffect->col.a > 0)
			{
				pEffect->col.a -= ALPHA_DOWN;
			}
			else
			{
				pEffect->bUse = false;
				pEffect->col.a = 1.0f;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�G�t�F�N�g�̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawEffect(void)
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

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffect[nCntEffect].mtxworld);

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
			g_aEffect[nCntEffect].mtxworld._11 = mtxView._11;
			g_aEffect[nCntEffect].mtxworld._12 = mtxView._21;
			g_aEffect[nCntEffect].mtxworld._13 = mtxView._31;
			g_aEffect[nCntEffect].mtxworld._21 = mtxView._12;
			g_aEffect[nCntEffect].mtxworld._22 = mtxView._22;
			g_aEffect[nCntEffect].mtxworld._23 = mtxView._32;
			g_aEffect[nCntEffect].mtxworld._31 = mtxView._13;
			g_aEffect[nCntEffect].mtxworld._32 = mtxView._23;
			g_aEffect[nCntEffect].mtxworld._33 = mtxView._33;
#endif

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxworld, &g_aEffect[nCntEffect].mtxworld, &mtxTrans);

			//���[���h�}�g���b�N�X
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].mtxworld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect);

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
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	//�ϐ��錾
	EFFECT *pEffect;

	pEffect = &g_aEffect[0];

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
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
void SetVertexEffect(int nIdx)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x - EFFECT_SIZE, g_aEffect[nIdx].pos.y - EFFECT_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x - EFFECT_SIZE, g_aEffect[nIdx].pos.y + EFFECT_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x + EFFECT_SIZE, g_aEffect[nIdx].pos.y - EFFECT_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aEffect[nIdx].pos.x + EFFECT_SIZE, g_aEffect[nIdx].pos.y + EFFECT_SIZE, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�F�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetColorEffect(int nIdx)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_aEffect[nIdx].col;
	pVtx[1].col = g_aEffect[nIdx].col;
	pVtx[2].col = g_aEffect[nIdx].col;
	pVtx[3].col = g_aEffect[nIdx].col;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}