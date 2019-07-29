//============================================
//  Effect関数  (Effect.cpp)
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
#include "effect.h"

//============================================
//
//  定数宣言
//
//============================================
#define MAX_EFFECT 100

#define EFFECT_ONE_DIS_MAX			3
#define EFFECT_TWO_DIS_MAX			3
#define EFFECT_THREE_DIS_MAX		3
#define EFFECT_FOUR_DIS_MAX			1
#define EFFECT_FIVE_DIS_MAX			3
#define EFFECT_SIX_DIS_MAX			3
#define EFFECT_SEVEN_DIS_MAX		3
#define EFFECT_EIGHT_DIS_MAX		3

//============================================
//
//  グローバル変数
//
//============================================
//LPはポインター!!
LPDIRECT3DTEXTURE9 g_pTextureEffect[EFFECT_MAX] = {};//Effectの張るテクスチャ、テクスチャインターフェース

/*頂点バッファ管理用*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferEffect = NULL;//ポインター!!&初期化

/*ノーツ構造体*/
EFFECT g_aEffect[MAX_EFFECT];

char* EffectTexName[] = {
	"data/TEXTURE/GAME/UI/kaihuku.png",
	"data/TEXTURE/GAME/UI/waza.png",
	"data/TEXTURE/GAME/UI/wazaon.png",
	"data/TEXTURE/GAME/UI/mahou01.png",
	"data/TEXTURE/GAME/UI/mahou02.png",
	"data/TEXTURE/GAME/UI/mahou022.png",
	"data/TEXTURE/GAME/UI/bakuhatu0221.png",
	"data/TEXTURE/GAME/UI/bakuhatu02-2.png",
};

int g_anDisTime[] = {3,3,3 , 1,3,1,1,3
};

//============================================
//
//  プロトタイプ宣言
//
//============================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);//頂点の作成

//============================================
//
//  名前  InitEffect関数
//  引数	void
//  戻り値  void
//  説明  Effect関係の初期化
//
//============================================
HRESULT InitEffect(void)
{
	UINT nID;  //メッセージボックスの返り値を入れる
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//頂点作成
	if(FAILED(MakeVertexEffect(pDevice)))
	{
		return E_FAIL;
	}//EOif
	
	for(int i = 0 ; i < EFFECT_MAX ; i++)
	{
		//テクスチャ取得
		if(FAILED(
		D3DXCreateTextureFromFile( pDevice , EffectTexName[i] , &g_pTextureEffect[i] )//テクスチャの読み込み、ディスクから読み込むん!!!!!!
			))
			{
				//エラーメッセージ
				nID = MessageBox(NULL , "テクスチャが取得できませんでした。","",MB_OK | MB_DEFBUTTON1);
			}//EOif
	}

	// ノーツ構造体の初期化
	for(int nCntEffect = 0 ; nCntEffect < MAX_EFFECT ; nCntEffect++)
	{
		g_aEffect[nCntEffect].bUse = false;
		g_aEffect[nCntEffect].bAnim = true;
		g_aEffect[nCntEffect].nMode = EFFECT_MAX;
		g_aEffect[nCntEffect].nAnimFlame = 0;
		g_aEffect[nCntEffect].nAnimFlameMax = 0;
		g_aEffect[nCntEffect].nAnimFlameBuf = 0;
		g_aEffect[nCntEffect].tex.pos = D3DXVECTOR2(0 , 0);
		g_aEffect[nCntEffect].tex.size = D3DXVECTOR2(0 , 0);
		g_aEffect[nCntEffect].poly.pos = D3DXVECTOR3(0 , 0 , 0);
		g_aEffect[nCntEffect].poly.size = D3DXVECTOR3(0 , 0 , 0);

	} // EO for

	return S_OK;
}//EOInitEffect

