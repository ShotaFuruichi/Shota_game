////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �u���b�N�̏��� [block.cpp]
//Author	: Shota Furuichi
//Since		: 2020/10/13
//
////////////////////////////////////////////////////////////////////////////////
#include "block.h"
#include "player.h"
#include "input.h"
#include "enemy.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBlock[BLOCKTYPE_MAX] = {};		//�e�N�X�`���ւ̃|�C���^
BLOCK g_aBlock[MAX_BLOCK];									//�u���b�N
int g_aMove[MAX_BLOCK];

////////////////////////////////////////////////////////////////////////////////
//����������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitBlock(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�ϐ��̏�����
	g_pVtxBuffBlock = NULL;
	for (int nCntBlock = 0; nCntBlock < BLOCKTYPE_MAX; nCntBlock++)
	{
		g_pTextureBlock[nCntBlock] = NULL;
	}

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].fWidth = 0.0f;
		g_aBlock[nCntBlock].fHeight = 0.0f;
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].bMove = false;
		g_aBlock[nCntBlock].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].nTexX = 0;
		g_aBlock[nCntBlock].nTexY = 0;
		g_aBlock[nCntBlock].type = BLOCKTYPE_NORMAL;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\block000.jpg", &g_pTextureBlock[BLOCKTYPE_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\soil.jpg", &g_pTextureBlock[BLOCKTYPE_GROUND]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\snowsoil.png", &g_pTextureBlock[BLOCKTYPE_SNOWGROUND]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\GrassSoil.jpg", &g_pTextureBlock[BLOCKTYPE_GRASSGROUND]);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBlock, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//���_���W�̐ݒ�
		SetVertexBlock(nCntBlock);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		SetColorBlock(nCntBlock);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�I������
