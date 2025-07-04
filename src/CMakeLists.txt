configure_file(config.h.in config.h @ONLY)

add_library(common STATIC
    core/Application.cpp core/Application.h
    settings/FileSettings.cpp settings/FileSettings.h settings/Settings.cpp settings/Settings.h
    ui/MainWindow.cpp ui/MainWindow.h
    ui/dialog/NewWorld.h ui/dialog/NewWorld.cpp
    ui/dialog/StandardDialog.cpp ui/dialog/StandardDialog.h
    ui/widget/BrowseLayout.cpp ui/widget/BrowseLayout.h
    world/World.h world/World.cpp
    ui/WorldController.h ui/WorldController.cpp
    ui/widget/AutomaticSlider.h ui/widget/AutomaticSlider.cpp
    ui/RecentWorldsMenu.cpp ui/RecentWorldsMenu.h
    core/Utils.h core/Utils.cpp
    ui/dialog/Preferences.h ui/dialog/Preferences.cpp
)

# For visibility in IDE (e.g., Qt Creator)
add_custom_target(custom
    SOURCES
    config.h.in
)

target_link_libraries(common PUBLIC Qt6::Widgets )
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
