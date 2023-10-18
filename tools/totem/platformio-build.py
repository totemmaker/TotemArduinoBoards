# 
# Copyright 2023 Totem Technology, UAB
# 
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
# 

from os.path import join

from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()

FRAMEWORK_DIR = env.PioPlatform().get_package_dir("framework-arduinoespressif32")

env.Append(
    CPPPATH=[
        join(FRAMEWORK_DIR, "tools", "totem", "include")
    ],

    LIBPATH=[
        join(FRAMEWORK_DIR, "tools", "totem", "lib")
    ],

    LIBS=[
        "-lBLE", "-lRoboBoard", "-lBluetoothServices", "-l"+env.BoardConfig().get("build.variant")
    ],

    CPPDEFINES=[
        "TOTEMMAKER_PLATFORM",
        ("CORE_DEBUG_LEVEL", 1)
    ]
)
