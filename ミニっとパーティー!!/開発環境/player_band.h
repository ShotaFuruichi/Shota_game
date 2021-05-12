//-------------------------------------------------------------------
//
// �v���C���[�o���h�w�b�_�[ (player_band.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _PLAYERBAND_H_
#define _PLAYERBAND_H_

#include "main.h"
#include "texture.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MAX_PLAYERBAND		(5)							// �v���C���[�o���h��
#define DISPLAY_PLAYERBAND	(4)							// �\������ő吔

//-------------------------------------------------------------------
// �񋓌^
//-------------------------------------------------------------------
typedef enum
{
	PLAYERBANDTYPE_1P = 0,		// 1P
	PLAYERBANDTYPE_2P,			// 2P
	PLAYERBANDTYPE_3P,			// 3P
	PLAYERBANDTYPE_4P,			// 4P
	PLAYERBANDTYPE_COM,			// COM
	PLAYERBANDTYPE_MAX,			
}PLAYERBANDTYPE;				// �v���C���[�o���h�̎��

//-------------------------------------------------------------------
// �\���̂̒�`
//-------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXCOLOR col;			// �F
	float fWidth;			// ��
	float fHeight;			// ����
	int nTexType;			// �e�N�X�`���^�C�v
	bool bUse;				// �g�p���Ă��邩�ǂ���
}PlayerBand;

//-------------------------------------------------------------------
// �v���g�^�C�v�錾
//-------------------------------------------------------------------
HRESULT InitPlayerBand(void);		// �v���C���[�o���h�̏���������
void UninitPlayerBand(void);		// �v���C���[�o���h�̏I������
void UpdatePlayerBand(void);		// �v���C���[�o���h�̍X�V����
void DrawPlayerBand(void);			// �v���C���[�o���h�̕`�揈��

void SetVertexPlayerBand(int nIdx); // ���_���W�̐ݒ�

PlayerBand *GetPlayerBand(void);	// �v���C���[�o���h���̎擾

void LoadPlayerBandData(void);		// �v���C���[�o���h���̓ǂݍ���

#endif