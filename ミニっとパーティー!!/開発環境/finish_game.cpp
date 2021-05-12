//-----------------------------------------------------------------
//
// �t�B�j�b�V���Q�[�� (finish_game.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "finish_game.h"
#include "timer.h"
#include "sound.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define FINISHGAME_X		(SCREEN_WIDTH / 2.0f)		// �t�B�j�b�V���Q�[���̒��S���W(X)
#define FINISHGAME_Y		(SCREEN_HEIGHT / 2.0f)		// �t�B�j�b�V���Q�[���̒��S���W(Y)
#define FINISHGAME_WIDTH	(320.0f)					// �t�B�j�b�V���Q�[���̕�
#define FINISHGAME_HEIGHT	(90.0f)						// �t�B�j�b�V���Q�[���̍���

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFinishGame = NULL;	// �t�B�j�b�V���Q�[���̃e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureFinishGame = NULL;			// �t�B�j�b�V���Q�[���̒��_�o�b�t�@�̃|�C���^
FinishGame g_FinishGame;								// �t�B�j�b�V���Q�[���̏��

//-----------------------------------------------------------------
// �t�B�j�b�V���Q�[���̏���������
//-----------------------------------------------------------------
HRESULT InitFinishGame(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/timeup_logo.png", &g_pTextureFinishGame);

	// �ϐ��̏�����
	g_FinishGame.pos = D3DXVECTOR3(FINISHGAME_X, FINISHGAME_Y, 0.0f);
	g_FinishGame.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_FinishGame.nCntAlufa = 50;
	g_FinishGame.fCntSize = 1.0f;
	g_FinishGame.nTExType = 0;
	g_FinishGame.bUse = true;
	g_FinishGame.bFinish = false;

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * MAX_VERTEX, // �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffFinishGame,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFinishGame->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̍X�V
	SetVertexFinishGame();

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �e�N�X�`���̍X�V
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFinishGame->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �t�B�j�b�V���Q�[���̏I������
//-----------------------------------------------------------------
void UninitFinishGame(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffFinishGame != NULL)
	{
		g_pVtxBuffFinishGame->Release();
		g_pVtxBuffFinishGame = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureFinishGame != NULL)
	{
		g_pTextureFinishGame->Release();
		g_pTextureFinishGame = NULL;
	}
	
}

//-----------------------------------------------------------------
// �t�B�j�b�V���Q�[���̍X�V����
//-----------------------------------------------------------------
void UpdateFinishGame(void)
{
	// ���_���W�̍X�V
	SetVertexFinishGame();
}

//-----------------------------------------------------------------
// �t�B�j�b�V���Q�[���̕`�揈��
//-----------------------------------------------------------------
void DrawFinishGame(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFinishGame, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�ƕ`��
	if (g_FinishGame.bFinish == true)
	{
		pDevice->SetTexture(0, g_pTextureFinishGame);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//-----------------------------------------------------------------
// ���_���W�̐ݒ�
//-----------------------------------------------------------------
void SetVertexFinishGame(void)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFinishGame->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(g_FinishGame.pos.x - (FINISHGAME_WIDTH / 2) * g_FinishGame.fCntSize, g_FinishGame.pos.y + (FINISHGAME_HEIGHT / 2) * g_FinishGame.fCntSize, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_FinishGame.pos.x - (FINISHGAME_WIDTH / 2) * g_FinishGame.fCntSize, g_FinishGame.pos.y - (FINISHGAME_HEIGHT / 2) * g_FinishGame.fCntSize, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_FinishGame.pos.x + (FINISHGAME_WIDTH / 2) * g_FinishGame.fCntSize, g_FinishGame.pos.y + (FINISHGAME_HEIGHT / 2) * g_FinishGame.fCntSize, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_FinishGame.pos.x + (FINISHGAME_WIDTH / 2) * g_FinishGame.fCntSize, g_FinishGame.pos.y - (FINISHGAME_HEIGHT / 2) * g_FinishGame.fCntSize, 0.0f);	

	// ���_�J���[�̍X�V
	pVtx[0].col = g_FinishGame.col;
	pVtx[1].col = g_FinishGame.col;
	pVtx[2].col = g_FinishGame.col;
	pVtx[3].col = g_FinishGame.col;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFinishGame->Unlock();
}

//-----------------------------------------------------------------
// �Q�[�����I��������ǂ����擾
//-----------------------------------------------------------------
void SetFinishGame(bool bFinish)
{
	if (g_FinishGame.bFinish == false)
	{
		PlaySound(SOUND_LABEL_SE_FINISH);
	}
	g_FinishGame.bFinish = bFinish;
}

//-----------------------------------------------------------------
// �Q�[�����I��������ǂ����擾
//-----------------------------------------------------------------
bool GetFinishGame(void)
{
	return g_FinishGame.bFinish;
}