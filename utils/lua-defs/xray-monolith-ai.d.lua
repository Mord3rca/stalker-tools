---@meta

-- Defined in src\xrGame\ai_crow_script.cpp
---@class CAI_Crow:CGameObject
CAI_Crow = {}

-- Defined in src\xrGame\ai\monsters\bloodsucker\bloodsucker_script.cpp
---@class CAI_Bloodsucker:CGameObject
CAI_Bloodsucker = {}

-- Defined here: src\xrGame\ai\monsters\bloodsucker\bloodsucker.h:203
---@enum visibility_t
local visibility_t = {
    unset = -1,
    no_visibility = 0,
    partial_visibility = 1,
    full_visibility = 2
}

---@param state visibility_t
function CAI_Bloodsucker:force_visibility_state(state) end

-- Defined in src\xrGame\ai\monsters\boar\boar_script.cpp
---@class CAI_Boar:CGameObject
CAI_Boar = {}

-- Defined in src\xrGame\ai\monsters\burer\burer_script.cpp
---@class CBurer:CGameObject
CBurer = {}

-- Defined in src\xrGame\ai\monsters\cat\cat_script.cpp
---@class CCat:CGameObject
CCat = {}

-- Defined in src\xrGame\ai\monsters\chimera\chimera_script.cpp
---@class CChimera:CGameObject
CChimera = {}

-- Defined in src\xrGame\ai\monsters\controller\controller_script.cpp
---@class CController:CGameObject
CController = {}

-- Defined in src\xrGame\ai\monsters\dog\dog_script.cpp
---@class CAI_Dog:CGameObject
CAI_Dog = {}

-- Defined in src\xrGame\ai\monsters\flesh\flesh_script.cpp
---@class CAI_Flesh:CGameObject
CAI_Flesh = {}

-- Defined in src\xrGame\ai\monsters\fracture\fracture_script.cpp
---@class CFracture:CGameObject
CFracture = {}

-- Defined in src\xrGame\ai\monsters\poltergeist\poltergeist_script.cpp
---@class CPoltergeist:CGameObject
CPoltergeist = {}

-- Defined in src\xrGame\ai\monsters\pseudodog\pseudodog_script.cpp
---@class CAI_PseudoDog:CGameObject
CAI_PseudoDog = {}

-- Defined in src\xrGame\ai\monsters\pseudodog\pseudodog_script.cpp
---@class CPsyDog:CGameObject
CPsyDog = {}

-- Defined in src\xrGame\ai\monsters\pseudodog\pseudodog_script.cpp
---@class CPsyDog:CGameObject
CPsyDog = {}

-- Defined in src\xrGame\ai\monsters\pseudogigant\pseudogigant_script.cpp
---@class CPseudoGigant:CGameObject
CPseudoGigant = {}

-- Defined in src\xrGame\ai\monsters\snork\snork_script.cpp
---@class CSnork:CGameObject
CSnork = {}

-- Defined in src\xrGame\ai\monsters\tushkano\tushkano_script.cpp
---@class CTushkano:CGameObject
CTushkano = {}

-- Defined in src\xrGame\ai\monsters\zombie\zombie_script.cpp
---@class CZombie:CGameObject
CZombie = {}

---@class stalker_ids
stalker_ids = {}

-- Defined here src\xrGame\stalker_decision_space.h
---@enum stalker_ids.properties
stalker_ids.properties = {
    property_alive = 0,
    property_dead = 1,
    property_already_dead = 2,
    property_alife = 3,
    property_puzzle_solved = 4,
    property_smart_terrain_task = 5,
    property_items = 6,
    property_enemy = 7,
    property_danger = 8,
    property_item_to_kill = 9,
    property_found_item_to_kill = 10,
    property_item_can_kill = 11,
    property_found_ammo = 12,
    property_ready_to_kill = 13,
    property_ready_to_detour = 14,
    property_see_enemy = 15,
    property_panic = 16,
    property_in_cover = 17,
    property_looked_out = 18,
    property_position_holded = 19,
    property_enemy_detoured = 20,
    property_use_suddenness = 21,
    property_use_crouch_to_look_out = 22,
    property_critically_wounded = 23,
    property_enemy_critically_wounded = 24,
    property_danger_unknown = 25,
    property_danger_in_direction = 26,
    property_danger_grenade = 27,
    property_danger_by_sound = 28,
    property_cover_actual = 29,
    property_cover_reached = 30,
    property_looked_around = 31,
    property_grenade_exploded = 32,
    property_anomaly = 33,
    property_inside_anomaly = 34,
    property_pure_enemy = 35,
    property_script = 36
}

