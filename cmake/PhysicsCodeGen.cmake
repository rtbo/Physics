
function(_physics_codegen_dim_file OutputPattern Dim Result)
    string(REPLACE @Dim@ ${Dim} OutputPattern "${OutputPattern}")
    file(TO_CMAKE_PATH "${OutputPattern}" OutputPattern)
    set(${Result} "${OutputPattern}" PARENT_SCOPE)
endfunction()

function(physics_dims_codegen Template Output)
    set(Script "${Physics_SOURCE_DIR}/Dimensions.py")
    set(Data "${Physics_SOURCE_DIR}/Dimensions.json")

    if(NOT IS_ABSOLUTE "${Template}")
        set(Template "${CMAKE_CURRENT_SOURCE_DIR}/${Template}")
    endif()
    if(NOT EXISTS "${Template}")
        message(FATAL_ERROR "File ${Template} does not exist but is required by physics_dims_codegen")
    endif()

    add_custom_command(
        OUTPUT "${Output}"
        COMMAND "${Python_EXECUTABLE}" "${Script}" --input "${Template}" --output "${Output}"
                --dims "${PHYSICS_DIMS}"
        DEPENDS "${Template}" "${Script}" "${Data}"
    )
endfunction()

function(physics_dim_codegen Template OutputPattern Result)
    set(Script "${Physics_SOURCE_DIR}/Dimensions.py")
    set(Data "${Physics_SOURCE_DIR}/Dimensions.json")

    if(NOT IS_ABSOLUTE "${Template}")
        set(Template "${CMAKE_CURRENT_SOURCE_DIR}/${Template}")
    endif()
    if(NOT EXISTS "${Template}")
        message(FATAL_ERROR "File ${Template} does not exist but is required by physics_dim_codegen")
    endif()

    set(OutputList)
    foreach(Dim ${PHYSICS_DIM_LIST})
        _physics_codegen_dim_file("${OutputPattern}" ${Dim} Output)
        add_custom_command(
            OUTPUT "${Output}"
            COMMAND "${Python_EXECUTABLE}" "${Script}" --dim ${Dim} --input "${Template}" --output "${Output}"
            WORKING_DIRECTORY "${Physics_SOURCE_DIR}"
            DEPENDS "${Template}" "${Script}" "${Data}"
        )
        list(APPEND OutputList "${Output}")
    endforeach()
    set(${Result} ${${Result}} ${OutputList} PARENT_SCOPE)
endfunction()