
add_executable(WidgetApp
    main.cpp
    widget.h
    widget.ui
    widget.cpp
)
set_property(TARGET WidgetApp PROPERTY AUTOMOC ON)
set_property(TARGET WidgetApp PROPERTY AUTOUIC ON)

target_link_libraries(WidgetApp Physics::Widgets)
