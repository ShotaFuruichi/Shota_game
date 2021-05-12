#include "Bomb.h"
#include "player.h"
#include "BombEffect.h"
#include "BombCollision.h"
#include "Cannon.h"
#include "shadow.h"
#include "chara_select_frame.h"

BOMB aBomb[BOMB_NUMBER];
D3DXMATERIAL *pMaterials_Bomb;
int g_nCntTimeBomb;
int g_nNumPlayer_Bomb;

HRESULT InitBomb() //BOMB��`
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	BOMB *pBomb = &aBomb[0];
	g_nCntTimeBomb = 0;
	g_nNumPlayer_Bomb = GetFrame();
	for (int nCnt = 0; nCnt < BOMB_NUMBER; nCnt++, pBomb++)
	{
		pBomb->bUse = false;
		pBomb->nID = nCnt;
		pBomb->nCntTime = BOMB_BLOW_UP_TIME;
		pBomb->pos = D3DXVECTOR3(0, 0, 0);
		pBomb->move = D3DXVECTOR3(0, 0, 0);
		pBomb->rot = D3DXVECTOR3(0, 0, 0);
		pBomb->rotMove = D3DXVECTOR3(0, 0, 0);
		pBomb->BombState = BOMB_NOTCREATE;
		pBomb->bCatch = false;
		pBomb->Xfile_Mesh = NULL;
		pBomb->Xfile_Materials = NULL;
		pBomb->Xfile_MaterialNum = 0;
		memset(pBomb->Xfile_Textures, NULL, sizeof(LPDIRECT3DTEXTURE9) * BOMB_TEXTURE);

		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX("data/MODEL/Bomb.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&pBomb->Xfile_Materials,
			NULL,
			&pBomb->Xfile_MaterialNum,
			&pBomb->Xfile_Mesh)))
			return E_FAIL;

		//Texture�̐ݒ�
		pMaterials_Bomb = (D3DXMATERIAL*)pBomb->Xfile_Materials->GetBufferPointer();
		for (DWORD nCnt = 0; nCnt < pBomb->Xfile_MaterialNum; nCnt++)
		{
			if (pMaterials_Bomb[nCnt].pTextureFilename != NULL)
			{
				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMaterials_Bomb[nCnt].pTextureFilename,
					&pBomb->Xfile_Textures[nCnt]);
			}
			else pBomb->Xfile_Textures[nCnt] = nullptr;
		}
	}

	// Bomb�̓����蔻��p����
	InitBombCollision();

	// �����̌x��mark
	InitBombWarnMark();

	// ����effect
	InitBlowEffect();

	// ��C
	InitCannon();
	return S_OK;
}

void UninitBomb()
{
	BOMB *pBomb = &aBomb[0];
	for (int nCnt = 0; nCnt < BOMB_NUMBER; nCnt++, pBomb++)
	{
		// mesh->release
		if (pBomb->Xfile_Mesh != NULL)
		{
			pBomb->Xfile_Mesh->Release();
			pBomb->Xfile_Mesh = NULL;
		}
		// materials->release
		if (pBomb->Xfile_Materials != NULL)
		{
			pBomb->Xfile_Materials->Release();
			pBomb->Xfile_Materials = NULL;
		}
	}

	UninitBombCollision();
	UninitBombWarnMark();
	UninitBlowEffect();
	UninitCannon();
}

void UpdateBomb() //BOMB�X�V����
{
	g_nCntTimeBomb++; //�J�E���gFrame
	BOMB *pBomb = &aBomb[0];														

	//Bomb�̏�ԊǗ�
	BombStateControl();

	//Bomb�����̉�]
	BombSpin();

	//�����x��mark�̍X�V
	UpdateBombWarnMark();

	//����effect�̍X�V
	if (g_nCntTimeBomb % 3 == 0)
		UpdateBlowEffect();

	//��C
	UpdateCannon();

	//shadow 
	/*for (int nCnt = 0; nCnt < BOMB_NUMBER && pBomb->bUse; nCnt++, pBomb++)
		SetPositionShadow(pBomb->nIdexShadow, D3DXVECTOR3(pBomb->pos.x, 52.5f, pBomb->pos.z));*/

}

