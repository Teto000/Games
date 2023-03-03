//===================================
//
// スキル処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "skill.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
const float CSkill::nSkillSpeed = 7.0f;	//速度

//===========================
// コンストラクタ
//===========================
CSkill::CSkill() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
	m_nCntTimer = 0;		//文字の表示時間
	m_fWidth = 0.0f;		//幅
	m_fHeight = 0.0f;		//高さ
	m_type = SKILLTYPE_MAX;	//種類
}

//===========================
// デストラクタ
//===========================
CSkill::~CSkill()
{

}

//===========================
// 初期化
//===========================
HRESULT CSkill::Init(D3DXVECTOR3 pos)
{
	//構造体に代入
	m_fWidth = 320.0f;
	m_fHeight = 80.0f;
	m_pos = D3DXVECTOR3(pos.x - (m_fWidth / 2), pos.y - (m_fHeight / 2), pos.z);

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);

	switch (m_type)
	{
	case SKILLTYPE_HEAL:
		CObject2D::SetTexture(CTexture::TEXTURE_SKILL_HPHEAL);	//テクスチャの設定
		break;

	case SKILLTYPE_SPEEDUP_FIRE:
		CObject2D::SetTexture(CTexture::TEXTURE_SKILL_SPEEDUP_FIRE);
		break;

	case SKILLTYPE_ATTACKUP:
		CObject2D::SetTexture(CTexture::TEXTURE_SKILL_ATTACKUP);
		break;

	case SKILLTYPE_SPEEDUP:
		CObject2D::SetTexture(CTexture::TEXTURE_SKILL_SPEEDUP);
		break;

	default:
		break;
	}

	return S_OK;
}

//===========================
// 終了
//===========================
void CSkill::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CSkill::Update()
{
	CObject2D::Update();
}

//===========================
// 描画
//===========================
void CSkill::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CSkill *CSkill::Create(SKILLTYPE type)
{
	CSkill *pSkill = nullptr;

	//----------------------------------
	// 敵の生成と初期化
	//----------------------------------
	pSkill = new CSkill;	//生成

	if (pSkill != nullptr)
	{//NULLチェック
		//メンバ変数に代入
		pSkill->m_type = type;

		//初期化
		switch (pSkill->m_type)
		{
		case SKILLTYPE_HEAL:
			pSkill->Init(D3DXVECTOR3(320.0f, 720.0f, 0.0f));
			break;

		case SKILLTYPE_SPEEDUP_FIRE:
			pSkill->Init(D3DXVECTOR3(640.0f, 720.0f, 0.0f));
			break;

		case SKILLTYPE_ATTACKUP:
			pSkill->Init(D3DXVECTOR3(960.0f, 720.0f, 0.0f));
			break;

		case SKILLTYPE_SPEEDUP:
			pSkill->Init(D3DXVECTOR3(1280.0f, 720.0f, 0.0f));
			break;

		default:
			break;
		}
		pSkill->SetObjType(OBJTYPE_SKILL);
	}

	return pSkill;
}