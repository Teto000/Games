//===================================
//
// スコア処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "score.h"
#include "texture.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
int CScore::m_nScore = 0;
int CScore::m_aPosTexU[nMaxScore] = {};
int CScore::nNum = 0;

//===========================
// コンストラクタ
//===========================
CScore::CScore() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fWidth = 0.0f;
	m_fHeight = 0.0;
	m_fSpace = 0.0f;
}

//===========================
// デストラクタ
//===========================
CScore::~CScore()
{

}

//===========================
// 初期化
//===========================
HRESULT CScore::Init(D3DXVECTOR3 pos)
{
	//構造体の初期化
	m_pos = pos;

	switch (m_mode)
	{
	case MODE_GAME:
		m_fWidth = 30.0f;		//幅
		m_fHeight = 50.0f;		//高さ
		break;

	case MODE_RESULT:
		m_fWidth = 60.0f;		//幅
		m_fHeight = 100.0f;		//高さ
		break;

	default:
		break;
	}

	m_nScore = 0;	//スコアの初期設定

	CObject2D::Init(m_pos);

	CObject2D::SetSize(m_fWidth, m_fHeight);

	CObject2D::SetTexture(CTexture::TEXTURE_NUMBER);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CScore::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CScore::Update()
{
	CObject2D::Update();

	//桁ごとの値を求める
	m_aPosTexU[nNum] = m_nScore % (1000000 / (int)pow(10, nNum)) / (100000 / (int)pow(10, nNum));

	//テクスチャ座標の設定
	CObject2D::SetTexCIE(0.0f + m_aPosTexU[nNum] * 0.1f, 0.1f + m_aPosTexU[nNum] * 0.1f);

	//配列を進める
	if (nNum >= nMaxScore - 1)
	{
		nNum = 0;
	}
	else 
	{
		nNum++;
	}
}
//===========================
// 描画
//===========================
void CScore::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CScore *CScore::Create(MODE mode)
{
	CScore *pScore = nullptr;

	//----------------------------------
	// プレイヤーの生成と初期化
	//----------------------------------
	for (int i = 0; i < nMaxScore; i++)
	{
		pScore = new CScore;	//生成

		if (pScore != nullptr)
		{//NULLチェック
			//メンバ変数に代入
			pScore->m_mode = mode;

			//初期化
			switch (pScore->m_mode)
			{
			case MODE_GAME:
				pScore->m_fSpace = 30.0f;	//間隔
				pScore->Init(D3DXVECTOR3(1095.0f + (i * pScore->m_fSpace), 90.0f, 0.0f));
				break;

			case MODE_RESULT:
				pScore->m_fSpace = 70.0f;	//間隔
				pScore->Init(D3DXVECTOR3(550.0f + (i * pScore->m_fSpace), 510.0f, 0.0f));
				break;
				
			default:
				break;
			}
			pScore->SetObjType(OBJTYPE_SCORE);
		}
	}

	return pScore;
}

//===========================
// 数値の加算
//===========================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
}

//===========================
// 数値の設定
//===========================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}

//===========================
// 数値の取得
//===========================
int CScore::GetScore()
{
	return m_nScore;
}