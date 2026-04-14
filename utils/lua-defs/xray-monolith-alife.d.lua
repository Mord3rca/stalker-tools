---@meta

-- Exported in src\xrGame\alife_monster_brain_script.cpp
---@class CALifeMonsterBrain
CALifeMonsterBrain = {}

---@return CALifeMonsterMovementManager
function CALifeMonsterBrain:movement() end

function CALifeMonsterBrain:update() end

---@param value boolean
function CALifeMonsterBrain:can_choose_alife_tasks(value) end

-- Exported in src\xrGame\alife_monster_detail_path_manager_script.cpp
---@class CALifeMonsterDetailPathManager
CALifeMonsterDetailPathManager = {}

---@param game_vertex_id number
---@param level_vertex_id number
---@param position vector
function CALifeMonsterDetailPathManager:target(game_vertex_id, level_vertex_id, position) end

---@param game_vertex_id number
function CALifeMonsterDetailPathManager:target(game_vertex_id) end

---@param task CALifeSmartTerrainTask
function CALifeMonsterDetailPathManager:target(task) end

---@param speed number
function CALifeMonsterDetailPathManager:speed(speed) end

---@return number
function CALifeMonsterDetailPathManager:speed() end

---@return boolean
function CALifeMonsterDetailPathManager:completed() end

---@return boolean
function CALifeMonsterDetailPathManager:actual() end

---@return boolean
function CALifeMonsterDetailPathManager:failed() end

-- Exported in src\xrGame\alife_monster_movement_manager_script.cpp
---@class CALifeMonsterMovementManager
CALifeMonsterMovementManager = {}

---@return CALifeMonsterDetailPathManager
function CALifeMonsterMovementManager:detail() end

---@return CALifeMonsterPatrolPathManager
function CALifeMonsterMovementManager:patrol() end

---@return EPathType
function CALifeMonsterMovementManager:path_type() end

---@return EPathType
function CALifeMonsterMovementManager:path_type() end

---@return boolean
function CALifeMonsterMovementManager:actual() end

---@return boolean
function CALifeMonsterMovementManager:completed() end

-- Exported in src\xrGame\alife_monster_patrol_path_manager_script.cpp
---@class CALifeMonsterPatrolPathManager
CALifeMonsterPatrolPathManager = {}

---@param path_name string
function CALifeMonsterPatrolPathManager:path(path_name) end

---@return number -- since EPatrolStartType dont exist
function CALifeMonsterPatrolPathManager:start_type() end

---@param start_type number -- since EPatrolStartType dont exist
function CALifeMonsterPatrolPathManager:start_type(start_type) end

---@return number
function CALifeMonsterPatrolPathManager:route_type() end

---@param route_type number
function CALifeMonsterPatrolPathManager:route_type(route_type) end

---@return boolean
function CALifeMonsterPatrolPathManager:actual() end

---@return boolean
function CALifeMonsterPatrolPathManager:completed() end

---@param start_vertex_index number
function CALifeMonsterPatrolPathManager:start_vertex_index(start_vertex_index) end

---@return boolean
function CALifeMonsterPatrolPathManager:use_randomness() end

---@param use_randomness boolean
function CALifeMonsterPatrolPathManager:use_randomness(use_randomness) end

---@return number
function CALifeMonsterPatrolPathManager:target_game_vertex_id() end

---@return number
function CALifeMonsterPatrolPathManager:target_level_vertex_id() end

---@return vector
function CALifeMonsterPatrolPathManager:target_position() end

-- Exported in src\xrGame\alife_simulator_script.cpp
---@class alife_object_iterator
alife_object_iterator = {}

function alife_object_iterator:next() end
function alife_object_iterator:__call() end

---@class alife_object_without_actor_iterator
alife_object_without_actor_iterator = {}

function alife_object_without_actor_iterator:next() end
function alife_object_without_actor_iterator:__call() end

---@class alife_simulator
alife_simulator = {}

---@param object_id number
---@return boolean
function alife_simulator:valid_object_id(object_id) end

---@return number
function alife_simulator:level_id() end

---@param level_id number
---@return string
function alife_simulator:level_name(level_id) end

---@param object_id number
---@return cse_alife_dynamic_object
function alife_simulator:object(object_id) end

---@param id number
---@param no_assert boolean
---@return cse_alife_dynamic_object
function alife_simulator:object(id, no_assert) end

---@param id number
---@return cse_alife_dynamic_object
function alife_simulator:story_object(id) end

---@param id number
---@param value boolean
function alife_simulator:set_switch_online(id, value) end

---@param id number
---@param value boolean
function alife_simulator:set_switch_offline(id, value) end

---@param id number
---@param value boolean
function alife_simulator:set_interactive(id, value) end

