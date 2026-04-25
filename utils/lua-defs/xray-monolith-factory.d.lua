---@meta

-- Defined in src\xrServerEntities\object_factory_script.cpp

---@class object_factory
object_factory = {}

---@param client_class string
---@param server_class string
---@param clsid string
---@param script_clsid string
---@return object_factory
function object_factory:register(client_class, server_class, clsid, script_clsid) end

---@param unknown_class string
---@param clsid string
---@param script_clsid string
---@return object_factory
function object_factory:register(unknown_class, clsid, script_clsid) end
