//-------------------------------------------------------------------
//
// モーションヘッダー (motion.h)
// Author:Itsuki Takaiwa
//
//-------------------------------------------------------------------
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"

//-------------------------------------------------------------------
// 列挙型
//-------------------------------------------------------------------
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	// ニュートラルモーション
	MOTIONTYPE_MOVE,		// 移動モーション
	MOTIONTYPE_THROW,		// 投げモーション
	MOTIONTYPE_JUMP,		// ジャンプモーション
	MOTIONTYPE_LAND,		// 着地モーション
	MOTIONTYPE_WIN,			// 勝利モーション
	MOTIONTYPE_LOSE,		// 敗北モーション
	MOTIONTYPE_SIRIMOTI,	// 尻もちモーション
	MOTIONTYPE_DAMAGE,		// のけぞりモーション
	MOTIONTYPE_SELECT,		// セレクトモーション
	MOTYONTYPE_MAX,			// モーションの最大値
}MOTIONTYPE;				// モーションの種類

//-------------------------------------------------------------------
// 構造体の定義
//-------------------------------------------------------------------
typedef struct
{
	float fPosX;			// 位置X
	float fPosY;			// 位置Y
	float fPosZ;			// 位置Z
	float fRotX;			// 向きX
	float fRotY;			// 向きY
	float fRotZ;			// 向きZ
}KEY;						// キーの構造体

typedef struct
{
	int nFrame;				// フレーム数
	KEY aKey[20];			// 各モデルのキー要素
}KEY_INFO;					// キーの構造体

typedef struct
{
	bool bLoop;				// ループするかどうか
	int nNumKey;			// キーの総数
	KEY_INFO aKeyInfo[10];	// キー情報
}MOTION_INFO;				// モーションの構造体

#endif