---@param l_tpALifeMonsterAbstract cse_alife_dynamic_object
---@param l_tGraphID number
---@param schedulable cse_alife_schedulable
function alife_simulator:kill_entity(l_tpALifeMonsterAbstract, l_tGraphID, schedulable) end

---@param monster cse_alife_dynamic_object
---@param game_vertex_id number
function alife_simulator:kill_entity(monster, game_vertex_id) end

---@param monster cse_alife_dynamic_object
function alife_simulator:kill_entity(monster) end

---@param monster cse_alife_dynamic_object
---@param id number
function alife_simulator:add_in_restriction(monster, id) end

---@param monster cse_alife_dynamic_object
---@param id number
function alife_simulator:add_out_restriction(monster, id) end

---@param monster cse_alife_dynamic_object
---@param id number
function alife_simulator:remove_in_restriction(monster, id) end

---@param monster cse_alife_dynamic_object
---@param id number
function alife_simulator:remove_out_restriction(monster, id) end

function alife_simulator:remove_all_restrictions() end

---@param spawn_id number
---@return cse_alife_dynamic_object
function alife_simulator:create(spawn_id) end

---@param section string
---@param position vector
---@param level_vertex_id number
---@param game_vertex_id number
---@return cse_abstract
function alife_simulator:create(section, position, level_vertex_id, game_vertex_id) end

---@param section string
---@param position vector
---@param level_vertex_id number
---@param game_vertex_id number
---@param id_parent number
---@return cse_abstract
function alife_simulator:create(section, position, level_vertex_id, game_vertex_id, id_parent) end

---@param section string
---@param position vector
---@param level_vertex_id number
---@param game_vertex_id number
---@param id_parent number
---@param reg? boolean
---@return cse_abstract
function alife_simulator:create(section, position, level_vertex_id, game_vertex_id, id_parent, reg) end

---@param section string
---@param position vector
---@param level_vertex_id number
---@param game_vertex_id number
---@param id_parent number
---@param ammo_to_spawn number
---@return cse_abstract
function alife_simulator:create_ammo(section, position, level_vertex_id, game_vertex_id, id_parent, ammo_to_spawn) end

---@param object cse_abstract
function alife_simulator:release(object) end

---@param spawn_story_id number
---@return number
function alife_simulator:spawn_id(spawn_story_id) end

---@return cse_alife_creature_actor
function alife_simulator:actor() end

---@param id number
---@param info_id string
---@return boolean
function alife_simulator:has_info(id, info_id) end

---@param id number
---@param info_id string
---@return boolean
function alife_simulator:dont_has_info(id, info_id) end

---@param id number
---@param info_id string
function alife_simulator:give_info(id, info_id) end

---@param id number
---@param info_id string
function alife_simulator:disable_info(id, info_id) end

---@return number
function alife_simulator:switch_distance() end

---@param switch_distance number
function alife_simulator:set_switch_distance(switch_distance) end

---@param id number
---@param game_vertex_id number
---@param level_vertex_id number
---@param position vector
function alife_simulator:teleport_object(id, game_vertex_id, level_vertex_id, position) end

---@param id number
---@param functor fun()
function alife_simulator:iterate_info(id, functor) end

---@param object cse_abstract
---@param section string
---@param position vector
---@param level_vertex_id number
---@param game_vertex_id number
---@param id_parent number
---@param bRegister? boolean
function alife_simulator:clone_weapon(object, section, position, level_vertex_id, game_vertex_id, id_parent, bRegister) end

---@param object cse_abstract
---@return cse_abstract
function alife_simulator:register(object) end

---@param count number
function alife_simulator:set_objects_per_update(count) end

---@param micro number
function alife_simulator:set_process_time(micro) end

---@param object cse_abstract
---@return number[]
function alife_simulator:get_children(object) end

---@param keytable? boolean
---@param withActor? boolean
---@return any
function alife_simulator:object_ids(keytable, withActor) end

---@param keytable? boolean
---@param withActor? boolean
---@return any
function alife_simulator:objects(keytable, withActor) end

---@param functor fun(se: any): boolean
function alife_simulator:iterate_objects(functor) end

---@return number
function alife_simulator:max_id() end

---@return alife_simulator
function alife() end

-- TODO: Check the 2 routines to gen _story_ids \ _spawn_story_ids tables

-- Exported in src\xrGame\alife_smart_terrain_task_script.cpp
---@class CALifeSmartTerrainTask
---@overload fun(string): CALifeSmartTerrainTask
---@overload fun(string, number): CALifeSmartTerrainTask
---@overload fun(number, number): CALifeSmartTerrainTask
CALifeSmartTerrainTask = {}

---@return number
function CALifeSmartTerrainTask:game_vertex_id() end

---@return number
function CALifeSmartTerrainTask:level_vertex_id() end

---@return vector
function CALifeSmartTerrainTask:position() end
