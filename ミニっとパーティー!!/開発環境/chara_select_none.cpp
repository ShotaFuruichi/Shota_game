//-----------------------------------------------------------------
//
// �L�����Z���N�g�m�[�� (chara_select_none.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "chara_select_none.h"
#include "chara_select_frame.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define SCORE_X			(970.0f)				// ���S���W(X)
#define SCORE_Y			(50.0f)					// ���S���W(Y)

#define SCORE_WIDTH		(45.0f)					// �X�R�A�̕�
#define SCORE_HEIGHT	(80.0f)					// �X�R�A�̍���
#define WIDTH_X			(40.0f)					// �X�R�A��z�u����Ԋu

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCharaSelectNone = NULL;				// �L�����Z���N�g�C���[�W�̃e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureCharaSelectNone = NULL;				// �L�����Z���N�g�C���[�W�̒��_�o�b�t�@�̃|�C���^
CharaSelectNone g_aCharaSelectNone[MAX_CHARANONE];						// �L�����Z���N�g�C���[�W�̏��
int g_nNumNone;															// �`�搔

//-----------------------------------------------------------------
// �L�����Z���N�g�m�[���̏���������
//-----------------------------------------------------------------
HRESULT InitCharaSelectNone(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���[�h���̎擾
	int nNumPlayer = GetFrame();

	g_nNumNone = MAX_CHARANONE - nNumPlayer;

	// �e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_select_none.jpg", &g_pTextureCharaSelectNone);

	// �ϐ��̏�����
	for (int nCntNone = 0; nCntNone < MAX_CHARANONE; nCntNone++)
	{
		g_aCharaSelectNone[nCntNone].pos = D3DXVECTOR3(1120.0f - nCntNone * 320.0f, 255.0f, 0.0f);
		g_aCharaSelectNone[nCntNone].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aCharaSelectNone[nCntNone].fWidth = 320.0f;
		g_aCharaSelectNone[nCntNone].fHeight = 520.0f;
		g_aCharaSelectNone[nCntNone].bSelect = false;
	}

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * MAX_CHARANONE, // �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffCharaSelectNone,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCharaSelectNone->Lock(0, 0, (void**)&pVtx, 0);

	// ������
	for (int nCntImage = 0; nCntImage < MAX_CHARANONE; nCntImage++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aCharaSelectNone[nCntImage].pos.x - (g_aCharaSelectNone[nCntImage].fWidth / 2), g_aCharaSelectNone[nCntImage].pos.y + (g_aCharaSelectNone[nCntImage].fHeight / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aCharaSelectNone[nCntImage].pos.x - (g_aCharaSelectNone[nCntImage].fWidth / 2), g_aCharaSelectNone[nCntImage].pos.y - (g_aCharaSelectNone[nCntImage].fHeight / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aCharaSelectNone[nCntImage].pos.x + (g_aCharaSelectNone[nCntImage].fWidth / 2), g_aCharaSelectNone[nCntImage].pos.y + (g_aCharaSelectNone[nCntImage].fHeight / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aCharaSelectNone[nCntImage].pos.x + (g_aCharaSelectNone[nCntImage].fWidth / 2), g_aCharaSelectNone[nCntImage].pos.y - (g_aCharaSelectNone[nCntImage].fHeight / 2), 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_aCharaSelectNone[nCntImage].col;
		pVtx[1].col = g_aCharaSelectNone[nCntImage].col;
		pVtx[2].col = g_aCharaSelectNone[nCntImage].col;
		pVtx[3].col = g_aCharaSelectNone[nCntImage].col;

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// �X�R�A�̏������ɂ���
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCharaSelectNone->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �L�����Z���N�g�m�[���̏I������
//-----------------------------------------------------------------
void UninitCharaSelectNone(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffCharaSelectNone != NULL)
	{
		g_pVtxBuffCharaSelectNone->Release();
		g_pVtxBuffCharaSelectNone = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureCharaSelectNone != NULL)
	{
		g_pTextureCharaSelectNone->Release();
		g_pTextureCharaSelectNone = NULL;
	}
}

//-----------------------------------------------------------------
// �L�����Z���N�g�m�[���̍X�V����
//-----------------------------------------------------------------
void UpdateCharaSelectNone(void)
{

}

//-----------------------------------------------------------------
// �L�����Z���N�g�m�[���̕`�揈��
//-----------------------------------------------------------------
void DrawCharaSelectNone(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���[�h���̎擾
	int nNumPlayer = GetFrame();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCharaSelectNone, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�ƕ`��
	for (int nCntTexture = 0; nCntTexture < 4 - nNumPlayer; nCntTexture++)
	{
		pDevice->SetTexture(0, g_pTextureCharaSelectNone);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexture * 4, 2);
	}
}