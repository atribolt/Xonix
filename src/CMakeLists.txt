set(SRCDIR ${PROJECT_SOURCE_DIR}/src)
set(INCDIR ${PROJECT_SOURCE_DIR}/include)

message(STATUS ${SRCDIR})
message(STATUS ${INCDIR})

set (SRC
  ${INCDIR}/Log.h
  ${SRCDIR}/Log.cpp
  ${INCDIR}/Logger.h
  ${SRCDIR}/Logger.cpp

  ${SRCDIR}/main.cpp
)
source_group("" FILES ${SRC})

add_executable(${PROJECT_NAME}
  ${SRC}
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE sfml-system sfml-window sfml-graphics pthread
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PUBLIC ${PROJECT_SOURCE_DIR}/external/SFML/include
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED yes
)
