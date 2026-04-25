---@meta

-- Defined in src\xrServerEntities\script_engine_script.cpp

---@param caMessage string
function log(caMessage) end

function print_stack() end
function error_log() end
function flush() end
function prefetch() end
function verify_if_thread_is_running() end
function editor() end
function bit_and() end
function bit_or() end
function bit_xor() end
function bit_not() end
function user_name() end
function time_global() end
function time_global_async() end
function add_scope_radii() end
function device() end
function is_enough_address_space_available() end

---@class profile_timer
profile_timer = {}

function profile_timer:start() end
function profile_timer:stop() end
function profile_timer:time() end
