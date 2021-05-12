//-----------------------------------------------------------------
//
// �|�[�Y (pause.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "Select_Mode.h"
#include "loadscreen.h"
#include "game.h"
#include "fade.h"
#include "input.h"
#include "gamepad.h"
#include "sound.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MAX_PATTERN				(5)					// �A�j���[�V�����p�^�[��No.�̍ő吔

#define PAUSE_MENU_BG_X			(SCREEN_WIDTH / 2)	// �|�[�Y���j���[�̒��S���WX
#define PAUSE_MENU_BG_Y			(370.0f)			// �|�[�Y���j���[�̒��S���WY
#define PAUSE_MENU_BG_WIDTH		(400.0f)			// �|�[�Y���j���[�̕�
#define PAUSE_MENU_BG_HEIGHT	(400.0f)			// �|�[�Y���j���[�̍���

#define LOGO_X					(SCREEN_WIDTH / 2)	// ���S�̒��S���WX(���ׂċ���)
#define LOGO_Y					(310.0f)			// ���S�̒��S���WY(���ׂċ���)
#define LOGO_WIDTH				(280.0f)			// ���S�̕�(���ׂċ���)
#define LOGO_HEIGHT				(70.0f)				// ���S�̍���(���ׂċ���)

#define ALUFA_INTERBAL			(10)				// �_�ł̃C���^�[�o��

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelectMode = NULL;			// �|�[�Y��ʂ̒��_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureSelectMode[MAX_PATTERN] = {};	// �|�[�Y��ʂ̃e�N�X�`���̃|�C���^
D3DXCOLOR g_Selectcol;									// �|�[�Y��ʂ̐F
int g_nSelectCnt;										// �ǂ̃��[�h��I��ł��邩
int g_nMoveSelectAlufaCnt;
bool g_bDraw;

