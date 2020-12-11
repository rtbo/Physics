
function(_si_units_codegen_dim_file OutputPattern Dim Result)
    string(REPLACE @Dim@ ${Dim} OutputPattern "${OutputPattern}")
    file(TO_CMAKE_PATH "${OutputPattern}" OutputPattern)
    set(${Result} "${OutputPattern}" PARENT_SCOPE)
endfunction()

function(si_units_dims_codegen Template Output)
    set(Script "${SI_Units_SOURCE_DIR}/Dimensions.py")
    set(Data "${SI_Units_SOURCE_DIR}/Dimensions.json")

    if(NOT IS_ABSOLUTE "${Template}")
        set(Template "${CMAKE_CURRENT_SOURCE_DIR}/${Template}")
    endif()
    if(NOT EXISTS "${Template}")
        message(FATAL_ERROR "File ${Template} does not exist but is required by si_units_dims_codegen")
    endif()

    add_custom_command(
        OUTPUT "${Output}"
        COMMAND "${Python3_EXECUTABLE}" "${Script}" --input "${Template}" --output "${Output}"
                --dims "${SI_UNITS_DIMS}"
        DEPENDS "${Template}" "${Script}" "${Data}" "${ARGV2}"
    )
endfunction()

function(si_units_dim_codegen Template OutputPattern Result)
    set(Script "${SI_Units_SOURCE_DIR}/Dimensions.py")
    set(Data "${SI_Units_SOURCE_DIR}/Dimensions.json")

    if(NOT IS_ABSOLUTE "${Template}")
        set(Template "${CMAKE_CURRENT_SOURCE_DIR}/${Template}")
    endif()
    if(NOT EXISTS "${Template}")
        message(FATAL_ERROR "File ${Template} does not exist but is required by si_units_dim_codegen")
    endif()

    set(OutputList)
    foreach(Dim ${SI_UNITS_DIM_LIST})
        _si_units_codegen_dim_file("${OutputPattern}" ${Dim} Output)
        add_custom_command(
            OUTPUT "${Output}"
            COMMAND "${Python3_EXECUTABLE}" "${Script}" --dim ${Dim} --input "${Template}" --output "${Output}"
            WORKING_DIRECTORY "${SI_Units_SOURCE_DIR}"
            DEPENDS "${Template}" "${Script}" "${Data}" "${ARGV3}"
        )
        list(APPEND OutputList "${Output}")
    endforeach()
    set(${Result} ${${Result}} ${OutputList} PARENT_SCOPE)
endfunction()