////////////////////////////////////////////////////////////////////////////////
void UninitBlock(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();	//�J��
		g_pVtxBuffBlock = NULL;		//������
	}

	//�e�N�X�`���̊J��
	for (int nCntBlock = 0; nCntBlock < BLOCKTYPE_MAX; nCntBlock++)
	{
		if (g_pTextureBlock[nCntBlock] != NULL)
		{
			g_pTextureBlock[nCntBlock]->Release();	//�J��
			g_pTextureBlock[nCntBlock] = NULL;		//������
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateBlock(void)
{
	BLOCK *pBlock;
	pBlock = &g_aBlock[0];

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{	
		if (pBlock->bUse == true)
		{
			//���_���W�̐ݒ�
			SetVertexBlock(nCntBlock);

			//�F�̐ݒ�
			SetColorBlock(nCntBlock);

			//�e�N�X�`�����W�̐ݒ�
			SetTextureBlock(nCntBlock);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawBlock(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	BLOCK *pBlock;
	pBlock = &g_aBlock[0];

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{	//�e���g�p����Ă���ꍇ

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBlock[pBlock->type]);

			//�|���S���̕`��
			if (pBlock->bDisp == true)
			{
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�Z�b�g
////////////////////////////////////////////////////////////////////////////////
void SetBlock(D3DXVECTOR3 pos, float fWidth, float fHeight, bool bDisp, bool bMove, D3DXCOLOR col, int texX, int texY, BLOCKTYPE type)
{
	//�ϐ��錾
	BLOCK *pBlock;

	pBlock = &g_aBlock[0];

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		if (pBlock->bUse == false)
		{	//�e���g�p����Ă��Ȃ��Ƃ�

			//�ʒu�̐ݒ�
			pBlock->pos = pos;

			//���E�����̐ݒ�
			pBlock->fWidth = fWidth;
			pBlock->fHeight = fHeight;

			//�����E�s�����̐ݒ�
			pBlock->bDisp = bDisp;

			//�e�N�X�`���̖���
			pBlock->nTexX = texX;
			pBlock->nTexY = texY;

			//������
			pBlock->bMove = bMove;

			//�F
			pBlock->col = col;

			//�^�C�v
			pBlock->type = type;

			//���_���W�̐ݒ�
			SetVertexBlock(nCntBlock);

			//�e���g�p����
			pBlock->bUse = true;

			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//���_���W�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetVertexBlock(int nIdx)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx�̃|�C���^����
	pVtx += nIdx * 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x, g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x, g_aBlock[nIdx].pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�F�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetColorBlock(int nIdx)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx�̃|�C���^����
	pVtx += nIdx * 4;

	//�F�̐ݒ�
	//���_�J���[�̐ݒ�
	pVtx[0].col = g_aBlock[nIdx].col;
	pVtx[1].col = g_aBlock[nIdx].col;
	pVtx[2].col = g_aBlock[nIdx].col;
	pVtx[3].col = g_aBlock[nIdx].col;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�e�N�X�`�����W�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetTextureBlock(int nIdx)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx�̃|�C���^����
	pVtx += nIdx * 4;

	//�F�̐ݒ�
	//���_�J���[�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f * g_aBlock[nIdx].nTexY);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f * g_aBlock[nIdx].nTexX, 1.0f * g_aBlock[nIdx].nTexY);
	pVtx[3].tex = D3DXVECTOR2(1.0f * g_aBlock[nIdx].nTexX, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�u���b�N�̓����蔻��
////////////////////////////////////////////////////////////////////////////////
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
{
	//�ϐ��錾
	BLOCK *pBlock;
	PLAYER *pPlayer;
	bool bLand = false;
	pBlock = &g_aBlock[0];
	pPlayer = GetPlayer();
	
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		if (pBlock->bUse == true)
		{
			if (pBlock->bMove == true)
			{
				g_aMove[nCntBlock]++;
				g_aMove[nCntBlock] = g_aMove[nCntBlock] % 1000;
				if (g_aMove[nCntBlock] <= 500)
				{
					pBlock->pos.x += 1;
				}
				else if (g_aMove[nCntBlock] > 500)
				{
					pBlock->pos.x -= 1;
				}
			}
			if ((pPlayer->pos.x + DIAGONAL_X) > pBlock->pos.x && (pPlayer->pos.x - DIAGONAL_X) < (pBlock->pos.x + pBlock->fWidth))
			{
				if (pPlayer->oldpos.y <= pBlock->pos.y)
				{
					if (pPlayer->pos.y > pBlock->pos.y)
					{
						pPlayer->bJump = false;
					}
				}
			}
			if ((pPos->x + fWidth) > pBlock->pos.x && (pPos->x - fWidth) < (pBlock->pos.x + pBlock->fWidth))
			{
				if (pPosOld->y <= pBlock->pos.y)
				{
					if (pPos->y > pBlock->pos.y)
					{
						pMove->y = 0.0f;
						pPos->y = pBlock->pos.y;
					}
				}
				
				if ((pPosOld->y - fHeight) > (pBlock->pos.y + pBlock->fHeight))
				{
					if ((pPos->y - fHeight) < (pBlock->pos.y + pBlock->fHeight))
					{
						pMove->y = 0.0f;
						pPos->y = pPosOld->y;
					}
				}
			}

			for (int nCnt = 0; nCnt < fHeight; nCnt++)
			{
				if ((pPos->y - nCnt) > pBlock->pos.y && (pPos->y - nCnt) < (pBlock->pos.y + pBlock->fHeight))
				{
					if ((pPosOld->x + fWidth) <= pBlock->pos.x)
					{
						if ((pPos->x + fWidth) > pBlock->pos.x)
						{
							pPos->x = pPosOld->x;
							bLand = true;
						}
					}
					else if ((pPosOld->x - fWidth) >= (pBlock->pos.x + pBlock->fWidth))
					{
						if ((pPos->x - fWidth) < (pBlock->pos.x + pBlock->fWidth))
						{
							pPos->x = pPosOld->x;
							bLand = true;
						}
					}
				}
			}

#if 0
			pBlock->PosOld = pBlock->pos;
			if (pPlayer->bMove == true)
			{
				if (GetKeyboardPress(DIK_D) == true)
				{
					if (GetKeyboardPress(DIK_A) == true)
					{
					}
					else
					{
						pBlock->pos.x -= 2.0f;
					}
				}
				else if (GetKeyboardPress(DIK_A) == true)
				{
					if (GetKeyboardPress(DIK_D) == true)
					{
					}
					else
					{
						pBlock->pos.x += 2.0f;
					}
				}
			}
#endif
		}
	}
	return bLand;
}
