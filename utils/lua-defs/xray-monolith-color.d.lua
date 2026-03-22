
---@meta

-- Definition of fcolor object in src/xrServerEntities/script_fcolor_script.cpp

-- Implementation of fcolor based on Fcolor in src/xrCore/_color.h

---@class fcolor
---@field r number
---@field g number
---@field b number
---@field a number
fcolor = {}

---Set RGBA value of fcolor object
---@param r number
---@param g number
---@param b number
---@param a number
---@return fcolor self
function fcolor:set(r, g, b, a) end

---Set RGBA value of fcolor object
---@param f fcolor
---@return fcolor self
function fcolor:set(f) end

---Set RGBA value of fcolor object
---@param v number u32
---@return fcolor self
function fcolor:set(v) end
