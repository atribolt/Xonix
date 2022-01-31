#ifndef GAMEEVENT_H
#define GAMEEVENT_H

class GameState;
class MenuState;
class InPlayState;
class GameOverState;

class GameEvent {
public:
  enum Type {
    StartGame,
    PauseGame,
    ResumeGame,
    RestartGame,
    GameOver,
    GoToMenu,
    ExitGame
  };

  GameEvent() {}

  Type type;

  union {
    struct {
      int score {0};
    } results;
  };

  union {
    GameState* sender;
    MenuState* menuState;
    InPlayState* playState;
    GameOverState* gameOverState {nullptr};
  };
};

#endif // GAMEEVENT_H
