// -*- mode: c++; coding: utf-8 -*-

// Linthesia

// Copyright (c) 2007 Nicholas Piegdon
// Adaptation to GNU/Linux by Oscar Aceña
// See COPYING for license information

#ifndef __GAMESTATE_H
#define __GAMESTATE_H

#include <exception>
#include <string>
#include <unordered_set>
#include <map>

#include "Textures.h"
#include "CompatibleSystem.h"
#include "FrameCounter.h"
#include "Renderer.h"

class GameStateError : public std::exception {
public:

  GameStateError(const std::string &error) throw() :
    m_error(error) {
  }

  virtual const char *what() const throw() {
    return m_error.c_str();
  }

  ~GameStateError() throw() {
  }

private:

  const std::string m_error;

  GameStateError operator=(const GameStateError&);
};

class GameStateManager;

enum MouseButton {

  MouseLeft,
  MouseRight
};

struct MouseButtons {

  MouseButtons() :
    left(false), right(false) {
  }

  bool left;
  bool right;
};

struct MouseInfo {

  MouseInfo() :
    x(0), y(0) {
  }

  int x;
  int y;

  MouseButtons held;
  MouseButtons newPress;
  MouseButtons released;
};

class GameState {
public:

  // Don't initialize anything that is dependent
  // on the protected functions (GetStateWidth,
  // GetStateMilliseconds, etc) here.  Wait until
  // Init() to do that.
  GameState() :
    m_manager(0),
    m_state_milliseconds(0),
    m_last_delta_milliseconds(0) {
  }

  virtual ~GameState() {
  }

protected:

  // This is called just after the state's manager
  // is set for the first time
  virtual void Init() = 0;

  // Called every frame
  virtual void Update() = 0;

  // Call when state dimesnsions changed
  virtual void Resize() = 0;

  // Called each frame.  Drawing bounds are [0,
  // GetStateWidth()) and [0, GetStateHeight())
  virtual void Draw(Renderer &renderer) const = 0;

  // How long has this state been running
  unsigned long GetStateMilliseconds() const {
    return m_state_milliseconds;
  }

  // How much time elapsed since the last update
  unsigned long GetDeltaMilliseconds() const {
    return m_last_delta_milliseconds;
  }

  int GetStateWidth() const;
  int GetStateHeight() const;

  // Once finished executing, use this to change
  // state to something new.  This can only be
  // called from inside Update().  After calling
  // this function, you're guaranteed that the only
  // function that will still be called (before
  // the destructor) is Draw().  You *must* be able
  // to continue supporting Draw() after you call
  // this function.
  //
  // new_state *must* be dynamically allocated and
  // by calling this function you hand off ownership
  // of the memory to the state handling subsystem.
  void ChangeState(GameState *new_state);

  Tga *GetTexture(Texture tex_name, bool smooth = false) const;

  // These are usable inside Update()
  bool IsKeyPressed(const std::string& key_name) const;
  const MouseInfo &Mouse() const;

private:

  void SetManager(GameStateManager *manager);
  GameStateManager *m_manager;

  void UpdateStateMicroseconds(unsigned long delta_ms) {
    m_state_milliseconds += delta_ms;
    m_last_delta_milliseconds = delta_ms;
  }

  unsigned long m_state_milliseconds;
  unsigned long m_last_delta_milliseconds;

  friend class GameStateManager;
};

// Your app calls this from the top level
class GameStateManager {
public:

  GameStateManager(int screen_width, int screen_height) :
    m_next_state(0),
    m_current_state(0),
    m_last_milliseconds(Compatible::GetMilliseconds()),
    m_inside_update(false),
    m_fps(500.0),
    m_show_fps(false),
    m_screen_x(screen_width),
    m_screen_y(screen_height) {
  }

  ~GameStateManager();

  // first_state must be dynamically allocated.
  // GameStateManager takes ownership of the memory
  // from this point forward.
  void SetInitialState(GameState *first_state);

  bool KeyPress(const std::string& key_name);
  bool IsKeyPressed(const std::string& key_name) const;
  bool IsKeyReleased(const std::string& key_name) const;

  void MousePress(MouseButton button);
  void MouseRelease(MouseButton button);
  void MouseMove(int x, int y);
  const MouseInfo &Mouse() const { return m_mouse; }

  void Update(bool skip_this_update);
  void Draw(Renderer &renderer);

  void ChangeState(GameState *new_state);

  Tga *GetTexture(Texture tex_name, bool smooth) const;

  int GetStateWidth() const { return m_screen_x; }
  int GetStateHeight() const { return m_screen_y; }

  void SetStateDimensions(int w, int h);

private:
  GameState *m_next_state;
  GameState *m_current_state;

  unsigned long m_last_milliseconds;
  std::unordered_set<std::string> m_keys_pressed;
  std::unordered_set<std::string> m_last_keys_pressed;

  bool m_inside_update;

  MouseInfo m_mouse;

  FrameCounter m_fps;
  bool m_show_fps;

  int m_screen_x;
  int m_screen_y;

  mutable std::map<Texture, Tga*> m_textures;
};

#endif // __GAMESTATE_H

