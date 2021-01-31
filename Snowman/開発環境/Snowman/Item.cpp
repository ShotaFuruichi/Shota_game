////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �A�C�e���̏��� [item.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/10/16
//
////////////////////////////////////////////////////////////////////////////////
#include "item.h"

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;	//���_���
LPDIRECT3DTEXTURE9 g_pTextureItem = NULL;		//�e�N�X�`�����
ITEM g_Item;

////////////////////////////////////////////////////////////////////////////////
//�w�i�̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitItem(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�ϐ��̏�����
	g_Item.pos = D3DXVECTOR3(18000.0f, 0.0f, 0.0f);
	g_Item.fWidth = 25.0f;
	g_Item.fHeight = 25.0f;
	g_Item.bUse = false;
	g_pVtxBuffItem = NULL;
	g_pTextureItem = NULL;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\right.png", &g_pTextureItem);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffItem, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	SetVertexItem();

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
	g_pVtxBuffItem->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�w�i�̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitItem(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();	//�J��
		g_pVtxBuffItem = NULL;		//������
	}

	//�e�N�X�`���̊J��
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();	//�J��
		g_pTextureItem = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�w�i�̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateItem(void)
{
	if (g_Item.bUse == true)
	{
		SetVertexItem();
	}
}

////////////////////////////////////////////////////////////////////////////////
//�w�i�̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawItem(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_Item.bUse == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureItem);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

////////////////////////////////////////////////////////////////////////////////
//�Z�b�g
////////////////////////////////////////////////////////////////////////////////
void SetItem(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//�ϐ��錾
	ITEM *pItem;
	pItem = &g_Item;

	//for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	//{
		if (pItem->bUse == false)
		{	//�G���g�p����Ă��Ȃ��Ƃ�

			//�A�C�e���̊�{���
			pItem->pos = pos;
			pItem->fWidth = fWidth;
			pItem->fHeight = fHeight;

			//�A�C�e�����g�p����
			pItem->bUse = true;

		}
	/*}*/
}

////////////////////////////////////////////////////////////////////////////////
//���_���W�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetVertexItem(void)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Item.pos.x - g_Item.fWidth, g_Item.pos.y + g_Item.fHeight, 0);
	pVtx[1].pos = D3DXVECTOR3(g_Item.pos.x - g_Item.fWidth, g_Item.pos.y - g_Item.fHeight, 0);
	pVtx[2].pos = D3DXVECTOR3(g_Item.pos.x + g_Item.fWidth, g_Item.pos.y + g_Item.fHeight, 0);
	pVtx[3].pos = D3DXVECTOR3(g_Item.pos.x + g_Item.fWidth, g_Item.pos.y - g_Item.fHeight, 0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

ITEM *GetItem(void)
{
	return &g_Item;
}