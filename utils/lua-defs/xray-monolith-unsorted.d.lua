---@meta

-- Exported in src\xrGame\CarScript.cpp

---@class CCar
CCar = {}

---@enum CCar.wpn_action
CCar.wpn_action = {
    eWpnDesiredDir = 0,
    eWpnDesiredPos = 1,
    eWpnActivate = 2,
    eWpnFire = 3,
    eWpnAutoFire = 4,
    eWpnToDefaultDir = 5
}  -- TODO: CHeck values

function CCar:Action() end
function CCar:SetParam() end
function CCar:SetParam() end
function CCar:CanHit() end
function CCar:FireDirDiff() end
function CCar:IsObjectVisible() end
function CCar:HasWeapon() end
function CCar:CurrentVel() end
function CCar:GetfHealth() end
function CCar:SetfHealth() end
function CCar:SetExplodeTime() end
function CCar:ExplodeTime() end
function CCar:CarExplode() end
function CCar:GetfFuel() end
function CCar:SetfFuel() end
function CCar:GetfFuelTank() end
function CCar:SetfFuelTank() end
function CCar:GetfFuelConsumption() end
function CCar:SetfFuelConsumption() end
function CCar:ChangefFuel() end
function CCar:ChangefHealth() end
function CCar:PlayDamageParticles() end
function CCar:StopDamageParticles() end
function CCar:StartEngine() end
function CCar:StopEngine() end
function CCar:IsActiveEngine() end
function CCar:HandBreak() end
function CCar:ReleaseHandBreak() end
function CCar:GetRPM() end
function CCar:SetRPM() end
function CCar:SetUseAction() end
function CCar:GetFlyWeightAdd() end
function CCar:SetFlyWeightAdd() end
function CCar:GetControlEle() end
function CCar:GetControlYaw() end
function CCar:GetControlPit() end
function CCar:GetControlRol() end

-- Exported in src\xrGame\client_spawn_manager_script.cpp

---@class client_spawn_manager
client_spawn_manager = {}

function client_spawn_manager:add() end
function client_spawn_manager:add() end
function client_spawn_manager:remove() end

-- Exported in src\xrGame\cover_point_script.cpp

---@class cover_point
cover_point = {}

function cover_point:position() end
function cover_point:level_vertex_id() end
function cover_point:is_smart_cover() end

-- Exported in src\xrGame\DemoInfo.cpp

---@class demo_player_info
demo_player_info = {}

function demo_player_info:get_name() end
function demo_player_info:get_frags() end
function demo_player_info:get_deaths() end
function demo_player_info:get_artefacts() end
function demo_player_info:get_spots() end
function demo_player_info:get_team() end
function demo_player_info:get_rank() end

---@class demo_info
demo_info = {}

function demo_info:get_map_name() end
function demo_info:get_map_version() end
function demo_info:get_game_type() end
function demo_info:get_game_score() end
function demo_info:get_author_name() end
function demo_info:get_players_count() end
function demo_info:get_player() end

-- Exported in src\xrGame\ef_storage_script.cpp

function ef_storage() end

---@class cef_storage
cef_storage = {}

function cef_storage:evaluate() end
function cef_storage:evaluate() end
function cef_storage:evaluate() end
function cef_storage:evaluate() end
function cef_storage:evaluate() end
function cef_storage:evaluate() end
function cef_storage:evaluate() end
function cef_storage:evaluate() end

-- Exported in src\xrGame\game_cl_single.cpp

---@enum game_difficulty
game_difficulty = {
    novice = 0,
    stalker = 1,
    veteran = 2,
    master = 3
} -- TODO: Check values

-- Exported in src\xrGame\game_graph_script.cpp

---@class GameGraph__LEVEL_MAP__value_type
---@field id number readonly
---@field level any readonly

function game_graph() end

---@class CGameGraph
CGameGraph = {}

function CGameGraph:accessible() end
function CGameGraph:accessible() end
function CGameGraph:valid_vertex_id() end
function CGameGraph:vertex() end
function CGameGraph:vertex_id() end
function CGameGraph:levels() end

---@class GameGraph__CVertex
GameGraph__CVertex = {}

function GameGraph__CVertex:level_point() end
function GameGraph__CVertex:game_point() end
function GameGraph__CVertex:level_id() end
function GameGraph__CVertex:level_vertex_id() end

-- Exported in src\xrGame\GameTask_script.cpp

task = {}

---@enum task.task_state
task.task_state = {
    fail = 0,
    in_progress = 1,
    completed = 2,
    task_dummy = 3
} -- TODO: Check values

