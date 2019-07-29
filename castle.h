//============================================
//  castle.cppのヘッダーファイル  (castle.h)
//
//  Author  Information
//  名前  石井  雄大
//  作成日   2017年04月21日
//  修正日   年月日
//  修正内容:
//
//
//============================================

#ifndef _CASTLE_H_
#define _CASTLE_H_
//============================================
//
//  インクルードファイル
//
//============================================
#include "main.h"

//============================================
//
//  マクロ定義
//
//============================================
#define CASTLE_NUM (1)	// 門の数
#define CASTLE_POSX (SCREEN_WIDTH / 100.0f * 54)
#define CASTLE_POSY (SCREEN_HEIGHT / 100.0f * 6)
#define CASTLE_WIDTH (SCREEN_WIDTH / 100.0f * 8)
#define CASTLE_HEIGHT (SCREEN_HEIGHT / 100.0f * 10)

//============================================
//
//  構造体
//
//============================================
// 門構造体
typedef struct
{
	bool bUse;	// 使用フラグ
	D3DXVECTOR3 fPos;	// 座標
	D3DXVECTOR2 fSize;	// 幅高さ
	D3DXVECTOR2 fUV;	// UV
	int         nHp;	// HP
}CASTLE;


//============================================
//
//   プロトタイプ宣言
//
//============================================
void InitCastle(int nStage);
void UninitCastle(void);
void UpdateCastle(void);
void DrawCastle(void);
void AddDamegeCastle(int nDamege);
int GetCastleHp(void);
#endif // _CASTLE_H_