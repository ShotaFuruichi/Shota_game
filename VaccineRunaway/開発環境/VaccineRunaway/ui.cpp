////////////////////////////////////////////////////////////////////////////////
//
//Contents	: ui�̏��� [ui.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/09/29
//
////////////////////////////////////////////////////////////////////////////////
#include "ui.h"
#include "player.h"
#include "item.h"

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemUi = NULL;	//���_���
LPDIRECT3DTEXTURE9 g_pTextureItemUi[4] = {};		//�e�N�X�`�����

////////////////////////////////////////////////////////////////////////////////
//�w�i�̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitUi(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_pTextureItemUi[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item002.png", &g_pTextureItemUi[ITEM_THROUGH]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item000.png", &g_pTextureItemUi[ITEM_REFLECTIVE]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item003.png", &g_pTextureItemUi[ITEM_DIFFUSION]);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffItemUi, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItemUi->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(100.0f, 50.0f, 0);
	pVtx[1].pos = D3DXVECTOR3(100.0f, 10.0f, 0);
	pVtx[2].pos = D3DXVECTOR3(170.0f, 50.0f, 0);
	pVtx[3].pos = D3DXVECTOR3(170.0f, 10.0f, 0);

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
	g_pVtxBuffItemUi->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�w�i�̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitUi(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffItemUi != NULL)
	{
		g_pVtxBuffItemUi->Release();	//�J��
		g_pVtxBuffItemUi = NULL;		//������
	}

	//�e�N�X�`���̊J��
	for (int nCntType = 0; nCntType < MAX_ITEMTYPE; nCntType++)
	{
		if (g_pTextureItemUi[nCntType] != NULL)
		{
			g_pTextureItemUi[nCntType]->Release();	//�J��
			g_pTextureItemUi[nCntType] = NULL;		//������
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�w�i�̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateUi(void)
{
	//�ϐ��錾
	PLAYER *pPlayer;

	pPlayer = GetPlayer();

	switch (pPlayer->BulletType)
	{
	case 0:
		SetVertexNormalItemUi();
		break;
	default:
		SetVertexSpecialItemUi();
	}
}

////////////////////////////////////////////////////////////////////////////////
//�w�i�̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawUi(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	PLAYER *pPlayer;

	pPlayer = GetPlayer();

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffItemUi, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	switch (pPlayer->BulletType)
	{
	case ITEM_THROUGH:
		pDevice->SetTexture(0, g_pTextureItemUi[ITEM_THROUGH]);
		break;

	case ITEM_REFLECTIVE:
		pDevice->SetTexture(0, g_pTextureItemUi[ITEM_REFLECTIVE]);
		break;

	case ITEM_DIFFUSION:
		pDevice->SetTexture(0, g_pTextureItemUi[ITEM_DIFFUSION]);
		break;
	default:
		pDevice->SetTexture(0, g_pTextureItemUi[0]);
		break;
	}
	
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

////////////////////////////////////////////////////////////////////////////////
//�ʏ펞���_���W�ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetVertexNormalItemUi(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItemUi->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(115.0f, 50.0f, 0);
	pVtx[1].pos = D3DXVECTOR3(115.0f, 10.0f, 0);
	pVtx[2].pos = D3DXVECTOR3(155.0f, 50.0f, 0);
	pVtx[3].pos = D3DXVECTOR3(155.0f, 10.0f, 0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItemUi->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�ʏ펞���_���W�ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetVertexSpecialItemUi(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItemUi->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(100.0f, 50.0f, 0);
	pVtx[1].pos = D3DXVECTOR3(100.0f, 10.0f, 0);
	pVtx[2].pos = D3DXVECTOR3(170.0f, 50.0f, 0);
	pVtx[3].pos = D3DXVECTOR3(170.0f, 10.0f, 0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItemUi->Unlock();
}