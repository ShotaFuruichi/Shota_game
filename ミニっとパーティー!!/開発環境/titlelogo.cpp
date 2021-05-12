//-----------------------------------------------------------------
//
// �^�C�g�����S (titlelogo.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "titlelogo.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MAX_PATTERN				(2)							// �A�j���[�V�����p�^�[��No.�̍ő吔

#define TITLELOGO_POS_Y			(200.0f)					// �z�u����Y���W
#define TITLELOGO_X				(800.0f)					// �^�C�g�����S��
#define TITLELOGO_Y				(300.0f)					// �^�C�g�����S�̍���
#define HEIGHT_Y				(300.0f)					// �^�C�g�����S�̏������SY���W

#define TITLELOGO_ROT_COUNTER	(100)						// �������J�E���g
#define TITLELOGO_ROT_Z			(0.002f)					// �^�C�g�����S�̉�]��

#define MOVE_TITLELOGO			(5.0f)						// �^�C�g�����S�̈ړ���

#define RATE					(0.05f)						// �������[�g�̑�����
#define MOVE_RATE				(0.001f)					// �������[�g�̑�����

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleLogo = NULL;		// �^�C�g�����S�̒��_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTitleLogo = NULL;			// �^�C�g�����S�̃e�N�X�`���̃|�C���^
TITLELOGO g_TitleLogo;									// �^�C�g�����S�̏��
D3DXCOLOR g_color;										// �F
bool g_bFall;											// �^�C�g�����S�����S�ɗ�����������
int g_TLCnt;											// �^�C�g�����S�̉�]�J�E���g

//-----------------------------------------------------------------
// �^�C�g�����S�̏���������
//-----------------------------------------------------------------
HRESULT InitTitlelogo(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// �ϐ��̏�����
	g_TitleLogo.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, HEIGHT_Y, 0.0f);
	g_TitleLogo.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_TitleLogo.fRateWidth = RATE;
	g_TitleLogo.fRateHeight = RATE;
	g_TitleLogo.fMoveRateWidth = g_TitleLogo.fRateWidth;
	g_TitleLogo.fMoveRateHeight = g_TitleLogo.fRateHeight;
	g_TitleLogo.fWidth = TITLELOGO_X * g_TitleLogo.fRateWidth;
	g_TitleLogo.fHeight =TITLELOGO_Y * g_TitleLogo.fRateHeight;
	g_TitleLogo.fAngle = atan2f(g_TitleLogo.fWidth, g_TitleLogo.fHeight);
	g_TitleLogo.fLength = sqrtf(g_TitleLogo.fWidth * g_TitleLogo.fWidth + g_TitleLogo.fHeight * g_TitleLogo.fHeight);
	g_TitleLogo.bMaxSize = false;
	g_TitleLogo.bNormalSize = false;
	g_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_bFall = false;
	g_TLCnt = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title_logo.png", &g_pTextureTitleLogo);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX, // �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleLogo,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	SetVerTexTitleLogo(0);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = g_color;
	pVtx[1].col = g_color;
	pVtx[2].col = g_color;
	pVtx[3].col = g_color;

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitleLogo->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �^�C�g�����S�̏I������
//-----------------------------------------------------------------
void UninitTitlelogo(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitleLogo != NULL)
	{
		g_pVtxBuffTitleLogo->Release();
		g_pVtxBuffTitleLogo = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureTitleLogo != NULL)
	{
		g_pTextureTitleLogo->Release();
		g_pTextureTitleLogo = NULL;
	}
}

