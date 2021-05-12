#include "BombWarningMark.h"
#include "Bomb.h"
#include "camera.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxMark = NULL;
LPDIRECT3DTEXTURE9 g_pTextureMark = NULL;

void InitBombWarnMark()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOMB *pBomb = GetBomb();
	VERTEX_2D *pVtx;

	//初期化
	for (int nCntBomb = 0; nCntBomb < BOMB_NUMBER; nCntBomb++, pBomb++)
	{
		for (int nCntMark = 0; nCntMark < WARNING_MARK_NUMBER; nCntMark++)
		{
			pBomb->aWarning_Mark[nCntMark].bUse = false;
			pBomb->aWarning_Mark[nCntMark].pos = D3DXVECTOR2(0, 0);
			pBomb->aWarning_Mark[nCntMark].frot = 0.f;
			pBomb->aWarning_Mark[nCntMark].size = D3DXVECTOR2(MARK_SIZE_X, MARK_SIZE_Y);
		}
	}

	D3DXCreateTextureFromFile(pDevice, "data/Texture/BombMark.png", &g_pTextureMark);
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * BOMB_NUMBER * WARNING_MARK_NUMBER,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED,
		&g_pVtxMark,
		NULL);

	g_pVtxMark->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntBomb = 0; nCntBomb < BOMB_NUMBER; nCntBomb++)
	{
		for (int nCntMark = 0; nCntMark < WARNING_MARK_NUMBER; nCntMark++, pVtx += 4)
		{
		pVtx[0].pos = D3DXVECTOR3(pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.x - pBomb[nCntBomb].aWarning_Mark[nCntMark].size.x, pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.y - pBomb[nCntBomb].aWarning_Mark[nCntMark].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.x + pBomb[nCntBomb].aWarning_Mark[nCntMark].size.x, pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.y - pBomb[nCntBomb].aWarning_Mark[nCntMark].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.x - pBomb[nCntBomb].aWarning_Mark[nCntMark].size.x, pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.y + pBomb[nCntBomb].aWarning_Mark[nCntMark].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.x + pBomb[nCntBomb].aWarning_Mark[nCntMark].size.x, pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.y + pBomb[nCntBomb].aWarning_Mark[nCntMark].size.y, 0.0f);
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);
		}
	}
	g_pVtxMark->Unlock();
}

void UninitBombWarnMark()
{
	if (g_pVtxMark != NULL)
	{
		g_pVtxMark->Release();
		g_pVtxMark = NULL;
	}
	if (g_pTextureMark != NULL)
	{
		g_pTextureMark->Release();
		g_pTextureMark = NULL;
	}
}

void UpdateBombWarnMark()
{
	BOMB *pBomb = GetBomb();
	VERTEX_2D *pVtx;
	g_pVtxMark->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntBomb = 0; nCntBomb < BOMB_NUMBER; nCntBomb++)
	{
		for (int nCntMark = 0; nCntMark < WARNING_MARK_NUMBER; nCntMark++, pVtx += 4)
		{
			if (pBomb[nCntBomb].aWarning_Mark[nCntMark].bUse)
			{
				pBomb[nCntBomb].aWarning_Mark[nCntMark].pos = Switch_Pos(pBomb[nCntBomb].pos);
				switch (nCntMark)
				{
				case 0:
					pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.x += POS_MARK_OFFSET_X_1;
					pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.y += POS_MARK_OFFSET_Y_1;
					break;
				case 1:
					pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.x += POS_MARK_OFFSET_X_2;
					pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.y += POS_MARK_OFFSET_Y_2;
					break;
				case 2:
					pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.x += POS_MARK_OFFSET_X_3;
					pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.y += POS_MARK_OFFSET_Y_3;
					break;
				}
				pVtx[0].pos = D3DXVECTOR3(pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.x - pBomb[nCntBomb].aWarning_Mark[nCntMark].size.x, pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.y - pBomb[nCntBomb].aWarning_Mark[nCntMark].size.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.x + pBomb[nCntBomb].aWarning_Mark[nCntMark].size.x, pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.y - pBomb[nCntBomb].aWarning_Mark[nCntMark].size.y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.x - pBomb[nCntBomb].aWarning_Mark[nCntMark].size.x, pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.y + pBomb[nCntBomb].aWarning_Mark[nCntMark].size.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.x + pBomb[nCntBomb].aWarning_Mark[nCntMark].size.x, pBomb[nCntBomb].aWarning_Mark[nCntMark].pos.y + pBomb[nCntBomb].aWarning_Mark[nCntMark].size.y, 0.0f);
			}
		}
	}
	g_pVtxMark->Unlock();
}

