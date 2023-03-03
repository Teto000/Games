//===================================
//
// ダメージ処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include <assert.h>
#include "damage.h"
#include "texture.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
int CDamage::m_nValue = 0;
int CDamage::m_nNum = 0;

//===========================
// コンストラクタ
//===========================
CDamage::CDamage() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//色
	m_nLife = 0;
	m_nDigit = 0;			//桁数
	m_fWidth = 0.0f;		//幅
	m_fHeight = 0.0f;		//高さ
	m_fSpace = 0.0f;		//間隔
	m_aPosTexU[m_nDigit] = {};
}

//===========================
// デストラクタ
//===========================
CDamage::~CDamage()
{

}

//===========================
// 初期化
//===========================
HRESULT CDamage::Init(D3DXVECTOR3 pos)
{
	//構造体の初期化
	m_pos = pos;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nLife = 70;

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);

	CObject2D::SetTexture(CTexture::TEXTURE_NUMBER);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CDamage::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CDamage::Update()
{
	CObject2D::Update();

	//桁数の計算
	int nFirst = (int)pow(10, m_nDigit);
	int nSecond = (int)pow(10, (m_nDigit - 1));
	int nDigit = (int)pow(10, m_nNum);

	//桁ごとの値を求める
	m_aPosTexU[m_nNum] = m_nValue % (nFirst / nDigit) / (nSecond / nDigit);

	//テクスチャ座標の設定
	CObject2D::SetTexCIE(m_aPosTexU[m_nNum] * 0.1f, m_aPosTexU[m_nNum] * 0.1f + 0.1f);

	//配列を進める
	if (m_nNum >= m_nDigit - 1)
	{
		m_nNum = 0;
	}
	else
	{
		m_nNum++;
	}

	//---------------------
	// 寿命の減少
	//---------------------
	m_nLife--;

	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	if (m_nLife <= 55)
	{
		//---------------------
		// ダメージ表記の移動
		//---------------------
		/*m_move = D3DXVECTOR3(0.0f, -2.0f, 0.0f);
		m_pos = CObject2D::AddMove(m_move);*/

		CObject2D::SetSize(m_fWidth, m_fHeight);

		//---------------------
		// 透明にする
		//---------------------
		m_col.a -= 0.05f;
		CObject2D::SetColor(m_col);

		if (m_col.a <= 0.0f)
		{
			Uninit();
			return;
		}
	}
	
}

//===========================
// 描画
//===========================
void CDamage::Draw()
{
	CObject2D::Draw();
}

//====================================
// 生成(位置,幅,高さ,間隔,桁数,数値)
//====================================
CDamage *CDamage::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fSpace,
						int nDigit, int nNumber)
{
	CDamage *pNumber = nullptr;

	//----------------------------------
	// プレイヤーの生成と初期化
	//----------------------------------
	for (int i = 0; i < nDigit; i++)
	{
		pNumber = new CDamage;	//生成

		if (pNumber != nullptr)
		{//NULLチェック
			//メンバ変数に代入
			pNumber->m_fWidth = fWidth;		//幅
			pNumber->m_fHeight = fHeight;	//高さ
			pNumber->m_fSpace = fSpace;		//間隔
			pNumber->m_nDigit = nDigit;		//桁数
			pNumber->m_nValue = nNumber;			//値

			//初期化
			pNumber->Init(D3DXVECTOR3(pos.x + i * fSpace, pos.y, pos.z));
			pNumber->SetObjType(OBJTYPE_SCORE);
		}
	}
	return pNumber;
}