---@enum task.task_type
task.task_type = {
    storyline = 0,
    additional = 1
} -- TODO: Check values

---@class CGameTask
CGameTask = {}

function CGameTask:set_title() end
function CGameTask:get_title() end
function CGameTask:set_priority() end
function CGameTask:get_priority() end
function CGameTask:get_id() end
function CGameTask:set_id() end
function CGameTask:set_type() end
--function CGameTask:get_type() end
function CGameTask:set_icon_name() end
function CGameTask:get_icon_name() end
function CGameTask:set_description() end
function CGameTask:set_map_hint() end
function CGameTask:set_map_location() end
function CGameTask:set_map_object_id() end
function CGameTask:get_map_location() end
function CGameTask:get_map_object_id() end
function CGameTask:create_map_location() end
function CGameTask:add_complete_info() end
function CGameTask:add_fail_info() end
function CGameTask:add_on_complete_info() end
function CGameTask:add_on_fail_info() end
function CGameTask:add_complete_func() end
function CGameTask:add_fail_func() end
function CGameTask:add_on_complete_func() end
function CGameTask:add_on_fail_func() end
function CGameTask:remove_map_locations() end
function CGameTask:change_map_location() end

-- Exported in src\xrGame\holder_custom_script.cpp

---@class holder
holder = {}

function holder:engaged() end
function holder:Action() end
function holder:SetParam() end
function holder:SetParam() end
function holder:SetEnterLocked() end
function holder:SetExitLocked() end
function holder:Owner() end

-- Exported in src\xrGame\inventory_item_script.cpp

---@class CInventoryItem

-- Exported in src\xrGame\InventoryOwner_script.cpp

---@class CInventoryOwner
CInventoryOwner = {}

function CInventoryOwner:IconName() end
function CInventoryOwner:get_money() end
function CInventoryOwner:EnableTalk() end
function CInventoryOwner:DisableTalk() end
function CInventoryOwner:IsTalkEnabled() end
function CInventoryOwner:EnableTrade() end
function CInventoryOwner:DisableTrade() end
function CInventoryOwner:IsTradeEnabled() end
function CInventoryOwner:EnableInvUpgrade() end
function CInventoryOwner:DisableInvUpgrade() end
function CInventoryOwner:IsInvUpgradeEnabled() end
function CInventoryOwner:GetTalkPartner() end
function CInventoryOwner:OfferTalk() end
function CInventoryOwner:StartTalk() end
function CInventoryOwner:StopTalk() end
function CInventoryOwner:IsTalking() end
function CInventoryOwner:deadbody_can_take() end
function CInventoryOwner:deadbody_can_take_status() end
function CInventoryOwner:deadbody_closed() end
function CInventoryOwner:deadbody_closed_status() end

-- Exported in src\xrGame\key_binding_registrator_script.cpp

function dik_to_keyname() end
function dik_to_bind() end
function bind_to_dik() end
function key_state() end

key_bindings = {}

