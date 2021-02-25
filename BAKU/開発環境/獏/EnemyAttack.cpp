////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �G�̍U������ [EnemyAttack.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/02/15
//
////////////////////////////////////////////////////////////////////////////////
#include "EnemyAttack.h"
#include "enemy.h"
#include "player.h"
#include "HitEffect.h"
#include "object.h"

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define MAX_ENEMYATTACK (64)		//�U���̍ő吔
#define ATTACK_TIME (120)			//�~������Ă���U�����s����܂ł̒���
#define ATTACK_TIME2 (180)			//�~������Ă���U�����s����܂ł̒���
#define ATTACK_SIZE (450)			//�~�̑傫��
#define ATTACK_SIZE2 (1000)			//�~�̑傫��
#define ENEMYATTACK_DAMAGE (1500)	//�G�̍U��1�̃_���[�W
#define ENEMYATTACK_DAMAGE2 (2000)	//�G�̍U��2�̃_���[�W


////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemyAttack[ENEMYATTACKTYPE_MAX];		//���_���
LPDIRECT3DTEXTURE9 g_pTextureEnemyAttack = NULL;						//�e�N�X�`�����
ENEMYATTACK g_aEnemyAttack[MAX_ENEMYATTACK][ENEMYATTACKTYPE_MAX];		//�G�̍U��

////////////////////////////////////////////////////////////////////////////////
//����������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitEnemyAttack(void)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\AttackSign.png", &g_pTextureEnemyAttack);

	for (int nCntAttack = 0; nCntAttack < MAX_ENEMYATTACK; nCntAttack++)
	{
		for (int nCntAttack2 = 0; nCntAttack2 < ENEMYATTACKTYPE_MAX; nCntAttack2++)
		{
			g_aEnemyAttack[nCntAttack][nCntAttack2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemyAttack[nCntAttack][nCntAttack2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemyAttack[nCntAttack][nCntAttack2].bUse = false;
		}
	}

	for (int nCntAttack2 = 0; nCntAttack2 < ENEMYATTACKTYPE_MAX; nCntAttack2++)
	{
		//���_�o�b�t�@�̐���
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ENEMYATTACK, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffEnemyAttack[nCntAttack2], NULL)))
		{
			return E_FAIL;
		}

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffEnemyAttack[nCntAttack2]->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntAttack = 0; nCntAttack < MAX_ENEMYATTACK; nCntAttack++)
		{
			switch (nCntAttack2)
			{
			case ENEMYATTACKTYPE_1:
				SetVertexAttack(nCntAttack);
				break;

			case ENEMYATTACKTYPE_2:
				SetVertexAttack2(nCntAttack);
			}

			//�@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

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

			pVtx += 4;
		}
	}

	for (int nCntAttack = 0; nCntAttack < ENEMYATTACKTYPE_MAX; nCntAttack++)
	{
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffEnemyAttack[nCntAttack]->Unlock();
	}

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�I������
////////////////////////////////////////////////////////////////////////////////
void UninitEnemyAttack(void)
{
	//���_�o�b�t�@�̊J��
	for (int nCntAttack = 0; nCntAttack < ENEMYATTACKTYPE_MAX; nCntAttack++)
	{
		if (g_pVtxBuffEnemyAttack[nCntAttack] != NULL)
		{
			g_pVtxBuffEnemyAttack[nCntAttack]->Release();	//�J��
			g_pVtxBuffEnemyAttack[nCntAttack] = NULL;		//������
		}
	}

	//�e�N�X�`���̊J��
	if (g_pTextureEnemyAttack != NULL)
	{
		g_pTextureEnemyAttack->Release();	//�J��
		g_pTextureEnemyAttack = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateEnemyAttack(void)
{
	EnemyAttack();
	EnemyAttack2();
}

////////////////////////////////////////////////////////////////////////////////
//�`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawEnemyAttack(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 120);

	//���C�e�B���O�̖���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntAttack = 0; nCntAttack < MAX_ENEMYATTACK; nCntAttack++)
	{
		for(int nCntAttack2 = 0; nCntAttack2 < ENEMYATTACKTYPE_MAX; nCntAttack2++)
		if (g_aEnemyAttack[nCntAttack][nCntAttack2].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEnemyAttack[nCntAttack][nCntAttack2].mtxworld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEnemyAttack[nCntAttack][nCntAttack2].pos.x, g_aEnemyAttack[nCntAttack][nCntAttack2].pos.y, g_aEnemyAttack[nCntAttack][nCntAttack2].pos.z);
			D3DXMatrixMultiply(&g_aEnemyAttack[nCntAttack][nCntAttack2].mtxworld, &g_aEnemyAttack[nCntAttack][nCntAttack2].mtxworld, &mtxTrans);

			//���[���h�}�g���b�N�X
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemyAttack[nCntAttack][nCntAttack2].mtxworld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEnemyAttack[nCntAttack2], 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEnemyAttack);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntAttack * 4, 2);
		}
	}

	//���e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//���C�e�B���O��L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

