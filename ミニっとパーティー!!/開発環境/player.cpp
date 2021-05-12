//-----------------------------------------------------------------
//
// �v���C���[ (player.cpp)
// Author:Itsuki Takaiwa
//
//-----------------------------------------------------------------
#include "player.h"
#include "motion.h"
#include "meshfield.h"
#include "Bomb.h"
#include "camera.h"
#include "shadow.h"
#include "input.h"
#include "gamepad.h"
#include "motion.h"
#include "model_set.h"
#include "sound.h"
#include "chara_select_frame.h"
#include "chara.h"
#include "light.h"
#include "count_down.h"
#include "chara_select_frame.h"
#include "finish_game.h"
#include "BombCollision.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define PLAYER_SIZEXZ (10)

#define MAX_BOMB (4)
#define DIS_BOMB (150)
#define EX_BOMB (50)

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
Player g_player[MAX_DISPLAY_CHARA];					// �v���C���[���
int g_nNumOperationPlayer;							// ����\�v���C���[��
BOMB bomb[MAX_BOMB];
int g_nDisPlayer;

//-----------------------------------------------------------------
// �v���C���[�̏���������
//-----------------------------------------------------------------
HRESULT InitPlayer(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �L�������̎擾
	Character *pCharacter = GetCharacter();

	// ����\�ȃv���C���[���̎擾
	g_nNumOperationPlayer = GetnCntController();

	// �L�����Z���N�g�C���[�W���̎擾
	CharaSelectFrame *pCharaSelectFrame = GetCharaSelectFrame();

	// ���[�h�̎擾
	MODE mode = GetMode();

	// ���[�h�̎擾
	int nNumPlayer = GetFrame();

	g_nDisPlayer = nNumPlayer;

	for (int nCntPlayer = 0; nCntPlayer < g_nDisPlayer; nCntPlayer++, pCharaSelectFrame++)
	{
		// �v���C���[���̏�����
		for (int nCntMotion = 0; nCntMotion < MOTYONTYPE_MAX; nCntMotion++)
		{
			g_player[nCntPlayer].aMotionInfo[nCntMotion] = pCharacter->characterInfo[pCharaSelectFrame->nNumChara].aMotionInfo[nCntMotion];
		}
		g_player[nCntPlayer].nNumModel = pCharacter->characterInfo[pCharaSelectFrame->nNumChara].nNumModel;
		g_player[nCntPlayer].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		g_player[nCntPlayer].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player[nCntPlayer].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player[nCntPlayer].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player[nCntPlayer].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player[nCntPlayer].bJump = false;
		g_player[nCntPlayer].state = PLAYERSTATE_NORMAL;
		g_player[nCntPlayer].MotionType = MOTIONTYPE_NEUTRAL;
		g_player[nCntPlayer].nStateCounter = 0;
		g_player[nCntPlayer].nCounterMotion = 1;
		g_player[nCntPlayer].nKey = 0;
		g_player[nCntPlayer].bLoopMotion = g_player[nCntPlayer].aMotionInfo[g_player[nCntPlayer].MotionType].bLoop;
		g_player[nCntPlayer].nNumKey = g_player[nCntPlayer].aMotionInfo[g_player[nCntPlayer].MotionType].nNumKey;
		g_player[nCntPlayer].MotionTypeBlend = MOTIONTYPE_NEUTRAL;
		g_player[nCntPlayer].bBlendMotion = false;
		g_player[nCntPlayer].nBombID = -1;

		if (mode == MODE_GAME)
		{
			g_player[nCntPlayer].bFall = false;
		}
		// �v���C���[�̃p�[�c�ݒ�
		for (int nCntModel = 0; nCntModel < g_player[nCntPlayer].nNumModel; nCntModel++)
		{
			// ���f�����̎擾
			g_player[nCntPlayer].aModel[nCntModel] = pCharacter->characterInfo[pCharaSelectFrame->nNumChara].aModel[nCntModel];

			// X�t�@�C���̓ǂݍ���
			if (FAILED(D3DXLoadMeshFromX(g_player[nCntPlayer].aModel[nCntModel].aFileName,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_player[nCntPlayer].aModel[nCntModel].pBuffMat,
				NULL,
				&g_player[nCntPlayer].aModel[nCntModel].nNumMat,
				&g_player[nCntPlayer].aModel[nCntModel].pMesh)))
			{
				return E_FAIL;
			}
		}

		// �ϐ��錾
		int nNumVtx;			// ���_��
		DWORD sizeFVF;			// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^

		for (int nCntModel = 0; nCntModel < g_player[nCntPlayer].nNumModel; nCntModel++)
		{
			// ���_���̎擾
			nNumVtx = g_player[nCntPlayer].aModel[nCntModel].pMesh->GetNumVertices();

			// ���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(g_player[nCntPlayer].aModel[nCntModel].pMesh->GetFVF());

			// ���_�o�b�t�@�̃��b�N
			g_player[nCntPlayer].aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				// ���_���W�̑��
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

				// ���_���r���ă��f���̍ŏ��l�ő�l�𔲂��o��
				if (g_player[nCntPlayer].minVecPlayer.x > vtx.x)
				{// X���W�̍ŏ��l
					g_player[nCntPlayer].minVecPlayer.x = vtx.x;
				}
				else if (g_player[nCntPlayer].maxVecPlayer.x < vtx.x)
				{// X���W�̍ő�l
					g_player[nCntPlayer].maxVecPlayer.x = vtx.x;
				}

				if (g_player[nCntPlayer].minVecPlayer.y > vtx.y)
				{// Y���W�̍ŏ��l
					g_player[nCntPlayer].minVecPlayer.y = vtx.y;
				}
				else if (g_player[nCntPlayer].maxVecPlayer.y < vtx.y)
				{// Y���W�̍ő�l
					g_player[nCntPlayer].maxVecPlayer.y = vtx.y;
				}

				if (g_player[nCntPlayer].minVecPlayer.z > vtx.z)
				{// Z���W�̍ŏ��l
					g_player[nCntPlayer].minVecPlayer.z = vtx.z;
				}
				else if (g_player[nCntPlayer].maxVecPlayer.z < vtx.z)
				{// Z���W�̍ő�l
					g_player[nCntPlayer].maxVecPlayer.z = vtx.z;
				}
				// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
				pVtxBuff += sizeFVF;
			}
			// ���_�o�b�t�@�̃A�����b�N
			g_player[nCntPlayer].aModel[nCntModel].pMesh->UnlockVertexBuffer();
		}
	}
	return S_OK;
}

//-----------------------------------------------------------------
// �v���C���[�̏I������
//-----------------------------------------------------------------
void UninitPlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < g_nDisPlayer; nCntPlayer++)
	{
		for (int nCnt = 0; nCnt < g_player[nCntPlayer].nNumModel; nCnt++)
		{
			// �}�e���A�����̊J��
			if (g_player[nCntPlayer].aModel[nCnt].pBuffMat != NULL)
			{
				g_player[nCntPlayer].aModel[nCnt].pBuffMat->Release();
				g_player[nCntPlayer].aModel[nCnt].pBuffMat = NULL;
			}

			// ���b�V�����̊J��
			if (g_player[nCntPlayer].aModel[nCnt].pMesh != NULL)
			{
				g_player[nCntPlayer].aModel[nCnt].pMesh->Release();
				g_player[nCntPlayer].aModel[nCnt].pMesh = NULL;
			}
		}
	}
}

