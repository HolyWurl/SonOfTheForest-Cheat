#pragma once
#include <cstdint>
#include "PlayerStateData.h"
#include "UPlayerData.h"

namespace sets {
	inline bool is_modify_leaf = false;
	inline int32_t leaf_amount = 2;

	inline CPlayerStateData* p_player_state_data = nullptr;

	inline bool patch_wood = false;

	inline bool item_bool = false;
	inline int32_t item_amount = 0;

	inline bool is_modify_fov = false;
	inline int32_t fov_value = 70;

	inline float pos_x = 0;
	inline float pos_y = 0;
	inline float pos_z = 0;
	inline bool is_modify_pos = false;
}
