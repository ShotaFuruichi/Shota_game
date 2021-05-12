//-----------------------------------------------------------------
//
// �L�������� (dicision_chara.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "dicision_chara.h"
#include "chara_select_frame.h"
#include "chara_select_image.h"
#include "chara.h"
#include "gamepad.h"
#include "player.h"
#include "fade.h"
#include "sound.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define MAX_TEXTURE		(2)						// �e�N�X�`������
#define MAX_DICISION	(5)
#define SCORE_X			(970.0f)				// ���S���W(X)
#define SCORE_Y			(50.0f)					// ���S���W(Y)

#define SCORE_WIDTH		(45.0f)					// �X�R�A�̕�
#define SCORE_HEIGHT	(80.0f)					// �X�R�A�̍���
#define WIDTH_X			(40.0f)					// �X�R�A��z�u����Ԋu

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDicisionChara = NULL;			// �L��������̃e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureDicisionChara[MAX_TEXTURE] = {};	// �L��������̒��_�o�b�t�@�̃|�C���^
DicisionChara g_aDicisionChara[MAX_DICISION];					// �L��������̏��
int g_nNumDicision;

//-----------------------------------------------------------------
// �L�����Z���N�g�g�̏���������
//-----------------------------------------------------------------
HRESULT InitDicisionChara(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// �L�����Z���N�g�C���[�W���̎擾
	CharaSelectImage *pCharaSelectImage = GetCharaSelectImage();

	g_nNumDicision = 0;

	// �e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/ok.png", &g_pTextureDicisionChara[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/press_start00.jpg", &g_pTextureDicisionChara[1]);

	// �ϐ��̏�����
	for (int nCntDicisionChara = 0; nCntDicisionChara < MAX_DICISION; nCntDicisionChara++, pCharaSelectImage++)
	{
		if (nCntDicisionChara == 4)
		{
			g_aDicisionChara[nCntDicisionChara].pos = D3DXVECTOR3(640.0f, 500.0f, 0.0f);
			g_aDicisionChara[nCntDicisionChara].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_aDicisionChara[nCntDicisionChara].fWidth = 1280.0f;
			g_aDicisionChara[nCntDicisionChara].fHeight = 60.0f;
			g_aDicisionChara[nCntDicisionChara].nTxType = 1;
		}
		else
		{
			g_aDicisionChara[nCntDicisionChara].pos = D3DXVECTOR3(160.0f + 320.0f * nCntDicisionChara, 500.0f, 0.0f);
			g_aDicisionChara[nCntDicisionChara].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_aDicisionChara[nCntDicisionChara].fWidth = 320.0f;
			g_aDicisionChara[nCntDicisionChara].fHeight = 60.0f;
			g_aDicisionChara[nCntDicisionChara].nTxType = 0;
		}
		g_aDicisionChara[nCntDicisionChara].bDicision = false;
	}

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * MAX_DICISION, // �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffDicisionChara,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffDicisionChara->Lock(0, 0, (void**)&pVtx, 0);

	// ������
	for (int nCntDicisionChara = 0; nCntDicisionChara < MAX_DICISION; nCntDicisionChara++)
	{
		// ���_���W�̐ݒ�
		SetVertexDicisionChara(nCntDicisionChara);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = g_aDicisionChara[nCntDicisionChara].col;
		pVtx[1].col = g_aDicisionChara[nCntDicisionChara].col;
		pVtx[2].col = g_aDicisionChara[nCntDicisionChara].col;
		pVtx[3].col = g_aDicisionChara[nCntDicisionChara].col;

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// �X�R�A�̏������ɂ���
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffDicisionChara->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �L�����Z���N�g�g�̏I������
//-----------------------------------------------------------------
void UninitDicisionChara(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffDicisionChara != NULL)
	{
		g_pVtxBuffDicisionChara->Release();
		g_pVtxBuffDicisionChara = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
	{
		if (g_pTextureDicisionChara[nCntTexture] != NULL)
		{
			g_pTextureDicisionChara[nCntTexture]->Release();
			g_pTextureDicisionChara[nCntTexture] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// �L�����Z���N�g�g�̍X�V����
//-----------------------------------------------------------------
void UpdateDicisionChara(void)
{
	// �t���[�������擾
	int nNumFrame = GetFrame();

	// �S���I�񂾎�
	if (g_nNumDicision == nNumFrame)
	{
		g_aDicisionChara[4].bDicision = true;

		for (int nCntPlayer = 0; nCntPlayer < nNumFrame; nCntPlayer++)
		{
			if (GetJoypadTrigger(nCntPlayer,JPINFO_PAUSE) == true)
			{// �~�j�Q�[���I����ʂɑJ��
				SetFade(FADE_OUT, MODE_GAME);
				PlaySound(SOUND_LABEL_SE_BOMB);
			}
		}
	}
	else
	{
		g_aDicisionChara[4].bDicision = false;
	}

	for (int nCntDicisionChara = 0; nCntDicisionChara < MAX_DICISION; nCntDicisionChara++)
	{
		if (g_aDicisionChara[nCntDicisionChara].bDicision == true)
		{
			// ���_���W�̍X�V
			SetVertexDicisionChara(nCntDicisionChara);
		}
	}
}

//-----------------------------------------------------------------
// �L�����Z���N�g�g�̕`�揈��
//-----------------------------------------------------------------
void DrawDicisionChara(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffDicisionChara, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �I�����ꂽ���[�h�ɉ����ĕ`��
	for (int nCntDicisionChara = 0; nCntDicisionChara < MAX_DICISION; nCntDicisionChara++)
	{
		if (g_aDicisionChara[nCntDicisionChara].bDicision == true)
		{
			pDevice->SetTexture(0, g_pTextureDicisionChara[g_aDicisionChara[nCntDicisionChara].nTxType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntDicisionChara * 4, 2);
		}
	}
}

//-----------------------------------------------------------------
// �L�����Z���N�g�t���[���̒��_���W�̐ݒ�
//-----------------------------------------------------------------
void SetVertexDicisionChara(int nIdx)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffDicisionChara->Lock(0, 0, (void**)&pVtx, 0);

	// ���Ԗڂ�
	pVtx += nIdx * 4;

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aDicisionChara[nIdx].pos.x - g_aDicisionChara[nIdx].fWidth / 2.0f, g_aDicisionChara[nIdx].pos.y + g_aDicisionChara[nIdx].fHeight / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aDicisionChara[nIdx].pos.x - g_aDicisionChara[nIdx].fWidth / 2.0f, g_aDicisionChara[nIdx].pos.y - g_aDicisionChara[nIdx].fHeight / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aDicisionChara[nIdx].pos.x + g_aDicisionChara[nIdx].fWidth / 2.0f, g_aDicisionChara[nIdx].pos.y + g_aDicisionChara[nIdx].fHeight / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aDicisionChara[nIdx].pos.x + g_aDicisionChara[nIdx].fWidth / 2.0f, g_aDicisionChara[nIdx].pos.y - g_aDicisionChara[nIdx].fHeight / 2.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffDicisionChara->Unlock();
}

//-----------------------------------------------------------------
// �L�����Z���N�g�t���[�����̎擾
//-----------------------------------------------------------------
DicisionChara *GetDicisionChara(void)
{
	return &g_aDicisionChara[0];
}

//-----------------------------------------------------------------
// �Z�b�g���邩�ǂ���
//-----------------------------------------------------------------
void SetDicisionChara(bool bDicision,int nCntPlayer)
{
	g_aDicisionChara[nCntPlayer].bDicision = bDicision;

	if (bDicision == true)
	{
		g_nNumDicision++;
	}
	else
	{
		g_nNumDicision--;
	}
}