//-------------------------------------------------------------------
//
// ���[�V�����w�b�_�[ (motion.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"

//-------------------------------------------------------------------
// �񋓌^
//-------------------------------------------------------------------
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	// �j���[�g�������[�V����
	MOTIONTYPE_MOVE,		// �ړ����[�V����
	MOTIONTYPE_THROW,		// �������[�V����
	MOTIONTYPE_JUMP,		// �W�����v���[�V����
	MOTIONTYPE_LAND,		// ���n���[�V����
	MOTIONTYPE_WIN,			// �������[�V����
	MOTIONTYPE_LOSE,		// �s�k���[�V����
	MOTIONTYPE_SIRIMOTI,	// �K�������[�V����
	MOTIONTYPE_DAMAGE,		// �̂����胂�[�V����
	MOTIONTYPE_SELECT,		// �Z���N�g���[�V����
	MOTYONTYPE_MAX,			// ���[�V�����̍ő�l
}MOTIONTYPE;				// ���[�V�����̎��

//-------------------------------------------------------------------
// �\���̂̒�`
//-------------------------------------------------------------------
typedef struct
{
	float fPosX;			// �ʒuX
	float fPosY;			// �ʒuY
	float fPosZ;			// �ʒuZ
	float fRotX;			// ����X
	float fRotY;			// ����Y
	float fRotZ;			// ����Z
}KEY;						// �L�[�̍\����

typedef struct
{
	int nFrame;				// �t���[����
	KEY aKey[20];			// �e���f���̃L�[�v�f
}KEY_INFO;					// �L�[�̍\����

typedef struct
{
	bool bLoop;				// ���[�v���邩�ǂ���
	int nNumKey;			// �L�[�̑���
	KEY_INFO aKeyInfo[10];	// �L�[���
}MOTION_INFO;				// ���[�V�����̍\����

#endif