#pragma once

#include "UserSettingsIO.h"
#include <sstream>
#include <unordered_set>

#ifndef MUSICDIR
#define MUSICDIR "../music/"
#endif

template <typename T>
inline std::string to_string(const T& t) {
    return t;
}

template <>
inline std::string to_string<int>(const int& t) {
    return std::to_string(t);
}

template <typename T>
inline T from_string(const std::string& str) {
    return str;
}

template <>
inline int from_string<int>(const std::string& str) {
    return std::stoi(str);
}

#define DEFINE_GETTER(SETTING_NAME, TYPE, DEFAULT_VALUE)                                    \
    static TYPE SETTING_NAME() {                                                            \
        std::string value_str = IO::Get((#SETTING_NAME), to_string<TYPE>(DEFAULT_VALUE));   \
        return from_string<TYPE>(value_str);                                                \
    }

#define DEFINE_SETTER(SETTING_NAME, TYPE)                                                   \
    static void set_##SETTING_NAME(const TYPE& value) {                                     \
        IO::Set((#SETTING_NAME), to_string<TYPE>(value));                                   \
    }

#define DEFINE_SETTING(SETTING_NAME, TYPE, DEFAULT_VALUE)                                   \
    DEFINE_GETTER(SETTING_NAME, TYPE, DEFAULT_VALUE);                                       \
    DEFINE_SETTER(SETTING_NAME, TYPE);

#define DEFINE_KEY(KEY_NAME, DEFAULT_KEY)                                                   \
    DEFINE_GETTER(KEY_NAME, std::string, DEFAULT_KEY);

template<typename IO>
struct UserSettingImpl {
    DEFINE_SETTING(song_lib_path, std::string, MUSICDIR);
    DEFINE_SETTING(song_lib_last_dir, std::string, MUSICDIR);
    DEFINE_SETTING(last_file, std::string, "");
    DEFINE_SETTING(default_music_directory, std::string, "");
    DEFINE_SETTING(font_desc, std::string, "");
    DEFINE_SETTING(last_output_device, std::string, "");
    DEFINE_SETTING(last_input_device, std::string, "");
    DEFINE_SETTING(min_key, int, 0);
    DEFINE_SETTING(max_key, int, 120);
    DEFINE_SETTING(refresh_rate, int, 30);
    DEFINE_SETTING(lead_in, int, 5500000);
    DEFINE_SETTING(lead_out, int, 1000000);
    DEFINE_SETTING(rewind_step, int, 5000000);
    DEFINE_SETTING(show_duration, int, 3250000);
    DEFINE_SETTING(show_duration_step, int, 250000);
    DEFINE_SETTING(show_duration_min, int, 250000);
    DEFINE_SETTING(show_duration_max, int, 10000000);

    DEFINE_KEY(key_show_fps, "F6");
    DEFINE_KEY(key_quit, "Escape");
    DEFINE_KEY(key_continue, "Return");
    DEFINE_KEY(key_pause, "space");
    DEFINE_KEY(key_loop, "F5");
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
            keys.insert(key_loop());
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
