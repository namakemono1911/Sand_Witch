//============================================
//  gate.cppのヘッダーファイル  (gate.h)
//
//  Author  Information
//  名前  石井  雄大
//  作成日   2017年04月21日
//  修正日   年月日
//  修正内容:
//
//
//============================================

#ifndef _GATE_H_
#define _GATE_H_
//============================================
//
//  インクルードファイル
//
//============================================
#include "main.h"
#include "polygon.h"

//============================================
//
//  マクロ定義
//
//============================================
#define GATE_NUM (4)	// 門の数
#define POSX (150.0f)

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
	bool        bCol;	// 衝突flag
	int nHeart;
	TEXTURE tex;
}GATE;


//============================================
//
//   プロトタイプ宣言
//
//============================================
void InitGate(void);
void UninitGate(void);
void UpdateGate(void);
void DrawGate(void);
GATE* GetGate(void);
void AddLife(int nIdx , int nLife);
#endif // _GATE_H_