//-----------------------------------------------------------------
// �v���C���[�̍X�V����
//-----------------------------------------------------------------
void UpdatePlayer(void)
{
	// ���[�h�̎擾
	MODE mode = GetMode();

	switch (mode)
	{
	case MODE_GAME:
		GamePlayer();
		break;

	case MODE_RESULT:
		ResultPlayer();
		break;
	}
}

//-----------------------------------------------------------------
// �v���C���[�̕`�揈��
//-----------------------------------------------------------------
void DrawPlayer(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				// �}�e���A���f�[�^�ւ̃|�C���^

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();
	Light *pLight = GetLight();

	for (int nCntPlayer = 0; nCntPlayer < g_nDisPlayer; nCntPlayer++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player[nCntPlayer].mtxWorld);

		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player[nCntPlayer].rot.y, g_player[nCntPlayer].rot.x, g_player[nCntPlayer].rot.z);
		D3DXMatrixMultiply(&g_player[nCntPlayer].mtxWorld, &g_player[nCntPlayer].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_player[nCntPlayer].pos.x, g_player[nCntPlayer].pos.y, g_player[nCntPlayer].pos.z);
		D3DXMatrixMultiply(&g_player[nCntPlayer].mtxWorld, &g_player[nCntPlayer].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player[nCntPlayer].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		for (int nCntModel = 0; nCntModel < g_player[nCntPlayer].nNumModel; nCntModel++)
		{
			// �ϐ��錾
			D3DXMATRIX mtxRotModel, mtxTransModel;		// �v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent;						// �e�̃}�g���b�N�X

			// �e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_player[nCntPlayer].aModel[nCntModel].mtxWorld);

			// �e�p�[�c�̌���
			D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player[nCntPlayer].aModel[nCntModel].rot.y, g_player[nCntPlayer].aModel[nCntModel].rot.x, g_player[nCntPlayer].aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_player[nCntPlayer].aModel[nCntModel].mtxWorld, &g_player[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxRotModel);

			// �e�p�[�c�̈ʒu
			D3DXMatrixTranslation(&mtxTransModel, g_player[nCntPlayer].aModel[nCntModel].pos.x, g_player[nCntPlayer].aModel[nCntModel].pos.y, g_player[nCntPlayer].aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_player[nCntPlayer].aModel[nCntModel].mtxWorld, &g_player[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxTransModel);

			// �e�p�[�c�̐e�̃}�g���b�N�X��ݒ�
			if (g_player[nCntPlayer].aModel[nCntModel].nIdxModelParent != -1)
			{
				mtxParent = g_player[nCntPlayer].aModel[g_player[nCntPlayer].aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{
				mtxParent = g_player[nCntPlayer].mtxWorld;
			}
			// �Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&g_player[nCntPlayer].aModel[nCntModel].mtxWorld,
				&g_player[nCntPlayer].aModel[nCntModel].mtxWorld,
				&mtxParent);

			// �e�p�[�c�̃}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_player[nCntPlayer].aModel[nCntModel].mtxWorld);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_player[nCntPlayer].aModel[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_player[nCntPlayer].aModel[nCntModel].nNumMat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_player[nCntPlayer].aModel[nCntModel].pTexture[nCntMat]);

				// ���f��(�p�[�c)�̕`��
				g_player[nCntPlayer].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}
			// �}�g���b�N�X���g�p�����e�̕`��
			MatrixShadow((int)g_player[nCntPlayer].aModel[nCntModel].nNumMat,
				g_player[nCntPlayer].aModel[nCntModel].mtxWorld, 
				g_player[nCntPlayer].PosShadow,
				g_player[nCntPlayer].aModel[nCntModel].pMesh);
		}
		// �ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//-----------------------------------------------------------------
// �v���C���[�̃Q�[������
//-----------------------------------------------------------------
void GamePlayer(void)
{
	// �ϐ��錾
	int nCntFallPlayer = 0;		// �������v���C���[�����J�E���g

	for (int nCntPlayer = 0; nCntPlayer < g_nDisPlayer; nCntPlayer++)
	{
		// �v���C���[���[�V����
		PlayerMotion(nCntPlayer);

		if (g_player[nCntPlayer].bFall == false)
		{
			// �v���C���[�̏�Ԃ𔻕�
			StateManagerPlayer(nCntPlayer);

			// �O�̍��W��ۑ�
			g_player[nCntPlayer].posOld = g_player[nCntPlayer].pos;

			// �ړ��ʂ̌���(����)
			g_player[nCntPlayer].move.x += (0.0f - g_player[nCntPlayer].move.x) * 0.3f;
			g_player[nCntPlayer].move.z += (0.0f - g_player[nCntPlayer].move.z) * 0.3f;

			// �d�͐ݒ�
			g_player[nCntPlayer].move.y -= GRAVITY;

			// �ʒu�̍X�V
			g_player[nCntPlayer].pos.x += g_player[nCntPlayer].move.x;
			g_player[nCntPlayer].pos.y += g_player[nCntPlayer].move.y;
			g_player[nCntPlayer].pos.z += g_player[nCntPlayer].move.z;

			// ���b�V���t�B�[���h�Ƃ̓����蔻��
			bool bLand = CollisionMeshField(&g_player[nCntPlayer].pos, &g_player[nCntPlayer].posOld, g_player[nCntPlayer].nIdx, &g_player[nCntPlayer].PosShadow);

			// ���f���Ƃ̓����蔻��
			bool bLandModel = CollisionModelSet(&g_player[nCntPlayer].pos, &g_player[nCntPlayer].posOld, &g_player[nCntPlayer].move, &g_player[nCntPlayer].minVecPlayer, &g_player[nCntPlayer].maxVecPlayer, g_player[nCntPlayer].nIdx, &g_player[nCntPlayer].PosShadow);
			CollisionPlayer(nCntPlayer);

			// player �Ɓ@bomb
			if (g_player[nCntPlayer].nBombID == -1)
			{
				BombAndPlayer(nCntPlayer);
			}

			if (bLandModel == true)
			{
				if (g_player[nCntPlayer].state == PLAYERSTATE_FLOATING)
				{// �W�����v���̂Ƃ��W�����v���Ă��Ȃ���Ԃɂ���
					g_player[nCntPlayer].state = PLAYERSTATE_NORMAL;
				}

				// �ړ��ʂ�0.0f�ɂ���
				g_player[nCntPlayer].move.y = 0.0f;
			}
			else if (bLandModel == false && g_player[nCntPlayer].state != PLAYERSTATE_DAMAGE)
			{
				g_player[nCntPlayer].state = PLAYERSTATE_FLOATING;
			}
			if (bLand == true)
			{
				if (g_player[nCntPlayer].nBombID != -1)
				{
					SetBombBlow(g_player[nCntPlayer].nBombID);
					g_player[nCntPlayer].nBombID = -1;
				}
				g_player[nCntPlayer].bFall = true;
				SetMotion(nCntPlayer, MOTIONTYPE_SIRIMOTI, true, 10);
			}
			if (g_player[nCntPlayer].bFall == false)
			{
				nCntFallPlayer++;
			}
		}
	}
	if (nCntFallPlayer == 1)
	{
		SetFinishGame(true);
	}
}

//-----------------------------------------------------------------
// �v���C���[�̃��U���g����
//-----------------------------------------------------------------
void ResultPlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < g_nDisPlayer; nCntPlayer++)
	{
		// �v���C���[���[�V����
		PlayerMotion(nCntPlayer);

		// �O�̍��W��ۑ�
		g_player[nCntPlayer].posOld = g_player[nCntPlayer].pos;

		// �ړ��ʂ̌���(����)
		g_player[nCntPlayer].move.x += (0.0f - g_player[nCntPlayer].move.x) * 0.3f;
		g_player[nCntPlayer].move.z += (0.0f - g_player[nCntPlayer].move.z) * 0.3f;

		// �d�͐ݒ�
		g_player[nCntPlayer].move.y -= GRAVITY;

		// �ʒu�̍X�V
		g_player[nCntPlayer].pos.x += g_player[nCntPlayer].move.x;
		g_player[nCntPlayer].pos.y += g_player[nCntPlayer].move.y;
		g_player[nCntPlayer].pos.z += g_player[nCntPlayer].move.z;

		// ���b�V���t�B�[���h�Ƃ̓����蔻��
		bool bLand = CollisionMeshField(&g_player[nCntPlayer].pos, &g_player[nCntPlayer].posOld, g_player[nCntPlayer].nIdx, &g_player[nCntPlayer].PosShadow);

		// ���f���Ƃ̓����蔻��
		bool bLandModel = CollisionModelSet(&g_player[nCntPlayer].pos, &g_player[nCntPlayer].posOld, &g_player[nCntPlayer].move, &g_player[nCntPlayer].minVecPlayer, &g_player[nCntPlayer].maxVecPlayer, g_player[nCntPlayer].nIdx, &g_player[nCntPlayer].PosShadow);

		if (bLandModel == true)
		{
			// �ړ��ʂ�0.0f�ɂ���
			g_player[nCntPlayer].move.y = 0.0f;
		}
		if (g_player[nCntPlayer].bFall == true)
		{
			SetMotion(nCntPlayer, MOTIONTYPE_LOSE, true, 10);
		}
		else if (g_player[nCntPlayer].bFall == false)
		{
			SetMotion(nCntPlayer, MOTIONTYPE_WIN, true, 10);
		}
	}
}

