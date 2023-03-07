#pragma once
#include <cstdint>
#include "PlayerStateData.h"

namespace sets {
	inline bool is_modify_leaf = false;
	inline int32_t leaf_amount = 2;

	inline CPlayerStateData* p_player_state_data = nullptr;

	inline bool patch_wood = false;

	inline bool item_bool = false;
	inline int32_t item_amount = 0;
}
