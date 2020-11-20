////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �n�C�X�R�A�\�� [Highscore.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/09/25
//
////////////////////////////////////////////////////////////////////////////////
#include "highscore.h"
#include "input.h"
#include "score.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define POS_X (585.0f)		//�n�C�X�R�A��X���W

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureHighScore = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHighScore = NULL;			//���_�o�b�t�@�ւ̐ݒ�
int g_nHighScore = 0;

////////////////////////////////////////////////////////////////////////////////
//�n�C�X�R�A�̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitHighScore(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number001.png", &g_pTextureHighScore);

	//������
	g_nHighScore = NULL;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffHighScore, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHighScore = 0; nCntHighScore < MAX_SCORE; nCntHighScore++)
	{
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 225, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

		pVtx += 4;

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHighScore->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�n�C�X�R�A�̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitHighScore(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffHighScore != NULL)
	{
		g_pVtxBuffHighScore->Release();	//�J��
		g_pVtxBuffHighScore = NULL;		//������
	}

	//�e�N�X�`���̊J��
	if (g_pTextureHighScore != NULL)
	{
		g_pTextureHighScore->Release();	//�J��
		g_pTextureHighScore = NULL;		//������
	}

}

////////////////////////////////////////////////////////////////////////////////
//�n�C�X�R�A�̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateHighScore(void)
{
	//�ϐ��錾
	int pScore;
	VERTEX_2D *pVtx;

	pScore = GetScore();

	if (pScore >= g_nHighScore)
	{
		g_nHighScore = pScore;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHighScore = 0; nCntHighScore < MAX_SCORE; nCntHighScore++)
	{
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(POS_X + (nCntHighScore * 95.0f), SCREEN_HEIGHT / 2 + 40.0f, 0);
	pVtx[1].pos = D3DXVECTOR3(POS_X + (nCntHighScore * 95.0f), SCREEN_HEIGHT / 2 - 40.0f, 0);
	pVtx[2].pos = D3DXVECTOR3(POS_X + ((nCntHighScore + 1) * 95.0f), SCREEN_HEIGHT / 2 + 40.0f, 0);
	pVtx[3].pos = D3DXVECTOR3(POS_X + ((nCntHighScore + 1) * 95.0f), SCREEN_HEIGHT / 2 - 40.0f, 0);
	pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHighScore->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�n�C�X�R�A�̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawHighScore(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffHighScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for (int nCntHighScore = 0; nCntHighScore < MAX_SCORE; nCntHighScore++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureHighScore);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntHighScore * 4, 2);	//�l�p�`�����ꍇ�v���~�e�B�u�̐���2�ɂ���
	}
}

////////////////////////////////////////////////////////////////////////////////
//�n�C�X�R�A�̕\��
////////////////////////////////////////////////////////////////////////////////
void AddHighScore(void)
{
	int nDigit = 10000000;	//�X�R�A��8��������
	int nHighScore;
	int nHighScore2;
	float fPosition;
	VERTEX_2D *pVtx;

	nHighScore = g_nHighScore;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHighScore = 0; nCntHighScore < 8; nCntHighScore++, nDigit /= 10)
	{
		//���݂̃X�R�A��10�̌����{�P��Ŋ������]�����
		nHighScore2 = nHighScore % (nDigit * 10);

		//��ŏo�����l��10�̌�����Ŋ�����������
		nHighScore2 /= nDigit;

		//�e�N�X�`���̃|�W�V����������
		fPosition = (float)nHighScore2 / 10;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(fPosition, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(fPosition, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(fPosition + 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(fPosition + 0.1f, 0.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHighScore->Unlock();
}