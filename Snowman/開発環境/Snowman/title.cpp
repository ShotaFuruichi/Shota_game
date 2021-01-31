////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �^�C�g���̏��� [title.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/10/30
//
////////////////////////////////////////////////////////////////////////////////
#include "title.h"
#include "input.h"
#include "fade.h"
#include "game.h"
#include "sound.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define BUTTON_ALPHA (1.0f)		//�{�^���̃��l����
#define BUTTON_COLOR (0.5f)		//�{�^���F�����l

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//���_���
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleGame = NULL;			//�Q�[���J�n�{�^�����_���
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleTuto = NULL;			//�`���[�g���A���{�^�����_���
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleQuit = NULL;			//�I���{�^�����_���

LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;					//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTitleGame = NULL;				//�Q�[���J�n�{�^���e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTextureTitleTuto = NULL;				//�`���[�g���A���{�^���e�N�X�`��
LPDIRECT3DTEXTURE9 g_pTextureTitleQuit = NULL;				//�I���{�^���e�N�X�`��

D3DXCOLOR g_colGame;										//�Q�[���J�n�{�^���F
D3DXCOLOR g_colTuto;										//�`���[�g���A���{�^���F
D3DXCOLOR g_colQuit;										//�I���{�^���F

int g_Menu = TITLE_MENU_GAME;								//�I�𒆂̃{�^��

