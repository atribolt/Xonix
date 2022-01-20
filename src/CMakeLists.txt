set (ENGINES
  Engines/Engine.h
  Engines/DrawEngine.h
  Engines/EventEngine.h
  Engines/ObjectFactory.h
  Engines/AnimationEngine.h

  Engines/Engine.cpp
  Engines/DrawEngine.cpp
  Engines/EventEngine.cpp
  Engines/ObjectFactory.cpp
  Engines/AnimationEngine.cpp
)

set (LOGGING
  Logging/Log.h
  Logging/Log.cpp
  Logging/Logger.h
  Logging/Logger.cpp
)

set (GAMEOBJECTS
  GameObjects/Map.h
  GameObjects/Block.h
  GameObjects/Entity.h
  GameObjects/Player.h
  GameObjects/Animation.h
  GameObjects/GameObject.h

  GameObjects/Map.cpp
  GameObjects/GameObject.cpp
)

set (EVENTHANDLERS
  EventHandlers/ExitGame.h
  EventHandlers/EventHandler.h
  EventHandlers/PlayerController.h

  EventHandlers/ExitGame.cpp
  EventHandlers/PlayerController.cpp
)

set (SRC
  Game.h
  Window.h
  Classes.h
  GameSettings.h

  Game.cpp
  GameSettings.cpp
  Window.cpp
  main.cpp
)

list(APPEND SRC_FILES
  ${ENGINES}
  ${LOGGING}
  ${SRC}
  ${GAMEOBJECTS}
  ${EVENTHANDLERS}
)

message(STATUS ${SRC_FILES})

source_group("Engines" FILES ${ENGINES})
source_group("Logging" FILES ${LOGGING})
source_group("Game Objects" FILES ${GAMEOBJECTS})
source_group("Event Handlers" FILES ${EVENTHANDLERS})
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
