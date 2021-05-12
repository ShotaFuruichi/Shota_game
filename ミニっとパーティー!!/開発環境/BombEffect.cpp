#include "BombEffect.h"
#include "Bomb.h"

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlowParticle = NULL; //頂点bufferのpointer
LPDIRECT3DTEXTURE9 g_pTextureBlowParticle[BOMB_PARTICLE_TEX] = {}; //textureのpointer
BLOW_EFFECT aBlow_Effect[BOMB_NUMBER];

HRESULT InitBlowEffect()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	VERTEX_3D *pVtx;
	BOMB *pBomb = GetBomb();

	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/BlowUp.png", &g_pTextureBlowParticle[0])))
		return E_FAIL;
	
	//初期化
	for (int nCnt = 0; nCnt < BOMB_NUMBER; nCnt++, pBomb++)
	{
		aBlow_Effect[nCnt].bUse = false;
		aBlow_Effect[nCnt].pos = D3DXVECTOR3(0, 0, 0);
		aBlow_Effect[nCnt].nID = nCnt;
		aBlow_Effect[nCnt].move = D3DXVECTOR3(0, 0, 0);
		aBlow_Effect[nCnt].nor = D3DXVECTOR3(0, 1, 0);
		aBlow_Effect[nCnt].nPatternAnime = 0;
		aBlow_Effect[nCnt].nTextureID = 0;
	}
	
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * BOMB_NUMBER * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlowParticle,
		NULL)))
		return E_FAIL;

	g_pVtxBuffBlowParticle->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < BOMB_NUMBER; nCnt++, pVtx += 4)
	{
		pVtx[0].pos = D3DXVECTOR3(-BLOW_EFFECT_SIZE_X, BLOW_EFFECT_SIZE_Y, 0.f);
		pVtx[1].pos = D3DXVECTOR3(BLOW_EFFECT_SIZE_X, BLOW_EFFECT_SIZE_Y, 0.f);
		pVtx[2].pos = D3DXVECTOR3(-BLOW_EFFECT_SIZE_X, -BLOW_EFFECT_SIZE_Y, 0.f);
		pVtx[3].pos = D3DXVECTOR3(BLOW_EFFECT_SIZE_X, -BLOW_EFFECT_SIZE_Y, 0.f);
		pVtx[0].nor = aBlow_Effect[nCnt].nor;
		pVtx[1].nor = aBlow_Effect[nCnt].nor;
		pVtx[2].nor = aBlow_Effect[nCnt].nor;
		pVtx[3].nor = aBlow_Effect[nCnt].nor;
		pVtx[0].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[1].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[2].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[3].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
		pVtx[0].tex = D3DXVECTOR2((float)(aBlow_Effect[nCnt].nPatternAnime) / BLOW_EFFECT_PART, 0);
		pVtx[1].tex = D3DXVECTOR2((float)((aBlow_Effect[nCnt].nPatternAnime + 1) / BLOW_EFFECT_PART), 0);
		pVtx[2].tex = D3DXVECTOR2((float)(aBlow_Effect[nCnt].nPatternAnime / BLOW_EFFECT_PART), 1);
		pVtx[3].tex = D3DXVECTOR2((float)((aBlow_Effect[nCnt].nPatternAnime + 1) / BLOW_EFFECT_PART), 1);
	}
	g_pVtxBuffBlowParticle->Unlock();
	return S_OK;
}

void UpdateBlowEffect()
{
	BLOW_EFFECT *pBlowEffect = &aBlow_Effect[0];
	BOMB *pBomb = GetBomb();
	VERTEX_3D *pVtx;

	g_pVtxBuffBlowParticle->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < BOMB_NUMBER; nCnt++, pBlowEffect++, pBomb++, pVtx += 4)
	{
		if (pBlowEffect->bUse)
		{
			if (pBlowEffect->nPatternAnime < BLOW_EFFECT_PART)
			{
				pBlowEffect->nPatternAnime++;
			}
			else
			{
				pBlowEffect->nPatternAnime = 0;
				pBlowEffect->bUse = false;
			}
			pVtx[0].tex = D3DXVECTOR2((float)(aBlow_Effect[nCnt].nPatternAnime) / BLOW_EFFECT_PART, 0);
			pVtx[1].tex = D3DXVECTOR2((float)((aBlow_Effect[nCnt].nPatternAnime + 1) / BLOW_EFFECT_PART), 0);
			pVtx[2].tex = D3DXVECTOR2((float)(aBlow_Effect[nCnt].nPatternAnime / BLOW_EFFECT_PART), 1);
			pVtx[3].tex = D3DXVECTOR2((float)((aBlow_Effect[nCnt].nPatternAnime + 1) / BLOW_EFFECT_PART), 1);
		}
	}
	g_pVtxBuffBlowParticle->Unlock();
}

void UninitBlowEffect()
{
	if (g_pVtxBuffBlowParticle != NULL)
	{
		g_pVtxBuffBlowParticle->Release();
		g_pVtxBuffBlowParticle = NULL;
	}
	for (int nCnt = 0; nCnt < BOMB_PARTICLE_TEX; nCnt++)
	{
		if (g_pTextureBlowParticle[nCnt] != NULL)
		{
			g_pTextureBlowParticle[nCnt]->Release();
			g_pTextureBlowParticle[nCnt] = NULL;
		}
	}
}
void DrawBlowEffect()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxTrans, WorldBillboard; //計算用のmatrix
	BLOW_EFFECT *pBlowEffect = &aBlow_Effect[0];

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE); //close the lighting and diffuse effect
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); //alpha test function
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100); //alpha number
	for (int nCnt = 0; nCnt < BOMB_NUMBER; nCnt++, pBlowEffect++)
	{
		if (pBlowEffect->bUse)
		{
			D3DXMatrixIdentity(&WorldBillboard); //単位行列
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&WorldBillboard, NULL, &mtxView);
			//平行移動の部分は無視する
			WorldBillboard._41 = 0.0f;
			WorldBillboard._42 = 0.0f;
			WorldBillboard._43 = 0.0f;
			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, pBlowEffect->pos.x, pBlowEffect->pos.y, pBlowEffect->pos.z); //世界matrix全体　移動したい距離というmatrixの合算
			D3DXMatrixMultiply(&WorldBillboard, &WorldBillboard, &mtxTrans); //世界matrixの移動

			pDevice->SetTransform(D3DTS_WORLD, &WorldBillboard); //set the world into Map
			pDevice->SetStreamSource(0, g_pVtxBuffBlowParticle, 0, sizeof(VERTEX_3D));
			pDevice->SetFVF(FVF_VERTEX_3D);
			pDevice->SetTexture(0, g_pTextureBlowParticle[pBlowEffect->nTextureID]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
	//reset
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//αテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}
void SetBlowEffect(BOMB *pBomb)
{
	aBlow_Effect[pBomb->nID].bUse = true;
	aBlow_Effect[pBomb->nID].pos = pBomb->pos;
	aBlow_Effect[pBomb->nID].pos.y += BLOW_EFFECT_Y_OFFSET;
}