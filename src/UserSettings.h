#pragma once

#include "UserSettingsIO.h"
#include <unordered_set>

#ifndef MUSICDIR
#define MUSICDIR "../music/"
#endif

#define DEFINE_GETTER(SETTING_NAME, DEFAULT_VALUE)              \
    static auto SETTING_NAME() {                                \
        return IO::Get((#SETTING_NAME), (DEFAULT_VALUE));       \
    }

#define DEFINE_SETTER(SETTING_NAME)                             \
    static void set_##SETTING_NAME(const std::string& value) {  \
        IO::Set((#SETTING_NAME), value);                        \
    }

#define DEFINE_SETTING(SETTING_NAME, DEFAULT_VALUE)             \
    DEFINE_GETTER(SETTING_NAME, DEFAULT_VALUE);                 \
    DEFINE_SETTER(SETTING_NAME);

#define DEFINE_KEY(KEY_NAME, DEFAULT_KEY)                       \
    DEFINE_GETTER(KEY_NAME, DEFAULT_KEY);

template<typename IO>
struct UserSettingImpl {
    DEFINE_SETTING(song_lib_path, MUSICDIR);
    DEFINE_SETTING(song_lib_last_dir, MUSICDIR);
    DEFINE_SETTING(last_file, "");
    DEFINE_SETTING(default_music_directory, "");
    DEFINE_SETTING(font_desc, "");
    DEFINE_SETTING(last_output_device, "");
    DEFINE_SETTING(last_input_device, "");
    DEFINE_SETTING(min_key, "0");
    DEFINE_SETTING(max_key, "120");
    DEFINE_SETTING(refresh_rate, "30");
    DEFINE_SETTING(lead_in, "5500000");
    DEFINE_SETTING(lead_out, "1000000");
    DEFINE_SETTING(rewind_step, "5000000");
    DEFINE_SETTING(show_duration, "3250000");
    DEFINE_SETTING(show_duration_step, "250000");
    DEFINE_SETTING(show_duration_min, "250000");
    DEFINE_SETTING(show_duration_max, "10000000");

    DEFINE_KEY(key_show_fps, "F6");
    DEFINE_KEY(key_quit, "Escape");
    DEFINE_KEY(key_continue, "Return");
    DEFINE_KEY(key_pause, "space");
    DEFINE_KEY(key_note_offset_inc, "greater");
    DEFINE_KEY(key_note_offset_dec, "less");
    DEFINE_KEY(key_show_duration_inc, "Down");
    DEFINE_KEY(key_show_duration_dec, "Up");
    DEFINE_KEY(key_song_speed_inc, "Right");
    DEFINE_KEY(key_song_speed_dec, "Left");
    DEFINE_KEY(key_base_volume_inc, "bracketright");
    DEFINE_KEY(key_base_volume_dec, "bracketlefts");
    DEFINE_KEY(key_rewind_fwd, "Page_Down");
    DEFINE_KEY(key_rewind_bwd, "Page_Up");
    DEFINE_KEY(key_down, "Down");
    DEFINE_KEY(key_up, "Up");
    DEFINE_KEY(key_left, "Left");
    DEFINE_KEY(key_right, "Right");

    static const auto& keys_all() {
        static std::unordered_set<std::string> keys;
        if (keys.empty()) {
            keys.insert(key_show_fps());
            keys.insert(key_quit());
            keys.insert(key_continue());
            keys.insert(key_pause());
            keys.insert(key_note_offset_inc());
            keys.insert(key_note_offset_dec());
            keys.insert(key_show_duration_inc());
            keys.insert(key_show_duration_dec());
            keys.insert(key_song_speed_inc());
            keys.insert(key_song_speed_dec());
            keys.insert(key_base_volume_inc());
            keys.insert(key_base_volume_dec());
            keys.insert(key_rewind_fwd());
            keys.insert(key_rewind_bwd());
            keys.insert(key_down());
            keys.insert(key_up());
            keys.insert(key_left());
            keys.insert(key_right());
        }
        return keys;
    }
};

using UserSetting = UserSettingImpl<UserSettingsIO>;

#undef DEFINE_KEY
#undef DEFINE_SETTING
#undef DEFINE_SETTER
#undef DEFINE_GETTER
