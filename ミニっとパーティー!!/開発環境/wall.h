//-------------------------------------------------------------------
//
// 壁ヘッダー (wall.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//-----------------------------------------------------------------
// 構造体の定義
//-----------------------------------------------------------------
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffWall = NULL;			// 壁の頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 pIdxBuffWall = NULL;				// 壁のインデックスへのポインタ
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3 pos;			// 壁の中心座標
	D3DXVECTOR3 rot;			// 壁の向き
	D3DXVECTOR3 moveRot;		// 回転量
	int nCntWallX;				// 壁の数(列)
	int nCntWallY;				// 壁の数(行)
	int nCntVecX;				// 列の頂点数
	int nCntVecY;				// 行の頂点数
	float fWidth;				// 幅
	float fHieght;				// 奥行
	float fsizeWidth;			// 幅のサイズ
	float fsizeHieght;			// 奥行のサイズ
	int nVetex;					// 頂点数
	int nPrimitive;				// プリミティブ数
	int nIndex;					// インデックス数
	int nIdxtexture;			// 何番目のテクスチャか
	bool bUse;					// 使用しているかどうか
}Wall;

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitWall(void);								// 壁の初期化処理
void UninitWall(void);								// 壁の終了処理
void UpdateWall(void);								// 壁の更新処理
void DrawWall(void);								// 壁の描画処理

void SetWall(int type, D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 moveRot,
	int blockX, int blockY, float sizeX, float sizeY);		// 壁の配置
void CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pvtxMin, D3DXVECTOR3 *pvtxMax);					// 壁との当たり判定
Wall *GetWall(void);									// 壁情報の取得

#endif