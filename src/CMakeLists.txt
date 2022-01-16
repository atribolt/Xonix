set(SRCDIR ${PROJECT_SOURCE_DIR}/src)
set(INCDIR ${PROJECT_SOURCE_DIR}/include)

message(STATUS ${SRCDIR})
message(STATUS ${INCDIR})

set (SRC
  ${SRCDIR}/main.cpp
)

add_executable(${PROJECT_NAME}
  ${SRC}
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE sfml-system sfml-window sfml-main sfml-graphics
)

target_include_directories(${PROJECT_NAME}
  PRIVATE ${PROJECT_SOURCE_DIR}/external/SFML/include
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED yes
)
