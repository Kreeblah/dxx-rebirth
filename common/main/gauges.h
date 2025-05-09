/*
 * Portions of this file are copyright Rebirth contributors and licensed as
 * described in COPYING.txt.
 * Portions of this file are copyright Parallax Software and licensed
 * according to the Parallax license below.
 * See COPYING.txt for license details.

THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF PARALLAX
SOFTWARE CORPORATION ("PARALLAX").  PARALLAX, IN DISTRIBUTING THE CODE TO
END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.
COPYRIGHT 1993-1999 PARALLAX SOFTWARE CORPORATION.  ALL RIGHTS RESERVED.
*/

/*
 *
 * Prototypes and defines for gauges
 *
 */

#pragma once

#include "fwd-piggy.h"
#include "fwd-player.h"
#include "fwd-object.h"
#include "kconfig.h"
#include "game.h"

//from gauges.c

namespace dcx {

enum class gauge_inset_window_view : unsigned
{
	primary,
	secondary,
};

void show_mousefs_indicator(grs_canvas &canvas, int mx, int my, int mz, int x, int y, int size);

// defines for the reticle(s)
enum class reticle_type : uint8_t
{
	classic       = 0,
	classic_reboot = 1,
	none          = 2,
	x             = 3,
	dot           = 4,
	circle        = 5,
	cross_v1      = 6,
	cross_v2      = 7,
	angle         = 8,
};

}

#ifdef DXX_BUILD_DESCENT
#if DXX_BUILD_DESCENT == 1
#define MAX_GAUGE_BMS_PC 80u		//	increased from 56 to 80 by a very unhappy MK on 10/24/94.
#define MAX_GAUGE_BMS_MAC 85u
#define MAX_GAUGE_BMS (MacPig ? MAX_GAUGE_BMS_MAC : MAX_GAUGE_BMS_PC)

extern std::array<bitmap_index, MAX_GAUGE_BMS_MAC> Gauges;   // Array of all gauge bitmaps.
#elif DXX_BUILD_DESCENT == 2
#define MAX_GAUGE_BMS 100u   // increased from 56 to 80 by a very unhappy MK on 10/24/94.

extern std::array<bitmap_index, MAX_GAUGE_BMS> Gauges;      // Array of all gauge bitmaps.
extern std::array<bitmap_index, MAX_GAUGE_BMS> Gauges_hires;    // hires gauges
#endif

// Flags for gauges/hud stuff

namespace dsx {
void add_points_to_score(player_info &, unsigned points, game_mode_flags);
void add_bonus_points_to_score(player_info &, unsigned points, game_mode_flags);
void render_gauges(grs_canvas &, game_mode_flags game_mode);
void init_gauges(void);
void draw_hud(const d_robot_info_array &Robot_info, grs_canvas &, const object &, const control_info &Controls, game_mode_flags);     // draw all the HUD stuff
}
#endif
void close_gauges(void);
#ifdef DXX_BUILD_DESCENT
namespace dsx {
void show_reticle(grs_canvas &canvas, const player_info &, reticle_type, int secondary_display);
void show_HUD_names(const d_robot_info_array &Robot_info, grs_canvas &, game_mode_flags);
}
#endif

void player_dead_message(grs_canvas &);
//extern void say_afterburner_status(void);

// from testgaug.c

#ifdef DXX_BUILD_DESCENT
namespace dsx {
extern void update_laser_weapon_info(void);
void play_homing_warning(const player_info &);
}
#endif

struct rgb {
	ubyte r,g,b;
};

using rgb_array_t = const per_player_array<rgb>;
extern const rgb_array_t player_rgb_normal;

/* Stub for mods that provide switchable player colors */
class rgb_array_wrapper
{
public:
	const rgb &operator[](const player_ship_color i) const
	{
		return player_rgb_normal[static_cast<std::size_t>(i)];
	}
};

constexpr rgb_array_wrapper player_rgb{};

#ifdef DXX_BUILD_DESCENT
#if DXX_BUILD_DESCENT == 2
namespace dsx {

enum class weapon_box_user : uint8_t
{
	weapon,
	missile,
	escort,
	rear,
	coop,
	guided,
	marker,
	post_missile_static,
};

// draws a 3d view into one of the cockpit windows.  win is 0 for
// left, 1 for right.  viewer is object.  NULL object means give up
// window user is one of the WBU_ constants.  If rear_view_flag is
// set, show a rear view.  If label is non-NULL, print the label at
// the top of the window.
void do_cockpit_window_view(grs_canvas &, gauge_inset_window_view win, const object &viewer, int rear_view_flag, weapon_box_user user, const char *label, const player_info * = nullptr);
void do_cockpit_window_view(gauge_inset_window_view win, weapon_box_user user);
}
#endif
#endif

#define GAUGE_HUD_NUMMODES 4

extern int	Color_0_31_0;

#define RET_COLOR_DEFAULT_R     0
#define RET_COLOR_DEFAULT_G     32
#define RET_COLOR_DEFAULT_B     0
#define RET_COLOR_DEFAULT_A     0
