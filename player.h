//============================================
//  polygon.cppのヘッダーファイル  (polygon.h)
//
//  Author  Information
//  名前  石井  雄大
//  作成日   2016年05月31日
//  修正日   年月日
//  修正内容:
//
//
//============================================

#ifndef _POLYGON_H_
#define _POLYGON_H_
//============================================
//
//  マクロ定義
//
//============================================

//============================================
//
//  インクルードファイル
//
//============================================
#include "main.h"

//============================================
//
//  インクルードファイル
//
//============================================
typedef struct
{
	bool bUse;			// 使用
	int  nPos;			// 体力
	int  nZanki;		// 残機
	D3DXVECTOR3 fPos;	// 現在座標
	D3DXVECTOR3 fMove;	// 移動量
	D3DXVECTOR2 fSize;	// 幅、高さ
	int  nMovePos;		// 現段階の座標
}PLAYER;

#define PLAYER_POS_1 (SCREEN_HEIGHT / 100.0f * 23.6f + 15.0f)
#define PLAYER_POS_2 (SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT + 15.0f)
#define PLAYER_POS_3 (SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 2 + 15.0f)
#define PLAYER_POS_4 (SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 3 + 15.0f)
#define PLAYER_POS_5 (SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4 + 15.0f)
//============================================
//
//   プロトタイプ宣言
//
//============================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);

#endif