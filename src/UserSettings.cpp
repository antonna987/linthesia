// -*- mode: c++; coding: utf-8 -*-

// Linthesia

// Copyright (c) 2007 Nicholas Piegdon
// Adaptation to GNU/Linux by Oscar Aceña
// See COPYING for license information

#include "UserSettings.h"

std::string UserSetting::Get(const std::string& setting, const std::string& default_value) {
  auto& instance = Instance();
  std::string result = instance.m_gconf->get_string(instance.m_app_name + "/" + setting);
  if (result.empty()) {
    return default_value;
  }
  return result;
}

void UserSetting::Set(const std::string& setting, const std::string& value) {
  auto& instance = Instance();
  instance.m_gconf->set(instance.m_app_name + "/" + setting, value);
}

UserSetting::UserSetting(const std::string& app_name) {
  Gnome::Conf::init();
  m_gconf = Gnome::Conf::Client::get_default_client();
  m_app_name = "/apps/" + app_name;
}

UserSetting& UserSetting::Instance() {
  static UserSetting user_setting("Linthesia");
  return user_setting;
}
