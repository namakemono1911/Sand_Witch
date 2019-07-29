//============================================
//  gate関数  (gate.cpp)
//
//  Author  Information
//  名前  石井  雄大
//  作成日   2017年04月21日
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
#include "gate.h"
#include "notes.h"
#include "bulletBoss.h"
#include "input.h"
#include "boss.h"
#include "sound.h"

#include "heart.h"

#include "polygon.h"

#include "effect.h"

//============================================
//
//  マクロ定義
//
//============================================
#define GATE_TEX_NAME	"data/texture/GAME/CASTLE/gate01.png"	// テクスチャ名

#define WIDTH (70)
#define GATE_HP 100	// 耐久力

//============================================
//
//  グローバル変数
//
//============================================
//LPはポインター!!
LPDIRECT3DTEXTURE9 g_pTextureGate = NULL;//Notesの張るテクスチャ、テクスチャインターフェース

/*頂点バッファ管理用*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferGate = NULL;//ポインター!!&初期化

/*門構造体*/
GATE g_aGate[GATE_NUM];

//============================================
//
//  プロトタイプ宣言
//
//============================================
HRESULT MakeVertexGate(LPDIRECT3DDEVICE9 pDevice);

//============================================
//
//  名前  InitGate関数
//  引数   void
//  戻り値 void
//  説明   門の初期化
//
//============================================
void InitGate(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();


	// 門構造体の初期化

	for(int i = 0 ; i < GATE_NUM ; i++)
	{
		g_aGate[i].bUse = true;
		g_aGate[i].bCol = true;
		g_aGate[i].fPos = D3DXVECTOR3(POSX , (SCREEN_HEIGHT / 100.0f * 26.5f) + ((SCREEN_HEIGHT / 100.0f * 15.0f) + (SCREEN_HEIGHT / 100.0f * 2.75f)) * i, 0.0f);
		g_aGate[i].fSize = D3DXVECTOR2(WIDTH , (SCREEN_HEIGHT / 100.0f * 15.0f));
		g_aGate[i].fUV = D3DXVECTOR2(0.0f , 0.0f);
		g_aGate[i].nHp = GATE_HP;
		g_aGate[i].nHeart = -1;
	} // EO for

	//頂点作成
	if(FAILED(MakeVertexGate(pDevice)))
	{
		return;
	} // EO if

	// テクスチャ取得
	if(FAILED(D3DXCreateTextureFromFile( pDevice , GATE_TEX_NAME , &g_pTextureGate )))
	{
		MessageBox(NULL , "門テクスチャが取得できませんでした" , "ERROR" , MB_OK);
	} // EO if

} // EO InitGate

//============================================
//
//  名前  UninitGate関数
//  引数   void
//  戻り値 void
//  説明   門の終了
//
//============================================
void UninitGate(void)
{
	// インターフェースの解放
	SAFE_RELEASE(g_pTextureGate);
	SAFE_RELEASE(g_pVtxBufferGate);

} // EO UninitGate

