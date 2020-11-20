////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �t�F�[�h�̏��� [fade.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/08/31
//
////////////////////////////////////////////////////////////////////////////////
#include "fade.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define FADE_SPEED (0.04f);

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	//���_���
FADE g_fade;									//�t�F�[�h���
MODE g_modeNext;								//�t�F�[�h�C����̃��[�h
D3DXCOLOR g_colorFade;							//�t�F�[�h�̐F

////////////////////////////////////////////////////////////////////////////////
//�t�F�[�h�̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitFade(MODE modeNext)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffFade, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

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
	
	//�F�̐ݒ�
	ColorFade();

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�t�F�[�h�̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitFade(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();	//�J��
		g_pVtxBuffFade = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�t�F�[�h�̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateFade(void)
{
	
	//�t�F�[�h�C���E�t�F�[�h�A�E�g
	switch(g_fade)
	{
	case FADE_IN:
		if (g_colorFade.a >= 0.0f)
		{
			g_colorFade.a -= FADE_SPEED;
		}
		else
		{
			g_fade = FADE_NONE;
			g_colorFade.a = 0.0f;
		}
		break;
	case FADE_OUT:
		if (g_colorFade.a <= 1.0f)
		{
			g_colorFade.a += FADE_SPEED;
		}
		else
		{
			g_fade = FADE_IN;
			SetMode(g_modeNext);
		}
		break;
	default:
		break;
	}

	//�F�̐ݒ�
	ColorFade();
}

////////////////////////////////////////////////////////////////////////////////
//�t�F�[�h�̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawFade(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

////////////////////////////////////////////////////////////////////////////////
//�t�F�[�h�̃Z�b�g����
////////////////////////////////////////////////////////////////////////////////
void SetFade(FADE fade, MODE modeNext)
{
	g_modeNext = modeNext;
	g_fade = fade;
}

////////////////////////////////////////////////////////////////////////////////
//�t�F�[�h�����I��
////////////////////////////////////////////////////////////////////////////////
void EndFade(void)
{
	switch (g_fade)
	{
	case FADE_IN:
		g_colorFade.a = 0.0f;
		break;
	case FADE_OUT:
		g_colorFade.a = 1.0f;
		break;
	default:
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////
//�t�F�[�h�̎擾
////////////////////////////////////////////////////////////////////////////////
FADE GetFade(void)
{
	return g_fade;
}

////////////////////////////////////////////////////////////////////////////////
//�t�F�[�h�̐F�ݒ�
////////////////////////////////////////////////////////////////////////////////
void ColorFade(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();
}