---@enum key_bindings.commands
key_bindings.commands = {
    kLEFT = 0,
    kRIGHT = 1,
    kUP = 2,
    kDOWN = 3,
    kJUMP = 4,
    kCROUCH = 5,
    kACCEL = 6,
    kSPRINT_TOGGLE = 7,
    kFWD = 8,
    kBACK = 9,
    kL_STRAFE = 10,
    kR_STRAFE = 11,
    kL_LOOKOUT = 12,
    kR_LOOKOUT = 13,
    kCAM_1 = 14,
    kCAM_2 = 15,
    kCAM_3 = 16,
    kCAM_ZOOM_IN = 17,
    kCAM_ZOOM_OUT = 18,
    kTORCH = 19,
    kNIGHT_VISION = 20,
    kDETECTOR = 21,
    kWPN_1 = 22,
    kWPN_2 = 23,
    kWPN_3 = 24,
    kWPN_4 = 25,
    kWPN_5 = 26,
    kWPN_6 = 27,
    kARTEFACT = 28,
    kWPN_NEXT = 29,
    kWPN_FIRE = 30,
    kWPN_ZOOM = 31,
    kWPN_ZOOM_INC = 32,
    kWPN_ZOOM_DEC = 33,
    kWPN_RELOAD = 34,
    kWPN_FUNC = 35,
    kWPN_FIREMODE_PREV = 36,
    kWPN_FIREMODE_NEXT = 37,
    kPAUSE = 38,
    kDROP = 39,
    kUSE = 40,
    kSCORES = 41,
    kCHAT = 42,
    kCHAT_TEAM = 43,
    kSCREENSHOT = 44,
    kQUIT = 45,
    kCONSOLE = 46,
    kINVENTORY = 47,
    kBUY = 48,
    kSKIN = 49,
    kTEAM = 50,
    kACTIVE_JOBS = 51,
    kVOTE_BEGIN = 52,
    kSHOW_ADMIN_MENU = 53,
    kVOTE = 54,
    kVOTEYES = 55,
    kVOTENO = 56,
    kNEXT_SLOT = 57,
    kPREV_SLOT = 58,
    kSPEECH_MENU_0 = 59,
    kSPEECH_MENU_1 = 60,
    kQUICK_USE_1 = 61,
    kQUICK_USE_2 = 62,
    kQUICK_USE_3 = 63,
    kQUICK_USE_4 = 64,
    kQUICK_SAVE = 65,
    kQUICK_LOAD = 66,
    kCUSTOM1 = 67,
    kCUSTOM2 = 68,
    kCUSTOM3 = 69,
    kCUSTOM4 = 70,
    kCUSTOM5 = 71,
    kCUSTOM6 = 72,
    kCUSTOM7 = 73,
    kCUSTOM8 = 74,
    kCUSTOM9 = 75,
    kCUSTOM10 = 76,
    kCUSTOM11 = 77,
    kCUSTOM12 = 78,
    kCUSTOM13 = 79,
    kCUSTOM14 = 80,
    kCUSTOM15 = 81,
    kCUSTOM16 = 82,
    kCUSTOM17 = 83,
    kCUSTOM18 = 84,
    kCUSTOM19 = 85,
    kCUSTOM20 = 86,
    kCUSTOM21 = 87,
    kCUSTOM22 = 88,
    kCUSTOM23 = 89,
    kCUSTOM24 = 90,
    kCUSTOM25 = 91,
    kSAFEMODE = 92,
    kFREELOOK = 93,
    kCAM_AUTOAIM = 94
}  -- TODO: Check values

DIK_keys = {}

---@enum DIK_keys.dik_keys
DIK_keys.dik_keys = {
    DIK_ESCAPE = 0,
    DIK_2 = 1,
    DIK_4 = 2,
    DIK_6 = 3,
    DIK_8 = 4,
    DIK_0 = 5,
    DIK_EQUALS = 6,
    DIK_TAB = 7,
    DIK_W = 8,
    DIK_R = 9,
    DIK_Y = 10,
    DIK_I = 11,
    DIK_P = 12,
    DIK_RBRACKET = 13,
    DIK_LCONTROL = 14,
    DIK_S = 15,
    DIK_F = 16,
    DIK_H = 17,
    DIK_K = 18,
    DIK_SEMICOLON = 19,
    DIK_GRAVE = 20,
    DIK_BACKSLASH = 21,
    DIK_X = 22,
    DIK_V = 23,
    DIK_N = 24,
    DIK_COMMA = 25,
    DIK_SLASH = 26,
    DIK_MULTIPLY = 27,
    DIK_SPACE = 28,
    DIK_F1 = 29,
    DIK_F3 = 30,
    DIK_F5 = 31,
    DIK_F7 = 32,
    DIK_F9 = 33,
    DIK_NUMLOCK = 34,
    DIK_NUMPAD7 = 35,
    DIK_NUMPAD9 = 36,
    DIK_NUMPAD4 = 37,
    DIK_NUMPAD6 = 38,
    DIK_NUMPAD1 = 39,
    DIK_NUMPAD3 = 40,
    DIK_DECIMAL = 41,
    DIK_F12 = 42,
    DIK_F14 = 43,
    DIK_KANA = 44,
    DIK_NOCONVERT = 45,
    DIK_NUMPADEQUALS = 46,
    DIK_AT = 47,
    DIK_UNDERLINE = 48,
    DIK_STOP = 49,
    DIK_UNLABELED = 50,
    DIK_RCONTROL = 51,
    DIK_DIVIDE = 52,
    DIK_RMENU = 53,
    DIK_UP = 54,
    DIK_LEFT = 55,
    DIK_END = 56,
    DIK_NEXT = 57,
    DIK_DELETE = 58,
    DIK_RWIN = 59,
    DIK_PAUSE = 60,
    MOUSE_2 = 61,
    DIK_1 = 62,
    DIK_3 = 63,
    DIK_5 = 64,
    DIK_7 = 65,
    DIK_9 = 66,
    DIK_MINUS = 67,
    DIK_BACK = 68,
    DIK_Q = 69,
    DIK_E = 70,
    DIK_T = 71,
    DIK_U = 72,
    DIK_O = 73,
    DIK_LBRACKET = 74,
    DIK_RETURN = 75,
    DIK_A = 76,
    DIK_D = 77,
    DIK_G = 78,
    DIK_J = 79,
    DIK_L = 80,
    DIK_APOSTROPHE = 81,
    DIK_LSHIFT = 82,
    DIK_Z = 83,
    DIK_C = 84,
    DIK_B = 85,
    DIK_M = 86,
    DIK_PERIOD = 87,
    DIK_RSHIFT = 88,
    DIK_LMENU = 89,
    DIK_CAPITAL = 90,
    DIK_F2 = 91,
    DIK_F4 = 92,
    DIK_F6 = 93,
    DIK_F8 = 94,
    DIK_F10 = 95,
    DIK_SCROLL = 96,
    DIK_NUMPAD8 = 97,
    DIK_SUBTRACT = 98,
    DIK_NUMPAD5 = 99,
    DIK_ADD = 100,
    DIK_NUMPAD2 = 101,
    DIK_NUMPAD0 = 102,
    DIK_F11 = 103,
    DIK_F13 = 104,
    DIK_F15 = 105,
    DIK_CONVERT = 106,
    DIK_YEN = 107,
    DIK_CIRCUMFLEX = 108,
    DIK_COLON = 109,
    DIK_KANJI = 110,
    DIK_AX = 111,
    DIK_NUMPADENTER = 112,
    DIK_NUMPADCOMMA = 113,
    DIK_SYSRQ = 114,
    DIK_HOME = 115,
    DIK_PRIOR = 116,
    DIK_RIGHT = 117,
    DIK_DOWN = 118,
    DIK_INSERT = 119,
    DIK_LWIN = 120,
    DIK_APPS = 121,
    MOUSE_1 = 122,
    MOUSE_3 = 123,
    MOUSE_4 = 124,
    MOUSE_5 = 125,
    MOUSE_6 = 126,
    MOUSE_7 = 127,
    MOUSE_8 = 128
} -- TODO: Check values

