//============================================
//  テクスチャ関数  (texture.cpp)
//
//  Author  Information
//  名前  小川将輝
//  作成日   2016年08月25日
//  修正日   2106年08月28日
//  修正内容: 石井 : インデックスを指定して消す関数追加
//  修正内容: 石井 : インデックスを指定してpos,uvを動かす関数追加
//  修正内容: 石井 : レイヤを指定してdraw
//
//
//============================================


//============================================
//
//  インクルードファイル
//
//============================================
#include "main.h"
#include "texture.h"

//============================================
//
//  マクロ定義
//
//============================================
#define MAX_TEXTURE (13)								// テクスチャの最大数
#define TEXTURENAME001 "data/texture/GAME/UI/red.png"			//  タイトル文字
#define TEXTURENAME002 "data/texture/GAME/UI/renga.png"			//  タイトル文字
#define TEXTURENAME003 "data/texture/GAME/UI/renga.png"			//  タイトル文字
#define TEXTURENAME004 "data/texture/GAME/UI/renga.png"			//  タイトル文字
#define TEXTURENAME005 "data/texture/GAME/UI/renga.png"			//  タイトル文字
#define TEXTURENAME006 "data/texture/GAME/UI/renga.png"			//  タイトル文字
#define TEXTURENAME007 "data/texture/charctor01.png"			//  タイトル文字
#define TEXTURENAME008 "data/texture/ui_a.png"			//  a
#define TEXTURENAME009 "data/texture/ui_b.png"			//  b
#define TEXTURENAME010 "data/texture/ui_x.png"			//  x
#define TEXTURENAME011 "data/texture/ui_y.png"			//  y
#define TEXTURENAME012 "data/texture/GAME/UI/resultBar.png"		//  バー
#define TEXTURENAME013 "data/texture/GAME/UI/resultBarOn.png"	//  バーン

//============================================
//
//  グローバル変数
//
//============================================
LPDIRECT3DTEXTURE9 g_pTexture[MAX_TEXTURE] = {};		// ポインタ型 テクスチャインターフェイス
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffer = NULL;			// ポインタ型 頂点バッファ管理インターフェイス

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// ここで読み込むテクスチャの名前を書く
///////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXTURE_a g_Tex[MAX_TEXTURE] = {							// テクスチャ情報の構造体生成
	{TEXTURENAME001},
	{TEXTURENAME002},
	{TEXTURENAME003},
	{TEXTURENAME004},
	{TEXTURENAME005},
	{TEXTURENAME006},
	{TEXTURENAME007},
	{TEXTURENAME008},
	{TEXTURENAME009},
	{TEXTURENAME010},
	{TEXTURENAME011},
	{TEXTURENAME012},
	{TEXTURENAME013}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//============================================
//
//  プロトタイプ宣言
//
//============================================
void MakeVertexTexture(LPDIRECT3DDEVICE9 pDevice);			// 頂点作成
void SetVertexTexture(int nTextureIndex);					// 頂点設定

//============================================
//
//  名前  InitTextuer関数
//  引数
//  戻り値
//  説明
//
//============================================
HRESULT InitTexture(void)
{
	int nCntTex = 0;			// カウンタ

	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	// テクスチャ情報を初期化
	for (nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		g_Tex[nCntTex].fPosX    = 0.0f;		// 座標X
		g_Tex[nCntTex].fPosY    = 0.0f;		// 座標Y
		g_Tex[nCntTex].fWidth   = 0.0f;		// 幅
		g_Tex[nCntTex].fHeight  = 0.0f;		// 高さ
		g_Tex[nCntTex].fTposu   = 0.0f;		// Uの値
		g_Tex[nCntTex].fTposv   = 0.0f;		// Vの値
		g_Tex[nCntTex].fTwidth  = 0.0f;		// UV値の幅
		g_Tex[nCntTex].fTheight = 0.0f;		// UV値の高さ
		g_Tex[nCntTex].bUse = false;		// 使用フラグ
	}

	// 頂点の作成
	MakeVertexTexture(pDevice);

	// テクスチャ読み込み
	for (nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		// テクスチャ読み込み
		if (FAILED(D3DXCreateTextureFromFile(
			pDevice,						// デバイスに頼む
			g_Tex[nCntTex].aName,			// テクスチャの名前
			&g_pTexture[nCntTex])))			// テクスチャの呼び込み 
		{
			// 読み込みに失敗していたら
			//MessageBox(NULL, "テクスチャの読み込みに失敗しました。", "エラー", MB_OK | MB_ICONHAND | MB_DEFBUTTON1);
			//DebugMsgBox(_TEXT("%d番目のテクスチャが読み込みに失敗しました。()") , nCntTex + 1);
		}
	}

	return S_OK;
}


