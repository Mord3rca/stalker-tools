---@meta

--- Exported in src\xrGame\account_manager_script.cpp

---@class account_manager
account_manager = {}

function account_manager:suggest_unique_nicks() end
function account_manager:stop_suggest_unique_nicks() end
function account_manager:get_suggested_unicks() end
function account_manager:create_profile() end
function account_manager:delete_profile() end
function account_manager:is_get_account_profiles_active() end
function account_manager:get_account_profiles() end
function account_manager:stop_fetching_account_profiles() end
function account_manager:get_found_profiles() end
function account_manager:verify_unique_nick() end
function account_manager:verify_email() end
function account_manager:verify_password() end
function account_manager:get_verify_error_descr() end
function account_manager:is_email_searching_active() end
function account_manager:search_for_email() end
function account_manager:stop_searching_email() end

---@class suggest_nicks_cb
suggest_nicks_cb = {}

function suggest_nicks_cb:bind() end
function suggest_nicks_cb:clear() end

---@class account_operation_cb
account_operation_cb = {}

function account_operation_cb:bind() end
function account_operation_cb:clear() end

---@class account_profiles_cb
account_profiles_cb = {}

function account_profiles_cb:bind() end
function account_profiles_cb:clear() end

---@class found_email_cb
found_email_cb = {}

function found_email_cb:bind() end
function found_email_cb:clear() end