void DrawBomb() //BOMB�`��
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxworld;
	D3DMATERIAL9 matDef;
	BOMB *pBomb = &aBomb[0];
	for (int nCnt = 0; nCnt < BOMB_NUMBER; nCnt++, pBomb++)
	{
		if (pBomb->bUse)
		{
			D3DXMatrixIdentity(&mtxworld);//�P��matrix
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pBomb->rot.y, pBomb->rot.x, pBomb->rot.z);//��]�p�x
			D3DXMatrixMultiply(&mtxworld, &mtxworld, &mtxRot);//���Z
			D3DXMatrixTranslation(&mtxTrans, pBomb->pos.x, pBomb->pos.y, pBomb->pos.z); //���Ematrix�S�́@�ړ������������Ƃ���matrix�̍��Z
			D3DXMatrixMultiply(&mtxworld, &mtxworld, &mtxTrans); //���Z�@���Ematrix�̈ړ�
			pDevice->SetTransform(D3DTS_WORLD, &mtxworld); //set the world into Map
			pDevice->GetMaterial(&matDef);//�ގ������
			for (DWORD nCntMat = 0; nCntMat < pBomb->Xfile_MaterialNum; nCntMat++)
			{
				pDevice->SetMaterial(&pMaterials_Bomb[nCntMat].MatD3D); //�ގ��̐ݒ�
				pDevice->SetTexture(0, pBomb->Xfile_Textures[nCntMat]); //Textute�̐ݒ�
				pBomb->Xfile_Mesh->DrawSubset(nCntMat); //�`��
			}
			MatrixShadow(pBomb->Xfile_MaterialNum,
				mtxworld,
				D3DXVECTOR3(0.0f,56.0f,0.0f),
				pBomb->Xfile_Mesh);

			pDevice->SetMaterial(&matDef); //�ގ��̐ݒ�reset
		}
	}

#ifdef _DEBUG
	//�@Bomb�����蔻��p���̂̕`��
	/*DrawBombCollision();*/
#endif // 1
	DrawBlowEffect();
	DrawCannon();
}

void SetBomb(int nCannonID) //BOMB�L����
{
	BOMB *pBomb = &aBomb[0];
	CANNON *pCannon = GetCannon();
	D3DXVECTOR2 Throw = D3DXVECTOR2(0.f, -BOMB_THROW_SPEED); //default����������ݒ肷��

	for (int nCnt = 0; nCnt < BOMB_NUMBER; nCnt++, pBomb++)
	{
		if (!pBomb->bUse)
		{
			pBomb->bUse = true;
			pBomb->pos = pCannon[nCannonID].pos;
			pBomb->move.x = -(Throw.x * cosf(pCannon[nCannonID].rot.y) - Throw.y * sinf(pCannon[nCannonID].rot.y));
			pBomb->move.z = Throw.x * sinf(pCannon[nCannonID].rot.y) + Throw.y * cosf(pCannon[nCannonID].rot.y);
			pBomb->move.x *= BOMB_SHOOT_POWER;
			pBomb->move.z *= BOMB_SHOOT_POWER;
			pBomb->move.y = BOMB_SHOOT_SPEED_Y;
			pBomb->rotMove.x = -(pBomb->move.z / 7.f) / D3DX_PI;
			pBomb->rotMove.z = (pBomb->move.x / 7.f) / D3DX_PI;
			pBomb->BombState = BOMB_SHOOT_OUT;
			//pBomb->nIdexShadow = SetShadow(D3DXVECTOR3(pBomb->pos.x, STAGE_HEIGHT, pBomb->pos.z), BOMB_SHADOW, BOMB_SHADOW);
			break;
		}
	}
}

