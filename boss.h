//============================================
//  Boss.cppのヘッダーファイル  (Boss.h)
//
//  Author  Information
//  名前  石井  雄大
//  作成日   2016年07月24日
//  修正日   年月日
//  修正内容:
//
//
//============================================

#ifndef _BOSS_H_
#define _BOSS_H_

//============================================
//
//   定数宣言
//
//============================================
#define MAX_BOSS    (4)   // ボスの最大数
#define BOSS_WIDTH  (100.0f) // ボスの幅
#define BOSS_HEIGHT (100.0f) // ボスの幅

#define LINE_OBJ_MAX (4) // １ラインのオブジェクトの最大数

//============================================
//
//   構造体
//
//============================================
/* ボスの種類 */
typedef enum
{
	BOSS_NONE = 0,
	BOSS_ONE,
	BOSS_TWO,
	BOSS_THREE,
	BOSS_MAX
}BOSS_MODE;

/* ボス構造体 */
typedef struct
{
	BOSS_MODE nMode;              // ボスの種類
	D3DXVECTOR2    fPos;           // 中心座標
	D3DXVECTOR2    fUV;            // UV座標
	float          fWidth;         // 幅
	float          fHeight;        // 高さ
	float          fFlame;         // UVアニメーションの速さ調節
	bool           bMoveFlag;      // 移動フラグ
	bool           bDrawFlag;      // 描画フラグ
	bool           bUse;           // 使用フラグ
	int            nNumHeart;     // 影の番号
	int            nLife;          // 体力
	int            nCntBullet;     // 弾の発射
	int            nCntBltTime;    // 弾を撃つ間隔
	D3DXVECTOR2    fSizeUV;        // UV幅
	int            nNumNucleus[4];    // 核の番号
	int            nNumNoMoveTime; // 移動しない
	int            nCntDamegeTime; // 攻撃間隔
	bool           bAttack;        // 攻撃フラグ
	int nBossMode;			// 0:ニュートラル , 1:攻撃 , 2混乱
	int nBossModeCount;	// 次のモーションまでのカウント
	int nBossMotionCount;	// 現在再生しているキー
}BOSS;
//============================================
//
//   プロトタイプ宣言
//
//============================================
HRESULT InitBoss   (void);
void    UninitBoss (void);
void    UpdateBoss (void);
void    DrawBoss   (void);
void    SetBoss    (float fPosX ,	   // 左上座標X
	float fPosY ,	   // 左上座標X
BOSS_MODE nMode				   // 種類
	);
BOSS*  GetBoss    (void);
void    AddDameageBoss(int nID , int nDamege);

#endif //_BOSS_H_