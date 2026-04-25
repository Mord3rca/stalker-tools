---@meta

-- Exported in src\xrGame\action_base_script.cpp

---@class action_base
---@field object game_object readonly
---@field storage property_storage readonly
action_base = {}

function action_base:action_base() end
function action_base:object() end
function action_base:storage() end
function action_base:add_precondition() end
function action_base:add_effect() end
function action_base:remove_precondition() end
function action_base:remove_effect() end
function action_base:setup() end
function action_base:initialize() end
function action_base:execute() end
function action_base:finalize() end
function action_base:weight() end
function action_base:set_weight() end
function action_base:show() end

-- Exported in src\xrGame\action_planner_action_script.cpp

---@class planner_action
planner_action = {}

function planner_action:setup() end
function planner_action:initialize() end
function planner_action:execute() end
function planner_action:finalize() end
function planner_action:show() end
function planner_action:weight() end

-- Exported in src\xrGame\action_planner_script.cpp

---@class action_planner
---@field object game_object readonly
---@field storage property_storage readonly
action_planner = {}

function action_planner:object() end
function action_planner:storage() end
function action_planner:actual() end
function action_planner:setup() end
function action_planner:update() end
function action_planner:add_action() end
function action_planner:remove_action() end
function action_planner:action() end
function action_planner:add_evaluator() end
function action_planner:remove_evaluator() end
function action_planner:evaluator() end
function action_planner:current_action_id() end
function action_planner:current_action() end
function action_planner:initialized() end
function action_planner:set_goal_world_state() end
function action_planner:clear() end
function action_planner:show() end
function action_planner:cast_planner() end