void BombThrow(int nID, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	BOMB *pBomb = &aBomb[0];
	D3DXVECTOR2 Throw = D3DXVECTOR2(0.f, -BOMB_THROW_SPEED); //default����������ݒ肷��

	 //default���������Ɖ�]�s��̌v�Z�i�ʂꂽ�j
	pBomb[nID].move.x = -(Throw.x * cosf(rot.y) - Throw.y * sinf(rot.y));
	pBomb[nID].move.z = Throw.x * sinf(rot.y) + Throw.y * cosf(rot.y);
	pBomb[nID].move.x *= BOMB_THROW_POWER;
	pBomb[nID].move.z *= BOMB_THROW_POWER;
	pBomb[nID].move.y = BOMB_THROW_SPEED_Y;
	pBomb[nID].BombState = BOMB_MOVE;
	pBomb[nID].bCatch = false;
	pBomb[nID].rotMove.x = -(pBomb[nID].move.z / 7.f) / D3DX_PI;
	pBomb[nID].rotMove.z = (pBomb[nID].move.x / 7.f) / D3DX_PI;
	//pBomb[nID].rotMove.y = BOMB_SPIN_Y;
}

void BombStateControl() //BOMB��ԊǗ�
{
	BOMB *pBomb = &aBomb[0];
	Player *pPlayer = GetPlayer();
	float fStageRadius;

	for (int nCntBomb = 0; nCntBomb < BOMB_NUMBER; nCntBomb++, pBomb++)
	{
		//�����J�E���g�_�E�� (60Frame = 1�b)
		if (pBomb->bUse && g_nCntTimeBomb % 60 == 0)
		{
			pBomb->nCntTime--;
			if (pBomb->nCntTime < WARNING_MARK_NUMBER)
				ResetBombMark(nCntBomb);
		}

		if (pBomb->nCntTime == 0)
		{
			SetBombBlow(nCntBomb);
		}
		else if (pBomb->nCntTime == WARNING_MARK_NUMBER) //�Ō��3�b
			SetBombMark(nCntBomb);

		switch (pBomb->BombState)
		{
		case BOMB_SHOOT_OUT:
			fStageRadius = sqrtf(pBomb->pos.x * pBomb->pos.x + pBomb->pos.z * pBomb->pos.z);
			if (fStageRadius < STAGE_RADIUS) pBomb->BombState = BOMB_MOVE;
			else pBomb->pos += pBomb->move;
			break;
		case BOMB_MOVE:
			//�ړ�����
			if (pBomb->pos.y >= STAGE_HEIGHT) //bomb����Ԓ�
			{
				pBomb->move.y -= BOMB_GRAVITY;
				if (pBomb->move.x > 0) pBomb->move.x -= BOMB_AIR_FRICTION;
				else pBomb->move.x += BOMB_AIR_FRICTION;
				if (pBomb->move.z > 0) pBomb->move.z -= BOMB_AIR_FRICTION;
				else pBomb->move.z += BOMB_AIR_FRICTION;
			}
			else if (pBomb->pos.y < STAGE_HEIGHT &&
				(fabsf(pBomb->move.x) > BOMB_GROUND_FRICTION) || (fabsf(pBomb->move.z) > BOMB_GROUND_FRICTION)) //�n�ʂɓ������A�܂������̈ړ��ʂ��n�ʂ̖��C�͂�葽���ꍇ
			{
				pBomb->move.y = -pBomb->move.y * BOMB_ELASTIC;
				pBomb->move.x -= BOMB_GROUND_FRICTION;
				pBomb->move.z -= BOMB_GROUND_FRICTION;
				pBomb->pos.y = STAGE_HEIGHT + pBomb->move.y;
			}
			else
			{
				pBomb->pos.y = STAGE_HEIGHT;
				pBomb->BombState = BOMB_STOP; //�ړ���~
			}

			pBomb->pos += pBomb->move;

			//stage�O�ɍs������
			fStageRadius = sqrtf(pBomb->pos.x * pBomb->pos.x + pBomb->pos.z * pBomb->pos.z);
			if (fStageRadius > STAGE_RADIUS)
			{
				SetBombBlow(nCntBomb);
			}

			break;
		case BOMB_STOP:
			if (pBomb->pos.y >= STAGE_HEIGHT)
				pBomb->BombState = BOMB_MOVE;
			break;
		case BOMB_CATCH:
			pPlayer = GetPlayer();
			for (int nCntPlayer = 0; nCntPlayer < g_nNumPlayer_Bomb; nCntPlayer++, pPlayer++)
			{
				if (pPlayer->nBombID == nCntBomb)
				{
					pBomb->pos.x = pPlayer->aModel[4].mtxWorld._41;
					pBomb->pos.y = pPlayer->aModel[4].mtxWorld._42;
					pBomb->pos.z = pPlayer->aModel[4].mtxWorld._43;
					break;
				}
			}
			break;
		case BOMB_BLOW:
			pPlayer = GetPlayer();
			for (int nCntPlayer = 0; nCntPlayer < g_nNumPlayer_Bomb; nCntPlayer++, pPlayer++)
			{
				if (!pPlayer->bFall)
				{
					pPlayer->move += BombBlow_Col(pPlayer->pos, nCntBomb);
					if (BombBlow_Col_Bool(pPlayer->pos, nCntBomb))
					{
						SetMotion(nCntPlayer, MOTIONTYPE_DAMAGE, true, 10);
					}
					if (pPlayer->nBombID == nCntBomb)
					{
						pPlayer->nBombID = -1;
					}
				}
			}
			pBomb->bUse = false;
			pBomb->bCatch = false;
			pBomb->nCntTime = BOMB_BLOW_UP_TIME;
			pBomb->pos = D3DXVECTOR3(0, 0, 0);
			pBomb->move = D3DXVECTOR3(0, 0, 0);
			pBomb->rot = D3DXVECTOR3(0, 0, 0);
			pBomb->BombState = BOMB_NOTCREATE;
			break;
		default:
			break;
		}
	}
}

