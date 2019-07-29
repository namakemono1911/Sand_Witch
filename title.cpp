//==========================================================================================
//	�^�C�g������[title.cpp]
//	Author : KAZUNORI MARUHASHI
//
//	Update :
//		YYYY/MM/DD	Updater :
//
//		2017/06/12	Updater : KAZUNORI MARUHASHI
//			�E���ō쐬
//			�E����L�[������̏����� JUMP ����
//			
//			
//	
//==========================================================================================

//==========================================================================================
// �C���N���[�h�t�@�C��
//==========================================================================================
#include "main.h"		//���C������
#include "input.h"		//���͏���
#include "inputX.h"		//���͏���
#include "sound.h"		//�T�E���h����
#include "title.h"		//�X�e�[�W�Z���N�g����
#include "fade.h"		//�t�F�[�h����

//==========================================================================================
// �}�N����`
//==========================================================================================
//�e�N�X�`���֌W
#define TITLE_TITLE_TEXTURENAME		"data/TEXTURE/TITLE/title.png"		//�X�e�[�W�Z���N�g����
#define TITLE_START_TEXTURENAME		"data/TEXTURE/TITLE/titleASC.png"	//�`���[�g���A������
#define TITLE_STAGE1_TEXTURENAME	"data/TEXTURE/GAME/BG/stageBG01.jpg"	//���摜
#define TITLE_STAGE2_TEXTURENAME	"data/TEXTURE/GAME/BG/stageBG02.jpg"	//��R�摜
#define TITLE_STAGE3_TEXTURENAME	"data/TEXTURE/GAME/BG/stageBG03.jpg"	//�ΎR�摜


//=========�ʒu�֘A(���W�͒��S���w��)==========//
//�w�i
#define TITLE_BG_POSX		(SCREEN_WIDTH  * 0.5f)
#define TITLE_BG_POSY		(SCREEN_HEIGHT * 0.5f)
#define TITLE_BG_SIZEX		(SCREEN_WIDTH)
#define TITLE_BG_SIZEY		(SCREEN_HEIGHT)

//�^�C�g������
#define TITLE_TITLE_POSX	(SCREEN_WIDTH  * 0.50f)
#define TITLE_TITLE_POSY	(SCREEN_HEIGHT * 0.25f)
#define TITLE_TITLE_SIZEX	(SCREEN_WIDTH  * 0.50f)
#define TITLE_TITLE_SIZEY	(SCREEN_HEIGHT * 0.20f)

//�Q�[���X�^�[�g
#define TITLE_START_POSX	(SCREEN_WIDTH  * 0.50f)
#define TITLE_START_POSY	(SCREEN_HEIGHT * 0.65f)
#define TITLE_START_SIZEX	(SCREEN_WIDTH  * 0.30f)
#define TITLE_START_SIZEY	(SCREEN_HEIGHT * 0.20f)

//�w�i�e�N�X�`���̏���U�l
#define TITLE_TEXTURE_SIZEU (0.7f)	

//�w�i�e�N�X�`���ړ���
#define TITLE_TEXTURE_MOVEU (0.001f)

//�w�i�t�F�[�h���x
#define TITLE_BGFADE_FRAME (120)

#define ONESECOND_FRAME (60)	//�P�b�̃t���[����

#define START_FADE_FRAME (ONESECOND_FRAME * 2)		//�ʏ펞�̃X�^�[�g�����_�ő��x
#define START_FADE_DICISION_FRAME (ONESECOND_FRAME)	//����L�[�������̃X�^�[�g�����_�ő��x

#define DICISION_KEY (DIK_Z)	//����L�[
#define CANCEL_KEY (DIK_X)		//�L�����Z���L�[

//==========================================================================================
// �\���̒�`
//==========================================================================================
//�e�N�X�`�����o�^�p�\����
struct CREATETEX
{
	char cStr[256];
	TITLE_TEX_LABEL label;
};

//==========================================================================================
// �v���g�^�C�v�錾
//==========================================================================================
HRESULT MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice);

//==========================================================================================
// �O���[�o���ϐ�
//==========================================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferTitle = NULL;
TITLE g_TitleObj[TITLE_OBJ_MAX];
LPDIRECT3DTEXTURE9 g_pTextureTitle[TITLE_TEX_MAX] = {};	//�e�N�X�`���C���^�[�t�F�[�X

