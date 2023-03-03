//=====================================
//
// MPヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _MP_H_
#define _MP_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// MPクラス
//--------------------------
class CMp : public CObject2D
{
public:
	CMp();				//コンストラクタ
	~CMp() override;	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetMP(int nMp, int nRemMp);
	void SubMP();	//MP減少時の処理

	//------------------
	// 静的メンバ関数
	//------------------
	static CMp *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	//------------------
	// メンバ変数
	//------------------
	D3DXVECTOR3 m_pos;	//位置
	int m_nMp;			//MP受け取り用
	int m_nRemMp;		//残りMP受け取り用
	float m_fWidth;		//幅
	float m_fHeight;	//高さ
	float m_fLength;	//HPバーの長さ
};

#endif