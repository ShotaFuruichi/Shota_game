////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �v���C���[�̏��� [player.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/12/17
//
////////////////////////////////////////////////////////////////////////////////
#include "player.h"
#include "camera.h"
#include "input.h"
#include "bullet.h"
#include "xinput_pad.h"
#include "object.h"
#include "fade.h"
#include "enemy.h"
#include "result.h"
#include "circle.h"
#include "effect.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define PMOVE_SPEED (5.0f)				//�v���C���[�̈ړ����x
#define MAX_INVI (4)					//�����ȕǂ̖���
#define EX_INVI (2000)					//�����ȕǂ̑傫��
#define PLAYER_APPEARX (0)				//�v���C���[�̏o���ʒuX���W
#define PLAYER_APPEARZ (-EX_INVI + 30)	//�v���C���[�̏o���ʒuZ���W
#define MP_COUNT (SEC_ONE * 15)			//mp�񕜂̊Ԋu
#define MP_RECOVERY (1000)				//mp�̉񕜗�
#define ATTACK_REACH (500.0f)			//�����U�����͂�����

#define ATTACK_DAMAGE (500)				//�����U���̈З�
#define HEAL_POWER (800)				//�񕜖��@�̌���

#define MAGIC_MP (600)					//�U�����@�̏���MP
#define HEAL_MP (800)					//�񕜖��@�̏���MP

#define NEUT_KEY (2)					//�j���[�g�������[�V�����̃L�[��
#define MOVE_KEY (4)					//�ړ����[�V�����̃L�[��
#define JUMP_KEY (5)					//�W�����v���[�V�����̃L�[��
#define ACTION_KEY (3)					//�A�N�V�������[�V�����̃L�[��

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
PLAYER g_Player;				//�v���C���[
D3DXVECTOR3 aPos[MAX_INVI];		//�O��
float fGaiseki[MAX_INVI * 2];	//�O��

////////////////////////////////////////////////////////////////////////////////
//����������
////////////////////////////////////////////////////////////////////////////////
void InitPlayer(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/model/body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[0].pBufferMat, NULL, &g_Player.aModel[0].nNumMat, &g_Player.aModel[0].pMesh);
	D3DXLoadMeshFromX("data/model/head.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[1].pBufferMat, NULL, &g_Player.aModel[1].nNumMat, &g_Player.aModel[1].pMesh);
	D3DXLoadMeshFromX("data/model/armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[2].pBufferMat, NULL, &g_Player.aModel[2].nNumMat, &g_Player.aModel[2].pMesh);
	D3DXLoadMeshFromX("data/model/armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[3].pBufferMat, NULL, &g_Player.aModel[3].nNumMat, &g_Player.aModel[3].pMesh);
	D3DXLoadMeshFromX("data/model/legR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[4].pBufferMat, NULL, &g_Player.aModel[4].nNumMat, &g_Player.aModel[4].pMesh);
	D3DXLoadMeshFromX("data/model/legL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[5].pBufferMat, NULL, &g_Player.aModel[5].nNumMat, &g_Player.aModel[5].pMesh);

	g_Player.nNumModel = MAX_MODEL_PLAYER;
	aPos[0] = D3DXVECTOR3(EX_INVI, 0.0f, EX_INVI);
	aPos[1] = D3DXVECTOR3(-EX_INVI, 0.0f, EX_INVI);
	aPos[2] = D3DXVECTOR3(-EX_INVI, 0.0f, -EX_INVI);
	aPos[3] = D3DXVECTOR3(EX_INVI, 0.0f, -EX_INVI);

	//�e�p�[�c�̊K�w�\���ݒ�
	g_Player.aModel[0].nIdxModelParent = -1;							//�e���f���̃C���f�b�N�X��ݒ�
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0f, 45.0f, 0.0f);			//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����̏����ݒ�
	g_Player.aModel[1].nIdxModelParent = 0;								//�e���f���̃C���f�b�N�X��ݒ�
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0f, 60.0f, 0.0f);			//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����̏����ݒ�
	g_Player.aModel[2].nIdxModelParent = 0;								//�e���f���̃C���f�b�N�X��ݒ�
	g_Player.aModel[2].pos = D3DXVECTOR3(-13.0f, 57.5f, 2.5f);			//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����̏����ݒ�
	g_Player.aModel[3].nIdxModelParent = 0;								//�e���f���̃C���f�b�N�X��ݒ�
	g_Player.aModel[3].pos = D3DXVECTOR3(13.0f, 57.5f, 2.6f);			//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����̏����ݒ�
	g_Player.aModel[4].nIdxModelParent = 0;								//�e���f���̃C���f�b�N�X��ݒ�
	g_Player.aModel[4].pos = D3DXVECTOR3(-10.0f, 7.5f, 2.5f);			//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����̏����ݒ�
	g_Player.aModel[5].nIdxModelParent = 0;								//�e���f���̃C���f�b�N�X��ݒ�
	g_Player.aModel[5].pos = D3DXVECTOR3(10.0f, 7.5f, 2.5f);			//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����̏����ݒ�

	g_Player.pos = D3DXVECTOR3(PLAYER_APPEARX, 0.0f, PLAYER_APPEARZ);	//�v���C���[�̈ʒu�̏����ݒ�
	g_Player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�v���C���[�̑O��X�V���̈ʒu�̏����ݒ�
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//�v���C���[�̌����̏����ݒ�
	g_Player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�v���C���[�̖ڕW�̌����̏����ݒ�
	g_Player.nowMotion = MOTION_NEUTRAL;								//�v���C���[�̌��݂̃��[�V�����̏����ݒ�
	g_Player.fGravity = 0.0f;											//�d�͂̏����ݒ�
	g_Player.bJump = true;												//�W�����v�̉s�̏����ݒ�
	g_Player.nLife = LIFE_PLAYER;										//�v���C���[�̗̑͂̏����ݒ�
	g_Player.nMP = MP_PLAYER;											//�v���C���[��mp�̏����ݒ�
	g_Player.nMpRec = 0;												//mp�񕜂̂��߂̃J�E���^
	g_Player.bMove = false;												//�v���C���[���ړ�����
	g_Player.bChant = false;											//�v���C���[���r������
	g_Player.nCooldown = 0;												//�X�L���̃N�[���_�E��
	g_Player.bUseSkill = true;											//�X�L�����g���邩
	g_Player.nChantCounter = 0;											//�r������
	g_Player.skill = SKILL_NONE;										//�g�p����X�L��
}

////////////////////////////////////////////////////////////////////////////////
//�I������
////////////////////////////////////////////////////////////////////////////////
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL_PLAYER; nCntModel++)
	{
		if (g_Player.aModel[nCntModel].pMesh != NULL)
		{
			g_Player.aModel[nCntModel].pMesh->Release();	//�j��
			g_Player.aModel[nCntModel].pMesh = NULL;		//������
		}

		if (g_Player.aModel[nCntModel].pBufferMat != NULL)
		{
			g_Player.aModel[nCntModel].pBufferMat->Release();	//�j��
			g_Player.aModel[nCntModel].pBufferMat = NULL;		//������
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdatePlayer(void)
{	
	//���[�V�����̗D��x�Ǘ�
	if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION)
	{	
		g_Player.nowMotion = MOTION_NEUTRAL;
	}

	g_Player.bMove = false;

	//MP��
	if (g_Player.nMP != MP_PLAYER)
	{
		g_Player.nMpRec++;
	}

	if (g_Player.nMpRec % MP_COUNT == 0)
	{
		int nRec = MP_RECOVERY;
		if (g_Player.nMP + MP_RECOVERY > MP_PLAYER)
		{
			nRec = MP_PLAYER - g_Player.nMP;
		}
		g_Player.nMP += nRec;
	}

	MovePlayer();
	SkillPlayer();
	MotionPlayer();

	if (g_Player.nLife <= 0)
	{	//�v���C���[�̗̑͂�0�ȉ��ɂȂ����ꍇ���U���g��
		SetFade(FADE_OUT, MODE_RESULT);
	}
}

////////////////////////////////////////////////////////////////////////////////
//�`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	//�v���C���[�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//�v���C���[�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	//�v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	//�v���C���[�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;					//�e�̃}�g���b�N�X

		//�e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

		//�e�p�[�c�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRot);

		//�e�p�[�c�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTrans);

		//�e�p�[�c�̐e�̃}�g���b�N�X��ݒ�
		if (g_Player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_Player.mtxWorld;	//�v���C���[�̃}�g���b�N�X��ݒ�
		}

		//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxParent);

		//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorld);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL *)g_Player.aModel[nCntModel].pBufferMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nNumMat; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//���f��(�p�[�c)�̕`��
			g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

////////////////////////////////////////////////////////////////////////////////
//�v���C���[�̃X�L������
////////////////////////////////////////////////////////////////////////////////
void SkillPlayer(void)
{
	//�ϐ���`
	XinputGamepad *pXinput = GetXinputGamepad();
	ENEMY *enemy = GetEnemy();
	static int nCntEff = 0;

	if (g_Player.nCooldown > 0)
	{	//�N�[���_�E��
		g_Player.nCooldown--;
	}

	if (g_Player.bChant == false)
	{
		if (g_Player.nCooldown == 0)
		{
			g_Player.bUseSkill = true;
		}
	}

	//�X�L���g�p
	if (g_Player.bUseSkill == true)
	{
		if (GetKeyboardTrigger(DIK_1) == TRUE || pXinput->bPressB == true)
		{
			float fDis;
			float fReach = powf(ATTACK_REACH, 2.0f);
			float fDisX = g_Player.pos.x - enemy->pos.x;
			float fDisZ = g_Player.pos.z - enemy->pos.z;
			fDisX = powf(fDisX, 2.0f);
			fDisZ = powf(fDisZ, 2.0f);
			fDis = fDisX + fDisZ;
			
			if (fDis < fReach)
			{
				g_Player.skill = SKILL_ATTACK;
				g_Player.bUseSkill = false;
			}
		}

		if (g_Player.nMP >= MAGIC_MP)
		{
			if (GetKeyboardTrigger(DIK_2) == TRUE || pXinput->bPressY == true)
			{
				g_Player.skill = SKILL_MAGICBALL;
				g_Player.nCooldown = MAX_COOLDOWN;
				g_Player.bUseSkill = false;
				SetCircle(SKILL_MAGICBALL);
			}
		}

		if (g_Player.nMP >= HEAL_MP)
		{
			if (GetKeyboardTrigger(DIK_3) == TRUE || pXinput->bPressX == true)
			{
				g_Player.skill = SKILL_HEAL;
				g_Player.nCooldown = MAX_COOLDOWN;
				g_Player.bUseSkill = false;
				SetCircle(SKILL_HEAL);
			}
		}
	}
		
	//�����U��
	if (g_Player.skill == SKILL_ATTACK)
	{
		//�_���[�W��
		int nAttack = GetRandom(ATTACK_DAMAGE, ATTACK_DAMAGE + 200);

		g_Player.bChant = true;

		if (enemy->nLife - nAttack < 0)
		{	//�U�����G�̎c��HP�𒴂����Ƃ�0�܂ł̃_���[�W�ɕϊ�
			nAttack = enemy->nLife;
		}

		g_Player.nowMotion = MOTION_ACTION;
		enemy->nLife -= nAttack;
		g_Player.nCooldown = MAX_COOLDOWN;
		g_Player.skill = SKILL_NONE;
		g_Player.bChant = false;
	}

	//�U�����@
	if (g_Player.skill == SKILL_MAGICBALL)
	{
		if (g_Player.bChant == false)
		{
			g_Player.nChantCounter = (int)CHANT_TIMEMAGIC;
		}
		g_Player.nChantCounter--;
		g_Player.bChant = true;

		if (g_Player.nChantCounter == 0)
		{	//�r���I�����ɉ񕜁A�N�[���_�E����ݒ�
			SetBullet(D3DXVECTOR3(g_Player.pos.x + sinf(g_Player.rot.y) * -100, g_Player.pos.y + 70, g_Player.pos.z + cosf(g_Player.rot.y) * -100));
			g_Player.skill = SKILL_NONE;
			g_Player.bChant = false;
			g_Player.nMP -= MAGIC_MP;
		}
	}

	//�񕜖��@
	if (g_Player.skill == SKILL_HEAL)
	{
		//HP�񕜗�
		int nHeal = HEAL_POWER;

		if (g_Player.bChant == false)
		{
			g_Player.nChantCounter = CHANT_TIMEHEAL;
		}
		g_Player.nChantCounter--;
		g_Player.bChant = true;

		if (g_Player.nLife + nHeal > LIFE_PLAYER)
		{	//HP����𒴂����񕜂�����܂ł̉񕜂ɕϊ�
			nHeal = LIFE_PLAYER - g_Player.nLife;
		}

		if (g_Player.nChantCounter == 0)
		{	//�r���I�����ɉ񕜁A�N�[���_�E����ݒ�
			g_Player.nLife += nHeal;
			g_Player.skill = SKILL_NONE;
			g_Player.bChant = false;
			g_Player.nMP -= HEAL_MP;
			nCntEff = 30;
		}
	}

	if (nCntEff > 0)
	{
		SetEffect(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 50, g_Player.pos.z), D3DXCOLOR(0.0f, 1.f, 0.6f, 0.2f));
		nCntEff--;
	}
		
	if (g_Player.bChant == true)
	{	//�r�����ɓ�������r�����f
		if (g_Player.bMove == true)
		{
			g_Player.skill = SKILL_NONE;
			g_Player.nCooldown = 0;
			g_Player.bChant = false;

		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�v���C���[�̈ړ�����
////////////////////////////////////////////////////////////////////////////////
void MovePlayer(void)
{
	CAMERA *camera = GetCamera();
	XinputGamepad *pXinput = GetXinputGamepad();
	ENEMY *enemy = GetEnemy();

	//�ʒu��ۑ�
	g_Player.posOld = g_Player.pos;

	if (g_Player.rotDest.y - g_Player.rot.y < -D3DX_PI)
	{// -3.14f��菬�����Ȃ����Ƃ��l��3.14f�ɂ���
		g_Player.rotDest.y += D3DX_PI * 2.0f;
	}
	else if (g_Player.rotDest.y - g_Player.rot.y > D3DX_PI)
	{// 3.14f���傫���Ȃ����Ƃ��l��-3.14f�ɂ���
		g_Player.rotDest.y -= D3DX_PI * 2.0f;
	}
	// �����̍X�V
	g_Player.rot.y += (g_Player.rotDest.y - g_Player.rot.y) * 0.08f;

	if (g_Player.rot.y < -D3DX_PI)
	{// -3.14f��菬�����Ȃ����Ƃ��l��3.14f�ɂ���
		g_Player.rot.y += D3DX_PI * 2.0f;
	}
	else if (g_Player.rot.y > D3DX_PI)
	{// 3.14f���傫���Ȃ����Ƃ��l��-3.14f�ɂ���
		g_Player.rot.y -= D3DX_PI * 2.0f;
	}

	D3DXVECTOR3 vector = enemy->pos - g_Player.pos;
	float fAngle = atan2f(vector.x, vector.z);

	if(g_Player.skill == SKILL_MAGICBALL)
	{
		g_Player.rotDest.y = D3DX_PI + fAngle;
	}

	//�ړ�
	if (pXinput->bPressLStick == true)
	{	//���X�e�B�b�N���X���������Ɉړ�
		g_Player.pos.x -= sinf(camera->rot.y - pXinput->fAngleL) * PMOVE_SPEED;
		g_Player.pos.z -= cosf(camera->rot.y - pXinput->fAngleL) * PMOVE_SPEED;
		g_Player.rotDest.y = camera->rot.y - pXinput->fAngleL;
		g_Player.bMove = true;

		if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION)
		{	//�W�����v�ȊO
			g_Player.nowMotion = MOTION_MOVE;
		}
	}

	if (GetKeyboardPress(DIK_W) == TRUE)
	{
		if (GetKeyboardPress(DIK_A) == TRUE)
		{	//���O
			g_Player.pos.x += sinf(camera->rot.y + D3DXToRadian(-45)) * PMOVE_SPEED;
			g_Player.pos.z += cosf(camera->rot.y + D3DXToRadian(-45)) * PMOVE_SPEED;
			g_Player.rotDest.y = (D3DXToRadian(135) + camera->rot.y);
			g_Player.bMove = true;

			if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION)
			{
				g_Player.nowMotion = MOTION_MOVE;
			}
		}
		else if (GetKeyboardPress(DIK_D) == TRUE)
		{	//�E�O
			g_Player.pos.x += sinf(camera->rot.y + D3DXToRadian(45)) * PMOVE_SPEED;
			g_Player.pos.z += cosf(camera->rot.y + D3DXToRadian(45)) * PMOVE_SPEED;
			g_Player.rotDest.y = (D3DXToRadian(-135) + camera->rot.y);
			g_Player.bMove = true;

			if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION)
			{
				g_Player.nowMotion = MOTION_MOVE;
			}
		}
		else
		{	//�O
			g_Player.pos.x += sinf(camera->rot.y) * PMOVE_SPEED;
			g_Player.pos.z += cosf(camera->rot.y) * PMOVE_SPEED;
			g_Player.rotDest.y = (D3DX_PI + camera->rot.y);
			g_Player.bMove = true;

			if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION)
			{
				g_Player.nowMotion = MOTION_MOVE;
			}
		}
	}
	else if (GetKeyboardPress(DIK_S) == TRUE)
	{
		if (GetKeyboardPress(DIK_A) == TRUE)
		{	//�����
			g_Player.pos.x -= sinf(camera->rot.y + D3DXToRadian(45)) * PMOVE_SPEED;
			g_Player.pos.z -= cosf(camera->rot.y + D3DXToRadian(45)) * PMOVE_SPEED;
			g_Player.rotDest.y = (D3DXToRadian(45) + camera->rot.y);
			g_Player.bMove = true;

			if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION)
			{
				g_Player.nowMotion = MOTION_MOVE;
			}
		}
		else if (GetKeyboardPress(DIK_D) == TRUE)
		{	//�E���
			g_Player.pos.x -= sinf(camera->rot.y + D3DXToRadian(-45)) * PMOVE_SPEED;
			g_Player.pos.z -= cosf(camera->rot.y + D3DXToRadian(-45)) * PMOVE_SPEED;
			g_Player.rotDest.y = (D3DXToRadian(-45) + camera->rot.y);
			g_Player.bMove = true;

			if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION)
			{
				g_Player.nowMotion = MOTION_MOVE;
			}
		}
		else
		{	//���
			g_Player.pos.x -= sinf(camera->rot.y) * PMOVE_SPEED;
			g_Player.pos.z -= cosf(camera->rot.y) * PMOVE_SPEED;
			g_Player.rotDest.y = (0.0f + camera->rot.y);
			g_Player.bMove = true;

			if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION)
			{
				g_Player.nowMotion = MOTION_MOVE;
			}
		}
	}
	else if (GetKeyboardPress(DIK_A) == TRUE)
	{	//��
		g_Player.pos.x -= sinf(camera->rot.y + D3DXToRadian(90)) * PMOVE_SPEED;
		g_Player.pos.z += cosf(camera->rot.y - D3DXToRadian(90)) * PMOVE_SPEED;
		g_Player.rotDest.y = (camera->rot.y + (D3DX_PI / 2));
		g_Player.bMove = true;

		if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION)
		{
			g_Player.nowMotion = MOTION_MOVE;
		}

	}
	else if (GetKeyboardPress(DIK_D) == TRUE)
	{	//�E
		g_Player.pos.x += sinf(camera->rot.y + D3DXToRadian(90)) * PMOVE_SPEED;
		g_Player.pos.z -= cosf(camera->rot.y - D3DXToRadian(90)) * PMOVE_SPEED;
		g_Player.rotDest.y = (camera->rot.y + (-D3DX_PI / 2));
		g_Player.bMove = true;

		if (g_Player.nowMotion != MOTION_JUMP && g_Player.nowMotion != MOTION_ACTION
			)
		{
			g_Player.nowMotion = MOTION_MOVE;
		}
	}

	//�ړ��͈͂̐���
	for (int nCnt = 0; nCnt < MAX_INVI; nCnt++)
	{
		if (nCnt != MAX_INVI - 1)
		{
			fGaiseki[nCnt * 2] = ((aPos[nCnt + 1].z - aPos[nCnt].z) * (g_Player.pos.x - aPos[nCnt].x)) - ((aPos[nCnt + 1].x - aPos[nCnt].x) * (g_Player.pos.z - aPos[nCnt].z));
			fGaiseki[nCnt * 2 + 1] = ((aPos[nCnt + 1].z - aPos[nCnt].z) * (g_Player.posOld.x - aPos[nCnt].x)) - ((aPos[nCnt + 1].x - aPos[nCnt].x) * (g_Player.posOld.z - aPos[nCnt].z));

			if (fGaiseki[nCnt * 2] >= 0)
			{
				if (fGaiseki[nCnt * 2 + 1] <= 0)
				{
					g_Player.pos = g_Player.posOld;
				}
			}
		}
		else
		{
			fGaiseki[nCnt * 2] = ((aPos[0].z - aPos[nCnt].z) * (g_Player.pos.x - aPos[nCnt].x)) - ((aPos[0].x - aPos[nCnt].x) * (g_Player.pos.z - aPos[nCnt].z));
			fGaiseki[nCnt * 2 + 1] = ((aPos[0].z - aPos[nCnt].z) * (g_Player.posOld.x - aPos[nCnt].x)) - ((aPos[0].x - aPos[nCnt].x) * (g_Player.posOld.z - aPos[nCnt].z));

			if (fGaiseki[nCnt * 2] >= 0)
			{
				if (fGaiseki[nCnt * 2 + 1] <= 0)
				{
					g_Player.pos = g_Player.posOld;
				}
			}
		}
	}

	//�W�����v
	if (g_Player.bJump == true)
	{
		if (pXinput->bPressA == true || GetKeyboardTrigger(DIK_SPACE) == true)
		{
			g_Player.fGravity += 20.0f;
			g_Player.bJump = false;
			g_Player.bMove = true;
			if (g_Player.nowMotion != MOTION_ACTION)
			{
				g_Player.nowMotion = MOTION_JUMP;
			}
		}
	}

	//�d�͉��Z
	g_Player.fGravity -= 1.0f;
	g_Player.pos.y += g_Player.fGravity;

	//�����߂�
	if (g_Player.pos.y < 0)
	{
		g_Player.fGravity = 0.0f;
		g_Player.bJump = true;
		g_Player.pos.y = g_Player.posOld.y;
	}
	if (CollisionObject(g_Player.pos, g_Player.posOld) == true)
	{
		g_Player.fGravity = 0.0f;
		g_Player.bJump = true;
		g_Player.pos.y = g_Player.posOld.y;
	}
}