//-----------------------------------------------------------------
// �|�[�Y�̏���������
//-----------------------------------------------------------------
HRESULT InitSelectMode(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// �ϐ��̏�����
	g_nSelectCnt = PAUSE_MENU_CONTINUE;
	g_Selectcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_nMoveSelectAlufaCnt = 0;
	g_bDraw = false;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause_menu_bg.png", &g_pTextureSelectMode[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/continue_logo.png", &g_pTextureSelectMode[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/chara_select_logo.png", &g_pTextureSelectMode[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/quit_logo.png", &g_pTextureSelectMode[4]);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * MAX_PATTERN, // �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelectMode,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSelectMode->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < MAX_PATTERN; nCntPause++)
	{
		// ���_���W�̐ݒ�
		SetVertexSelectMode(nCntPause);

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

		// ���̍X�V
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelectMode->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �|�[�Y�̏I������
//-----------------------------------------------------------------
void UninitSelectMode(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffSelectMode != NULL)
	{
		g_pVtxBuffSelectMode->Release();
		g_pVtxBuffSelectMode = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCntPause = 0; nCntPause < MAX_PATTERN; nCntPause++)
	{
		if (g_pTextureSelectMode[nCntPause] != NULL)
		{
			g_pTextureSelectMode[nCntPause]->Release();
			g_pTextureSelectMode[nCntPause] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// �|�[�Y�̍X�V����
//-----------------------------------------------------------------
void UpdateSelectMode(void)
{
	// �ϐ��錾
	bool *pStick = GetStickTrigger(PLAYER_1);
	bool *pCrossKey = GetCrossKeyTrigger(PLAYER_1);

	if (g_bDraw == false)
	{
		if (GetJoypadTrigger(PLAYER_1, JPINFO_OKorJUMP) == true)
		{
			g_bDraw = true;
		}
	}
	else
	{
		// JOYPAD �̏���
		if (pStick[STICKTRIGGER_UP] == true ||
			pCrossKey[CROSSKEYPRESS_UP] == true ||
			GetKeyboardTrigger(KEYINFO_UP) == true)
		{// ���̏��̊m��
			g_nSelectCnt--;

			if (g_nSelectCnt < PAUSE_MENU_CONTINUE)
			{// 0��菬�����Ȃ����Ƃ��X�V
				g_nSelectCnt = PAUSE_MENU_QUIT;
			}
			// SE
			PlaySound(SOUND_LABEL_SE_CURSOR);
		}
		if (pStick[STICKTRIGGER_DOWN] == true ||
			pCrossKey[CROSSKEYPRESS_DOWN] == true ||
			GetKeyboardTrigger(KEYINFO_DOWN) == true)
		{// ���̏��̊m��
			g_nSelectCnt++;

			if (g_nSelectCnt > PAUSE_MENU_QUIT)
			{// 2���傫���Ȃ����Ƃ��X�V
				g_nSelectCnt = PAUSE_MENU_CONTINUE;
			}
			// SE
			PlaySound(SOUND_LABEL_SE_CURSOR);
		}
		// �ǂ̏��ŉ�������
		if (GetJoypadTrigger(PLAYER_1, JPINFO_OKorJUMP) == true ||
			GetKeyboardTrigger(KEYINFO_OK) == true)
		{
			if (g_nSelectCnt == PAUSE_MENU_CONTINUE)
			{// �R���e�B�j���[
				SetFade(FADE_OUT, MODE_GAME);
				// SE
				PlaySound(SOUND_LABEL_SE_DICIDE);
			}
			else if (g_nSelectCnt == PAUSE_MENU_RETRY)
			{// ���g���C
				SetFade(FADE_OUT, MODE_CHARASELECT);
				// SE
				PlaySound(SOUND_LABEL_SE_DICIDE);
			}
			else if (g_nSelectCnt == PAUSE_MENU_QUIT)
			{// �N�C�b�g
				SetFade(FADE_OUT, MODE_TITLE);
				// SE
				PlaySound(SOUND_LABEL_SE_DICIDE);
			}
		}
		if (GetJoypadTrigger(PLAYER_1, JPINFO_CANCEL) == true)
		{
			g_bDraw = false;
		}
	}
	// ���_���W�̍X�V
	for (int nCnt = 0; nCnt < MAX_PATTERN; nCnt++)
	{
		SetVertexSelectMode(nCnt);
	}
}

//-----------------------------------------------------------------
// �|�[�Y�̕`�揈��
//-----------------------------------------------------------------
void DrawSelectMode(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSelectMode, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	if (g_bDraw == true)
	{
		for (int nCntPause = 0; nCntPause < MAX_PATTERN; nCntPause++)
		{
			pDevice->SetTexture(0, g_pTextureSelectMode[nCntPause]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);
		}
	}
}

//-----------------------------------------------------------------
// �|�[�Y�̒��_���W�̐ݒ�
//-----------------------------------------------------------------
void SetVertexSelectMode(int nCntPause)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSelectMode->Lock(0, 0, (void**)&pVtx, 0);

	// ���Ԗڂ�
	pVtx += nCntPause * 4;
	if (nCntPause == 0)
	{// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	}
	else if (nCntPause == 1)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(PAUSE_MENU_BG_X - PAUSE_MENU_BG_WIDTH / 2, PAUSE_MENU_BG_Y + PAUSE_MENU_BG_HEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(PAUSE_MENU_BG_X - PAUSE_MENU_BG_WIDTH / 2, PAUSE_MENU_BG_Y - PAUSE_MENU_BG_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(PAUSE_MENU_BG_X + PAUSE_MENU_BG_WIDTH / 2, PAUSE_MENU_BG_Y + PAUSE_MENU_BG_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(PAUSE_MENU_BG_X + PAUSE_MENU_BG_WIDTH / 2, PAUSE_MENU_BG_Y - PAUSE_MENU_BG_HEIGHT / 2, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (nCntPause >= 2 && nCntPause < 5)
	{
		SelectMenu(nCntPause);
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelectMode->Unlock();
}

//-----------------------------------------------------------------
// �|�[�Y���j���[
//-----------------------------------------------------------------
void SelectMenu(int nCnt)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSelectMode->Lock(0, 0, (void**)&pVtx, 0);

	// �ϐ��錾
	float fPosY = 80;

	pVtx += 4 * nCnt;
	fPosY *= nCnt - 2;

	// ���_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(LOGO_X - (LOGO_WIDTH / 2), LOGO_Y + fPosY + (LOGO_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(LOGO_X - (LOGO_WIDTH / 2), LOGO_Y + fPosY - (LOGO_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(LOGO_X + (LOGO_WIDTH / 2), LOGO_Y + fPosY + (LOGO_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(LOGO_X + (LOGO_WIDTH / 2), LOGO_Y + fPosY - (LOGO_HEIGHT / 2), 0.0f);

	if (g_nSelectCnt == (nCnt - 2) % PAUSE_MENU_MAX)
	{// �I�΂�Ă���Ƃ��_�łɂ���
		g_Selectcol.a = 1.0f;
	}
	else
	{// �I�΂�Ă��Ȃ��Ƃ��������ɂ���
		g_Selectcol.a = 0.2f;
	}
	// ���_�J���[�̐ݒ�
	pVtx[0].col = g_Selectcol;
	pVtx[1].col = g_Selectcol;
	pVtx[2].col = g_Selectcol;
	pVtx[3].col = g_Selectcol;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelectMode->Unlock();
}