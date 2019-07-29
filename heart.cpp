//============================================
//  Heart関数  (Heart.cpp)
//
//  Author  Information
//  名前  石井  雄大
//  作成日   2016年07月24日
//  修正日   年月日
//  修正内容:
//
//
//============================================

//============================================
//
//  インクルードファイル
//
//============================================
#include "main.h"
#include "notes.h"
#include "castle.h"
#include "gate.h"
#include "heart.h"

//============================================
//
//  定数宣言
//
//============================================
#//読み込むテクスチャファイル名
#define HEART_ONE_TEXTURENAME       "data/TEXTURE/GAME/ENEMY/haert.png"   // NHEART_ONE

//============================================
//
//  グローバル変数
//
//============================================
//LPはポインター!!
LPDIRECT3DTEXTURE9 g_pTextureHeart[MAX_HEART] = {};//Heartの張るテクスチャ、テクスチャインターフェース

/*頂点バッファ管理用*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferHeart = NULL;//ポインター!!&初期化

/*ハート構造体*/
HEART g_aHeart[MAX_HEART];

//============================================
//
//  プロトタイプ宣言
//
//============================================
HRESULT MakeVertexHeart(LPDIRECT3DDEVICE9 pDevice);//頂点の作成

//============================================
//
//  名前  InitHeart関数
//  引数	void
//  戻り値  void
//  説明  Heart関係の初期化
//
//============================================
HRESULT InitHeart(void)
{
	UINT nID;  //メッセージボックスの返り値を入れる
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//頂点作成
	if(FAILED(MakeVertexHeart(pDevice)))
	{
		return E_FAIL;
	}//EOif
	
	//テクスチャ取得
	if(FAILED(
	D3DXCreateTextureFromFile( pDevice , HEART_ONE_TEXTURENAME , &g_pTextureHeart[0] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
		))
		{
			//エラーメッセージ
			nID = MessageBox(NULL , "テクスチャが取得できませんでした。","HEART_ONE",MB_OK | MB_DEFBUTTON1);
		}//EOif

	// ハート構造体の初期化
	for(int nCntHeart = 0 ; nCntHeart < MAX_HEART ; nCntHeart++)
	{
		g_aHeart[nCntHeart].bUse = false;
		g_aHeart[nCntHeart].fHeight = 0.0f;
		g_aHeart[nCntHeart].fPos = D3DXVECTOR2(0.0f , 0.0f);
		g_aHeart[nCntHeart].fUV = D3DXVECTOR2(0.0f , 0.0f);
		g_aHeart[nCntHeart].fUVSize = D3DXVECTOR2(0.0f , 0.0f);
		g_aHeart[nCntHeart].fWidth = 0.0f;
	} // EO for

	return S_OK;
}//EOInitHeart

//============================================
//
//  名前  UninitHeart関数
//  引数	void
//  戻り値  void
//  説明  Heart関係の終了処理
//
//============================================
void UninitHeart(void)
{
	//テクスチャインターフェースの後片付け
	SAFE_RELEASE( g_pTextureHeart[0] );

	//頂点バッファの後片付け
	SAFE_RELEASE( g_pVtxBufferHeart );
}//EOUninitHeart

//============================================
//
//  名前  UpdateHeart関数
//  引数	void
//  戻り値  void
//  説明  Heart関係の更新処理
//
//============================================
void UpdateHeart(void)
{
	//頂点バッファ
	VERTEX2D* pVtx;//仮想アドレスを取得するためのポインター、ここにhiaruyo

		//頂点バッファをロックして、仮想アドレスを取得する
	g_pVtxBufferHeart -> Lock(0,	//どこからロックするか
								0,				//どこまでロックするか(0~0で全部ロック)
								(void**)&pVtx,	//ポインタのポインタ(アドレスが書かれたメモ帳のアドレス)
								0);				//四つ目調べると面白いかも。

	// UVアニメーションでハート
	for(int nCntHeart = 0 ; nCntHeart < MAX_HEART ; nCntHeart++)
	{
		// 使用チェック
		if(g_aHeart[nCntHeart].bUse == true)
		{
			//頂点座標の設定(2D座標 , 右回り )
			pVtx [ 0 + 4*nCntHeart] . pos = D3DXVECTOR3 (g_aHeart[nCntHeart].fPos.x , g_aHeart[nCntHeart].fPos.y , 0.0f);
			pVtx [ 1 + 4*nCntHeart] . pos = D3DXVECTOR3 (g_aHeart[nCntHeart].fPos.x + g_aHeart[nCntHeart].fWidth ,g_aHeart[nCntHeart].fPos.y , 0.0f);
			pVtx [ 2 + 4*nCntHeart] . pos = D3DXVECTOR3 (g_aHeart[nCntHeart].fPos.x , g_aHeart[nCntHeart].fPos.y + g_aHeart[nCntHeart].fHeight , 0.0f);
			pVtx [ 3 + 4*nCntHeart] . pos = D3DXVECTOR3 (g_aHeart[nCntHeart].fPos.x + g_aHeart[nCntHeart].fWidth , g_aHeart[nCntHeart].fPos.y + g_aHeart[nCntHeart].fHeight , 0.0f);

		    //各頂点のテクスチャ座標の設定
			pVtx [ 0 + 4*nCntHeart] . tex = D3DXVECTOR2 (g_aHeart[nCntHeart].fUV.x , g_aHeart[nCntHeart].fUV.y);
			pVtx [ 1 + 4*nCntHeart] . tex = D3DXVECTOR2 (g_aHeart[nCntHeart].fUV.x + g_aHeart[nCntHeart].fUVSize.x , g_aHeart[nCntHeart].fUV.y);
			pVtx [ 2 + 4*nCntHeart] . tex = D3DXVECTOR2 (g_aHeart[nCntHeart].fUV.x , g_aHeart[nCntHeart].fUV.y + g_aHeart[nCntHeart].fUVSize.y);
			pVtx [ 3 + 4*nCntHeart] . tex = D3DXVECTOR2 (g_aHeart[nCntHeart].fUV.x + g_aHeart[nCntHeart].fUVSize.x , g_aHeart[nCntHeart].fUV.y+ g_aHeart[nCntHeart].fUVSize.y);


		} // EO if
	} // EO for

	g_pVtxBufferHeart->Unlock ();												//ロック解除

}//EOUpdateHeart

//============================================
//
//  名前  DrawHeart関数
//  引数	void
//  戻り値  void
//  説明  Heart関係の描画処理
//
//============================================
void DrawHeart(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//パイプラインの設定
	pDevice -> SetStreamSource(0,//ストリーム番号(何本も作れる)
						g_pVtxBufferHeart ,//データのある場所(先頭アドレス)
						0,//オフセット(単位バイト)、データのどの辺から持ってくるか,0は先頭
						sizeof(VERTEX2D) );//ストライド量(一個の単位の大きさ)

	//頂点フォーマットの設定
	pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

	// 最大数チェック
	for(int nCntHeart = 0 ; nCntHeart < MAX_HEART ; nCntHeart++)
	{
		if(g_aHeart[nCntHeart].bUse == true)
		{
			//Heartの描画をする寸前
			pDevice -> SetTexture( 0 , g_pTextureHeart[0] );

			//プリミティブの描画
			pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
				nCntHeart * 4 ,//オフセット(頂点数)何頂点目からとるか
				NUM_POLYGON );//いくつ頂点持ってくればいいのか、プリミティブの枚数を教えたゲル。パイプラインは垂れ流しになっているから。
		} // EO if
	} // EO for
}//EODarwHeart

