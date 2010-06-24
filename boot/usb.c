/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <boot/boot.h>

void ulpi_write(unsigned val, unsigned reg);
unsigned ulpi_read(unsigned reg);

void board_usb_init(void)
{
    writeb(0, 0x98000004);
    mdelay(100);
    writeb((1 << 5), 0x98000004);
    mdelay(100);
}

void board_ulpi_init(void)
{
        /* adjust eye diagram */
    ulpi_write(0x40, 0x31);

        /* disable VBUS interrupt to avoid stuck PHY issue */
    ulpi_write(0x1D, 0x0D);
    ulpi_write(0x1D, 0x10);
}
