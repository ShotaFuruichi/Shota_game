////////////////////////////////////////////////////////////////////////////////
//
//Contents	: ���U���g�̏��� [result.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/10/30
//
////////////////////////////////////////////////////////////////////////////////
#include "result.h"
#include "input.h"
#include "fade.h"
#include "xinput_pad.h"
#include "player.h"
#include "enemy.h"

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;			//���_���
LPDIRECT3DTEXTURE9 g_pTextureResult[RESULT_MAX] = {};		//�e�N�X�`���ւ̃|�C���^
RESULT g_Result;											//�ǂ̃��U���g��`�悷�邩

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
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gameover000.jpg", &g_pTextureResult[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\clear.jpg", &g_pTextureResult[1]);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffResult, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffResult->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�I������
////////////////////////////////////////////////////////////////////////////////
void UninitResult(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();	//�J��
		g_pVtxBuffResult = NULL;		//������
	}

	//�e�N�X�`���̊J��
	for (int nCntResult = 0; nCntResult < RESULT_MAX; nCntResult++)
	{
		if (g_pTextureResult[nCntResult] != NULL)
		{
			g_pTextureResult[nCntResult]->Release();
			g_pTextureResult[nCntResult] = NULL;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateResult(void)
{
	XinputGamepad *pXinput = GetXinputGamepad();

	if (GetKeyboardTrigger(DIK_RETURN) == true || pXinput->bPressA == true)
	{
		SetFade(FADE_OUT, MODE_TITLE);
	}
}

////////////////////////////////////////////////////////////////////////////////
//�`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawResult(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	PLAYER *player = GetPlayer();
	ENEMY *enemy = GetEnemy();

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	if (player->nLife <= 0)
	{
		pDevice->SetTexture(0, g_pTextureResult[0]);
	}
	else if (enemy->nLife <= 0)
	{
		pDevice->SetTexture(0, g_pTextureResult[1]);
	}

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}