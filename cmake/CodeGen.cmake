function(code_gen_item_substitute INPUT_PATTERN resultVar)
    set(ITEM_LIST)
    #message(${PHYSICS_ITEMS})
    foreach (ITEM ${PHYSICS_ITEMS})
        code_gen_capitalize(${ITEM} CAP_ITEM)
        string(REGEX REPLACE "^(.*){Item}(.*)$" "\\1${CAP_ITEM}\\2" ITEM_RES ${INPUT_PATTERN})
        string(REGEX REPLACE "^(.*){item}(.*)$" "\\1${ITEM}\\2" ITEM_RES ${ITEM_RES})
        list(APPEND ITEM_LIST ${ITEM_RES})
    endforeach()
    set(${resultVar} ${ITEM_LIST} PARENT_SCOPE)
endfunction()

function(code_gen_capitalize INPUT resultVar)
    string(SUBSTRING ${INPUT} 0 1 FIRST_LETTER)
    string(TOUPPER ${FIRST_LETTER} FIRST_LETTER)
    string(REGEX REPLACE "^.(.*)" "${FIRST_LETTER}\\1" RESULT "${INPUT}")
    set(${resultVar} ${RESULT} PARENT_SCOPE)
endfunction()

function(code_gen_glob_file TEMPLATE_DIR TEMPLATE OUTPUT_DIR resultVar)
    string(REPLACE ".glob.j2" "" OUTPUT_FILE "${TEMPLATE}")
    string(REPLACE "${TEMPLATE_DIR}" "${OUTPUT_DIR}" OUTPUT_FILE "${OUTPUT_FILE}")
    file(TO_CMAKE_PATH ${OUTPUT_FILE} OUTPUT_FILE)
    set(${resultVar} ${OUTPUT_FILE} PARENT_SCOPE)
endfunction()

function(code_gen_item_file TEMPLATE_DIR TEMPLATE OUTPUT_DIR ITEM resultVar)
    code_gen_capitalize("${ITEM}" CAP_ITEM)
    string(REPLACE ".item.j2" "" OUTPUT_FILE "${TEMPLATE}")
    string(REPLACE "Item" "${CAP_ITEM}" OUTPUT_FILE "${OUTPUT_FILE}")
    string(REPLACE "item" "${ITEM}" OUTPUT_FILE "${OUTPUT_FILE}")
    string(REPLACE "${TEMPLATE_DIR}" "${OUTPUT_DIR}" OUTPUT_FILE "${OUTPUT_FILE}")
    file(TO_CMAKE_PATH ${OUTPUT_FILE} OUTPUT_FILE)
    set(${resultVar} ${OUTPUT_FILE} PARENT_SCOPE)
endfunction()


function(code_gen_glob TEMPLATE_DIR OUTPUT_DIR resultVar)
    file(TO_CMAKE_PATH "${TEMPLATE_DIR}" TEMPLATE_DIR)
    file(TO_CMAKE_PATH "${OUTPUT_DIR}" OUTPUT_DIR)

    file(GLOB_RECURSE TEMPLATES "${TEMPLATE_DIR}/*.glob.j2")

    set(GEN_LIST)
    foreach(TEMPLATE ${TEMPLATES})
        code_gen_glob_file("${TEMPLATE_DIR}" "${TEMPLATE}" "${OUTPUT_DIR}" OUTPUT_FILE)
        add_custom_command(
            OUTPUT "${OUTPUT_FILE}"
            COMMAND ${Python_EXECUTABLE} PhysicsCodeGen.py --mode glob --input "${TEMPLATE}" --output "${OUTPUT_FILE}"
            WORKING_DIRECTORY "${Physics_SOURCE_DIR}"
            DEPENDS "${TEMPLATE}"
            )
        list(APPEND GEN_LIST "${OUTPUT_FILE}")
    endforeach()
    set(${resultVar} ${GEN_LIST} PARENT_SCOPE)
endfunction()


function(code_gen_item TEMPLATE_DIR OUTPUT_DIR resultVar)
    file(TO_CMAKE_PATH "${TEMPLATE_DIR}" TEMPLATE_DIR)
    file(TO_CMAKE_PATH "${OUTPUT_DIR}" OUTPUT_DIR)

    file(GLOB_RECURSE TEMPLATES "${TEMPLATE_DIR}/*.item.j2")

    set(GEN_LIST)
    foreach(TEMPLATE ${TEMPLATES})
        foreach(ITEM ${PHYSICS_ITEMS})

            code_gen_item_file("${TEMPLATE_DIR}" "${TEMPLATE}" "${OUTPUT_DIR}" "${ITEM}" OUTPUT_FILE)
            add_custom_command(
                OUTPUT "${OUTPUT_FILE}"
                COMMAND ${Python_EXECUTABLE} PhysicsCodeGen.py --mode item --item "${ITEM}" --input "${TEMPLATE}" --output "${OUTPUT_FILE}"
                WORKING_DIRECTORY "${Physics_SOURCE_DIR}"
                DEPENDS "${TEMPLATE}" "${Physics_SOURCE_DIR}/PhysicsCodeGen.py" "${Physics_SOURCE_DIR}/PhysicsData.json"
                )
            list(APPEND GEN_LIST "${OUTPUT_FILE}")

        endforeach()
    endforeach()
    set(${resultVar} ${GEN_LIST} PARENT_SCOPE)
endfunction()
