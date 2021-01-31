////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �e�̏��� [bullet.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/08/03
//
////////////////////////////////////////////////////////////////////////////////
#include "bullet.h"
#include "enemy.h"
#include "sound.h"
#include "effect.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define BULLET_SIZE (20.0f)	//�e�̑傫��
#define BULLET_DAMAGE (1)	//�e�̃_���[�W��
#define BULLET_LIFE (15)	//�g�U�Ɏg���e�̎���

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9 g_pTextureBullet[TYPE_MAX] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		//���_�o�b�t�@�ւ̐ݒ�
BULLET g_aBullet[MAX_BULLET];							//�e�̏��
int g_EffectCounter[MAX_EFFECT] = {};					//�G�t�F�N�g�J�E���^�[

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

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_pTextureBullet[TYPE_NORMAL]);			//�ʏ�e
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_pTextureBullet[TYPE_THROUGH]);		//�ђʒe
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_pTextureBullet[TYPE_REFLECTIVE]);		//���˒e
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_pTextureBullet[TYPE_DIFFUSION]);		//�g�U�e

	//�ϐ��̏�����
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{	
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0, 0, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].nType = TYPE_NORMAL;
		g_aBullet[nCntBullet].nEffect = 0;
	}

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
	for (int nCntBullet = 0; nCntBullet < TYPE_MAX; nCntBullet++)
	{
		if (g_pTextureBullet[nCntBullet] != NULL)
		{
			g_pTextureBullet[nCntBullet]->Release();	//�J��
			g_pTextureBullet[nCntBullet] = NULL;		//������
		}
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

	pBullet = &g_aBullet[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{	//�e���g�p����Ă���Ƃ�

			// �ʒu�X�V
			pBullet->pos.x += pBullet->move.x;
			pBullet->pos.y += pBullet->move.y;

			//��������
			pBullet->nLife--;

			//���_���W�̐ݒ�
			SetVertexBullet(nCntBullet);

			//�G�̏����擾
			pEnemy = GetEnemy();

			switch (pBullet->nType)
			{
			case TYPE_NORMAL:	//�ʏ�̒e
				//�G�Ƃ̓����蔻��
				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					//��ʊO�`�F�b�N
					if (pBullet->pos.y < 0 || pBullet->pos.y > SCREEN_HEIGHT || pBullet->pos.x < 0 || pBullet->pos.x > SCREEN_WIDTH)
					{
					pBullet->bUse = false;
					}

					if (pEnemy->bUse == true)
					{	//�G���g�p���Ă���ꍇ
						switch (pEnemy->nType)
						{
						case ENEMYTYPE_BIG:
							if (pBullet->pos.y < (pEnemy->pos.y + BIGENEMY_SIZE) && pBullet->pos.y >(pEnemy->pos.y - BIGENEMY_SIZE) &&
								pBullet->pos.x > (pEnemy->pos.x - BIGENEMY_SIZE) && pBullet->pos.x < (pEnemy->pos.x + BIGENEMY_SIZE))
							{	//�����蔻��

								//���e���Đ�
								PlaySound(SOUND_LABEL_SE_HIT);

								//�e�̔j��
								pBullet->bUse = false;

								g_aBullet[nCntBullet].nEffect = 0;

								//�G�̔�e����
								HitEnemy(nCntEnemy, BULLET_DAMAGE);
							}
							break;

						default:
							if (pBullet->pos.y < (pEnemy->pos.y + ENEMY_SIZE) && pBullet->pos.y >(pEnemy->pos.y - ENEMY_SIZE) &&
								pBullet->pos.x > (pEnemy->pos.x - ENEMY_SIZE) && pBullet->pos.x < (pEnemy->pos.x + ENEMY_SIZE))
							{	//�����蔻��

								//���e���Đ�
								PlaySound(SOUND_LABEL_SE_HIT);

								//�e�̔j��
								pBullet->bUse = false;

								g_aBullet[nCntBullet].nEffect = 0;

								//�G�̔�e����
								HitEnemy(nCntEnemy, BULLET_DAMAGE);
							}
							break;
						}
					}
				}
				break;

			case TYPE_THROUGH:	//�ђʒe
								
				//�G�t�F�N�g�g�p
				SetEffect(pBullet->pos, D3DXCOLOR(1.0f, 0.75f, 0.5f, 1.0f));

				//�G�Ƃ̓����蔻��
				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{	//�G���g�p���Ă���ꍇ
						switch (pEnemy->nType)
						{
						case ENEMYTYPE_BIG:
							if (pBullet->pos.y < (pEnemy->pos.y + BIGENEMY_SIZE) && pBullet->pos.y >(pEnemy->pos.y - BIGENEMY_SIZE) &&
								pBullet->pos.x > (pEnemy->pos.x - BIGENEMY_SIZE) && pBullet->pos.x < (pEnemy->pos.x + BIGENEMY_SIZE))
							{
								//���e���Đ�
								PlaySound(SOUND_LABEL_SE_HIT);

								//�G�̔�e����
								HitEnemy(nCntEnemy, BULLET_DAMAGE);
							}
							break;

						default:
							if (pBullet->pos.y < (pEnemy->pos.y + ENEMY_SIZE) && pBullet->pos.y >(pEnemy->pos.y - ENEMY_SIZE) &&
								pBullet->pos.x > (pEnemy->pos.x - ENEMY_SIZE) && pBullet->pos.x < (pEnemy->pos.x + ENEMY_SIZE))
							{
								//���e���Đ�
								PlaySound(SOUND_LABEL_SE_HIT);

								//�G�̔�e����
								HitEnemy(nCntEnemy, BULLET_DAMAGE);
							}
							break;
						}
					}
				}
				break;

			case TYPE_REFLECTIVE:	//���˒e

				//�G�t�F�N�g�g�p
				SetEffect(pBullet->pos, D3DXCOLOR(0.5f, 0.75f, 1.0f, 1.0f));

				//��ʊO�`�F�b�N
				if (pBullet->pos.y <= 0 + BULLET_SIZE || pBullet->pos.y >= SCREEN_HEIGHT - BULLET_SIZE)
				{
					pBullet->move.y *= -1;
				}
				if (pBullet->pos.x <= 0 + BULLET_SIZE || pBullet->pos.x >= SCREEN_WIDTH - BULLET_SIZE)
				{
					pBullet->move.x *= -1;
				}

				//�G�Ƃ̓����蔻��
				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{	//�G���g�p���Ă���ꍇ
						switch (pEnemy->nType)
						{
						case ENEMYTYPE_BIG:
							if (pBullet->pos.y < (pEnemy->pos.y + BIGENEMY_SIZE) && pBullet->pos.y >(pEnemy->pos.y - BIGENEMY_SIZE) &&
								pBullet->pos.x > (pEnemy->pos.x - BIGENEMY_SIZE) && pBullet->pos.x < (pEnemy->pos.x + BIGENEMY_SIZE))
							{
								//���e���Đ�
								PlaySound(SOUND_LABEL_SE_HIT);

								//�e�̔j��
								pBullet->bUse = false;

								g_aBullet[nCntBullet].nEffect = 0;

								//�G�̔�e����
								HitEnemy(nCntEnemy, BULLET_DAMAGE);
							}
							break;

						default:
							if (pBullet->pos.y < (pEnemy->pos.y + ENEMY_SIZE) && pBullet->pos.y >(pEnemy->pos.y - ENEMY_SIZE) &&
								pBullet->pos.x > (pEnemy->pos.x - ENEMY_SIZE) && pBullet->pos.x < (pEnemy->pos.x + ENEMY_SIZE))
							{
								//���e���Đ�
								PlaySound(SOUND_LABEL_SE_HIT);

								//�e�̔j��
								pBullet->bUse = false;

								g_aBullet[nCntBullet].nEffect = 0;

								//�G�̔�e����
								HitEnemy(nCntEnemy, BULLET_DAMAGE);
							}
							break;
						}
					}
				}
				break;

			case TYPE_DIFFUSION:

				//�G�t�F�N�g�g�p
				SetEffect(pBullet->pos, D3DXCOLOR(0.5f, 1.0f, 0.5f, 1.0f));

				//�G�Ƃ̓����蔻��
				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					//��ʊO�`�F�b�N
					if (pBullet->pos.y < 0 || pBullet->pos.y > 1080 || pBullet->pos.x < 0 || pBullet->pos.x > 1920)
					{
						pBullet->bUse = false;
					}

					if (pBullet->nLife < 0)
					{
						SetBullet(pBullet->pos, D3DXVECTOR3(BULLET_SPEED, 0.0f, 0.0f), BULLET_LIFE, TYPE_NORMAL);
						SetBullet(pBullet->pos, D3DXVECTOR3(-BULLET_SPEED, 0.0f, 0.0f), BULLET_LIFE, TYPE_NORMAL);
						SetBullet(pBullet->pos, D3DXVECTOR3(0.0f, BULLET_SPEED, 0.0f), BULLET_LIFE, TYPE_NORMAL);
						SetBullet(pBullet->pos, D3DXVECTOR3(0.0f, -BULLET_SPEED, 0.0f), BULLET_LIFE, TYPE_NORMAL);
						//�e�̔j��
						pBullet->bUse = false;
					}

					if (pEnemy->bUse == true)
					{	//�G���g�p���Ă���ꍇ
						switch (pEnemy->nType)
						{
						case ENEMYTYPE_BIG:
							if (pBullet->pos.y < (pEnemy->pos.y + BIGENEMY_SIZE) && pBullet->pos.y >(pEnemy->pos.y - BIGENEMY_SIZE) &&
								pBullet->pos.x > (pEnemy->pos.x - BIGENEMY_SIZE) && pBullet->pos.x < (pEnemy->pos.x + BIGENEMY_SIZE))
							{	//�����蔻��

								SetBullet(pBullet->pos, D3DXVECTOR3(BULLET_SPEED, 0.0f, 0.0f), BULLET_LIFE, TYPE_NORMAL);
								SetBullet(pBullet->pos, D3DXVECTOR3(-BULLET_SPEED, 0.0f, 0.0f), BULLET_LIFE, TYPE_NORMAL);
								SetBullet(pBullet->pos, D3DXVECTOR3(0.0f, BULLET_SPEED, 0.0f), BULLET_LIFE, TYPE_NORMAL);
								SetBullet(pBullet->pos, D3DXVECTOR3(0.0f, -BULLET_SPEED, 0.0f), BULLET_LIFE, TYPE_NORMAL);

								//���e���Đ�
								PlaySound(SOUND_LABEL_SE_HIT);

								//�e�̔j��
								pBullet->bUse = false;

								g_aBullet[nCntBullet].nEffect = 0;

								//�G�̔�e����
								HitEnemy(nCntEnemy, BULLET_DAMAGE);		
							}
							break;

						default:
							if (pBullet->pos.y < (pEnemy->pos.y + ENEMY_SIZE) && pBullet->pos.y >(pEnemy->pos.y - ENEMY_SIZE) &&
								pBullet->pos.x > (pEnemy->pos.x - ENEMY_SIZE) && pBullet->pos.x < (pEnemy->pos.x + ENEMY_SIZE))
							{	//�����蔻��

								SetBullet(pBullet->pos, D3DXVECTOR3(BULLET_SPEED, 0.0f, 0.0f), BULLET_LIFE, TYPE_NORMAL);
								SetBullet(pBullet->pos, D3DXVECTOR3(-BULLET_SPEED, 0.0f, 0.0f), BULLET_LIFE, TYPE_NORMAL);
								SetBullet(pBullet->pos, D3DXVECTOR3(0.0f, BULLET_SPEED, 0.0f), BULLET_LIFE, TYPE_NORMAL);
								SetBullet(pBullet->pos, D3DXVECTOR3(0.0f, -BULLET_SPEED, 0.0f), BULLET_LIFE, TYPE_NORMAL);

								//���e���Đ�
								PlaySound(SOUND_LABEL_SE_HIT);

								//�e�̔j��
								pBullet->bUse = false;

								g_aBullet[nCntBullet].nEffect = 0;

								//�G�̔�e����
								HitEnemy(nCntEnemy, BULLET_DAMAGE);
							}
							break;
						}
						
					}
				}
				break;
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
			pDevice->SetTexture(0, g_pTextureBullet[g_aBullet[nCntBullet].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
	
}

////////////////////////////////////////////////////////////////////////////////
//�e�̃Z�b�g����
////////////////////////////////////////////////////////////////////////////////
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType)
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

			//�e�̎�ނ̐ݒ�
			pBullet->nType = nType;

			//���ˉ��Đ�
			PlaySound(SOUND_LABEL_SE_SHOT);
			
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
	pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_SIZE, g_aBullet[nIdx].pos.y + BULLET_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_SIZE, g_aBullet[nIdx].pos.y - BULLET_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_SIZE, g_aBullet[nIdx].pos.y + BULLET_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_SIZE, g_aBullet[nIdx].pos.y - BULLET_SIZE, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}