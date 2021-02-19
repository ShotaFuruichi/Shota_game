////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �v���C���[�̏��� [player.h]
//Author	: ShotaFuruichi
//Since		: 2020/12/17
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define SEC_ONE (60)							//1�b
	
#define MAX_MODEL_PLAYER (10)					//���f���̍ő吔
#define PLAYER_SIZEXZ (10.0f)					//�v���C���[�̃T�C�YXZ��
#define PLAYER_SIZEY (35.0f)					//�v���C���[�̃T�C�YY��
#define LIFE_PLAYER (10000)						//�v���C���[�̗̑�
#define MP_PLAYER (8000)						//mp�̍ő�l
#define MAX_COOLDOWN (SEC_ONE * 2)				//�N�[���_�E��
#define CHANT_TIMEMAGIC ((float)SEC_ONE * 1.5f)	//�U�����@�̉r������
#define CHANT_TIMEHEAL (SEC_ONE)				//�񕜖��@�̉r������

////////////////////////////////////////////////////////////////////////////////
//���݂̃��[�V����
////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	MOTION_NEUTRAL = 0,	//�j���[�g�������[�V����
	MOTION_MOVE,		//�ړ����[�V����
	MOTION_JUMP,		//�W�����v���[�V����
	MOTION_ACTION,		//�A�N�V�������[�V����
	MOTION_MAX
} MOTION;

////////////////////////////////////////////////////////////////////////////////
//���݉r�����̖��@
////////////////////////////////////////////////////////////////////////////////
typedef enum
{
	SKILL_NONE = 0,		//�����r�����Ă��Ȃ����
	SKILL_ATTACK,		//�����U��
	SKILL_MAGICBALL, 	//�U�����@
	SKILL_HEAL,			//�񕜖��@
	SKILL_MAX
} SKILL;

////////////////////////////////////////////////////////////////////////////////
//���f���̍\����
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	LPD3DXMESH pMesh;			//���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBufferMat;	//�}�e���A���ւ̃|�C���^
	DWORD nNumMat;				//�}�e���A���̐�
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 rot;			//����
	D3DXMATRIX mtxWorld;		//���[���h�}�g���b�N�X
	int nIdxModelParent;		//�e���f���̃C���f�b�N�X
} MODEL;

////////////////////////////////////////////////////////////////////////////////
//�v���C���[�̍\����
////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 posOld;				//�O��X�V���̈ʒu
	D3DXVECTOR3 rot;				//����
	D3DXVECTOR3 rotDest;			//�ڕW�̌���
	D3DXMATRIX mtxWorld;			//���[���h�}�g���b�N�X
	MOTION nowMotion;				//���݂̃��[�V����
	bool bA;						//����������
	bool bMove;						//�����Ă��邩
	bool bChant;					//�r�������ǂ���
	bool bUseSkill;					//�X�L�����g���邩
	int nChantCounter;				//�r������
	int nCooldown;					//�X�L�����ʃN�[���_�E��
	SKILL skill;					//���݉r�����̖��@
	int nLife;						//�̗�
	int nMP;						//�}�W�b�N�|�C���g
	int nMpRec;						//mp�񕜂̂��߂̃J�E���^
	float fGravity;					//�d��
	bool bJump;						//�W�����v�̉s��
	MODEL aModel[MAX_MODEL_PLAYER];	//���f��(�p�[�c)
	int nNumModel;					//���f��(�p�[�c)��

} PLAYER;

////////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
////////////////////////////////////////////////////////////////////////////////
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

void SkillPlayer(void);
void MovePlayer(void);

void MotionPlayer(void);
void MotionPlayerNeutral(void);
void MotionPlayerMove(void);
void MotionPlayerJump(void);
void MotionPlayerAction(void);

D3DXVECTOR3 *GetPosPlayer(void);
D3DXVECTOR3 *GetPosOld(void);
D3DXVECTOR3 *GetRotPlayer(void);
PLAYER *GetPlayer(void);
float *GetGaiseki(void);
int GetRandom(int min, int max);

#endif