bool bDicision;	//����L�[�������ꂽ��
bool bBGAlpha;	//�w�iBG
bool bStartAlpha;	//�X�^�[�g�����_�ŉ�
	
//�e�I�u�W�F�N�g�̏����ݒ�(�ʒu�A�T�C�Y�AUV�l�AUV�T�C�Y�A�e�N�X�`��ID, ���l, �`��L��)
const TITLE coTitleObj[TITLE_OBJ_MAX] =
{
	//�w�i
	{D3DXVECTOR3(TITLE_BG_POSX, TITLE_BG_POSY, 0.0f),
	 D3DXVECTOR3(TITLE_BG_SIZEX, TITLE_BG_SIZEY, 0.0f), 
	 D3DXVECTOR2(0.0f, 0.0f),
	 D3DXVECTOR2(TITLE_TEXTURE_SIZEU, 1.0f),
	 TITLE_TEX_STAGE1, 
	 1.0f, 
	 true
	}, 

	//�w�i�t�F�[�h�p
	{D3DXVECTOR3(TITLE_BG_POSX, TITLE_BG_POSY, 0.0f),
	 D3DXVECTOR3(TITLE_BG_SIZEX, TITLE_BG_SIZEY, 0.0f), 
	 D3DXVECTOR2(0.0f, 0.0f),
	 D3DXVECTOR2(1.0f, 1.0f),
	 TITLE_TEX_NONE, 
	 0.0f, 
	 true
	},

	//�^�C�g������
	{D3DXVECTOR3(TITLE_TITLE_POSX, TITLE_TITLE_POSY, 0.0f),
	 D3DXVECTOR3(TITLE_TITLE_SIZEX, TITLE_TITLE_SIZEY, 0.0f), 
	 D3DXVECTOR2(0.0f, 0.0f),
	 D3DXVECTOR2(1.0f, 1.0f),
	 TITLE_TEX_TITLE, 
	 1.0f, 
	 true
	}, 

	//�Q�[���X�^�[�g����
	{D3DXVECTOR3(TITLE_START_POSX, TITLE_START_POSY, 0.0f),
	 D3DXVECTOR3(TITLE_START_SIZEX, TITLE_START_SIZEY, 0.0f), 
	 D3DXVECTOR2(0.0f, 0.0f),
	 D3DXVECTOR2(1.0f, 1.0f),
	 TITLE_TEX_GAMESTART, 
	 1.0f, 
	 true
	}, 


};

//�e�N�X�`���̓o�^���(�t�@�C���A�h���X, ���x��)
const CREATETEX coTitleTex[TITLE_TEX_MAX] =
{
	{"", TITLE_TEX_NONE},
	{TITLE_STAGE1_TEXTURENAME, TITLE_TEX_STAGE1}, 
	{TITLE_STAGE2_TEXTURENAME, TITLE_TEX_STAGE2}, 
	{TITLE_STAGE3_TEXTURENAME, TITLE_TEX_STAGE3}, 
	{TITLE_TITLE_TEXTURENAME, TITLE_TEX_TITLE}, 
	{TITLE_START_TEXTURENAME, TITLE_TEX_GAMESTART}, 
};

//==========================================================================================
// ����������
//==========================================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�̎擾

	//���_�̐ݒ�
	if(FAILED(MakeVertexTitle(pDevice)))
	{
		MessageBox(NULL, "���_�o�b�t�@�̐ݒ�Ɏ��s���܂����B", " ", MB_OK);
		return;
	}

	//�t�F�[�h�C��
	startFadeIn(60, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	//�e�N�X�`������
	for(int i = 0; i < TITLE_TEX_MAX; i++){
		if(coTitleTex[i].label != TITLE_TEX_NONE){
			char cErrmsg[256] = "";
			strcat(cErrmsg, coTitleTex[i].cStr);
			strcat(cErrmsg, "�̐����Ɏ��s���܂����B");

			if(FAILED(D3DXCreateTextureFromFile(
					  pDevice , 
					  coTitleTex[i].cStr,
					  &g_pTextureTitle[coTitleTex[i].label] )))
					  {
							//�G���[���b�Z�[�W
							MessageBox(NULL , cErrmsg, "�G���[",MB_OK | MB_DEFBUTTON1);
					  }//EOif
		}
	}

	//�I�u�W�F�N�g�������e�ݒ�
	for(int i = 0; i < TITLE_OBJ_MAX; i++){
		g_TitleObj[i] = coTitleObj[i];
	}

	//�_�Ŋ֘A������
	bDicision = false;
	bBGAlpha = false;
	bStartAlpha = false;

	//BGM�Đ�
	PlaySound(BGM_TITLE);
}