//============================================
//
//  名前  UninitTextuer関数
//  引数
//  戻り値
//  説明
//
//============================================
void UninitTexture(void)
{
	int nCntTex = 0;		// カウンタ

	// テクスチャインターフェイス
	for(int i = 0; i< MAX_TEXTURE; i++)
	{
		SAFE_RELEASE(g_pTexture[i]);
	}

	// 頂点バッファ管理インターフェイス
	if (g_pVtxBuffer != NULL)
	{
		g_pVtxBuffer->Release();			// 頂点バッファ管理インターフェイスの解放
		g_pVtxBuffer = NULL;				// アドレスをNULLにする
	}

	// テクスチャ情報を初期化
	for (nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		g_Tex[nCntTex].fPosX = 0;		// 座標X
		g_Tex[nCntTex].fPosY = 0;		// 座標Y
		g_Tex[nCntTex].fWidth = 0;		// 幅
		g_Tex[nCntTex].fHeight = 0;		// 高さ
		g_Tex[nCntTex].fTposu = 0;		// Uの値
		g_Tex[nCntTex].fTposv = 0;		// Vの値
		g_Tex[nCntTex].fTwidth = 0;		// UV値の幅
		g_Tex[nCntTex].fTheight = 0;	// UV値の高さ
		g_Tex[nCntTex].bUse = false;	// 使用フラグ
	}
}

//============================================
//
//  名前  UpdateTextuer関数
//  引数
//  戻り値
//  説明
//
//============================================
void UpdateTexture(void)
{

}

//============================================
//
//  名前  DrawTextuer関数
//  引数
//  戻り値
//  説明
//
//============================================
void DrawTexture(int nLayer)
{
	int nCntTexture = 0;			// カウンタ

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	// プリミティブの設定
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffer,
		0,								// オフセット(単位バイト)
		sizeof(VERTEX2D));				// ストライド量。頂点データ1個分のサイズ

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D | D3DFVF_TEX1);

	// 描画
	for (nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
	{
		// 使用フラグがONなら描画
		if (g_Tex[nCntTexture].bUse == true && g_Tex[nCntTexture].nLayer == nLayer)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTexture[nCntTexture]);

			// プリミティブの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// プリミティブの種類
				nCntTexture * 4,				// オフセット(頂点数)
				NUM_POLYGON);					// プリミティブ数
		}
	}
}

//============================================
//
//  名前  SetTexture関数
//  引数  インデックス, 座標X, 座標Y, 幅, 高さ, Uの値, Vの値, UVの幅, UVの高さ
//  戻り値
//  説明
//
//============================================
void SetTexture(int nTextureIndex, float fPosX, float fPosY, float fWidth, float fHeight,
	float fTposu, float fTposv, float fTwidth, float fTheight , int nLayer)
{
	// テクスチャ情報を設定
	g_Tex[nTextureIndex].fPosX    = fPosX;		// 座標X
	g_Tex[nTextureIndex].fPosY    = fPosY;		// 座標Y
	g_Tex[nTextureIndex].fWidth   = fWidth;		// 幅
	g_Tex[nTextureIndex].fHeight  = fHeight;	// 高さ
	g_Tex[nTextureIndex].fTposu   = fTposu;		// Uの値
	g_Tex[nTextureIndex].fTposv   = fTposv;		// Vの値
	g_Tex[nTextureIndex].fTwidth  = fTwidth;	// UV値の幅
	g_Tex[nTextureIndex].fTheight = fTheight;	// UV値の高さ
	g_Tex[nTextureIndex].bUse     = true;		// 使用フラグオン
	g_Tex[nTextureIndex].nLayer = nLayer;       // 何番目のレイヤーか

	// 頂点設定
	SetVertexTexture(nTextureIndex);
}

