/*
 * Copyright (C) 2015 MediaTek Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#define LOG_TAG "LCM"

#ifndef BUILD_LK
#include <linux/string.h>
#include <linux/kernel.h>
#endif

#include "lcm_drv.h"

#ifdef BUILD_LK
#include <platform/upmu_common.h>
#include <platform/mt_gpio.h>
#include <platform/mt_i2c.h>
#include <platform/mt_pmic.h>
#include <string.h>
#elif defined(BUILD_UBOOT)
#include <asm/arch/mt_gpio.h>
#endif

#ifdef BUILD_LK
#define LCM_LOGI(string, args...)  dprintf(ALWAYS, "[LK/"LOG_TAG"]"string, ##args)
#define LCM_LOGD(string, args...)  dprintf(INFO, "[LK/"LOG_TAG"]"string, ##args)
#else
#define LCM_LOGI(fmt, args...)  pr_notice("[KERNEL/"LOG_TAG"]"fmt, ##args)
#define LCM_LOGD(fmt, args...)  pr_debug("[KERNEL/"LOG_TAG"]"fmt, ##args)
#endif

#define LCM_DSI_CMD_MODE                0
#define FRAME_WIDTH			(720)
#define FRAME_HEIGHT			(1600)

//prize-tangcong modify LCD size-20200331-start
#define LCM_PHYSICAL_WIDTH                  				(63100)
#define LCM_PHYSICAL_HEIGHT                  				(123970)
//prize-tangcong modify LCD size-20200331-end

#define REGFLAG_PORT_SWAP               0xFFFA
#define REGFLAG_DELAY                   0xFFFC
#define REGFLAG_UDELAY                  0xFFFB
#define REGFLAG_END_OF_TABLE            0xFFFD


// ---------------------------------------------------------------------------
//  Local Variable
// ---------------------------------------------------------------------------
static struct LCM_UTIL_FUNCS lcm_util;


#define SET_RESET_PIN(v)	(lcm_util.set_reset_pin((v)))
#define MDELAY(n)		(lcm_util.mdelay(n))
#define UDELAY(n)		(lcm_util.udelay(n))

#define dsi_set_cmdq_V22(cmdq, cmd, count, ppara, force_update) \
	lcm_util.dsi_set_cmdq_V22(cmdq, cmd, count, ppara, force_update)
#define dsi_set_cmdq_V2(cmd, count, ppara, force_update) \
	lcm_util.dsi_set_cmdq_V2(cmd, count, ppara, force_update)
#define dsi_set_cmdq(pdata, queue_size, force_update) \
		lcm_util.dsi_set_cmdq(pdata, queue_size, force_update)
#define wrtie_cmd(cmd) lcm_util.dsi_write_cmd(cmd)
#define write_regs(addr, pdata, byte_nums) \
		lcm_util.dsi_write_regs(addr, pdata, byte_nums)
#define read_reg(cmd) \
		lcm_util.dsi_dcs_read_lcm_reg(cmd)
#define read_reg_v2(cmd, buffer, buffer_size) \
		lcm_util.dsi_dcs_read_lcm_reg_v2(cmd, buffer, buffer_size)

#ifndef BUILD_LK
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/i2c.h>
#include <linux/irq.h>
/* #include <linux/jiffies.h> */
/* #include <linux/delay.h> */
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#endif
struct LCM_setting_table {
	unsigned int cmd;
	unsigned char count;
	unsigned char para_list[120];
};

