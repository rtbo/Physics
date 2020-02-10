
function(svg_to_png Svg PngPath Result)
    if(NOT INKSCAPE)
        message(FATAL_ERROR "INKSCAPE is not specified!")
    endif()

    get_filename_component(Basename "${Svg}" NAME_WE)

    set(Png "${PngPath}/${Basename}.png")

    # Rasterize svg --> png
    add_custom_command(
        OUTPUT "${Png}"
        COMMAND "${INKSCAPE}" -z --export-png="${Png}" "${Svg}"
        DEPENDS "${Svg}"
    )

    set(${Result} ${${Result}} "${Png}" PARENT_SCOPE)

Endfunction()