-- Exported in src\xrGame\level_script.cpp

---@class CEnvDescriptor
---@field fog_density any
---@field far_plane any

---@class CEnvironment
CEnvironment = {}

function CEnvironment:current() end

---@class DBG_ScriptObject
---@field color any
---@field hud any
---@field visible any
DBG_ScriptObject = {}

---@enum DBG_ScriptObject.dbg_type
DBG_ScriptObject.dbg_type = {
    line = 0,
    sphere = 1,
    box = 2
} -- TODO: Check value

function DBG_ScriptObject:cast_dbg_sphere() end
function DBG_ScriptObject:cast_dbg_box() end
function DBG_ScriptObject:cast_dbg_line() end

---@class DBG_ScriptSphere
---@field matrix any

---@class DBG_ScriptBox
---@field matrix any
---@field size any

---@class DBG_ScriptLine
---@field point_a any
---@field point_b any

-- Defined as a module ... Imported implicitly
---@class debug_render
debug_render = {}

function debug_render.add_object() end
function debug_render.add_object() end
function debug_render.remove_object() end
function debug_render.remove_object() end
function debug_render.get_object() end
function debug_render.get_object() end
function debug_render.get_flags() end
function debug_render.set_flags() end

ETraceTarget = {}

--@enum ETraceTarget.trace_targets
ETraceTarget.trace_targets = {
    Actor = 0,
    Camera = 1,
    Weapon = 2,
    Device = 3
}  -- TODO: Check values

DxEncoding = {}

---@enum DxEncoding.DxEncoding
DxEncoding.DxEncoding = {
    A8R8G8B8 = 0,
    DXT1 = 1,
    DXT5 = 2,
    BC7 = 3
}  -- TODO: Check values

-- Defined as module
---@class level
level = {}