//============================================
//
//  名前  MakeVertexHeart関数
//  引数	LPDIRECT3DDEVICE9 pDevice
//  戻り値  void
//  説明  頂点の作成
//
//============================================
HRESULT MakeVertexHeart(LPDIRECT3DDEVICE9 pDevice)
{

	//頂点バッファ作成
	if(FAILED(
		pDevice -> CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX * MAX_HEART,//作成したい頂点バッファのサイズ = 1つの頂点のサイズ * 頂点数
																	//どれくらいメモリほしいか、ここをめっちゃふやすんでーーー
			D3DUSAGE_WRITEONLY,									//頂点バッファの使用方法、書き込み専用なので、恐らく最速
			FVF_VERTEX_2D,										//NULLや0でも大丈夫、マナー的には書こうよ。このバッファの頂点フォーマットを問う
			D3DPOOL_MANAGED,									//メモリ管理どうする設定、この状態はデバイスにお任せ
			&g_pVtxBufferHeart,						//出来上がった頂点バッファを管理するアドレス
			NULL)												//謎だけれどNULL
	))
	{
		return E_FAIL;
	}


	//頂点バッファ
	VERTEX2D* pVtx;//仮想アドレスを取得するためのポインター、ここにhiaruyo
	//頂点バッファをロックして、仮想アドレスを取得する
	g_pVtxBufferHeart -> Lock(0,	//どこからロックするか
								0,				//どこまでロックするか(0~0で全部ロック)
								(void**)&pVtx,	//ポインタのポインタ(アドレスが書かれたメモ帳のアドレス)
								0);				//四つ目調べると面白いかも。

		// 最大数回す
	for(int nCntHeart = 0 ; nCntHeart < MAX_HEART ; nCntHeart++)
	{
		//rhwの設定(必ず1.0fを入れる!!!!!!!!)
		pVtx[0 + 4 * nCntHeart].rhw = 1.0f;
		pVtx[1 + 4 * nCntHeart].rhw = 1.0f;
		pVtx[2 + 4 * nCntHeart].rhw = 1.0f;
		pVtx[3 + 4 * nCntHeart].rhw = 1.0f;

		//頂点カラー(0～255の整数値)
		pVtx[0 + 4 * nCntHeart].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[1 + 4 * nCntHeart].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[2 + 4 * nCntHeart].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[3 + 4 * nCntHeart].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

	} // EO for

	//鍵をアンロック
	g_pVtxBufferHeart -> Unlock();

	return S_OK;

}//EOMakeVertexHeart

