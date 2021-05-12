#pragma once
#include "main.h"
#include "BombWarningMark.h"

#define BOMB_NUMBER 30 //���e��
#define BOMB_CREATE_TIME 100 //���e�������ԊԊu
#define BOMB_BLOW_UP_TIME 5 //�������Ԍ���
#define BOMB_BLOW_UP_FRAME 60 //��������������Frame
#define BOMB_TEXTURE 100 //�ގ��pTextute�ő�l
#define BOMB_SHOOT_SPEED_Y 2.5f //bomb���˂̏����x(����)
#define BOMB_SHOOT_POWER ((rand () % 15 / 10.f) + 2.f) 
#define BOMB_THROW_SPEED 1.5f
#define BOMB_THROW_SPEED_Y 4.0f
#define BOMB_THROW_POWER 2.5f
#define BOMB_GRAVITY 0.2f //�d��
#define BOMB_ELASTIC 0.75f //�e�͌W��
#define BOMB_AIR_FRICTION 0.02f //��C���C��
#define BOMB_GROUND_FRICTION 0.05f //�n�ʖ��C��
#define STAGE_HEIGHT 70//�X�e�[�W�̍���
#define BOMB_RADIUS 30.f //Bomb�����蔻�苅�̔��a
#define BOMB_PLAYER_CATCH_Y 30.f //�v���C�A�̓��̏��bomb���f���č���
#define STAGE_RADIUS 300.f //stage�̔��a
#define BOMB_SHADOW 20.f
#define BOMB_SPIN_Y 10.f
typedef enum
{
	BOMB_MOVE = 0, //�ړ���
	BOMB_STOP, //stage�ɂ���
	BOMB_CATCH, //player�̎�ɂ���
	BOMB_BLOW, //����
	BOMB_SHOOT_OUT, //��C���甭�˂���܂�stage�ɓ����ĂȂ���
	BOMB_NOTCREATE, //������
}BOMB_STATE;

typedef	struct
{
	bool bUse; //�L�����f
	int nID; //�ԍ�
	int nCntTime; //�������ԃJ�E���g�_�E��
	int nIdexShadow;
	bool bCatch;
	D3DXVECTOR3 pos; //�ʒu
	D3DXVECTOR3 move; //�ړ���
	D3DXVECTOR3 rot; //�p�x
	D3DXVECTOR3 rotMove; //��]��
	BOMB_STATE BombState; //��ԊǗ�

	LPD3DXMESH Xfile_Mesh; //mesh
	LPD3DXBUFFER Xfile_Materials; //�ގ�
	DWORD Xfile_MaterialNum; //�ގ��̐�
	LPDIRECT3DTEXTURE9 Xfile_Textures[BOMB_TEXTURE] = {}; //�ގ��p��texture
	D3DXMATRIX Xfile_MtxWorld; //

	WARNING_MARK aWarning_Mark[WARNING_MARK_NUMBER];
}BOMB;

HRESULT InitBomb(); //BOMB��`
void UninitBomb(); //��������
void UpdateBomb(); //BOMB�X�V����
void DrawBomb(); //BOMB�`��

void SetBomb(int nCannonID); //BOMB����
void BombStateControl(); //BOMB��ԊǗ�
void BombThrow(int nID, D3DXVECTOR3 pos, D3DXVECTOR3 rot); //BOMB������
void BombSpin();
BOMB *GetBomb();
void BombAndPlayer(int nCntPlayer);
void SetBombBlow(int nCntBomb);