//============================================
//
//  名前  UninitEffect関数
//  引数	void
//  戻り値  void
//  説明  Effect関係の終了処理
//
//============================================
void UninitEffect(void)
{
	for(int nCntEffect = 0 ; nCntEffect < EFFECT_MAX  ; nCntEffect++)
	{
		//テクスチャインターフェースの後片付け
		SAFE_RELEASE( g_pTextureEffect[nCntEffect] );
	} // EO for

	//頂点バッファの後片付け
	SAFE_RELEASE( g_pVtxBufferEffect );
}//EOUninitEffect

//============================================
//
//  名前  UpdateEffect関数
//  引数	void
//  戻り値  void
//  説明  Effect関係の更新処理
//
//============================================
void UpdateEffect(void)
{
	//頂点バッファ
	VERTEX2D* pVtx;//仮想アドレスを取得するためのポインター、ここにhiaruyo

		//頂点バッファをロックして、仮想アドレスを取得する
	g_pVtxBufferEffect -> Lock(0,	//どこからロックするか
								0,				//どこまでロックするか(0~0で全部ロック)
								(void**)&pVtx,	//ポインタのポインタ(アドレスが書かれたメモ帳のアドレス)
								0);				//四つ目調べると面白いかも。

	// UVアニメーションでノーツ
	for(int nCntEffect = 0 ; nCntEffect < MAX_EFFECT ; nCntEffect++)
	{
		// 使用チェック
		if(g_aEffect[nCntEffect].bUse == true)
		{
			if(g_aEffect[nCntEffect].bAnim == true)
			{
				g_aEffect[nCntEffect].nAnimFlame++;
				if(g_aEffect[nCntEffect].nAnimFlame > g_aEffect[nCntEffect].nAnimFlameMax)
				{
					if(g_aEffect[nCntEffect].nAnimFlameBuf == 0)
					{
						g_aEffect[nCntEffect].nAnimFlame = 0;
						g_aEffect[nCntEffect].tex.pos += g_aEffect[nCntEffect].tex.size;
					}

					if(g_aEffect[nCntEffect].tex.pos.x >= 1.0f || g_aEffect[nCntEffect].nAnimFlameBuf != 0)
					{
						// 特別処理(通常弾)
						if(g_aEffect[nCntEffect].nMode == EFFECT_MAGIC_ON_NORMAL_1)
						{
							if(g_aEffect[nCntEffect].nAnimFlameBuf == 0)
							{
								SetEffect(g_aEffect[nCntEffect].poly.pos.x , g_aEffect[nCntEffect].poly.pos.y , g_aEffect[nCntEffect].poly.size.x,
									g_aEffect[nCntEffect].poly.size.y , EFFECT_MAGIC_ON_NORMAL_2);
								g_aEffect[nCntEffect].nAnimFlameBuf++;
								g_aEffect[nCntEffect].tex.pos -= g_aEffect[nCntEffect].tex.size;
							}
							else
							{
								g_aEffect[nCntEffect].nAnimFlameBuf++;
								if(g_aEffect[nCntEffect].nAnimFlameBuf >= g_anDisTime[4] * 10.0f)
								{
									g_aEffect[nCntEffect].bAnim = false;
								}
							}
						}
						else if(g_aEffect[nCntEffect].nMode == EFFECT_MAGIC_ON_EXPLOSION_1)
						{
							if(g_aEffect[nCntEffect].nAnimFlameBuf == 0)
							{
								SetEffect(g_aEffect[nCntEffect].poly.pos.x , g_aEffect[nCntEffect].poly.pos.y , g_aEffect[nCntEffect].poly.size.x,
									g_aEffect[nCntEffect].poly.size.y , EFFECT_MAGIC_ON_EXPLOSION_2);
								g_aEffect[nCntEffect].nAnimFlameBuf++;
								g_aEffect[nCntEffect].tex.pos -= g_aEffect[nCntEffect].tex.size;
							}
							else
							{
								g_aEffect[nCntEffect].nAnimFlameBuf++;
								if(g_aEffect[nCntEffect].nAnimFlameBuf >= g_anDisTime[6] * 10.0f + g_anDisTime[7] * 10.0f)
								{
									g_aEffect[nCntEffect].bAnim = false;
								}
							}
						}
						else if(g_aEffect[nCntEffect].nMode == EFFECT_MAGIC_ON_EXPLOSION_2)
						{
							if(g_aEffect[nCntEffect].nAnimFlameBuf == 0)
							{
								SetEffect(g_aEffect[nCntEffect].poly.pos.x , g_aEffect[nCntEffect].poly.pos.y , g_aEffect[nCntEffect].poly.size.x,
									g_aEffect[nCntEffect].poly.size.y , EFFECT_MAGIC_ON_EXPLOSION_3);
								g_aEffect[nCntEffect].bAnim = false;
								g_aEffect[nCntEffect].fAlphaDif += 0.02f;
								g_aEffect[nCntEffect].nAnimFlameBuf++;
								g_aEffect[nCntEffect].tex.pos -= g_aEffect[nCntEffect].tex.size;
							}
						}
						else if(g_aEffect[nCntEffect].nMode == EFFECT_MAGIC_ON_EXPLOSION_3 || g_aEffect[nCntEffect].nMode == EFFECT_MAGIC_ON_NORMAL_2)
						{
							g_aEffect[nCntEffect].bAnim = false;
							g_aEffect[nCntEffect].fAlphaDif = 0.008f;
							g_aEffect[nCntEffect].tex.pos -= g_aEffect[nCntEffect].tex.size;
						}
						else
						{
							g_aEffect[nCntEffect].bUse = false;
						}
					}
				}
			}
			else
			{
				g_aEffect[nCntEffect].fAlpha -= g_aEffect[nCntEffect].fAlphaDif;
				if(g_aEffect[nCntEffect].fAlpha <= 0.0f)
				{
					g_aEffect[nCntEffect].bUse = false;
				}
			}

			//頂点座標の設定(2D座標 , 右回り )
			setBuffer(&pVtx[4 * nCntEffect], g_aEffect[nCntEffect].poly);

		    //各頂点のテクスチャ座標の設定
			setTexture(&pVtx[4 * nCntEffect], g_aEffect[nCntEffect].tex);

			//頂点カラー(0～255の整数値)
			pVtx[0 + 4 * nCntEffect].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aEffect[nCntEffect].fAlpha);
			pVtx[1 + 4 * nCntEffect].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aEffect[nCntEffect].fAlpha);
			pVtx[2 + 4 * nCntEffect].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aEffect[nCntEffect].fAlpha);
			pVtx[3 + 4 * nCntEffect].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aEffect[nCntEffect].fAlpha);
		} // EO if
	} // EO for

	g_pVtxBufferEffect->Unlock ();												//ロック解除

}//EOUpdateEffect