static struct LCM_setting_table lcm_initialization_setting[] = {
{0xFF,3,{0x98,0x82,0x01}},
{0x00,1,{0x46}},
{0x01,1,{0x33}},
{0x02,1,{0x00}},
{0x03,1,{0x00}},
{0x04,1,{0x42}},
{0x05,1,{0x33}},
{0x06,1,{0x00}},
{0x07,1,{0x00}},
{0x08,1,{0x83}},
{0x09,1,{0x03}},
{0x0A,1,{0x72}},
{0x0B,1,{0x00}},
{0x0C,1,{0x00}},
{0x0D,1,{0x00}},
{0x0E,1,{0x00}},
{0x0F,1,{0x00}},
{0x31,1,{0x02}},
{0x32,1,{0x02}},
{0x33,1,{0x02}},
{0x34,1,{0x0E}},
{0x35,1,{0x0C}},
{0x36,1,{0x16}},
{0x37,1,{0x14}},
{0x38,1,{0x12}},
{0x39,1,{0x10}},
{0x3A,1,{0x08}},
{0x3B,1,{0x0A}},
{0x3C,1,{0x07}},
{0x3D,1,{0x07}},
{0x3E,1,{0x07}},
{0x3F,1,{0x07}},
{0x40,1,{0x07}},
{0x41,1,{0x07}},
{0x42,1,{0x07}},
{0x43,1,{0x07}},
{0x44,1,{0x07}},
{0x45,1,{0x07}},
{0x46,1,{0x07}},
{0x47,1,{0x02}},
{0x48,1,{0x02}},
{0x49,1,{0x02}},
{0x4A,1,{0x0F}},
{0x4B,1,{0x0D}},
{0x4C,1,{0x17}},
{0x4D,1,{0x15}},
{0x4E,1,{0x13}},
{0x4F,1,{0x11}},
{0x50,1,{0x09}},
{0x51,1,{0x0B}},
{0x52,1,{0x07}},
{0x53,1,{0x07}},
{0x54,1,{0x07}},
{0x55,1,{0x07}},
{0x56,1,{0x07}},
{0x57,1,{0x07}},
{0x58,1,{0x07}},
{0x59,1,{0x07}},
{0x5A,1,{0x07}},
{0x5B,1,{0x07}},
{0x5C,1,{0x07}},
{0x61,1,{0x02}},
{0x62,1,{0x02}},
{0x63,1,{0x02}},
{0x64,1,{0x09}},
{0x65,1,{0x0B}},
{0x66,1,{0x15}},
{0x67,1,{0x17}},
{0x68,1,{0x11}},
{0x69,1,{0x13}},
{0x6A,1,{0x0F}},
{0x6B,1,{0x0D}},
{0x6C,1,{0x07}},
{0x6D,1,{0x07}},
{0x6E,1,{0x07}},
{0x6F,1,{0x07}},
{0x70,1,{0x07}},
{0x71,1,{0x07}},
{0x72,1,{0x07}},
{0x73,1,{0x07}},
{0x74,1,{0x07}},
{0x75,1,{0x07}},
{0x76,1,{0x07}},
{0x77,1,{0x02}},
{0x78,1,{0x02}},
{0x79,1,{0x02}},
{0x7A,1,{0x08}},
{0x7B,1,{0x0A}},
{0x7C,1,{0x14}},
{0x7D,1,{0x16}},
{0x7E,1,{0x10}},
{0x7F,1,{0x12}},
{0x80,1,{0x0E}},
{0x81,1,{0x0C}},
{0x82,1,{0x07}},
{0x83,1,{0x07}},
{0x84,1,{0x07}},
{0x85,1,{0x07}},
{0x86,1,{0x07}},
{0x87,1,{0x07}},
{0x88,1,{0x07}},
{0x89,1,{0x07}},
{0x8A,1,{0x07}},
{0x8B,1,{0x07}},
{0x8C,1,{0x07}},
{0xE7,1,{0x54}},
{0xFF,3,{0x98,0x82,0x02}},
{0xF1,1,{0x1C}},
{0x4B,1,{0x5A}},
{0x50,1,{0xCA}},
{0x51,1,{0x00}},
{0x06,1,{0x8D}},
{0x0B,1,{0xA0}},
{0x0C,1,{0x00}},
{0x0D,1,{0x1A}},
{0x0E,1,{0xFA}},
{0x4E,1,{0x11}},
{0x01,1,{0x14}},
{0x02,1,{0x0A}},
{0xFF,3,{0x98,0x82,0x05}},
{0x03,1,{0x01}},
{0x04,1,{0x25}},
{0x63,1,{0x7E}},
{0x64,1,{0x7E}},
{0x68,1,{0xA1}},
{0x69,1,{0xA7}},
{0x6A,1,{0x8D}},
{0x6B,1,{0x7F}},
{0x85,1,{0x37}},
{0x46,1,{0x00}},
{0xFF,3,{0x98,0x82,0x06}},
{0xD9,1,{0x1F}},
{0xC0,1,{0x40}},
{0xC1,1,{0x16}},
{0xFF,3,{0x98,0x82,0x08}},
{0xE0,27,{0x00,0x24,0x49,0x6A,0x97,0x50,0xC1,0xE4,0x0F,0x33,0x55,0x6F,0xA2,0xD0,0xFC,0xAA,0x2A,0x62,0x86,0xB4,0xFE,0xDB,0x0F,0x50,0x86,0x03,0xEC}},
{0xE1,27,{0x00,0x24,0x49,0x6A,0x97,0x50,0xC1,0xE4,0x0F,0x33,0x55,0x6F,0xA2,0xD0,0xFC,0xAA,0x2A,0x62,0x86,0xB4,0xFE,0xDB,0x0F,0x50,0x86,0x03,0xEC}},
{0xFF,3,{0x98,0x82,0x0B}},
{0x9A,1,{0x44}},
{0x9B,1,{0x81}},
{0x9C,1,{0x03}},
{0x9D,1,{0x03}},
{0x9E,1,{0x70}},
{0x9F,1,{0x70}},
{0xAB,1,{0xE0}},
{0xFF,3,{0x98,0x82,0x0E}},
{0x11,1,{0x10}},
{0x13,1,{0x10}},
{0x00,1,{0xA0}},
{0xFF,3,{0x98,0x82,0x00}},
{0x35,1,{0x00}},

{0x11,1,{0x00}},
{REGFLAG_DELAY,120,{}},
{0x29,1,{0x00}},
{REGFLAG_DELAY,20,{}},

};

