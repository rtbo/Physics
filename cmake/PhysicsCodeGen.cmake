
# capitalize first letter of Input (item ==> Item)
function(_physics_codegen_capitalize Input Result)
    string(SUBSTRING ${Input} 0 1 FirstLetter)
    string(TOUPPER ${FirstLetter} FirstLetter)
    string(REGEX REPLACE "^.(.*)" "${FirstLetter}\\1" CapInput "${Input}")
    set(${Result} ${CapInput} PARENT_SCOPE)
endfunction()

function(_physics_codegen_item_file OutputPattern Item Result)
    _physics_codegen_capitalize(${Item} CapItem)

    string(REPLACE @Item@ ${CapItem} OutputPattern "${OutputPattern}")
    string(REPLACE @item@ ${Item} OutputPattern "${OutputPattern}")

    file(TO_CMAKE_PATH "${OutputPattern}" OutputPattern)

    set(${Result} "${OutputPattern}" PARENT_SCOPE)
endfunction()

function(_physics_codegen_dim_file OutputPattern Dim Result)
    string(REPLACE @Dim@ ${Dim} OutputPattern "${OutputPattern}")
    file(TO_CMAKE_PATH "${OutputPattern}" OutputPattern)
    set(${Result} "${OutputPattern}" PARENT_SCOPE)
endfunction()

function(physics_glob_codegen Template Output)
    set(Script "${Physics_SOURCE_DIR}/PhysicsCodeGen.py")
    set(Data "${Physics_SOURCE_DIR}/PhysicsData.json")

    if(NOT IS_ABSOLUTE "${Template}")
        set(Template "${CMAKE_CURRENT_SOURCE_DIR}/${Template}")
    endif()
    if(NOT EXISTS "${Template}")
        message(FATAL_ERROR "File ${Template} does not exist but is required by physics_glob_codegen")
    endif()

    add_custom_command(
        OUTPUT "${Output}"
        COMMAND "${Python_EXECUTABLE}" "${Script}" --datafile "${Data}"
                --mode glob --input "${Template}" --output "${Output}"
        DEPENDS "${Template}" "${Script}" "${Data}"
    )
endfunction()

function(physics_item_codegen Template OutputPattern Result)
    set(Script "${Physics_SOURCE_DIR}/PhysicsCodeGen.py")
    set(Data "${Physics_SOURCE_DIR}/PhysicsData.json")

    if(NOT IS_ABSOLUTE "${Template}")
        set(Template "${CMAKE_CURRENT_SOURCE_DIR}/${Template}")
    endif()
    if(NOT EXISTS "${Template}")
        message(FATAL_ERROR "File ${Template} does not exist but is required by physics_item_codegen")
    endif()

    set(OutputList)
    foreach(Item ${PHYSICS_ITEMS})
        _physics_codegen_item_file("${OutputPattern}" ${Item} Output)
        add_custom_command(
            OUTPUT "${Output}"
            COMMAND "${Python_EXECUTABLE}" "${Script}" --datafile "${Data}"
                    --mode item --item ${Item} --input "${Template}" --output "${Output}"
            WORKING_DIRECTORY "${Physics_SOURCE_DIR}"
            DEPENDS "${Template}" "${Script}" "${Data}"
        )
        list(APPEND OutputList "${Output}")
    endforeach()
    set(${Result} ${${Result}} ${OutputList} PARENT_SCOPE)
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
    foreach(Dim ${PHYSICS_DIMS})
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