//============================================
//
//  名前  MakeVertexTexture関数
//  引数
//  戻り値
//  説明
//
//============================================
void MakeVertexTexture(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX2D) * (MAX_TEXTURE * NUM_VERTEX),		// 頂点バッファのサイズ。動的メモリ確保
		D3DUSAGE_WRITEONLY,									// 書き込みのみ。最速でできる
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,									// メモリ管理方法(デバイスにおまかせ)
		&g_pVtxBuffer,
		NULL);
}

//============================================
//
//  名前  SetVertexTexture関数
//  引数
//  戻り値
//  説明
//
//============================================
void SetVertexTexture(int nTextureIndex)
{
	int nCntTexture = 0;		// カウンタ
	 VERTEX2D* pVtx;			// 仮想アドレスのポインタ

	// 頂点バッファをロックして仮想アドレスを取得する；
	g_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定(2D座標・右回り ZかNの順番)
	pVtx[4 * nTextureIndex + 0].pos = D3DXVECTOR3(g_Tex[nTextureIndex].fPosX, g_Tex[nTextureIndex].fPosY, 0.0f);							// 引数はX,Y,Z
	pVtx[4 * nTextureIndex + 1].pos = D3DXVECTOR3(g_Tex[nTextureIndex].fPosX + g_Tex[nTextureIndex].fWidth, g_Tex[nTextureIndex].fPosY, 0.0f);
	pVtx[4 * nTextureIndex + 2].pos = D3DXVECTOR3(g_Tex[nTextureIndex].fPosX, g_Tex[nTextureIndex].fPosY + g_Tex[nTextureIndex].fHeight, 0.0f);
	pVtx[4 * nTextureIndex + 3].pos = D3DXVECTOR3(g_Tex[nTextureIndex].fPosX + g_Tex[nTextureIndex].fWidth, g_Tex[nTextureIndex].fPosY + g_Tex[nTextureIndex].fHeight, 0.0f);

	// テクスチャのUV値設定
	pVtx[4 * nTextureIndex + 0].tex = D3DXVECTOR2(g_Tex[nTextureIndex].fTposu, g_Tex[nTextureIndex].fTposv);								// 引数はU,V
	pVtx[4 * nTextureIndex + 1].tex = D3DXVECTOR2(g_Tex[nTextureIndex].fTposu + g_Tex[nTextureIndex].fTwidth, g_Tex[nTextureIndex].fTposv);
	pVtx[4 * nTextureIndex + 2].tex = D3DXVECTOR2(g_Tex[nTextureIndex].fTposu, g_Tex[nTextureIndex].fTposv + g_Tex[nTextureIndex].fTheight);
	pVtx[4 * nTextureIndex + 3].tex = D3DXVECTOR2(g_Tex[nTextureIndex].fTposu + g_Tex[nTextureIndex].fTwidth, g_Tex[nTextureIndex].fTposv + g_Tex[nTextureIndex].fTheight);

	// rhwと色の設定
	for (nCntTexture = 0; nCntTexture < 4; nCntTexture++) {
		// rhwの設定
		pVtx[4 * nTextureIndex + nCntTexture].rhw = 1.0f;			// 必ず1.0fを入れる
		// 頂点カラーの設定(0～255の整数値)
		pVtx[4 * nTextureIndex + nCntTexture].color = D3DCOLOR_RGBA(255, 255, 255, 255);		// アルファの値はとりあえず255
	}

	// 頂点バッファアンロック
	g_pVtxBuffer->Unlock();

}

//============================================
//
//  名前  OffTexture関数
//  引数
//  戻り値
//  説明
//
//============================================
void OffTexture(int nIndex)
{
	if(g_Tex[nIndex].bUse == true)
	{
		g_Tex[nIndex].bUse = false;
	} // EO if
}

