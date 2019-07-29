//============================================
//  texture.cppのヘッダーファイル  (texture.h)
//
//  Author  Information
//  名前  小川将輝
//  作成日   2016年08月25日
//  修正日   年月日
//  修正内容:
//
//
//============================================

#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//============================================
//
//  インクルードファイル
//
//============================================

//============================================
//
//  構造体定義
//
//============================================
// テクスチャ情報の構造体
typedef struct
{
	char aName[128];		// 名前
	float fPosX;			// 位置X
	float fPosY;			// 位置Y
	float fWidth;			// 幅
	float fHeight;			// 高さ
	float fTposu;			// U値
	float fTposv;			// V値
	float fTwidth;			// UV値の幅
	float fTheight;			// UV値の高さ
	bool  bUse;				// 使用フラグ
	int   nLayer;           // 何番目に描画するか
}TEXTURE_a;

//============================================
//
//  プロトタイプ宣言
//
//============================================
HRESULT InitTexture(void);		// 初期化
void UninitTexture(void);		// 終了
void UpdateTexture(void);		// 更新
void DrawTexture(int nLayer);			// 描画
void SetTexture(int nTextureIndex, float fPosX, float fPosY, float fWidth, float fHeight,
	float fTposu, float fTposv, float fTwidth, float fTheight , int nLayer);					// テクスチャ設定
void OffTexture(int nIndex);													// 指定したポリゴンを破棄
void AllOffTexture(void);													// 指定したポリゴンを破棄
void MovePosTexture(int nIndex , float fMoveX , float fMoveY);					// テクスチャのポジション移動
void MoveUVTexture(int nIndex , float fMoveU , float fMoveV);					// テクスチャのUV移動
float GetTexturePosX(int nIndex);												// X座標の取得
float GetTexturePosY(int nIndex);												// Y座標の取得
void SetPosTexture(int nIndex , float fMoveX , float fMoveY);					// テクスチャのポジショ指定
void SetUVTexture(int nIndex , float fMoveU , float fMoveV);					// テクスチャのUV指定
void SetColorTexture(int nIndex , float r , float g , float b , float alpha);			// テクスチャの色指定
TEXTURE_a* GetTexture(int nIndex);
#endif _TEXTURE_H_