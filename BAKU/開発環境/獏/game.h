////////////////////////////////////////////////////////////////////////////////
//
//Contents	: ゲーム画面の処理 [game.h]
//Author	: ShotaFuruichi
//Since		: 2020/10/30
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"

////////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
////////////////////////////////////////////////////////////////////////////////
HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
#endif