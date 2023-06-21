/*
Copyright 2019 Ryan Caltabiano <https://github.com/XScorpion2>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <stdint.h>
#include <stdbool.h>

#if !defined(I2C_USERSPACE_TIMEOUT)
#    define I2C_USERSPACE_TIMEOUT 100
#endif

// Initialize the i2c system  returns true if the system was initialized successfully
bool i2c_userspace_init(void);

// Send commands and data to screen
//bool i2c_userspace_send_data(const uint8_t *data, uint16_t size);
void i2c_userspace_driver_init(void);
void i2c_userspace_write(uint8_t* buf, uint8_t sz);

// Basically it's i2c_render, but with timeout management and i2c_task_user calling!
void i2c_userspace_kb_task_loop(void);

// Called at the start of i2c_task, weak function overridable by the user
bool i2c_userspace_task_kb(void);
bool i2c_userspace_task_user(void);