static struct LCM_setting_table lcm_deep_sleep_mode_in_setting[] = {
	{0x26, 1, {0x08}},
	// Display off sequence
	{0x28, 0, {0x00}},
	{REGFLAG_DELAY, 50, {}},
	// Sleep Mode On
	{0x10, 0, {0x00}},
	{REGFLAG_DELAY, 120, {}},
	{REGFLAG_END_OF_TABLE, 0x00, {}},
};

static void push_table(struct LCM_setting_table *table, unsigned int count, unsigned char force_update)
{
	unsigned int i;
	for(i = 0; i < count; i++) {
		unsigned int cmd;
		cmd = table[i].cmd;
		switch (cmd) {
			case REGFLAG_DELAY :
				MDELAY(table[i].count);
				break;
			case REGFLAG_END_OF_TABLE :
				break;
			default:
				dsi_set_cmdq_V2(cmd, table[i].count, table[i].para_list, force_update);
		}
	}
}

// ---------------------------------------------------------------------------
//  LCM Driver Implementations
// ---------------------------------------------------------------------------
static void lcm_set_util_funcs(const struct LCM_UTIL_FUNCS *util)
{
	memcpy(&lcm_util, util, sizeof(struct LCM_UTIL_FUNCS));
}

static void lcm_get_params(struct LCM_PARAMS *params)
{
	memset(params, 0, sizeof(struct LCM_PARAMS));

	params->type = LCM_TYPE_DSI;

	params->width = FRAME_WIDTH;
	params->height = FRAME_HEIGHT;

//	params->virtual_width = VIRTUAL_WIDTH;
//	params->virtual_height = VIRTUAL_HEIGHT;

#if (LCM_DSI_CMD_MODE)
	params->dsi.mode            = CMD_MODE;
#else
	params->dsi.mode            = BURST_VDO_MODE;
#endif

	/* The following defined the fomat for data coming from LCD engine. */
	params->dsi.data_format.color_order	= LCM_COLOR_ORDER_RGB;
	params->dsi.data_format.trans_seq	= LCM_DSI_TRANS_SEQ_MSB_FIRST;
	params->dsi.data_format.padding		= LCM_DSI_PADDING_ON_LSB;
	params->dsi.data_format.format		= LCM_DSI_FORMAT_RGB888;

	/* Highly depends on LCD driver capability */
	/* video mode timing */
	params->dsi.PS                                  = LCM_PACKED_PS_24BIT_RGB888;
	params->dsi.vertical_sync_active                = 4;
	params->dsi.vertical_backporch                  = 10;
	params->dsi.vertical_frontporch                 = 230;
	params->dsi.vertical_active_line                = FRAME_HEIGHT;
	params->dsi.horizontal_sync_active              = 8;
	params->dsi.horizontal_backporch                = 20;
	params->dsi.horizontal_frontporch               = 20;
	params->dsi.horizontal_active_pixel             = FRAME_WIDTH;
	params->dsi.LANE_NUM                            = LCM_FOUR_LANE;
	/*prize-zhaopengge modify lcd fps-20201012-start*/
	params->dsi.PLL_CLOCK                           = 260;
	/*prize-zhaopengge modify lcd fps-20201012-end*/
     //prize-tangcong modify LCD size-20200331-start
	params->physical_width = LCM_PHYSICAL_WIDTH/1000;
	params->physical_height = LCM_PHYSICAL_HEIGHT/1000;
	//prize-tangcong modify LCD size-20200331-end
	params->dsi.ssc_disable                         = 1;
	params->dsi.ssc_range                           = 4;

	params->dsi.HS_TRAIL                            = 15;
	params->dsi.noncont_clock                       = 1;
	params->dsi.noncont_clock_period                = 1;

	/* ESD check function */
	params->dsi.esd_check_enable                    = 1;
	params->dsi.customization_esd_check_enable      = 0;
	//params->dsi.clk_lp_per_line_enable              = 1;
	params->dsi.lcm_esd_check_table[0].cmd          = 0x0A;
	params->dsi.lcm_esd_check_table[0].count        = 1;
	params->dsi.lcm_esd_check_table[0].para_list[0] = 0x9C;
#ifdef CONFIG_MTK_ROUND_CORNER_SUPPORT
	params->round_corner_en = 1;
	params->full_content = 0;
/*prize-zhaopengge modify round corner size-20200928-start*/
	params->corner_pattern_width = 720;
	params->corner_pattern_height = 16;
	params->corner_pattern_height_bot = 16;
/*prize-zhaopengge modify round corner size-20200928-end*/
#endif
}