//============================================
//
//  名前  SetHeart関数
//  引数	void
//  戻り値  float fPosX ,float fPosY,float fWidth,float fHeught,Heart_MODE nMode
//  説明  ハートをセット
//
//============================================
int    SetHeart    (float fPosX , // 中心座標X
	float fPosY,					   // 中心座標Y
	float fWidth,					   // 幅
	float fHeught,					   // 高さ
	int nHp
	)
{
	for(int nCntHeart = 0 ; nCntHeart < MAX_HEART ; nCntHeart++)
	{
		if(g_aHeart[nCntHeart].bUse == false)
		{
			g_aHeart[nCntHeart].bUse = true;
			g_aHeart[nCntHeart].fPos = D3DXVECTOR2(fPosX , fPosY);
			g_aHeart[nCntHeart].fUV = D3DXVECTOR2(0.0f , 0.0f);
			g_aHeart[nCntHeart].fWidth = fWidth;
			g_aHeart[nCntHeart].fHeight = fHeught;

			// hpからサイズ計算
			float x= 1.0f / 10.0f * nHp;
			g_aHeart[nCntHeart].fUVSize = D3DXVECTOR2(x , 1.0f);

			return nCntHeart;
		} // EO if
	} // EO for

	return -1;
} // EO SetHeart

//============================================
//
//  名前  GetHeart関数
//  引数	void
//  戻り値  HEART *g_aHeart[0]
//  説明  g_aHeartの先頭アドレスを渡す
//
//============================================
HEART* GetHeart()
{
	return &g_aHeart[0];
} // EO GetHeart

void SetPosHeart (int nIdx , D3DXVECTOR2 fPos)	// 座標
{
	if(g_aHeart[nIdx].bUse == false)
	{
		return;
	}

	g_aHeart[nIdx].fPos = fPos;

}

void SetUVSizeHeart(int nIdx , int nLife)	// ライフからuv計算
{
	if(g_aHeart[nIdx].bUse == false)
	{
		return;
	}

	float x = 1.0f / 10.0f * nLife;
	g_aHeart[nIdx].fUVSize.x = x;
	g_aHeart[nIdx].fWidth = nLife * HEART_WIDTH;
}

void OffHeart(int nIdx)
{
	if(g_aHeart[nIdx].bUse == false)
	{
		return;
	}
	g_aHeart[nIdx].bUse = false;
}

