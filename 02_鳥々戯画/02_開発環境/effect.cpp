//===================================
//
// エフェクトの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "effect.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "texture.h"

//===========================
// コンストラクタ
//===========================
CEffect::CEffect() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);		//位置
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//色
	m_fRadius = 0.0f;	//半径(大きさ)
}

//===========================
// デストラクタ
//===========================
CEffect::~CEffect()
{

}

//===========================
// 初期化
//===========================
HRESULT CEffect::Init(D3DXVECTOR3 pos)
{
	//構造体の初期化
	m_pos = pos;			//位置
	m_fRadius = 50.0f;	//半径
	m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);	//色

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fRadius, m_fRadius);	//サイズの設定

	CObject2D::SetTexture(CTexture::TEXTURE_EFFECT);		//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CEffect::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CEffect::Update()
{
	CObject2D::Update();

	//徐々に小さくする
	m_fRadius -= 1.0f;

	//徐々に透明にする
	m_col.a -= 0.05f;

	if (m_fRadius <= 0.0f || m_col.a <= 0.0f)
	{//小さくなって消えた or 完全に透明なら
		//エフェクトの消去
		Uninit();
		return;
	}
	else
	{
		//サイズの設定
		SetSize(m_fRadius, m_fRadius);

		//色の設定
		CObject2D::SetColor(m_col);
	}
}

//===========================
// 描画
//===========================
void CEffect::Draw()
{
	//αブレンディングを加算合成に設定
	CObject2D::SetAddALPHA();

	CObject2D::Draw();

	//αブレンディングを元に戻す
	CObject2D::ResAddALPHA();
}

//===========================
// 生成
//===========================
CEffect *CEffect::Create(D3DXVECTOR3 pos)
{
	CEffect *pEffect = nullptr;

	//----------------------------------
	// プレイヤーの生成と初期化
	//----------------------------------
	pEffect = new CEffect;	//生成

	if (pEffect != nullptr)
	{//NULLチェック
		//初期化
		pEffect->Init(pos);
		pEffect->SetObjType(OBJTYPE_EFFECT);
	}

	return pEffect;
}