local log_name = "[DLTX Exporter] "

function debug_cmd_list.cmd.export_system_config(_, __, cout)
    cout:SendOutput(log_name .. "Exporting configuration")
    system_ini():save_as("outfile.ini")
    cout:SendOutput(log_name .. "Export finished")
end

-- Register dumping function in DBG mode menu
ui_debug_launcher.inject("action", {name = "Export System Config", cmd = "export_system_config", hide_ui = 0})
