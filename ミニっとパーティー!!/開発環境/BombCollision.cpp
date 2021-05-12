#include "BombCollision.h"
#include "Bomb.h"
#include "player.h"
LPD3DXMESH pMesh = NULL; //mesh
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBombCol = NULL; //���_buffer��pointer
D3DXMATERIAL pMaterials_BombCol; //�ގ� 
void InitBombCollision()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOMB *pBomb = GetBomb();

	for (int nCnt = 0; nCnt < BOMB_NUMBER; nCnt++, pBomb++)
		D3DXCreateSphere(pDevice, BOMB_RADIUS, BOMB_COL_SLICES, BOMB_COL_STACKS, &pMesh, NULL);

	pMaterials_BombCol.MatD3D.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 0.5f); //��light
	pMaterials_BombCol.MatD3D.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 0.5f); //����light
}

void UninitBombCollision()
{
	if (pMesh != NULL)
	{
		pMesh->Release();
		pMesh = NULL;
	}
}

void DrawBombCollision()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX WorldMtxGround, mtxRot, mtxTrans; //�v�Z�p��matrix
	D3DMATERIAL9 matDef;
	BOMB *pBomb = GetBomb();

	for (int nCnt = 0; nCnt < BOMB_NUMBER; nCnt++, pBomb++)
	{
		if (pBomb->bUse)
		{
			D3DXMatrixIdentity(&WorldMtxGround); //�P�ʍs��
			D3DXMatrixTranslation(&mtxTrans, pBomb->pos.x, pBomb->pos.y, pBomb->pos.z); //���Ematrix�S�́@�ړ������������Ƃ���matrix�̍��Z
			D3DXMatrixMultiply(&WorldMtxGround, &WorldMtxGround, &mtxTrans); //���Ematrix�̈ړ�
			pDevice->SetTransform(D3DTS_WORLD, &WorldMtxGround); //set the world into Map
			pDevice->GetMaterial(&matDef); //default�ގ���ۑ�����
			pDevice->SetMaterial(&pMaterials_BombCol.MatD3D); //�����蔻��p���̍ގ��ݒ�
			pDevice->SetTexture(0, NULL); //texture�Ȃ�
			pMesh->DrawSubset(0); //�`��
			pDevice->SetMaterial(&matDef); //default�ގ��ɖ߂�
		}
	}
}

BOOL BombCollision(D3DXVECTOR3 TargetPos, int nBombID)
{
	BOMB *pBomb = GetBomb();
	D3DXVECTOR3 Length = TargetPos - pBomb[nBombID].pos;
	float fLength = sqrtf(Length.x * Length.x + Length.y * Length.y + Length.z * Length.z);
	if (fLength <= BOMB_RADIUS)
	{
		return true;
	}
	return false;
}

D3DXVECTOR3 BombBlow_Col(D3DXVECTOR3 TargetPos, int nBombID)
{
	BOMB *pBomb = GetBomb();

	D3DXVECTOR3 Length_Vector = TargetPos - pBomb[nBombID].pos;
	D3DXVECTOR3 BlowUp_Force = D3DXVECTOR3(0.f, 0.f, 0.f);
	float fLength = sqrtf(Length_Vector.x * Length_Vector.x + Length_Vector.y * Length_Vector.y + Length_Vector.z * Length_Vector.z);


	if (fLength <= BOMB_PLAYER_BLOW_RANGE_1) //�������S
	{
		//῝�
#if 1
		if (pBomb[nBombID].bCatch)
		{
			BlowUp_Force = Length_Vector * BOMB_SELF_BLOW_UP;
			BlowUp_Force.y = BLOW_UP_FORCE_Y1_OFFSET;
		}
		else
		{
			BlowUp_Force = Length_Vector / BOMB_PLAYER_BLOW_RANGE_1 * BLOW_UP_FORCE_DEFAULT;
			BlowUp_Force.y = BLOW_UP_FORCE_Y1_OFFSET;
		}
#endif // 0
		return BlowUp_Force;
	}
	else if (fLength <= BOMB_PLAYER_BLOW_RANGE_2) //�������S�ɋ߂�
	{
		BlowUp_Force = Length_Vector / BOMB_PLAYER_BLOW_RANGE_2 * BLOW_UP_FORCE_DEFAULT;
		BlowUp_Force.y = BLOW_UP_FORCE_Y2_OFFSET;
		return BlowUp_Force;
	}
	else if (fLength <= BOMB_PLAYER_BLOW_RANGE_3) //�������S�ɉ���
	{
		BlowUp_Force = Length_Vector / BOMB_PLAYER_BLOW_RANGE_3 * BLOW_UP_FORCE_DEFAULT;
		BlowUp_Force.y = BLOW_UP_FORCE_Y3_OFFSET;
		return BlowUp_Force;
	}
	else //�����������I������� reset
	{
		return BlowUp_Force;
	}

}

bool BombBlow_Col_Bool(D3DXVECTOR3 TargetPos, int nBombID)
{
	BOMB *pBomb = GetBomb();
	D3DXVECTOR3 Length_Vector = TargetPos - pBomb[nBombID].pos;
	D3DXVECTOR3 BlowUp_Force = D3DXVECTOR3(0.f, 0.f, 0.f);
	float fLength = sqrtf(Length_Vector.x * Length_Vector.x + Length_Vector.y * Length_Vector.y + Length_Vector.z * Length_Vector.z);

	if (fLength <= BOMB_PLAYER_BLOW_RANGE_3)
	{
		return true;
	}
	else
	{
		return false;
	}
}