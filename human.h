//============================================
//  Human.cppのヘッダーファイル  (Human.h)
//
//  Author  Information
//  名前  石井  雄大
//  作成日   2016年07月24日
//  修正日   年月日
//  修正内容:
//
//
//============================================

#ifndef _HUMAN_H_
#define _HUMAN_H_

//============================================
//
//   定数宣言
//
//============================================
#define MAX_HUMAN    (100)   // 人の最大数
#define HUMAN_WIDTH  (100.0f) // 人の幅
#define HUMAN_HEIGHT (100.0f) // 人の幅

//============================================
//
//   構造体
//
//============================================
/* 人の種類 */
typedef enum
{
	HUMAN_NONE = 0,
	HUMAN_ONE,
	HUMAN_TWO,
	HUMAN_THREE,
	HUMAN_FOUR,
	HUMAN_FIVE,
	HUMAN_SIX,
	HUMAN_SEVEN,
	HUMAN_SEVEN_2,
	HUMAN_MAX
}HUMAN_MODE;

/* 人構造体 */
typedef struct
{
	HUMAN_MODE nMode;              // 人の種類
	D3DXVECTOR2    fPos;           // 中心座標
	D3DXVECTOR2    fUV;            // UV座標
	float          fWidth;         // 幅
	float          fHeight;        // 高さ
	float          fFlame;         // UVアニメーションの速さ調節
	int            nPoint;         // 得点
	bool           bMoveFlag;      // 移動フラグ
	bool           bDrawFlag;      // 描画フラグ
	bool           bUse;           // 使用フラグ
	int            nNumShadow;     // 影の番号
	int            nLife;          // 体力
	int            nParticleFlame; // パーティクルのでるフレーム
	int            nNumWarning;    // ワーニングの番号
	int            nCntDamegeTime; // 攻撃時間
	bool           bAttack;        // 攻撃フラグ
	bool           bUpdateFlag;    // 更新フラグ
	int            nCntAnim;         // 得点

	float fAlpha;
	bool bAlpha;
}HUMAN;
//============================================
//
//   プロトタイプ宣言
//
//============================================
HRESULT InitHuman   (void);
void    UninitHuman (void);
void    UpdateHuman (void);
void    DrawHuman   (void);
void    SetHuman    (float fPosX ,	   // 左上座標X
	float fPosY,					   // 左上座標Y
	float fWidth,					   // 幅
	float fHeught,					   // 高さ
	HUMAN_MODE nMode				   // 種類
	);
HUMAN*  GetHuman    (void);
bool    CheckHumanTime(void);
void    AddDameageHuman(int nID , int nDamege);
D3DXVECTOR3    GetHumanPos(int n);
#endif //_HUMAN_H_