function level.send() end
function level.get_target_obj() end
function level.get_target_obj() end
function level.get_target_dist() end
function level.get_target_dist() end
function level.get_target_element() end
function level.get_target_element() end
function level.get_target_pos() end
function level.get_target_pos() end
function level.get_sun_pos() end
function level.get_sun_color() end
function level.get_sun_intensity() end
function level.is_sun_visible() end
function level.take_screenshot() end
function level.add_cam_effector() end
function level.get_target_result() end
function level.get_target_result() end
function level.spawn_item() end
function level.get_active_cam() end
function level.set_active_cam() end
function level.get_start_time() end
function level.get_view_entity() end
function level.set_view_entity() end
function level.object_by_id() end
function level.object_by_id() end
function level.object_by_id() end
function level.debug_object() end
function level.debug_actor() end
function level.check_object() end
function level.get_weather() end
function level.set_weather() end
function level.set_weather_fx() end
function level.start_weather_fx_from_time() end
function level.is_wfx_playing() end
function level.get_wfx_time() end
function level.stop_weather_fx() end
function level.environment() end
function level.set_time_factor() end
function level.get_time_factor() end
function level.set_game_difficulty() end
function level.get_game_difficulty() end
function level.get_time_days() end
function level.get_time_hours() end
function level.get_time_minutes() end
function level.change_game_time() end
function level.get_nearby_covers() end
function level.vertex_link() end
function level.high_cover_in_direction() end
function level.low_cover_in_direction() end
function level.vertex_in_direction() end
function level.rain_factor() end
function level.rain_wetness() end
function level.rain_hemi() end
function level.patrol_path_exists() end
function level.vertex_position() end
function level.name() end
function level.prefetch_sound() end
function level.client_spawn_manager() end
function level.map_add_object_spot_ser() end
function level.map_add_object_spot() end
function level.map_add_object_spot_complex() end
function level.map_remove_object_spot() end
function level.map_has_object_spot() end
function level.map_change_spot_hint() end
function level.map_remove_all_object_spots() end
function level.map_get_object_spot_static() end
function level.map_get_object_minimap_spot_static() end
function level.map_get_object_spots_by_id() end
function level.add_dialog_to_render() end
function level.remove_dialog_to_render() end
function level.hide_indicators() end
function level.hide_indicators_safe() end
function level.show_indicators() end
function level.show_weapon() end
function level.add_call() end
function level.add_call() end
function level.add_call() end
function level.remove_call() end
function level.remove_call() end
function level.remove_call() end
function level.remove_calls_for_object() end
function level.present() end
function level.disable_input() end
function level.enable_input() end
function level.spawn_phantom() end
function level.get_bounding_volume() end
function level.iterate_sounds() end
function level.iterate_sounds() end
function level.physics_world() end
function level.get_snd_volume() end
function level.get_rain_volume() end
function level.set_snd_volume() end
function level.get_music_volume() end
function level.set_music_volume() end
function level.add_cam_effector() end
function level.add_cam_effector() end
function level.add_cam_effector() end
function level.add_cam_effector() end
function level.set_cam_custom_position_direction() end
function level.set_cam_custom_position_direction() end
function level.set_cam_custom_position_direction() end
function level.set_cam_custom_position_direction() end
function level.remove_cam_custom_position_direction() end
function level.remove_cam_effector() end
function level.set_cam_effector_factor() end
function level.get_cam_effector_factor() end
function level.get_cam_effector_length() end
function level.check_cam_effector() end
function level.add_pp_effector() end
function level.set_pp_effector_factor() end
function level.set_pp_effector_factor() end
function level.remove_pp_effector() end
function level.add_complex_effector() end
function level.remove_complex_effector() end
function level.vertex_id() end
function level.get_nearby_vertices() end
function level.game_id() end
function level.ray_pick() end
function level.press_action() end
function level.release_action() end
function level.hold_action() end
function level.actor_moving_state() end
function level.get_env_rads() end
function level.iterate_nearest() end
function level.pick_material() end
function level.add_bullet() end
function level.add_bullet() end
function level.add_attachment() end
function level.get_attachment() end
function level.remove_attachment() end
function level.remove_attachment() end
function level.iterate_attachments() end

-- Defined as module
---@class actor_stats
actor_stats = {}

function actor_stats.add_points() end
function actor_stats.add_points_str() end
function actor_stats.get_points() end

---@class ray_pick
ray_pick = {}

function ray_pick:set_position() end
function ray_pick:set_direction() end
function ray_pick:set_range() end
function ray_pick:set_flags() end
function ray_pick:set_ignore_object() end
function ray_pick:query() end
function ray_pick:get_result() end
function ray_pick:get_object() end
function ray_pick:get_distance() end
function ray_pick:get_element() end

