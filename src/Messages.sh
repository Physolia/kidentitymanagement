#! /bin/sh
# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: none
$XGETTEXT `find -name *.cpp -o -name *.h -name \*.qml` -o $podir/libkpimidentities5.pot
