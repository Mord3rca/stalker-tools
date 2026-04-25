---@meta

-- Exported in src\xrServerEntities\xrServer_Objects_ALife_Items_script.cpp

---@class cse_alife_inventory_item
cse_alife_inventory_item = {}

function cse_alife_inventory_item:has_upgrade() end
function cse_alife_inventory_item:add_upgrade() end

---@class cse_alife_item
cse_alife_item = {}

---@class cse_alife_item_torch
cse_alife_item_torch = {}

---@class cse_alife_item_ammo
cse_alife_item_ammo = {}

---@class cse_alife_item_weapon
cse_alife_item_weapon = {}

function cse_alife_item_weapon:clone_addons() end
function cse_alife_item_weapon:set_ammo_elapsed() end
function cse_alife_item_weapon:get_ammo_elapsed() end
function cse_alife_item_weapon:get_ammo_magsize() end

---@class cse_alife_item_weapon_shotgun
cse_alife_item_weapon_shotgun = {}

---@class cse_alife_item_weapon_auto_shotgun
cse_alife_item_weapon_auto_shotgun = {}

---@class cse_alife_item_detector
cse_alife_item_detector = {}

---@class cse_alife_item_artefact
cse_alife_item_artefact = {}

-- Exported in src\xrServerEntities\xrServer_Objects_ALife_Items_script2.cpp

---@class cse_alife_item_pda 
---@class cse_alife_item_document 
---@class cse_alife_item_grenade 
---@class cse_alife_item_explosive 
---@class cse_alife_item_bolt 
---@class cse_alife_item_custom_outfit 
---@class cse_alife_item_helmet 
---@class cse_alife_item_weapon_magazined

-- Exported in src\xrServerEntities\xrServer_Objects_ALife_Items_script3.cpp

---@class cse_alife_item_weapon_magazined_w_gl

-- Exported in src\xrServerEntities\xrServer_Objects_ALife_Monsters_script.cpp

---@class cse_alife_trader_abstract
cse_alife_trader_abstract = {}

function cse_alife_trader_abstract:community() end
function cse_alife_trader_abstract:profile_name() end
function cse_alife_trader_abstract:set_profile_name() end
function cse_alife_trader_abstract:character_name() end
function cse_alife_trader_abstract:character_name_str() end
function cse_alife_trader_abstract:set_character_name() end
function cse_alife_trader_abstract:rank() end
function cse_alife_trader_abstract:set_rank() end
function cse_alife_trader_abstract:reputation() end
function cse_alife_trader_abstract:character_icon() end

---@class cse_alife_trader
cse_alife_trader = {}

---@class cse_custom_zone
cse_custom_zone = {}

---@class cse_anomalous_zone
cse_anomalous_zone = {}

---@class cse_alife_monster_rat
cse_alife_monster_rat = {}

-- Exported in src\xrServerEntities\xrServer_Objects_ALife_Monsters_script2.cpp

---@class cse_alife_creature_crow
cse_alife_creature_crow = {}

---@class cse_alife_monster_zombie
cse_alife_monster_zombie = {}

---@class cse_alife_monster_base
cse_alife_monster_base = {}

---@class cse_alife_human_stalker
cse_alife_human_stalker = {}

-- Exported in src\xrServerEntities\xrserver_objects_alife_monsters_script3.cpp

---@class cse_alife_creature_actor
cse_alife_creature_actor = {}

---@class cse_torrid_zone
cse_torrid_zone = {}

---@class cse_zone_visual
cse_zone_visual = {}

---@class cse_alife_creature_abstract
---@field team number
---@field squad number
---@field group number
cse_alife_creature_abstract = {}

function cse_alife_creature_abstract:health() end
function cse_alife_creature_abstract:alive() end
function cse_alife_creature_abstract:o_torso() end

---@class MEMBERS__value_type
---@field id number
---@field object cse_alife_monster_abstract
MEMBERS__value_type = {}

---@class cse_alife_online_offline_group
cse_alife_online_offline_group = {}

function cse_alife_online_offline_group:register_member() end
function cse_alife_online_offline_group:unregister_member() end
function cse_alife_online_offline_group:commander_id() end
function cse_alife_online_offline_group:squad_members() end
function cse_alife_online_offline_group:npc_count() end
function cse_alife_online_offline_group:add_location_type() end
function cse_alife_online_offline_group:clear_location_types() end
function cse_alife_online_offline_group:force_change_position() end

