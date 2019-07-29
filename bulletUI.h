/*****************************************************************************
bulletUI.h
Aythor	: 上野　匠
Data	: 2017_05_21
=============================================================================
Updata

*****************************************************************************/
#ifndef BULLET_UI_H
#define BULLET_UI_H
//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef enum
{
	BULLET_UI000 = 0,
	BULLET_UI_WHITE,
	BULLET_UI_MAX
}BULLET_UI_TYPE;

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
HRESULT	initBulletUI	( void );
void	uninitBulletUI	( void );
void	updateBulletUI	( void );
void	drawBulletUI	( void );
int		setBulletUI		( const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR color );
void	setBulletUICoolTime	( const UINT num, const UINT coolTime );
int		getBulletCoolTime(const UINT num);

#endif