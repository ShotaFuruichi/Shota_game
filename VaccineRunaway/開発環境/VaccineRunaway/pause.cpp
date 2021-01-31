////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �|�[�Y��ʂ̏��� [pause.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/09/08
//
////////////////////////////////////////////////////////////////////////////////
#include "pause.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "xinput_pad.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define BG_ALPHA (150)			//�w�i�̃��l
#define BUTTON_ALPHA (1.0f)		//�{�^���̃��l����
#define BUTTON_COLOR (0.0f)		//�{�^���F�����l

#define MENU_POSX (250)			//���j���[��ʒ��S����̋���X
#define MENU_POSY (350)			//���j���[��ʒ��S����̋���Y
#define BUTTON_X (200)			//���j���[��ʒ��S����̃{�^������X

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseBg = NULL;			//�w�i���_���
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseMenu = NULL;			//���j���[���_���
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;				//�|�[�Y���_���
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseContinue = NULL;		//�R���e�B�j���[�{�^�����_���
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseRetry = NULL;		//���g���C�{�^�����_���
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseQuit = NULL;			//�I���{�^�����_���
LPDIRECT3DTEXTURE9 g_pTexturePause = NULL;					//�|�[�Y�e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTexturePauseMenu = NULL;				//���j���[�e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTexturePauseContinue = NULL;			//�R���e�B�j���[�{�^���e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTexturePauseRetry = NULL;				//���g���C�{�^���e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTexturePauseQuit = NULL;				//�I���{�^���e�N�X�`��

D3DXVECTOR3 g_posMenu;										//���j���[���S���W
D3DXCOLOR g_colContinue;									//�R���e�B�j���[�{�^���F
D3DXCOLOR g_colRetry;										//���g���C�{�^���F
D3DXCOLOR g_colQuit;										//�I���{�^���F

int g_Menu = PAUSE_MENU_CONTINUE;							//�I�𒆂̃{�^��

////////////////////////////////////////////////////////////////////////////////
//�|�[�Y��ʂ̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitPause(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\menu.jpg", &g_pTexturePauseMenu);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\pause.png", &g_pTexturePause);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\continue.png", &g_pTexturePauseContinue);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\retry.png", &g_pTexturePauseRetry);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\quit.png", &g_pTexturePauseQuit);

	//�w�i
	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPauseBg, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseBg->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, BG_ALPHA);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, BG_ALPHA);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, BG_ALPHA);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, BG_ALPHA);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseBg->Unlock();

	//���j���[���
	//���
	g_posMenu = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPauseMenu, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posMenu.x - MENU_POSX, g_posMenu.y + MENU_POSY, 0);
	pVtx[1].pos = D3DXVECTOR3(g_posMenu.x - MENU_POSX, g_posMenu.y - MENU_POSY, 0);
	pVtx[2].pos = D3DXVECTOR3(g_posMenu.x + MENU_POSX, g_posMenu.y + MENU_POSY, 0);
	pVtx[3].pos = D3DXVECTOR3(g_posMenu.x + MENU_POSX, g_posMenu.y - MENU_POSY, 0);

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

	//�e�N�X�`�����_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseBg->Unlock();

	//�|�[�Y
	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPause, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posMenu.x - BUTTON_X, g_posMenu.y - 200, 0);
	pVtx[1].pos = D3DXVECTOR3(g_posMenu.x - BUTTON_X, g_posMenu.y - 300, 0);
	pVtx[2].pos = D3DXVECTOR3(g_posMenu.x + BUTTON_X, g_posMenu.y - 200, 0);
	pVtx[3].pos = D3DXVECTOR3(g_posMenu.x + BUTTON_X, g_posMenu.y - 300, 0);

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

	//�e�N�X�`�����_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

	//�R���e�B�j���[�{�^��
	//���
	g_colContinue = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPauseContinue, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseContinue->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posMenu.x - BUTTON_X, g_posMenu.y - 50, 0);
	pVtx[1].pos = D3DXVECTOR3(g_posMenu.x - BUTTON_X, g_posMenu.y - 150, 0);
	pVtx[2].pos = D3DXVECTOR3(g_posMenu.x + BUTTON_X, g_posMenu.y - 50, 0);
	pVtx[3].pos = D3DXVECTOR3(g_posMenu.x + BUTTON_X, g_posMenu.y - 150, 0);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	ColorContinue();

	//�e�N�X�`�����_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseContinue->Unlock();

	//���g���C�{�^��
	//���
	g_colRetry = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPauseRetry, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseRetry->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posMenu.x - BUTTON_X, g_posMenu.y + 125, 0);
	pVtx[1].pos = D3DXVECTOR3(g_posMenu.x - BUTTON_X, g_posMenu.y + 25, 0);
	pVtx[2].pos = D3DXVECTOR3(g_posMenu.x + BUTTON_X, g_posMenu.y + 125, 0);
	pVtx[3].pos = D3DXVECTOR3(g_posMenu.x + BUTTON_X, g_posMenu.y + 25, 0);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	ColorRetry();

	//�e�N�X�`�����_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseRetry->Unlock();

	//�I���{�^��
	//���
	g_colQuit = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPauseQuit, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseQuit->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posMenu.x - BUTTON_X, g_posMenu.y + 300, 0);
	pVtx[1].pos = D3DXVECTOR3(g_posMenu.x - BUTTON_X, g_posMenu.y + 200, 0);
	pVtx[2].pos = D3DXVECTOR3(g_posMenu.x + BUTTON_X, g_posMenu.y + 300, 0);
	pVtx[3].pos = D3DXVECTOR3(g_posMenu.x + BUTTON_X, g_posMenu.y + 200, 0);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	ColorQuit();

	//�e�N�X�`�����_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseQuit->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�|�[�Y��ʂ̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitPause(void)
{
	//�w�i���_�o�b�t�@�̊J��
	if (g_pVtxBuffPauseBg != NULL)
	{
		g_pVtxBuffPauseBg->Release();	//�J��
		g_pVtxBuffPauseBg = NULL;		//������
	}

	//���j���[��ʒ��_�o�b�t�@�̊J��
	if (g_pVtxBuffPauseMenu != NULL)
	{
		g_pVtxBuffPauseMenu->Release();	//�J��
		g_pVtxBuffPauseMenu = NULL;		//������
	}

	//�|�[�Y���_�o�b�t�@�̊J��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();	//�J��
		g_pVtxBuffPause = NULL;		//������
	}

	//�R���e�B�j���[�{�^�����_�o�b�t�@�̊J��
	if (g_pVtxBuffPauseContinue != NULL)
	{
		g_pVtxBuffPauseContinue->Release();	//�J��
		g_pVtxBuffPauseContinue = NULL;		//������
	}

	//���g���C�{�^�����_�o�b�t�@�̊J��
	if (g_pVtxBuffPauseRetry != NULL)
	{
		g_pVtxBuffPauseRetry->Release();	//�J��
		g_pVtxBuffPauseRetry = NULL;		//������
	}

	//�I���{�^�����_�o�b�t�@�̊J��
	if (g_pVtxBuffPauseQuit != NULL)
	{
		g_pVtxBuffPauseQuit->Release();	//�J��
		g_pVtxBuffPauseQuit = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�|�[�Y��ʂ̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdatePause(void)
{
	//�ϐ��錾
	FADE fade = GetFade();
	XinputGamepad *pXinput = GetXinputGamepad();

	if (GetKeyboardTrigger(DIK_UP) == true || pXinput->bPressUP == true)
	{
		g_Menu += 2;
	}
	if (GetKeyboardTrigger(DIK_DOWN) == true || pXinput->bPressDOWN == true)
	{
		g_Menu += 1;
	}
	g_Menu %= 3;

	switch (g_Menu)
	{
	case PAUSE_MENU_CONTINUE:
		//����������
		g_colQuit = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);
		g_colRetry = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);;
		ColorContinue();
		ColorRetry();
		ColorQuit();

		//����
		g_colContinue = D3DXCOLOR(1.0f, 1.0f, 1.0f, BUTTON_ALPHA);
	

		//�Q�[���ɖ߂�
		if (GetKeyboardTrigger(DIK_RETURN) == true || pXinput->bPressA == true)
		{
			SetPause(false);
		}
		break;

	case PAUSE_MENU_RETRY:

		//����������
		g_colContinue = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);;
		g_colQuit = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);;
		ColorContinue();
		ColorRetry();
		ColorQuit();
		
		//����
		g_colRetry = D3DXCOLOR(1.0f, 1.0f, 1.0f, BUTTON_ALPHA);;

		//�Q�[����ʂ��烊�g���C
		if (GetKeyboardTrigger(DIK_RETURN) == true || pXinput->bPressA == true)
		{
			//��ʑJ��
			if (fade == FADE_NONE)
			{
				SetFade(FADE_OUT, MODE_GAME);
			}
			SetPause(false);
			g_Menu = PAUSE_MENU_CONTINUE;
		}
		break;

	case PAUSE_MENU_QUIT:
		//����������
		g_colContinue = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);;
		g_colRetry = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);;
		ColorContinue();
		ColorRetry();
		ColorQuit();

		//����
		g_colQuit = D3DXCOLOR(1.0f, 1.0f, 1.0f, BUTTON_ALPHA);;
		
		//�^�C�g���ɖ߂�
		if (GetKeyboardTrigger(DIK_RETURN) == true || pXinput->bPressA == true)
		{
			//��ʑJ��
			if (fade == FADE_NONE)
			{
				SetFade(FADE_OUT, MODE_TITLE);
			}
			SetPause(false);
			g_Menu = PAUSE_MENU_CONTINUE;
		}
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////
//�|�[�Y��ʂ̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawPause(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�w�i
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseBg, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���j���[���
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseMenu, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePauseMenu);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�|�[�Y
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePause);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�R���e�B�j���[�{�^��
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseContinue, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePauseContinue);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���g���C�{�^��
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseRetry, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePauseRetry);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�I���{�^��
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseQuit, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePauseQuit);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

////////////////////////////////////////////////////////////////////////////////
//�R���e�B�j���[�{�^�����_�J���[�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void ColorContinue(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseContinue->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_colContinue;
	pVtx[1].col = g_colContinue;
	pVtx[2].col = g_colContinue;
	pVtx[3].col = g_colContinue;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseContinue->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//���g���C�{�^�����_�J���[�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void ColorRetry(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseRetry->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_colRetry;
	pVtx[1].col = g_colRetry;
	pVtx[2].col = g_colRetry;
	pVtx[3].col = g_colRetry;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseRetry->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�I���{�^�����_�J���[�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void ColorQuit(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseQuit->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_colQuit;
	pVtx[1].col = g_colQuit;
	pVtx[2].col = g_colQuit;
	pVtx[3].col = g_colQuit;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseQuit->Unlock();
}