//-----------------------------------------------------------------
// �v���C���[��Ԃ̔���
//-----------------------------------------------------------------
void StateManagerPlayer(int nCntPlayer)
{
	// �v���C���[�̏�Ԃ𒲂ׂ�
	switch (g_player[nCntPlayer].state)
	{// ��Ԃ��ʏ�̂Ƃ�
	case PLAYERSTATE_NORMAL:
		PlayerStateNormal(nCntPlayer);
		break;
		// ��Ԃ����V�̂Ƃ�
	case PLAYERSTATE_FLOATING:
		PlayerStateFloating(nCntPlayer);
		break;
		// ��Ԃ��_���[�W�̂Ƃ�
	case PLAYERSTATE_DAMAGE:
		PlayerStateDamage(nCntPlayer);
		break;

		// ��Ԃ��_���[�W�̂Ƃ�
	case PLAYERSTATE_THROW:
		PlayerStateThrow(nCntPlayer);
		break;
	}
}

//-----------------------------------------------------------------
// �v���C���[��Ԃ��ʏ�̎�
//-----------------------------------------------------------------
void PlayerStateNormal(int nCntPlayer)
{
	// �Q�[���p�b�h���̎擾
	DIJOYSTATE2 Controller = GetControllerPless(nCntPlayer);

	if (nCntPlayer < g_nNumOperationPlayer)
	{
		// �v���C���[�̈ړ�����
		MovePlayer(nCntPlayer);
	}
	if (g_player[nCntPlayer].bJump == false && g_player[nCntPlayer].MotionType == MOTIONTYPE_MOVE &&
		Controller.lX == 0 && Controller.lY == 0)
	{
		// �������Ȃ��Ƃ��j���[�g�������[�V�����ɐݒ�
		SetMotion(nCntPlayer, MOTIONTYPE_NEUTRAL, true, 10);
	}
}

//-----------------------------------------------------------------
// �v���C���[��Ԃ����V�̎�
//-----------------------------------------------------------------
void PlayerStateFloating(int nCntPlayer)
{
	if (nCntPlayer < g_nNumOperationPlayer)
	{
		// �v���C���[�̈ړ�����
		MovePlayer(nCntPlayer);
	}
}

//-----------------------------------------------------------------
// �v���C���[���_���[�W��Ԃ̂Ƃ�
//-----------------------------------------------------------------
void PlayerStateDamage(int nCntPlayer)
{
	// ��ԃJ�E���^��i�߂�
	g_player[nCntPlayer].nStateCounter++;

	// ��ԃJ�E���^�[��20�ɂȂ����Ƃ�����
	if (g_player[nCntPlayer].nStateCounter >= 40)
	{
		// ��Ԃ��m�[�}���ɖ߂�
		SetMotion(nCntPlayer, MOTIONTYPE_NEUTRAL, true, 10); 

		// ��ԃJ�E���^�[��0�ɏ�����
		g_player[nCntPlayer].nStateCounter = 0;
	}
}

// ������Ԃ̎�
void PlayerStateThrow(int nCntPlayer)
{
	
}

//-----------------------------------------------------------------
// �v���C���[�̈ړ�����
//-----------------------------------------------------------------
void MovePlayer(int nCntPlayer)
{
	// �J�E���g�_�E�����̎擾
	int nCountDown = GetCountDown();

	// ���݂̉�]�p�𐧌�
	if (g_player[nCntPlayer].rotDest.y - g_player[nCntPlayer].rot.y < -D3DX_PI)
	{// -3.14f��菬�����Ȃ����Ƃ��l��3.14f�ɂ���
		g_player[nCntPlayer].rotDest.y += D3DX_PI * 2.0f;
	}
	else if (g_player[nCntPlayer].rotDest.y - g_player[nCntPlayer].rot.y > D3DX_PI)
	{// 3.14f���傫���Ȃ����Ƃ��l��-3.14f�ɂ���
		g_player[nCntPlayer].rotDest.y -= D3DX_PI * 2.0f;
	}
	// �����̍X�V
	g_player[nCntPlayer].rot.y += (g_player[nCntPlayer].rotDest.y - g_player[nCntPlayer].rot.y) * 0.15f;

	// ���݂̉�]�p�𐧌�
	if (g_player[nCntPlayer].rot.y < -D3DX_PI)
	{// -3.14f��菬�����Ȃ����Ƃ��l��3.14f�ɂ���
		g_player[nCntPlayer].rot.y += D3DX_PI * 2.0f;
	}
	else if (g_player[nCntPlayer].rot.y > D3DX_PI)
	{// 3.14f���傫���Ȃ����Ƃ��l��-3.14f�ɂ���
		g_player[nCntPlayer].rot.y -= D3DX_PI * 2.0f;
	}

	if (nCountDown == 0)
	{
		// �L�[�{�[�h
		MovePlayerKeyboard(nCntPlayer);

		// �Q�[���p�b�h
		MovePlayerGamepad(nCntPlayer);
	}
}

