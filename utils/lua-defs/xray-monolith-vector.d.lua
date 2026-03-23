
---@meta

-- Definition of vectors object in src/xrServerEntities/script_fvector_script.cpp

-- vector2 implementation based on Fvector2 in src/xrCore/_vector2.h

---@class vector2
---@field x number
---@field y number
vector2 = {}

---Normalize vector
---@param v vector2
---@return vector2 self
function vector2:normalize(v) end

---Set vector fields
---@param v vector2
---@return vector2 self
function vector2:set(v) end

---Set vector fields
---@param x number
---@param y number
---@return vector2 self
function vector2:set(x, y) end

-- Fbox implementation based on Fbox in src/xrCore/_fbox.h

---@class Fbox
---@field min number
---@field max number

-- Frect implementation based on Frect in src/xrCore/_rect.h

---@class Frect
---@field lt vector2
---@field rb vector2
---@field x1 number
---@field x2 number
---@field y1 number
---@field y2 number
Frect = {}

---Set Frect values
---@param x1 number
---@param x2 number
---@param y1 number
---@param y2 number
---@return Frect self
function Frect:set(x1, x2, y1, y2) end

-- vector implementation based on Fvector in src/xrCore/_vector3d.h

---@class vector
---@field x number
---@field y number
---@field z number
vector = {}

---generate_orthonormal_basis
---@param dir vector
---@param up vector
---@param right vector
function vector.generate_orthonormal_basis(dir, up, right) end

---generate_orthonormal_basis_normalized
---@param dir vector
---@param up vector
---@param right vector
function vector.generate_orthonormal_basis_normalized(dir, up, right) end

---Set
---@param x number
---@param y number
---@param z number
---@return vector self
function vector:set(x, y, z) end

---Set
---@param v vector
---@return vector self
function vector:set(v) end

---Add
---@param v number
---@return vector self
function vector:add(v) end

---Add
---@param x number
---@param y number
---@param z number
---@return vector self
function vector:add(x, y, z) end

---Add
---@param v vector
---@return vector self
function vector:add(v) end

---Add
---@param a vector
---@param v vector
---@return vector self
function vector:add(a, v) end

---Add
---@param a vector
---@param v number
---@return vector self
function vector:add(a, v) end

---Sub
---@param v number
---@return vector self
function vector:sub(v) end

---Sub
---@param x number
---@param y number
---@param z number
---@return vector self
function vector:sub(x, y, z) end

---Sub
---@param v vector
---@return vector self
function vector:sub(v) end

---Sub
---@param a vector
---@param v vector
---@return vector self
function vector:sub(a, v) end

---Sub
---@param a vector
---@param v number
---@return vector self
function vector:sub(a, v) end

---Mul
---@param v number
---@return vector self
function vector:mul(v) end

---Mul
---@param x number
---@param y number
---@param z number
---@return vector self
function vector:mul(x, y, z) end

---Mul
---@param v vector
---@return vector self
function vector:mul(v) end

---Mul
---@param a vector
---@param v vector
---@return vector self
function vector:mul(a, v) end

---Mul
---@param a vector
---@param v number
---@return vector self
function vector:mul(a, v) end

---Div
---@param v number
---@return vector self
function vector:div(v) end

---Div
---@param x number
---@param y number
---@param z number
---@return vector self
function vector:div(x, y, z) end

---Div
---@param v vector
---@return vector self
function vector:div(v) end

---Div
---@param a vector
---@param v vector
---@return vector self
function vector:div(a, v) end

---Div
---@param a vector
---@param v number
---@return vector self
function vector:div(a, v) end

--Invert
---@return vector self
function vector:invert() end

--Invert
---@param a vector
---@return vector self
function vector:invert(a) end

--Min
---@param a vector
---@return vector self
function vector:min(a) end

--Min
---@param v1 vector
---@param v2 vector
---@return vector self
function vector:min(v1, v2) end

--Max
---@param a vector
---@return vector self
function vector:max(a) end

--Max
---@param v1 vector
---@param v2 vector
---@return vector self
function vector:max(v1, v2) end

--Abs
---@param v vector
---@return vector self
function vector:abs(v) end

--Similar
---@param v vector
---@param e number
---@return boolean
function vector:similar(v, e) end

--Set length
---@param l number
---@return vector self
function vector:set_length(l) end

--Align
---@return vector self
function vector:align() end

---Clamp
---@param v vector
---@return vector self
function vector:clamp(v) end

---Clamp
---@param min vector
---@param max vector
---@return vector self
function vector:clamp(min, max) end

---Inertion
---@param p vector
---@param v number
---@return vector self
function vector:inertion(p, v) end

---Average
---@param p vector
---@return vector self
function vector:average(p) end

---Average
---@param p1 vector
---@param p2 vector
---@return vector self
function vector:average(p1, p2) end

---Lerp
---@param p1 vector
---@param p2 vector
---@param t number
---@return vector self
function vector:lerp(p1, p2, t) end

---Mad
---@param d vector
---@param m number
---@return vector self
function vector:mad(d, m) end

---Mad
---@param p vector
---@param d vector
---@param m number
---@return vector self
function vector:mad(p, d, m) end

---Mad
---@param d vector
---@param s vector
---@return vector self
function vector:mad(d, s) end

