configure_file(config.h.in config.h @ONLY)

add_library(common STATIC
    core/Application.cpp core/Application.h
    settings/FileSettings.cpp settings/FileSettings.h settings/Settings.cpp settings/Settings.h
    ui/MainWindow.cpp ui/MainWindow.h
    ui/dialog/NewWorld.h ui/dialog/NewWorld.cpp
    ui/dialog/StandardDialog.cpp ui/dialog/StandardDialog.h
    ui/widget/BrowseLayout.cpp ui/widget/BrowseLayout.h
    world/World.h world/World.cpp
    ui/Dashboard.h ui/Dashboard.cpp
    ui/widget/AutoSlider.h ui/widget/AutoSlider.cpp
    ui/RecentFilesMenu.cpp ui/RecentFilesMenu.h
    core/Utils.h core/Utils.cpp
    ui/dialog/Preferences.h ui/dialog/Preferences.cpp
    database/Database.cpp database/Database.h
    database/Migrater.cpp database/Migrater.h
    database/DatabaseException.cpp database/DatabaseException.h
    core/Exception.cpp core/Exception.h
)

# For visibility in IDE (e.g., Qt Creator)
add_custom_target(custom
    SOURCES
    config.h.in
)

target_link_libraries(common PUBLIC Qt6::Widgets Qt6::Sql)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
