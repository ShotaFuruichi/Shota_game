////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �`���[�g���A���̏��� [tutorial.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/10/06
//
////////////////////////////////////////////////////////////////////////////////
#include "tutorial.h"
#include "fade.h"
#include "input.h"

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;	//���_���
LPDIRECT3DTEXTURE9 g_pTextureTutorial = NULL;			//�e�N�X�`�����

////////////////////////////////////////////////////////////////////////////////
//�w�i�̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitTutorial(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial1.jpg", &g_pTextureTutorial);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTutorial, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffTutorial->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�w�i�̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitTutorial(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();	//�J��
		g_pVtxBuffTutorial = NULL;		//������
	}

	//�e�N�X�`���̊J��
	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();	//�J��
		g_pTextureTutorial = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�w�i�̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateTutorial(void)
{
	FADE fade;
	fade = GetFade();

	//��ʑJ��
	if (fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			SetFade(FADE_OUT, MODE_GAME);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�w�i�̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawTutorial(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTutorial);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}