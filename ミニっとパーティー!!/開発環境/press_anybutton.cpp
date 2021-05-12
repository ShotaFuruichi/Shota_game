//-----------------------------------------------------------------
//
// �{�^���w�� (press_anybutton.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "press_anybutton.h"
#include "texture.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "sound.h"

// �}�N��
#define FLASH_INTERBAL_MODELOGO		(10)				// �_�ŃC���^�[�o��
#define CLEAR_NUMBER_MODELOGO		(5)					// ����
#define LESS_CLEAR_NUMBER_MODELOGO	(0)					// �s����
#define FLASH_COUNT					(50)				// �t���b�V���J�E���g

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPressAnyButton = NULL;			// �Z���N�g���[�h�̒��_�o�b�t�@�̃|�C���^
PressAnyButton g_PressAnyButton;								// �Z���N�g���[�h�̏��
int g_nCntFlash;												// �_�ŃJ�E���g

//-----------------------------------------------------------------
// �{�^���w���̏���������
//-----------------------------------------------------------------
HRESULT InitPressAnyButton(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// �ϐ��̏�����
	g_PressAnyButton.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PressAnyButton.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_PressAnyButton.fRemoveAlpha = 0.0f;
	g_PressAnyButton.fWidth = 0.0f;
	g_PressAnyButton.fHeight = 0.0f;
	g_PressAnyButton.nTexType = -1;
	g_PressAnyButton.bUse = false;
	g_PressAnyButton.bPressAnyButton = false;

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX , // �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPressAnyButton,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPressAnyButton->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	SetVertexPressAnyButton();

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

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPressAnyButton->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �{�^���w���̏I������
//-----------------------------------------------------------------
void UninitPressAnyButton(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPressAnyButton != NULL)
	{
		g_pVtxBuffPressAnyButton->Release();
		g_pVtxBuffPressAnyButton = NULL;
	}
}

//-----------------------------------------------------------------
// �{�^���w���̍X�V����
//-----------------------------------------------------------------
void UpdatePressAnyButton(void)
{
	// ���_���W�̍X�V
	if (g_PressAnyButton.bPressAnyButton == false)
	{
		if (GetJoypadTrigger(PLAYER_1, JPINFO_PAUSE))
		{
			g_PressAnyButton.bPressAnyButton = true;
			PlaySound(SOUND_LABEL_SE_DICIDE);
		}
		if ((g_PressAnyButton.col.a < 0.3f) || (g_PressAnyButton.col.a > 1.0f))
		{// ����
			g_PressAnyButton.fRemoveAlpha -= g_PressAnyButton.fRemoveAlpha * 2.0f;
		}
		// �F�̍X�V
		g_PressAnyButton.col.a -= g_PressAnyButton.fRemoveAlpha;
	}
	else
	{
		// �_�ł����邽�߂ɃJ�E���g��i�߂�
		g_nCntFlash++;

		if (CLEAR_NUMBER_MODELOGO == g_nCntFlash % FLASH_INTERBAL_MODELOGO)
		{// ����
			g_PressAnyButton.col.a = 0.0f;
		}
		else if (LESS_CLEAR_NUMBER_MODELOGO == g_nCntFlash % FLASH_INTERBAL_MODELOGO)
		{// �s����
			g_PressAnyButton.col.a = 1.0f;
		}
		// �J�E���g��������x�i�񂾂�J��
		if (g_nCntFlash >= FLASH_COUNT)
		{// ���ɐi�񂾂Ƃ�����
		 // �Q�[���ɑJ��
			SetFade(FADE_OUT, MODE_TUTORIAL);
		}
	}
	// ���_���W�̍X�V
	SetVertexPressAnyButton();
}

//-----------------------------------------------------------------
// �{�^���w���̕`�揈��
//-----------------------------------------------------------------
void DrawPressAnyButton(void)
{
	// UI�e�N�X�`�����̎擾
	Texture *pTexture = GetUITexture();

	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPressAnyButton, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	pDevice->SetTexture(0, pTexture->TextureInfo[g_PressAnyButton.nTexType].pTexture);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, 2);
}

//-----------------------------------------------------------------
// �{�^���w���̐ݒu
//-----------------------------------------------------------------
void SetPressAnyButton(D3DXVECTOR3 pos, D3DXCOLOR col,float fRemoveAlpha, float fWidth, float fHeight, int nTextype)
{
	// �Z���N�g���[�h�ݒu���̎擾
	PressAnyButton *pPressAnyButton = &g_PressAnyButton;

	if (pPressAnyButton->bUse == false)
	{
		// �ʒu���̊i�[
		pPressAnyButton->pos = pos;

		// �F���̊i�[
		pPressAnyButton->col = col;

		// ���l�����ʂ̊i�[
		pPressAnyButton->fRemoveAlpha = fRemoveAlpha;

		// ���̊i�[
		pPressAnyButton->fWidth = fWidth;

		// �����̊i�[
		pPressAnyButton->fHeight = fHeight;

		// �e�N�X�`���^�C�v�̊i�[
		pPressAnyButton->nTexType = nTextype;

		// �g�p��Ԃ�true�ɂ���
		pPressAnyButton->bUse = true;
	}
}

//-----------------------------------------------------------------
// ���_���W�̐ݒ�
//-----------------------------------------------------------------
void SetVertexPressAnyButton(void)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;
	PressAnyButton *pPressAnyButton = &g_PressAnyButton;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPressAnyButton->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(pPressAnyButton->pos.x - (pPressAnyButton->fWidth / 2.0f), pPressAnyButton->pos.y + (pPressAnyButton->fHeight / 2.0f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pPressAnyButton->pos.x - (pPressAnyButton->fWidth / 2.0f), pPressAnyButton->pos.y - (pPressAnyButton->fHeight / 2.0f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pPressAnyButton->pos.x + (pPressAnyButton->fWidth / 2.0f), pPressAnyButton->pos.y + (pPressAnyButton->fHeight / 2.0f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pPressAnyButton->pos.x + (pPressAnyButton->fWidth / 2.0f), pPressAnyButton->pos.y - (pPressAnyButton->fHeight / 2.0f), 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = pPressAnyButton->col;
	pVtx[1].col = pPressAnyButton->col;
	pVtx[2].col = pPressAnyButton->col;
	pVtx[3].col = pPressAnyButton->col;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPressAnyButton->Unlock();
}

//-----------------------------------------------------------------
// �{�^���w�����̎擾
//-----------------------------------------------------------------
PressAnyButton *GetPressAnyButton(void)
{
	return &g_PressAnyButton;
}