//============================================
//
//  名前  MovePosTexture関数
//  引数
//  戻り値
//  説明
//
//============================================
void MovePosTexture(int nIndex , float fMoveX , float fMoveY) // テクスチャのポジション移動
{
	// テクスチャ情報を設定
	g_Tex[nIndex].fPosX += fMoveX;			// 座標X
	g_Tex[nIndex].fPosY += fMoveY;			// 座標Y

	int nCntTexture = 0;		// カウンタ
	VERTEX2D* pVtx;			// 仮想アドレスのポインタ

	// 頂点バッファをロックして仮想アドレスを取得する；
	g_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定(2D座標・右回り ZかNの順番)
	pVtx[4 * nIndex + 0].pos = D3DXVECTOR3(g_Tex[nIndex].fPosX,  g_Tex[nIndex].fPosY, 0.0f);							// 引数はX,Y,Z
	pVtx[4 * nIndex + 1].pos = D3DXVECTOR3(g_Tex[nIndex].fPosX + g_Tex[nIndex].fWidth, g_Tex[nIndex].fPosY, 0.0f);
	pVtx[4 * nIndex + 2].pos = D3DXVECTOR3(g_Tex[nIndex].fPosX,  g_Tex[nIndex].fPosY + g_Tex[nIndex].fHeight, 0.0f);
	pVtx[4 * nIndex + 3].pos = D3DXVECTOR3(g_Tex[nIndex].fPosX + g_Tex[nIndex].fWidth, g_Tex[nIndex].fPosY + g_Tex[nIndex].fHeight, 0.0f);

	// 頂点バッファアンロック
	g_pVtxBuffer->Unlock();
} // EO MovePosTexture

//============================================
//
//  名前  MoveUVTexture関数
//  引数
//  戻り値
//  説明
//
//============================================
void MoveUVTexture(int nIndex , float fMoveU , float fMoveV) // テクスチャのUV移動
{
	// テクスチャ情報を設定
	g_Tex[nIndex].fTposu += fMoveU;			// 座標Y
	g_Tex[nIndex].fTposv += fMoveV;			// 座標Y

	int nCntTexture = 0;		// カウンタ
	 VERTEX2D* pVtx;			// 仮想アドレスのポインタ

	// 頂点バッファをロックして仮想アドレスを取得する；
	g_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャのUV値設定
	pVtx[4 * nIndex + 0].tex = D3DXVECTOR2(g_Tex[nIndex].fTposu,  g_Tex[nIndex].fTposv);
	pVtx[4 * nIndex + 1].tex = D3DXVECTOR2(g_Tex[nIndex].fTposu + g_Tex[nIndex].fTwidth, g_Tex[nIndex].fTposv);
	pVtx[4 * nIndex + 2].tex = D3DXVECTOR2(g_Tex[nIndex].fTposu,  g_Tex[nIndex].fTposv + g_Tex[nIndex].fTheight);
	pVtx[4 * nIndex + 3].tex = D3DXVECTOR2(g_Tex[nIndex].fTposu + g_Tex[nIndex].fTwidth, g_Tex[nIndex].fTposv + g_Tex[nIndex].fTheight);

	// 頂点バッファアンロック
	g_pVtxBuffer->Unlock();
} // EO MoveUVTexture

//============================================
//
//  名前  GetTexturePosX関数
//  引数
//  戻り値
//  説明
//
//============================================
float GetTexturePosX(int nIndex) // X座標の取得
{

	return g_Tex[nIndex].fPosX;

} // EO GetTexturePosX
//============================================
//
//  名前  GetTexturePosY関数
//  引数
//  戻り値
//  説明
//
//============================================
float GetTexturePosY(int nIndex) // Y座標の取得
{

	return g_Tex[nIndex].fPosY;

} // EO GetTexturePosY

//============================================
//
//  名前  MovePosTexture関数
//  引数
//  戻り値
//  説明
//
//============================================
void SetPosTexture(int nIndex , float fMoveX , float fMoveY) // テクスチャのポジション移動
{
	// テクスチャ情報を設定
	g_Tex[nIndex].fPosX = fMoveX;			// 座標X
	g_Tex[nIndex].fPosY = fMoveY;			// 座標Y

	int nCntTexture = 0;		// カウンタ
	VERTEX2D* pVtx;			// 仮想アドレスのポインタ

	// 頂点バッファをロックして仮想アドレスを取得する；
	g_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定(2D座標・右回り ZかNの順番)
	pVtx[4 * nIndex + 0].pos = D3DXVECTOR3(g_Tex[nIndex].fPosX,  g_Tex[nIndex].fPosY, 0.0f);							// 引数はX,Y,Z
	pVtx[4 * nIndex + 1].pos = D3DXVECTOR3(g_Tex[nIndex].fPosX + g_Tex[nIndex].fWidth, g_Tex[nIndex].fPosY, 0.0f);
	pVtx[4 * nIndex + 2].pos = D3DXVECTOR3(g_Tex[nIndex].fPosX,  g_Tex[nIndex].fPosY + g_Tex[nIndex].fHeight, 0.0f);
	pVtx[4 * nIndex + 3].pos = D3DXVECTOR3(g_Tex[nIndex].fPosX + g_Tex[nIndex].fWidth, g_Tex[nIndex].fPosY + g_Tex[nIndex].fHeight, 0.0f);

	// 頂点バッファアンロック
	g_pVtxBuffer->Unlock();
} // EO MovePosTexture

