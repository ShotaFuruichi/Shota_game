////////////////////////////////////////////////////////////////////////////////
//
//Contents	: �G�̏��� [enemy.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/02/15
//
////////////////////////////////////////////////////////////////////////////////
#include "enemy.h"
#include "EnemyAttack.h"
#include "fade.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
ENEMY g_Enemy;	//�G	

////////////////////////////////////////////////////////////////////////////////
//����������
////////////////////////////////////////////////////////////////////////////////
void InitEnemy(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/model/enemy_body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Enemy.aModel[0].pBufferMat, NULL, &g_Enemy.aModel[0].nNumMat, &g_Enemy.aModel[0].pMesh);
	D3DXLoadMeshFromX("data/model/enemy_head.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Enemy.aModel[1].pBufferMat, NULL, &g_Enemy.aModel[1].nNumMat, &g_Enemy.aModel[1].pMesh);
	D3DXLoadMeshFromX("data/model/enemy_armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Enemy.aModel[2].pBufferMat, NULL, &g_Enemy.aModel[2].nNumMat, &g_Enemy.aModel[2].pMesh);
	D3DXLoadMeshFromX("data/model/enemy_handR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Enemy.aModel[3].pBufferMat, NULL, &g_Enemy.aModel[3].nNumMat, &g_Enemy.aModel[3].pMesh);
	D3DXLoadMeshFromX("data/model/enemy_armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Enemy.aModel[4].pBufferMat, NULL, &g_Enemy.aModel[4].nNumMat, &g_Enemy.aModel[4].pMesh);
	D3DXLoadMeshFromX("data/model/enemy_handL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Enemy.aModel[5].pBufferMat, NULL, &g_Enemy.aModel[5].nNumMat, &g_Enemy.aModel[5].pMesh);

	g_Enemy.nNumModel = MAX_MODEL_ENEMY;

	//�e�p�[�c�̊K�w�\���ݒ�
	g_Enemy.aModel[0].nIdxModelParent = -1;									//�e���f���̃C���f�b�N�X��ݒ�
	g_Enemy.aModel[0].pos = D3DXVECTOR3(0.0f, 0.0f, .0f);					//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Enemy.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�����̏����ݒ�
	g_Enemy.aModel[1].nIdxModelParent = 0;									//�e���f���̃C���f�b�N�X��ݒ�
	g_Enemy.aModel[1].pos = D3DXVECTOR3(0.0f, 275.0f, 0.0f);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Enemy.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�����̏����ݒ�
	g_Enemy.aModel[2].nIdxModelParent = 0;									//�e���f���̃C���f�b�N�X��ݒ�
	g_Enemy.aModel[2].pos = D3DXVECTOR3(-75.0f, 200.0f, 0.0f);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Enemy.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 45.0f);					//�����̏����ݒ�
	g_Enemy.aModel[3].nIdxModelParent = 2;									//�e���f���̃C���f�b�N�X��ݒ�
	g_Enemy.aModel[3].pos = D3DXVECTOR3(-150.0f, 0.0f, 0.0f);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Enemy.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�����̏����ݒ�
	g_Enemy.aModel[4].nIdxModelParent = 0;									//�e���f���̃C���f�b�N�X��ݒ�
	g_Enemy.aModel[4].pos = D3DXVECTOR3(75.0f, 200.0f, 0.0f);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Enemy.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, -45.0f);				//�����̏����ݒ�
	g_Enemy.aModel[5].nIdxModelParent = 4;									//�e���f���̃C���f�b�N�X��ݒ�
	g_Enemy.aModel[5].pos = D3DXVECTOR3(150.0f, 0.0f, 0.0f);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�
	g_Enemy.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�����̏����ݒ�
	
	g_Enemy.pos = D3DXVECTOR3(ENEMY_APPEARX, ENEMY_APPEARY, ENEMY_APPEARZ);	//�v���C���[�̈ʒu�̏����ݒ�
	g_Enemy.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//�v���C���[�̑O��X�V���̈ʒu�̏����ݒ�
	g_Enemy.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							//�v���C���[�̌����̏����ݒ�
	g_Enemy.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//�v���C���[�̖ڕW�̌����̏����ݒ�
	g_Enemy.nowMotion = MOTION_NEUTRAL;										//���݂̃��[�V����
	g_Enemy.nLife = LIFE_ENEMY;												//�G�̗̑�
}

////////////////////////////////////////////////////////////////////////////////
//�I������
////////////////////////////////////////////////////////////////////////////////
void UninitEnemy(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL_ENEMY; nCntModel++)
	{
		if (g_Enemy.aModel[nCntModel].pMesh != NULL)
		{
			g_Enemy.aModel[nCntModel].pMesh->Release();	//�j��
			g_Enemy.aModel[nCntModel].pMesh = NULL;		//������
		}

		if (g_Enemy.aModel[nCntModel].pBufferMat != NULL)
		{
			g_Enemy.aModel[nCntModel].pBufferMat->Release();	//�j��
			g_Enemy.aModel[nCntModel].pBufferMat = NULL;		//������
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateEnemy(void)
{
	if (g_Enemy.nowMotion != MOTION_JUMP && g_Enemy.nowMotion != MOTION_ACTION)
	{
		g_Enemy.nowMotion = MOTION_NEUTRAL;
	}

	if (g_Enemy.nLife <= 0)
	{
		SetFade(FADE_OUT, MODE_RESULT);
	}
	
	AttackEnemy();

	g_Enemy.aModel[1].rot.x -= 0.01f;
	g_Enemy.aModel[1].rot.y -= 0.01f;
	g_Enemy.aModel[1].rot.z -= 0.01f;

	//MotionEnemy();
}

////////////////////////////////////////////////////////////////////////////////
//�`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

												//�v���C���[�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Enemy.mtxWorld);

	//�v���C���[�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy.rot.y, g_Enemy.rot.x, g_Enemy.rot.z);
	D3DXMatrixMultiply(&g_Enemy.mtxWorld, &g_Enemy.mtxWorld, &mtxRot);

	//�v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Enemy.pos.x, g_Enemy.pos.y, g_Enemy.pos.z);
	D3DXMatrixMultiply(&g_Enemy.mtxWorld, &g_Enemy.mtxWorld, &mtxTrans);

	//�v���C���[�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Enemy.mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_Enemy.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	//�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;					//�e�̃}�g���b�N�X

												//�e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Enemy.aModel[nCntModel].mtxWorld);

		//�e�p�[�c�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy.aModel[nCntModel].rot.y, g_Enemy.aModel[nCntModel].rot.x, g_Enemy.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Enemy.aModel[nCntModel].mtxWorld, &g_Enemy.aModel[nCntModel].mtxWorld, &mtxRot);

		//�e�p�[�c�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Enemy.aModel[nCntModel].pos.x, g_Enemy.aModel[nCntModel].pos.y, g_Enemy.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Enemy.aModel[nCntModel].mtxWorld, &g_Enemy.aModel[nCntModel].mtxWorld, &mtxTrans);

		//�e�p�[�c�̐e�̃}�g���b�N�X��ݒ�
		if (g_Enemy.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_Enemy.aModel[g_Enemy.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_Enemy.mtxWorld;	//�v���C���[�̃}�g���b�N�X��ݒ�
		}

		//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_Enemy.aModel[nCntModel].mtxWorld, &g_Enemy.aModel[nCntModel].mtxWorld, &mtxParent);

		//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Enemy.aModel[nCntModel].mtxWorld);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL *)g_Enemy.aModel[nCntModel].pBufferMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Enemy.aModel[nCntModel].nNumMat; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//���f��(�p�[�c)�̕`��
			g_Enemy.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

////////////////////////////////////////////////////////////////////////////////
//�G�̍U��
////////////////////////////////////////////////////////////////////////////////
void AttackEnemy(void)
{
	g_Enemy.AttackCounter++;
	if (g_Enemy.AttackCounter % ATTACK_INTERVAL == 0)
	{
		for (int nAttack = 0; nAttack < 4; nAttack++)
		{
			SetEnemyAttack();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//�G�̏����擾
////////////////////////////////////////////////////////////////////////////////
ENEMY *GetEnemy(void)
{
	return &g_Enemy;
}