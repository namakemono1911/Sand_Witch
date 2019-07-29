//-------------------------------------------------------
//	ナンバー処理[number.cpp]
//	Author : KAZUNORI MARUHASHI
//	
//-------------------------------------------------------

//-------------------------------------------------------
//	更新履歴
//-------------------------------------------------------
/*
	2017/02/22
		作成


*/
//-------------------------------------------------------
//	インクルードファイル
//-------------------------------------------------------
#include "main.h"		//メインヘッダ
#include "number.h"
#include <math.h>

//-------------------------------------------------------
//	マクロ定義
//-------------------------------------------------------
#define NUMBER_TEXTURENAME "data/TEXTURE/number.png"		//テクスチャアドレス

//-------------------------------------------------------
//	構造体定義
//-------------------------------------------------------

//-------------------------------------------------------
//	プロトタイプ宣言
//-------------------------------------------------------
HRESULT MakeVertexNumber(LPDIRECT3DDEVICE9 pDevice);
void SetNumberPos(float fPosX, float fPosY);

//-------------------------------------------------------
//	グローバル変数
//-------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferNumber = NULL;

int g_iNumber;

//-------------------------------------------------------
//	ポリゴン初期化処理
//-------------------------------------------------------
void InitNumber(void)
{
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスの取得

	//頂点の設定
	if(FAILED(MakeVertexNumber(pDevice)))
	{
		MessageBox(NULL, "頂点バッファの設定に失敗しました。", " ", MB_OK);
		return;
	}

	//ターゲット数初期化
	g_iNumber = 0;
}

//-------------------------------------------------------
//	ポリゴン終了処理
//-------------------------------------------------------
void UninitNumber(void)
{
	if(g_pVtxBufferNumber != NULL)
	{
		g_pVtxBufferNumber -> Release();
		g_pVtxBufferNumber = NULL;
	}
}

//-------------------------------------------------------
//	ポリゴン更新処理
//-------------------------------------------------------
void UpdateNumber(void)
{

}

//-------------------------------------------------------
//	頂点の作成
//-------------------------------------------------------
HRESULT MakeVertexNumber(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX2D* pVtx;	//仮想アドレス取得用ポインタ

	if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX2D)*8,	//確保したい頂点バッファの数＊頂点数
								  D3DUSAGE_WRITEONLY,	//確保した後中を見ることはできない
								  FVF_VERTEX_2D,		//一応書かずとも平気
								  D3DPOOL_MANAGED,		//メモリ管理をどうするか(これはお任せ)
								  &g_pVtxBufferNumber,
								  NULL)))
	{
		return E_FAIL;
	}

	//仮想アドレスを取得する
	g_pVtxBufferNumber -> Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定（x, y, z）
	pVtx[0].pos = D3DXVECTOR3(0.0f-0.5f, 0.0f-0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH-0.5f, 0.0f-0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f-0.5f, SCREEN_HEIGHT-0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH-0.5f, SCREEN_HEIGHT-0.5f, 0.0f);

	//rhwの設定(必ず1.0f)
	pVtx[0].rhw =
	pVtx[1].rhw =
	pVtx[2].rhw = 
	pVtx[3].rhw = 1.0f;

	//カラーの設定
	pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ―座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBufferNumber -> Unlock();

	return S_OK;
}

void DrawNumber(int iNumber, int iDigit, D3DXVECTOR2 Pos, D3DXVECTOR2 Size, float fMargin, LPDIRECT3DTEXTURE9 pTexture)
{
	
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスの取得
	
	pDevice ->SetStreamSource(0, 
							  g_pVtxBufferNumber,
							  0,					//オフセット
							  sizeof(VERTEX2D));		//ストライド量
	

	//頂点フォーマットの設定
	pDevice -> SetFVF(FVF_VERTEX_2D | D3DFVF_TEX1);

	pDevice -> SetTexture(0, pTexture);

	int iValue = iNumber;
	int iDrawNumber = 0;

	for(int iAllNumber = 0; iAllNumber < iDigit; iAllNumber++){
		iDrawNumber = iValue % 10;
		iValue *= 0.1f;

		SetNumber(iDrawNumber, Pos - D3DXVECTOR2(fMargin * iAllNumber, 0.0f), Size);

		//プリミティブの描画
		pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
								 0,					//オフセット(頂点数)
								 4);			//プリミティブ数
		//整数が存在しない場合
		if(iValue < 1){
			break;
		}
	}
}