////////////////////////////////////////////////////////////////////////////////
//���[�V�����̐؂�ւ�
////////////////////////////////////////////////////////////////////////////////
void MotionPlayer(void)
{
	switch(g_Player.nowMotion)
	{
	case MOTION_NEUTRAL:	//�j���[�g����
		MotionPlayerNeutral();
		break;
	case MOTION_MOVE:		//�ړ�
		MotionPlayerMove();
		break;
	case MOTION_JUMP:		//�W�����v
		MotionPlayerJump();
		break;
	case MOTION_ACTION:		//�A�N�V����
		MotionPlayerAction();
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////
//�j���[�g�������[�V����
////////////////////////////////////////////////////////////////////////////////
void MotionPlayerNeutral(void)
{
	static int nNextKey = 0;
	D3DXVECTOR3 diff[MAX_MODEL_PLAYER];
	D3DXVECTOR3 next[NEUT_KEY][MAX_MODEL_PLAYER];
	static int nFrame = 40;
	
	if (g_Player.bChant == false)
	{
		//�L�[1
		next[0][0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		next[0][1] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);
		next[0][2] = D3DXVECTOR3(0.03f, 0.0f, 0.5f);
		next[0][3] = D3DXVECTOR3(0.03f, 0.0f, -0.5f);
		next[0][4] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);
		next[0][5] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);

		//�L�[2
		next[1][0] = D3DXVECTOR3(-0.03f, 0.0f, 0.0f);
		next[1][1] = D3DXVECTOR3(-0.06f, 0.0f, 0.0f);
		next[1][2] = D3DXVECTOR3(0.03f, 0.0f, 0.79f);
		next[1][3] = D3DXVECTOR3(0.03f, 0.0f, -0.79f);
		next[1][4] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);
		next[1][5] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);
	}
	else if (g_Player.bChant == true)
	{
		//�L�[1
		next[0][0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		next[0][1] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);
		next[0][2] = D3DXVECTOR3(0.03f, -1.5f, 0.5f);
		next[0][3] = D3DXVECTOR3(0.03f, 0.0f, -0.5f);
		next[0][4] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);
		next[0][5] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);

		//�L�[2
		next[1][0] = D3DXVECTOR3(-0.03f, 0.0f, 0.0f);
		next[1][1] = D3DXVECTOR3(-0.06f, 0.0f, 0.0f);
		next[1][2] = D3DXVECTOR3(0.03f, -1.5f, 0.5f);
		next[1][3] = D3DXVECTOR3(0.03f, 0.0f, -0.79f);
		next[1][4] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);
		next[1][5] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);
	}
	
	for (int nCntNeut = 0; nCntNeut < MAX_MODEL_PLAYER; nCntNeut++)
	{
		diff[nCntNeut] = next[nNextKey][nCntNeut] - g_Player.aModel[nCntNeut].rot;
		g_Player.aModel[nCntNeut].rot += (diff[nCntNeut] / (float)nFrame);
	}
	nFrame--;

	if(nFrame == 0)
	{
		if (nNextKey == NEUT_KEY - 1)
		{
			nNextKey = 0;
		}
		else
		{
			nNextKey++;
		}
		nFrame = 40;
	}
}

