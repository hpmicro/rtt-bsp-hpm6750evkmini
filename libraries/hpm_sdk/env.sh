#
# Copyright (c) 2021 hpmicro
#
# SPDX-License-Identifier: BSD-3-Clause
#

if [ "X$name" "==" "Xenv.sh" ]; then
    echo "Please source this file, rather than executing it."
    exit
fi

script=$(cd -P -- "$(dirname -- "$0")" && printf '%s\n' "$(pwd -P)/$(basename -- "$0")")
export HPM_SDK_BASE=$(dirname "$script")

export OPENOCD_SCRIPTS=${HPM_SDK_BASE}/boards/openocd