//============================================
//
//  名前  DrawEffect関数
//  引数	void
//  戻り値  void
//  説明  Effect関係の描画処理
//
//============================================
void DrawEffect(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//パイプラインの設定
	pDevice -> SetStreamSource(0,//ストリーム番号(何本も作れる)
						g_pVtxBufferEffect ,//データのある場所(先頭アドレス)
						0,//オフセット(単位バイト)、データのどの辺から持ってくるか,0は先頭
						sizeof(VERTEX2D) );//ストライド量(一個の単位の大きさ)

	//頂点フォーマットの設定
	pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

	// 最大数チェック
	for(int nCntEffect = 0 ; nCntEffect < MAX_EFFECT ; nCntEffect++)
	{
		if(g_aEffect[nCntEffect].bUse == true)
		{

			pDevice -> SetTexture( 0 , g_pTextureEffect[g_aEffect[nCntEffect].nMode] );

			//プリミティブの描画
			pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
				nCntEffect * 4 ,//オフセット(頂点数)何頂点目からとるか
				NUM_POLYGON );//いくつ頂点持ってくればいいのか、プリミティブの枚数を教えたゲル。パイプラインは垂れ流しになっているから。
		} // EO if
	} // EO for
}//EODarwEffect

//============================================
//
//  名前  MakeVertexEffect関数
//  引数	LPDIRECT3DDEVICE9 pDevice
//  戻り値  void
//  説明  頂点の作成
//
//============================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{

	//頂点バッファ作成
	if(FAILED(
		pDevice -> CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX * MAX_EFFECT,//作成したい頂点バッファのサイズ = 1つの頂点のサイズ * 頂点数
																	//どれくらいメモリほしいか、ここをめっちゃふやすんでーーー
			D3DUSAGE_WRITEONLY,									//頂点バッファの使用方法、書き込み専用なので、恐らく最速
			FVF_VERTEX_2D,										//NULLや0でも大丈夫、マナー的には書こうよ。このバッファの頂点フォーマットを問う
			D3DPOOL_MANAGED,									//メモリ管理どうする設定、この状態はデバイスにお任せ
			&g_pVtxBufferEffect,						//出来上がった頂点バッファを管理するアドレス
			NULL)												//謎だけれどNULL
	))
	{
		return E_FAIL;
	}


	//頂点バッファ
	VERTEX2D* pVtx;//仮想アドレスを取得するためのポインター、ここにhiaruyo
	//頂点バッファをロックして、仮想アドレスを取得する
	g_pVtxBufferEffect -> Lock(0,	//どこからロックするか
								0,				//どこまでロックするか(0~0で全部ロック)
								(void**)&pVtx,	//ポインタのポインタ(アドレスが書かれたメモ帳のアドレス)
								0);				//四つ目調べると面白いかも。

		// 最大数回す
	for(int nCntEffect = 0 ; nCntEffect < MAX_EFFECT ; nCntEffect++)
	{
		//rhwの設定(必ず1.0fを入れる!!!!!!!!)
		pVtx[0 + 4 * nCntEffect].rhw = 1.0f;
		pVtx[1 + 4 * nCntEffect].rhw = 1.0f;
		pVtx[2 + 4 * nCntEffect].rhw = 1.0f;
		pVtx[3 + 4 * nCntEffect].rhw = 1.0f;

		//頂点カラー(0～255の整数値)
		pVtx[0 + 4 * nCntEffect].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[1 + 4 * nCntEffect].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[2 + 4 * nCntEffect].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[3 + 4 * nCntEffect].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

	} // EO for

	//鍵をアンロック
	g_pVtxBufferEffect -> Unlock();

	return S_OK;

}//EOMakeVertexEffect