---@class rq_result
---@field object any
---@field range any
---@field element any
---@field material_name any
---@field material_flags any
---@field material_phfriction any
---@field material_phdamping any
---@field material_phspring any
---@field material_phbounce_start_velocity any
---@field material_phbouncing any
---@field material_flotation_factor any
---@field material_shoot_factor any
---@field material_shoot_factor_mp any
---@field material_bounce_damage_factor any
---@field material_injurious_speed any
---@field material_vis_transparency_factor any
---@field material_snd_occlusion_factor any
---@field material_density_factor any

rq_target = {}

---@enum rq_target.targets
rq_target.targets = {
    rqtNone = 0,
    rqtObject = 1,
    rqtStatic = 2,
    rqtShape = 3,
    rqtObstacle = 4,
    rqtBoth = 5,
    rqtDyn = 6
}  -- TODO: Check values

function command_line() end
function IsGameTypeSingle() end
function IsDynamicMusic() end
function render_get_dx_level() end
function IsImportantSave() end

-- Defined as a module
---@class weather
weather = {}

function weather.get_value_numric() end
function weather.get_value_vector() end
function weather.get_value_string() end
function weather.pause() end
function weather.is_paused() end
function weather.set_value_numric() end
function weather.set_value_vector() end
function weather.set_value_string() end
function weather.reload() end
function weather.boost_value() end
function weather.boost_reset() end
function weather.sun_time() end

-- Defined as a module
---@class hud_adjust
hud_adjust = {}

function hud_adjust.enabled() end
function hud_adjust.set_vector() end
function hud_adjust.set_value() end
function hud_adjust.remove_hud_model() end

-- Defined as a module
---@class relation_registry
relation_registry = {}

function relation_registry.relation_registry() end
function relation_registry.community_goodwill() end
function relation_registry.set_community_goodwill() end
function relation_registry.change_community_goodwill() end
function relation_registry.community_relation() end
function relation_registry.set_community_relation() end
function relation_registry.get_general_goodwill_between() end

game = {}

---@class game.CTime
game.CTime = {}

---@enum game.CTime.date_format
game.CTime.date_format = {
    DateToDay = 0,
    DateToMonth = 1,
    DateToYear = 2
}  -- TODO: Check values

---@enum game.CTime.time_format
game.CTime.time_format = {
    TimeToHours = 0,
    TimeToMinutes = 1,
    TimeToSeconds = 2,
    TimeToMilisecs = 3
} -- TODO: Check values

function game.CTime:diffSec() end
function game.CTime:add() end
function game.CTime:sub() end
function game.CTime:setHMS() end
function game.CTime:setHMSms() end
function game.CTime:set() end
function game.CTime:get() end
function game.CTime:dateToString() end
function game.CTime:timeToString() end
function game.CTime:time() end
function game.CTime:get_game_time() end
function game.CTime:get_surge_time() end
function game.CTime:get_object_by_name() end
function game.CTime:open_originals_link() end
function game.CTime:start_tutorial() end
function game.CTime:stop_tutorial() end
function game.CTime:has_active_tutorial() end
function game.CTime:translate_string() end
function game.CTime:reload_language() end
function game.CTime:get_resolutions() end
function game.CTime:play_hud_motion() end
function game.CTime:stop_hud_motion() end
function game.CTime:get_motion_length() end
function game.CTime:hud_motion_allowed() end
function game.CTime:play_hud_anm() end
function game.CTime:stop_hud_anm() end
function game.CTime:stop_all_hud_anms() end
function game.CTime:set_hud_anm_time() end
function game.CTime:only_allow_movekeys() end
function game.CTime:only_movekeys_allowed() end
function game.CTime:set_actor_allow_ladder() end
function game.CTime:set_nv_lumfactor() end
function game.CTime:reload_ui_xml() end
function game.CTime:actor_weapon_lowered() end
function game.CTime:actor_lower_weapon() end
function game.CTime:prefetch_texture() end
function game.CTime:prefetch_model() end
function game.CTime:get_visual_userdata() end
function game.CTime:world2ui() end
function game.CTime:world2ui_with_depth() end
function game.CTime:ui2world() end
function game.CTime:ui2world() end
function game.CTime:ui2world_offscreen() end
function game.CTime:ui2world_offscreen() end
function game.CTime:change_game_news_show_time() end
function game.CTime:update_pda_news_from_uiwindow() end

function game.get_actor_alcohol() end

-- Exported in src\xrGame\login_manager_script.cpp

---@class login_manager
login_manager = {}

