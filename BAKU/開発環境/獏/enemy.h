////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �G�̏��� [enemy.h]
//Author	: ShotaFuruichi
//Since		: 2021/02/15
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "player.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define MAX_MODEL_ENEMY (6)
#define ENEMY_APPEARX (0)
#define ENEMY_APPEARY (10)
#define ENEMY_APPEARZ (0)
#define ATTACK_INTERVAL (300)
#define LIFE_ENEMY (30000)

////////////////////////////////////////////////////////////////////////////////
//�G�̍\����
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 posOld;				//�O��X�V���̈ʒu
	D3DXVECTOR3 rot;				//����
	D3DXVECTOR3 rotDest;			//�ڕW�̌���
	D3DXMATRIX mtxWorld;			//���[���h�}�g���b�N�X
	MOTION nowMotion;				//���݂̃��[�V����
	MODEL aModel[MAX_MODEL_ENEMY];	//���f��(�p�[�c)
	int nNumModel;					//���f��(�p�[�c)��
	int nAttackCounter;				//�U���Ԋu
	int nLife;						//�̗�
} ENEMY;

////////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
////////////////////////////////////////////////////////////////////////////////
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

void AttackEnemy(void);

void MotionEnemy(void);
void MotionEnemyNeutral(void);
void MotionEnemyMove(void);
void MotionEnemyJump(void);
void MotionEnemyAction(void);

ENEMY *GetEnemy(void);

#endif
