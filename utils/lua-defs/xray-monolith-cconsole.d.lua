---@meta

---@class CConsole

CConsole = {}

---Execute a command
---@param cmd string
function CConsole:execute(cmd) end

---Execute a script
---@param str string
function CConsole:execute_script(str) end

---Show Console
function CConsole:show() end

---Hide Console
function CConsole:hide() end

---Get string
---@param cmd string
---@return string
function CConsole:get_string(cmd) end

---Get integer
---@param cmd string
---@return number
function CConsole:get_integer(cmd) end

---Get variable bound
---@param cmd string
---@return {min: number, max: number}
function CConsole:get_variable_bounds(cmd) end

---Get boolean
---@param cmd string
---@return boolean
function CConsole:get_bool(cmd) end

---Get float
---@param cmd string
---@return number
function CConsole:get_float(cmd) end

---Get token (same as get string)
---@param cmd string
---@return string
function CConsole:get_token(cmd) end

---Get token list
---@param cmd string
---@return string[]
function CConsole:get_token_list(cmd) end

---Deferred execution of string
---@param string_to_execute string
function CConsole:execute_deferred(string_to_execute) end

---Get Console handler
---@return CConsole
function get_console() end