static void lcm_init(void)
{

    display_ldo18_enable(1);
	MDELAY(15);
    display_bias_enable();
	MDELAY(15);

	SET_RESET_PIN(1);
	MDELAY(10);
	SET_RESET_PIN(0);
	MDELAY(10);
	SET_RESET_PIN(1);
	MDELAY(35);

	push_table(lcm_initialization_setting, sizeof(lcm_initialization_setting) / sizeof(struct LCM_setting_table), 1);
}

static void lcm_suspend(void)
{
	push_table(lcm_deep_sleep_mode_in_setting, sizeof(lcm_deep_sleep_mode_in_setting) / sizeof(struct LCM_setting_table), 1);
	MDELAY(5);
	
	display_bias_disable();
	MDELAY(10);
	display_ldo18_enable(0);
	MDELAY(5);
}

static void lcm_resume(void)
{
	lcm_init();
}

static unsigned int lcm_compare_id(void)
{
    int array[4];
    char buffer[4]={0,0,0,0};
	char buffer1[4]={0,0,0,0};
	char buffer2[4]={0,0,0,0};
    unsigned int id=0;
	//int rawdata = 0;
	//int ret = 0;

	
	struct LCM_setting_table switch_table_page6[] = {
		{ 0xFF, 0x03, {0x98, 0x82, 0x06} }
	};
//	struct LCM_setting_table switch_table_page0[] = {
//		{ 0xFF, 0x03, {0x98, 0x81, 0x00} }
//	};

	MDELAY(10);
	SET_RESET_PIN(1);
	MDELAY(10);
    SET_RESET_PIN(0);
    MDELAY(20);
    SET_RESET_PIN(1);
    MDELAY(120);

	push_table(switch_table_page6,sizeof(switch_table_page6) / sizeof(struct LCM_setting_table),1);

    MDELAY(5);
    array[0] = 0x00013700;
    dsi_set_cmdq(array, 1, 1);
    //MDELAY(10);
    read_reg_v2(0xF0, buffer, 1);//    NC 0x00  0x98 
	
	MDELAY(5);
    array[0] = 0x00013700;
    dsi_set_cmdq(array, 1, 1);
    //MDELAY(10);
    read_reg_v2(0xF1, buffer1, 1);//    NC 0x00  0x82 
	
	MDELAY(5);
    array[0] = 0x00013700;
    dsi_set_cmdq(array, 1, 1);
    //MDELAY(10);
    read_reg_v2(0xF2, buffer2, 1);//    NC 0x00  0x0d 

    id = (buffer[0]<<16) | (buffer1[0]<<8) |buffer2[0];
	
#ifdef BUILD_LK
	dprintf(CRITICAL, "%s, LK debug: ili9882 id = 0x%08x\n", __func__, id);
#else
	printk("%s: ili9882 id = 0x%08x \n", __func__, id);
#endif
  
    if(0x98820d == id)
	{
		//is_9882N_detect=1;
	    return 1;
	}
    else{
		return 0;
	}

}

