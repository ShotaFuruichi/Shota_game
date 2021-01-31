////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �Q�[����ʂ̏��� [game.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/08/28
//
////////////////////////////////////////////////////////////////////////////////
#include "game.h"
#include "bg.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "player.h"
#include "score.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "effect.h"
#include "Pause.h"
#include "item.h"
#include "stdlib.h"
#include "time.h"
#include "xinput_pad.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define ENEMY_NUM (12)			//�G��for���Ŏg�����
#define ENEMY_TYPE (3)			//�G�̎�ސ�
#define ENEMY_FREQUENCY (75)	//�G�̏o���p�x
#define HIGH_FREQUENCY (25)		//�G�̍ő��o���p�x
#define CHANGE_FREQUENCY (5)	//���̂��Ƃɏo���p�x�𑁂����邩
#define ITEM_FREQUENCY (500)	//�A�C�e���̏o���p�x

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
bool g_bPause = false;			//�|�[�Y�����ǂ���	
int g_EnemyCounter;				//�G�̃J�E���^�[
int g_ItemCounter;				//�A�C�e���̃J�E���^�[
int g_EnemyFrequency;			//�G���o�銴�o
int g_EnemyCount;				//�G���o�銴�o�𑁂߂邽�߂̃J�E���^

////////////////////////////////////////////////////////////////////////////////
//�Q�[����ʂ̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitGame(void)
{
	g_EnemyCounter = 0;
	g_ItemCounter = 0;
	g_EnemyFrequency = ENEMY_FREQUENCY;

	//�w�i�̏���������
	InitBg();

	//�e�̏���������
	InitBullet();

	//�G�t�F�N�g�̏�����
	InitEffect();

	//�A�C�e���̏�����
	InitItem();

	//�v���C���[�̏���������
	InitPlayer();

	//�G�̏���������
	InitEnemy();

	//�����̏���������
	InitExplosion();

	//�X�R�A�̏�����
	InitScore();

	//�|�[�Y��ʂ̏�����
	InitPause();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM002);

	/*for (int nCount = 0; nCount < 10; nCount++)
	{
		SetEnemy();
	}*/

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�I������
////////////////////////////////////////////////////////////////////////////////
void UninitGame(void)
{	
	//�T�E���h�̒�~
	StopSound();

	//�|�[�Y��ʂ̏I������
	UninitPause();

	//�����̏I������
	UninitExplosion();

	//�G�̏I������
	UninitEnemy();

	//�v���C���[�̏I������
	UninitPlayer();

	//�A�C�e���̏I������
	UninitItem();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�e�̏I������
	UninitBullet();

	//�w�i�̏I������
	UninitBg();
}

////////////////////////////////////////////////////////////////////////////////
//�X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateGame(void)
{
	FADE fade = GetFade();
	XinputGamepad *pXinput = GetXinputGamepad();

	//�|�[�Y����
	if (GetKeyboardTrigger(DIK_P) == true || pXinput->bPressStart == true)
	{
		g_bPause = g_bPause ? false : true;
	}

	//�e�X�V
	if (g_bPause == true)
	{
		UpdatePause();
	}
	else
	{
		//�w�i�̍X�V����
		UpdateBg();

		//�e�̍X�V����
		UpdateBullet();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//�A�C�e���̍X�V����
		UpdateItem();

		//�v���C���[�̍X�V����
		UpdatePlayer();

		//�G�̍X�V����
		UpdateEnemy();

		//�����̍X�V����
		UpdateExplosion();

		//�X�R�A�̍X�V����
		UpdateScore();

		//�G�o��
		g_EnemyCounter++;
		if (g_EnemyCounter % g_EnemyFrequency == 0)
		{
			SetEnemy();
			if (g_EnemyFrequency > HIGH_FREQUENCY)
			{
				g_EnemyCount++;
				if (g_EnemyCount % CHANGE_FREQUENCY == 0)
				{
					g_EnemyFrequency--;
				}
			}
		}

		//�A�C�e���o��
		g_ItemCounter++;
		if (g_ItemCounter % ITEM_FREQUENCY == 0)
		{
			SetItem();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBg();

	//�e�̕`�揈��
	DrawBullet();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�A�C�e���̕`�揈��
	DrawItem();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�G�̕`�揈��
	DrawEnemy();

	//�����̕`�揈��
	DrawExplosion();

	//�X�R�A�̕`�揈��
	DrawScore();

	if (g_bPause == true)
	{
		DrawPause();
	}
}

////////////////////////////////////////////////////////////////////////////////
//�|�[�Y��Ԏ擾
////////////////////////////////////////////////////////////////////////////////
void SetPause(bool bPause)
{
	g_bPause = bPause;
}

////////////////////////////////////////////////////////////////////////////////
//�����_���Ȑ��l���擾
////////////////////////////////////////////////////////////////////////////////
float GetRandom(float min, float max)
{
	static int nNum;

	if (nNum == 0)
	{
		srand((unsigned int)time(NULL));
		nNum = 1;
	}

	return min + (int)(rand() * (max - min + 1.0f) / (1.0f + RAND_MAX));
}
