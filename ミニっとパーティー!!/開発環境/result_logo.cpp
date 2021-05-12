//-----------------------------------------------------------------
//
// ���U���g�w�i (result_bg.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "result_logo.h"
#include "player.h"
#include "chara_select_frame.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MAX_PATTERN			(4)							// �w�i�̎��
#define MAX_TEXTURE			(6)							// �w�i�̎��

#define RESULT_BG_X			(SCREEN_WIDTH / 2)			// �^�C�g���w�i�̈ʒu(X���W)
#define RESULT_BG_Y			(SCREEN_HEIGHT / 2)			// �^�C�g���w�i�̈ʒu(Y���W)
#define RESULT_BG_WIDTH		(300.0f)				// �^�C�g���w�i�̕�
#define RESULT_BG_HEIGHT	(130.0f)				// �^�C�g���w�i�̍���

#define RESULT_PLAYER_SIZE		(150.0f)				// �^�C�g���w�i�̕�

//-----------------------------------------------------------------
// �\���̂̒�`
//-----------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	float fWidth;		// ��
	float fHeight;		// ����
	int nTexType;		// �\��e�N�X�`���̎��
}ResultLogo;

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultLogo = NULL;				// �w�i�̒��_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureresultLogo[MAX_TEXTURE] = {};			// �w�i�̃e�N�X�`���̃|�C���^
ResultLogo g_ResultLogo[MAX_PATTERN];
int g_nNumLogo;

//-----------------------------------------------------------------
// ���U���g���S�̏���������
//-----------------------------------------------------------------
HRESULT InitResultLogo(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n���A������
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_1.png", &g_pTextureresultLogo[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_2.png", &g_pTextureresultLogo[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_3.png", &g_pTextureresultLogo[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_4.png", &g_pTextureresultLogo[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/win_logo.png", &g_pTextureresultLogo[4]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/draw_logo.png", &g_pTextureresultLogo[5]);

	// �v���C���[���̎擾
	Player *pPlayer = GetPlayer();
	int nNumFrame = GetFrame();
	g_nNumLogo = 1;

	for (int nCntPlayer = 0; nCntPlayer < nNumFrame; nCntPlayer++, pPlayer++)
	{
		if (pPlayer->bFall == false)
		{
			g_nNumLogo++;
			g_ResultLogo[g_nNumLogo - 2].nTexType = nCntPlayer;
		}
	}
	if (g_nNumLogo == 1 || g_nNumLogo == (nNumFrame + 1))
	{
		g_ResultLogo[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 500.0f, 0.0f);
		g_ResultLogo[0].fWidth = RESULT_BG_WIDTH;
		g_ResultLogo[0].fHeight = RESULT_BG_HEIGHT;
		g_ResultLogo[0].nTexType = 5;
		g_nNumLogo = 1;
	}
	else
	{
		for (int nCntLogo = 0; nCntLogo < g_nNumLogo - 1; nCntLogo++)
		{
			g_ResultLogo[nCntLogo].pos = D3DXVECTOR3(SCREEN_WIDTH / 2.0f + (nCntLogo * 150.0f) - (100.0f * g_nNumLogo), 500.0f, 0.0f);
			g_ResultLogo[nCntLogo].fWidth = RESULT_PLAYER_SIZE;
			g_ResultLogo[nCntLogo].fHeight = RESULT_PLAYER_SIZE;
		}
		g_ResultLogo[g_nNumLogo - 1].pos = D3DXVECTOR3(g_ResultLogo[g_nNumLogo - 2].pos.x + 300.0f, 500.0f, 0.0f);
		g_ResultLogo[g_nNumLogo - 1].fWidth = RESULT_BG_WIDTH;
		g_ResultLogo[g_nNumLogo - 1].fHeight = RESULT_BG_HEIGHT;
		g_ResultLogo[g_nNumLogo - 1].nTexType = 4;
	}

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX * g_nNumLogo,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultLogo,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResultLogo->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntResultLogo = 0; nCntResultLogo < g_nNumLogo; nCntResultLogo++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_ResultLogo[nCntResultLogo].pos.x - (g_ResultLogo[nCntResultLogo].fWidth / 2), g_ResultLogo[nCntResultLogo].pos.y + (g_ResultLogo[nCntResultLogo].fHeight / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_ResultLogo[nCntResultLogo].pos.x - (g_ResultLogo[nCntResultLogo].fWidth / 2), g_ResultLogo[nCntResultLogo].pos.y - (g_ResultLogo[nCntResultLogo].fHeight / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_ResultLogo[nCntResultLogo].pos.x + (g_ResultLogo[nCntResultLogo].fWidth / 2), g_ResultLogo[nCntResultLogo].pos.y + (g_ResultLogo[nCntResultLogo].fHeight / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_ResultLogo[nCntResultLogo].pos.x + (g_ResultLogo[nCntResultLogo].fWidth / 2), g_ResultLogo[nCntResultLogo].pos.y - (g_ResultLogo[nCntResultLogo].fHeight / 2), 0.0f);


		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���̍X�V
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResultLogo->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// ���U���g���S�̏I������
//-----------------------------------------------------------------
void UninitResultLogo(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffResultLogo != NULL)
	{
		g_pVtxBuffResultLogo->Release();
		g_pVtxBuffResultLogo = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCntBg = 0; nCntBg < MAX_TEXTURE; nCntBg++)
	{
		if (g_pTextureresultLogo[nCntBg] != NULL)
		{
			g_pTextureresultLogo[nCntBg]->Release();
			g_pTextureresultLogo[nCntBg] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// ���U���g���S�̍X�V����
//-----------------------------------------------------------------
void UpdateResultLogo(void)
{

}

//-----------------------------------------------------------------
// ���U���g���S�̕`�揈��
//-----------------------------------------------------------------
void DrawResultLogo(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResultLogo, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntBg = 0; nCntBg < g_nNumLogo; nCntBg++)
	{
		pDevice->SetTexture(0, g_pTextureresultLogo[g_ResultLogo[nCntBg].nTexType]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBg * 4, 2);
	}
}