function login_manager:login() end
function login_manager:stop_login() end
function login_manager:login_offline() end
function login_manager:logout() end
function login_manager:set_unique_nick() end
function login_manager:stop_setting_unique_nick() end
function login_manager:save_email_to_registry() end
function login_manager:get_email_from_registry() end
function login_manager:save_password_to_registry() end
function login_manager:get_password_from_registry() end
function login_manager:save_remember_me_to_registry() end
function login_manager:get_remember_me_from_registry() end
function login_manager:save_nick_to_registry() end
function login_manager:get_nick_from_registry() end
function login_manager:get_current_profile() end
function login_manager:forgot_password() end

---@class profile
profile = {}

function profile:unique_nick() end
function profile:online() end

---@class login_operation_cb
login_operation_cb = {}

function login_operation_cb:bind() end
function login_operation_cb:clear() end

-- Exported in src\xrGame\memory_space_script.cpp

---@class rotation
---@field yaw any readonly
---@field pitch any readonly

---@class object_params
---@field orientation any readonly
---@field level_vertex any readonly
---@field position any readonly

---@class memory_object
---@field game_time any readonly
---@field level_time any readonly
---@field last_game_time any readonly
---@field last_level_time any readonly
---@field first_game_time any readonly
---@field first_level_time any readonly
---@field update_count any readonly

---@class entity_memory_object
---@field object_info any readonly
---@field self_info any readonly
entity_memory_object = {}

function entity_memory_object:object() end

---@class game_memory_object
---@field object_info any readonly
---@field self_info any readonly
game_memory_object = {}

function game_memory_object:object() end

---@class hit_memory_object
---@field direction any readonly
---@field bone_index any readonly
---@field amount any readonly

---@class visible_memory_object

---@class memory_info
---@field visual_info any readonly
---@field sound_info any readonly
---@field hit_info any readonly

---@class sound_memory_object
---@field power any readonly
sound_memory_object = {}

function sound_memory_object:type() end

---@class not_yet_visible_object
---@field value any readonly
not_yet_visible_object = {}

function not_yet_visible_object:object() end

---@class danger_object
danger_object = {}

---@enum danger_object.danger_type
danger_object.danger_type = {
    bullet_ricochet = 0,
    attack_sound = 1,
    entity_attacked = 2,
    entity_death = 3,
    entity_corpse = 4,
    attacked = 5,
    grenade = 6,
    enemy_sound = 7
}  -- TODO: Check values

---@enum danger_object.danger_perceive_type
danger_object.danger_perceive_type = {
    visual = 0,
    sound = 1,
    hit = 3
}  -- TODO: Check values

function danger_object:position() end
function danger_object:time() end
function danger_object:type() end
function danger_object:perceive_type() end
function danger_object:object() end
function danger_object:dependent_object() end

-- Exported in src\xrGame\particle_params_script.cpp

---@class particle_params

-- Exported in src\xrGame\patrol_path_params_script.cpp

---@class patrol
patrol = {}

---@enum patrol.start
patrol.start = {
    start = 0,
    stop = 1,
    nearest = 2,
    custom = 3,
    next = 4,
    dummy = 5
}  -- TODO: Check values

---@enum patrol.stop
patrol.stop = {
    stop = 0,
    continue = 1,
    dummy = 2
}  -- TODO: Check values

function patrol:count() end
function patrol:level_vertex_id() end
function patrol:game_vertex_id() end
function patrol:point() end
function patrol:name() end
function patrol:index() end
function patrol:get_nearest() end
function patrol:flag() end
function patrol:flags() end
function patrol:terminal() end

-- Exported in src\xrGame\PhraseDialog_script.cpp

---@class CPhrase
CPhrase = {}

function CPhrase:GetPhraseScript() end

---@class CPhraseDialog
CPhraseDialog = {}

function CPhraseDialog:AddPhrase() end

---@class CPhraseScript
CPhraseScript = {}

function CPhraseScript:AddPrecondition() end
function CPhraseScript:AddAction() end
function CPhraseScript:AddHasInfo() end
function CPhraseScript:AddDontHasInfo() end
function CPhraseScript:AddGiveInfo() end
function CPhraseScript:AddDisableInfo() end
function CPhraseScript:SetScriptText() end

-- Exported in src\xrGame\PHSimpleCallsScript.cpp

---@class phcondition_callonstep
phcondition_callonstep = {}

function phcondition_callonstep:set_step() end
function phcondition_callonstep:set_steps_interval() end
function phcondition_callonstep:set_global_time_ms() end
function phcondition_callonstep:set_global_time_s() end
function phcondition_callonstep:set_time_interval_ms() end
function phcondition_callonstep:set_time_interval_s() end

---@class phcondition_expireonstep

---@class phaction_constforce

