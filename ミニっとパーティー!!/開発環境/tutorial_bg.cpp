//-----------------------------------------------------------------
//
// �`���[�g���A����ʂ̔w�i (tutorial_bg.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "tutorial_bg.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MAX_IMAGE				(1)							// �w�i�̎��

#define TUTORIAL_BG_X			(SCREEN_WIDTH / 2)			// �`���[�g���A����ʔw�i�̈ʒu(X���W)
#define TUTORIAL_BG_Y			(SCREEN_HEIGHT / 2)			// �`���[�g���A����ʔw�i�̈ʒu(Y���W)
#define TUTORIAL_BG_WIDTH		(SCREEN_WIDTH)				// �`���[�g���A����ʔw�i�̕�
#define TUTORIAL_BG_HEIGHT		(SCREEN_HEIGHT)				// �`���[�g���A����ʔw�i�̍���

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorialBg = NULL;		// �`���[�g���A����ʔw�i�̒��_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTutorialBg[MAX_IMAGE] = {};	// �`���[�g���A����ʔw�i�̃e�N�X�`���̃|�C���^
D3DXVECTOR3 g_posTutorialBg;

//-----------------------------------------------------------------
// �`���[�g���A����ʔw�i�̏���������
//-----------------------------------------------------------------
HRESULT InitTutorialBg(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n���A������
	pDevice = GetDevice();
	g_posTutorialBg = D3DXVECTOR3(TUTORIAL_BG_X, TUTORIAL_BG_Y, 0.0f);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/tutorial_bg.jpg", &g_pTextureTutorialBg[0]);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * MAX_IMAGE,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialBg,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorialBg->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBg = 0; nCntBg < MAX_IMAGE; nCntBg++)
	{
		// ���_���W�̐ݒ�
		SetVertexTutorialBg(nCntBg);

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
	g_pVtxBuffTutorialBg->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �`���[�g���A���Z���N�g��ʔw�i�̏I������
//-----------------------------------------------------------------
void UninitTutorialBg(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTutorialBg != NULL)
	{
		g_pVtxBuffTutorialBg->Release();
		g_pVtxBuffTutorialBg = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCntBg = 0; nCntBg < MAX_IMAGE; nCntBg++)
	{
		if (g_pTextureTutorialBg[nCntBg] != NULL)
		{
			g_pTextureTutorialBg[nCntBg]->Release();
			g_pTextureTutorialBg[nCntBg] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// �`���[�g���A����ʔw�i�̍X�V����
//-----------------------------------------------------------------
void UpdateTutorialBg(void)
{

}

//-----------------------------------------------------------------
// �`���[�g���A����ʂ̕`�揈��
//-----------------------------------------------------------------
void DrawTutorialBg(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorialBg, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntBg = 0; nCntBg < MAX_IMAGE; nCntBg++)
	{
		pDevice->SetTexture(0, g_pTextureTutorialBg[nCntBg]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBg * 4, 2);
	}
}

//-----------------------------------------------------------------
// �`���[�g���A����ʂ̒��_���W�̐ݒ�
//-----------------------------------------------------------------
void SetVertexTutorialBg(int nCnt)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorialBg->Lock(0, 0, (void**)&pVtx, 0);

	// ���Ԗڂ�
	pVtx += nCnt * 4;

	// ���_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(g_posTutorialBg.x - (TUTORIAL_BG_WIDTH / 2), g_posTutorialBg.y + (TUTORIAL_BG_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posTutorialBg.x - (TUTORIAL_BG_WIDTH / 2), g_posTutorialBg.y - (TUTORIAL_BG_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posTutorialBg.x + (TUTORIAL_BG_WIDTH / 2), g_posTutorialBg.y + (TUTORIAL_BG_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posTutorialBg.x + (TUTORIAL_BG_WIDTH / 2), g_posTutorialBg.y - (TUTORIAL_BG_HEIGHT / 2), 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorialBg->Unlock();
}