//-----------------------------------------------------------------
// �^�C�g�����S�̍X�V����
//-----------------------------------------------------------------
void UpdateTitlelogo(void)
{
	// �t�F�[�h���̎擾
	int nFade = GetFade();

	if (g_TitleLogo.bNormalSize == false)
	{
#if 1
		if (g_TitleLogo.bMaxSize == false)
		{
			// �T�C�Y�����̊����X�V
			g_TitleLogo.fRateWidth -= MOVE_RATE;
			g_TitleLogo.fRateHeight -= MOVE_RATE;

			// �T�C�Y�����ʍX�V
			g_TitleLogo.fMoveRateWidth += g_TitleLogo.fRateWidth;
			g_TitleLogo.fMoveRateHeight += g_TitleLogo.fRateHeight;

			// �T�C�Y�X�V
			g_TitleLogo.fWidth = TITLELOGO_X * g_TitleLogo.fMoveRateWidth;
			g_TitleLogo.fHeight = TITLELOGO_Y * g_TitleLogo.fMoveRateHeight;

			// 
			if ((g_TitleLogo.fWidth >= TITLELOGO_X) && (g_TitleLogo.fHeight >= TITLELOGO_Y))
			{
				g_TitleLogo.bMaxSize = true;
			}
		}
		else
		{
			// �T�C�Y�����̊����X�V
			g_TitleLogo.fRateWidth -= RATE / 30.0f;
			g_TitleLogo.fRateHeight -= RATE / 30.0f;

			// �T�C�Y�����ʍX�V
			g_TitleLogo.fMoveRateWidth += g_TitleLogo.fRateWidth;
			g_TitleLogo.fMoveRateHeight += g_TitleLogo.fRateHeight;

			// �T�C�Y�X�V
			g_TitleLogo.fWidth = TITLELOGO_X * g_TitleLogo.fMoveRateWidth;
			g_TitleLogo.fHeight = TITLELOGO_Y * g_TitleLogo.fMoveRateHeight;

			if ((g_TitleLogo.fWidth <= TITLELOGO_X) && (g_TitleLogo.fHeight <= TITLELOGO_Y))
			{
				g_TitleLogo.bNormalSize = true;
			}
		}
#else
		if (g_TitleLogo.bMaxSize == false)
		{
			// �T�C�Y�����̊����X�V
			g_TitleLogo.fRateWidth -= MOVE_RATE;
			g_TitleLogo.fRateHeight -= MOVE_RATE;

			// �T�C�Y�����ʍX�V
			g_TitleLogo.fMoveRateWidth += g_TitleLogo.fRateWidth;
			g_TitleLogo.fMoveRateHeight += g_TitleLogo.fRateHeight;

			// �T�C�Y�X�V
			g_TitleLogo.fWidth = TITLELOGO_X * g_TitleLogo.fMoveRateWidth;
			g_TitleLogo.fHeight = TITLELOGO_Y * g_TitleLogo.fMoveRateHeight;

			// 
			if ((g_TitleLogo.fMoveRateWidth >= 1.0f) && (g_TitleLogo.fMoveRateHeight >= 1.0f))
			{
				g_TitleLogo.bMaxSize = true;
			}
		}
		else
		{
			// �T�C�Y�����̊����X�V
			g_TitleLogo.fRateWidth -= RATE / 30.0f;
			g_TitleLogo.fRateHeight -= RATE / 30.0f;

			// �T�C�Y�����ʍX�V
			g_TitleLogo.fMoveRateWidth += g_TitleLogo.fRateWidth;
			g_TitleLogo.fMoveRateHeight += g_TitleLogo.fRateHeight;

			// �T�C�Y�X�V
			g_TitleLogo.fWidth = TITLELOGO_X * g_TitleLogo.fMoveRateWidth;
			g_TitleLogo.fHeight = TITLELOGO_Y * g_TitleLogo.fMoveRateHeight;

			if ((g_TitleLogo.fMoveRateWidth <= 1.0f) && (g_TitleLogo.fMoveRateHeight <= 1.0f))
			{
				g_TitleLogo.bNormalSize = true;
			}
		}
#endif 
	}
	// ���_���W�̍X�V
	SetVerTexTitleLogo(0);
}

//-----------------------------------------------------------------
// �^�C�g�����S�̕`�揈��
//-----------------------------------------------------------------
void DrawTitlelogo(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitleLogo, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	pDevice->SetTexture(0, g_pTextureTitleLogo);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//-----------------------------------------------------------------
// ���_���W�̐ݒ�
//-----------------------------------------------------------------
void SetVerTexTitleLogo(int nIdx)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

	// ���Ԗڂ̏��
	pVtx += 4 * nIdx;

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_TitleLogo.pos.x - (g_TitleLogo.fWidth / 2.0f), g_TitleLogo.pos.y - (g_TitleLogo.fHeight / 2.0f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_TitleLogo.pos.x + (g_TitleLogo.fWidth / 2.0f), g_TitleLogo.pos.y - (g_TitleLogo.fHeight / 2.0f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_TitleLogo.pos.x - (g_TitleLogo.fWidth / 2.0f), g_TitleLogo.pos.y + (g_TitleLogo.fHeight / 2.0f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_TitleLogo.pos.x + (g_TitleLogo.fWidth / 2.0f), g_TitleLogo.pos.y + (g_TitleLogo.fHeight / 2.0f), 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitleLogo->Unlock();
}

//-----------------------------------------------------------------
// �^�C�g�����S���̎擾
//-----------------------------------------------------------------
bool GetFall(void)
{
	return g_bFall;
}