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

#include "i2c_master.h"
#include "i2c_userspace.h"
#include "timer.h"
#include "print.h"
#include <string.h>
#include "wait.h"

uint8_t         i2c_buffer[64];
uint8_t         i2c_buffer_sz;
bool            i2c_userspace_initialized    = false;

// Transmit/Write Funcs.
__attribute__((weak)) bool i2c_send_data(const uint8_t addr, const uint8_t *data, uint16_t size) {
    i2c_status_t status = i2c_transmit((addr << 1), data, size, I2C_USERSPACE_TIMEOUT);
    return (status == I2C_STATUS_SUCCESS);
}

void rst_i2c_buffer(void) {
    memset(i2c_buffer, 0, sizeof(i2c_buffer));
    i2c_buffer_sz = 0;
}

void i2c_userspace_write(uint8_t* buf, uint8_t sz) {
    memcpy(&i2c_buffer, buf, sz);
    i2c_buffer_sz = sz;
}

bool i2c_userspace_init(void) {
    i2c_init();
    i2c_userspace_initialized = true;
    return true;
}

void i2c_userspace_kb_task_loop(void) {
    if (!i2c_userspace_initialized) {
        return;
    }
    i2c_userspace_task_kb();

    if (i2c_buffer_sz >0  && i2c_send_data(0x01, i2c_buffer, i2c_buffer_sz)) {
        rst_i2c_buffer();
    }
}

__attribute__((weak)) bool i2c_userspace_task_kb(void) {
    return i2c_userspace_task_user();
}

__attribute__((weak)) bool i2c_userspace_task_user(void) {
    return true;
}
