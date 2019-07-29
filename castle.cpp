//============================================
//  castle関数  (castle.cpp)
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
#include "castle.h"
#include "game.h"
#include "sound.h"

//============================================
//
//  マクロ定義
//
//============================================
#define CASTLE_TEX_NAME	"data/TEXTURE/GAME/CASTLE/castle01.png"	// テクスチャ名

#define CASTLE_HP 100	// 耐久力

//============================================
//
//  グローバル変数
//
//============================================
//LPはポインター!!
LPDIRECT3DTEXTURE9 g_pTextureCastle = NULL;//Notesの張るテクスチャ、テクスチャインターフェース

/*頂点バッファ管理用*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferCastle = NULL;//ポインター!!&初期化

/*門構造体*/
CASTLE g_aCastle[CASTLE_NUM];

//============================================
//
//  プロトタイプ宣言
//
//============================================
HRESULT MakeVertexCastle(LPDIRECT3DDEVICE9 pDevice);

//============================================
//
//  名前  InitCastle関数
//  引数   int nStage
//  戻り値 void
//  説明   門の初期化
//
//============================================
void InitCastle(int nStage)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();


	// 門構造体の初期化

	for(int i = 0 ; i < CASTLE_NUM ; i++)
	{
		g_aCastle[i].bUse = true;
		g_aCastle[i].fPos = D3DXVECTOR3(CASTLE_POSX , CASTLE_POSY , 0.0f);
		g_aCastle[i].fSize = D3DXVECTOR2(CASTLE_WIDTH , CASTLE_HEIGHT);
		g_aCastle[i].fUV = D3DXVECTOR2(0.0f , 0.0f);
		g_aCastle[i].nHp = CASTLE_HP;
	} // EO for

	//頂点作成
	if(FAILED(MakeVertexCastle(pDevice)))
	{
		return;
	} // EO if

	// テクスチャ取得
	if(FAILED(D3DXCreateTextureFromFile( pDevice , CASTLE_TEX_NAME , &g_pTextureCastle )))
	{
		MessageBox(NULL , "門テクスチャが取得できませんでした" , "ERROR" , MB_OK);
	} // EO if

} // EO InitCastle

//============================================
//
//  名前  UninitCastle関数
//  引数   void
//  戻り値 void
//  説明   門の終了
//
//============================================
void UninitCastle(void)
{
	// インターフェースの解放
	SAFE_RELEASE(g_pTextureCastle);
	SAFE_RELEASE(g_pVtxBufferCastle);

} // EO UninitCastle

//============================================
//
//  名前  UpdateCastle関数
//  引数   void
//  戻り値 void
//  説明   門の更新
//
//============================================
void UpdateCastle(void)
{
	//頂点バッファ
	VERTEX2D* pVtx;
	//頂点バッファをロックして、仮想アドレスを取得する
	g_pVtxBufferCastle -> Lock(0,0,(void**)&pVtx,0);

	if(g_aCastle[0].nHp >= 50)
	{
		pVtx[0].tex = D3DXVECTOR2( 0.0f , 0.0f );
		pVtx[1].tex = D3DXVECTOR2( 0.25f , 0.0f );
		pVtx[2].tex = D3DXVECTOR2( 0.0f , 1.0f );
		pVtx[3].tex = D3DXVECTOR2( 0.25f , 1.0f );
	}
	else if(g_aCastle[0].nHp < 50 && g_aCastle[0].nHp >= 30)
	{
		pVtx[0].tex = D3DXVECTOR2( 0.25f , 0.0f );
		pVtx[1].tex = D3DXVECTOR2( 0.5f , 0.0f );
		pVtx[2].tex = D3DXVECTOR2( 0.25f , 1.0f );
		pVtx[3].tex = D3DXVECTOR2( 0.5f , 1.0f );
	}
	else if(g_aCastle[0].nHp < 30 && g_aCastle[0].nHp > 0)
	{
		pVtx[0].tex = D3DXVECTOR2( 0.5f , 0.0f );
		pVtx[1].tex = D3DXVECTOR2( 0.75f , 0.0f );
		pVtx[2].tex = D3DXVECTOR2( 0.5f , 1.0f );
		pVtx[3].tex = D3DXVECTOR2( 0.75f , 1.0f );
	}
	else
	{
		pVtx[0].tex = D3DXVECTOR2( 0.75f , 0.0f );
		pVtx[1].tex = D3DXVECTOR2( 1.00f , 0.0f );
		pVtx[2].tex = D3DXVECTOR2( 0.75f , 1.0f );
		pVtx[3].tex = D3DXVECTOR2( 1.00f , 1.0f );
	}

	g_pVtxBufferCastle -> Unlock();

} // EO UpdateCastle

