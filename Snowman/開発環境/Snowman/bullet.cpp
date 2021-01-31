////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �e�̏��� [bullet.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/10/26
//
////////////////////////////////////////////////////////////////////////////////
#include "bullet.h"
#include "enemy.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define BULLET_SIZEX (50.0f)	//�e�̉��̑傫��
#define BULLET_SIZEY (30.0f)	//�e�̏c�̑傫��
#define BULLET_DAMAGE (1)		//�e�̃_���[�W��

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		//���_�o�b�t�@�ւ̐ݒ�
BULLET g_aBullet[MAX_BULLET];							//�e�̏��
int g_nCntAnim;											//�A�j���[�V����

////////////////////////////////////////////////////////////////////////////////
//�e�̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitBullet(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�ϐ��̏�����
	g_pTextureBullet = NULL;
	g_pVtxBuffBullet = NULL;

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{	
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0, 0, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\��C01.png", &g_pTextureBullet);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBullet, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�
		SetVertexBullet(nCntBullet);

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

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f,1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f,1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f,0.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�e�̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitBullet(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();	//�J��
		g_pVtxBuffBullet = NULL;		//������
	}

	//�e�N�X�`���̊J��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();	//�J��
		g_pTextureBullet = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�e�̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateBullet(void)
{
	//�ϐ��錾
	BULLET *pBullet;
	ENEMY *pEnemy;

	//�G�̏����擾
	pBullet = &g_aBullet[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{	//�e���g�p����Ă���Ƃ�
#if 0
			g_nCntAnim++;
			if (g_nCntAnim % 50 == 0)
			{
				//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
				g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(g_nCntAnim * 0.25f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(g_nCntAnim * 0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((g_nCntAnim + 1)* 0.25f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2((g_nCntAnim + 1)* 0.25f, 0.0f);

				//���_�o�b�t�@���A�����b�N����
				g_pVtxBuffBullet->Unlock();
			}
#endif

			// �ʒu�X�V
			pBullet->pos.x += pBullet->move.x;
			pBullet->pos.y += pBullet->move.y;

			//��������
			pBullet->nLife--;
			if (pBullet->nLife == 0)
			{
				pBullet->bUse = false;
			}

			//���_���W�̐ݒ�
			SetVertexBullet(nCntBullet);

			pEnemy = GetEnemy();

			//�G�Ƃ̓����蔻��
			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				//��ʊO�`�F�b�N
				if (pBullet->pos.y < 0 || pBullet->pos.y > 1080 || pBullet->pos.x < 0 || pBullet->pos.x > 1920)
				{
					pBullet->bUse = false;
				}

				if (pEnemy->bUse == true)
				{	//�G���g�p���Ă���ꍇ
					if (pBullet->pos.y < pEnemy->pos.y && pBullet->pos.y >(pEnemy->pos.y - ENEMY_SIZEY) &&
						pBullet->pos.x > (pEnemy->pos.x - ENEMY_SIZEX) && pBullet->pos.x < (pEnemy->pos.x + ENEMY_SIZEX))
					{	//�����蔻��

						//�G�̔�e����
						HitEnemy(nCntEnemy, BULLET_DAMAGE);
					}
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�e�̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawBullet(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{	//�e���g�p����Ă���ꍇ
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�e�̃Z�b�g����
////////////////////////////////////////////////////////////////////////////////
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	//�ϐ��錾
	BULLET *pBullet;

	pBullet = &g_aBullet[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{	//�e���g�p����Ă��Ȃ��Ƃ�

			//�ʒu�̐ݒ�
			pBullet->pos = pos;

			//���_���W�̐ݒ�
			SetVertexBullet(nCntBullet);

			//�ړ��ʂ̐ݒ�
			pBullet->move = move;

			//�����̐ݒ�
			pBullet->nLife = nLife;
			
			//�e���g�p����
			pBullet->bUse = true;
			
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�e�̒��_���W�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetVertexBullet(int nIdx)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx�̃|�C���^����
	pVtx += nIdx * 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_SIZEX, g_aBullet[nIdx].pos.y + BULLET_SIZEY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_SIZEX, g_aBullet[nIdx].pos.y - BULLET_SIZEY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_SIZEX, g_aBullet[nIdx].pos.y + BULLET_SIZEY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_SIZEX, g_aBullet[nIdx].pos.y - BULLET_SIZEY, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}