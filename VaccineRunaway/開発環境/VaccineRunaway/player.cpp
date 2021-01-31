////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �v���C���[�̏��� [player.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/07/21
//
////////////////////////////////////////////////////////////////////////////////
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#include "fade.h"
#include "effect.h"
#include "explosion.h"
#include "item.h"
#include "sound.h"
#include "xinput_pad.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define POS_X (SCREEN_WIDTH / 2)	//���SX���W
#define POS_Y (780)					//���SY���W
#define POS_Z (0)					//���SZ���W

#define DIAGONAL_X (40)				//X����1�ӂ̒���
#define DIAGONAL_Y (40)				//Y����1�ӂ̒���

#define SHOT_INTERVAL (50)			//�ˌ��̊Ԋu
#define STOP_SHOT (50)				//�e���~�߂��鎞��

#define MOVE_SPEED (4.0f)			//�ړ����x
#define DOWN_SPEED (0.6f)			//�ړ����x * DOWN_SPEED �Ō���

#define PLAYER_LIFE (2)				//�v���C���[�̃��C�t
#define DAMAGE_FLASH (10)			//�_���[�W���󂯂����̓_�ő��x
#define DAMAGE_END (60)				//�_���[�W���󂯂鏈���̏I�����x
#define DEATH_TIME (30)				//���S����t�F�[�h�܂ł̑��x

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePlayer2 = NULL;		//�e�N�X�`���ւ̃|�C���^
PLAYER g_Player;									//�v���C���[�̏��
int g_nCounterShot = 0;								///�ˌ��J�E���^�[
int g_nStopShot = 0;								//�ˌ����~�߂�J�E���^�[
bool g_bStopShot = false;							//�ˌ������ǂ���

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

	g_Player.pos = D3DXVECTOR3(POS_X, POS_Y, POS_Z);								//���S���W�̐ݒ�
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//��]�p�̐ݒ�
	g_Player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								//��]�p�̐ݒ�
	g_Player.fLength = sqrtf(DIAGONAL_X * DIAGONAL_X + DIAGONAL_Y * DIAGONAL_Y);	//�Ίp���̒����̐ݒ�
	g_Player.fAngle = atan2f(DIAGONAL_X, DIAGONAL_Y);								//�Ίp���̊p�x�̐ݒ�
	g_Player.nLife = 2;																//�̗͂̐ݒ�
	g_Player.state = PLAYERSTATE_APPER;												//��Ԃ̐ݒ�
	g_Player.nCounterState = 0;														//��ԃJ�E���^�̐ݒ�
	g_Player.nCounterDisp = 0;														//�\���J�E���^�̐ݒ�
	g_Player.bDisp = true;															//�\��ON/OFF�̐ݒ�
	g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);								//�F�̐ݒ�
	g_Player.BulletType = 0;														//�e�̃^�C�v
	g_Player.BulletResidue = 0;														//����e�̎c�e��

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\player.png", &g_pTexturePlayer);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\player2.png", &g_pTexturePlayer2);

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
	SetColor();

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
	//�ϐ��錾
	FADE fade= GetFade();

	//�ʏ�̒��_���̐ݒ�
	SetVertexPlayer();

	switch (g_Player.state)
	{
	case PLAYERSTATE_APPER:
		if (fade == FADE_NONE)
		{
			g_Player.state = PLAYERSTATE_NORMAL;
		}	
		break;
	case PLAYERSTATE_NORMAL:

		//�F
		SetColor();

		//�ړ�����
		MovePlayer();

		//�ˌ�����
		ShotPlayer();

		//�G�Ƃ̓����蔻��
		HitPlayer();

		//�A�C�e���Ƃ̓����蔻��
		HitItem();

		break;

	case PLAYERSTATE_DAMAGE:

		//�ړ�����
		MovePlayer();

		//�ˌ�����
		ShotPlayer();

		g_Player.nCounterState++;
		if (g_Player.nLife > 1)
		{	//���C�t��2�ȏ�c���Ă���Ƃ�
			if (g_Player.nCounterState % DAMAGE_FLASH == 0)
			{
				if (g_Player.col.g == 1.0f && g_Player.col.b == 1.0f)
				{
					g_Player.col.g = 0.0f;
					g_Player.col.b = 0.0f;
				}
				else if (g_Player.col.g == 0.0f && g_Player.col.b == 0.0f)
				{
					g_Player.col.g = 1.0f;
					g_Player.col.b = 1.0f;
				}
				SetColor();
			}

			if (g_Player.nCounterState == DAMAGE_END)
			{	
				g_Player.col.g = 1.0f;
				g_Player.col.b = 1.0f;
				g_Player.nLife--;
				g_Player.nCounterState = 0;
				g_Player.state = PLAYERSTATE_NORMAL;
			}
		}
		else if (g_Player.nLife == 1)
		{	//���C�t���c��1�̎�
			g_Player.state = PLAYERSTATE_DEATH;
			PlaySound(SOUND_LABEL_SE_DEATH);
		}
		break;

	case PLAYERSTATE_DEATH:
		g_Player.bDisp = false;
		g_Player.nCounterDisp++;
		if (g_Player.nCounterDisp == 0)
		{
			SetExplosion(g_Player.pos);
		}
		
		if (g_Player.nCounterDisp == DEATH_TIME)
		{
			//��ʑJ��
			if (fade == FADE_NONE)
			{
				SetFade(FADE_OUT, MODE_RESULT);
			}
			break;
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

	//�e�N�X�`���̐ݒ�
	if (g_Player.nLife == 1 && g_Player.state == PLAYERSTATE_NORMAL)
	{
		pDevice->SetTexture(0, g_pTexturePlayer2);
	}
	else
	{
		pDevice->SetTexture(0, g_pTexturePlayer);
	}

	if(g_Player.bDisp == true)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
	
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
	pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI * 0.00f - g_Player.fAngle)) * g_Player.fLength;
	pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI * 0.00f - g_Player.fAngle)) * g_Player.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI * 1.00f + g_Player.fAngle)) * g_Player.fLength;
	pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI * 1.00f + g_Player.fAngle)) * g_Player.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI * 0.00f + g_Player.fAngle)) * g_Player.fLength;
	pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI * 0.00f + g_Player.fAngle)) * g_Player.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI * 1.00f - g_Player.fAngle)) * g_Player.fLength;
	pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI * 1.00f - g_Player.fAngle)) * g_Player.fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

