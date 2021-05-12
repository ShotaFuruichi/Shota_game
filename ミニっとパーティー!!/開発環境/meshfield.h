//-------------------------------------------------------------------
//
// メッシュフィールドヘッダー (meshfield.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

//-----------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------
#define MAX_MESHFIELD	(16)

//-----------------------------------------------------------------
// 構造体の定義
//-----------------------------------------------------------------
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffMeshField = NULL;				// メッシュフィールドの頂点バッファのポインタ
	LPDIRECT3DINDEXBUFFER9 pIdxBuffMeshField = NULL;				// メッシュフィールドのインデックスへのポインタ
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3 pos;			// 壁の中心座標
	D3DXVECTOR3 rot;			// 壁の向き
	int nCntMeshFieldX;			// 壁の数(列)
	int nCntMeshFieldZ;			// 壁の数(行)
	int nCntVecX;				// 列の頂点数
	int nCntVecZ;				// 行の頂点数
	float fWidth;				// 幅
	float fDepth;				// 奥行
	float fsizeWidth;			// 幅のサイズ
	float fsizeDepth;			// 奥行のサイズ
	int nVetex;					// 頂点数
	int nPrimitive;				// プリミティブ数
	int nIndex;					// インデックス数
	int nIdxtexture;			// 何番目のテクスチャか
	bool bUse;					// 使用しているかどうか
}MeshField;

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitMeshField(void);									// メッシュフィールドの初期化処理
void UninitMeshField(void);										// メッシュフィールドの終了処理
void UpdateMeshField(void);										// メッシュフィールドの更新処理
void DrawMeshField(void);										// メッシュフィールドの描画処理

bool CollisionMeshField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, int nIdxShadow, D3DXVECTOR3 *PosShadow);// 当たり判定

void SetMeshField(int type,D3DXVECTOR3 pos, D3DXVECTOR3 rot, 
	int blockX, int blockZ, float sizeX, float sizeZ);				// メッシュフィールドセット

MeshField *GetMeshField(void);									// メッシュフィールド情報の取得

#endif