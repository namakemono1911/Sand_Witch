//============================================
//  NucleusBoss.cppのヘッダーファイル  (NucleusBoss.h)
//
//  Author  Information
//  名前  石井  雄大
//  作成日   2016年07月24日
//  修正日   年月日
//  修正内容:
//
//
//============================================

#ifndef _BOSSNUCLEUS_H_
#define _BOSSNUCLEUS_H_

//============================================
//
//   定数宣言
//
//============================================
#define MAX_BOSSNUCLEUS (100) // 最大ボスの弾数

//============================================
//
//   構造体
//
//============================================
/* ボスの弾の種類 */
typedef enum
{
	BOSSNUCLEUS_NONE,
	BOSSNUCLEUS_ONE,
	BOSSNUCLEUS_TWO,
	BOSSNUCLEUS_THREE,
	BOSSNUCLEUS_MAX
}BOSSNUCLEUS_TYPE;

/* ボスの弾構造体 */
typedef struct
{
	D3DXVECTOR2    fPos;    // 中心座標
	D3DXVECTOR2    fUV;     // UV座標
	float          fWidth;  // 幅
	float          fHeight; // 高さ
	int            nFlame;  // UVアニメーションの速さ調節
	bool           bUse;    // 使用フラグ
	int            nLife;   // 寿命
	bool           bDraw;   // 描画フラグ
	int            nDrawTime; // 描画時間
	BOSSNUCLEUS_TYPE       nType;   // 種類
}BOSSNUCLEUS;
//============================================
//
//   プロトタイプ宣言
//
//============================================
HRESULT InitNucleusBoss   (void);
void    UninitNucleusBoss (void);
void    UpdateNucleusBoss (void);
void    DrawNucleusBoss   (void);
int     SetNucleusBoss    (float fPosX , // 中心座標X
	float fPosY,					   // 中心座標Y
	float fWidth,					   // 幅
	float fHeught,					   // 高さ
	BOSSNUCLEUS_TYPE nType
	);
void SetPosNucleusBoss(int nIndex , D3DXVECTOR2 fPos);
void OffDrawNucleusBoss(int nIndex);
void OnDrawNucleusBoss(int nIndex , int nTime);
void ReleaseNucleusBoss(int nIdx);
void OffNucleusBoss(int nIndex);
BOSSNUCLEUS*    GetNucleusBoss    (void);
void AddDmgNucBoss(int damage, int num);

#endif //_NucleusBoss_H_