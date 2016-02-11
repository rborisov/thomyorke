/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * libstreamripper.h
 * Copyright (C) 2013 Hans Oesterholt <debian@oesterholt.net>
 * 
 * libstreamripper is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * libstreamripper is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __LIBSTREAMRIPPER_H__
#define __LIBSTREAMRIPPER_H__

#ifdef __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__
  #define __UNIX__ 1
#else
 #ifdef __linux
   #define __UNIX__ 1
 #endif
#endif


#include <sr/compat.h>
#include <sr/srtypes.h>
#include <sr/prefs.h>
#include <sr/errors.h>
#include <sr/rip_manager.h>

void sr_debug_enable(void);

#endif
