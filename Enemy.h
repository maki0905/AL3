#pragma once

#include "BaseCharacter.h"

class Enemy : public BaseCharacter{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const std::vector<Model*>& models) override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;


	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection) override;

	// 飛行ギミック初期化
	void InitializeFlightingGimmick();
	// 飛行ギミック更新
	void UpdateFlightingGimmick();

	// 移動ベクトルの初期化
	void InitializeMove();
	
	// 移動
	void Move();

private:
	// ワールド変換データ
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;

	// 飛行ギミックの媒介変数
	float flightingParameter_ = 0.0f;

	// 
	float angle_ = 0.0f;
	float angularVelocity_ = 0.0f;
};
