#pragma once

#include "Actor.h"

#include "game/map/TileState.h"

#include "util/Timer.h"

using namespace types;
using namespace util;

namespace task {
namespace game {
namespace actor {

CLASS( TileSelection, Actor )

	static constexpr uint16_t GLOW_STEP = 10; // ms
	static constexpr float GLOW_SPEED = 0.04f; // per step
	static constexpr float GLOW_MAX = 1.0f;
	static constexpr float GLOW_MIN = 0.25f;

	TileSelection( ::game::map::TileState::tile_vertices_t coords );

	void Iterate() override;

private:
	Texture* m_texture = nullptr;

	float m_glow = GLOW_MAX;
	int8_t m_glow_direction = -1;
	Timer m_glow_timer;

};

}
}
}