////////////////////////////////////////////////////////////////////////////////
//�G�̍U���̃Z�b�g�����@
////////////////////////////////////////////////////////////////////////////////
void SetEnemyAttack(void)
{
	//�ϐ��錾
	PLAYER *player = GetPlayer();

	for (int nCntAttack = 0; nCntAttack < MAX_ENEMYATTACK; nCntAttack++)
	{
		if (g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].bUse == false)
		{
			g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].pos = D3DXVECTOR3(player->pos.x + GetRandom(-500, 500), 1.0f, player->pos.z + GetRandom(-500, 500));
			g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].bUse = true;
			g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].nTime = ATTACK_TIME;
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�G�̍U�����Z�b�g�A
////////////////////////////////////////////////////////////////////////////////
void SetEnemyAttack2(void)
{
	ENEMY *enemy = GetEnemy();

	for (int nCntAttack = 0; nCntAttack < MAX_ENEMYATTACK; nCntAttack++)
	{
		if (g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].bUse == false)
		{
			g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].pos = D3DXVECTOR3(enemy->pos.x, 1.0f, enemy->pos.z);
			g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].bUse = true;
			g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].nTime = ATTACK_TIME2;
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�G�̍U���@
////////////////////////////////////////////////////////////////////////////////
void EnemyAttack(void)
{
	PLAYER *player = GetPlayer();
	D3DXVECTOR3 Distance[MAX_ENEMYATTACK];
	float fDis[MAX_ENEMYATTACK];
	float fSize = powf(ATTACK_SIZE, 2.0f);
	int nAttack = ENEMYATTACK_DAMAGE;

	for (int nCntAttack = 0; nCntAttack < MAX_ENEMYATTACK; nCntAttack++)
	{
		if (g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].bUse == true)
		{
			Distance[nCntAttack].x = (player->pos.x - g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].pos.x);
			Distance[nCntAttack].z = (player->pos.z - g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].pos.z);

			Distance[nCntAttack].x = powf(Distance[nCntAttack].x, 2.0f);
			Distance[nCntAttack].z = powf(Distance[nCntAttack].z, 2.0f);

			Distance[nCntAttack].x -= powf(PLAYER_SIZEXZ, 2.0f);
			Distance[nCntAttack].z -= powf(PLAYER_SIZEXZ, 2.0f);

			fDis[nCntAttack] = Distance[nCntAttack].x + Distance[nCntAttack].z;

			g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].nTime--;
			if (g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].nTime <= 0)
			{
				if (fDis[nCntAttack] <= fSize)
				{
					if (player->nLife - nAttack < 0)
					{	//�U�����G�̎c��HP�𒴂����Ƃ�0�܂ł̃_���[�W�ɕϊ�
						nAttack = player->nLife;
					}
					player->nLife -= nAttack;
					SetHitEffect(player->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].bUse = false;
				SetObject(g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_1].pos);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�G�̍U���A
////////////////////////////////////////////////////////////////////////////////
void EnemyAttack2(void)
{
	PLAYER *player = GetPlayer();
	D3DXVECTOR3 Distance[MAX_ENEMYATTACK];
	float fDis[MAX_ENEMYATTACK];
	float fSize = powf(ATTACK_SIZE2, 2.0f);
	int nAttack = ENEMYATTACK_DAMAGE;

	for (int nCntAttack = 0; nCntAttack < MAX_ENEMYATTACK; nCntAttack++)
	{
		if (g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].bUse == true)
		{
			Distance[nCntAttack].x = (player->pos.x - g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].pos.x);
			Distance[nCntAttack].z = (player->pos.z - g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].pos.z);

			Distance[nCntAttack].x = powf(Distance[nCntAttack].x, 2.0f);
			Distance[nCntAttack].z = powf(Distance[nCntAttack].z, 2.0f);

			Distance[nCntAttack].x -= powf(PLAYER_SIZEXZ, 2.0f);
			Distance[nCntAttack].z -= powf(PLAYER_SIZEXZ, 2.0f);

			fDis[nCntAttack] = Distance[nCntAttack].x + Distance[nCntAttack].z;

			g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].nTime--;
			if (g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].nTime <= 0)
			{
				if (fDis[nCntAttack] <= fSize)
				{
					if (player->nLife - nAttack < 0)
					{	//�U�����G�̎c��HP�𒴂����Ƃ�0�܂ł̃_���[�W�ɕϊ�
						nAttack = player->nLife;
					}
					player->nLife -= nAttack;
					SetHitEffect(player->pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				g_aEnemyAttack[nCntAttack][ENEMYATTACKTYPE_2].bUse = false;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//���_���W�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetVertexAttack(int nIdx)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemyAttack[ENEMYATTACKTYPE_1]->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx�̃|�C���^����
	pVtx += nIdx * 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_1].pos.x - ATTACK_SIZE, 1, g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_1].pos.z - ATTACK_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_1].pos.x - ATTACK_SIZE, 1, g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_1].pos.z + ATTACK_SIZE);
	pVtx[2].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_1].pos.x + ATTACK_SIZE, 1, g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_1].pos.z - ATTACK_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_1].pos.x + ATTACK_SIZE, 1, g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_1].pos.z + ATTACK_SIZE);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemyAttack[ENEMYATTACKTYPE_1]->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//���_���W�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetVertexAttack2(int nIdx)
{
	//�ϐ��錾
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemyAttack[ENEMYATTACKTYPE_2]->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx�̃|�C���^����
	pVtx += nIdx * 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_2].pos.x - ATTACK_SIZE2, 1, g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_2].pos.z - ATTACK_SIZE2);
	pVtx[1].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_2].pos.x - ATTACK_SIZE2, 1, g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_2].pos.z + ATTACK_SIZE2);
	pVtx[2].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_2].pos.x + ATTACK_SIZE2, 1, g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_2].pos.z - ATTACK_SIZE2);
	pVtx[3].pos = D3DXVECTOR3(g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_2].pos.x + ATTACK_SIZE2, 1, g_aEnemyAttack[nIdx][ENEMYATTACKTYPE_2].pos.z + ATTACK_SIZE2);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemyAttack[ENEMYATTACKTYPE_2]->Unlock();
}