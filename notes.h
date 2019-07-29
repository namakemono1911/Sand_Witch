//============================================
//  Notes.cppのヘッダーファイル  (Notes.h)
//
//  Author  Information
//  名前  石井  雄大
//  作成日   2016年07月24日
//  修正日   年月日
//  修正内容:
//
//
//============================================

#ifndef _NOTES_H_
#define _NOTES_H_

//============================================
//
//   定数宣言
//
//============================================
#define MAX_NOTES    (100)   // ノーツの最大数
#define NOTES_WIDTH  (100.0f) // ノーツの幅
#define NOTES_HEIGHT (100.0f) // ノーツの幅

#define LINE_OBJ_MAX (4) // １ラインのオブジェクトの最大数

#define LINE_FD (SCREEN_HEIGHT / 3  - (SCREEN_HEIGHT / 100 * 6.0f))
#define LINE_HEIGHT (SCREEN_HEIGHT / 100 * 18.0f)
#define LINE_ONE	(LINE_FD)
#define LINE_TWO	(LINE_FD + LINE_HEIGHT)
#define LINE_THREE	(LINE_FD + LINE_HEIGHT * 2)
#define LINE_FOUR	(LINE_FD + LINE_HEIGHT * 3)

//============================================
//
//   構造体
//
//============================================
/* ノーツの種類 */
typedef enum
{
	NOTES_NONE = 0,
	NOTES_ONE,
	NOTES_TWO,
	NOTES_THREE,
	NOTES_FOUR,
	NOTES_FIVE,
	NOTES_SIX,
	NOTES_SEVEN,
	NOTES_SEVEN_2,
	NOTES_MAX
}NOTES_MODE;

/* ノーツ構造体 */
typedef struct
{
	NOTES_MODE nMode;              // ノーツの種類
	D3DXVECTOR2    fPos;           // 中心座標
	D3DXVECTOR2    fUV;            // UV座標
	float          fWidth;         // 幅
	float          fHeight;        // 高さ
	float          fFlame;         // UVアニメーションの速さ調節
	int            nPoint;         // 得点
	bool           bMoveFlag;      // 移動フラグ
	bool           bDrawFlag;      // 描画フラグ
	bool           bUse;           // 使用フラグ
	int            nNumHp;     // 影の番号
	int            nLife;          // 体力
	int            nParticleFlame; // パーティクルのでるフレーム
	int            nNumWarning;    // ワーニングの番号
	int            nCntDamegeTime; // 攻撃時間
	bool           bAttack;        // 攻撃フラグ
	bool           bUpdateFlag;    // 更新フラグ
	int nNumLife;					// 元の体力

	int nTimeAttack;

	int nAnimTime;	// アニメーションカウント

	int nStopTime;		// 止まるカウンター
	bool bStop;			// 止まるフラグ
	int nStopDamage;	// 止まった末のダメージ

}NOTES;
//============================================
//
//   プロトタイプ宣言
//
//============================================
HRESULT InitNotes   (void);
void    UninitNotes (void);
void    UpdateNotes (void);
void    DrawNotes   (void);
void    SetNotes    (float fPosX ,	   // 左上座標X
	float fPosY,					   // 左上座標Y
	float fWidth,					   // 幅
	float fHeught,					   // 高さ
	NOTES_MODE nMode				   // 種類
	);
NOTES*  GetNotes    (void);
bool    CheckEnemyTime(void);
void    AddDameage(int nID , int nDamege);
D3DXVECTOR3    GetEnemyPos(int n);
int GetTimeGameNow();
bool GetZeroNotes(void);	// 敵がすべてfalseならtrue,そうでないならfalseを返す

void StopDamage(int nIndex , int nDamage);

#endif //_NOTES_H_