/*****************************************************************************
fade.h
Aythor	: ���@��
Data	: 2016_09_28
=============================================================================
Updata

*****************************************************************************/
#ifndef	FADE_H
#define	FADE_H

//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef enum
{
	FADE_IN = 0,		//�t�F�[�h�C��
	FADE_OUT,			//�t�F�[�h�A�E�g
	FADE_MODE_MAX,		//�t�F�[�h���[�h����
	FADE_MODE_NONE		//NULL
}FADE_MODE;


//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
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