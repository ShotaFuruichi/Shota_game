////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �G�̏��� [enemy.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/08/05
//
////////////////////////////////////////////////////////////////////////////////
#include "enemy.h"
#include "score.h"
#include "game.h"
#include "explosion.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define MAX_TYPE (3)	//�^�C�v�̍ő吔
#define MAX_LIFE (1)	//�G�̃��C�t�̍ő�l

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureEnemy[MAX_TYPE] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;		//���_�o�b�t�@�ւ̐ݒ�
ENEMY g_aEnemy[MAX_ENEMY];							//�G�̏��
int g_nEnemyNumber[MAX_ENEMY];						//�G�̐������

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

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy.png", &g_pTextureEnemy[ENEMYTYPE_NORMAL]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy2.png", &g_pTextureEnemy[ENEMYTYPE_BIG]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy002.png", &g_pTextureEnemy[ENEMYTYPE_SHOT]);

	//�ϐ��̏�����
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{	
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = NULL;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = NULL;
		g_aEnemy[nCntEnemy].nLife = MAX_LIFE;
		g_aEnemy[nCntEnemy].bSwitch = false;
		g_aEnemy[nCntEnemy].bDisp = false;
	}

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
	for (int nCntEnemy = 0; nCntEnemy < MAX_TYPE; nCntEnemy++)
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
	VERTEX_2D *pVtx;

	pEnemy = &g_aEnemy[0];

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{	//�G���g�p����Ă���Ƃ�

			//�ʒu�̍X�V
			pEnemy->pos.x += pEnemy->move.x;

			switch (pEnemy->nType)
			{
			case ENEMYTYPE_BIG:
				//�ł����G�̒��_���̐ݒ�
				SetVertexBigEnemy(nCntEnemy);
				break;

			default:
				//�G�̒��_���W�̐ݒ�
				SetVertexEnemy(nCntEnemy);
				break;
			}

			//�i�ޕ���
			if (pEnemy->bSwitch == false)
			{	
				if (pEnemy->pos.x < (SCREEN_WIDTH / 2))
				{	//�G����ʒ�����荶���ɂ���Ƃ�
					if (pEnemy->nType == ENEMYTYPE_SHOT)
					{	//�����G
						pEnemy->move.x = SHOTENEMY_SPEED;
					}
					else
					{	//�ʏ�G
						pEnemy->move.x = ENEMY_SPEED;
					}
				}
				else if (pEnemy->pos.x >(SCREEN_WIDTH / 2))
				{	//�G�����������E���ɂ���Ƃ�
					if (pEnemy->nType == ENEMYTYPE_SHOT)
					{	//�����G
						pEnemy->move.x = -SHOTENEMY_SPEED;
					}
					else
					{	//�ʏ�G
						pEnemy->move.x = -ENEMY_SPEED;
					}
				}

				if (pEnemy->pos.x > 0 + ENEMY_SIZE && pEnemy->pos.x < SCREEN_WIDTH - ENEMY_SIZE)
				{	//��ʓ��ɓ������玟�ɉ�ʊO�ɏo�����ɏ�����悤�ɂ���
					pEnemy->bSwitch = true;
				}
				pEnemy->bDisp = true;
			}

			if (pEnemy->bSwitch == true)
			{
				if (pEnemy->pos.x < 0 - ENEMY_SIZE || pEnemy->pos.x > SCREEN_WIDTH + ENEMY_SIZE)
				{	//��ʊO�ɏo�������
					pEnemy->bUse = false;
					pEnemy->bDisp = false;
					pEnemy->bSwitch = false;
				}
			}

			switch (g_aEnemy[g_nEnemyNumber[nCntEnemy]].state)
			{
			case ENEMYSTATE_DAMAGE:	//�_���[�W���󂯂���
				g_aEnemy[g_nEnemyNumber[nCntEnemy]].nCounterState--;

				if (g_aEnemy[g_nEnemyNumber[nCntEnemy]].nCounterState <= 0)
				{	//��ԃJ�E���^��0�ȉ��ɂȂ������Ɍ��ɖ߂�
					g_aEnemy[g_nEnemyNumber[nCntEnemy]].state = ENEMYSTATE_NORMAL;

					//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
					g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

					pVtx += g_nEnemyNumber[nCntEnemy] * 4;

					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

					//���_�o�b�t�@���A�����b�N����
					g_pVtxBuffEnemy->Unlock();
				}
				break;

			default:
				break;
			}
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
		if (g_aEnemy[nCntEnemy].bDisp == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�G�̃Z�b�g����
////////////////////////////////////////////////////////////////////////////////
void SetEnemy(void)
{
	//�ϐ��錾
	ENEMY *pEnemy;
	int nPos;
	pEnemy = &g_aEnemy[0];

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == false)
		{	//�G���g�p����Ă��Ȃ��Ƃ�
			nPos = (int)GetRandom(0, 1);

			switch (nPos)
			{
			case 0:
				pEnemy->pos.x = SCREEN_WIDTH + BIGENEMY_SIZE;
				break;
			case 1:
				pEnemy->pos.x = SCREEN_LEFT - BIGENEMY_SIZE;
				break;
			}
			pEnemy->pos.y = GetRandom(100.0f + BIGENEMY_SIZE, SCREEN_HEIGHT - BIGENEMY_SIZE);

			pEnemy->nType = (int)GetRandom(0, 2);

			//�G���g�p����
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
	pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x - ENEMY_SIZE, g_aEnemy[nIdx].pos.y + ENEMY_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x - ENEMY_SIZE, g_aEnemy[nIdx].pos.y - ENEMY_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x + ENEMY_SIZE, g_aEnemy[nIdx].pos.y + ENEMY_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x + ENEMY_SIZE, g_aEnemy[nIdx].pos.y - ENEMY_SIZE, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�傫���G�̒��_���W�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetVertexBigEnemy(int nIdx)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x - BIGENEMY_SIZE, g_aEnemy[nIdx].pos.y + BIGENEMY_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x - BIGENEMY_SIZE, g_aEnemy[nIdx].pos.y - BIGENEMY_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x + BIGENEMY_SIZE, g_aEnemy[nIdx].pos.y + BIGENEMY_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x + BIGENEMY_SIZE, g_aEnemy[nIdx].pos.y - BIGENEMY_SIZE, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�G�̃X�e�[�g����
////////////////////////////////////////////////////////////////////////////////
bool HitEnemy(int nIdx, int nDamage)
{
	//���C�t���_���[�W������
	g_aEnemy[nIdx].nLife -= nDamage;

	if (g_aEnemy[nIdx].nLife <= 0)
	{	//���C�t��0�ȉ��ɂȂ�����
		if(g_aEnemy[nIdx].nType == ENEMYTYPE_BIG)
		{
			for (int nCntEnemy = 0; nCntEnemy < 2; nCntEnemy++)
			{	//�傫���^�C�v�̓G��|�����Ƃ��͓G���̃Z�b�g
				SetEnemy();
			}
		}

		//�G��j��
		g_aEnemy[nIdx].bUse = false;
		g_aEnemy[nIdx].bDisp = false;
		g_aEnemy[nIdx].bSwitch = false;

		//�����Đ�
		SetExplosion(g_aEnemy[nIdx].pos);

		//�^�C�v���ƂɃX�R�A�����Z
		switch (g_aEnemy[nIdx].nType)
		{
		case ENEMYTYPE_NORMAL:
			AddScore(1000);
		case ENEMYTYPE_SHOT:
			AddScore(3000);
		case ENEMYTYPE_BIG:
			AddScore(5000);
		}
		
		return true;
	}
	else
	{
		g_nEnemyNumber[nIdx] = nIdx;
		g_aEnemy[nIdx].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nIdx].nCounterState = 6;

		//�ϐ��錾
		VERTEX_2D *pVtx;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nIdx * 4;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 150);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 150);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 150);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 150);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffEnemy->Unlock();

		return false;
	}
}
