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
#include <boot/board.h>
#include <boot/gpio_keypad.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
static unsigned int dream_row_gpios[] = {
#if 0 // unused?
    35, /* KP_MKOUT0 */
    34, /* KP_MKOUT1 */
    33, /* KP_MKOUT2 */
    32, /* KP_MKOUT3 */
    31, /* KP_MKOUT4 */
    23, /* KP_MKOUT5 */
#endif
#if 1
    30, /* KP_MKOUT6 */
    78, /* KP_MKOUT7 */
#endif
};

static unsigned int dream_col_gpios[] = {
#if 1 // main buttons
    42, /* KP_MKIN0 */
    41, /* KP_MKIN1 */
    40, /* KP_MKIN2 */
    39, /* KP_MKIN3 */
#endif
#if 1 // side buttons
    38, /* KP_MKIN4 */
    37, /* KP_MKIN5 */
    36, /* KP_MKIN6 */
#endif
};
static gpio_keypad_info dream_keypad = {
    .output_gpios = dream_row_gpios,
    .input_gpios = dream_col_gpios,
    .noutputs = ARRAY_SIZE(dream_row_gpios),
    .ninputs = ARRAY_SIZE(dream_col_gpios),
    .settle_time = 5000,
    .polarity = 0
};

static void keypad_poll()
{
    static int skip = 0;
    skip++;
    if(skip > 10) {
        gpio_keypad_scan_keys(&dream_keypad);
        skip = 0;
    }
}


void keypad_init(void)
{
    gpio_keypad_init(&dream_keypad);
    boot_register_poll_func(keypad_poll);
}
