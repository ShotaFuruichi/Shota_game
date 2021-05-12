//-------------------------------------------------------------------
//
// �v���C���[�w�b�_�[ (player.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "motion.h"
#include "chara.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define MAX_FILENAME (64)		// X�t�@�C���l�[���̍ő啶����

#define MOVE_PLAYER			(1.5f)
#define JUMP_PLAYER			(11.0f)
#define PI_QUARTER			(D3DX_PI / 4.0f)
#define GRAVITY				(0.5f)		// �d��

#define LENGTH				(8.0f)
#define MAX_DISPLAY_CHARA	(4)				// �v���C���[�̑���

//-------------------------------------------------------------------
// �v���C���[���(�񋓌^)
//-------------------------------------------------------------------
typedef enum
{
	PLAYERSTATE_NORMAL = 0,		// �ʏ�
	PLAYERSTATE_FLOATING,		// ���V
	PLAYERSTATE_DAMAGE,			// �_���[�W
	PLAYERSTATE_THROW,			// �_���[�W
	PLAYERSTATE_MAX,			// ��Ԃ̍ő吔
}PLAYERSTATE;

//-------------------------------------------------------------------
// �\���̂̒�`
//-------------------------------------------------------------------
typedef struct
{
	int nCharaNumber;							// ���Ԗڂ̃L�����N�^�[��
	D3DXVECTOR3 pos;							// ���S���W
	D3DXVECTOR3 posOld;							// �O�̒��S���W
	D3DXVECTOR3 rot;							// ���݂̌���
	D3DXVECTOR3 rotDest;						// �ړI�̌���
	D3DXMATRIX mtxWorld;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3 move;							// �ړ���
	PLAYERSTATE state;							// �v���C���[�̏��
	int nStateCounter;							// ��ԃJ�E���^
	CharacterModel aModel[20];					// ���f��
	int nNumModel;								// ���f����
	D3DXVECTOR3 minVecPlayer;					// ���_�̍ŏ��l
	D3DXVECTOR3 maxVecPlayer;					// ���_�̍ő�l
	float fHeight;								// �����蔻��̍���
	float fRadius;								// �����蔻��̔��a
	int nIdx;									// ���Ԗڂ̉e��
	D3DXVECTOR3 PosShadow;							// �e�̈ʒu
	bool bJump;									// �W�����v�������ǂ���
	bool bFall;									// ���������ǂ���

	bool bFinishMotion;							// ���݂̃��[�V�������I��������ǂ���
	bool bBlendMotion;							// �u�����h���[�V���������邩�ǂ���
	MOTION_INFO aMotionInfo[MOTYONTYPE_MAX];	// ���[�V�������
	int nNumMotion;								// ���[�V������
	MOTIONTYPE MotionType;						// ���[�V�����^�C�v
	bool bLoopMotion;							// ���[�v���邩�ǂ���
	int nNumKey;								// �L�[��
	int nKey;									// �L�[No.
	int nCounterMotion;							// ���[�V�����J�E���^

	MOTIONTYPE MotionTypeBlend;					// �u�����h���[�V�����^�C�v
	bool bLoopMotionBlend;						// �u�����h���[�V���������[�v���邩�ǂ���
	int nNumKeyBlend;							// �u�����h���[�V�����̃L�[��
	int nKeyBlend;								// �u�����h���[�V�����̃L�[No.
	int nCounterMotionBlend;					// �u�����h���[�V�����J�E���^
	int nFrameBlend;							// �u�����h�t���[����
	int nCounterBlend;							// �u�����h�J�E���^

	int nBombID;
	bool bHaveBomb;
	int nNearPlayer;
	bool bPush;
}Player;

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
HRESULT InitPlayer(void);					// �v���C���[�̏���������
void UninitPlayer(void);					// �v���C���[�̏I������
void UpdatePlayer(void);					// �v���C���[�̍X�V����
void DrawPlayer(void);						// �v���C���[�̕`�揈��

Player *GetPlayer(void);					// �v���C���[���̎擾

void GamePlayer(void);						// �v���C���[�̃Q�[������
void ResultPlayer(void);					// �v���C���[�̃��U���g����

void StateManagerPlayer(int nCntPlayer);	// �v���C���[��Ԃ̔���
void PlayerStateNormal(int nCntPlayer);		// �v���C���[��Ԃ��ʏ�̎�
void PlayerStateFloating(int nCntPlayer);	// �v���C���[��Ԃ����V�̎�
void PlayerStateDamage(int nCntPlayer);		// �v���C���[���_���[�W��Ԃ̂Ƃ�
void PlayerStateThrow(int nCntPlayer);		// �v���C���[���_���[�W��Ԃ̂Ƃ�

void MoveAi(int nCntPlayer);
void ThrowAi(int nCntPlayer);
bool CollisionPlayer(int nCntPlayer);

void MovePlayer(int nCntPlayer);			// �v���C���[�̈ړ�����
void MovePlayerKeyboard(int nCntPlayer);	// �v���C���[�̈ړ�����(�L�[�{�[�h)
void MovePlayerGamepad(int nCntPlayer);		// �v���C���[�̈ړ�����(�Q�[���p�b�h)

void PlayerMotion(int nCntPlayer);			// �v���C�����[�V�����̐ݒ�
void SetMotion(int nCntPlayer,MOTIONTYPE motiontype, bool bBlend, int nFrameBlend);	// ���[�V�����̐ݒ�

D3DXVECTOR3 AngleCorrection(float rotX, float rotY, float rotZ);	// �p�x�̐���

#endif