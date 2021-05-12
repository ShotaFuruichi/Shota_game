//-----------------------------------------------------------------
//
// �L�����Z���N�g�C���[�W (chara_select_image.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "chara_select_image.h"

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
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCharaSelectImage = NULL;				// �L�����Z���N�g�C���[�W�̃e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureCharaSelectImage[MAX_CHARAIMAGE] = {};		// �L�����Z���N�g�C���[�W�̒��_�o�b�t�@�̃|�C���^
CharaSelectImage g_aCharaSelectImage[MAX_CHARAIMAGE];						// �L�����Z���N�g�C���[�W�̏��

//-----------------------------------------------------------------
// �L�����Z���N�g�C���[�W�̏���������
//-----------------------------------------------------------------
HRESULT InitCharaSelectImage(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_image1.jpg", &g_pTextureCharaSelectImage[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_image2.jpg", &g_pTextureCharaSelectImage[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_image3.jpg", &g_pTextureCharaSelectImage[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_image4.jpg", &g_pTextureCharaSelectImage[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_image_random.jpg", &g_pTextureCharaSelectImage[4]);

	// �ϐ��̏�����
	for (int nCntImage = 0; nCntImage < MAX_CHARAIMAGE; nCntImage++)
	{
		g_aCharaSelectImage[nCntImage].pos = D3DXVECTOR3(340.0f + nCntImage * 150.0f, 620.0f, 0.0f);
		g_aCharaSelectImage[nCntImage].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aCharaSelectImage[nCntImage].fWidth = 120.0f;
		g_aCharaSelectImage[nCntImage].fHeight = 120.0f;
		g_aCharaSelectImage[nCntImage].bSelect = false;
	}

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * MAX_CHARAIMAGE, // �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffCharaSelectImage,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCharaSelectImage->Lock(0, 0, (void**)&pVtx, 0);

	// ������
	for (int nCntImage = 0; nCntImage < MAX_CHARAIMAGE; nCntImage++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aCharaSelectImage[nCntImage].pos.x - (g_aCharaSelectImage[nCntImage].fWidth / 2), g_aCharaSelectImage[nCntImage].pos.y + (g_aCharaSelectImage[nCntImage].fHeight / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aCharaSelectImage[nCntImage].pos.x - (g_aCharaSelectImage[nCntImage].fWidth / 2), g_aCharaSelectImage[nCntImage].pos.y - (g_aCharaSelectImage[nCntImage].fHeight / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aCharaSelectImage[nCntImage].pos.x + (g_aCharaSelectImage[nCntImage].fWidth / 2), g_aCharaSelectImage[nCntImage].pos.y + (g_aCharaSelectImage[nCntImage].fHeight / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aCharaSelectImage[nCntImage].pos.x + (g_aCharaSelectImage[nCntImage].fWidth / 2), g_aCharaSelectImage[nCntImage].pos.y - (g_aCharaSelectImage[nCntImage].fHeight / 2), 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_aCharaSelectImage[nCntImage].col;
		pVtx[1].col = g_aCharaSelectImage[nCntImage].col;
		pVtx[2].col = g_aCharaSelectImage[nCntImage].col;
		pVtx[3].col = g_aCharaSelectImage[nCntImage].col;

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// �X�R�A�̏������ɂ���
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCharaSelectImage->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �L�����Z���N�g�C���[�W�̏I������
//-----------------------------------------------------------------
void UninitCharaSelectImage(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffCharaSelectImage != NULL)
	{
		g_pVtxBuffCharaSelectImage->Release();
		g_pVtxBuffCharaSelectImage = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCntTexture = 0; nCntTexture < MAX_CHARAIMAGE; nCntTexture++)
	{
		if (g_pTextureCharaSelectImage[nCntTexture] != NULL)
		{
			g_pTextureCharaSelectImage[nCntTexture]->Release();
			g_pTextureCharaSelectImage[nCntTexture] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// �L�����Z���N�g�g�̍X�V����
//-----------------------------------------------------------------
void UpdateCharaSelectImage(void)
{

}

//-----------------------------------------------------------------
// �L�����Z���N�g�C���[�W�̕`�揈��
//-----------------------------------------------------------------
void DrawCharaSelectImage(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffCharaSelectImage, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�ƕ`��
	for (int nCntTexture = 0; nCntTexture < MAX_CHARAIMAGE; nCntTexture++)
	{
		pDevice->SetTexture(0, g_pTextureCharaSelectImage[nCntTexture]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexture * 4, 2);
	}
}

//-----------------------------------------------------------------
// �L�����Z���N�g�C���[�W���̎擾
//-----------------------------------------------------------------
CharaSelectImage *GetCharaSelectImage(void)
{
	return &g_aCharaSelectImage[0];
}