//============================================
//
//  名前  UpdateGate関数
//  引数   void
//  戻り値 void
//  説明   門の更新
//
//============================================
void UpdateGate(void)
{
	// 敵との当たり判定
	//頂点バッファ
	VERTEX2D* pVtx;
	//頂点バッファをロックして、仮想アドレスを取得する
	g_pVtxBufferGate -> Lock(0,0,(void**)&pVtx,0);
	int nCntGate;
	for(nCntGate = 0 ; nCntGate < GATE_NUM ; nCntGate++)
	{
		if(g_aGate[nCntGate].bUse == true)
		{
			SetPosHeart(g_aGate[nCntGate].nHeart , D3DXVECTOR2(g_aGate[nCntGate].fPos.x , g_aGate[nCntGate].fPos.y));
			SetUVSizeHeart(g_aGate[nCntGate].nHeart , g_aGate[nCntGate].nHp / 10);
			if(g_aGate[nCntGate].nHp >= 50)
			{
				pVtx[0 + 4 * nCntGate].tex = D3DXVECTOR2( 0.0f , 0.0f );
				pVtx[1 + 4 * nCntGate].tex = D3DXVECTOR2( 0.25f , 0.0f );
				pVtx[2 + 4 * nCntGate].tex = D3DXVECTOR2( 0.0f , 1.0f );
				pVtx[3 + 4 * nCntGate].tex = D3DXVECTOR2( 0.25f , 1.0f );
			}
			else if(g_aGate[nCntGate].nHp < 50 && g_aGate[nCntGate].nHp >= 30)
			{
				pVtx[0 + 4 * nCntGate].tex = D3DXVECTOR2( 0.25f , 0.0f );
				pVtx[1 + 4 * nCntGate].tex = D3DXVECTOR2( 0.5f , 0.0f );
				pVtx[2 + 4 * nCntGate].tex = D3DXVECTOR2( 0.25f , 1.0f );
				pVtx[3 + 4 * nCntGate].tex = D3DXVECTOR2( 0.5f , 1.0f );
			}
			else if(g_aGate[nCntGate].nHp < 30 && g_aGate[nCntGate].nHp > 0)
			{
				pVtx[0 + 4 * nCntGate].tex = D3DXVECTOR2( 0.5f , 0.0f );
				pVtx[1 + 4 * nCntGate].tex = D3DXVECTOR2( 0.75f , 0.0f );
				pVtx[2 + 4 * nCntGate].tex = D3DXVECTOR2( 0.5f , 1.0f );
				pVtx[3 + 4 * nCntGate].tex = D3DXVECTOR2( 0.75f , 1.0f );
			}
			else
			{
				pVtx[0 + 4 * nCntGate].tex = D3DXVECTOR2( 0.75f , 0.0f );
				pVtx[1 + 4 * nCntGate].tex = D3DXVECTOR2( 1.00f , 0.0f );
				pVtx[2 + 4 * nCntGate].tex = D3DXVECTOR2( 0.75f , 1.0f );
				pVtx[3 + 4 * nCntGate].tex = D3DXVECTOR2( 1.00f , 1.0f );
			}

			float a = (float)g_aGate[nCntGate].nHp / 100.0f;
			pVtx[0 + 4 * nCntGate].color = D3DXCOLOR(1.0f , 1.0f * a , 1.0f * a, 1.0f);
			pVtx[1 + 4 * nCntGate].color = D3DXCOLOR(1.0f , 1.0f * a , 1.0f * a, 1.0f);
			pVtx[2 + 4 * nCntGate].color = D3DXCOLOR(1.0f , 1.0f * a , 1.0f * a, 1.0f);
			pVtx[3 + 4 * nCntGate].color = D3DXCOLOR(1.0f , 1.0f * a , 1.0f * a, 1.0f);
		} // EO if
	} // EO for

	g_pVtxBufferGate -> Unlock();

} // EO UpdateGate

//============================================
//
//  名前  DrawGate関数
//  引数   void
//  戻り値 void
//  説明   門の描画
//
//============================================
void DrawGate(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//パイプラインの設定
	pDevice -> SetStreamSource(0,//ストリーム番号(何本も作れる)
						g_pVtxBufferGate ,//データのある場所(先頭アドレス)
						0,//オフセット(単位バイト)、データのどの辺から持ってくるか,0は先頭
						sizeof(VERTEX2D) );//ストライド量(一個の単位の大きさ)

	//頂点フォーマットの設定
	pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

	for(int nCntNotes = 0 ; nCntNotes < GATE_NUM ; nCntNotes++ )
	{
		if(g_aGate[nCntNotes].bUse == false)
		{
			int i = 0;
		}
		if(g_aGate[nCntNotes].bUse == true)
		{
			pDevice->SetTexture(0  ,g_pTextureGate);
			//プリミティブの描画
			pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
				nCntNotes * 4 ,//オフセット(頂点数)何頂点目からとるか
				NUM_POLYGON );//いくつ頂点持ってくればいいのか、プリミティブの枚数を教えたゲル。パイプラインは垂れ流しになっているから。
		} // EO if
	} // EO fro

} // EO DrawGate

