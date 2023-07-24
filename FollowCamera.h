#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <memory>
#include "Input.h"

// GameSceneの前方宣言
class GameScene;

/// <summary>
/// 追従カメラ
/// </summary>
class FollowCamera {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const ViewProjection& viewProjection);

	/// <summary>
	///　更新
	/// </summary>
	void Update();

	/// <summary>
	/// 　Get
	/// </summary>
	ViewProjection* GetViewProjection() { return &viewProjection_; }


	/// <summary>
	/// 　Set
	/// </summary>
	void SetTarget(const WorldTransform* target) { target_ = target; }

private:
	// ビュープロジェクション
	ViewProjection viewProjection_;
	// ゲームシーン
	std::unique_ptr<GameScene> gameScene_;
	// 追従対象
	const WorldTransform* target_ = nullptr;
	// 入力
	Input* input_ = nullptr;
};
