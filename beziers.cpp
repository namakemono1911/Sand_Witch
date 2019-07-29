/*****************************************************************************
beziers.cpp
Aythor	: 上野　匠
Data	: 2016_07_05
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "beziers.h"
#include "input.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define TEXTURE_NAME	"data/TEXTURE/white.png"	//テクスチャファイルネーム

#define BEZIERS_POS_X	(SCREEN_WIDTH * 0.5f)		//ポリゴンの表示位置X
#define BEZIERS_POS_Y	(SCREEN_HEIGHT * 0.5f)		//ポリゴンの表示位置Y

#define BEZIERS_WIDTH	(SCREEN_WIDTH)				//ポリゴンの幅
#define BEZIERS_HEIGHT	(SCREEN_HEIGHT)				//ポリゴンの高さ
#define BEZIERS_RATE	(0.0001f)					//フェード係数

#define	MAX_BEZIERS	(100.f)							//曲線の頂点数

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	POLYGON		conf;		//ポリゴンのコンフィグ
	float		width;		//線幅
	D3DXVECTOR3	impact[4];	//影響点
}BEZIERS;

BEZIERS	beziers;
//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexBeziers ( LPDIRECT3DDEVICE9 pDevice );
D3DXVECTOR3	bezieFormula	( float	t );

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9		g_pTextureBeziers = NULL;		//テクスチャインターフェイス
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBeziers = NULL;	//頂点バッファ管理インターフェイス

//////////////////////////////////////////////////////////////////////////////
//関数名	: initBeziers
//返り値	: 
//説明		: ポリゴン初期化
//////////////////////////////////////////////////////////////////////////////
void initBeziers ( void )
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスポインタ取得

	//構造体初期化
	beziers.impact[0] = D3DXVECTOR3(50, BEZIERS_POS_Y, 0.f);
	beziers.impact[1] = D3DXVECTOR3(SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT, 0.f);
	beziers.impact[2] = D3DXVECTOR3(SCREEN_WIDTH * 0.6f, 0.f, 0.f);
	beziers.impact[3] = D3DXVECTOR3(SCREEN_WIDTH * 0.8f, BEZIERS_POS_Y, 0.f);
	beziers.width = 3;

	//テクスチャの読み込み
	/*if(FAILED(D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureBeziers)))
	{
		MessageBox(NULL, "beziers", "エラー", MB_OK);
	}*/

	//デバイス取得
	makeVertexBeziers(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: uninitBeziers
//返り値	: 
//説明		: ポリゴン終了
//////////////////////////////////////////////////////////////////////////////
void uninitBeziers ( void )
{
	//テクスチャインターフェイスの解放
	if(g_pTextureBeziers != NULL)
	{
		g_pTextureBeziers->Release();
		g_pTextureBeziers = NULL;
	}

	//頂点バッファ管理の解放
	if(g_pVtxBufferBeziers != NULL)
	{
		g_pVtxBufferBeziers->Release();
		g_pVtxBufferBeziers = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: updateBeziers
//返り値	: 
//説明		: ポリゴン更新
//////////////////////////////////////////////////////////////////////////////
void updateBeziers ( void )
{
	
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: drawBeziers
//返り値	: 
//説明		: ポリゴン描写
//////////////////////////////////////////////////////////////////////////////
void drawBeziers ( void )
{
	//変数宣言
	int		i;			//loop
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//描画設定を加算合成に変更
	addDevice();

	//ストリーム作成
	pDevice->SetStreamSource(0, g_pVtxBufferBeziers, 0, sizeof(VERTEX2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0,g_pTextureBeziers);

	//描画
	for(i = 0; i < MAX_BEZIERS; i++)
	{
		pDevice->DrawPrimitive
			(
			D3DPT_TRIANGLESTRIP,			//ポリゴンの種類
			NUM_VERTEX * i,				//オフセット(頂点数)
			NUM_POLYGON						//ポリゴンの数
			);
	}

	//描画設定を乗算合成に変更
	initDevice();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: makeVertexBeziers
//返り値	: 
//説明		: 頂点作成
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexBeziers ( LPDIRECT3DDEVICE9 pDevice )
{
	//変数宣言
	float		i;		//loop
	VERTEX2D *pVtx = NULL;;		//仮想アドレス用ポインタ

	//頂点バッファの設定
	if(FAILED(pDevice->CreateVertexBuffer
			(
			(UINT)(sizeof(VERTEX2D) * NUM_VERTEXLIST * MAX_BEZIERS),		//頂点バッファサイズ
			D3DUSAGE_WRITEONLY,					//頂点バッファの使用方法
			FVF_VERTEX_2D,						//
			D3DPOOL_MANAGED,					//メモリ管理方法
			&g_pVtxBufferBeziers,				//頂点バッファ管理インターフェイス
			NULL
			)
		))
		
	{
		return E_FAIL;
	}

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferBeziers->Lock(0, 0, (void**)&pVtx, 0);

	for(i = 0; i <= 0.9f; i += 1 / MAX_BEZIERS)
	{
		//頂点座標の設定(2D座標・右回り)
		pVtx[0].pos = bezieFormula(i);
		pVtx[1].pos = bezieFormula(i + 1 / MAX_BEZIERS);
		pVtx[2].pos = D3DXVECTOR3(bezieFormula(i).x, bezieFormula(i).y + beziers.width, 0.f);
		pVtx[3].pos = D3DXVECTOR3(bezieFormula(i + 1 / MAX_BEZIERS).x, bezieFormula(i + 1 / MAX_BEZIERS).y + beziers.width, 0.f);

		//rhwの設定(必ず1.0f)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定(0~155の整数値)
		pVtx[0].color = D3DCOLOR_RGBA(100, 100, 192, 255);
		pVtx[1].color = D3DCOLOR_RGBA(100, 100, 192, 255);
		pVtx[2].color = D3DCOLOR_RGBA(100, 100, 192, 255);
		pVtx[3].color = D3DCOLOR_RGBA(100, 100, 192, 255);
	
		//テクスチャ頂点座標の設定(0~1)
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//ポインタ移動
		pVtx += NUM_VERTEX;
	}

	//私のこころアーンロック♪
	g_pVtxBufferBeziers->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: bezieFormula
//返り値	: 
//説明		: 頂点の方程式
//////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3	bezieFormula	( float	t )
{
	return D3DXVECTOR3(
		beziers.impact[0].x * ((1 - t) * (1 - t) * (1 - t)) + beziers.impact[1].x * 3 * t *(( 1 - t ) * ( 1 - t )) + beziers.impact[2].x * 3 * (t * t) * ( 1 - t ) + beziers.impact[3].x * (t * t * t),
		beziers.impact[0].y * ((1 - t) * (1 - t) * (1 - t)) + beziers.impact[1].y * 3 * t *(( 1 - t ) * ( 1 - t )) + beziers.impact[2].y * 3 * (t * t) * ( 1 - t ) + beziers.impact[3].y * (t * t * t),
		0.f);
}