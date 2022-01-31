set (LOGGING
  Logging/Log.h
  Logging/Log.cpp
  Logging/Logger.h
  Logging/Logger.cpp
)

set (INTERFACE
  Interface/GameState.h
  Interface/GameState.cpp
)

set (GAMESTATES
  GameStates/MenuState.h
  GameStates/InPlayState.h
  GameStates/GameOverState.h
)

set (SRC
  Game.h
  GameEvent.h
  GameSettings.h

  Game.cpp
  GameSettings.cpp
  main.cpp
)

list(APPEND SRC_FILES
  ${LOGGING}
  ${SRC}
  ${INTERFACE}
  ${GAMESTATES}
)

message(STATUS ${SRC_FILES})

source_group("Logging" FILES ${LOGGING})
source_group("Interface" FILES ${INTERFACE})
source_group("Game States" FILES ${GAMESTATES})
source_group("src" FILES ${SRC})

add_executable(${PROJECT_NAME} ${SRC_FILES})


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
