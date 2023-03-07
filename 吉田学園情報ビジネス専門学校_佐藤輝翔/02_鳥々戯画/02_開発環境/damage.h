//============================
//
// ナンバーヘッダー
// Author:Teruto Sato
//
//============================
#ifndef _DAMAGE_H_
#define _DAMAGE_H_	//二重インクルード防止

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// ナンバークラスの定義
//--------------------------
class CDamage : public CObject2D
{
public:
	CDamage();				//コンストラクタ
	~CDamage() override;		//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	//----------------
	// 静的メンバ関数
	//----------------
	static CDamage *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, float fSpace,
							int nDigit, int nNumber);

private:
	//----------------
	// 定数
	//----------------
	static const int nMaxDigit = 6;		//最大桁数

	//----------------
	// メンバ変数
	//----------------
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_move;	//移動量
	D3DXCOLOR	m_col;	//色
	int m_nDigit;		//桁数
	int m_nLife;		//寿命
	float m_fWidth;		//幅
	float m_fHeight;	//高さ
	float m_fSpace;		//間隔
	int m_aPosTexU[nMaxDigit];

	//----------------
	// 静的メンバ変数
	//----------------
	static int m_nValue;	//値
	static int m_nNum;		//配列カウント用
};

#endif