void DrawBombWarnMark()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BOMB *pBomb = GetBomb();
	int nCntVtx = 0;
	pDevice->SetStreamSource(0, g_pVtxMark, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBomb = 0; nCntBomb < BOMB_NUMBER; nCntBomb++, pBomb++)
	{
		for (int nCntMark = 0; nCntMark < WARNING_MARK_NUMBER; nCntMark++)
		{
			if (pBomb->aWarning_Mark[nCntMark].bUse)
			{
				pDevice->SetTexture(0, g_pTextureMark);
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntVtx * 4, 2);
			}
			nCntVtx ++;
		}
	}
}

void SetBombMark(int nCntBomb)
{
	BOMB *pBomb = GetBomb();
	for (int nCnt = 0; nCnt < WARNING_MARK_NUMBER; nCnt++)
		pBomb[nCntBomb].aWarning_Mark[nCnt].bUse = true;
}

void ResetBombMark(int nCntBomb)
{
	BOMB *pBomb = GetBomb();
	pBomb[nCntBomb].aWarning_Mark[pBomb[nCntBomb].nCntTime].bUse = false;
}

D3DXVECTOR2 Switch_Pos(D3DXVECTOR3 pos)
{
	Camera *pCamera = GetCamera();

	//vectorからmatrixになる (posと４*４行列を計算するため)
	D3DXMATRIX Pos_Mtx
	(pos.x, pos.y, pos.z, 1.0f,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0);

	D3DXMatrixMultiply(&Pos_Mtx, &Pos_Mtx, &pCamera->CameraInfo[0].mtxView);//カメラ行列と合算
	D3DXMatrixMultiply(&Pos_Mtx, &Pos_Mtx, &pCamera->CameraInfo[0].mtxProjection);//projection行列と合算

	//四列目の値を消す -> x,y軸の値-1から１まで絞る
	Pos_Mtx._11 = Pos_Mtx._11 / Pos_Mtx._14;
	Pos_Mtx._12 = Pos_Mtx._12 / Pos_Mtx._14;
	Pos_Mtx._13 = Pos_Mtx._13 / Pos_Mtx._14;
	Pos_Mtx._14 = Pos_Mtx._14 / Pos_Mtx._14;

	//スクリーン行列の設定
	float w = SCREEN_WIDTH / 2.0f;
	float h = SCREEN_HEIGHT / 2.0f;
	D3DXMATRIX Screen_Mtx = {
		w, 0, 0, 0,
		0, -h, 0, 0,
		0, 0, 1, 0,
		w, h, 0, 1
	};
	D3DXMatrixMultiply(&Pos_Mtx, &Pos_Mtx, &Screen_Mtx);//スクリーン行列と合算
	D3DXVECTOR2 Pos_UV = D3DXVECTOR2(Pos_Mtx._11, Pos_Mtx._12);//スクリーン座標を取る
	return	Pos_UV;
}

void ResetBombMarkALL(int nCntBomb)
{
	BOMB *pBomb = GetBomb();
	pBomb[nCntBomb].aWarning_Mark[0].bUse = false;
	pBomb[nCntBomb].aWarning_Mark[1].bUse = false;
	pBomb[nCntBomb].aWarning_Mark[2].bUse = false;
}