////////////////////////////////////////////////////////////////////////////////
//�v���C���[�̎ˌ�����
////////////////////////////////////////////////////////////////////////////////
void ShotPlayer(void)
{

	//�V�t�g��������
	if (g_nStopShot <= STOP_SHOT)
	{
		if (GetKeyboardPress(DIK_SPACE) == true)
		{
			g_bStopShot = true;
		}
	}
	
	if (g_bStopShot == false)
	{	
		if (g_nStopShot > 0)
		{
			g_nStopShot--;
		}

		g_nCounterShot++;
		if (g_nCounterShot % SHOT_INTERVAL == 0)
		{
			SetBullet(g_Player.pos, D3DXVECTOR3(sinf(D3DX_PI - g_Player.rot.z) * -10.0f, cosf(D3DX_PI - g_Player.rot.z) * 10.0f, 0.0f), 40, g_Player.BulletType);

			if (g_Player.BulletType == 1)
			{
				g_Player.BulletResidue++;
				if (g_Player.BulletResidue == 30)
				{
					g_Player.BulletType = 0;
					g_Player.BulletResidue = 0;
				}
			}
		}
	}
	else if (g_bStopShot == true)
	{
		g_nStopShot++;
		if (g_nStopShot >= STOP_SHOT)
		{
			g_nStopShot += STOP_SHOT;
		}
		g_bStopShot = false;
	}
}

