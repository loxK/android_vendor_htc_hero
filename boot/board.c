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
#include <boot/flash.h>

ptentry PTABLE[] = {
    {
        .start = 310,
        .length = 40,
        .name = "recovery",
    },
    {
        .start = 350,
        .length = 20,
        .name = "boot",
    },
    {
        .start = 370,
        .length = 540,
        .name = "system",
    },
    {
        .start = 910,
        .length = 1138,
        .name = "userdata",
    },
    {
        .start = 0,
        .length = 0,
        .name = "",
    },
};

#define MISC2_CHARGER_OFF  0x01  /* DISABLE charge circuitry */
#define MISC2_ISET         0x02  /* Enable Current Limit */

#define MISC2_H2W_MASK     0xC0
#define MISC2_H2W_GPIO     0x00
#define MISC2_H2W_UART1    0x40
#define MISC2_H2W_UART3    0x80
#define MISC2_H2W_BT       0xC0

void board_init()
{
    unsigned n;

    /* if we already have partitions from elsewhere,
    ** don't use the hardcoded ones
    */
    if(flash_get_ptn_count() == 0) {
        for(n = 0; PTABLE[n].name[0]; n++) {
            flash_add_ptn(PTABLE + n);
        }
    }

    /* UART configuration */
#if 1
        /* UART3 */
    writeb(MISC2_H2W_UART3, 0x98000000);
    uart_init(2);
#else
        /* UART1 */
    writeb(MISC2_H2W_UART1, 0x98000000);
    uart_init(0);
#endif
    mdelay(100);
}

const char *board_cmdline(void)
{
    return "mem=112M console=ttyMSM0 androidboot.console=ttyMSM0";
};

unsigned board_machtype(void)
{
    return 1440;
}

void board_reboot(void)
{
    gpio_set(25, 0);
}

void board_getvar(const char *name, char *value)
{
    if(!strcmp(name, "version.amss")) {
        get_version_modem(value);
    } else if(!strcmp(name, "version.amss.sbl")) {
        get_version_modem_sbl(value);
    }
}
