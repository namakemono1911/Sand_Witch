//============================================
//  Heart.cppのヘッダーファイル  (Heart.h)
//
//  Author  Information
//  名前  石井  雄大
//  作成日   2016年07月24日
//  修正日   年月日
//  修正内容:
//
//
//============================================

#ifndef _HEART_H_
#define _HEART_H_
#include "main.h"

//============================================
//
//   定数宣言
//
//============================================
#define MAX_HEART    (100)   // ハートの最大数
#define HEART_WIDTH  (20.0f) // ハートの幅
#define HEART_HEIGHT (100.0f) // ハートの幅

//============================================
//
//   構造体
//
//============================================
/* ハート構造体 */
typedef struct
{
	D3DXVECTOR2    fPos;           // 中心座標
	D3DXVECTOR2    fUV;            // UV座標
	D3DXVECTOR2    fUVSize;            // UV座標
	float          fWidth;         // 幅
	float          fHeight;        // 高さ
	bool           bUse;           // 使用フラグ
}HEART;
//============================================
//
//   プロトタイプ宣言
//
//============================================
HRESULT InitHeart   (void);
void    UninitHeart (void);
void    UpdateHeart (void);
void    DrawHeart   (void);
int     SetHeart    (float fPosX ,	   // 左上座標X
	float fPosY,					   // 左上座標Y
	float fWidth,					   // 幅
	float fHeught,					   // 高さ
	int nHp
	);
HEART*  GetHeart    (void);
void SetPosHeart (int nIdx , D3DXVECTOR2 fPos);	// 座標
void SetUVSizeHeart(int nIdx , int nLife);	// ライフからuv計算
void OffHeart(int nIdx);
#endif //_HEART_H_