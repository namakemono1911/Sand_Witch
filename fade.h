/*****************************************************************************
fade.h
Aythor	: 上野　匠
Data	: 2016_09_28
=============================================================================
Updata

*****************************************************************************/
#ifndef	FADE_H
#define	FADE_H

//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef enum
{
	FADE_IN = 0,		//フェードイン
	FADE_OUT,			//フェードアウト
	FADE_MODE_MAX,		//フェードモード総数
	FADE_MODE_NONE		//NULL
}FADE_MODE;


//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
void	initFade		( void );
void	uninitFade		( void );
void	updateFade		( void );
void	setFade			( char *texAdd, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR2 texPos, D3DXVECTOR2 texSize );
void	startFadeIn		( int time, D3DXCOLOR color );
void	startFadeOut	( int time, D3DXCOLOR color, MODE nextMode );
void	setFadeMode		( FADE_MODE mode );
void	drawFade		( void );
bool	getFadeAction	( void );

#endif