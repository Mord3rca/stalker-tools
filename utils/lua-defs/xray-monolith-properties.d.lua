---@meta

-- Exported in src\xrGame\property_evaluator_script.cpp

---@class property_evaluator
---@field object game_object readonly
---@field storage property_storage readonly
property_evaluator = {}

function property_evaluator:setup() end
function property_evaluator:evaluate() end

---@class property_evaluator_const:property_evaluator

-- Exported in src\xrGame\property_storage_script.cpp

---@class property_storage
property_storage = {}

function property_storage:set_property() end
function property_storage:property() end