void DrawNumberFloat(float iNumber, int iDigit, int fFloatDigit, D3DXVECTOR2 Pos, D3DXVECTOR2 Size, float fMargin, LPDIRECT3DTEXTURE9 pTexture)
{
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスの取得
	VERTEX2D* pVtx;	//仮想アドレス取得用ポインタ

	//整数部の描画
	DrawNumber((int)iNumber, iDigit, Pos, Size, fMargin, pTexture);

	//===== 小数点の描画 =====//

	//仮想アドレスを取得する
	g_pVtxBufferNumber -> Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定（x, y, z）
	pVtx[0].pos = D3DXVECTOR3(Pos.x + fMargin - Size.x * 0.5f, Pos.y - Size.y * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Pos.x + fMargin + Size.x * 0.5f, Pos.y - Size.y * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Pos.x + fMargin - Size.x * 0.5f, Pos.y + Size.y * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Pos.x + fMargin + Size.x * 0.5f, Pos.y + Size.y * 0.5f, 0.0f);

	//テクスチャ―座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.5f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	g_pVtxBufferNumber -> Unlock();

	pDevice ->SetStreamSource(0, 
							  g_pVtxBufferNumber,
							  0,					//オフセット
							  sizeof(VERTEX2D));		//ストライド量

	//頂点フォーマットの設定
	pDevice -> SetFVF(FVF_VERTEX_2D);

	pDevice -> SetTexture(0, pTexture);

	//プリミティブの描画
	pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
								0,					//オフセット(頂点数)
								4);			//プリミティブ数

	//===== 小数点の描画 終了=====//

	float iSelf = iNumber;

	for(int iLoop = 0; iLoop < fFloatDigit; iLoop++){
		 iSelf *= 10;

		 //小数部の描画
		DrawNumber((int)iSelf, 1, Pos + D3DXVECTOR2(fMargin * (2.0f + 1.0f * iLoop), 0.0f), Size, -fMargin, pTexture);
	}

	

}

void SetNumber(int iNumber, D3DXVECTOR2 Pos, D3DXVECTOR2 Size)
{
	VERTEX2D* pVtx;	//仮想アドレス取得用ポインタ

	//仮想アドレスを取得する
	g_pVtxBufferNumber -> Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定（x, y, z）
	pVtx[0].pos = D3DXVECTOR3(Pos.x - Size.x * 0.5f, Pos.y - Size.y * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Pos.x + Size.x * 0.5f, Pos.y - Size.y * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Pos.x - Size.x * 0.5f, Pos.y + Size.y * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Pos.x + Size.x * 0.5f, Pos.y + Size.y * 0.5f, 0.0f);

	//テクスチャ―座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.1f * iNumber, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f * iNumber + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * iNumber, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.1f * iNumber + 0.1f, 0.5f);

	g_pVtxBufferNumber -> Unlock();
}

//-------------------------------------------------------
//	色の設定
//-------------------------------------------------------
void SetColor(D3DXCOLOR color)
{
	VERTEX2D* pVtx;	//仮想アドレス取得用ポインタ

	//仮想アドレスを取得する
	g_pVtxBufferNumber -> Lock(0, 0, (void**)&pVtx, 0);

	//カラーの設定
	pVtx[0].color = color;
	pVtx[1].color = color;
	pVtx[2].color = color;
	pVtx[3].color = color;

	g_pVtxBufferNumber -> Unlock();
}