////////////////////////////////////////////////////////////////////////////////
//AI�ړ�
////////////////////////////////////////////////////////////////////////////////
void MoveAi(int nCntPlayer)
{
/*
	D3DXVECTOR3 Distance[MAX_BOMB];
	float fDis[MAX_BOMB];
	float fSize = powf(EX_BOMB, 2.0f);

	D3DXVECTOR3 vector;
	float fAngle;

	for (int nCnt = 0; nCnt < MAX_BOMB; nCnt++)
	{
		if (bomb[nCnt].bUse == true && bomb[nCnt].bHave == false && bomb[nCnt].fExplosion <= 90)
		{	//�g�p���Ă��ĒN�������Ă��Ȃ�����1.5�b�Ŕ������锚�e�����݂���ꍇ

			//�v���C���[�Ɣ����͈͂̋�����ϐ��ɑ��
			Distance[nCnt].x = (g_player[nCntPlayer].pos.x - bomb[nCnt].pos.x);
			Distance[nCnt].z = (g_player[nCntPlayer].pos.z - bomb[nCnt].pos.z);

			//�v���C���[�Ɣ����͈͂̋�����2��
			Distance[nCnt].x = powf(Distance[nCnt].x, 2.0f);
			Distance[nCnt].z = powf(Distance[nCnt].z, 2.0f);

			//�v���C���[�̑傫���̕����}�C�i�X
			Distance[nCnt].x -= powf(PLAYER_SIZEXZ, 2.0f);
			Distance[nCnt].z -= powf(PLAYER_SIZEXZ, 2.0f);

			//x���W��z���W�̋��������킹��
			fDis[nCnt] = Distance[nCnt].x + Distance[nCnt].z;

			if (fDis[nCnt] <= fSize)
			{	//�v���C���[�Ɣ����Ƃ̋����������͈͈ȉ��ɂȂ��Ă���Ƃ�

				//�x�N�g���E�p�x�Z�o
				vector = bomb[nCnt].pos - g_player[nCnt].pos;
				fAngle = atan2f(-vector.x, -vector.z);

				//�ړ�
				g_player[nCntPlayer].pos.x += sinf(fAngle) * MOVE_PLAYER;
				g_player[nCntPlayer].pos.z += cosf(fAngle) * MOVE_PLAYER;
				g_player[nCntPlayer].rotDest.y = (fAngle += D3DX_PI);
			}
		}
	}

	if (g_player[nCntPlayer].bHaveBomb == false)
	{	//�v���C���[�����e�������Ă��Ȃ��ꍇ

		D3DXVECTOR3 vector[MAX_BOMB];
		D3DXVECTOR3 vectorA;

		float fVector[MAX_BOMB];
		float fVectorA;
		float fAngle;
		float fSpeed;
		int nCountBomb = 0;

		for (int nCnt = 0; nCnt < MAX_BOMB; nCnt++)
		{
			if (bomb[nCnt].bUse == true && bomb[nCnt].bHave == false && bomb[nCnt].fExplosion > 90)
			{	//�g�p���Ă��ĒN�������Ă��Ȃ������܂ł̎��Ԃ�1.5�b�ȏ゠�锚�e�����݂���ꍇ

				//�x�N�g���ƃx�N�g���̒����̎Z�o
				vector[nCnt] = bomb[nCnt].pos - g_player[nCntPlayer].pos;
				fVector[nCnt] = D3DXVec3Length(&D3DXVECTOR3(vector[nCnt].x, 0, vector[nCnt].z));

				vectorA = vector[nCnt];
				fVectorA = fVector[nCnt];
			}
		}

		for (int nCnt = 0; nCnt < MAX_BOMB; nCnt++)
		{
			if (bomb[nCnt].bUse == true && bomb[nCnt].bHave == false && bomb[nCnt].fExplosion > 90)
			{	//�g�p���Ă��ĒN�������Ă��Ȃ������܂ł̎��Ԃ�1.5�b�ȏ゠�锚�e�����݂���ꍇ

				if (fVectorA > fVector[nCnt])
				{	//��ԋ߂��̔��e�𔻒�
					vectorA = vector[nCnt];
					fVectorA = fVector[nCnt];
				}

				//�p�x
				fAngle = atan2f(vectorA.x, vectorA.z);
				fSpeed = MOVE_PLAYER;

				if (fSpeed > fVectorA)
				{	//���e�܂ł̋��������ړ��ʂ̕����傫���ꍇ

					//�ړ��ʂ𔚒e�܂ł̋����ɕύX
					fSpeed = fVectorA;
				}

				nCountBomb++;
			}
		}

		if (nCountBomb == 0)
		{	//�����ɓ��Ă͂܂锚�e��1���Ȃ��ꍇ

			//�ړ������E�p�x�͈����p��
			fSpeed = 0.0f;
			fAngle = g_player[nCntPlayer].rotDest.y - D3DX_PI;
		}

		//�ړ�
		g_player[nCntPlayer].pos.x += sinf(fAngle) * fSpeed;
		g_player[nCntPlayer].pos.z += cosf(fAngle) * fSpeed;
		g_player[nCntPlayer].rotDest.y = (fAngle += D3DX_PI);

		for (int nCnt = 0; nCnt < MAX_BOMB; nCnt++)
		{
			if (bomb[nCnt].bUse == true && bomb[nCnt].bHave == false)
			{	//�g�p���Ă��ĒN�������Ă��Ȃ����e�����݂���ꍇ
				if (g_player[nCntPlayer].pos.x == bomb[nCnt].pos.x && g_player[nCntPlayer].pos.z == bomb[nCnt].pos.z)
				{	//X���W�AY���W���d�Ȃ��Ă���Ƃ�

					//���e���E��
					g_player[nCntPlayer].bHaveBomb = true;
					bomb[nCnt].bHave = true;
				}
			}
		}
	}
	else
	{
		D3DXVECTOR3 vector;
		float fVector;
		float fAngle;

		//�x�N�g���E�x�N�g���̒������Z�o
		vector = g_player[g_player[nCntPlayer].nNearPlayer].pos - g_player[nCntPlayer].pos;
		fVector = D3DXVec3Length(&D3DXVECTOR3(vector.x, 0.0f, vector.z));

		if (fVector > DIS_BOMB)
		{	//��ԋ߂��̓G�܂ł̋��������e�̔򋗗��ȏ�̏ꍇ

			//�G�܂ł̊p�x
			fAngle = atan2f(vector.x, vector.z);

			//�ړ�
			g_player[nCntPlayer].pos.x += sinf(fAngle) * MOVE_PLAYER;
			g_player[nCntPlayer].pos.z += cosf(fAngle) * MOVE_PLAYER;
		}
	}*/
}

