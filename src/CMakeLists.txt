configure_file(config.h.in config.h @ONLY)

add_library(common STATIC
    core/Application.cpp core/Application.h
    ui/MainWindow.cpp ui/MainWindow.h
    world/World.h world/World.cpp
    ui/dialog/StandardDialog.cpp ui/dialog/StandardDialog.h
    ui/dialog/NewWorld.h ui/dialog/NewWorld.cpp
    ui/widget/BrowseLayout.cpp ui/widget/BrowseLayout.h
)

# For visibility in IDE (e.g., Qt Creator)
add_custom_target(custom
    SOURCES
    config.h.in
)

target_link_libraries(common PUBLIC Qt6::Widgets )
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
