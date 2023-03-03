//===================================
//
// MPの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "mp.h"
#include "main.h"
#include "object2D.h"
#include "application.h"

//===========================
// コンストラクタ
//===========================
CMp::CMp() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_fWidth = 0.0f;		//幅
	m_fHeight = 0.0f;		//高さ
	m_fLength = 0.0f;		//MPバーの長さ
}

//===========================
// デストラクタ
//===========================
CMp::~CMp()
{
}

//===========================
// 初期化
//===========================
HRESULT CMp::Init(D3DXVECTOR3 pos)
{
	//位置の設定
	m_pos = pos;
	m_fLength = (m_fWidth / 100);

	CObject2D::Init(m_pos);
	CObject2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

	//頂点座標の設定
	CObject2D::SetVtxCIE_Gauge(m_pos, -m_fWidth / 2,
		-m_fWidth / 2 + (m_fLength * 100), -m_fHeight / 2, m_fHeight / 2);

	CObject2D::SetTexture(CTexture::TEXTURE_NONE);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CMp::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CMp::Update()
{
	CObject2D::Update();

	//MP減少時の処理
	SubMP();
}

//===========================
// 描画
//===========================
void CMp::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CMp *CMp::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CMp *pMP = nullptr;

	//----------------------------------
	// プレイヤーの生成と初期化
	//----------------------------------
	pMP = new CMp;	//生成

	if (pMP != nullptr)
	{//NULLチェック
		//メンバ変数に代入
		pMP->m_fWidth = fWidth;
		pMP->m_fHeight = fHeight;

		//初期化
		pMP->Init(pos);
		pMP->SetObjType(OBJTYPE_MP);
	}

	return pMP;
}

//===========================
// MPの設定
//===========================
void CMp::SetMP(int nMp, int nRemMp)
{
	m_nMp = nMp;
	m_nRemMp = nRemMp;

	SubMP();
}

//===========================
// MP減少時の処理
//===========================
void CMp::SubMP()
{
	//-------------------------
	// 頂点座標の設定
	//-------------------------
	if (m_nRemMp >= 1)
	{//残り体力(%)があるなら
	 //その体力分の座標を設定
		CObject2D::SetVtxCIE_Gauge(m_pos, -m_fWidth / 2,
			-m_fWidth / 2 + (m_fLength * m_nRemMp), -m_fHeight / 2, m_fHeight / 2);
	}
	else if (m_nRemMp == 0 && m_nMp > 0)
	{//残り体力が0% かつ 体力が0じゃないなら
		//1%分のゲージを維持
		CObject2D::SetVtxCIE_Gauge(m_pos, -m_fWidth / 2,
			-m_fWidth / 2 + m_fLength, -m_fHeight / 2, m_fHeight / 2);
	}
}