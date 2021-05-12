//-----------------------------------------------------------------
//
// �^�C�}�[�w�i (timer_bg.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "timer_bg.h"
#include "sound.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define TIMERBG_X				(SCREEN_WIDTH / 2.0f)	// �}���`���[�h�̃^�C�}�[�̒��S���W(X)
#define TIMERBG_Y				(60.0f)					// �}���`���[�h�̃^�C�}�[�̒��S���W(Y)

#define TIMERBG_WIDTH			(200.0f)					// �^�C�}�[�̕�
#define TIMERBG_HEIGHT			(80.0f)					// �^�C�}�[�̍���

#define MAX_PATTERN				(1)						// �A�j���[�V�����p�^�[��No.�̍ő吔

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimerBg = NULL;	// �^�C�}�[�̃e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTimerBg = NULL;		// �^�C�}�[�̒��_�o�b�t�@�̃|�C���^
D3DXVECTOR3 g_posTimerBg;							// �^�C�}�[�̒��S���W

//-----------------------------------------------------------------
// �^�C�}�[�w�i�̏���������
//-----------------------------------------------------------------
HRESULT InitTimerBg(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/time.png", &g_pTextureTimerBg);

	// �ϐ��̏�����
	g_posTimerBg = D3DXVECTOR3(TIMERBG_X, TIMERBG_Y, 0.0f);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * MAX_PATTERN, // �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimerBg,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimerBg->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posTimerBg.x - (TIMERBG_WIDTH / 2), g_posTimerBg.y + (TIMERBG_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posTimerBg.x - (TIMERBG_WIDTH / 2), g_posTimerBg.y - (TIMERBG_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posTimerBg.x + (TIMERBG_WIDTH / 2), g_posTimerBg.y + (TIMERBG_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posTimerBg.x + (TIMERBG_WIDTH / 2), g_posTimerBg.y - (TIMERBG_HEIGHT / 2), 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	// �e�N�X�`���̍X�V
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimerBg->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �^�C�}�[�w�i�̏I������
//-----------------------------------------------------------------
void UninitTimerBg(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTimerBg != NULL)
	{
		g_pVtxBuffTimerBg->Release();
		g_pVtxBuffTimerBg = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureTimerBg != NULL)
	{
		g_pTextureTimerBg->Release();
		g_pTextureTimerBg = NULL;
	}
}

//-----------------------------------------------------------------
// �^�C�}�[�w�i�̍X�V����
//-----------------------------------------------------------------
void UpdateTimerBg(void)
{

}

//-----------------------------------------------------------------
// �^�C�}�[�w�i�̕`�揈��
//-----------------------------------------------------------------
void DrawTimerBg(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimerBg, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�ƕ`��
	for (int nCntTimer = 0; nCntTimer < MAX_PATTERN; nCntTimer++)
	{// �X�R�A�̕\��
		pDevice->SetTexture(0, g_pTextureTimerBg);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTimer * 4, 2);
	}
}