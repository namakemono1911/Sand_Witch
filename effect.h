//============================================
//  Effect.cppのヘッダーファイル  (Effect.h)
//
//  Author  Information
//  名前  石井  雄大
//  作成日   2016年07月24日
//  修正日   年月日
//  修正内容:
//
//
//============================================

#ifndef _EFECT_H_
#define _EFECT_H_

#include "polygon.h"

//============================================
//
//   定数宣言
//
//============================================
#define MAX_EFECT    (100)   // ノーツの最大数
#define EFECT_WIDTH  (100.0f) // ノーツの幅
#define EFECT_HEIGHT (100.0f) // ノーツの幅

//============================================
//
//   構造体
//
//============================================
/* ノーツの種類 */
typedef enum
{
	EFFECT_RECOVER,					// 門と城回復				門or城
	EFFECT_KILL,					// 必殺技が溜まる			門
	EFFECT_KILL_ON,					// 必殺技が溜まり切った時	ウィッチ(プレイヤー)
	EFFECT_MAGIC_ON_NORMAL_1,		// 魔法発動-1				敵
	EFFECT_MAGIC_ON_NORMAL_2,		// 魔法発動-2				敵
	EFFECT_MAGIC_ON_EXPLOSION_1,	// 魔法発動-爆発-1			敵
	EFFECT_MAGIC_ON_EXPLOSION_2,	// 魔法発動-爆発-2			敵
	EFFECT_MAGIC_ON_EXPLOSION_3,	// 魔法発動-爆発-3			敵
	EFFECT_MAX
}EFFECT_MODE;


/* ノーツ構造体 */
typedef struct
{
	bool bUse;
	EFFECT_MODE nMode;              // ノーツの種類
	int nAnimFlame;					// アニメーション間隔 計測係
	int nAnimFlameMax;					// アニメーション間隔
	int nAnimFlameBuf;					// アニメーション間隔 4番目用
	TEXTURE tex;
	POLYGON poly;
	float fAlpha;
	float fAlphaDif;
	bool bAnim;
}EFFECT;

//============================================
//
//   プロトタイプ宣言
//
//============================================
HRESULT InitEffect   (void);
void    UninitEffect (void);
void    UpdateEffect (void);
void    DrawEffect   (void);
void    SetEffect    (float fPosX ,	   // 中心座標X
	float fPosY,					   // 中心座標Y
	float fWidth,					   // 幅
	float fHeught,					   // 高さ
	EFFECT_MODE nMode				   // 種類
	);

#endif //_EFECT_H_