#include "BombCollision.h"
#include "Bomb.h"
#include "player.h"
LPD3DXMESH pMesh = NULL; //mesh
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBombCol = NULL; //頂点bufferのpointer
D3DXMATERIAL pMaterials_BombCol; //材質 
void InitBombCollision()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOMB *pBomb = GetBomb();

	for (int nCnt = 0; nCnt < BOMB_NUMBER; nCnt++, pBomb++)
		D3DXCreateSphere(pDevice, BOMB_RADIUS, BOMB_COL_SLICES, BOMB_COL_STACKS, &pMesh, NULL);

	pMaterials_BombCol.MatD3D.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 0.5f); //環境light
	pMaterials_BombCol.MatD3D.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 0.5f); //反射light
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
	D3DXMATRIX WorldMtxGround, mtxRot, mtxTrans; //計算用のmatrix
	D3DMATERIAL9 matDef;
	BOMB *pBomb = GetBomb();

	for (int nCnt = 0; nCnt < BOMB_NUMBER; nCnt++, pBomb++)
	{
		if (pBomb->bUse)
		{
			D3DXMatrixIdentity(&WorldMtxGround); //単位行列
			D3DXMatrixTranslation(&mtxTrans, pBomb->pos.x, pBomb->pos.y, pBomb->pos.z); //世界matrix全体　移動したい距離というmatrixの合算
			D3DXMatrixMultiply(&WorldMtxGround, &WorldMtxGround, &mtxTrans); //世界matrixの移動
			pDevice->SetTransform(D3DTS_WORLD, &WorldMtxGround); //set the world into Map
			pDevice->GetMaterial(&matDef); //default材質を保存する
			pDevice->SetMaterial(&pMaterials_BombCol.MatD3D); //当たり判定用球の材質設定
			pDevice->SetTexture(0, NULL); //textureなし
			pMesh->DrawSubset(0); //描画
			pDevice->SetMaterial(&matDef); //default材質に戻す
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


	if (fLength <= BOMB_PLAYER_BLOW_RANGE_1) //爆発中心
	{
		//眩暈
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
	else if (fLength <= BOMB_PLAYER_BLOW_RANGE_2) //爆発中心に近い
	{
		BlowUp_Force = Length_Vector / BOMB_PLAYER_BLOW_RANGE_2 * BLOW_UP_FORCE_DEFAULT;
		BlowUp_Force.y = BLOW_UP_FORCE_Y2_OFFSET;
		return BlowUp_Force;
	}
	else if (fLength <= BOMB_PLAYER_BLOW_RANGE_3) //爆発中心に遠い
	{
		BlowUp_Force = Length_Vector / BOMB_PLAYER_BLOW_RANGE_3 * BLOW_UP_FORCE_DEFAULT;
		BlowUp_Force.y = BLOW_UP_FORCE_Y3_OFFSET;
		return BlowUp_Force;
	}
	else //爆発処理が終わったら reset
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