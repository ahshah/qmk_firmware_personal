#!/bin/bash
#qmk json2c ~/Downloads/joleen_rebound.json > /Users/hyshah/qmk_firmware_rebound/keyboards/montsinger/rebound/rev4/keymaps/ahshah/keymap.c
make montsinger/rebound/rev4:ahshah
make montsinger/rebound/rev4:ahshah:dfu
