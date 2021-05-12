#include "Cannon.h"
#include "Bomb.h"
#include "timer.h"
D3DXMATERIAL *pMaterials_Cannon;
CANNON aCannon[CANNON_NUM];
int g_nCntTimeCannon;
void InitCannon()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_nCntTimeCannon = 0;
	aCannon[0].pos = D3DXVECTOR3(CANNON_POS_X, CANNON_POS_Y, 0);
	aCannon[0].rot = D3DXVECTOR3(INIT_ROT_ANGLE_X, INIT_ROT_ANGLE_Y, 0);
	aCannon[1].pos = D3DXVECTOR3(-CANNON_POS_X, CANNON_POS_Y, 0);
	aCannon[1].rot = D3DXVECTOR3(INIT_ROT_ANGLE_X, -INIT_ROT_ANGLE_Y, 0);

	for (int nCnt = 0; nCnt < CANNON_NUM; nCnt++)
	{
		aCannon[nCnt].Xfile_MaterialNum = NULL;
		aCannon[nCnt].Xfile_Materials = NULL;
		aCannon[nCnt].Xfile_Mesh = NULL;
		aCannon[nCnt].fRotSpeed = ROT_SPEED;
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data/MODEL/Cannon.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&aCannon[nCnt].Xfile_Materials,
			NULL,
			&aCannon[nCnt].Xfile_MaterialNum,
			&aCannon[nCnt].Xfile_Mesh);

		//Texture�̐ݒ�
		pMaterials_Cannon = (D3DXMATERIAL*)aCannon[nCnt].Xfile_Materials->GetBufferPointer();
		for (DWORD nCntMaterial = 0; nCntMaterial < aCannon[nCnt].Xfile_MaterialNum; nCntMaterial++)
		{
			if (pMaterials_Cannon[nCnt].pTextureFilename != NULL)
			{
				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMaterials_Cannon[nCnt].pTextureFilename,
					&aCannon[nCnt].Xfile_Textures[nCntMaterial]);
			}
			else aCannon[nCnt].Xfile_Textures[nCntMaterial] = nullptr;
		}
	}
}

void UninitCannon()
{
	for (int nCnt = 0; nCnt < CANNON_NUM; nCnt++)
	{
		// mesh->release
		if (aCannon[nCnt].Xfile_Mesh != NULL)
		{
			aCannon[nCnt].Xfile_Mesh->Release();
			aCannon[nCnt].Xfile_Mesh = NULL;
		}
		// materials->release
		if (aCannon[nCnt].Xfile_Materials != NULL)
		{
			aCannon[nCnt].Xfile_Materials->Release();
			aCannon[nCnt].Xfile_Materials = NULL;
		}
	}
}

void UpdateCannon()
{
	g_nCntTimeCannon++;
	int nTime = GetTimer();

	//��]
	for (int nCnt = 0; nCnt < CANNON_NUM; nCnt++) aCannon[nCnt].rot.y += aCannon[nCnt].fRotSpeed;

	if (nTime > 15)
	{
		//�p�x�i�� right 
		if (aCannon[0].rot.y > MAX_ROT_ANGLE) aCannon[0].fRotSpeed = -ROT_SPEED;
		else if (aCannon[0].rot.y < MIN_ROT_ANGLE) aCannon[0].fRotSpeed = ROT_SPEED;

		//�p�x�i�� left
		if (aCannon[1].rot.y < -MAX_ROT_ANGLE) aCannon[1].fRotSpeed = ROT_SPEED;
		else if (aCannon[1].rot.y > -MIN_ROT_ANGLE) aCannon[1].fRotSpeed = -ROT_SPEED;

		//���e����
		if (g_nCntTimeCannon % BOMB_CREATE_TIME == 0)
		{
			int nCannonID = rand() % 2;
			SetBomb(nCannonID);
		}
	}
	else
	{
		//�p�x�i�� right 
		if (aCannon[0].rot.y > MAX_ROT_ANGLE) aCannon[0].fRotSpeed = -ROT_SPEED * 5;
		else if (aCannon[0].rot.y < MIN_ROT_ANGLE) aCannon[0].fRotSpeed = ROT_SPEED * 5;

		//�p�x�i�� left
		if (aCannon[1].rot.y < -MAX_ROT_ANGLE) aCannon[1].fRotSpeed = ROT_SPEED * 5;
		else if (aCannon[1].rot.y > -MIN_ROT_ANGLE) aCannon[1].fRotSpeed = -ROT_SPEED * 5;

		//���e����
		if (g_nCntTimeCannon % (BOMB_CREATE_TIME / 2) == 0)
		{
			int nCannonID = rand() % 2;
			SetBomb(nCannonID);
		}
	}



}

void DrawCannon()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxworld;
	D3DMATERIAL9 matDef;
	for (int nCnt = 0; nCnt < CANNON_NUM; nCnt++)
	{

		D3DXMatrixIdentity(&mtxworld);//�P��matrix
		D3DXMatrixRotationYawPitchRoll(&mtxRot, aCannon[nCnt].rot.y, aCannon[nCnt].rot.x, aCannon[nCnt].rot.z);//��]�p�x
		D3DXMatrixMultiply(&mtxworld, &mtxworld, &mtxRot);//���Z
		D3DXMatrixTranslation(&mtxTrans, aCannon[nCnt].pos.x, aCannon[nCnt].pos.y, aCannon[nCnt].pos.z); //���Ematrix�S�́@�ړ������������Ƃ���matrix�̍��Z
		D3DXMatrixMultiply(&mtxworld, &mtxworld, &mtxTrans); //���Z�@���Ematrix�̈ړ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxworld); //set the world into Map
		pDevice->GetMaterial(&matDef);//�ގ������
		for (DWORD nCntMat = 0; nCntMat < aCannon[nCnt].Xfile_MaterialNum; nCntMat++)
		{
			pDevice->SetMaterial(&pMaterials_Cannon[nCntMat].MatD3D); //�ގ��̐ݒ�
			pDevice->SetTexture(0, aCannon[nCnt].Xfile_Textures[nCntMat]); //Textute�̐ݒ�
			aCannon[nCnt].Xfile_Mesh->DrawSubset(nCntMat); //�`��
		}
		pDevice->SetMaterial(&matDef); //�ގ��̐ݒ�reset
	}

}

CANNON *GetCannon()
{
	return &aCannon[0];
}