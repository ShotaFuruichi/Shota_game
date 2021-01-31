////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �v���C���[�̏��� [player.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/10/13
//
////////////////////////////////////////////////////////////////////////////////
#include "game.h"
#include "player.h"
#include "input.h"
#include "Item.h"
#include "block.h"
#include "enemy.h"
#include "bullet.h"
#include "fade.h"
#include "time.h"
#include "sound.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define POS_X (DIAGONAL_X)					//���SX���W
#define POS_Y (SCREEN_HEIGHT - BLOCK_SIZE)	//���SY���W
#define POS_Z (0)							//���SZ���W

#define SHOT_INTERVAL (50)					//�ˌ��̊Ԋu
#define STOP_SHOT (50)						//�e���~�߂��鎞��

#define MOVE_SPEED (3.0f)					//�ړ����x
#define DOWN_SPEED (0.7f)					//�ړ����x * DOWN_SPEED �Ō���
#define ROTATE_SPEED (0.04f)				//��]�̑��x

#define DAMAGE_FLASH (10)					//�_���[�W���󂯂����̓_�ő��x
#define DAMAGE_END (60)						//�_���[�W���󂯂鏈���̏I�����x
#define DEATH_TIME (30)						//���S����t�F�[�h�܂ł̑��x

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePlayer;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePlayer2;			//�e�N�X�`���ւ̃|�C���^
PLAYER g_Player;									//�v���C���[�̏��
int g_nCounterShot = 0;								///�ˌ��J�E���^�[
int g_AnimCounter;
int g_AnimNum;	
int g_stage;

