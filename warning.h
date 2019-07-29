//============================================
//  Warning.cのヘッダーファイル  (Warning.h)
//
//  Author  InformaWarningon
//  名前  石井  雄大
//  作成日   2016年06月29日
//  修正日   年月日
//  修正内容:
//
//
//============================================

#ifndef _WARNING_H_
#define _WARNING_H_
//============================================
//
//   プロトタイプ宣言
//
//============================================
/*ワーニングタイプ列挙型*/
typedef enum 
{
	WARNING_NORMAL = 0,
	WARNING_BOSS
}WARNING_TYPE;
/* ワーニング構造体 */
typedef struct
{
	bool bUse;            // 使用フラグ
	D3DXVECTOR2 fPos;     // 場所
	bool bFlash;          // 点滅フラグ
	int  nMaxFlash;       // 点滅切り替えフレーム(何フレームでαが0になるか)
	int  nCntflash;       // 点滅カウント(今何フレームか)
	float fAlpha;         // α値
	WARNING_TYPE type;
}WARNING;
//============================================
//
//   プロトタイプ宣言
//
//============================================
HRESULT InitWarning(void);
void UninitWarning(void);
void UpdateWarning(void);
void DrawWarning(void);
int  SetWarning(float fPosY , WARNING_TYPE type); // ワーニングをセットする
void OffWarning(int nIndex);
#endif//_Warning_H_