////////////////////////////////////////////////////////////////////////////////
//����������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitTitle(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�ϐ��̏�����
	g_pVtxBuffTitle = NULL;
	g_pTextureTitle = NULL;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title.jpg", &g_pTextureTitle);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\start.png", &g_pTextureTitleGame);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial.png", &g_pTextureTitleTuto);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\quit.png", &g_pTextureTitleQuit);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTitle->Unlock();

	//�Q�[���J�n�{�^��
	//���
	g_colGame = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitleGame, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitleGame->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.75f, SCREEN_HEIGHT - 400, 0);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.75f, SCREEN_HEIGHT - 500, 0);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.25f, SCREEN_HEIGHT - 400, 0);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.25f, SCREEN_HEIGHT - 500, 0);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	ColorGame();

	//�e�N�X�`�����_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitleGame->Unlock();

	//�`���[�ƃ��A���{�^��
	//���
	g_colTuto = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitleTuto, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitleTuto->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.75f, SCREEN_HEIGHT - 250, 0);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.75f, SCREEN_HEIGHT - 350, 0);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.25f, SCREEN_HEIGHT - 250, 0);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.25f, SCREEN_HEIGHT - 350, 0);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	ColorTuto();

	//�e�N�X�`�����_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitleTuto->Unlock();

	//�Q�[���I���{�^��
	//���
	g_colQuit = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitleQuit, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitleQuit->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.75f, SCREEN_HEIGHT - 100, 0);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.75f, SCREEN_HEIGHT - 200, 0);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.25f, SCREEN_HEIGHT - 100, 0);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 1.25f, SCREEN_HEIGHT - 200, 0);

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
	g_pVtxBuffTitleQuit->Unlock();

	//bgm�̍Đ�
	StopSound();
	PlaySound(SOUND_LABEL_BGM000);

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�I������
////////////////////////////////////////////////////////////////////////////////
void UninitTitle(void)
{
	//�^�C�g��
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();	//�J��
		g_pVtxBuffTitle = NULL;		//������
	}

	//�e�N�X�`���̊J��
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();	//�J��
		g_pTextureTitle = NULL;		//������
	}

	//�Q�[���J�n�{�^��
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitleGame != NULL)
	{
		g_pVtxBuffTitleGame->Release();	//�J��
		g_pVtxBuffTitleGame = NULL;		//������
	}

	//�e�N�X�`���̊J��
	if (g_pTextureTitleGame != NULL)
	{
		g_pTextureTitleGame->Release();	//�J��
		g_pTextureTitleGame = NULL;		//������
	}

	//�`���[�g���A���{�^��
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitleTuto != NULL)
	{
		g_pVtxBuffTitleTuto->Release();	//�J��
		g_pVtxBuffTitleTuto = NULL;		//������
	}

	//�e�N�X�`���̊J��
	if (g_pTextureTitleTuto != NULL)
	{
		g_pTextureTitleTuto->Release();	//�J��
		g_pTextureTitleTuto = NULL;		//������
	}

	//�I���{�^��
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitleQuit != NULL)
	{
		g_pVtxBuffTitleQuit->Release();	//�J��
		g_pVtxBuffTitleQuit = NULL;		//������
	}

	//�e�N�X�`���̊J��
	if (g_pTextureTitleQuit != NULL)
	{
		g_pTextureTitleQuit->Release();	//�J��
		g_pTextureTitleQuit = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateTitle(void)
{
	//�ϐ��錾
	FADE fade;
	HWND hWnd;
	fade = GetFade();
	hWnd = GethWnd();

	if (GetKeyboardTrigger(DIK_UP) == true)
	{
		g_Menu += 2;
		PlaySound(SOUND_LABEL_SE_SELECT);
	}
	if (GetKeyboardTrigger(DIK_DOWN) == true)
	{
		g_Menu += 1;
		PlaySound(SOUND_LABEL_SE_SELECT);
	}
	g_Menu %= 3;

	switch (g_Menu)
	{
	case TITLE_MENU_GAME:
		//����������
		g_colQuit = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);
		g_colTuto = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);;
		ColorGame();
		ColorTuto();
		ColorQuit();

		//����
		g_colGame = D3DXCOLOR(1.0f, 1.0f, 1.0f, BUTTON_ALPHA);
		//if (g_colContinue.r > 1.0f || g_colContinue.r < 0.01f)
		//{
		//	g_fFlashR *= -1;
		//}

		//�Q�[����ʂɂ�����
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//��ʑJ��
			if (fade == FADE_NONE)
			{
				SetFade(FADE_OUT, MODE_GAME);
				PlaySound(SOUND_LABEL_SE_DESICION);
			}
		}
		break;

	case TITLE_MENU_TUTORIAL:

		//����������
		g_colGame = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);;
		g_colQuit = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);;
		ColorGame();
		ColorTuto();
		ColorQuit();

		//����
		g_colTuto = D3DXCOLOR(1.0f, 1.0f, 1.0f, BUTTON_ALPHA);;

		//�`���[�g���A����ʂɂ�����
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//��ʑJ��
			if (fade == FADE_NONE)
			{
				SetFade(FADE_OUT, MODE_TUTORIAL);
				PlaySound(SOUND_LABEL_SE_DESICION);
			}
		}
		break;

	case TITLE_MENU_QUIT:
		//����������
		g_colGame = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);;
		g_colTuto = D3DXCOLOR(BUTTON_COLOR, BUTTON_COLOR, BUTTON_COLOR, BUTTON_ALPHA);;
		ColorGame();
		ColorTuto();
		ColorQuit();

		//����
		g_colQuit = D3DXCOLOR(1.0f, 1.0f, 1.0f, BUTTON_ALPHA);;

		//�^�C�g���ɖ߂�
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (GetKeyboardTrigger(DIK_RETURN) == true)
			{
				DestroyWindow(hWnd);
				PlaySound(SOUND_LABEL_SE_DESICION);
			}
		}
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////
//�`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawTitle(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitle);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�R���e�B�j���[�{�^��
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitleGame, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitleGame);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�`���[�g���A���{�^��
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitleTuto, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitleTuto);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�I���{�^��
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitleQuit, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitleQuit);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

////////////////////////////////////////////////////////////////////////////////
//�Q�[���J�n�{�^�����_�J���[�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void ColorGame(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitleGame->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_colGame;
	pVtx[1].col = g_colGame;
	pVtx[2].col = g_colGame;
	pVtx[3].col = g_colGame;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitleGame->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�`���[�g���A���{�^�����_�J���[�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void ColorTuto(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitleTuto->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_colTuto;
	pVtx[1].col = g_colTuto;
	pVtx[2].col = g_colTuto;
	pVtx[3].col = g_colTuto;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitleTuto->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�I���{�^�����_�J���[�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void ColorQuit(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitleQuit->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_colQuit;
	pVtx[1].col = g_colQuit;
	pVtx[2].col = g_colQuit;
	pVtx[3].col = g_colQuit;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitleQuit->Unlock();
}