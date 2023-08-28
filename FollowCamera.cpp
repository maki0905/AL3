#include "FollowCamera.h"
#include "GameScene.h"
#include "MathFunction.h"

void FollowCamera::Initialize(const ViewProjection& viewProjection) {
	viewProjection_ = viewProjection;
	// シングルトンインスタンスを取得
	input_ = Input::GetInstance();
}

void FollowCamera::Update() {

	// 押した方向で移動ベクトルを変更(左右)
	if (input_->PushKey(DIK_A)) {
		// 速さ
		const float speed = 0.1f;
		viewProjection_.rotation_.y -= speed;
	} else if (input_->PushKey(DIK_D)) {
		// 速さ
		const float speed = 0.1f;
		viewProjection_.rotation_.y += speed;
	}

	// ゲームパッドの状態を得る変数(XINPUT)
	XINPUT_STATE joyState;
	// ジョイスティック状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// 速さ
		const float speed = 0.3f;

		viewProjection_.rotation_.y += (float)joyState.Gamepad.sThumbRX * speed;
	}

	if (target_) {

		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 10.0f, -30.0f};

		Matrix4x4 rotate = MakeRotateYMatrix(viewProjection_.rotation_.y);

		// オフセットをカメラの回転に合わせて回転させる
		offset = TransformNormal(offset, rotate);

		// 座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = Add(target_->translation_, offset);
	}

	// ビュー行列の更新
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();
}