////////////////////////////////////////////////////////////////////////////////
//�ړ����[�V����
////////////////////////////////////////////////////////////////////////////////
void MotionPlayerMove(void)
{
	static int nNextKey = 0;
	D3DXVECTOR3 diff[MAX_MODEL_PLAYER];
	D3DXVECTOR3 next[MOVE_KEY][MAX_MODEL_PLAYER];
	static int nFrame = 15;

	//�L�[1
	next[0][0] = D3DXVECTOR3(-0.3f, -0.16f, 0.0f);
	next[0][1] = D3DXVECTOR3(0.22f, 0.09f, 0.0f);
	next[0][2] = D3DXVECTOR3(2.1f, 0.0f, 1.31f);
	next[0][3] = D3DXVECTOR3(-1.07f, 0.0f, -1.32f);
	next[0][4] = D3DXVECTOR3(-2.02f, 0.0f, 0.1f);
	next[0][5] = D3DXVECTOR3(1.5f, 0.0f, -0.1f);

	//�L�[2
	next[1][0] = D3DXVECTOR3(-0.4f, 0.0f, 0.0f);
	next[1][1] = D3DXVECTOR3(0.31f, 0.0f, 0.0f);
	next[1][2] = D3DXVECTOR3(2.01f, 0.0f, 1.32f);
	next[1][3] = D3DXVECTOR3(-0.75f, 0.0f, -1.32f);
	next[1][4] = D3DXVECTOR3(-1.33f, 0.0f, 0.1f);
	next[1][5] = D3DXVECTOR3(0.83f, 0.0f, -0.1f);

	//�L�[3
	next[2][0] = D3DXVECTOR3(-0.3f, 0.15f, 0.0f);
	next[2][1] = D3DXVECTOR3(0.22f, -0.1f, 0.0f);
	next[2][2] = D3DXVECTOR3(-1.07f, 0.0f, 1.32f);
	next[2][3] = D3DXVECTOR3(2.1f, 0.0f, -1.32f);
	next[2][4] = D3DXVECTOR3(2.23f, 0.0f, 0.1f);
	next[2][5] = D3DXVECTOR3(-1.5f, 0.0f, -0.1f);

	//�L�[4
	next[3][0] = D3DXVECTOR3(-0.4f, 0.0f, 0.0f);
	next[3][1] = D3DXVECTOR3(0.31f, 0.0f, 0.0f);
	next[3][2] = D3DXVECTOR3(-0.75f, 0.0f, 1.32f);
	next[3][3] = D3DXVECTOR3(2.01f, 0.0f, -1.32f);
	next[3][4] = D3DXVECTOR3(1.33f, 0.0f, 0.1f);
	next[3][5] = D3DXVECTOR3(-0.83f, 0.0f, -0.1f);

	for (int nCntNeut = 0; nCntNeut < MAX_MODEL_PLAYER; nCntNeut++)
	{
		diff[nCntNeut] = next[nNextKey][nCntNeut] - g_Player.aModel[nCntNeut].rot;
		g_Player.aModel[nCntNeut].rot += (diff[nCntNeut] / (float)nFrame);
	}
	nFrame--;

	if (nFrame == 0)
	{
		if (nNextKey == MOVE_KEY - 1)
		{
			nNextKey = 0;
		}
		else
		{
			nNextKey++;
		}
		nFrame = 8;
	}
}