////////////////////////////////////////////////////////////////////////////////
//�v���C���[�̈ړ�����
////////////////////////////////////////////////////////////////////////////////
void MovePlayer(void)
{
	//�ϐ��錾
	XinputGamepad *pXinput = GetXinputGamepad();

	//�����Ă�������ֈړ�
	if (GetKeyboardPress(DIK_LSHIFT) == true || GetKeyboardPress(DIK_RSHIFT) == true || pXinput->bPressB == true)
	{	//���V�t�g�������Ă��鎞�͌�������
		g_Player.pos += D3DXVECTOR3(sinf(D3DX_PI - g_Player.rot.z) * -(MOVE_SPEED * DOWN_SPEED), cosf(D3DX_PI - g_Player.rot.z) * (MOVE_SPEED * DOWN_SPEED), 0.0f);
	}
	else
	{	//�ʏ�ړ�
		g_Player.pos += D3DXVECTOR3(sinf(D3DX_PI - g_Player.rot.z) * -MOVE_SPEED, cosf(D3DX_PI - g_Player.rot.z) * MOVE_SPEED, 0.0f);
	}

	//��ʊO�ɏo�Ȃ��悤�ɂ���
	if (g_Player.pos.x < (0 + DIAGONAL_X))
	{
		g_Player.pos.x = (0 + DIAGONAL_X);
		g_Player.state = PLAYERSTATE_DEATH;
		PlaySound(SOUND_LABEL_SE_DEATH);
		SetExplosion(g_Player.pos);
	}
	else if (g_Player.pos.x > (SCREEN_WIDTH - DIAGONAL_X))
	{
		g_Player.pos.x = (SCREEN_WIDTH - DIAGONAL_X);
		g_Player.state = PLAYERSTATE_DEATH;
		PlaySound(SOUND_LABEL_SE_DEATH);
		SetExplosion(g_Player.pos);
	}

	if (g_Player.pos.y < (0 + DIAGONAL_Y))
	{
		g_Player.pos.y = (0 + DIAGONAL_Y);
		g_Player.state = PLAYERSTATE_DEATH;
		PlaySound(SOUND_LABEL_SE_DEATH);
		SetExplosion(g_Player.pos);
	}
	else if (g_Player.pos.y > (SCREEN_HEIGHT - DIAGONAL_Y))
	{
		g_Player.pos.y = (SCREEN_HEIGHT - DIAGONAL_Y);
		g_Player.state = PLAYERSTATE_DEATH;
		PlaySound(SOUND_LABEL_SE_DEATH);
		SetExplosion(g_Player.pos);
	}

	if (g_Player.rotDest.z - g_Player.rot.z < -D3DX_PI)
	{// -3.14f��菬�����Ȃ����Ƃ��l��3.14f�ɂ���
		g_Player.rotDest.z += D3DX_PI * 2.0f;
	}
	else if (g_Player.rotDest.z - g_Player.rot.z > D3DX_PI)
	{// 3.14f���傫���Ȃ����Ƃ��l��-3.14f�ɂ���
		g_Player.rotDest.z -= D3DX_PI * 2.0f;
	}
	// �����̍X�V
	g_Player.rot.z += (g_Player.rotDest.z - g_Player.rot.z) * 0.08f;

	if (g_Player.rot.z < -D3DX_PI)
	{// -3.14f��菬�����Ȃ����Ƃ��l��3.14f�ɂ���
		g_Player.rot.z += D3DX_PI * 2.0f;
	}
	else if (g_Player.rot.z > D3DX_PI)
	{// 3.14f���傫���Ȃ����Ƃ��l��-3.14f�ɂ���
		g_Player.rot.z -= D3DX_PI * 2.0f;
	}

	//��]
	if (pXinput->bPressLStick == true)
	{
		g_Player.rotDest.z = pXinput->fAngle;
	}

	if (GetKeyboardPress(DIK_W) == TRUE || pXinput->bPressUP == true)
	{
		if (GetKeyboardPress(DIK_A) == TRUE || pXinput->bPressLEFT == true)
		{
			g_Player.rotDest.z = D3DXToRadian(45);
		}
		else if (GetKeyboardPress(DIK_D) == TRUE || pXinput->bPressRIGHT == true)
		{
			g_Player.rotDest.z = D3DXToRadian(-45);
		}
		else
		{
			g_Player.rotDest.z = 0.0f;
		}
	}
	else if (GetKeyboardPress(DIK_S) == TRUE || pXinput->bPressDOWN == true)
	{
		if (GetKeyboardPress(DIK_A) == TRUE || pXinput->bPressLEFT == true)
		{
			g_Player.rotDest.z = D3DXToRadian(135);
		}
		else if (GetKeyboardPress(DIK_D) == TRUE || pXinput->bPressRIGHT == true)
		{
			g_Player.rotDest.z = D3DXToRadian(-135);
		}
		else
		{
			g_Player.rotDest.z = D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_A) == TRUE || pXinput->bPressLEFT == true)
	{
		g_Player.rotDest.z = (D3DX_PI / 2);
	}
	else if (GetKeyboardPress(DIK_D) == TRUE || pXinput->bPressRIGHT == true)
	{
		g_Player.rotDest.z = (-D3DX_PI / 2);
	}
}

