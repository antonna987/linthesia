// -*- mode: c++; coding: utf-8 -*-

// Linthesia

// Copyright (c) 2007 Nicholas Piegdon
// Adaptation to GNU/Linux by Oscar Aceña
// See COPYING for license information

#pragma once

#include <gconfmm.h>
#include <string>

struct UserSettingsIO {
   static std::string Get(const std::string& setting, const std::string& default_value);
   static void Set(const std::string& setting, const std::string& value);

private:
   UserSettingsIO(const std::string& app_name);
   static UserSettingsIO& Instance();

   Glib::RefPtr<Gnome::Conf::Client> m_gconf;
   std::string m_app_name;
};