//==========================================================================================
// �I������
//==========================================================================================
void UninitTitle(void)
{
	if(g_pVtxBufferTitle != NULL)
	{
		g_pVtxBufferTitle -> Release();
		g_pVtxBufferTitle = NULL;
	}
	for(int iSelf = 0; iSelf < TITLE_TEX_MAX; iSelf++){
		if(g_pTextureTitle[iSelf] != NULL){
			g_pTextureTitle[iSelf] -> Release();
			g_pTextureTitle[iSelf] = NULL;
		}
	}
	StopSound(BGM_TITLE);
}

//==========================================================================================
// �X�V����
//==========================================================================================
void UpdateTitle(void)
{
	//�X�^�[�g�����_��
	if(false == bDicision){
		if(false == bStartAlpha){
			g_TitleObj[TITLE_OBJ_START].fAlpha += 1.0f / START_FADE_FRAME;
			if(g_TitleObj[TITLE_OBJ_START].fAlpha >= 1.0f){
				g_TitleObj[TITLE_OBJ_START].fAlpha = 1.0f;
				bStartAlpha = true;
			}
		}
		else{
			g_TitleObj[TITLE_OBJ_START].fAlpha -= 1.0f / START_FADE_FRAME;
			if(g_TitleObj[TITLE_OBJ_START].fAlpha <= 0.0f){
				g_TitleObj[TITLE_OBJ_START].fAlpha = 0.0f;
				bStartAlpha = false;
			}
		}
	}
	else{
		if(false == bStartAlpha){
			g_TitleObj[TITLE_OBJ_START].fAlpha += 1.0f / START_FADE_DICISION_FRAME;
			if(g_TitleObj[TITLE_OBJ_START].fAlpha >= 1.0f){
				g_TitleObj[TITLE_OBJ_START].fAlpha = 1.0f;
				bStartAlpha = true;
			}
		}
		else{
			g_TitleObj[TITLE_OBJ_START].fAlpha -= 1.0f / START_FADE_DICISION_FRAME;
			if(g_TitleObj[TITLE_OBJ_START].fAlpha <= 0.0f){
				g_TitleObj[TITLE_OBJ_START].fAlpha = 0.0f;
				bStartAlpha = false;
			}
		}
	}
	

	//�w�i�ړ�
	static TITLE_TEX_LABEL label;
	if(g_TitleObj[TITLE_OBJ_BG].UV.x + TITLE_TEXTURE_SIZEU < 1.0f){
		g_TitleObj[TITLE_OBJ_BG].UV.x += TITLE_TEXTURE_MOVEU;
		g_TitleObj[TITLE_OBJ_BGFADE].fAlpha -= 1.0f / TITLE_BGFADE_FRAME;
		label = g_TitleObj[TITLE_OBJ_BG].label;

		if(g_TitleObj[TITLE_OBJ_BGFADE].fAlpha <= 0.0f){
			g_TitleObj[TITLE_OBJ_BGFADE].fAlpha = 0.0f;
		}
	}

	if(g_TitleObj[TITLE_OBJ_BG].UV.x + TITLE_TEXTURE_SIZEU >= 1.0f){
		//�w�i�t�F�[�h
		if(g_TitleObj[TITLE_OBJ_BGFADE].fAlpha < 1.0f){
			g_TitleObj[TITLE_OBJ_BG].UV.x = 1.0f - TITLE_TEXTURE_SIZEU;
			g_TitleObj[TITLE_OBJ_BGFADE].fAlpha += 1.0f / TITLE_BGFADE_FRAME;
		}
		else if(g_TitleObj[TITLE_OBJ_BGFADE].fAlpha >- 1.0f && g_TitleObj[TITLE_OBJ_BG].label == label) {
			g_TitleObj[TITLE_OBJ_BGFADE].fAlpha = 1.0f;
			//�`�悷��e�N�X�`���̕ύX
			if(g_TitleObj[TITLE_OBJ_BG].label == TITLE_TEX_STAGE1){
				g_TitleObj[TITLE_OBJ_BG].label = TITLE_TEX_STAGE2;
				g_TitleObj[TITLE_OBJ_BG].UV.x = 0.0f;
			}
			else if(g_TitleObj[TITLE_OBJ_BG].label == TITLE_TEX_STAGE2){
				g_TitleObj[TITLE_OBJ_BG].label = TITLE_TEX_STAGE3;
				g_TitleObj[TITLE_OBJ_BG].UV.x = 0.0f;
			}
			else{
				g_TitleObj[TITLE_OBJ_BG].label = TITLE_TEX_STAGE1;
				g_TitleObj[TITLE_OBJ_BG].UV.x = 0.0f;
			}
		}
	}

	//����L�[����������
	if(GetKeyboardTrigger(DICISION_KEY) || GetKeyXInputTrigger(XINPUT_GAMEPAD_A)){
		bDicision = true;
		g_TitleObj[TITLE_OBJ_START].fAlpha = 1.0f;
		bStartAlpha = true;
		PlaySound(SE_PUSH);

		// JUMP //
		startFadeOut(60, D3DXCOLOR(1.f, 1.f, 1.f, 0.f), STAGE_SELECT);
	}


	VERTEX2D* pVtx;	//���z�A�h���X�擾�p�|�C���^
	//���z�A�h���X���擾����
	g_pVtxBufferTitle -> Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ�
	for(int VtxLoop = 0; VtxLoop < TITLE_OBJ_MAX; VtxLoop++){
		//���_���W�̐ݒ�ix, y, z�j
		pVtx[0+4*VtxLoop].pos = D3DXVECTOR3(g_TitleObj[VtxLoop].Pos.x - g_TitleObj[VtxLoop].Size.x * 0.5f,
											g_TitleObj[VtxLoop].Pos.y - g_TitleObj[VtxLoop].Size.y * 0.5f, 0.0f);

		pVtx[1+4*VtxLoop].pos = D3DXVECTOR3(g_TitleObj[VtxLoop].Pos.x + g_TitleObj[VtxLoop].Size.x * 0.5f,
											g_TitleObj[VtxLoop].Pos.y - g_TitleObj[VtxLoop].Size.y * 0.5f, 0.0f);

		pVtx[2+4*VtxLoop].pos = D3DXVECTOR3(g_TitleObj[VtxLoop].Pos.x - g_TitleObj[VtxLoop].Size.x * 0.5f,
											g_TitleObj[VtxLoop].Pos.y + g_TitleObj[VtxLoop].Size.y * 0.5f, 0.0f);

		pVtx[3+4*VtxLoop].pos = D3DXVECTOR3(g_TitleObj[VtxLoop].Pos.x + g_TitleObj[VtxLoop].Size.x * 0.5f,
											g_TitleObj[VtxLoop].Pos.y + g_TitleObj[VtxLoop].Size.y * 0.5f, 0.0f);		

		//�J���[�̐ݒ�
		pVtx[0+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_TitleObj[VtxLoop].fAlpha);
		pVtx[1+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_TitleObj[VtxLoop].fAlpha);
		pVtx[2+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_TitleObj[VtxLoop].fAlpha);
		pVtx[3+4*VtxLoop].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_TitleObj[VtxLoop].fAlpha);

		//�e�N�X�`���\���W�̐ݒ�
		pVtx[0+4*VtxLoop].tex = D3DXVECTOR2(g_TitleObj[VtxLoop].UV.x,
											g_TitleObj[VtxLoop].UV.y);
		pVtx[1+4*VtxLoop].tex = D3DXVECTOR2(g_TitleObj[VtxLoop].UV.x + g_TitleObj[VtxLoop].UVSize.x, 
											g_TitleObj[VtxLoop].UV.y);
		pVtx[2+4*VtxLoop].tex = D3DXVECTOR2(g_TitleObj[VtxLoop].UV.x, 
											g_TitleObj[VtxLoop].UV.y + g_TitleObj[VtxLoop].UVSize.y);
		pVtx[3+4*VtxLoop].tex = D3DXVECTOR2(g_TitleObj[VtxLoop].UV.x + g_TitleObj[VtxLoop].UVSize.x, 
											g_TitleObj[VtxLoop].UV.y + g_TitleObj[VtxLoop].UVSize.y);
	}

	g_pVtxBufferTitle -> Unlock();
}

