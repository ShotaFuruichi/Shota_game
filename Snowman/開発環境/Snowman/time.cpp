////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �������Ԃ̕\�� [time.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/11/09
//
////////////////////////////////////////////////////////////////////////////////
#include "time.h"
#include "fade.h"
#include "game.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define POS_X (900.0f)		//�������Ԃ�X���W

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;			//���_�o�b�t�@�ւ̐ݒ�
int g_nTime;
bool g_bClear;

////////////////////////////////////////////////////////////////////////////////
//�������Ԃ̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitTime(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	
	//������
	g_pTextureTime = NULL;
	g_pVtxBuffTime = NULL;
	g_nTime = 7200;
	g_bClear = false;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number000.png", &g_pTextureTime);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTime, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(POS_X + (nCntTime *90.0f), 100.0f, 0);
		pVtx[1].pos = D3DXVECTOR3(POS_X + (nCntTime * 90.0f), 0, 0);
		pVtx[2].pos = D3DXVECTOR3(POS_X + ((nCntTime + 1) * 90.0f), 100.0f, 0);
		pVtx[3].pos = D3DXVECTOR3(POS_X + ((nCntTime + 1) * 90.0f), 0, 0);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

		pVtx += 4;


	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�������Ԃ̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitTime(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();	//�J��
		g_pVtxBuffTime = NULL;		//������
	}

	//�e�N�X�`���̊J��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();	//�J��
		g_pTextureTime = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�������Ԃ̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateTime(void)
{
	int nTime = 0;
	int nTime2 = 0;
	int nDigit = 100;
	float fPosition;
	VERTEX_2D *pVtx;

	//�N���A�܂��̓Q�[���I�[�o�[���Ă��Ȃ��Ƃ�
	if (g_bClear == false)
	{
		g_nTime--;
		nTime = g_nTime;

		nTime /= 60;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++, nDigit /= 10)
		{
			//���݂̎��Ԃ�10�̌����{�P��Ŋ������]�����
			nTime2 = nTime % (nDigit * 10);

			//��ŏo�����l��10�̌�����Ŋ�����������
			nTime2 /= nDigit;

			//�e�N�X�`���̃|�W�V����������
			fPosition = (float)nTime2 / 10;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(fPosition, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(fPosition, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(fPosition + 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(fPosition + 0.1f, 0.0f);

			pVtx += 4;
		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTime->Unlock();

		if (g_nTime == 0)
		{
			g_bClear = true;
			SetFade(FADE_OUT, MODE_RESULT);
			SetStageMode(STAGE_MAX);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�������Ԃ̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawTime(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTime);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);	//�l�p�`�����ꍇ�v���~�e�B�u�̐���2�ɂ���
	}

}

//////////////////////////////////////////////////////////////////////////////////
////�X�R�A�ϊ�
//////////////////////////////////////////////////////////////////////////////////
//void AddScore(int nValue)
//{
//	int nDigit = 10000000;	//�X�R�A��8��������
//	int nScore;
//	int nScore2;
//	float fPosition;
//	VERTEX_2D *pVtx;
//
//	g_nScore += nValue;
//
//	nScore = g_nScore;
//
//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (int nCntScore = 0; nCntScore < 8; nCntScore++, nDigit /= 10)
//	{
//		//���݂̃X�R�A��10�̌����{�P��Ŋ������]�����
//		nScore2 = nScore % (nDigit * 10);
//
//		//��ŏo�����l��10�̌�����Ŋ�����������
//		nScore2 /= nDigit;
//
//		//�e�N�X�`���̃|�W�V����������
//		fPosition = (float)nScore2 / 10;
//
//		//�e�N�X�`�����W�̐ݒ�
//		pVtx[0].tex = D3DXVECTOR2(fPosition, 1.0f);
//		pVtx[1].tex = D3DXVECTOR2(fPosition, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(fPosition + 0.1f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(fPosition + 0.1f, 0.0f);
//
//		pVtx += 4;
//	}
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffScore->Unlock();
//}

////////////////////////////////////////////////////////////////////////////////
//�X�R�A�̎擾
////////////////////////////////////////////////////////////////////////////////
int GetTime(void)
{
	return g_nTime;
}

////////////////////////////////////////////////////////////////////////////////
//�N���A���̎擾
////////////////////////////////////////////////////////////////////////////////
bool GetClear(void)
{
	return g_bClear;
}