//============================================
//
//  名前  SetEffect関数
//  引数	void
//  戻り値  float fPosX ,float fPosY,float fWidth,float fHeught,Effect_MODE nMode
//  説明  ノーツをセット
//
//============================================
void    SetEffect    (float fPosX , // 中心座標X
	float fPosY,					   // 中心座標Y
	float fWidth,					   // 幅
	float fHeught,					   // 高さ
	EFFECT_MODE nMode			   // 種類
	)
{
	for(int nCntEffect = 0 ; nCntEffect < MAX_EFFECT ; nCntEffect++)
	{
		if(g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].bUse = true;
			g_aEffect[nCntEffect].nMode = nMode;
			g_aEffect[nCntEffect].tex.pos = D3DXVECTOR2(0 , 0);
			g_aEffect[nCntEffect].tex.size = D3DXVECTOR2(0.1f , 1);
			g_aEffect[nCntEffect].poly.size = D3DXVECTOR3(fWidth , fHeught , 0);
			g_aEffect[nCntEffect].poly.pos= D3DXVECTOR3(fPosX , fPosY , 0);
			g_aEffect[nCntEffect].nAnimFlame = 0;
			g_aEffect[nCntEffect].nAnimFlameBuf = 0;
			g_aEffect[nCntEffect].bAnim = true;
			g_aEffect[nCntEffect].nAnimFlameMax = g_anDisTime[nMode];
			g_aEffect[nCntEffect].fAlpha = 1.0f;
			g_aEffect[nCntEffect].fAlphaDif = 0.01f;
			
			return;
		} // EO if
	} // EO for
} // EO SetEffect


