//===================================================
//
// フェードヘッダー
// Author : Sato Teruto
//
//===================================================
#ifndef _FADE_H_
#define _FADE_H_	

//-------------------------------
// インクルード
//--------------------------------
#include <d3dx9.h>
#include "object.h"
#include "mode.h"
#include "object2d.h"

//================================
// フェードクラスの定義
//================================
class CFade
{
public:
	//フェードの状態
	enum FADE
	{
		FADE_NONE = 0,	//何もしていない状態
		FADE_IN,		//フェードイン状態
		FADE_OUT,		//フェードアウト状態
		FADE_MAX
	};

	CFade();	//コンストラクタ
	~CFade();	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init(CMode::MODE modeNext);
	void Uninit();
	void Update();
	void Draw();
	void SetFade(CMode::MODE modeNext);
	FADE GetFade(void) { return m_fade; };

private:
	//------------------
	// メンバ変数
	//------------------
	FADE		m_fade;			//フェードの状態
	D3DXCOLOR	m_col;			//ポリゴン(フェード)の色
	CMode::MODE m_modeNext;		//次の画面(モード)
	CObject2D*	m_pObject;		//フェード用ポリゴン

};

#endif