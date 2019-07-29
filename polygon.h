/*****************************************************************************
polygon.h
Aythor	: 上野　匠
Data	: 2016_07_05
=============================================================================
Updata

*****************************************************************************/
#ifndef POLYGON_H
#define POLYGON_H

//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3	pos;		//表示座標
	D3DXVECTOR3	size;		//ポリゴンの幅高さ
}POLYGON;

typedef struct
{
	POLYGON		conf;		//中心座標とサイズ
	float	rot;			//ポリゴンの回転量
	FLOAT	length;			//ポリゴンの対角線の長さ
	float	angle;			//ポリゴンの対角線の角度
}ROTPOLYGON;

typedef struct
{
	D3DXVECTOR2	pos;		//テクスチャの描画位置
	D3DXVECTOR2	size;		//テクスチャのサイズ
}TEXTURE;

//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
void initDevice ( void );
void addDevice ( void );
void initPolygon ( POLYGON *polygon, D3DXVECTOR3 pos, D3DXVECTOR3 size );
void initRotPolygon ( ROTPOLYGON *polygon, D3DXVECTOR3 pos, D3DXVECTOR3 size );
void initTexture ( TEXTURE	*tex, D3DXVECTOR2 pos, D3DXVECTOR2 size );
void setTexture ( VERTEX2D *pVtx, TEXTURE texture );
void setBuffer ( VERTEX2D *pVtx, POLYGON polygon );
void setListBuffer ( VERTEX2D *pVtx, POLYGON polygon );
void setRotBuffer ( VERTEX2D *pVtx, ROTPOLYGON polygon );
void setDegenerate ( VERTEX2D *pVtx, D3DXVECTOR3 pos, D3DXVECTOR3 nextPos );

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////

#endif