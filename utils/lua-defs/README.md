## LUA definition files

This is a collection of LUA definition files used for documenting STALKER [XRay Monolith](https://github.com/themrdemonized/xray-monolith) LUA API.

### Installation

This set of definition are designed to be use with [lua-language-server](https://github.com/luals/lua-language-server) a VSCode addon

Add this folder to your `workspace.library` configuration key in addon settings (more info [here](https://luals.github.io/wiki/configuration/))

### TODO

List of files containing a LUA register which need a def file:

* [ ] src/Layers/xrRenderDX10/dx10ResourceManager_Scripting.cpp
* [ ] src/Layers/xrRender/ResourceManager_Scripting.cpp
* [ ] src/xrGame/account_manager_script.cpp
* [ ] src/xrGame/action_base_script.cpp
* [ ] src/xrGame/action_planner_action_script.cpp
* [ ] src/xrGame/action_planner_script.cpp
* [ ] src/xrGame/ActorCondition_script.cpp
* [ ] src/xrGame/actor_script.cpp
* [x] src/xrGame/ai_crow_script.cpp
* [x] src/xrGame/ai/monsters/bloodsucker/bloodsucker_script.cpp
* [x] src/xrGame/ai/monsters/boar/boar_script.cpp
* [x] src/xrGame/ai/monsters/burer/burer_script.cpp
* [x] src/xrGame/ai/monsters/cat/cat_script.cpp
* [x] src/xrGame/ai/monsters/chimera/chimera_script.cpp
* [x] src/xrGame/ai/monsters/controller/controller_script.cpp
* [x] src/xrGame/ai/monsters/dog/dog_script.cpp
* [x] src/xrGame/ai/monsters/flesh/flesh_script.cpp
* [x] src/xrGame/ai/monsters/fracture/fracture_script.cpp
* [x] src/xrGame/ai/monsters/poltergeist/poltergeist_script.cpp
* [x] src/xrGame/ai/monsters/pseudodog/pseudodog_script.cpp
* [x] src/xrGame/ai/monsters/pseudogigant/pseudogigant_script.cpp
* [x] src/xrGame/ai/monsters/snork/snork_script.cpp
* [x] src/xrGame/ai/monsters/tushkano/tushkano_script.cpp
* [x] src/xrGame/ai/monsters/zombie/zombie_script.cpp
* [x] src/xrGame/ai/stalker/ai_stalker_script.cpp
* [x] src/xrGame/ai/trader/ai_trader_script.cpp
* [x] src/xrGame/alife_monster_brain_script.cpp
* [x] src/xrGame/alife_monster_detail_path_manager_script.cpp
* [x] src/xrGame/alife_monster_movement_manager_script.cpp
* [x] src/xrGame/alife_monster_patrol_path_manager_script.cpp
* [x] src/xrGame/alife_simulator_script.cpp
* [x] src/xrGame/alife_smart_terrain_task_script.cpp
* [ ] src/xrGame/antirad_script.cpp
* [ ] src/xrGame/artefact_script.cpp
* [x] src/xrGame/base_client_classes_script.cpp
* [ ] src/xrGame/BottleItem_script.cpp
* [ ] src/xrGame/CarScript.cpp
* [ ] src/xrGame/client_spawn_manager_script.cpp
* [x] src/xrGame/console_registrator_script.cpp
* [ ] src/xrGame/cover_point_script.cpp
* [ ] src/xrGame/CustomOutfit_script.cpp
* [ ] src/xrGame/CustomZone_script.cpp
* [ ] src/xrGame/DemoInfo.cpp
* [ ] src/xrGame/eatable_item_script.cpp
* [ ] src/xrGame/ef_storage_script.cpp
* [ ] src/xrGame/ExplosiveScript.cpp
* [ ] src/xrGame/F1.cpp
* [ ] src/xrGame/FoodItem_script.cpp
* [ ] src/xrGame/fs_registrator_script.cpp
* [ ] src/xrGame/game_graph_script.cpp
* [ ] src/xrGame/GameTask_script.cpp
* [ ] src/xrGame/HairsZone_script.cpp
* [ ] src/xrGame/HangingLamp.cpp
* [ ] src/xrGame/helicopter_script.cpp
* [ ] src/xrGame/holder_custom_script.cpp
* [ ] src/xrGame/HudItem.cpp
* [ ] src/xrGame/HUDManager.cpp
* [ ] src/xrGame/HUDTarget.cpp
* [ ] src/xrGame/InventoryBox_script.cpp
* [ ] src/xrGame/inventory_item_script.cpp
* [ ] src/xrGame/InventoryOwner_script.cpp
* [ ] src/xrGame/level_script.cpp
* [ ] src/xrGame/login_manager_script.cpp
* [ ] src/xrGame/medkit_script.cpp
* [ ] src/xrGame/memory_space_script.cpp
* [ ] src/xrGame/mincer_script.cpp
* [ ] src/xrGame/Missile.cpp
* [ ] src/xrGame/mixed_delegate.h
* [ ] src/xrGame/MosquitoBald_script.cpp
* [ ] src/xrGame/particle_params_script.cpp
* [ ] src/xrGame/patrol_path_manager.cpp
* [ ] src/xrGame/patrol_path_params_script.cpp
* [ ] src/xrGame/PhraseDialog_script.cpp
* [ ] src/xrGame/PHSimpleCallsScript.cpp
* [ ] src/xrGame/PhysicObject_script.cpp
* [ ] src/xrGame/physics_element_scripted.cpp
* [ ] src/xrGame/physics_joint_scripted.cpp
* [ ] src/xrGame/physics_shell_scripted.cpp
* [ ] src/xrGame/physics_world_scripted.cpp
* [ ] src/xrGame/player_hud_script.cpp
* [ ] src/xrGame/profile_data_types_script.cpp
* [ ] src/xrGame/profile_store_script.cpp
* [ ] src/xrGame/property_evaluator_script.cpp
* [ ] src/xrGame/property_storage_script.cpp
* [ ] src/xrGame/relation_registry_fights.cpp
* [ ] src/xrGame/RGD5.cpp
* [ ] src/xrGame/saved_game_wrapper_script.cpp
* [ ] src/xrGame/Scope.cpp
* [ ] src/xrGame/script_action_condition_script.cpp
* [ ] src/xrGame/script_animation_action_script.cpp
* [ ] src/xrGame/script_attachment_script.cpp
* [ ] src/xrGame/script_binder_object_script.cpp
* [ ] src/xrGame/script_effector_script.cpp
* [ ] src/xrGame/script_entity_action_script.cpp
* [ ] src/xrGame/script_game_object3.cpp
* [ ] src/xrGame/script_game_object_script2.cpp
* [ ] src/xrGame/script_game_object_script3.cpp
* [ ] src/xrGame/script_game_object_script.cpp
* [ ] src/xrGame/script_game_object_script_trader.cpp
* [ ] src/xrGame/script_hit_script.cpp
* [ ] src/xrGame/script_lanim.cpp
* [ ] src/xrGame/script_light_script.cpp
* [ ] src/xrGame/script_monster_action_script.cpp
* [ ] src/xrGame/script_monster_hit_info_script.cpp
* [ ] src/xrGame/script_movement_action_script.cpp
* [ ] src/xrGame/script_object_action_script.cpp
* [ ] src/xrGame/script_particle_action_script.cpp
* [ ] src/xrGame/script_particles_script.cpp
* [ ] src/xrGame/script_render_device_script.cpp
* [ ] src/xrGame/script_sound_action_script.cpp
* [ ] src/xrGame/script_sound_info_script.cpp
* [ ] src/xrGame/script_sound_script.cpp
* [ ] src/xrGame/script_wallmarks_script.cpp
* [ ] src/xrGame/script_watch_action_script.cpp
* [ ] src/xrGame/script_world_property_script.cpp
* [ ] src/xrGame/script_world_state_script.cpp
* [ ] src/xrGame/ScriptXMLInit.cpp
* [ ] src/xrGame/script_zone_script.cpp
* [ ] src/xrGame/searchlight_script.cpp
* [ ] src/xrGame/smart_cover_default_behaviour_planner.cpp
* [ ] src/xrGame/smart_cover_evaluators.cpp
* [ ] src/xrGame/smart_cover_object_script.cpp
* [ ] src/xrGame/space_restriction_bridge.cpp
* [ ] src/xrGame/space_restrictor_script.cpp
* [ ] src/xrGame/StalkerOutfit.cpp
* [ ] src/xrGame/torch_script.cpp
* [ ] src/xrGame/trade_parameters_inline.h
* [ ] src/xrGame/ui_export_script.cpp
* [ ] src/xrGame/UIGameCustom_script.cpp
* [ ] src/xrGame/ui/UIActorMenu_script.cpp
* [ ] src/xrGame/ui/UIButton_script.cpp
* [ ] src/xrGame/ui/UIComboBox_script.cpp
* [ ] src/xrGame/ui/UIEditBox_script.cpp
* [ ] src/xrGame/ui/UIListBox_script.cpp
* [ ] src/xrGame/ui/UIMapInfo_script.cpp
* [ ] src/xrGame/ui/UIMessageBox_script.cpp
* [ ] src/xrGame/ui/UIOptionsManagerScript.cpp
* [ ] src/xrGame/ui/UIProgressBar_script.cpp
* [ ] src/xrGame/ui/UIPropertiesBox_script.cpp
* [x] src/xrGame/ui/uiscriptwnd_script2.cpp
* [x] src/xrGame/ui/UIScriptWnd_script.cpp
* [ ] src/xrGame/ui/UIStatic_script.cpp
* [ ] src/xrGame/ui/UITabControl_script.cpp
* [ ] src/xrGame/ui/UIWindow_script.cpp
* [x] src/xrGame/WeaponAK74.cpp
* [x] src/xrGame/WeaponAmmo_script.cpp
* [x] src/xrGame/WeaponBinoculars_script.cpp
* [x] src/xrGame/weaponBM16_script.cpp
* [x] src/xrGame/WeaponFN2000.cpp
* [x] src/xrGame/WeaponFORT.cpp
* [x] src/xrGame/WeaponGroza.cpp
* [x] src/xrGame/WeaponHPSA_script.cpp
* [x] src/xrGame/WeaponKnife_script.cpp
* [x] src/xrGame/WeaponLR300.cpp
* [x] src/xrGame/WeaponPM.cpp
* [x] src/xrGame/WeaponRG6_script.cpp
* [x] src/xrGame/WeaponRPG7_script.cpp
* [x] src/xrGame/weaponshotgun_script.cpp
* [x] src/xrGame/WeaponSSRS_script.cpp
* [x] src/xrGame/WeaponStatMgunIR.cpp
* [x] src/xrGame/WeaponSVD.cpp
* [x] src/xrGame/WeaponSVU.cpp
* [x] src/xrGame/WeaponUSP45.cpp
* [x] src/xrGame/WeaponVal.cpp
* [x] src/xrGame/WeaponVintorez.cpp
* [x] src/xrGame/WeaponWalther.cpp
* [x] src/xrServerEntities/object_factory_script.cpp
* [x] src/xrServerEntities/script_engine_script.cpp
* [x] src/xrServerEntities/script_fcolor_script.cpp
* [x] src/xrServerEntities/script_flags_script.cpp
* [x] src/xrServerEntities/script_fmatrix_script.cpp
* [x] src/xrServerEntities/script_fvector_script.cpp
* [x] src/xrServerEntities/script_ini_file_script.cpp
* [x] src/xrServerEntities/script_net_packet_script.cpp
* [x] src/xrServerEntities/script_reader_script.cpp
* [x] src/xrServerEntities/script_rtoken_list_script.cpp
* [x] src/xrServerEntities/script_token_list_script.cpp
* [x] src/xrServerEntities/xrServer_Objects_ALife_Items_script.cpp
* [x] src/xrServerEntities/xrServer_Objects_ALife_Items_script2.cpp
* [x] src/xrServerEntities/xrServer_Objects_ALife_Items_script3.cpp
* [x] src/xrServerEntities/xrserver_objects_alife_monsters_script3.cpp
* [x] src/xrServerEntities/xrServer_Objects_ALife_Monsters_script4.cpp
* [x] src/xrServerEntities/xrServer_Objects_ALife_Monsters_script2.cpp
* [x] src/xrServerEntities/xrServer_Objects_ALife_Monsters_script.cpp
* [x] src/xrServerEntities/xrServer_Objects_ALife_script2.cpp
* [x] src/xrServerEntities/xrServer_Objects_ALife_script3.cpp
* [x] src/xrServerEntities/xrServer_Objects_ALife_script.cpp
* [x] src/xrServerEntities/xrServer_Objects_Alife_Smartcovers_script.cpp
* [x] src/xrServerEntities/xrServer_Objects_script2.cpp
* [x] src/xrServerEntities/xrServer_Objects_script.cpp

Command used to gen file list: `grep -lR '\.def' | sort -u`

Yes ... I may have missed some of them.
