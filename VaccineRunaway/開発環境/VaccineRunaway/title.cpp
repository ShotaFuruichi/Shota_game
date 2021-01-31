////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �^�C�g����� [title.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/08/31
//
////////////////////////////////////////////////////////////////////////////////
#include "title.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "xinput_pad.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define LOGO_POSX (780)			//���S���S����̋���X
#define LOGO_POSY (360)			//���S���S����̋���Y
#define LOGO_STOP (400)			//���S�~�߂�Y���W
#define LOGO_SPEED (5)			//���S�̈ړ����x

#define SIGN_POSX (390)			//�T�C�����S����̋���X
#define SIGN_POSY (90)			//�T�C�����S����̋���Y
#define SIGN_FLASH (25)			//�T�C���_�ŃX�s�[�h

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleBg = NULL;	//�w�i�̒��_���
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleLogo = NULL;	//���S�̒��_���
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleSign = NULL;	//�T�C���̒��_���
LPDIRECT3DTEXTURE9 g_pTextureTitleSign = NULL;		//�T�C���̃e�N�X�`�����
LPDIRECT3DTEXTURE9 g_pTextureTitleBg = NULL;		//�w�i�̃e�N�X�`�����
LPDIRECT3DTEXTURE9 g_pTextureTitleLogo = NULL;		//���S�̃e�N�X�`�����
D3DXVECTOR3 g_posLogo;								//���S�̈ʒu���
D3DXVECTOR3 g_posSign;								//�T�C���̈ʒu���
int g_SignCounter;									//�T�C���J�E���^�[
bool g_bDisp;										//�T�C���_��
int g_FadeCounter;									//�t�F�[�h�܂ł̃J�E���g
int g_FlashSpeed;									//�_�ő��x
bool g_bFlash;										//�����_�ł��Ă��邩�ǂ���

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

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg00000.jpg", &g_pTextureTitleBg);		//�w�i
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\title100.png", &g_pTextureTitleLogo);	//���S
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\sign000.png", &g_pTextureTitleSign);		//�T�C��

	//������
	g_SignCounter = 1;
	g_bDisp = false;
	g_FadeCounter = 0;
	g_FlashSpeed = SIGN_FLASH;
	g_bFlash = false;

	//�w�i
	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitleBg, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitleBg->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitleBg->Unlock();

	//���S
	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitleLogo, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

	//���S�̒��S���W�̐ݒ�
	g_posLogo = D3DXVECTOR3(SCREEN_WIDTH / 2, -200.0f, 0.0f);

	//���_���W�̐ݒ�
	SetVertexLogo();

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
	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitleLogo->Unlock();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitleSign, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitleSign->Lock(0, 0, (void**)&pVtx, 0);

	//���S�̒��S���W�̐ݒ�
	g_posSign = D3DXVECTOR3(SCREEN_WIDTH / 2, 890.0f, 0.0f);

	//���_���W�̐ݒ�
	SetVertexSign();

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
	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitleSign->Unlock();

	PlaySound(SOUND_LABEL_BGM001);

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�I������
////////////////////////////////////////////////////////////////////////////////
void UninitTitle(void)
{
	StopSound();
	
	//�w�i���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitleBg != NULL)
	{
		g_pVtxBuffTitleBg->Release();	//�J��
		g_pVtxBuffTitleBg = NULL;		//������
	}
	//�w�i�e�N�X�`���̊J��
	if (g_pTextureTitleBg != NULL)
	{
		g_pTextureTitleBg->Release();	//�J��
		g_pTextureTitleBg = NULL;		//������
	}

	//���S���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitleLogo != NULL)
	{
		g_pVtxBuffTitleLogo->Release();	//�J��
		g_pVtxBuffTitleLogo = NULL;		//������
	}
	//���S�e�N�X�`���̊J��
	if (g_pTextureTitleLogo != NULL)
	{
		g_pTextureTitleLogo->Release();	//�J��
		g_pTextureTitleLogo = NULL;		//������
	}

	//�T�C�����_�o�b�t�@�̊J��
	if (g_pVtxBuffTitleSign != NULL)
	{
		g_pVtxBuffTitleSign->Release();	//�J��
		g_pVtxBuffTitleSign = NULL;		//������
	}
	//�T�C���e�N�X�`���̊J��
	if (g_pTextureTitleSign != NULL)
	{
		g_pTextureTitleSign->Release();	//�J��
		g_pTextureTitleSign = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateTitle(void)
{
	//�ϐ��錾
	FADE fade;
	XinputGamepad *pXinput = GetXinputGamepad();
	fade = GetFade();

	//���S�ړ�
	if (g_posLogo.y < LOGO_STOP)
	{
		g_posLogo.y += LOGO_SPEED;
	}
	else
	{
		//�_��
		g_SignCounter++;
		if (g_SignCounter % g_FlashSpeed == 0)
		{
			g_bDisp = g_bDisp ? false : true;
		}
	}

	//�����_�ł��n�߂���t�F�[�h�J�E���^�[
	if (g_bFlash == true)
	{
		g_FadeCounter++;
	}

	//�G���^�[�L�[���������Ƃ�
	if (GetKeyboardTrigger(DIK_RETURN) == true || pXinput->bPressStart == true || pXinput->bPressA)
	{
		if (g_posLogo.y == LOGO_STOP)
		{
			if (g_bFlash == false)
			{
				g_FlashSpeed /= 6;
			}
			g_bFlash = true;
		}
		else
		{
			g_posLogo.y = LOGO_STOP;
		}	
	}

	//�����_�ł��Ă���1�b��t�F�[�h�A�E�g
	if (g_FadeCounter > 60)
	{
		if (fade == FADE_NONE)
		{
			SetFade(FADE_OUT, MODE_TUTORIAL);
		}
	}

	//���S�̒��_���W�̐ݒ�
	SetVertexLogo();

	//�T�C���̒��_���W�̐ݒ�
	SetVertexSign();
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
	
	//�w�i
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitleBg, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitleBg);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���S
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitleLogo, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitleLogo);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�T�C��
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitleSign, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTitleSign);

	if (g_bDisp == true)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

////////////////////////////////////////////////////////////////////////////////
//���S�̒��_���W�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetVertexLogo(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitleLogo->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posLogo.x - LOGO_POSX, g_posLogo.y + LOGO_POSY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posLogo.x - LOGO_POSX, g_posLogo.y - LOGO_POSY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posLogo.x + LOGO_POSX, g_posLogo.y + LOGO_POSY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posLogo.x + LOGO_POSX, g_posLogo.y - LOGO_POSY, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitleLogo->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�T�C���̒��_���W�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetVertexSign(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitleSign->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posSign.x - SIGN_POSX, g_posSign.y + SIGN_POSY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posSign.x - SIGN_POSX, g_posSign.y - SIGN_POSY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posSign.x + SIGN_POSX, g_posSign.y + SIGN_POSY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posSign.x + SIGN_POSX, g_posSign.y - SIGN_POSY, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitleSign->Unlock();
}