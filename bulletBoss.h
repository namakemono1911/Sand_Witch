//============================================
//  BulletBoss.cppのヘッダーファイル  (BulletBoss.h)
//
//  Author  Information
//  名前  石井  雄大
//  作成日   2016年07月24日
//  修正日   年月日
//  修正内容:
//
//
//============================================

#ifndef _BOSSBULLET_H_
#define _BOSSBULLET_H_

//============================================
//
//   定数宣言
//
//============================================
#define MAX_BOSSBULLET (100) // 最大ボスの弾数

//============================================
//
//   構造体
//
//============================================
/* ボスの弾の種類 */
typedef enum
{
	BOSSBULLET_NONE,
	BOSSBULLET_ONE,
	BOSSBULLET_TWO,
	BOSSBULLET_THREE,
	BOSSBULLET_MAX
}BOSSBULLET_TYPE;

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
	BOSSBULLET_TYPE       nType;   // 種類
}BOSSBULLET;
//============================================
//
//   プロトタイプ宣言
//
//============================================
HRESULT InitBulletBoss   (void);
void    UninitBulletBoss (void);
void    UpdateBulletBoss (void);
void    DrawBulletBoss   (void);
void    SetBulletBoss    (float fPosX , // 中心座標X
	float fPosY,					   // 中心座標Y
	float fWidth,					   // 幅
	float fHeught,					   // 高さ
	BOSSBULLET_TYPE nType
	);
BOSSBULLET*    GetBulletBoss    (void);
void	AddDmgBulletBoss(int numBullet, int damage);

#endif //_BulletBoss_H_