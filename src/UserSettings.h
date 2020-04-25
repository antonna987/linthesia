#pragma once

#include "UserSettingsIO.h"

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

template<typename IO>
struct UserSettingImpl {
    DEFINE_SETTING(song_lib_path, MUSICDIR);
    DEFINE_SETTING(song_lib_last_dir, MUSICDIR);
    DEFINE_SETTING(last_file, "");
    DEFINE_SETTING(default_music_directory, "");
    DEFINE_SETTING(font_desc, "");
    DEFINE_SETTING(last_output_device, "");
    DEFINE_SETTING(last_input_device, "");
    DEFINE_SETTING(min_key, "");
    DEFINE_SETTING(max_key, "");
    DEFINE_SETTING(refresh_rate, "");
};

using UserSetting = UserSettingImpl<UserSettingsIO>;

#undef DEFINE_SETTING
#undef DEFINE_SETTER
#undef DEFINE_GETTER