////////////////////////////////////////////////////////////////////////////////
//�F�̐ݒ�
////////////////////////////////////////////////////////////////////////////////
void SetColor(void)
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
	float fRangeX2;
	float fRangeY2;
	ENEMY *pEnemy;
	pEnemy = GetEnemy();
	fRangeX = DIAGONAL_X + ENEMY_SIZE;
	fRangeY = DIAGONAL_Y + ENEMY_SIZE;
	fRangeX2 = DIAGONAL_X + BIGENEMY_SIZE;
	fRangeY2 = DIAGONAL_Y + BIGENEMY_SIZE;

	//�G�Ƃ̓����蔻��
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{	//�G���g�p���Ă���ꍇ

			if (g_Player.pos.x >= pEnemy->pos.x)
			{
				fDisX = g_Player.pos.x - pEnemy->pos.x;
			}
			else if (g_Player.pos.x <= pEnemy->pos.x)
			{
				fDisX = pEnemy->pos.x - g_Player.pos.x;
			}

			if (g_Player.pos.y >= pEnemy->pos.y)
			{
				fDisY = g_Player.pos.y - pEnemy->pos.y;
			}
			else if (g_Player.pos.y <= pEnemy->pos.y)
			{
				fDisY = pEnemy->pos.y - g_Player.pos.y;
			}

			switch (pEnemy->nType)
			{
			case ENEMYTYPE_BIG:
				if (0 > (fDisX - fRangeX2) && 0 > (fDisY - fRangeY2))
				{
					g_Player.state = PLAYERSTATE_DAMAGE;
					pEnemy->bUse = false;
					pEnemy->bDisp = false;
					//�����Đ�
					SetExplosion(pEnemy->pos);
					PlaySound(SOUND_LABEL_SE_HIT);
				}
				break;

			default:
				if (0 > (fDisX - fRangeX) && 0 > (fDisY - fRangeY))
				{
					g_Player.state = PLAYERSTATE_DAMAGE;
					pEnemy->bUse = false;
					pEnemy->bDisp = false;
					//�����Đ�
					SetExplosion(pEnemy->pos);
					PlaySound(SOUND_LABEL_SE_HIT);
				}
				break;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�A�C�e���Ƃ̓����蔻��
////////////////////////////////////////////////////////////////////////////////
void HitItem(void)
{
	//�ϐ��錾
	float fDisX;
	float fDisY;
	float fRangeX;
	float fRangeY;
	ITEM *pItem;
	pItem = GetItem();
	fRangeX = DIAGONAL_X + ITEM_SIZEX;
	fRangeY = DIAGONAL_Y + ITEM_SIZEY;

	//�A�C�e���Ƃ̓����蔻��
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
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

			if (g_Player.pos.y >= pItem->pos.y)
			{
				fDisY = g_Player.pos.y - pItem->pos.y;
			}
			else if (g_Player.pos.y <= pItem->pos.y)
			{
				fDisY = pItem->pos.y - g_Player.pos.y;
			}

			if (0 > (fDisX - fRangeX) && 0 > (fDisY - fRangeY))
			{
				g_Player.BulletType = pItem->nType;
				g_Player.BulletResidue = 0;
				pItem->bUse = false;
				pItem->bDisp = false;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�v���C���[�̏��̎擾
////////////////////////////////////////////////////////////////////////////////
PLAYER *GetPlayer(void)
{
	return &g_Player;
}