//============================================
//
//  名前  MakeVertexGate関数
//  引数	LPDIRECT3DDEVICE9 pDevice
//  戻り値  void
//  説明  頂点の作成
//
//============================================
HRESULT MakeVertexGate(LPDIRECT3DDEVICE9 pDevice)
{
	//頂点バッファ作成
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX * MAX_NOTES,D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBufferGate,NULL)))
	{
		MessageBox(NULL , "頂点バッファの作成に失敗しました" , "ERROR" , MB_OK);
		return E_FAIL;
	} // EO if


	//頂点バッファ
	VERTEX2D* pVtx;
	//頂点バッファをロックして、仮想アドレスを取得する
	g_pVtxBufferGate -> Lock(0,0,(void**)&pVtx,0);

	for(int nCntNotes = 0 ; nCntNotes < GATE_NUM ; nCntNotes++)
	{
		pVtx[0 + 4 * nCntNotes].pos = D3DXVECTOR3(g_aGate[nCntNotes].fPos.x , g_aGate[nCntNotes].fPos.y , 0.0f);
		pVtx[1 + 4 * nCntNotes].pos = D3DXVECTOR3(g_aGate[nCntNotes].fPos.x + WIDTH , g_aGate[nCntNotes].fPos.y , 0.0f);
		pVtx[2 + 4 * nCntNotes].pos = D3DXVECTOR3(g_aGate[nCntNotes].fPos.x , g_aGate[nCntNotes].fPos.y + g_aGate[nCntNotes].fSize.y, 0.0f);
		pVtx[3 + 4 * nCntNotes].pos = D3DXVECTOR3(g_aGate[nCntNotes].fPos.x  + WIDTH , g_aGate[nCntNotes].fPos.y + g_aGate[nCntNotes].fSize.y, 0.0f);

		pVtx[0 + 4 * nCntNotes].tex = D3DXVECTOR2( 0.0f , 0.0f );
		pVtx[1 + 4 * nCntNotes].tex = D3DXVECTOR2( 0.25f , 0.0f );
		pVtx[2 + 4 * nCntNotes].tex = D3DXVECTOR2( 0.0f , 1.0f );
		pVtx[3 + 4 * nCntNotes].tex = D3DXVECTOR2( 0.25f , 1.0f );

		//rhwの設定(必ず1.0fを入れる!!!!!!!!)
		pVtx[0 + 4 * nCntNotes].rhw = 1.0f;
		pVtx[1 + 4 * nCntNotes].rhw = 1.0f;
		pVtx[2 + 4 * nCntNotes].rhw = 1.0f;
		pVtx[3 + 4 * nCntNotes].rhw = 1.0f;

		//頂点カラー(0～255の整数値)
		pVtx[0 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[1 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[2 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[3 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

	} // EO for

	//鍵をアンロック
	g_pVtxBufferGate -> Unlock();

	return S_OK;
}//EOMakeVertexNotes

GATE* GetGate(void)
{
	return &g_aGate[0];
}

void AddLife(int nIdx , int nLife)
{
	g_aGate[nIdx].nHp += nLife;


	if(nLife > 0)
	{
		SetEffect(g_aGate[nIdx].fPos.x + g_aGate[nIdx].fSize.x / 2 , g_aGate[nIdx].fPos.y + g_aGate[nIdx].fSize.y / 2 , g_aGate[nIdx].fSize.x * 3, LINE_HEIGHT ,EFFECT_RECOVER);
	}

	if(nLife < 0)
	{
		PlaySound(SE_GAME_GATE_BREAK);
	}
	if(g_aGate[nIdx].nHp >= 100)
	{
		g_aGate[nIdx].nHp = 100;
	}

	if(g_aGate[nIdx].nHp <= 0)
	{
		g_aGate[nIdx].nHp = 0;
		PlaySound(SE_GAME_GATE_BREAK_ALL);
	}
}
