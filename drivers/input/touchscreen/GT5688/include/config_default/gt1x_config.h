/* drivers/input/touchscreen/gt1x_config.h
 *
 * 2010 - 2014 Goodix Technology.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be a reference
 * to you, when you are integrating the GOODiX's CTP IC into your system,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * Version: 1.0
 * Revision Record:
 *      V1.0:  first release. 2014/09/28.
 *
 */

#ifndef _GT1X_CONFIG_H_
#define _GT1X_CONFIG_H_

//#define GTP_DRIVER_SEND_CFG //driver send config to TP 
//#define CONFIG_GTP_CUSTOM_CFG 
//#define CONFIG_GTP_AUTO_UPDATE //auto update firmware
//#define CONFIG_GTP_HEADER_FW_UPDATE //updated fw by gt1x_firmware.h,function together with GTP_AUTO_UPDATE

//#define CONFIG_GTP_CHANGE_X2Y //swap x  y
#define CONFIG_GTP_CREATE_WR_NODE //supports GTP Tools
#define CONFIG_GTP_POWER_CTRL_SLEEP //power off  when suspend

//#define CONFIG_GTP_GESTURE_WAKEUP

//#define CONFIG_GTP_HOTKNOT
//#define CONFIG_HOTKNOT_TYPE
//#define CONFIG_HOTKNOT_BLOCK_RW

//#define CONFIG_GTP_PROXIMITY

//#define CONFIG_GTP_WITH_STYLUS
//#define CONFIG_GTP_HAVE_STYLUS_KEY

//#define CONFIG_GTP_ESD_PROTECT //esd protection
//#define CONFIG_GTP_CHARGER_SWITCH //charger plugin & plugout detect

//#define CONFIG_GTP_DEBUG_ARRAY_ON
//#define CONFIG_GTP_DEBUG_FUNC_ON

/***************************PART2:TODO define**********************************/
/*TODO: puts the config info corresponded to your TP here, the following is just
		a sample config, send this config should cause the chip can not work normally*/

/* TODO define your config for Sensor_ID == 0 here, if needed */
#define GTP_CFG_GROUP0 {\
0x97,0x38,0x04,0x80,0x07,0x0A,0x05,0x03,0x01,0x00,\
0x00,0x05,0x50,0x3C,0x53,0x11,0x00,0x00,0x00,0x00,\
0x14,0x18,0x1A,0x1D,0x0A,0x04,0x00,0x00,0x00,0x00,\
0x00,0x00,0x53,0x00,0x14,0x00,0x00,0x00,0x00,0x00,\
0x3C,0x0A,0x0A,0x64,0x1E,0x28,0x8A,0x2B,0x0C,0x41,\
0x43,0xDF,0x07,0x60,0x3A,0x60,0x12,0x02,0x24,0x00,\
0x00,0x22,0x59,0xC0,0x14,0x02,0x00,0x00,0x54,0xCA,\
0x2B,0xA9,0x34,0x92,0x3D,0x80,0x46,0x74,0x4F,0x6A,\
0x00,0x00,0x00,0x18,0x50,0x00,0x00,0xF0,0x50,0x3C,\
0xFF,0xFF,0x07,0x00,0x00,0x00,0x02,0x14,0x14,0x03,\
0x04,0x00,0x21,0x64,0x0A,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x32,0x30,0x3C,0x3C,0x1E,0x00,0x00,0x00,0x00,0x00,\
0x0D,0x06,0x0C,0x05,0x0B,0x04,0x0A,0x03,0x09,0x02,\
0x08,0x01,0xFF,0xFF,0x00,0x01,0x02,0x03,0x04,0x05,\
0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,\
0x10,0x11,0x12,0x13,0x14,0xFF,0xFF,0xFF,0xFF,0xFF,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x3C,0x00,0x05,0x1E,0x00,0x02,\
0x2A,0x1E,0x19,0x14,0x02,0x00,0x03,0x0A,0x05,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0x86,\
0x22,0x02,0x00,0x00,0x32,0x05,0x0F,0x00,0x00,0x00,\
0x50,0x3C,0x00,0x00,0x00,0x00,0xFC,0x03,0x01\
}

/* TODO define your config for Sensor_ID == 0 here, if needed */
#define GTP_CFG_GROUP0_CHARGER {\
}

/* TODO define your config for Sensor_ID == 1 here, if needed */
#define GTP_CFG_GROUP1 {\
0x97,0x38,0x04,0x80,0x07,0x0A,0x05,0x03,0x01,0x00,\
0x00,0x05,0x50,0x3C,0x53,0x11,0x00,0x00,0x00,0x00,\
0x14,0x18,0x1A,0x1D,0x0A,0x04,0x00,0x00,0x00,0x00,\
0x00,0x00,0x53,0x00,0x14,0x00,0x00,0x00,0x00,0x00,\
0x3C,0x0A,0x0A,0x64,0x1E,0x28,0x8A,0x2B,0x0C,0x41,\
0x43,0xDF,0x07,0x60,0x3A,0x60,0x12,0x02,0x24,0x00,\
0x00,0x22,0x59,0xC0,0x14,0x02,0x00,0x00,0x54,0xCA,\
0x2B,0xA9,0x34,0x92,0x3D,0x80,0x46,0x74,0x4F,0x6A,\
0x00,0x00,0x00,0x18,0x50,0x00,0x00,0xF0,0x50,0x3C,\
0xFF,0xFF,0x07,0x00,0x00,0x00,0x02,0x14,0x14,0x03,\
0x04,0x00,0x21,0x64,0x0A,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x32,0x30,0x3C,0x3C,0x1E,0x00,0x00,0x00,0x00,0x00,\
0x0D,0x06,0x0C,0x05,0x0B,0x04,0x0A,0x03,0x09,0x02,\
0x08,0x01,0xFF,0xFF,0x00,0x01,0x02,0x03,0x04,0x05,\
0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,\
0x10,0x11,0x12,0x13,0x14,0xFF,0xFF,0xFF,0xFF,0xFF,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x3C,0x00,0x05,0x1E,0x00,0x02,\
0x2A,0x1E,0x19,0x14,0x02,0x00,0x03,0x0A,0x05,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0x86,\
0x22,0x02,0x00,0x00,0x32,0x05,0x0F,0x00,0x00,0x00,\
0x50,0x3C,0x00,0x00,0x00,0x00,0xFC,0x03,0x01\
}

/* TODO define your config for Sensor_ID == 1 here, if needed */
#define GTP_CFG_GROUP1_CHARGER {\
}

/* TODO define your config for Sensor_ID == 2 here, if needed */
#define GTP_CFG_GROUP2 {\
}

/* TODO define your config for Sensor_ID == 2 here, if needed */
#define GTP_CFG_GROUP2_CHARGER {\
}

/* TODO define your config for Sensor_ID == 3 here, if needed */
#define GTP_CFG_GROUP3 {\
}

/* TODO define your config for Sensor_ID == 3 here, if needed */
#define GTP_CFG_GROUP3_CHARGER {\
}

/* TODO define your config for Sensor_ID == 4 here, if needed */
#define GTP_CFG_GROUP4 {\
}

/* TODO define your config for Sensor_ID == 4 here, if needed */
#define GTP_CFG_GROUP4_CHARGER {\
}

/* TODO define your config for Sensor_ID == 5 here, if needed */
#define GTP_CFG_GROUP5 {\
}

/* TODO define your config for Sensor_ID == 5 here, if needed */
#define GTP_CFG_GROUP5_CHARGER {\
}

#endif				/* _GT1X_CONFIG_H_ */