////////////////////////////////////////////////////////////////////////////////
//�W�����v���[�V����
////////////////////////////////////////////////////////////////////////////////
void MotionPlayerJump(void)
{
	static int nNextKey = 0;
	D3DXVECTOR3 diff[MAX_MODEL_PLAYER];
	D3DXVECTOR3 next[JUMP_KEY][MAX_MODEL_PLAYER];
	static int nFrame = 5;

	//�L�[1
	next[0][0] = D3DXVECTOR3(-0.03f, 0.0f, 0.0f);
	next[0][1] = D3DXVECTOR3(0.03f, 0.0f, 0.0f);
	next[0][2] = D3DXVECTOR3(0.0f, -0.25f, 0.82f);
	next[0][3] = D3DXVECTOR3(0.0f, 0.25f, -0.82f);
	next[0][4] = D3DXVECTOR3(0.13f, 0.0f, 0.0f);
	next[0][5] = D3DXVECTOR3(0.13f, 0.0f, 0.0f);

	//�L�[2
	next[1][0] = D3DXVECTOR3(0.06f, -0.06f, 0.0f);
	next[1][1] = D3DXVECTOR3(-0.06f, 0.06f, 0.0f);
	next[1][2] = D3DXVECTOR3(0.0f, -1.41f, -0.44f);
	next[1][3] = D3DXVECTOR3(-1.16f, 0.0f, -1.41f);
	next[1][4] = D3DXVECTOR3(-1.19f, 0.0f, 0.0f);
	next[1][5] = D3DXVECTOR3(1.1f, 0.0f, 0.0f);

	//�L�[3
	next[2][0] = D3DXVECTOR3(0.06f, -0.06f, 0.0f);
	next[2][1] = D3DXVECTOR3(-0.06f, 0.06f, 0.0f);
	next[2][2] = D3DXVECTOR3(0.0f, -1.41f, -0.64f);
	next[2][3] = D3DXVECTOR3(-1.36f, 0.0f, -1.41f);
	next[2][4] = D3DXVECTOR3(-1.19f, 0.0f, 0.0f);
	next[2][5] = D3DXVECTOR3(1.1f, 0.0f, 0.0f);

	//�L�[4
	next[3][0] = D3DXVECTOR3(0.06f, -0.06f, 0.0f);
	next[3][1] = D3DXVECTOR3(-0.06f, 0.06f, 0.0f);
	next[3][2] = D3DXVECTOR3(0.0f, -1.41f, -0.64f);
	next[3][3] = D3DXVECTOR3(-1.36f, 0.0f, -1.41f);
	next[3][4] = D3DXVECTOR3(-1.19f, 0.0f, 0.0f);
	next[3][5] = D3DXVECTOR3(1.1f, 0.0f, 0.0f);

	//�L�[5
	next[4][0] = D3DXVECTOR3(0.06f, -0.06f, 0.0f);
	next[4][1] = D3DXVECTOR3(-0.06f, 0.06f, 0.0f);
	next[4][2] = D3DXVECTOR3(0.0f, -1.41f, -0.64f);
	next[4][3] = D3DXVECTOR3(-1.36f, 0.0f, -1.41f);
	next[4][4] = D3DXVECTOR3(-1.19f, 0.0f, 0.0f);
	next[4][5] = D3DXVECTOR3(1.1f, 0.0f, 0.0f);

	for (int nCntNeut = 0; nCntNeut < MAX_MODEL_PLAYER; nCntNeut++)
	{
		diff[nCntNeut] = next[nNextKey][nCntNeut] - g_Player.aModel[nCntNeut].rot;
		g_Player.aModel[nCntNeut].rot += (diff[nCntNeut] / (float)nFrame);
	}
	nFrame--;

	if (nFrame == 0)
	{
		if (nNextKey == JUMP_KEY - 1)
		{
			g_Player.nowMotion = MOTION_NEUTRAL;
			nNextKey = 0;
		}
		else
		{
			nNextKey++;
		}
		nFrame = 5;
	}
}