//==========================================================================================
// �`�揈��
//==========================================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�̎擾
	
	pDevice ->SetStreamSource(0, 
							  g_pVtxBufferTitle,
							  0,					//�I�t�Z�b�g
							  sizeof(VERTEX2D));		//�X�g���C�h��

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF(FVF_VERTEX_2D | D3DFVF_TEX1);

	//�|���S���̕`��
	for(int iDraw = 0; iDraw < TITLE_OBJ_MAX; iDraw++){
		//�`�������ꍇ
		if(g_TitleObj[iDraw].bDraw == true){
			
			//�e�N�X�`�����g�p���邩�ǂ���
			if(g_TitleObj[iDraw].label != TITLE_TEX_NONE){
				pDevice -> SetTexture(0, g_pTextureTitle[g_TitleObj[iDraw].label]);
			}
			else{
				pDevice -> SetTexture(0, NULL);
			}
			
			//�v���~�e�B�u�̕`��
			pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
										iDraw * 4,					//�I�t�Z�b�g(���_��)
										NUM_POLYGON);			//�v���~�e�B�u��
		}
	}
}

//==========================================================================================
// ���_�̐���
//==========================================================================================
HRESULT MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX2D* pVtx;	//���z�A�h���X�擾�p�|�C���^

	if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX2D)*NUM_VERTEX*TITLE_OBJ_MAX,	//�m�ۂ��������_�o�b�t�@�̐������_��
								  D3DUSAGE_WRITEONLY,	//�m�ۂ����㒆�����邱�Ƃ͂ł��Ȃ�
								  FVF_VERTEX_2D,		//�ꉞ�������Ƃ����C
								  D3DPOOL_MANAGED,		//�������Ǘ����ǂ����邩(����͂��C��)
								  &g_pVtxBufferTitle,
								  NULL)))
	{
		return E_FAIL;
	}

	//���z�A�h���X���擾����
	g_pVtxBufferTitle -> Lock(0, 0, (void**)&pVtx, 0);

	for(int VtxLoop = 0; VtxLoop < TITLE_OBJ_MAX; VtxLoop++){

		//���_���W�̐ݒ�ix, y, z�j
		pVtx[0+4*VtxLoop].pos = D3DXVECTOR3(g_TitleObj[VtxLoop].Pos.x - g_TitleObj[VtxLoop].Size.x,
											g_TitleObj[VtxLoop].Pos.y - g_TitleObj[VtxLoop].Size.y, 0.0f);

		pVtx[1+4*VtxLoop].pos = D3DXVECTOR3(g_TitleObj[VtxLoop].Pos.x + g_TitleObj[VtxLoop].Size.x,
											g_TitleObj[VtxLoop].Pos.y - g_TitleObj[VtxLoop].Size.y, 0.0f);

		pVtx[2+4*VtxLoop].pos = D3DXVECTOR3(g_TitleObj[VtxLoop].Pos.x - g_TitleObj[VtxLoop].Size.x,
											g_TitleObj[VtxLoop].Pos.y + g_TitleObj[VtxLoop].Size.y, 0.0f);

		pVtx[3+4*VtxLoop].pos = D3DXVECTOR3(g_TitleObj[VtxLoop].Pos.x + g_TitleObj[VtxLoop].Size.x,
											g_TitleObj[VtxLoop].Pos.y + g_TitleObj[VtxLoop].Size.y, 0.0f);

		//rhw�̐ݒ�(�K��1.0f)
		pVtx[0+4*VtxLoop].rhw =
		pVtx[1+4*VtxLoop].rhw =
		pVtx[2+4*VtxLoop].rhw = 
		pVtx[3+4*VtxLoop].rhw = 1.0f;

		//�J���[�̐ݒ�
		pVtx[0+4*VtxLoop].color = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[1+4*VtxLoop].color = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[2+4*VtxLoop].color = D3DCOLOR_RGBA(255, 255, 255, 0);
		pVtx[3+4*VtxLoop].color = D3DCOLOR_RGBA(255, 255, 255, 0);

		//�e�N�X�`���\���W�̐ݒ�
		pVtx[0+4*VtxLoop].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1+4*VtxLoop].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2+4*VtxLoop].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3+4*VtxLoop].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	g_pVtxBufferTitle -> Unlock();

	return S_OK;
}
