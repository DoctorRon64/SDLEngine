#pragma once
struct Animation {
	int frameCount;
	Vector2 frameSize;
	float frameTime;
	bool loop;
	int row = 0;
};

class Animator {
private:
	ImageRenderer* renderer;
	Animation anim;
	float timer = 0.f;
	int currentFrame = 0;

public:
	Animator(ImageRenderer* r, const Animation& a)
		: renderer(r), anim(a) {}

	void Update(float dt) {
		timer += dt;

		if(timer >= anim.frameTime) {
			timer -= anim.frameTime;
			currentFrame++;

			if(currentFrame >= anim.frameCount) {
				currentFrame = anim.loop ? 0 : anim.frameCount - 1;
			}

			renderer->SetSourceRect(
				{ anim.frameSize.x * currentFrame,
				  anim.frameSize.y * anim.row },
				anim.frameSize
			);
		}
	}

	void Reset() {
		currentFrame = 0;
		timer = 0.f;

		renderer->SetSourceRect(
			{ 0, anim.frameSize.y * anim.row },
			anim.frameSize
		);
	}
};
