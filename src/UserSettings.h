#pragma once

#include "UserSettingsIO.h"

template<typename IO>
struct UserSettingImpl {
    static std::string Get(const std::string& setting, const std::string& default_value) {
        return IO::Get(setting, default_value);
    }

    static void Set(const std::string& setting, const std::string& value) {
        return IO::Set(setting, value);
    }
};

using UserSetting = UserSettingImpl<UserSettingsIO>;
