//===================================
//
// スキル選択画面の処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "skillselect.h"
#include "renderer.h"
#include "input.h"
#include "input_keybord.h"
#include "input_joypad.h"
#include "application.h"
#include "bg.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
CBg *CSkillSelect::m_pBG = nullptr;	//背景

//===========================
// コンストラクタ
//===========================
CSkillSelect::CSkillSelect()
{

}

//===========================
// デストラクタ
//===========================
CSkillSelect::~CSkillSelect()
{

}

//===========================
// 初期化
//===========================
HRESULT CSkillSelect::Init()
{
	return S_OK;
}

//===========================
// 終了
//===========================
void CSkillSelect::Uninit()
{

}

//===========================
// 更新
//===========================
void CSkillSelect::Update()
{
	if (CInputKeyboard::Trigger(DIK_RETURN))
	{
		CApplication::SetMode(CApplication::MODE_GAME);
	}
}

//===========================
// 背景の取得
//===========================
CBg *CSkillSelect::GetBG()
{
	return m_pBG;
}