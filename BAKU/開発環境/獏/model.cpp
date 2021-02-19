////////////////////////////////////////////////////////////////////////////////
//
//Contents	: ���f���̏��� [model.cpp]
//Author	: ShotaFuruichi
//Since		: 2020/11/16
//
////////////////////////////////////////////////////////////////////////////////
#include "model.h"
#include "input.h"
#include "camera.h"
#include "bullet.h"

////////////////////////////////////////////////////////////////////////////////
//�}�N����`
////////////////////////////////////////////////////////////////////////////////
#define MOVE_SPEED (1.0f)

////////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
////////////////////////////////////////////////////////////////////////////////
LPD3DXMESH  g_pMeshModel = NULL;		//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL;	//�}�e���A��(�ގ����)�ւ̃|�C���^
DWORD g_nNumMatModel;					//�}�e���A���̐�
D3DXVECTOR3 g_posModel;					//�ʒu
D3DXVECTOR3 g_rotModel;					//����
D3DXMATRIX g_mtxWorldModel;				//���[���h�}�g���b�N�X

////////////////////////////////////////////////////////////////////////////////
//���f���̏���������
////////////////////////////////////////////////////////////////////////////////
void InitModel(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/model/3Dgame_head.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatModel, NULL, &g_nNumMatModel, &g_pMeshModel);

	g_posModel = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

////////////////////////////////////////////////////////////////////////////////
//���f���̏I������
////////////////////////////////////////////////////////////////////////////////
void UninitModel(void)
{
	//���b�V���̔j��
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();	//�j��
		g_pMeshModel = NULL;		//������
	}

	//�}�e���A���̊J��
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();	//�J��
		g_pBuffMatModel = NULL;		//������
	}
}

////////////////////////////////////////////////////////////////////////////////
//���f���̍X�V����
////////////////////////////////////////////////////////////////////////////////
void UpdateModel(void)
{
	CAMERA *camera = GetCamera();

	#if 0
	//��]
	if (GetKeyboardPress(DIK_M) == TRUE)
	{
		g_rotModel.y += 0.025f;
	}
	if (GetKeyboardPress(DIK_N) == TRUE)
	{
		g_rotModel.y -= 0.025f;
	}

	if (g_rotModel.x < D3DXToRadian(90) && GetKeyboardPress(DIK_B) == TRUE)
	{
		g_rotModel.x += 0.025f;
	}
	if (g_rotModel.x > -D3DXToRadian(90) && GetKeyboardPress(DIK_V) == TRUE)
	{
		g_rotModel.x -= 0.025f;
	}
	#endif

#if 1
	//�ړ�
	if (GetKeyboardPress(DIK_W) == TRUE)
	{
		g_posModel.x += sinf(camera->rot.y) * MOVE_SPEED;
		g_posModel.z += cosf(camera->rot.y) * MOVE_SPEED;
		if (g_rotModel.y <= camera->rot.y + (D3DX_PI - camera->rot.y) && g_rotModel.y >= 0)
		{
			g_rotModel.y = g_rotModel.y += ((camera->rot.y + D3DX_PI) - g_rotModel.y) * 0.1f;
		}
		else if (g_rotModel.y >= camera->rot.y - (D3DX_PI + camera->rot.y) && g_rotModel.y <= 0)
		{
			g_rotModel.y = g_rotModel.y += ((camera->rot.y - D3DX_PI) - g_rotModel.y) * 0.1f;
		}
	}
	if (GetKeyboardPress(DIK_S) == TRUE)
	{
		g_posModel.x -= sinf(camera->rot.y) * MOVE_SPEED;
		g_posModel.z -= cosf(camera->rot.y) * MOVE_SPEED;
		if (g_rotModel.y > camera->rot.y)
		{
			g_rotModel.y = g_rotModel.y += (camera->rot.y - g_rotModel.y) * 0.1f;
		}
		else if (g_rotModel.y <= camera->rot.y)
		{
			g_rotModel.y = g_rotModel.y += (camera->rot.y - g_rotModel.y) * 0.1f;
		}
	}
	if (GetKeyboardPress(DIK_A) == TRUE)
	{
		g_posModel.x -= sinf(camera->rot.y + D3DXToRadian(90)) * MOVE_SPEED;
		g_posModel.z += cosf(camera->rot.y - D3DXToRadian(90)) * MOVE_SPEED;
		if (g_rotModel.y <= camera->rot.y + ((D3DX_PI / 2) + camera->rot.y) && g_rotModel.y >= ((-D3DX_PI / 2) - camera->rot.y))
		{
			g_rotModel.y = g_rotModel.y += ((camera->rot.y + (D3DX_PI / 2)) - g_rotModel.y) * 0.1f;
		}
		else if (g_rotModel.y >= camera->rot.y + ((D3DX_PI / 2) + camera->rot.y) && g_rotModel.y <= ((-D3DX_PI / 2) + camera->rot.y))
		{
			g_rotModel.y = g_rotModel.y += ((camera->rot.y + (D3DX_PI / 2)) - g_rotModel.y) * 0.1f;
		}
	}
	if (GetKeyboardPress(DIK_D) == TRUE)
	{
		g_posModel.x += sinf(camera->rot.y + D3DXToRadian(90)) * MOVE_SPEED;
		g_posModel.z -= cosf(camera->rot.y - D3DXToRadian(90)) * MOVE_SPEED;
		g_rotModel.y = camera->rot.y - D3DXToRadian(90);
	}
	if (GetKeyboardPress(DIK_O) == TRUE)
	{
		g_posModel.y += MOVE_SPEED;
	}
	if (GetKeyboardPress(DIK_L) == TRUE)
	{
		g_posModel.y -= MOVE_SPEED;
	}
#endif

	if (g_rotModel.y < -D3DX_PI)
	{
		g_rotModel.y += D3DX_PI * 2.0f;
	}
	else if (g_rotModel.y > D3DX_PI)
	{
		g_rotModel.y -= D3DX_PI * 2.0f;
	}
}

////////////////////////////////////////////////////////////////////////////////
//���f���̕`�揈��
////////////////////////////////////////////////////////////////////////////////
void DrawModel(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	//���݂̃}�e���A���̎擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL *)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//���f��(�p�[�c)�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//////////////////////////////////////////////////////////////////////////////////
////���f���̎ˌ�����
//////////////////////////////////////////////////////////////////////////////////
//void ShotModel(void)
//{
//	if (GetKeyboardTrigger(DIK_RETURN) == TRUE)
//	{
//		SetBullet(g_posModel, D3DXVECTOR3(sinf(g_rotModel.y) * -5.0f, 0.0f, cosf(g_rotModel.y) * -5.0f), 40);
//	}
//}

////////////////////////////////////////////////////////////////////////////////
//���f���̈ʒu���擾
////////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3 *GetPosModel(void)
{
	return &g_posModel;
}

////////////////////////////////////////////////////////////////////////////////
//���f���̈ʒu���擾
////////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3 *GetRotModel(void)
{
	return &g_rotModel;
}