////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �Q�[����ʂ̏��� [game.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/10/30
//
////////////////////////////////////////////////////////////////////////////////
#include "game.h"
#include "Billboard.h"
#include "bullet.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "meshfield.h"
#include "player.h"
#include "fade.h"
#include "model.h"
#include "object.h"
#include "polygon.h"
#include "shadow.h"
#include "wall.h"
#include "xinput_pad.h"
#include "enemy.h"
#include "EnemyAttack.h"
#include "UI.h"

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//�Q�[����ʂ̏���������
////////////////////////////////////////////////////////////////////////////////
HRESULT InitGame(void)
{
	//�J�����̏�����
	InitCamera();

	//���C�g�̏�����
	InitLight();

	//�|���S���̏�����
	InitMeshfield();

	//�ǂ̏�����
	InitWall();

	//�r���{�[�h�̏�����
	InitBillboard();

	//�e�̏�����
	InitShadow();

	//�e�̏�����
	InitBullet();

	//�I�u�W�F�N�g�̏�����
	InitObject();

	//���f���̏�����
	InitModel();

	//�v���C���[�̏�����
	InitPlayer();

	//�G�̏�����
	InitEnemy();

	//�G�̍U���̏�����
	InitEnemyAttack();

	//UI�̏�����
	InitUI();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
//�I������
////////////////////////////////////////////////////////////////////////////////
void UninitGame(void)
{
	//UI�̏I��
	UninitUI();

	//�G�̍U���̏I��
	UninitEnemyAttack();

	//�G�̏I��
	UninitEnemy();

	//�v���C���[�̏I��
	UninitPlayer();

	//���f���̏I��
	UninitModel();

	//�I�u�W�F�N�g�̏I��
	UninitObject();

	//�e�̏I��
	UninitBullet();

	//�e�̏I��
	UninitShadow();

	//�r���{�[�h�̏I��
	UninitBillboard();

	//�ǂ̏I��
	UninitWall();

	//�|���S���̏I��
	UninitMeshfield();

	//���C�g�̏I��
	UninitPolygon();

	//�J�����̏I��
	UninitCamera();
}

////////////////////////////////////////////////////////////////////////////////
//�X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateGame(void)
{
	//�J�����̍X�V
	UpdateCamera();

	//���C�g�̍X�V
	UpdateLight();

	//�|���S���̍X�V
	UpdateMeshfield();

	//�ǂ̍X�V
	UpdateWall();

	//�r���{�[�h�̍X�V
	UpdateBillboard();

	//�e�̍X�V
	UpdateShadow();

	//�e�̍X�V
	UpdateBullet();

	//�I�u�W�F�N�g�̍X�V
	UpdateObject();

	//���f���̍X�V
	UpdateModel();

	//�v���C���[�̍X�V
	UpdatePlayer();

	//�G�̍X�V
	UpdateEnemy();

	//�G�̍U���̍X�V
	UpdateEnemyAttack();

	//UI�̍X�V
	UpdateUI();

	XinputGamepad *pXinput = GetXinputGamepad();
}

////////////////////////////////////////////////////////////////////////////////
//�`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawGame(void)
{
	//�J�����̐ݒ�
	SetCamera();

	//�|���S���̕`��
	DrawMeshfield();

	//�ǂ̕`��
	DrawWall();

	//�r���{�[�h�̍X�V
	DrawBillboard();

	//�e�̕`��
	DrawShadow();

	//�e�̕`��
	DrawBullet();

	//�I�u�W�F�N�g�̕`��
	DrawObject();

	//���f���̕`��
	DrawModel();

	//�v���C���[�̕`��
	DrawPlayer();

	//�G�̕`��
	DrawEnemy();

	//�G�̍U���̕`��
	DrawEnemyAttack();

	//UI�̕`��
	DrawUI();
}