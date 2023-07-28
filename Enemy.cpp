#include "Enemy.h"

#include <cassert>
#include <cmath>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include "ImGuiManager.h"

#include "MathFunction.h"

void Enemy::Initialize(const std::vector<Model*>& models) {
	// 基底クラスの初期化
	BaseCharacter::Initialize(models);

	InitializeFlightingGimmick();
	InitializeMove();

	// ワールドトランスフォームの初期化
	worldTransformBody_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();
	// ワールドトランスフォームの調整
	worldTransform_.translation_.z = 10.0f;
	worldTransform_.translation_.y = 2.0f;
	worldTransform_.translation_.x = 10.0f;
	worldTransformL_arm_.translation_.x = 0.704f;
	worldTransformL_arm_.translation_.y = 0.28f;
	worldTransformR_arm_.translation_.x = -0.704f;
	worldTransformR_arm_.translation_.y = 0.28f;
}

void Enemy::Update() {

	// 円運動
	Move();





	UpdateFlightingGimmick();
	Matrix4x4 worldMatrix = MakeAffineMatrix(
	    worldTransformBody_.scale_, worldTransformBody_.rotation_,
	    worldTransformBody_.translation_);
	worldTransformBody_.matWorld_ = Multiply(worldMatrix, worldTransform_.matWorld_);
	worldMatrix = MakeAffineMatrix(
	    worldTransformL_arm_.scale_, worldTransformL_arm_.rotation_,
	    worldTransformL_arm_.translation_);
	worldTransformL_arm_.matWorld_ = Multiply(worldMatrix, worldTransformBody_.matWorld_);
	worldMatrix = MakeAffineMatrix(
	    worldTransformR_arm_.scale_, worldTransformR_arm_.rotation_,
	    worldTransformR_arm_.translation_);
	worldTransformR_arm_.matWorld_ = Multiply(worldMatrix, worldTransformBody_.matWorld_);
	// 　行列を更新
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	BaseCharacter::Update();
	worldTransformBody_.TransferMatrix();
	worldTransformL_arm_.TransferMatrix();
	worldTransformR_arm_.TransferMatrix();


}

void Enemy::Draw(const ViewProjection& viewProjection) {
	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformL_arm_, viewProjection);
	models_[2]->Draw(worldTransformR_arm_, viewProjection);

}

void Enemy::InitializeFlightingGimmick() { flightingParameter_ = 0.0f; }

void Enemy::UpdateFlightingGimmick() {
	// 浮遊移動のサイクル<frame>
	int period = 60;
	// 1フレームでのパラメータ加算値
	const float step = 2.0f * float(M_PI) / period;
	// パラメータを1ステップ分加算
	flightingParameter_ += step;
	// 2πを超えたらθに戻す
	flightingParameter_ = std::fmod(flightingParameter_, float(2.0f * M_PI));
	// 浮遊の振幅<m>
	float amplitude = 1.0f;
	// 浮遊を座標に反映
	worldTransformL_arm_.rotation_.z = std::sin(flightingParameter_) * (amplitude / 2.0f);
	worldTransformR_arm_.rotation_.z = -worldTransformL_arm_.rotation_.z;

	ImGui::Begin("Enemy");
	ImGui::SliderFloat3("ArmL Trasnlation", &worldTransformL_arm_.translation_.x, -10.0f, 10.0f);
	ImGui::SliderFloat3("ArmR Trasnlation", &worldTransformR_arm_.translation_.x, -10.0f, 10.0f);
	ImGui::SliderInt("周期", &period, 0, 120);
	ImGui::SliderFloat("浮遊の振幅", &amplitude, -2.0f, 2.0f);

	ImGui::End();



}

void Enemy::InitializeMove() { 
	angle_ = 0.0f;
	angularVelocity_ = 1.0f;
}

void Enemy::Move() {
	int period = 60;
	float radius = 10.0f;
	angle_ += angularVelocity_ * (1.0f / float(period));

	Vector3 move = {
	    angularVelocity_ * std::sin(angle_), 0.0f,
	    -angularVelocity_ * std::cos(angle_)
	};
	
	// Y軸周り角度(θy)
	worldTransform_.rotation_.y = std::atan2(move.x, move.z);

	worldTransform_.translation_.x = std::cos(angle_) * radius;
	worldTransform_.translation_.z = radius + std::sin(angle_) * radius;

}