////////////////////////////////////////////////////////////////////////////////
//�A�N�V�������[�V����
////////////////////////////////////////////////////////////////////////////////
void MotionPlayerAction(void)
{
	static int nowKey;
	static int nNextKey = 0;
	D3DXVECTOR3 diff[MAX_MODEL_PLAYER];
	D3DXVECTOR3 next[ACTION_KEY][MAX_MODEL_PLAYER];
	static int nFrame = 12;

	//�L�[1
	next[0][0] = D3DXVECTOR3(0.0f, 0.31f, 0.0f);
	next[0][1] = D3DXVECTOR3(0.0f, -0.31f, 0.0f);
	next[0][2] = D3DXVECTOR3(0.0f, 0.0f, 1.04f);
	next[0][3] = D3DXVECTOR3(0.0f, 0.0f, -0.66f);
	next[0][4] = D3DXVECTOR3(-0.38f, -0.16f, 0.0f);
	next[0][5] = D3DXVECTOR3(-0.16f, 0.0f, 0.0f);

	//�L�[2
	next[1][0] = D3DXVECTOR3(0.0f, -0.41f, 0.0f);
	next[1][1] = D3DXVECTOR3(0.0f, 0.22f, 0.0f);
	next[1][2] = D3DXVECTOR3(0.0f, -1.36f, 0.0f);
	next[1][3] = D3DXVECTOR3(0.0f, 0.0f, -1.1f);
	next[1][4] = D3DXVECTOR3(-0.75f, 0.22f, 0.0f);
	next[1][5] = D3DXVECTOR3(0.75f, 0.22f, 0.0f);
	
	//�L�[3
	next[2][0] = D3DXVECTOR3(0.0f, -0.41f, 0.0f);
	next[2][1] = D3DXVECTOR3(0.0f, 0.22f, 0.0f);
	next[2][2] = D3DXVECTOR3(0.0f, -1.36f, 0.0f);
	next[2][3] = D3DXVECTOR3(0.0f, 0.0f, -1.1f);
	next[2][4] = D3DXVECTOR3(-0.75f, 0.22f, 0.0f);
	next[2][5] = D3DXVECTOR3(0.75f, 0.22f, 0.0f);
	
	for (int nCntNeut = 0; nCntNeut < MAX_MODEL_PLAYER; nCntNeut++)
	{
		diff[nCntNeut] = next[nNextKey][nCntNeut] - g_Player.aModel[nCntNeut].rot;
		g_Player.aModel[nCntNeut].rot += (diff[nCntNeut] / (float)nFrame);
	}
	nFrame--;

	if (nFrame == 0)
	{
		if (nNextKey == ACTION_KEY - 1)
		{
			g_Player.nowMotion = MOTION_NEUTRAL;
			nNextKey = 0;
		}
		else
		{
			nNextKey++;
		}
		nFrame = 12;
	}
}

