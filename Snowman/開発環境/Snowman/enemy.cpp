////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �G�̏��� [enemy.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/10/23
//
////////////////////////////////////////////////////////////////////////////////
#include "enemy.h"
#include "block.h"
#include "time.h"
#include <time.h>

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define MAX_LIFE (100)	//�G�̃��C�t�̍ő�l

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureEnemy[ENEMYTYPE_MAX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;			//���_�o�b�t�@�ւ̐ݒ�
ENEMY g_aEnemy[MAX_ENEMY];								//�G�̏��

////////////////////////////////////////////////////////////////////////////////
//�G�̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitEnemy(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�ϐ��̏�����
	for (int nCntEnemy = 0; nCntEnemy < ENEMYTYPE_MAX; nCntEnemy++)
	{
		g_pTextureEnemy[nCntEnemy] = NULL;	//�e�N�X�`���ւ̃|�C���^
	}
	g_pVtxBuffEnemy = NULL;

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{	
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(10000.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nJumpCounter = 0;
		g_aEnemy[nCntEnemy].nJumpTiming = GetRandom(30, 60);
		g_aEnemy[nCntEnemy].type = ENEMYTYPE_SPRING;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = NULL;
		g_aEnemy[nCntEnemy].nLife = MAX_LIFE;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy00.png", &g_pTextureEnemy[ENEMYTYPE_SPRING]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy00Freeze.png", &g_pTextureEnemy[ENEMYTYPE_SPRINGFREEZE]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy01.png", &g_pTextureEnemy[ENEMYTYPE_SUMMER]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy01Freeze.png", &g_pTextureEnemy[ENEMYTYPE_SUMMERFREEZE]);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffEnemy, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//���_���̐ݒ�
		SetVertexEnemy(nCntEnemy);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(225, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�G�̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitEnemy(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();	//�J��
		g_pVtxBuffEnemy = NULL;		//������
	}

	//�e�N�X�`���̊J��
	for (int nCntEnemy = 0; nCntEnemy < ENEMYTYPE_MAX; nCntEnemy++)
	{
		if (g_pTextureEnemy[nCntEnemy] != NULL)
		{
			g_pTextureEnemy[nCntEnemy]->Release();	//�J��
			g_pTextureEnemy[nCntEnemy] = NULL;		//������
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�G�̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateEnemy(void)
{
	//�ϐ��錾
	ENEMY *pEnemy;

	pEnemy = &g_aEnemy[0];

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{	//�G���g�p����Ă���Ƃ�
			
			pEnemy->posold = pEnemy->pos;
			switch (pEnemy->state)
			{
			case ENEMYSTATE_NORMAL:
				pEnemy->nCounterState = 0;
				pEnemy->move.y += 1.5f;

				pEnemy->pos.x += pEnemy->move.x;
				pEnemy->pos.y += pEnemy->move.y;

				if (pEnemy->pos.y > SCREEN_HEIGHT)
				{
					pEnemy->move.y = 0.0f;
					pEnemy->pos.y = SCREEN_HEIGHT;
				}
				
				if ((pEnemy->pos.x - DIAGONAL_X - 20) <= 0)
				{
					pEnemy->pos.x = DIAGONAL_X + 20;
					pEnemy->move.x *= -1;
				}
				if ((pEnemy->pos.x + DIAGONAL_X + 20) >= SCREEN_WIDTH)
				{
					pEnemy->pos.x = SCREEN_WIDTH - DIAGONAL_X - 20;
					pEnemy->move.x *= -1;
				}


				if (pEnemy->nLife <= 0)
				{
					pEnemy->state = ENEMYSTATE_FREEZE;
					pEnemy->move.x = 0.0f;
					pEnemy->move.y += 5.0f;
				}

				if (ColisionBlock(&pEnemy->pos, &pEnemy->posold, &pEnemy->move, ENEMY_SIZEX, ENEMY_SIZEY) == true)
				{
					pEnemy->move.x *= -1;
				}
				SetTextureEnemy(nCntEnemy);

				switch (pEnemy->type)
				{
				case ENEMYTYPE_SUMMER:
					pEnemy->nJumpCounter++;
					if (pEnemy->nJumpCounter % pEnemy->nJumpTiming == 0)
					{
						pEnemy->move.y -= 20.0f;
					}
					break;
				}

				break;
				
			case ENEMYSTATE_FREEZE:
				pEnemy->move.y += 1.5f;

				pEnemy->pos.x += pEnemy->move.x;
				pEnemy->pos.y += pEnemy->move.y;

				if ((pEnemy->pos.x - DIAGONAL_X - 20) <= 0)
				{
					pEnemy->pos.x = DIAGONAL_X + 20;
					pEnemy->move.x *= -1;
				}
				if ((pEnemy->pos.x + DIAGONAL_X + 20) >= SCREEN_WIDTH)
				{
					pEnemy->pos.x = SCREEN_WIDTH - DIAGONAL_X - 20;
					pEnemy->move.x *= -1;
				}

				if (pEnemy->pos.y > SCREEN_HEIGHT)
				{
					pEnemy->move.y = 0.0f;
					pEnemy->pos.y = SCREEN_HEIGHT;
				}
				if (ColisionBlock(&pEnemy->pos, &pEnemy->posold, &pEnemy->move, ENEMY_SIZEX, ENEMY_SIZEY) == true)
				{
					pEnemy->move.x = 0;
					
				}

				pEnemy->nCounterState++;
				if (pEnemy->nCounterState > 500)
				{
					pEnemy->state = ENEMYSTATE_NORMAL;
					pEnemy->nLife = MAX_LIFE;
					pEnemy->move.x = 2.5f;
				}

				break;
			}

			SetVertexEnemy(nCntEnemy);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�G�̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawEnemy(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			switch (g_aEnemy[nCntEnemy].type)
			{
			case ENEMYTYPE_SPRING:
				switch (g_aEnemy[nCntEnemy].state)
				{
				case ENEMYSTATE_NORMAL:
					pDevice->SetTexture(0, g_pTextureEnemy[ENEMYTYPE_SPRING]);
					break;
				case ENEMYSTATE_FREEZE:
					pDevice->SetTexture(0, g_pTextureEnemy[ENEMYTYPE_SPRINGFREEZE]);
					break;
				}
				break;

			case ENEMYTYPE_SUMMER:
				switch (g_aEnemy[nCntEnemy].state)
				{
				case ENEMYSTATE_NORMAL:
					pDevice->SetTexture(0, g_pTextureEnemy[ENEMYTYPE_SUMMER]);
					break;
				case ENEMYSTATE_FREEZE:
					pDevice->SetTexture(0, g_pTextureEnemy[ENEMYTYPE_SUMMERFREEZE]);
					break;
				}
				break;
			}
			

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�G�̃Z�b�g����
////////////////////////////////////////////////////////////////////////////////
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMYTYPE type)
{
	//�ϐ��錾
	ENEMY *pEnemy;
	pEnemy = &g_aEnemy[0];

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == false)
		{	//�G���g�p����Ă��Ȃ��Ƃ�
			pEnemy->pos = pos;
			pEnemy->move = move;
			pEnemy->type = type;
			pEnemy->state = ENEMYSTATE_NORMAL;
			pEnemy->nLife = MAX_LIFE;
			pEnemy->bUse = true;
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�|�C���^�̎擾
////////////////////////////////////////////////////////////////////////////////
ENEMY *GetEnemy(void)
{
	return &g_aEnemy[0];
}

////////////////////////////////////////////////////////////////////////////////
//�ʏ�G�̒��_���W�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetVertexEnemy(int nIdx)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x - ENEMY_SIZEX, g_aEnemy[nIdx].pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x - ENEMY_SIZEX, g_aEnemy[nIdx].pos.y - ENEMY_SIZEY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x + ENEMY_SIZEX, g_aEnemy[nIdx].pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x + ENEMY_SIZEX, g_aEnemy[nIdx].pos.y - ENEMY_SIZEY, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�e�N�X�`�����W
////////////////////////////////////////////////////////////////////////////////
void SetTextureEnemy(int nIdx)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	if (g_aEnemy[nIdx].move.x < 0)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}
	else
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�G�̃X�e�[�g����
////////////////////////////////////////////////////////////////////////////////
bool HitEnemy(int nIdx, int nDamage)
{
	g_aEnemy[nIdx].nLife -= nDamage;
	
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//�����_���Ȑ��l���擾
////////////////////////////////////////////////////////////////////////////////
int GetRandom(int min, int max)
{
	static int nNum;

	if (nNum == 0)
	{
		srand((unsigned int)time(NULL));
		nNum = 1;
	}

	return min + (rand() * (max - min + 1) / (1 + RAND_MAX));
}
