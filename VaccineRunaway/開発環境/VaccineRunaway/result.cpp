////////////////////////////////////////////////////////////////////////////////
//
//Contents	: ���U���g��ʂ̏��� [result.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/08/31
//
////////////////////////////////////////////////////////////////////////////////
#include "result.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "score.h"
#include "highscore.h"
#include "sound.h"
#include "xinput_pad.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define HIGHSCORE_POSX (585.0f)	//�n�C�X�R�A�̒��S����̋���X
#define HIGHSCORE_POSY (135.0f)	//�n�C�X�R�A�̒��S����̋���Y
#define EXPAND_RESULTX (8.6f)	//���U���g�̒��S����̍L����̑���X
#define EXPAND_RESULTY (2.0f)	//���U���g�̒��S����̍L����̑���Y

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultBg = NULL;			//���U���g�w�i���_���
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultHighscore = NULL;	//���U���g�N���A���_���
LPDIRECT3DTEXTURE9 g_pTextureResultBg = NULL;				//���U���g�w�i�e�N�X�`�����
LPDIRECT3DTEXTURE9 g_pTextureResultHighscore = NULL;		//���U���g�N���A�e�N�X�`�����
D3DXVECTOR3 g_posHighscore;									//�n�C�X�R�A�̈ʒu
float g_fLengthX;											//���S����̒���x
float g_fLengthY;											//���S����̒���y

////////////////////////////////////////////////////////////////////////////////
//����������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitResult(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg.jpg", &g_pTextureResultBg);				//���U���g�w�i�e�N�X�`��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\highscore.png", &g_pTextureResultHighscore);		//���U���g�n�C�X�R�A�e�N�X�`��

	//�w�i
	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffResultBg, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResultBg->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffResultBg->Unlock();

	//�n�C�X�R�A
	g_posHighscore = D3DXVECTOR3(SCREEN_WIDTH / 2, 400.0f, 0.0f);
	g_fLengthX = 0.0f;
	g_fLengthY = 0.0f;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffResultHighscore, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResultHighscore->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	SetVertexHighscore();

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
	g_pVtxBuffResultHighscore->Unlock();

	PlaySound(SOUND_LABEL_BGM000);

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�I������
////////////////////////////////////////////////////////////////////////////////
void UninitResult(void)
{
	UninitScore();

	StopSound();

	//�w�i
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffResultBg != NULL)
	{
		g_pVtxBuffResultBg->Release();	//�J��
		g_pVtxBuffResultBg = NULL;		//������
	}
	//�e�N�X�`���̊J��
	if (g_pTextureResultBg != NULL)
	{
		g_pTextureResultBg->Release();	//�J��
		g_pTextureResultBg = NULL;		//������
	}
	
	//�n�C�X�R�A
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffResultHighscore != NULL)
	{
		g_pVtxBuffResultHighscore->Release();	//�J��
		g_pVtxBuffResultHighscore = NULL;		//������
	}
	//�e�N�X�`���̊J��
	if (g_pTextureResultHighscore != NULL)
	{
		g_pTextureResultHighscore->Release();	//�J��
		g_pTextureResultHighscore = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateResult(void)
{
	//�ϐ��錾
	FADE fade = GetFade();
	PLAYER *pPlayer = GetPlayer();
	XinputGamepad *pXinput = GetXinputGamepad();

	if (g_fLengthX < HIGHSCORE_POSX)
	{
		g_fLengthX += EXPAND_RESULTX;
	}
	if (g_fLengthY < HIGHSCORE_POSY)
	{
		g_fLengthY += EXPAND_RESULTY;
	}

	UpdateHighScore();
	AddHighScore();

	//���_���W�̐ݒ�
	SetVertexHighscore();

	//��ʑJ��
	if (fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || pXinput->bPressStart == true || pXinput->bPressA)
		{
			SetFade(FADE_OUT, MODE_TITLE);
		}
	}
	UpdateScore();
	AddScore(0);
}

////////////////////////////////////////////////////////////////////////////////
//�`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawResult(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�w�i
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResultBg, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResultBg);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�n�C�X�R�A
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResultHighscore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResultHighscore);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	DrawScore();

	DrawHighScore();
}

////////////////////////////////////////////////////////////////////////////////
//�n�C�X�R�A�̒��_���W�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetVertexHighscore(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResultHighscore->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posHighscore.x - g_fLengthX, g_posHighscore.y + g_fLengthY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posHighscore.x - g_fLengthX, g_posHighscore.y - g_fLengthY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posHighscore.x + g_fLengthX, g_posHighscore.y + g_fLengthY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posHighscore.x + g_fLengthX, g_posHighscore.y - g_fLengthY, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResultHighscore->Unlock();
}