////////////////////////////////////////////////////////////////////////////////
//�v���C���[�̈ʒu���擾
////////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3 *GetPosPlayer(void)
{
	return &g_Player.pos;
}

////////////////////////////////////////////////////////////////////////////////
//�v���C���[�̉ߋ��̈ʒu���擾
////////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3 *GetPosOld(void)
{
	return &g_Player.posOld;
}

////////////////////////////////////////////////////////////////////////////////
//�v���C���[�̌������擾
////////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3 *GetRotPlayer(void)
{
	return &g_Player.rot;
}

////////////////////////////////////////////////////////////////////////////////
//�v���C���[���擾
////////////////////////////////////////////////////////////////////////////////
PLAYER *GetPlayer(void)
{
	return &g_Player;
}

////////////////////////////////////////////////////////////////////////////////
//�O��
////////////////////////////////////////////////////////////////////////////////
float *GetGaiseki(void)
{
	return &fGaiseki[0];
}

////////////////////////////////////////////////////////////////////////////////
//�����_���Ȑ��l���擾
////////////////////////////////////////////////////////////////////////////////
int GetRandom(int min, int max)
{
	static int nNum;

	if (nNum == 0)
	{
		srand((unsigned int)time(NULL));
		nNum = 1;
	}

	return min + (rand() * (max - min + 1) / (1 + RAND_MAX));
}