////////////////////////////////////////////////////////////////////////////////
//AI����
////////////////////////////////////////////////////////////////////////////////
void ThrowAi(int nCntPlayer)
{
	D3DXVECTOR3 vector[MAX_DISPLAY_CHARA];
	D3DXVECTOR3 vectorA;

	float fVector[MAX_DISPLAY_CHARA];
	float fVectorA = 30000000000000.0f;

	float fAngle = 0.0f;

	if (g_player[nCntPlayer].bHaveBomb == true)
	{	//���e���������Ă���ꍇ

		//���v���C���[�ւ̃x�N�g�����擾
		for (int nCnt = 0; nCnt < MAX_DISPLAY_CHARA; nCnt++)
		{
			if (nCnt != nCntPlayer)
			{	//�����ȊO

				//���v���C���[�ւ̃x�N�g���E�x�N�g���̒������Z�o
				vector[nCnt] = g_player[nCnt].pos - g_player[nCntPlayer].pos;
				fVector[nCnt] = D3DXVec3Length(&D3DXVECTOR3(vector[nCnt].x, 0, vector[nCnt].z));

				if (fVectorA > fVector[nCnt])
				{	//��ԋ߂��v���C���[
					fVectorA = fVector[nCnt];
					vectorA = vector[nCnt];
					g_player[nCntPlayer].nNearPlayer = nCnt;
				}
			}
		}

		//���̃v���C���[���򋗗����ɂ��邩�ǂ���
		if (fVectorA <= DIS_BOMB)
		{//�򋗗����ɂ���ꍇ

		 //���������鏈���̓v���C���[�̌����œ�������������߂�̂ł��̃v���C���[�̕����Ɍ�����
			fAngle = atan2f(vectorA.x, vectorA.z);
			g_player[nCntPlayer].rotDest.y = (fAngle += D3DX_PI);

			//������
			if (g_player[nCntPlayer].rot == g_player[nCntPlayer].rotDest)
			{

			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�v���C���[���m�̓����蔻��
////////////////////////////////////////////////////////////////////////////////
bool CollisionPlayer(int nCntPlayer)
{
	D3DXVECTOR3 vector[MAX_DISPLAY_CHARA];
	float fVector[MAX_DISPLAY_CHARA];
	float fPlayerSize;

	for (int nCnt = 0; nCnt < g_nDisPlayer; nCnt++)
	{
		if (nCnt != nCntPlayer)
		{
			vector[nCnt] = g_player[nCnt].pos - g_player[nCntPlayer].pos;
			fVector[nCnt] = D3DXVec3Length(&D3DXVECTOR3(vector[nCnt].x, 0.0f, vector[nCnt].z));

			fPlayerSize = ((g_player[nCntPlayer].pos.x + g_player[nCntPlayer].maxVecPlayer.x) - g_player[nCntPlayer].pos.x) * 3;

			if (fVector[nCnt] < fPlayerSize)
			{
				float fAngle = atan2f(vector[nCnt].x, vector[nCnt].z);
				g_player[nCntPlayer].bPush = true;

				g_player[nCnt].pos.x += sinf(fAngle) * fPlayerSize /10;
				g_player[nCnt].pos.z += cosf(fAngle) * fPlayerSize /10;
				return true;
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------
// �v���C���[�̈ړ�����(�L�[�{�[�h)
//-----------------------------------------------------------------
void MovePlayerKeyboard(int nCntPlayer)
{
	// ���̎擾
	Camera *pCamera = GetCamera();				// �J�������
#if 0
	if (GetKeyboardPress(KEYINFO_UP) == true)
	{
		if (GetKeyboardPress(KEYINFO_RIGHT) == true)
		{// ���f���΂߉E��ړ�
			g_player[nCntPlayer].move.z -= MOVE_MODEL * sinf(pCamera->CameraInfo[0].rot.y - PI_QUARTER);
			g_player[nCntPlayer].move.x += MOVE_MODEL * cosf(pCamera->CameraInfo[0].rot.y - PI_QUARTER);
			g_player[nCntPlayer].rotDest.y = pCamera->CameraInfo[0].rot.y - PI_QUARTER * 3.0f;
		}
		else if (GetKeyboardPress(KEYINFO_LEFT) == true)
		{// ���f���΂߉E��ړ�
			g_player[nCntPlayer].move.z += MOVE_MODEL * sinf(pCamera->CameraInfo[0].rot.y + PI_QUARTER);
			g_player[nCntPlayer].move.x -= MOVE_MODEL * cosf(pCamera->CameraInfo[0].rot.y + PI_QUARTER);
			g_player[nCntPlayer].rotDest.y = pCamera->CameraInfo[0].rot.y + PI_QUARTER * 3.0f;
		}
		else
		{// ���f����ړ�
			g_player[nCntPlayer].move.z += MOVE_MODEL * cosf(pCamera->CameraInfo[0].rot.y);
			g_player[nCntPlayer].move.x += MOVE_MODEL * sinf(pCamera->CameraInfo[0].rot.y);
			g_player[nCntPlayer].rotDest.y = pCamera->CameraInfo[0].rot.y - D3DX_PI;
		}
		// �ړ����Ă���Ƃ��ړ����[�V�����ɐݒ�
		SetMotion(nCntPlayer, MOTIONTYPE_MOVE, false, 0);
	}
	else if (GetKeyboardPress(KEYINFO_DOWN) == true)
	{
		if (GetKeyboardPress(KEYINFO_RIGHT) == true)
		{// ���f���΂߉E��ړ�
			g_player[nCntPlayer].move.z -= MOVE_MODEL * sinf(pCamera->CameraInfo[0].rot.y + PI_QUARTER);
			g_player[nCntPlayer].move.x += MOVE_MODEL * cosf(pCamera->CameraInfo[0].rot.y + PI_QUARTER);
			g_player[nCntPlayer].rotDest.y = pCamera->CameraInfo[0].rot.y - PI_QUARTER;
		}
		else if (GetKeyboardPress(KEYINFO_LEFT) == true)
		{// ���f���΂߉E��ړ�
			g_player[nCntPlayer].move.z += MOVE_MODEL * sinf(pCamera->CameraInfo[0].rot.y - PI_QUARTER);
			g_player[nCntPlayer].move.x -= MOVE_MODEL * cosf(pCamera->CameraInfo[0].rot.y - PI_QUARTER);
			g_player[nCntPlayer].rotDest.y = pCamera->CameraInfo[0].rot.y + PI_QUARTER;
		}
		else
		{// ���f�����ړ�
			g_player[nCntPlayer].move.z -= MOVE_MODEL * cosf(pCamera->CameraInfo[0].rot.y);
			g_player[nCntPlayer].move.x -= MOVE_MODEL * sinf(pCamera->CameraInfo[0].rot.y);
			g_player[nCntPlayer].rotDest.y = pCamera->CameraInfo[0].rot.y;
		}
		// �ړ����Ă���Ƃ��ړ����[�V�����ɐݒ�
		SetMotion(nCntPlayer, MOTIONTYPE_MOVE, false, 0);
	}
	else if (GetKeyboardPress(KEYINFO_RIGHT) == true)
	{// ���f���E�ړ�
		g_player[nCntPlayer].move.z -= MOVE_MODEL * sinf(pCamera->CameraInfo[0].rot.y);
		g_player[nCntPlayer].move.x += MOVE_MODEL * cosf(pCamera->CameraInfo[0].rot.y);
		g_player[nCntPlayer].rotDest.y = pCamera->CameraInfo[0].rot.y - D3DX_PI / 2.0f;

		// �ړ����Ă���Ƃ��ړ����[�V�����ɐݒ�
		SetMotion(nCntPlayer, MOTIONTYPE_MOVE, false, 0);
	}
	else if (GetKeyboardPress(KEYINFO_LEFT) == true)
	{// ���f�����ړ�
		g_player[nCntPlayer].move.z += MOVE_MODEL * sinf(pCamera->CameraInfo[0].rot.y);
		g_player[nCntPlayer].move.x -= MOVE_MODEL * cosf(pCamera->CameraInfo[0].rot.y);
		g_player[nCntPlayer].rotDest.y = pCamera->CameraInfo[0].rot.y + D3DX_PI / 2.0f;

		// �ړ����Ă���Ƃ��ړ����[�V�����ɐݒ�
		SetMotion(nCntPlayer, MOTIONTYPE_MOVE, false, 0);
	}
	if (GetKeyboardTrigger(KEYINFO_SHOOT) == true &&
		g_player[nCntPlayer].state != PLAYERSTATE_FLOATING)
	{
		g_player[nCntPlayer].move.y += JUMP_PLAYER;
		g_player[nCntPlayer].state = PLAYERSTATE_FLOATING;

		// �����o��
		//PlaySound(SOUND_LABEL_SE_JUMP);
	}
#endif
}

//-----------------------------------------------------------------
// �v���C���[�̈ړ�����(�Q�[���p�b�h)
//-----------------------------------------------------------------
void MovePlayerGamepad(int nCntPlayer)
{
	// ���̎擾
	Camera *pCamera = GetCamera();				// �J�������

	// �Q�[���p�b�h���̎擾
	DIJOYSTATE2 Controller = GetControllerPless(nCntPlayer);

	// JOYPAD�̃X�e�B�b�N����
	// �ړ�����
	if (Controller.lX != 0 || Controller.lY != 0)
	{// �X�e�B�b�N�̓��͊p�x
		float fAngle = atan2f((float)Controller.lX, (float)Controller.lY);

		g_player[nCntPlayer].rotDest.y = pCamera->CameraInfo[0].rot.y - fAngle;								// �����̐ݒ�
		g_player[nCntPlayer].move.x -= MOVE_PLAYER * sinf(g_player[nCntPlayer].rotDest.y);			// X���ړ��ʂ̌���
		g_player[nCntPlayer].move.z -= MOVE_PLAYER * cosf(g_player[nCntPlayer].rotDest.y);			// Z���ړ��ʂ̌���

		// ���݂̉�]�p�𐧌�
		if (g_player[nCntPlayer].rotDest.y > D3DX_PI)
		{// 3.14f���傫���Ȃ����Ƃ��l��-3.14f�ɂ���
			g_player[nCntPlayer].rotDest.y -= D3DX_PI * 2.0f;
		}
		else if (g_player[nCntPlayer].rotDest.y < -D3DX_PI)
		{// -3.14f��菬�����Ȃ����Ƃ��l��3.14f�ɂ���
			g_player[nCntPlayer].rotDest.y += D3DX_PI * 2.0f;
		}
		// ���[�V�������ړ����[�V�����ɂ���
		SetMotion(nCntPlayer,MOTIONTYPE_MOVE,true,10);
	}
	// �������[�V����
	if (GetJoypadTrigger(nCntPlayer, JPINFO_OKorJUMP) == true &&
		g_player[nCntPlayer].state != PLAYERSTATE_FLOATING)
	{
		// ���[�V�����𓊂����[�V�����ɂ���
		SetMotion(nCntPlayer, MOTIONTYPE_THROW, true, 10);
		g_player[nCntPlayer].state = PLAYERSTATE_THROW;
	}
	// �W�����v����
	if (GetJoypadTrigger(nCntPlayer, JPINFO_CANCEL) == true &&
		g_player[nCntPlayer].state != PLAYERSTATE_FLOATING)
	{
		g_player[nCntPlayer].move.y += JUMP_PLAYER;
		g_player[nCntPlayer].state = PLAYERSTATE_FLOATING;
		// ���[�V�����𓊂����[�V�����ɂ���
		SetMotion(nCntPlayer, MOTIONTYPE_JUMP, true, 10);
	}
}

//-----------------------------------------------------------------
// �v���C���[���̎擾
//-----------------------------------------------------------------
Player *GetPlayer(void)
{
	return &g_player[0];
}

//-----------------------------------------------------------------
// �v���C��-���[�V�����̐ݒ�
//-----------------------------------------------------------------
void PlayerMotion(int nCntPlayer)
{
	// �ϐ��錾
	Player *pPlayer = GetPlayer();
	pPlayer += nCntPlayer;	// ���Ԗڂ̃v���C���[��
	KEY *pKey;				// �L�[���
	KEY *pKeyNext;			// ���̃L�[���
	KEY *pKeyBlend;			// �u�����h�L�[���
	KEY *pKeyNextBlend;		// ���̃u�����h�L�[���
	float fPosX;
	float fPosY;
	float fPosZ;
	float fRotX;
	float fRotY;
	float fRotZ;

	for (int nCntModel = 0; nCntModel < g_player[nCntPlayer].nNumModel; nCntModel++)
	{
		// �L�[�̊m��
		pKey = &pPlayer->aMotionInfo[pPlayer->MotionType].aKeyInfo[pPlayer->nKey].aKey[nCntModel];
		pKeyNext = &pPlayer->aMotionInfo[pPlayer->MotionType].aKeyInfo[(pPlayer->nKey + 1) % pPlayer->nNumKey].aKey[nCntModel];

		// �����̊m��
		float fDiffMoitonPosX = pKeyNext->fPosX - pKey->fPosX;
		float fDiffMoitonPosY = pKeyNext->fPosY - pKey->fPosY;
		float fDiffMoitonPosZ = pKeyNext->fPosZ - pKey->fPosZ;
		float fDiffMoitonRotX = pKeyNext->fRotX - pKey->fRotX;
		float fDiffMoitonRotY = pKeyNext->fRotY - pKey->fRotY;
		float fDiffMoitonRotZ = pKeyNext->fRotZ - pKey->fRotZ;

		// ���Βl�̊m��
		float fRateMotion = (float)pPlayer->nCounterMotion / (float)pPlayer->aMotionInfo[pPlayer->MotionType].aKeyInfo[pPlayer->nKey].nFrame;

		if (g_player[nCntPlayer].bBlendMotion == true)
		{
			// �L�[�̊m��
			pKeyBlend = &pPlayer->aMotionInfo[pPlayer->MotionTypeBlend].aKeyInfo[pPlayer->nKeyBlend].aKey[nCntModel];
			pKeyNextBlend = &pPlayer->aMotionInfo[pPlayer->MotionTypeBlend].aKeyInfo[(pPlayer->nKeyBlend + 1) % pPlayer->nNumKeyBlend].aKey[nCntModel];

			// �����̊m��
			float fDiffMoitonBlendPosX = pKeyNextBlend->fPosX - pKeyBlend->fPosX;
			float fDiffMoitonBlendPosY = pKeyNextBlend->fPosY - pKeyBlend->fPosY;
			float fDiffMoitonBlendPosZ = pKeyNextBlend->fPosZ - pKeyBlend->fPosZ;
			float fDiffMoitonBlendRotX = pKeyNextBlend->fRotX - pKeyBlend->fRotX;
			float fDiffMoitonBlendRotY = pKeyNextBlend->fRotY - pKeyBlend->fRotY;
			float fDiffMoitonBlendRotZ = pKeyNextBlend->fRotZ - pKeyBlend->fRotZ;

			// ���Βl�̊m��
			float fRateMotionBlend = (float)pPlayer->nCounterMotionBlend / (float)pPlayer->aMotionInfo[pPlayer->MotionTypeBlend].aKeyInfo[pPlayer->nKeyBlend].nFrame;

			float fRateBlend = (float)pPlayer->nCounterBlend / (float)pPlayer->nFrameBlend;

			// ���݂̃��[�V�����̈ʒu�ƌ����̊m��
			float fPosXCurrent = pKey->fPosX + (fDiffMoitonPosX * fRateMotion);
			float fPosYCurrent = pKey->fPosY + (fDiffMoitonPosY * fRateMotion);
			float fPosZCurrent = pKey->fPosZ + (fDiffMoitonPosZ * fRateMotion);
			float fRotXCurrent = pKey->fRotX + (fDiffMoitonRotX * fRateMotion);
			float fRotYCurrent = pKey->fRotY + (fDiffMoitonRotY * fRateMotion);
			float fRotZCurrent = pKey->fRotZ + (fDiffMoitonRotZ * fRateMotion);

			// �p�x�̐���
			D3DXVECTOR3(fRotXCurrent, fRotYCurrent, fRotZCurrent) = AngleCorrection(fRotXCurrent, fRotYCurrent, fRotZCurrent);

			// �u�����h���[�V�����̈ʒu�ƌ����̊m��
			float fPosXBlend = pKeyBlend->fPosX + (fDiffMoitonBlendPosX * fRateMotionBlend);
			float fPosYBlend = pKeyBlend->fPosY + (fDiffMoitonBlendPosY * fRateMotionBlend);
			float fPosZBlend = pKeyBlend->fPosZ + (fDiffMoitonBlendPosZ * fRateMotionBlend);
			float fRotXBlend = pKeyBlend->fRotX + (fDiffMoitonBlendRotX * fRateMotionBlend);
			float fRotYBlend = pKeyBlend->fRotY + (fDiffMoitonBlendRotY * fRateMotionBlend);
			float fRotZBlend = pKeyBlend->fRotZ + (fDiffMoitonBlendRotZ * fRateMotionBlend);

			// �p�x�̐���
			D3DXVECTOR3(fRotXBlend, fRotYBlend, fRotZBlend) = AngleCorrection(fRotXBlend, fRotYBlend, fRotZBlend);

			// ���݂̃��[�V�����ƃu�����h���[�V�����̍���
			float fDiffBlendPosX = fPosXBlend - fPosXCurrent;
			float fDiffBlendPosY = fPosYBlend - fPosYCurrent;
			float fDiffBlendPosZ = fPosZBlend - fPosZCurrent;
			float fDiffBlendRotX = fRotXBlend - fRotXCurrent;
			float fDiffBlendRotY = fRotYBlend - fRotYCurrent;
			float fDiffBlendRotZ = fRotZBlend - fRotZCurrent;

			// �p�x�̐���
			D3DXVECTOR3(fDiffBlendRotX, fDiffBlendRotY, fDiffBlendRotZ) = AngleCorrection(fDiffBlendRotX, fDiffBlendRotY, fDiffBlendRotZ);

			// �u�����h���[�V�����̈ʒu�ƌ����̊m��
			fPosX = fPosXCurrent + (fDiffBlendPosX * fRateBlend);
			fPosY = fPosYCurrent + (fDiffBlendPosY * fRateBlend);
			fPosZ = fPosZCurrent + (fDiffBlendPosZ * fRateBlend);
			fRotX = fRotXCurrent + (fDiffBlendRotX * fRateBlend);
			fRotY = fRotYCurrent + (fDiffBlendRotY * fRateBlend);
			fRotZ = fRotZCurrent + (fDiffBlendRotZ * fRateBlend);
		}
		else
		{
			// ���[�V�����̈ʒu�ƌ����̊m��
			fPosX = pKey->fPosX + (fDiffMoitonPosX * fRateMotion);
			fPosY = pKey->fPosY + (fDiffMoitonPosY * fRateMotion);
			fPosZ = pKey->fPosZ + (fDiffMoitonPosZ * fRateMotion);
			fRotX = pKey->fRotX + (fDiffMoitonRotX * fRateMotion);
			fRotY = pKey->fRotY + (fDiffMoitonRotY * fRateMotion);
			fRotZ = pKey->fRotZ + (fDiffMoitonRotZ * fRateMotion);
		}
		// �p�x�̐���
		D3DXVECTOR3(fRotX, fRotY, fRotZ) = AngleCorrection(fRotX, fRotY, fRotZ);

		// �ʒu�ƌ����̐ݒ�
		pPlayer->aModel[nCntModel].pos.x = fPosX;
		pPlayer->aModel[nCntModel].pos.y = fPosY;
		pPlayer->aModel[nCntModel].pos.z = fPosZ;
		pPlayer->aModel[nCntModel].rot.x = fRotX;
		pPlayer->aModel[nCntModel].rot.y = fRotY;
		pPlayer->aModel[nCntModel].rot.z = fRotZ;
	}

	if (g_player[nCntPlayer].bBlendMotion == true)
	{
		if (pPlayer->nCounterMotionBlend > pPlayer->aMotionInfo[pPlayer->MotionTypeBlend].aKeyInfo[pPlayer->nKeyBlend].nFrame)
		{
			// �u�����h���[�V�����J�E���^�̏�����
			pPlayer->nCounterMotionBlend = 0;

			// �L�[�̍X�V
			pPlayer->nKeyBlend++;

			// �L�[�̊m��
			pPlayer->nKeyBlend = pPlayer->nKeyBlend % pPlayer->nNumKeyBlend;
		}
		else
		{
			// �u�����h���[�V�����J�E���^�̍X�V
			pPlayer->nCounterMotionBlend++;

			// �u�����h�J�E���^�̍X�V
			pPlayer->nCounterBlend++;

			if (pPlayer->nCounterBlend >= pPlayer->nFrameBlend)
			{
				// ���[�V�����̊m��
				pPlayer->MotionType = pPlayer->MotionTypeBlend;

				// ���[�V�����J�E���^��������
				pPlayer->nCounterMotion = pPlayer->nCounterMotionBlend;

				// ���݂̃L�[��������
				pPlayer->nKey = pPlayer->nKeyBlend;

				// ���[�v���邩�ǂ���
				pPlayer->bLoopMotion = pPlayer->bLoopMotionBlend;

				// �L�[���̊m��
				pPlayer->nNumKey = pPlayer->nNumKeyBlend;

				// ���[�V�����u�����h���I����
				pPlayer->bBlendMotion = false;

				pPlayer->bFinishMotion = false;
			}
		}
	}
	else
	{
		if (pPlayer->nCounterMotion > pPlayer->aMotionInfo[pPlayer->MotionType].aKeyInfo[pPlayer->nKey].nFrame)
		{
			// ���[�V�����J�E���^�̏�����
			pPlayer->nCounterMotion = 0;

			// �L�[�̍X�V
			pPlayer->nKey++;

			// �L�[�̊m��
			pPlayer->nKey = pPlayer->nKey % pPlayer->nNumKey;

			if (pPlayer->nKey == (pPlayer->nNumKey - 1))
			{
				if (pPlayer->aMotionInfo[pPlayer->MotionType].bLoop == false)
				{
					if ((pPlayer->MotionType == MOTIONTYPE_THROW) || (pPlayer->MotionType == MOTIONTYPE_JUMP))
					{
						SetMotion(nCntPlayer, MOTIONTYPE_NEUTRAL, true, 10);
					}
				}
			}
		}
		else if (pPlayer->MotionType == MOTIONTYPE_THROW &&
			pPlayer->nKey == 1 &&
			pPlayer->nCounterMotion == 5)
		{
			BombThrow(pPlayer->nBombID, pPlayer->pos, pPlayer->rot);
			pPlayer->nBombID = -1;
		}
		// ���[�V�����J�E���^�̍X�V
		pPlayer->nCounterMotion++;
	}
}

//-----------------------------------------------------------------
// ���[�V�����̐ݒ�
//-----------------------------------------------------------------
void SetMotion(int nCntPlayer,MOTIONTYPE motiontype, bool bBlend, int nFrameBlend)
{
	// �ϐ��錾
	Player *pPlayer = GetPlayer();
	pPlayer += nCntPlayer;

	switch (motiontype)
	{
	case MOTIONTYPE_NEUTRAL:
		pPlayer->state = PLAYERSTATE_NORMAL;
		break;

	case MOTIONTYPE_MOVE:
		break;

	case MOTIONTYPE_THROW:
		pPlayer->state = PLAYERSTATE_THROW;
		break;

	case MOTIONTYPE_LAND:
		break;

	case MOTIONTYPE_DAMAGE:
		pPlayer->state = PLAYERSTATE_DAMAGE;
		break;

	default:
		break;
	}
	//if (pPlayer->bFinishMotion == true)
	{
		if (bBlend == true && pPlayer->MotionTypeBlend != motiontype)
		{
			// ���[�V�����̊m��
			pPlayer->MotionTypeBlend = motiontype;

			// ���[�V�����J�E���^��������
			pPlayer->nCounterMotionBlend = 0;

			// ���݂̃L�[��������
			pPlayer->nKeyBlend = 0;

			// ���[�v���邩�ǂ���
			pPlayer->bLoopMotionBlend = pPlayer->aMotionInfo[pPlayer->MotionTypeBlend].bLoop;

			// �L�[���̊m��
			pPlayer->nNumKeyBlend = pPlayer->aMotionInfo[pPlayer->MotionTypeBlend].nNumKey;

			// �u�����h�t���[���̐ݒ�
			pPlayer->nFrameBlend = nFrameBlend;

			// �u�����h���邩�ǂ���
			pPlayer->bBlendMotion = bBlend;

			// �u�����h�J�E���^�̏�����
			pPlayer->nCounterBlend = 0;
		}
		else if (bBlend == false && pPlayer->MotionType != motiontype && pPlayer->bFinishMotion == true)
		{
			// ���[�V�����̊m��
			pPlayer->MotionType = motiontype;

			// ���[�V�����J�E���^��������
			pPlayer->nCounterMotion = 0;

			// ���݂̃L�[��������
			pPlayer->nKey = 0;

			// ���[�v���邩�ǂ���
			pPlayer->bLoopMotion = pPlayer->aMotionInfo[pPlayer->MotionType].bLoop;

			// �L�[���̊m��
			pPlayer->nNumKey = pPlayer->aMotionInfo[pPlayer->MotionType].nNumKey;

			pPlayer->bFinishMotion = false;
		}
	}
}

//-----------------------------------------------------------------
// �p�x�̐���
//-----------------------------------------------------------------
D3DXVECTOR3 AngleCorrection(float rotX, float rotY, float rotZ)
{
	// ���݂̉�]�p�𐧌�
	if (rotX > D3DX_PI)
	{// 3.14f���傫���Ȃ����Ƃ��l��-3.14f�ɂ���
		rotX -= D3DX_PI * 2.0f;
	}
	else if (rotX < -D3DX_PI)
	{// -3.14f��菬�����Ȃ����Ƃ��l��3.14f�ɂ���
		rotX += D3DX_PI * 2.0f;
	}
	// ���݂̉�]�p�𐧌�
	if (rotY  > D3DX_PI)
	{// 3.14f���傫���Ȃ����Ƃ��l��-3.14f�ɂ���
		rotY -= D3DX_PI * 2.0f;
	}
	else if (rotY < -D3DX_PI)
	{// -3.14f��菬�����Ȃ����Ƃ��l��3.14f�ɂ���
		rotY += D3DX_PI * 2.0f;
	}
	// ���݂̉�]�p�𐧌�
	if (rotZ > D3DX_PI)
	{// 3.14f���傫���Ȃ����Ƃ��l��-3.14f�ɂ���
		rotZ -= D3DX_PI * 2.0f;
	}
	else if (rotZ < -D3DX_PI)
	{// -3.14f��菬�����Ȃ����Ƃ��l��3.14f�ɂ���
		rotZ += D3DX_PI * 2.0f;
	}

	return D3DXVECTOR3(rotX, rotY, rotZ);
}