---Mad
---@param p vector
---@param d vector
---@param s vector
---@return vector self
function vector:mad(p, d, s) end

---Magnitude
---@return number
function vector:magnitude() end

---Normalize
---@return vector self
function vector:normalize() end

---Normalize
---@param v vector
---@return vector self
function vector:normalize(v) end

---Normalize safe
---@return vector self
function vector:normalize_safe() end

---Normalize safe
---@param v vector
---@return vector self
function vector:normalize_safe(v) end

---Dot product
---@param v vector
---@return number
function vector:dotproduct(v) end

---Cross product
---@param v1 vector
---@param v2 vector
---@return vector self
function vector:crossproduct(v1, v2) end

---Distance to xz
---@param v vector
---@return number
function vector:distance_to_xz(v) end

---Distance to xz sqr
---@param v vector
---@return number
function vector:distance_to_xz_sqr(v) end

---Distance to sqr
---@param v vector
---@return number
function vector:distance_to_sqr(v) end

---Distance to
---@param v vector
---@return number
function vector:distance_to(v) end

---Set HP
---@param h number
---@param p number
---@return vector self
function vector:setHP(h, p) end

---Get H
---@return number
function vector:getH() end

---Get P
---@return number
function vector:getP() end

---Reflect
---@param dir vector
---@param norm vector
---@return vector self
function vector:reflect(dir, norm) end

---Slide
---@param dir vector
---@param norm vector
---@return vector self
function vector:slide(dir, norm) end

---Project
---@param v vector
---@param other vector
---@return vector self
function vector:project(v, other) end

---Project
---@param other vector
---@return vector self
function vector:project(other) end

---Hud to world
---@return vector self
function vector:hud_to_world() end

---World to hud
---@return vector self
function vector:world_to_hud() end

---Hud to world dir
---@return vector self
function vector:hud_to_world_dir() end

---World to hud dir
---@return vector self
function vector:world_to_hud_dir() end

-- vector4 implementation based on Fvector4 in src/xrCore/_vector4.h

---@class vector4
---@field x number
---@field y number
---@field z number
---@field w number
vector4 = {}

---Set vector4
---@param x number
---@param y number
---@param z number
---@param w number
---@return vector4 self
function vector4:set(x, y, z, w) end

---Set vector4
---@param v vector4
---@return vector4 self
function vector4:set(v) end

---Add to vector4
---@param x number
---@param y number
---@param z number
---@param w? number
---@return vector4 self
function vector4:add(x, y, z, w) end

---Add to vector4
---@param v vector4
---@return vector4 self
function vector4:add(v) end

---Add to vector4
---@param vs number
---@return vector4 self
function vector4:add(s) end

---Add to vector4
---@param a vector4
---@param v vector4
---@return vector4 self
function vector4:add(a, v) end

---Add to vector4
---@param a vector4
---@param s number
---@return vector4 self
function vector4:add(a, s) end

---Subtract to vector4
---@param x number
---@param y number
---@param z number
---@param w? number
---@return vector4 self
function vector4:sub(x, y, z, w) end

---Subtract to vector4
---@param v vector4
---@return vector4 self
function vector4:sub(v) end

---Subtract to vector4
---@param s number
---@return vector4 self
function vector4:sub(s) end

---Subtract to vector4
---@param a vector4
---@param v vector4
---@return vector4 self
function vector4:sub(a, v) end

---Subtract to vector4
---@param a vector4
---@param s number
---@return vector4 self
function vector4:sub(a, s) end

---Multiply vector4
---@param x number
---@param y number
---@param z number
---@param w? number
---@return vector4 self
function vector4:mul(x, y, z, w) end

---Multiply vector4
---@param v vector4
---@return vector4 self
function vector4:mul(v) end

---Multiply vector4
---@param s number
---@return vector4 self
function vector4:mul(s) end

---Multiply vector4
---@param a vector4
---@param v vector4
---@return vector4 self
function vector4:mul(a, v) end

---Multiply vector4
---@param a vector4
---@param s number
---@return vector4 self
function vector4:mul(a, s) end

---Divide vector4
---@param x number
---@param y number
---@param z number
---@param w? number
---@return vector4 self
function vector4:div(x, y, z, w) end

---Divide vector4
---@param v vector4
---@return vector4 self
function vector4:div(v) end

---Divide vector4
---@param s number
---@return vector4 self
function vector4:div(s) end

---Divide vector4
---@param a vector4
---@param v vector4
---@return vector4 self
function vector4:div(a, v) end

---Divide vector4
---@param a vector4
---@param s number
---@return vector4 self
function vector4:div(a, s) end

---Clamp vector4
---@param min vector4
---@param max vector4
---@return vector4 self
function vector4:clamp(min, max) end

---Clamp vector4
---@param v vector4
---@return vector4 self
function vector4:clamp(v) end

---Verify similitude
---@param v vector4
---@param r? number
---@return boolean
function vector4:similar(v, r) end

---Get magnitude
---@return number
function vector4:magnitude() end

---Normalize
---@return vector4 self
function vector4:normalize() end

---Normalize as plane
---@return vector4 self
function vector4:normalize_as_plane() end

---Lerp
---@param p1 vector4
---@param p2 vector4
---@param t number
---@return vector4 self
function vector4:lerp(p1, p2, t) end
