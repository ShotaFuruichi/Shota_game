////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �A�C�e���̏��� [item.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/09/12
//
////////////////////////////////////////////////////////////////////////////////
#include "item.h"
#include "game.h"
////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define ITEM_SPEED (2.0f)	//�A�C�e���̈ړ���
#define ITEM_TOP (200)		//�A�C�e�������̏�͈�
#define ITEM_BOTTOM (880)	//�A�C�e�������̉��͈�

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;			//���_���
LPDIRECT3DTEXTURE9 g_pTextureItem[MAX_ITEMTYPE] = {};	//�e�N�X�`�����
ITEM g_aItem[MAX_ITEM];									//�A�C�e���̏��

////////////////////////////////////////////////////////////////////////////////
//�A�C�e���̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitItem(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Item002.png", &g_pTextureItem[ITEM_THROUGH]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Item000.png", &g_pTextureItem[ITEM_REFLECTIVE]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Item003.png", &g_pTextureItem[ITEM_DIFFUSION]);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].bUse = false;
		g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].nType = NULL;
		g_aItem[nCntItem].pos = D3DXVECTOR3(30000.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].bSwitch = false;
		g_aItem[nCntItem].bDisp = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffItem, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		SetVertexItem(nCntItem);

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

		//�e�N�X�`�����_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�A�C�e���̏I������
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
	for (int nCntItem = 0; nCntItem < MAX_ITEMTYPE; nCntItem++)
	{
		if (g_pTextureItem[nCntItem] != NULL)
		{
			g_pTextureItem[nCntItem]->Release();	//�J��
			g_pTextureItem[nCntItem] = NULL;		//������
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�A�C�e���̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateItem(void)
{
	//�ϐ��錾
	ITEM *pItem;
	pItem = &g_aItem[0];

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		if (pItem->bUse == true)
		{	
			//�ʒu�̍X�V
			pItem->pos.x += pItem->move.x;

			SetVertexItem(nCntItem);
		
			//�i�ޕ���
			if (pItem->bSwitch == false)
			{
				if (pItem->pos.x < (SCREEN_WIDTH / 2))
				{	//��ʒ������������ɂ���Ƃ�
					pItem->move.x = ITEM_SPEED;

				}
				else if (pItem->pos.x >(SCREEN_WIDTH / 2))
				{	//��ʒ��������E���ɂ���Ƃ�
					pItem->move.x = -ITEM_SPEED;
				}

				if (pItem->pos.x > SCREEN_LEFT + ITEM_SIZEX && pItem->pos.x < SCREEN_WIDTH - ITEM_SIZEX)
				{	//���߂ĉ�ʓ��ɓ��������ɉ�ʊO�ɏo��Ə�����悤�ɂ���
					pItem->bSwitch = true;
				}

				pItem->bDisp = true;
			}
			if (pItem->bSwitch == true)
			{
				if (pItem->pos.x < SCREEN_LEFT - ITEM_SIZEX)
				{
					pItem->bUse = false;
					pItem->bDisp = false;
					pItem->bSwitch = false;
				}
				else if (pItem->pos.x > SCREEN_WIDTH + ITEM_SIZEX)
				{
					pItem->bUse = false;
					pItem->bDisp = false;
					pItem->bSwitch = false;
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�A�C�e���̕`�揈��
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

	//�|���S���̕`��
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bDisp == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureItem[g_aItem[nCntItem].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�A�C�e���̃Z�b�g����
////////////////////////////////////////////////////////////////////////////////
void SetItem(void)
{
	//�ϐ��錾
	ITEM *pItem;
	int nPos;

	pItem = &g_aItem[0];

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		if (pItem->bUse == false)
		{	//�G���g�p����Ă��Ȃ��Ƃ�

			pItem->nType = (int)GetRandom(1, 3);
			nPos = (int)GetRandom(0, 1);

			switch (nPos)
			{
			case 0:
				pItem->pos.x = SCREEN_WIDTH + ITEM_SIZEX;
				break;
			case 1:
				pItem->pos.x = 0.0f - ITEM_SIZEX;
				break;
			}
			pItem->pos.y = GetRandom(ITEM_TOP, ITEM_BOTTOM);

			//�A�C�e�����g�p����
			pItem->bUse = true;

			break;
		}	
	}
}

////////////////////////////////////////////////////////////////////////////////
//���_���W�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetVertexItem(int nIdx)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x - ITEM_SIZEX, g_aItem[nIdx].pos.y + ITEM_SIZEY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x - ITEM_SIZEX, g_aItem[nIdx].pos.y - ITEM_SIZEY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x + ITEM_SIZEX, g_aItem[nIdx].pos.y + ITEM_SIZEY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x + ITEM_SIZEX, g_aItem[nIdx].pos.y - ITEM_SIZEY, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�A�C�e���̃|�C���^�擾
////////////////////////////////////////////////////////////////////////////////
ITEM *GetItem(void)
{
	return &g_aItem[0];
}
