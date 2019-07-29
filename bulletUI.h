/*****************************************************************************
bulletUI.h
Aythor	: ���@��
Data	: 2017_05_21
=============================================================================
Updata

*****************************************************************************/
#ifndef BULLET_UI_H
#define BULLET_UI_H
//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef enum
{
	BULLET_UI000 = 0,
	BULLET_UI_WHITE,
	BULLET_UI_MAX
}BULLET_UI_TYPE;

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
HRESULT	initBulletUI	( void );
void	uninitBulletUI	( void );
void	updateBulletUI	( void );
void	drawBulletUI	( void );
int		setBulletUI		( const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR color );
void	setBulletUICoolTime	( const UINT num, const UINT coolTime );
int		getBulletCoolTime(const UINT num);

#endif