//============================================
//
//  名前  DrawCastle関数
//  引数   void
//  戻り値 void
//  説明   門の描画
//
//============================================
void DrawCastle(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//パイプラインの設定
	pDevice -> SetStreamSource(0,//ストリーム番号(何本も作れる)
						g_pVtxBufferCastle ,//データのある場所(先頭アドレス)
						0,//オフセット(単位バイト)、データのどの辺から持ってくるか,0は先頭
						sizeof(VERTEX2D) );//ストライド量(一個の単位の大きさ)

	//頂点フォーマットの設定
	pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

	for(int nCntNotes = 0 ; nCntNotes < CASTLE_NUM ; nCntNotes++ )
	{
		if(g_aCastle[nCntNotes].bUse == false)
		{
			int i = 0;
		}
		if(g_aCastle[nCntNotes].bUse == true)
		{
			pDevice->SetTexture(0  ,g_pTextureCastle);
			//プリミティブの描画
			pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
				nCntNotes * 4 ,//オフセット(頂点数)何頂点目からとるか
				NUM_POLYGON );//いくつ頂点持ってくればいいのか、プリミティブの枚数を教えたゲル。パイプラインは垂れ流しになっているから。
		} // EO if
	} // EO fro

} // EO DrawCastle

//============================================
//
//  名前  MakeVertexCastle関数
//  引数	LPDIRECT3DDEVICE9 pDevice
//  戻り値  void
//  説明  頂点の作成
//
//============================================
HRESULT MakeVertexCastle(LPDIRECT3DDEVICE9 pDevice)
{
	//頂点バッファ作成
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX,D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBufferCastle,NULL)))
	{
		MessageBox(NULL , "頂点バッファの作成に失敗しました" , "ERROR" , MB_OK);
		return E_FAIL;
	} // EO if


	//頂点バッファ
	VERTEX2D* pVtx;
	//頂点バッファをロックして、仮想アドレスを取得する
	g_pVtxBufferCastle -> Lock(0,0,(void**)&pVtx,0);

	for(int nCntNotes = 0 ; nCntNotes < CASTLE_NUM ; nCntNotes++)
	{
		pVtx[0 + 4 * nCntNotes].pos = D3DXVECTOR3(g_aCastle[nCntNotes].fPos.x , g_aCastle[nCntNotes].fPos.y , 0.0f);
		pVtx[1 + 4 * nCntNotes].pos = D3DXVECTOR3(g_aCastle[nCntNotes].fPos.x + CASTLE_WIDTH , g_aCastle[nCntNotes].fPos.y , 0.0f);
		pVtx[2 + 4 * nCntNotes].pos = D3DXVECTOR3(g_aCastle[nCntNotes].fPos.x , g_aCastle[nCntNotes].fPos.y + g_aCastle[nCntNotes].fSize.y, 0.0f);
		pVtx[3 + 4 * nCntNotes].pos = D3DXVECTOR3(g_aCastle[nCntNotes].fPos.x  + CASTLE_WIDTH , g_aCastle[nCntNotes].fPos.y + g_aCastle[nCntNotes].fSize.y, 0.0f);

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
	g_pVtxBufferCastle -> Unlock();

	return S_OK;
}//EOMakeVertexNotes

void AddDamegeCastle(int nDamege)
{
	g_aCastle[0].nHp -= nDamege;
	if(g_aCastle[0].nHp <= 0)
	{
		g_aCastle[0].nHp = 0;
		PlaySound(SE_GAME_GATE_BREAK_ALL);
		setGameState(LOSE);
	}
	else
	{
		PlaySound(SE_GAME_GATE_BREAK);
	}
}

int GetCastleHp(void)
{
	return g_aCastle[0].nHp;
}