////////////////////////////////////////////////////////////////////////////////
//�v���C���[�̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitPlayer(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_pVtxBuffPlayer = NULL;														//���_�o�b�t�@�ւ̃|�C���^
	g_pTexturePlayer = NULL;														//�e�N�X�`���ւ̃|�C���^
	g_pTexturePlayer2 = NULL;														//�e�N�X�`���ւ̃|�C���^
	g_Player.pos = D3DXVECTOR3(POS_X, POS_Y, POS_Z);								//���S���W�̐ݒ�
	g_Player.oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								//�O�̈ʒu
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//��]�p�̐ݒ�
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//�ړ���
	g_Player.bJump = false;															//�W�����v���Ă��邩
	g_Player.fLength = sqrtf(DIAGONAL_X * DIAGONAL_X + DIAGONAL_Y * DIAGONAL_Y);	//�Ίp���̒����̐ݒ�
	g_Player.fAngle = atan2f(DIAGONAL_X, DIAGONAL_Y);								//�Ίp���̊p�x�̐ݒ�
	g_Player.nLife = 2;																//�̗͂̐ݒ�
	g_Player.state = PLAYERSTATE_APPER;												//��Ԃ̐ݒ�
	g_Player.nCounterState = 0;														//��ԃJ�E���^�̐ݒ�
	g_Player.nCounterDisp = 0;														//�\���J�E���^�̐ݒ�
	g_Player.bDisp = true;															//�\��ON/OFF�̐ݒ�
	g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);								//�F�̐ݒ�
	g_Player.Direction = false;														//����
	g_AnimCounter = 0;
	g_AnimNum;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\snowman0.png", &g_pTexturePlayer);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPlayer, NULL)))
	{
		return E_FAIL;
	}
	
	//���_���̐ݒ�
	SetVertexPlayer();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�F�̐ݒ�
	SetColorPlayer();

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�v���C���[�̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitPlayer(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();	//�J��
		g_pVtxBuffPlayer = NULL;		//������
	}

	//�e�N�X�`���̊J��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();	//�J��
		g_pTexturePlayer = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//�v���C���[�̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdatePlayer(void)
{
	STAGE stage;
	bool bClear;
	bClear = GetClear();
	stage = GetStage();

	//�O��̈ʒu�̕ۑ�
	g_Player.oldpos = g_Player.pos;

	//�ړ�����
	MovePlayer();
	
	//�G�Ƃ̓����蔻��
	HitPlayer();

	//�ˌ�����
	ShotPlayer();
	
	//�u���b�N�̓����蔻��
	ColisionBlock(&g_Player.pos, &g_Player.oldpos, &g_Player.move, DIAGONAL_X, DIAGONAL_Y);

	//�ʏ�̒��_���̐ݒ�
	SetVertexPlayer();
	
	//�A�C�e���Ƃ̓����蔻��
	if (HitItem() == true)
	{
		switch (stage)
		{
		case STAGE_0:
			SetStageMode(STAGE_1);
			break;

		case STAGE_1:
			/*SetStageMode(STAGE_2);*/
			bClear = true;
			SetFade(FADE_OUT, MODE_RESULT);
			SetStageMode(STAGE_MAX);
			break;

		/*case STAGE_2:
			SetStageMode(STAGE_3);
			break;

		case STAGE_3:
			SetFade(FADE_OUT, MODE_RESULT);
			SetStageMode(STAGE_MAX);
			break;*/
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�v���C���[�̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawPlayer(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`��
	pDevice->SetTexture(0, g_pTexturePlayer);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

////////////////////////////////////////////////////////////////////////////////
//�v���C���[�̒��_���̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetVertexPlayer(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���̈ʒu��ݒ�
	pVtx[0].pos.x = g_Player.pos.x - DIAGONAL_X;
	pVtx[0].pos.y = g_Player.pos.y;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Player.pos.x - DIAGONAL_X;
	pVtx[1].pos.y = g_Player.pos.y - (DIAGONAL_Y);
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Player.pos.x + DIAGONAL_X;
	pVtx[2].pos.y = g_Player.pos.y;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Player.pos.x + DIAGONAL_X;
	pVtx[3].pos.y = g_Player.pos.y - (DIAGONAL_Y);
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�v���C���[�̎ˌ�����
////////////////////////////////////////////////////////////////////////////////
void ShotPlayer(void)
{
	if (GetKeyboardPress(DIK_RETURN) == true)
	{
		g_nCounterShot++;
		if (g_nCounterShot % 2 == 0)
		{
			if (g_Player.Direction == false)
			{
				SetBullet(D3DXVECTOR3(g_Player.pos.x + DIAGONAL_X + 25.0f, g_Player.pos.y - 40, 0.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 10);
				PlaySoundN(SOUND_LABEL_SE_SHOT);
			}
			else if (g_Player.Direction == true)
			{
				SetBullet(D3DXVECTOR3(g_Player.pos.x - DIAGONAL_X - 25.0f, g_Player.pos.y - 40, 0.0f), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 10);
				PlaySoundN(SOUND_LABEL_SE_SHOT);
			}
		}
	}
	else
	{
		StopSound(SOUND_LABEL_SE_SHOT);
	}
}

////////////////////////////////////////////////////////////////////////////////
//�v���C���[�̈ړ�����
////////////////////////////////////////////////////////////////////////////////
void MovePlayer(void)
{	
	//�ϐ��錾
	VERTEX_2D *pVtx;

	g_Player.oldpos = g_Player.pos;

	if (GetKeyboardPress(DIK_D) == true)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{
		}
		else
		{
			g_Player.move.x += 0.425f;

			g_Player.Direction = false;

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffPlayer->Unlock();
		}	
	}
	else if(GetKeyboardPress(DIK_A) == true)
	{
		if (GetKeyboardPress(DIK_D) == true)
		{
		}
		else
		{
			g_Player.move.x -= 0.425f;

			g_Player.Direction = true;

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffPlayer->Unlock();
		}
	}

	if (g_Player.bJump == false)
	{
		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{
			g_Player.move.y -= 20.0f;
			g_Player.bJump = true;
			PlaySound(SOUND_LABEL_SE_JUMP);
		}
	}
	if (g_Player.state == PLAYERSTATE_DAMAGE)
	{
		g_Player.move.y -= 3.0f;
		g_Player.state = PLAYERSTATE_NORMAL;
	}

	g_Player.move.y += 1.5f;

	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.1f;

	if (g_Player.pos.y > SCREEN_HEIGHT)
	{
		g_Player.move.y = 0.0f;
		g_Player.pos.y = SCREEN_HEIGHT;
		g_Player.bJump = false;
	}

	if ((g_Player.pos.x - DIAGONAL_X) <= 0)
	{
		g_Player.pos.x = DIAGONAL_X;
	}
	if ((g_Player.pos.x + DIAGONAL_X) >= SCREEN_WIDTH)
	{
		g_Player.pos.x = (SCREEN_WIDTH - DIAGONAL_X);
	}
}

////////////////////////////////////////////////////////////////////////////////
//�F�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetColorPlayer(void)
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = g_Player.col;
	pVtx[1].col = g_Player.col;
	pVtx[2].col = g_Player.col;
	pVtx[3].col = g_Player.col;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�����蔻��
////////////////////////////////////////////////////////////////////////////////
void HitPlayer(void)
{
	//�ϐ��錾
	float fDisX;
	float fDisY;
	float fRangeX;
	float fRangeY;
	ENEMY *pEnemy;
	pEnemy = GetEnemy();
	fRangeX = DIAGONAL_X + ENEMY_SIZEX;
	fRangeY = DIAGONAL_Y + ENEMY_SIZEY;

	//�G�Ƃ̓����蔻��
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{	//�G���g�p���Ă���ꍇ
			switch (pEnemy->state)
			{
			case ENEMYSTATE_NORMAL:
				if (g_Player.pos.x >= pEnemy->pos.x)
				{
					fDisX = g_Player.pos.x - pEnemy->pos.x + 20;
				}
				else if (g_Player.pos.x <= pEnemy->pos.x)
				{
					fDisX = pEnemy->pos.x - g_Player.pos.x + 20;
				}

				if ((g_Player.pos.y - (DIAGONAL_Y / 2)) >= (pEnemy->pos.y - (ENEMY_SIZEY / 2)))
				{
					fDisY = (g_Player.pos.y - (DIAGONAL_Y / 2)) - (pEnemy->pos.y - (ENEMY_SIZEY / 2));
				}
				else if ((g_Player.pos.y - (DIAGONAL_Y / 2)) <= (pEnemy->pos.y - (ENEMY_SIZEY / 2)))
				{
					fDisY = (pEnemy->pos.y - (ENEMY_SIZEY / 2)) - (g_Player.pos.y - (DIAGONAL_Y / 2));
				}

				if (0 > (fDisX - fRangeX) && -60 > (fDisY - fRangeY))
				{
					g_Player.state = PLAYERSTATE_DAMAGE;
					if (pEnemy->pos.x < g_Player.pos.x)
					{
						g_Player.move.x += 8.0f;
						g_Player.bDisp = false;
					}
					else
					{
						g_Player.move.x -= 8.0f;
						g_Player.bDisp = false;
					}
				}
				break;

			case ENEMYSTATE_FREEZE:
				if ((g_Player.pos.x + DIAGONAL_X) > (pEnemy->pos.x - ENEMY_SIZEX) && (g_Player.pos.x - DIAGONAL_X) < (pEnemy->pos.x + ENEMY_SIZEX))
				{
					if (g_Player.oldpos.y <= (pEnemy->pos.y - ENEMY_SIZEY))
					{
						if (g_Player.pos.y > (pEnemy->pos.y - ENEMY_SIZEY))
						{
							g_Player.move.y = 0.0f;
							g_Player.pos.y = (pEnemy->pos.y - ENEMY_SIZEY);
							g_Player.bJump = false;
							g_Player.move.x += pEnemy->move.x / 10;
						}
					}
					if ((g_Player.oldpos.y - DIAGONAL_Y) >= pEnemy->pos.y)
					{
						if ((g_Player.pos.y - DIAGONAL_Y) < pEnemy->pos.y)
						{
							g_Player.move.y = 0.0f;
							g_Player.pos.y = g_Player.oldpos.y;
						}
					}
				}

				for (int nCnt = 0; nCnt < DIAGONAL_Y; nCnt++)
				{
					if ((g_Player.pos.y - nCnt) > (pEnemy->pos.y - ENEMY_SIZEY) && (g_Player.pos.y - nCnt) < pEnemy->pos.y)
					{
						if ((g_Player.oldpos.x + DIAGONAL_X) <= (pEnemy->pos.x - ENEMY_SIZEX))
						{
							if ((g_Player.pos.x + DIAGONAL_X) > (pEnemy->pos.x - ENEMY_SIZEX))
							{
									g_Player.pos.x = g_Player.oldpos.x;
									pEnemy->move.x += 2.0f;
							}
						}
						else if ((g_Player.oldpos.x - DIAGONAL_X) >= (pEnemy->pos.x + ENEMY_SIZEX))
						{
							if ((g_Player.pos.x - DIAGONAL_X) < (pEnemy->pos.x + ENEMY_SIZEX))
							{
									g_Player.pos.x = g_Player.oldpos.x;
									pEnemy->move.x -= 2.0f;
							}
						}
					}
				}
				break;
			}
		}
	}
}


////////////////////////////////////////////////////////////////////////////////
//�A�C�e���Ƃ̓����蔻��
////////////////////////////////////////////////////////////////////////////////
bool HitItem(void)
{
	//�ϐ��錾
	float fDisX;
	float fDisY;
	float fRangeX;
	float fRangeY;
	ITEM *pItem;
	pItem = GetItem();
	fRangeX = DIAGONAL_X + pItem->fWidth;
	fRangeY = DIAGONAL_Y + pItem->fHeight;

	////�A�C�e���Ƃ̓����蔻��
	//for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	//{
		if (pItem->bUse == true)
		{	//�A�C�e�����g�p���Ă���ꍇ

			if (g_Player.pos.x >= pItem->pos.x)
			{
				fDisX = g_Player.pos.x - pItem->pos.x;
			}
			else if (g_Player.pos.x <= pItem->pos.x)
			{
				fDisX = pItem->pos.x - g_Player.pos.x;
			}

			if ((g_Player.pos.y - 80) >= pItem->pos.y)
			{
				fDisY = (g_Player.pos.y - 80) - pItem->pos.y;
			}
			else if ((g_Player.pos.y - 80) <= pItem->pos.y)
			{
				fDisY = (pItem->pos.y - 80) - g_Player.pos.y;
			}

			if (0 > (fDisX - fRangeX) && 0 > (fDisY - fRangeY))
			{	
				pItem->bUse = false;
				return true;
			}
		}
		return false;
	/*}*/
}

////////////////////////////////////////////////////////////////////////////////
//�v���C���[�̏��̎擾
////////////////////////////////////////////////////////////////////////////////
PLAYER *GetPlayer(void)
{
	return &g_Player;
}