---@enum stalker_ids.action
stalker_ids.action = {
    action_dead = 0,
    action_dying = 1,
    action_gather_items = 2,
    action_no_alife = 3,
    action_smart_terrain_task = 4,
    action_solve_zone_puzzle = 5,
    action_reach_task_location = 6,
    action_accomplish_task = 7,
    action_reach_customer_location = 8,
    action_communicate_with_customer = 9,
    get_out_of_anomaly = 10,
    detect_anomaly = 11,
    action_get_item_to_kill = 12,
    action_find_item_to_kill = 13,
    action_make_item_killing = 14,
    action_find_ammo = 15,
    action_aim_enemy = 16,
    action_get_ready_to_kill = 17,
    action_kill_enemy = 18,
    action_retreat_from_enemy = 19,
    action_take_cover = 20,
    action_look_out = 21,
    action_hold_position = 22,
    action_get_distance = 23,
    action_detour_enemy = 24,
    action_search_enemy = 25,
    action_hide_from_grenade = 26,
    action_sudden_attack = 27,
    action_kill_enemy_if_not_visible = 28,
    action_reach_wounded_enemy = 29,
    action_prepare_wounded_enemy = 30,
    action_kill_wounded_enemy = 31,
    action_kill_if_player_on_the_path = 32,
    action_critically_wounded = 33,
    action_kill_if_enemy_critically_wounded = 34,
    action_throw_grenade = 35,
    action_danger_unknown_planner = 36,
    action_danger_in_direction_planner = 37,
    action_danger_grenade_planner = 38,
    action_danger_by_sound_planner = 39,
    action_danger_unknown_take_cover = 40,
    action_danger_unknown_look_around = 41,
    action_danger_unknown_search = 42,
    action_danger_in_direction_take_cover = 43,
    action_danger_in_direction_look_out = 44,
    action_danger_in_direction_hold_position = 45,
    action_danger_in_direction_detour = 46,
    action_danger_in_direction_search = 47,
    action_danger_grenade_take_cover = 48,
    action_danger_grenade_wait_for_explosion = 49,
    action_danger_grenade_take_cover_after_explosion = 50,
    action_danger_grenade_look_around = 51,
    action_danger_grenade_search = 52,
    action_death_planner = 53,
    action_alife_planner = 54,
    action_combat_planner = 55,
    action_anomaly_planner = 56,
    action_danger_planner = 57,
    action_post_combat_wait = 58,
    action_script = 59
}

---@enum stalker_ids.sounds
stalker_ids.sounds = {
    sound_die = 0,
    sound_die_in_anomaly = 1,
    sound_injuring = 2,
    sound_humming = 3,
    sound_alarm = 4,
    sound_attack_no_allies = 5,
    sound_attack_allies_single_enemy = 6,
    sound_attack_allies_several_enemies = 7,
    sound_backup = 8,
    sound_detour = 9,
    sound_search1_no_allies = 10,
    sound_search1_with_allies = 11,
    sound_enemy_lost_no_allies = 12,
    sound_enemy_lost_with_allies = 13,
    sound_injuring_by_friend = 14,
    sound_panic_human = 15,
    sound_panic_monster = 16,
    sound_tolls = 17,
    sound_wounded = 18,
    sound_grenade_alarm = 19,
    sound_friendly_grenade_alarm = 20,
    sound_need_backup = 21,
    sound_running_in_danger = 22,
    sound_walking_in_danger = 23,
    sound_kill_wounded = 24,
    sound_enemy_critically_wounded = 25,
    sound_enemy_killed_or_wounded = 26,
    sound_script = 27
}

-- Defined in src\xrGame\ai\stalker\ai_stalker_script.cpp
---@class CAI_Stalker:CGameObject
CAI_Stalker = {}

-- Defined in src\xrGame\ai\trader\ai_trader_script.cpp
---@class CAI_Trader:CGameObject
CAI_Trader = {}

