//-----------------------------------------------------------------
//
// �L�����Z���N�g��ʂ̔w�i (chara_select_bg.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "chara_select_bg.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MAX_PATTERN					(1)							// �w�i�̎��

#define CHARASELECT_BG_X			(SCREEN_WIDTH / 2)			// �L�����Z���N�g��ʔw�i�̈ʒu(X���W)
#define CHARASELECT_BG_Y			(SCREEN_HEIGHT / 2)			// �L�����Z���N�g��ʔw�i�̈ʒu(Y���W)
#define CHARASELECT_BG_WIDTH		(SCREEN_WIDTH)				// �L�����Z���N�g��ʔw�i�̕�
#define CHARASELECT_BG_HEIGHT		(SCREEN_HEIGHT)				// �L�����Z���N�g��ʔw�i�̍���

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCharaSelectBg = NULL;			// �L�����Z���N�g��ʔw�i�̒��_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureCharaSelectBg[MAX_PATTERN] = {};	// �L�����Z���N�g��ʔw�i�̃e�N�X�`���̃|�C���^
D3DXVECTOR3 g_posCharaSelectBg;

//-----------------------------------------------------------------
// �L�����Z���N�g��ʔw�i�̏���������
//-----------------------------------------------------------------
HRESULT InitCharaSelectBg(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n���A������
	pDevice = GetDevice();
	g_posCharaSelectBg = D3DXVECTOR3(CHARASELECT_BG_X, CHARASELECT_BG_Y, 0.0f);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_select_bg.png", &g_pTextureCharaSelectBg[0]);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * MAX_PATTERN,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffCharaSelectBg,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCharaSelectBg->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBg = 0; nCntBg < MAX_PATTERN; nCntBg++)
	{
		// ���_���W�̐ݒ�
		SetVertexCharaSelectBg(nCntBg);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���̍X�V
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCharaSelectBg->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �L�����Z���N�g��ʔw�i�̏I������
//-----------------------------------------------------------------
void UninitCharaSelectBg(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffCharaSelectBg != NULL)
	{
		g_pVtxBuffCharaSelectBg->Release();
		g_pVtxBuffCharaSelectBg = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCntBg = 0; nCntBg < MAX_PATTERN; nCntBg++)
	{
		if (g_pTextureCharaSelectBg[nCntBg] != NULL)
		{
			g_pTextureCharaSelectBg[nCntBg]->Release();
			g_pTextureCharaSelectBg[nCntBg] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// �L�����Z���N�g��ʔw�i�̍X�V����
//-----------------------------------------------------------------
void UpdateCharaSelectBg(void)
{

}

//-----------------------------------------------------------------
// �L�����Z���N�g��ʂ̕`�揈��
//-----------------------------------------------------------------
void DrawCharaSelectBg(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCharaSelectBg, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntBg = 0; nCntBg < MAX_PATTERN; nCntBg++)
	{
		pDevice->SetTexture(0, g_pTextureCharaSelectBg[nCntBg]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBg * 4, 2);
	}
}

//-----------------------------------------------------------------
// �L�����Z���N�g��ʂ̒��_���W�̐ݒ�
//-----------------------------------------------------------------
void SetVertexCharaSelectBg(int nCnt)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCharaSelectBg->Lock(0, 0, (void**)&pVtx, 0);

	// ���Ԗڂ�
	pVtx += nCnt * 4;

	// ���_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(g_posCharaSelectBg.x - (CHARASELECT_BG_WIDTH / 2), g_posCharaSelectBg.y + (CHARASELECT_BG_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posCharaSelectBg.x - (CHARASELECT_BG_WIDTH / 2), g_posCharaSelectBg.y - (CHARASELECT_BG_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posCharaSelectBg.x + (CHARASELECT_BG_WIDTH / 2), g_posCharaSelectBg.y + (CHARASELECT_BG_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posCharaSelectBg.x + (CHARASELECT_BG_WIDTH / 2), g_posCharaSelectBg.y - (CHARASELECT_BG_HEIGHT / 2), 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCharaSelectBg->Unlock();
}