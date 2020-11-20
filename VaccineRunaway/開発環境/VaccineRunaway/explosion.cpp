////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �������� [explosion.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/08/05
//
////////////////////////////////////////////////////////////////////////////////
#include "explosion.h"
#include "sound.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define EXPLOSION_SIZE (30.0f)			//�����̃T�C�Y

#define MAX_ANIM (8)					//�A�j���[�V��������
#define ANIM_DIVIDE (1.0f  / MAX_ANIM)	//�A�j���[�V�����摜��؂�

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;			//���_�o�b�t�@�ւ̐ݒ�
EXPLOSION g_aExplosion[MAX_EXPLOSION];						//�����̏��
int g_nCounterAnimEx[MAX_EXPLOSION];						//�A�j���[�V�����J�E���^�[
int g_nPatternAnimEx[MAX_EXPLOSION];						//�A�j���[�V�����p�^�[��NO.

////////////////////////////////////////////////////////////////////////////////
//�����̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitExplosion(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\explosion000.png", &g_pTextureExplosion);

	//������
	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{	
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0, 0, 0.0f);
		g_aExplosion[nCntExplosion].bUse = false;
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(0.0f, 0.0f, 0.f, 0.0f);
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffExplosion, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//���_���W�̐ݒ�
		SetVertexExplosion(nCntExplosion);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffExplosion->Unlock();
	}
	

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�����̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitExplosion(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();	//�J��
		g_pVtxBuffExplosion = NULL;		//������
	}
	//�e�N�X�`���̊J��
	
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();	//�J��
		g_pTextureExplosion = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�����̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateExplosion(void)
{
	//�ϐ��錾
	EXPLOSION *pExplosion;
	VERTEX_2D *pVtx;

	pExplosion = &g_aExplosion[0];

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
	{	
		if (pExplosion->bUse == true)
		{	//�������g�p����Ă���Ƃ�

			//�A�j���[�V�����J�E���^�[�̍X�V
			g_nCounterAnimEx[nCntExplosion]++;

			if (g_nCounterAnimEx[nCntExplosion] % 5 == 0)
			{
				g_nPatternAnimEx[nCntExplosion]++;

				pVtx[0].tex = D3DXVECTOR2(ANIM_DIVIDE * (float)g_nPatternAnimEx[nCntExplosion], 1.0f);
				pVtx[1].tex = D3DXVECTOR2(ANIM_DIVIDE * (float)g_nPatternAnimEx[nCntExplosion], 0.0f);
				pVtx[2].tex = D3DXVECTOR2(ANIM_DIVIDE * ((float)g_nPatternAnimEx[nCntExplosion] + 1.0f), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(ANIM_DIVIDE * ((float)g_nPatternAnimEx[nCntExplosion] + 1.0f), 0.0f);

				if (g_nPatternAnimEx[nCntExplosion] >= MAX_ANIM)
				{
					pExplosion->bUse = false;
					g_nPatternAnimEx[nCntExplosion] = NULL;
				}
			}
		}
		pVtx+= 4;
	}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffExplosion->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�����̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawExplosion(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureExplosion);

		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}

}

////////////////////////////////////////////////////////////////////////////////
//�����̃Z�b�g����
////////////////////////////////////////////////////////////////////////////////
void SetExplosion(D3DXVECTOR3 pos)
{
	//�ϐ��錾
	EXPLOSION *pExplosion;

	pExplosion = &g_aExplosion[0];

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++, pExplosion++)
	{
		if (pExplosion->bUse == false)
		{	//�������g�p����Ă��Ȃ��Ƃ�

			pExplosion->pos = pos;
			
			//���_���W�̐ݒ�
			SetVertexExplosion(nCntExplosion);

			//�e���g�p����
			pExplosion->bUse = true;

			break;
		}
	}
	
}

////////////////////////////////////////////////////////////////////////////////
//�����̒��_���W�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetVertexExplosion(int nIdx)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nIdx].pos.x - EXPLOSION_SIZE, g_aExplosion[nIdx].pos.y + EXPLOSION_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nIdx].pos.x - EXPLOSION_SIZE, g_aExplosion[nIdx].pos.y - EXPLOSION_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nIdx].pos.x + EXPLOSION_SIZE, g_aExplosion[nIdx].pos.y + EXPLOSION_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nIdx].pos.x + EXPLOSION_SIZE, g_aExplosion[nIdx].pos.y - EXPLOSION_SIZE, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}