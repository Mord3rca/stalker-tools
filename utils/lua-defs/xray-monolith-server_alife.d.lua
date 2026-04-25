---@meta

-- Exported in src\xrServerEntities\xrServer_Objects_ALife_script.cpp

---@class cse_alife_schedulable
cse_alife_schedulable = {}

---@class cse_alife_dynamic_object
cse_alife_dynamic_object = {}

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