-- Exported in src\xrServerEntities\xrServer_Objects_ALife_Monsters_script4.cpp

---@class cse_alife_monster_abstract
---@field group_id number
---@field m_smart_terrain_id number
cse_alife_monster_abstract = {}

function cse_alife_monster_abstract:smart_terrain_id() end
function cse_alife_monster_abstract:clear_smart_terrain() end
function cse_alife_monster_abstract:brain() end
function cse_alife_monster_abstract:rank() end
function cse_alife_monster_abstract:smart_terrain_task_activate() end
function cse_alife_monster_abstract:smart_terrain_task_deactivate() end
function cse_alife_monster_abstract:travel_speed() end
function cse_alife_monster_abstract:travel_speed() end
function cse_alife_monster_abstract:current_level_travel_speed() end
function cse_alife_monster_abstract:current_level_travel_speed() end
function cse_alife_monster_abstract:kill() end
function cse_alife_monster_abstract:has_detector() end
function cse_alife_monster_abstract:force_set_goodwill() end

---@class cse_alife_human_abstract
cse_alife_human_abstract = {}

function cse_alife_human_abstract:brain() end
function cse_alife_human_abstract:rank() end
function cse_alife_human_abstract:set_rank() end

---@class cse_alife_psydog_phantom
cse_alife_psydog_phantom = {}

-- Exported in src\xrServerEntities\xrServer_Objects_ALife_script.cpp

---@class ipure_schedulable_object
ipure_schedulable_object = {}

---@class cse_alife_schedulable
cse_alife_schedulable = {}

---@class cse_alife_graph_point
cse_alife_graph_point = {}

---@class cse_alife_object
---@field online boolean
---@field m_level_vertex_id number
---@field m_game_vertex_id number
---@field m_story_id number
cse_alife_object = {}

function cse_alife_object:move_offline() end
function cse_alife_object:move_offline() end
function cse_alife_object:visible_for_map() end
function cse_alife_object:visible_for_map() end
function cse_alife_object:can_switch_online() end
function cse_alife_object:can_switch_offline() end
function cse_alife_object:use_ai_locations() end

---@class cse_alife_group_abstract
cse_alife_group_abstract = {}

---@class cse_alife_dynamic_object
cse_alife_dynamic_object = {}

---@class cse_alife_dynamic_object_visual
cse_alife_dynamic_object_visual = {}

---@class cse_alife_ph_skeleton_object
cse_alife_ph_skeleton_object = {}

---@class cse_alife_space_restrictor
cse_alife_space_restrictor = {}

---@class cse_alife_level_changer
cse_alife_level_changer = {}

---@class cse_alife_inventory_box
cse_alife_inventory_box = {}

-- Exported in src\xrServerEntities\xrServer_Objects_ALife_script2.cpp

---@class cse_alife_object_projector
cse_alife_object_projector = {}

---@class cse_alife_helicopter
cse_alife_helicopter = {}

---@class cse_alife_car
cse_alife_car = {}

---@class cse_alife_stmgun
cse_alife_stmgun = {}

function cse_alife_stmgun:get_ammo_magsize() end
function cse_alife_stmgun:set_ammo_elapsed() end
function cse_alife_stmgun:get_ammo_elapsed() end
function cse_alife_stmgun:get_ammo_type() end
function cse_alife_stmgun:set_ammo_type() end

---@class cse_alife_object_breakable
cse_alife_object_breakable = {}

---@class cse_alife_object_climable
cse_alife_object_climable = {}

---@class cse_alife_mounted_weapon
cse_alife_mounted_weapon = {}

---@class cse_alife_team_base_zone
cse_alife_team_base_zone = {}

-- Exported in src\xrServerEntities\xrServer_Objects_ALife_script3.cpp

---@class cse_alife_object_hanging_lamp
cse_alife_object_hanging_lamp = {}

---@class cse_alife_object_physic
cse_alife_object_physic = {}

function cse_alife_object_physic:set_yaw() end

---@class cse_alife_smart_zone
cse_alife_smart_zone = {}

-- Exported in src\xrServerEntities\xrServer_Objects_Alife_Smartcovers_script.cpp

---@class cse_smart_cover
cse_smart_cover = {}

function cse_smart_cover:description() end
function cse_smart_cover:set_available_loopholes() end
function cse_smart_cover:set_loopholes_table_checker() end