//============================================
//
//  名前  MoveUVTexture関数
//  引数
//  戻り値
//  説明
//
//============================================
void SetUVTexture(int nIndex , float fMoveU , float fMoveV) // テクスチャのUV移動
{
	// テクスチャ情報を設定
	g_Tex[nIndex].fTposu = fMoveU;			// 座標Y
	g_Tex[nIndex].fTposv = fMoveV;			// 座標Y

	int nCntTexture = 0;		// カウンタ
	 VERTEX2D* pVtx;			// 仮想アドレスのポインタ

	// 頂点バッファをロックして仮想アドレスを取得する；
	g_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャのUV値設定
	pVtx[4 * nIndex + 0].tex = D3DXVECTOR2(g_Tex[nIndex].fTposu,  g_Tex[nIndex].fTposv);
	pVtx[4 * nIndex + 1].tex = D3DXVECTOR2(g_Tex[nIndex].fTposu + g_Tex[nIndex].fTwidth, g_Tex[nIndex].fTposv);
	pVtx[4 * nIndex + 2].tex = D3DXVECTOR2(g_Tex[nIndex].fTposu,  g_Tex[nIndex].fTposv + g_Tex[nIndex].fTheight);
	pVtx[4 * nIndex + 3].tex = D3DXVECTOR2(g_Tex[nIndex].fTposu + g_Tex[nIndex].fTwidth, g_Tex[nIndex].fTposv + g_Tex[nIndex].fTheight);

	// 頂点バッファアンロック
	g_pVtxBuffer->Unlock();
} // EO MoveUVTexture

//============================================
//
//  名前  MovePosTexture関数
//  引数
//  戻り値
//  説明
//
//============================================
void SetColorTexture(int nIndex , float r , float g , float b , float alpha) // テクスチャのポジション移動
{
	VERTEX2D* pVtx;			// 仮想アドレスのポインタ

	// 頂点バッファをロックして仮想アドレスを取得する；
	g_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定(2D座標・右回り ZかNの順番)
	pVtx[4 * nIndex + 0].color = D3DXCOLOR(r, g , b , alpha);							// 引数はX,Y,Z
	pVtx[4 * nIndex + 1].color = D3DXCOLOR(r, g , b , alpha);
	pVtx[4 * nIndex + 2].color = D3DXCOLOR(r, g , b , alpha);
	pVtx[4 * nIndex + 3].color = D3DXCOLOR(r, g , b , alpha);

	// 頂点バッファアンロック
	g_pVtxBuffer->Unlock();
} // EO MovePosTexture

TEXTURE_a* GetTexture(int nIndex)
{
	return &g_Tex[nIndex];
}

void AllOffTexture(void)
{
	int nCntTex = 0;
	// テクスチャ情報を初期化
	for (nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		g_Tex[nCntTex].fPosX = 0;		// 座標X
		g_Tex[nCntTex].fPosY = 0;		// 座標Y
		g_Tex[nCntTex].fWidth = 0;		// 幅
		g_Tex[nCntTex].fHeight = 0;		// 高さ
		g_Tex[nCntTex].fTposu = 0;		// Uの値
		g_Tex[nCntTex].fTposv = 0;		// Vの値
		g_Tex[nCntTex].fTwidth = 0;		// UV値の幅
		g_Tex[nCntTex].fTheight = 0;	// UV値の高さ
		g_Tex[nCntTex].bUse = false;	// 使用フラグ
	}
} // EO AllOffTexture
