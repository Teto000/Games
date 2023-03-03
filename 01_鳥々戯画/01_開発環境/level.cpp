//===================================
//
// レベルの処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "level.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"
#include "sound.h"
#include "exp.h"

//---------------------------
// 静的メンバ変数宣言
//---------------------------
int CLevel::m_nExpPoint = 0;

//===========================
// コンストラクタ
//===========================
CLevel::CLevel() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//回転
	m_nLevel = 0;
	m_nExpPoint = 0;
	m_fLength = 0.0f;	//幅
	m_pExp = nullptr;
}

//===========================
// デストラクタ
//===========================
CLevel::~CLevel()
{

}

//===========================
// 初期化
//===========================
HRESULT CLevel::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;
	m_fLength = 80;		//幅
	m_nLevel = 1;		//レベル

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fLength, m_fLength);

	CObject2D::SetTexCIE(0.0f, 0.2f);

	CObject2D::SetTexture(CTexture::TEXTURE_LEVEL);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CLevel::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CLevel::Update()
{
	CObject2D::Update();

	LevelUp();
}

//===========================
// 描画
//===========================
void CLevel::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CLevel *CLevel::Create()
{
	CLevel *pLevel = nullptr;

	//----------------------------------
	// レベルの生成と初期化
	//----------------------------------
	pLevel = new CLevel;	//生成

	if (pLevel != nullptr)
	{//NULLチェック
		//初期化
		pLevel->Init(D3DXVECTOR3(120.0f, 75.0f, 0.0f));
		pLevel->SetObjType(OBJTYPE_LEVEL);
	}

	return pLevel;
}

//===========================
// レベルアップ
//===========================a
void CLevel::LevelUp()
{
	//取得した経験値で出現するゲージ分回す
	for (int i = 0; i < m_nExpPoint / (5 * m_nLevel); i++)
	{
		//円形に移動した座標を求める
		D3DXVECTOR3 CirclePos = CObject2D::MoveCircle(m_pos, m_rot.x, m_fLength * 0.6f);

		//位置の設定
		CObject2D::SetPosition(m_pos);

		//-----------------------
		// レベルアップの処理
		//-----------------------
		if (m_nLevel > nMaxLevel)
		{//レベルが最大なら
			return;
		}

		if (m_nExpPoint < (5 * m_nLevel))
		{//一定経験値量に達していないなら
			return;
		}

		//経験値ゲージの生成
		m_pExp = CExp::Create(CirclePos, m_rot, m_fLength * 0.6f);

		if (m_rot.x >= 360.0f)
		{//ゲージが一周したら
			m_rot.x -= 360.0f;	//正規化

								//テクスチャ座標の変更
			CObject2D::SetTexCIE(0.0f + (0.2f * m_nLevel), 0.2f + (0.2f * m_nLevel));
			m_nLevel++;		//レベルの加算
		}
		else
		{
			//経験値ゲージを配置する角度を加算
			m_rot.x += 30.0f;
		}
	}

	//経験値の値をリセット
	m_nExpPoint = 0;
}

//===========================
// レベルの取得
//===========================
int CLevel::GetLevel()
{
	return m_nLevel;
}

//===========================
// 経験値の加算
//===========================
void CLevel::AddExp(int nValue)
{
	m_nExpPoint += nValue;
}