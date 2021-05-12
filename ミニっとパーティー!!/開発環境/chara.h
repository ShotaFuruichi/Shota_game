//-------------------------------------------------------------------
//
// キャラヘッダー (chara.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _CHARA_H_
#define _CHARA_H_

#include "main.h"
#include "motion.h"

//-------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------
#define MAX_CHARA		(5)		// キャラの最大数
#define MAX_FILENAME	(64)		// Xファイルネームの最大文字数

//-------------------------------------------------------------------
// 構造体の定義
//-------------------------------------------------------------------
typedef struct
{
	LPD3DXMESH pMesh;				// メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER pBuffMat;			// マテリアル(材質情報)へのポインタ
	DWORD nNumMat = 0;				// マテリアルの数
	LPDIRECT3DTEXTURE9 pTexture[16] = {};	// テクスチャへのポインタ
	char aFileName[MAX_FILENAME];	// ファイルの名前
	D3DXVECTOR3 pos;				// 中心座標
	D3DXVECTOR3 rot;				// 回転角
	D3DXMATRIX mtxWorld;			// ワールドマトリックス
	int nIdxModelParent;			// 親モデルのインデックス
	D3DXVECTOR3 minVecModel;		// 頂点の最小値
	D3DXVECTOR3 maxVecModel;		// 頂点の最大値
}CharacterModel;

typedef struct
{
	D3DXVECTOR3 pos;							// 中心座標
	D3DXVECTOR3 posOld;							// 前の中心座標
	D3DXVECTOR3 rot;							// 現在の向き
	D3DXVECTOR3 rotDest;						// 目的の向き
	D3DXMATRIX mtxWorld;						// ワールドマトリックス
	CharacterModel aModel[20];					// モデル
	int nNumModel;								// モデル数
	D3DXVECTOR3 minVecPlayer;					// 頂点の最小値
	D3DXVECTOR3 maxVecPlayer;					// 頂点の最大値
	float fHeight;								// 当たり判定の高さ
	float fRadius;								// 当たり判定の半径
	int nIdx;									// 何番目の影か
	MOTION_INFO aMotionInfo[MOTYONTYPE_MAX];	// モーション情報
	int nNumMotion;								// モーション数
	MOTIONTYPE MotionType;						// モーションタイプ
	bool bLoopMotion;							// ループするかどうか
	int nNumKey;								// キー数
	int nKey;									// キーNo.
	int nCounterMotion;							// モーションカウンタ
	bool bFall;									// 落ちたかどうか
}CharacterInfo;

typedef struct
{
	CharacterInfo characterInfo[MAX_CHARA];		// キャラクター情報
	int nNumCharacter;							// 情報を読み込むキャラクターの総数
	char aTextName[MAX_CHARA][256];				// テキストネーム読み込み用
}Character;

//-------------------------------------------------------------------
// プロトタイプ宣言
//-------------------------------------------------------------------
HRESULT InitCharacter(void);				// キャラの初期化処理
void UninitCharacter(void);					// キャラの終了処理
void UpdateCharacter(void);					// キャラの更新処理
void DrawCharacter(void);					// キャラの描画処理

Character *GetCharacter(void);				// キャラ情報の取得

void CharacterMotion(int Character);			// プレイヤモーションの設定
void SetCharaMotion(int Character, MOTIONTYPE motiontype, bool bBlend, int nFrameBlend);	// モーションの設定

#endif