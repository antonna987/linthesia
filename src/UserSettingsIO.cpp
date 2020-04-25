// -*- mode: c++; coding: utf-8 -*-

// Linthesia

// Copyright (c) 2007 Nicholas Piegdon
// Adaptation to GNU/Linux by Oscar Aceña
// See COPYING for license information

#include "UserSettingsIO.h"

std::string UserSettingsIO::Get(const std::string& setting, const std::string& default_value) {
  auto& instance = Instance();
  std::string result = instance.m_gconf->get_string(instance.m_app_name + "/" + setting);
  if (result.empty()) {
    Set(setting, default_value);
    return default_value;
  }
  return result;
}

void UserSettingsIO::Set(const std::string& setting, const std::string& value) {
  auto& instance = Instance();
  instance.m_gconf->set(instance.m_app_name + "/" + setting, value);
}

UserSettingsIO::UserSettingsIO(const std::string& app_name) {
  Gnome::Conf::init();
  m_gconf = Gnome::Conf::Client::get_default_client();
  m_app_name = "/apps/" + app_name;
}

UserSettingsIO& UserSettingsIO::Instance() {
  static UserSettingsIO user_settings_io("Linthesia");
  return user_settings_io;
}
