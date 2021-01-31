////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �X�R�A�\�� [score.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/08/24
//
////////////////////////////////////////////////////////////////////////////////
#include "score.h"
#include "input.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define POS_X (750.0f)		//�X�R�A��X���W
#define SCORE_WIDTH (45.0f)	//�X�R�A�̑傫��X
#define SCORE_HEIGHT (50.0f)//�X�R�A�̑傫��Y

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;			//���_�o�b�t�@�ւ̐ݒ�
int g_nScore;

////////////////////////////////////////////////////////////////////////////////
//�X�R�A�̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitScore(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number001.png", &g_pTextureScore);

	//������
	g_nScore = NULL;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffScore, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(POS_X + (nCntScore * SCORE_WIDTH), SCORE_HEIGHT,0);
		pVtx[1].pos = D3DXVECTOR3(POS_X + (nCntScore * SCORE_WIDTH), 0, 0);
		pVtx[2].pos = D3DXVECTOR3(POS_X + ((nCntScore + 1) * SCORE_WIDTH), SCORE_HEIGHT, 0);
		pVtx[3].pos = D3DXVECTOR3(POS_X + ((nCntScore + 1) * SCORE_WIDTH), 0, 0);

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
	g_pVtxBuffScore->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�X�R�A�̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitScore(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();	//�J��
		g_pVtxBuffScore = NULL;		//������
	}

	//�e�N�X�`���̊J��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();	//�J��
		g_pTextureScore = NULL;		//������
	}

}

////////////////////////////////////////////////////////////////////////////////
//�X�R�A�̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateScore(void)
{
	
}

////////////////////////////////////////////////////////////////////////////////
//�X�R�A�̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawScore(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureScore);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);	//�l�p�`�����ꍇ�v���~�e�B�u�̐���2�ɂ���
	}

}

////////////////////////////////////////////////////////////////////////////////
//�X�R�A�ϊ�
////////////////////////////////////////////////////////////////////////////////
void AddScore(int nValue)
{
	int nDigit = 10000000;	//�X�R�A��8��������
	int nScore;
	int nScore2;
	float fPosition;
	VERTEX_2D *pVtx;

	g_nScore += nValue;

	nScore = g_nScore;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < 8; nCntScore++, nDigit /= 10)
	{
		//���݂̃X�R�A��10�̌����{�P��Ŋ������]�����
		nScore2 = nScore % (nDigit * 10);

		//��ŏo�����l��10�̌�����Ŋ�����������
		nScore2 /= nDigit;

		//�e�N�X�`���̃|�W�V����������
		fPosition = (float)nScore2 / 10;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(fPosition, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(fPosition, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(fPosition + 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(fPosition + 0.1f, 0.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�X�R�A�̎擾
////////////////////////////////////////////////////////////////////////////////p
int GetScore(void)
{
	return g_nScore;
}