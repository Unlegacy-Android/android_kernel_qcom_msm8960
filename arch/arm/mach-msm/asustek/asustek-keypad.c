/*
 * arch/arm/mach-msm/asustek/asustek-keypad.c
 * Keys configuration for Qualcomm platform.
 *
 * Copyright (C) 2012-2013 Asustek, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307, USA
 */

#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/device.h>
#include <linux/gpio_keys.h>

#include <mach/board_asustek.h>

#define GPIO_KEY_VOLUMEUP	53
#define GPIO_KEY_VOLUMEDOWN	54

#define GPIO_KEY(_id, _iswake)		\
	{					\
		.code = _id,			\
		.gpio = GPIO_##_id,		\
		.active_low = 1,		\
		.desc = #_id,			\
		.type = EV_KEY,			\
		.wakeup = _iswake,		\
		.debounce_interval = 15,	\
	}

static struct gpio_keys_button asustek_keys[] = {
	[0] = GPIO_KEY(KEY_VOLUMEUP, 0),
	[1] = GPIO_KEY(KEY_VOLUMEDOWN, 0),
};

static struct gpio_keys_platform_data asustek_keys_platform_data = {
	.buttons	= asustek_keys,
	.nbuttons	= ARRAY_SIZE(asustek_keys),
};

static struct platform_device asustek_keys_device = {
	.name   = "gpio-keys",
	.id     = 0,
	.dev    = {
		.platform_data  = &asustek_keys_platform_data,
	},
};

void __init asustek_add_keypad(void)
{
	pr_info("Registering gpio keys\n");

	platform_device_register(&asustek_keys_device);
}