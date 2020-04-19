// -*- mode: c++; coding: utf-8 -*-

// Linthesia

// Copyright (c) 2007 Nicholas Piegdon
// Adaptation to GNU/Linux by Oscar Aceña
// See COPYING for license information

#ifndef __SHARED_STATE_H
#define __SHARED_STATE_H

#include <string>
#include <vector>

#include "TrackProperties.h"
#include "MidiComm.h"
#include "libmidi/Midi.h"
#include "DpmsThread.h"

struct SongStatistics {

  SongStatistics() :
    total_note_count(0),
    notes_user_could_have_played(0),
    speed_integral(0),
    notes_user_actually_played(0),
    stray_notes(0),
    total_notes_user_pressed(0),
    longest_combo(0),
    score(0) {
  }

  int total_note_count;

  int notes_user_could_have_played;
  long speed_integral;

  int notes_user_actually_played;

  int stray_notes;
  int total_notes_user_pressed;

  int longest_combo;
  double score;

};

// This many microseconds of the song will be shown on the screen at once
class ShowDuration {
public:
  ShowDuration() :
    duration(DefaultShowDurationMicroseconds)
    {}

  void increase() {
    duration += StepShowDurationMicroseconds;
    duration = std::min(duration, MaxShowDurationMicroseconds);
  }

  void decrease() {
    duration -= StepShowDurationMicroseconds;
    duration = std::max(duration, MinShowDurationMicroseconds);
  }

  operator microseconds_t() const {
    return duration;
  }

private:
  static const microseconds_t DefaultShowDurationMicroseconds = 3250000;
  static const microseconds_t StepShowDurationMicroseconds = 250000;
  static const microseconds_t MinShowDurationMicroseconds = 250000;
  static const microseconds_t MaxShowDurationMicroseconds = 10000000;
  
  microseconds_t duration;
};

struct SharedState {

  SharedState() :
    midi(0),
    midi_out(0),
    midi_in(0),
    dpms_thread(0),
    song_speed(100),
    base_volume(1)
    {}

  Midi *midi;
  MidiCommOut *midi_out;
  MidiCommIn *midi_in;
  DpmsThread *dpms_thread;

  SongStatistics stats;

  int song_speed;
  double base_volume;
  ShowDuration show_duration;

  std::vector<Track::Properties> track_properties;
  std::string song_title;
};

#endif // __SHARED_STATE_H
