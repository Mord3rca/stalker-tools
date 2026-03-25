local log_name = "[DLTX Exporter] "


function _adding_motion_length(section)
    local anim_key_name = {
        "anm_reload", "anm_reload_1", "anm_reload_2",
        "anm_reload_aim", "anm_reload_aim_ammo1", "anm_reload_aim_ammo11",
        "anm_reload_aim_ammo13", "anm_reload_aim_ammo15",
        "anm_reload_aim_ammo17", "anm_reload_aim_ammo19", "anm_reload_aim_ammo2",
        "anm_reload_aim_ammo21", "anm_reload_aim_ammo23", "anm_reload_aim_ammo25",
        "anm_reload_aim_ammo27", "anm_reload_aim_ammo29", "anm_reload_aim_ammo3",
        "anm_reload_aim_ammo31", "anm_reload_aim_ammo4", "anm_reload_aim_ammo5",
        "anm_reload_aim_ammo6", "anm_reload_aim_ammo7", "anm_reload_aim_ammo8",
        "anm_reload_aim_ammo9", "anm_reload_ammo1", "anm_reload_ammo11",
        "anm_reload_ammo13", "anm_reload_ammo15", "anm_reload_ammo17",
        "anm_reload_ammo19", "anm_reload_ammo2", "anm_reload_ammo21",
        "anm_reload_ammo23", "anm_reload_ammo25", "anm_reload_ammo27",
        "anm_reload_ammo29", "anm_reload_ammo3", "anm_reload_ammo31",
        "anm_reload_ammo4", "anm_reload_ammo5", "anm_reload_ammo6",
        "anm_reload_ammo7", "anm_reload_ammo8", "anm_reload_ammo9",
        "anm_reload_empty", "anm_reload_empty_aim", "anm_reload_empty_end",
        "anm_reload_empty_no_mag", "anm_reload_empty_variant1", "anm_reload_empty_w_gl",
        "anm_reload_empty_w_gl_aim", "anm_reload_empty_w_gl_variant1", "anm_reloadendemptytac_end",
        "anm_reloadendtac_end", "anm_reloadendtacnachalo_end", "anm_reload_g",
        "anm_reload_misfire", "anm_reload_misfire_aim", "anm_reload_misfire_aim_jammed",
        "anm_reload_misfire_empty", "anm_reload_misfire_empty_aim", "anm_reload_misfire_jammed",
        "anm_reload_misfire_variant1", "anm_reload_misfire_variant2", "anm_reload_misfire_variant3",
        "anm_reload_misfire_variant4", "anm_reload_misfire_variant5", "anm_reload_misfire_variant6",
        "anm_reload_misfire_w_gl", "anm_reload_misfire_w_gl_aim", "anm_reload_variant1",
        "anm_reload_w_gl", "anm_reload_w_gl_aim", "anm_reload_w_gl_misfire",
        "anm_reload_w_gl_variant1",
    } -- Can be extended for your needs
    -- To get all available anm key exec: grep -Eo 'anm_[^= ]*' outfile.ini | sort -u

    for _, name in pairs(anim_key_name) do
        if system_ini():line_exist(section, name) then
            -- If exist ask the game to calculate anim length and write it down to sys. config
            system_ini():w_float(
                section, name .. "_mlength",
                game.get_motion_length(section, name, 1)
            )
        end
    end

    return false  -- Continue iteration
end

local function export_system_config(_, __, cout)
        cout:SendOutput(log_name .. "Exporting configuration")
        system_ini():save_as(getFS():update_path("$logs$", string.format("outfile-%d.ini", os.time(os.date("!*t")))))
        cout:SendOutput(log_name .. "Export finished")
end

local function export_system_config_extended(_, __, cout)
        cout:SendOutput(log_name .. "Adding add. info in system configuration")
        system_ini():set_readonly(false)
        system_ini():section_for_each(_adding_motion_length)
        system_ini():set_readonly(true)

        -- Use previous func to dump system config
        export_system_config(_, __, cout)
end

local function on_game_load()
    local cmd = debug_cmd_list.command_get_list()

    -- Register dumping functions in DBG mode menu
    cmd.export_system_config = export_system_config
    ui_debug_launcher.inject("action", {name = "Export System Config", cmd = "export_system_config", hide_ui = 0})

    cmd.export_system_config_extended = export_system_config_extended
    ui_debug_launcher.inject("action", {name = "Export Sys. Config Ext.", cmd = "export_system_config_extended", hide_ui = 0})
end

function on_game_start()
    if not DEV_DEBUG then
        return
    end

    RegisterScriptCallback("on_game_load", on_game_load)
end
