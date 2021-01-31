////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �w�i�̏��� [bg.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/10/13
//
////////////////////////////////////////////////////////////////////////////////
#include "bg.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "game.h"
#include "fade.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define MAX_BUFF (2) //���_���̌�

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg[MAX_BUFF] = {};		//���_���
LPDIRECT3DTEXTURE9 g_pTextureBg[STAGE_MAX] = {};	//�e�N�X�`�����

BGTEX g_Bg;
D3DXCOLOR g_col;

float g_f;
float g_f2;

////////////////////////////////////////////////////////////////////////////////
//�w�i�̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitBg(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntTexture = 0; nCntTexture < STAGE_MAX; nCntTexture++)
	{
		g_pTextureBg[nCntTexture] = NULL;
	}
	g_Bg = BG_WINTER;
	g_f = 0.0f;
	g_f2 = 1.0f;
	g_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\winter.jpg", &g_pTextureBg[STAGE_0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\spring.jpg", &g_pTextureBg[STAGE_1]);

	for (int nCntBG = 0; nCntBG < MAX_BUFF; nCntBG++)
	{
		//�ϐ��̏�����
		g_pVtxBuffBg[nCntBG] = NULL;

		//���_�o�b�t�@�̐���
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBg[nCntBG], NULL)))
		{
			return E_FAIL;
		}

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffBg[nCntBG]->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0);

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

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffBg[nCntBG]->Unlock();

	}

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�w�i�̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitBg(void)
{
	//���_�o�b�t�@�̊J��
	//�e�N�X�`���̊J��
	for (int nCntBuff = 0; nCntBuff < MAX_BUFF; nCntBuff++)
	{
		if (g_pVtxBuffBg[nCntBuff] != NULL)
		{
			g_pVtxBuffBg[nCntBuff]->Release();	//�J��
			g_pVtxBuffBg[nCntBuff] = NULL;		//������
		}
	}

	//�e�N�X�`���̊J��
	for (int nCntTexture = 0; nCntTexture < STAGE_MAX; nCntTexture++)
	{
		if (g_pTextureBg[nCntTexture] != NULL)
		{
			g_pTextureBg[nCntTexture]->Release();	//�J��
			g_pTextureBg[nCntTexture] = NULL;		//������
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�w�i�̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateBg(void)
{
	PLAYER *pPlayer;
	VERTEX_2D *pVtx;
	pPlayer = GetPlayer();

#if 0
		if (GetKeyboardPress(DIK_D) == true)
		{
			if (GetKeyboardPress(DIK_A) == true)
			{
			}
			else
			{
				g_f -= 0.0005f;
				g_f2 -= 0.0005f;
			}
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{
			if (GetKeyboardPress(DIK_D) == true)
			{
			}
			else
			{
				g_f += 0.0005f;
				g_f2 += 0.0005f;
			}
		}
#endif
		/*if (g_Bg == BG_WINTER)
		{
			if (g_f2 < 1.0f)
			{
				g_f += 0.005f;
				g_f2 += 0.005f;
			}
		}*/

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBg[1]->Lock(0, 0, (void**)&pVtx, 0);
	
	if (g_col.a > 0)
	{
		g_col.a -= 0.01f;
	}

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_col;
	pVtx[1].col = g_col;
	pVtx[2].col = g_col;
	pVtx[3].col = g_col;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBg[1]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�w�i�̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawBg(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	FADE fade;
	STAGE stage;
	stage = GetStage();
	fade = GetFade();

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBg[0], 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBg[STAGE_1]);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBg[1], 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_Bg == BG_WINTER)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBg[STAGE_0]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
	
}

////////////////////////////////////////////////////////////////////////////////
//bg�̏��擾
////////////////////////////////////////////////////////////////////////////////
void SetBg(BGTEX bg)
{
	g_Bg = bg;
}