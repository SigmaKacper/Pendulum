#include "Animation.h"
#include "SpriteEffect.h"

Animation::Animation(int x, int y, int width, int height, int count, const Surface& sprite, float holdTime, Color chroma)
	:
	sprite(sprite),
	holdTime(holdTime),
	chroma(chroma)
{
	frames.reserve(count);
	for (int i = 0; i < count; i++)
	{
		frames.emplace_back(RectI(i * width, (i + 1) * width, y, y + height));
	}
}

void Animation::Draw(const Vei2& pos, Graphics& gfx) const
{
	gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], sprite, SpriteEffect::Ghost{chroma} ); 
}

void Animation::Draw(const Vei2& pos, Graphics& gfx, const RectI& clip) const
{
	gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], clip, sprite, SpriteEffect::Copy{});
}

void Animation::DrawColor(const Vei2& pos, Graphics& gfx, Color c) const
{
	gfx.DrawSprite(pos.x, pos.y, frames[iCurFrame], sprite, SpriteEffect::Substitution{c, chroma});
}

void Animation::Update(float dt)
{
	curFrameTime += dt;
	while (curFrameTime > holdTime)
	{
		curFrameTime -= holdTime;
		Advance();
	}
}

void Animation::Advance()
{
	if (++iCurFrame >= frames.size())
	{
		iCurFrame = 0;
	}
}