-- Exported in src\xrGame\physics_element_scripted.cpp

---@class physics_element
physics_element = {}

function physics_element:apply_force() end
function physics_element:apply_torque() end
function physics_element:is_breakable() end
function physics_element:get_linear_vel() end
function physics_element:get_angular_vel() end
function physics_element:get_mass() end
function physics_element:get_density() end
function physics_element:get_volume() end
function physics_element:fix() end
function physics_element:release_fixed() end
function physics_element:is_fixed() end
function physics_element:global_transform() end

-- Exported in src\xrGame\physics_joint_scripted.cpp

---@class physics_joint
physics_joint = {}

function physics_joint:get_bone_id() end
function physics_joint:get_first_element() end
function physics_joint:get_stcond_element() end
function physics_joint:set_anchor_global() end
function physics_joint:set_anchor_vs_first_element() end
function physics_joint:set_anchor_vs_second_element() end
function physics_joint:get_axes_number() end
function physics_joint:set_axis_spring_dumping_factors() end
function physics_joint:set_joint_spring_dumping_factors() end
function physics_joint:set_axis_dir_global() end
function physics_joint:set_axis_dir_vs_first_element() end
function physics_joint:set_axis_dir_vs_second_element() end
function physics_joint:set_limits() end
function physics_joint:set_max_force_and_velocity() end
function physics_joint:get_max_force_and_velocity() end
function physics_joint:get_axis_angle() end
function physics_joint:get_limits() end
function physics_joint:get_axis_dir() end
function physics_joint:get_anchor() end
function physics_joint:is_breakable() end

-- Exported in src\xrGame\physics_shell_scripted.cpp

---@class physics_shell
physics_shell = {}

function physics_shell:apply_force() end
function physics_shell:apply_torque() end
function physics_shell:get_element_by_bone_name() end
function physics_shell:get_element_by_bone_id() end
function physics_shell:get_element_by_order() end
function physics_shell:get_elements_number() end
function physics_shell:get_joint_by_bone_name() end
function physics_shell:get_joint_by_bone_id() end
function physics_shell:get_joint_by_order() end
function physics_shell:get_joints_number() end
function physics_shell:block_breaking() end
function physics_shell:unblock_breaking() end
function physics_shell:is_breaking_blocked() end
function physics_shell:is_breakable() end
function physics_shell:get_linear_vel() end
function physics_shell:get_angular_vel() end
function physics_shell:freeze() end
function physics_shell:unfreeze() end

-- Exported in src\xrGame\physics_world_scripted.cpp

---@class physics_world
physics_world = {}

function physics_world:set_gravity() end
function physics_world:gravity() end
function physics_world:add_call() end

-- Exported in src\xrGame\player_hud_script.cpp

---@class player_hud
player_hud = {}

function player_hud:set_hands() end
function player_hud:reset_hands() end

function get_player_hud() end

-- Exported in src\xrGame\profile_data_types_script.cpp

---@class award_data
---@field m_count any readonly
---@field m_last_reward_date any readonly

---@class award_pair_t
---@field first any readonly
---@field second any readonly

---@class best_scores_pair_t
---@field first any readonly
---@field second any readonly

---@class store_operation_cb
store_operation_cb = {}

function store_operation_cb:bind() end
function store_operation_cb:clear() end

-- Exported in src\xrGame\profile_store_script.cpp

---@class profile_store
profile_store = {}

function profile_store:load_current_profile() end
function profile_store:stop_loading() end
function profile_store:get_awards() end
function profile_store:get_best_scores() end

---@enum profile_store.enum_awards_t
profile_store.enum_awards_t = {
    at_award_massacre = 0,
    at_awards_count = 1
}  -- TODO: Check values


--@enum profile_store.enum_best_score_type
profile_store.enum_best_score_type = {
    bst_kills_in_row = 0,
    bst_kinife_kills_in_row = 1,
    bst_backstabs_in_row = 2,
    bst_head_shots_in_row = 3,
    bst_eye_kills_in_row = 4,
    bst_bleed_kills_in_row = 5,
    bst_explosive_kills_in_row = 6,
    bst_score_types_count = 7
}  -- TODO: Check values

-- Exported in src\xrGame\saved_game_wrapper_script.cpp

---@class CSavedGameWrapper
CSavedGameWrapper = {}

function CSavedGameWrapper:game_time() end
function CSavedGameWrapper:level_id() end
function CSavedGameWrapper:level_name() end
function CSavedGameWrapper:actor_health() end

function valid_saved_game() end