#ifndef BUILD_LK
extern atomic_t ESDCheck_byCPU;
#endif
static unsigned int lcm_ata_check(unsigned char *buffer)
{
#if 1
#ifndef BUILD_LK 
unsigned int ret = 0 ,ret1=2; 
//unsigned int x0 = FRAME_WIDTH/4; 
//unsigned int x1 = FRAME_WIDTH*3/4; 
//unsigned int y0 = 0;
//unsigned int y1 = y0 + FRAME_HEIGHT - 1;
unsigned char x0_MSB = 0x5;//((x0>>8)&0xFF); 
unsigned char x0_LSB = 0x2;//(x0&0xFF); 
unsigned char x1_MSB = 0x1;//((x1>>8)&0xFF); 
unsigned char x1_LSB = 0x4;//(x1&0xFF); 
	//unsigned char y0_MSB = ((y0>>8)&0xFF);
	//unsigned char y0_LSB = (y0&0xFF);
	//unsigned char y1_MSB = ((y1>>8)&0xFF);
	//unsigned char y1_LSB = (y1&0xFF);
	
unsigned int data_array[6]; 
unsigned char read_buf[4]; 
unsigned char read_buf1[4]; 
unsigned char read_buf2[4]; 
unsigned char read_buf3[4]; 
#ifdef BUILD_LK 
printf("ATA check kernel size = 0x%x,0x%x,0x%x,0x%x\n",x0_MSB,x0_LSB,x1_MSB,x1_LSB); 
#else 
printk("ATA check kernel size = 0x%x,0x%x,0x%x,0x%x\n",x0_MSB,x0_LSB,x1_MSB,x1_LSB); 
#endif 
//write page frist lhr
//data_array[0]= 0x0002150A;//HS packet 
//data_array[1]= (x1_MSB<<24)|(x0_LSB<<16)|(x0_MSB<<8)|0x51; 
//data_array[2]= (x1_LSB); 
//dsi_set_cmdq(data_array, 3, 1); 
   
data_array[0]= 0x0002390A;//HS packet 
data_array[1]= 0x00002453; 
//data_array[2]= (x1_LSB); 
dsi_set_cmdq(data_array, 2, 1); 
    
 data_array[0]= 0x0002390A;//HS packet 
data_array[1]= 0x0000F05e; 
dsi_set_cmdq(data_array, 2, 1); 
data_array[0]= 0x0002390A;//HS packet 
data_array[1]= 0x00000151; 
dsi_set_cmdq(data_array, 2, 1); 
data_array[0]= 0x0002390A;//HS packet 
data_array[1]= 0x00000355; 
//data_array[2]= (x1_LSB); 
dsi_set_cmdq(data_array, 2, 1); 
 
//data_array[0]= 0x0002150A;//HS packet 
//data_array[1]= (x1_MSB<<24)|(x0_LSB<<16)|(x0_MSB<<8)|0x51; 
//data_array[2]= (x1_LSB); 
//dsi_set_cmdq(data_array, 3, 1); 
 
data_array[0] = 0x00013700; 
dsi_set_cmdq(data_array, 1, 1); 
atomic_set(&ESDCheck_byCPU, 1);
read_reg_v2(0X52, read_buf, 1); 
read_reg_v2(0X56, read_buf1, 1); 
read_reg_v2(0X54, read_buf2, 1); 
read_reg_v2(0X5F, read_buf3, 1);
atomic_set(&ESDCheck_byCPU, 0);
if((read_buf1[0] == 0x03) && (read_buf2[0] == 0x24) /*&& (read_buf3[0] == 0xf0)*/) 
   ret = 1; 
else 
    ret = 0; 
#ifdef BUILD_LK 
printf("ATA read buf kernel size = 0x%x,0x%x,0x%x,0x%x,ret= %d\n",read_buf[0],read_buf[1],read_buf[2],read_buf[3],ret); 
#else 
printk("ATA read buf kernel size = 0x%x,0x%x,0x%x,0x%x,ret= %d ret1= %d\n",read_buf[0],read_buf1[0],read_buf2[0],read_buf3[0],ret,ret1); 
printk("ATA read buf new kernel size = 0x%x,0x%x,0x%x,0x%x,ret= %d ret1= %d\n",read_buf1[0],read_buf1[1],read_buf1[2],read_buf1[3],ret,ret1); 
//printk("ATA read buf new kernel size = 0x%x,0x%x,0x%x,0x%x,ret= %d ret1= %d\n",read_buf1,read_buf1,read_buf1,read_buf1,ret,ret1); 
#endif 
return ret; 
#endif 
#endif
}

struct LCM_DRIVER ili9882n_hdp_dsi_vdo_txd_ata_lcm_drv =
{
	.name		= "ili9882n_hdp_dsi_vdo_txd_ata",
	#if defined(CONFIG_PRIZE_HARDWARE_INFO) && !defined (BUILD_LK)
	.lcm_info = {
		.chip	= "ili9882",
		.vendor	= "ilitek",
		.id = "0x98820d",
		.more	= "720*1600",
	},
   #endif
	.set_util_funcs	= lcm_set_util_funcs,
	.get_params	= lcm_get_params,
	.init		= lcm_init,
	.suspend	= lcm_suspend,
	.resume		= lcm_resume,
	.compare_id	= lcm_compare_id,
	.ata_check	= lcm_ata_check,
};