void BombSpin()
{
	BOMB *pBomb = &aBomb[0];
	for (int nCnt = 0; nCnt < BOMB_NUMBER && pBomb->bUse; nCnt++, pBomb++)
	{
		if (pBomb->bUse)
		{
			pBomb->rot.x += pBomb->rotMove.x;
			pBomb->rot.z += pBomb->rotMove.z;
			if (pBomb->rotMove.x > 0.002f / D3DX_PI) pBomb->rotMove.x -= 0.002f / D3DX_PI;
			else if (pBomb->rotMove.x < -0.002f / D3DX_PI) pBomb->rotMove.x += 0.002f / D3DX_PI;
			else pBomb->rotMove.x = 0.f;
			if (pBomb->rotMove.z > 0.002f / D3DX_PI) pBomb->rotMove.z -= 0.002f / D3DX_PI;
			else if (pBomb->rotMove.z < -0.002f / D3DX_PI) pBomb->rotMove.z += 0.002f / D3DX_PI;
			else pBomb->rotMove.z = 0.f;
		}
	}
}

BOMB *GetBomb()
{
	return &aBomb[0];
}

void BombAndPlayer(int nCntPlayer)
{
	//�v���C�A�Ɠ����蔻��
	BOMB *pBomb = &aBomb[0];
	Player *pPlayer = GetPlayer();
	for (int nCntBomb = 0; nCntBomb < BOMB_NUMBER; nCntBomb++, pBomb++)
	{
		if (!pBomb->bCatch && !pPlayer[nCntPlayer].bFall && (BombCollision(pPlayer[nCntPlayer].pos, nCntBomb)))
		{
			pBomb->BombState = BOMB_CATCH;
			pPlayer[nCntPlayer].nBombID = nCntBomb;
			pBomb->pos = pPlayer->pos;
			pBomb->pos.y += pPlayer[nCntPlayer].maxVecPlayer.y + BOMB_PLAYER_CATCH_Y;
			pBomb->bCatch = true;
			break; //���Bomb���������܂���B
		}
	}
}

void SetBombBlow(int nCntBomb)
{
	aBomb[nCntBomb].BombState = BOMB_BLOW;
	SetBlowEffect(&aBomb[nCntBomb]);
	//DeleteShadow(aBomb[nCntBomb].nIdexShadow);
	ResetBombMarkALL(nCntBomb);
}