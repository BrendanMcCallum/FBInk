/*
 * Copyright (C) 2004-2015 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * - Modified by houqp, added mxcfb_update_data struct from GeekMaster's
 *   video player, refer to:
 *   http://www.mobileread.com/forums/showthread.php?t=177455&page=10
 *
 * - Modified mxcfb_alt_buffer_data struct according to include/linux/mxcfb.h
 *   from Kindle 5.3.0 firmware. Thanks to eureka@mobileread.
 *   http://www.mobileread.com/forums/showpost.php?p=2337118&postcount=818
 *
 * - Frankensteined w/ PW2 stuff -- NiLuJe
 *
 * - Frankensteined w/ KT2 & KV stuff -- NiLuJe
 *
 * - Frankensteined w/ KOA2 stuff
 *   Upstream could afford to break backward compatibility, we can't,
 *   so all the KOA2 pre/suffixing is ours. -- NiLuJe
 */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
/*
 * Copyright 2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 */

/*
 * @file uapi/linux/mxcfb.h
 *
 * @brief Global header file for the MXC frame buffer
 *
 * @ingroup Framebuffer
 */
#ifndef __ASM_ARCH_MXCFB_H__
#define __ASM_ARCH_MXCFB_H__

//#include <linux/fb.h>

#define FB_SYNC_OE_LOW_ACT	0x80000000
#define FB_SYNC_CLK_LAT_FALL	0x40000000
#define FB_SYNC_DATA_INVERT	0x20000000
#define FB_SYNC_CLK_IDLE_EN	0x10000000
#define FB_SYNC_SHARP_MODE	0x08000000
#define FB_SYNC_SWAP_RGB	0x04000000
/* PW2 */
#define FB_ACCEL_TRIPLE_FLAG	0x00000000
#define FB_ACCEL_DOUBLE_FLAG	0x00000001

struct mxcfb_gbl_alpha {
	int enable;
	int alpha;
};

struct mxcfb_loc_alpha {
	int enable;
	int alpha_in_pixel;
	unsigned long alpha_phy_addr0;
	unsigned long alpha_phy_addr1;
};

struct mxcfb_color_key {
	int enable;
	__u32 color_key;
};

struct mxcfb_pos {
	__u16 x;
	__u16 y;
};

struct mxcfb_gamma {
	int enable;
	int constk[16];
	int slopek[16];
};

/* KOA2 */
struct mxcfb_gpu_split_fmt {
	struct fb_var_screeninfo var;
	unsigned long offset;
};

struct mxcfb_rect {
	__u32 top;
	__u32 left;
	__u32 width;
	__u32 height;
};

#define GRAYSCALE_8BIT				0x1
#define GRAYSCALE_8BIT_INVERTED			0x2

/* PW2 */
#define GRAYSCALE_4BIT				0x3
#define GRAYSCALE_4BIT_INVERTED			0x4

#define AUTO_UPDATE_MODE_REGION_MODE		0
#define AUTO_UPDATE_MODE_AUTOMATIC_MODE		1

/* Touch/PW1, Gone w/ KOA2 */
#define AUTO_UPDATE_MODE_AUTOMATIC_MODE_FULL	AUTO_UPDATE_MODE_AUTOMATIC_MODE /* Lab126 */
#define AUTO_UPDATE_MODE_AUTOMATIC_MODE_PART	2 /* Lab126 */

#define UPDATE_SCHEME_SNAPSHOT			0
#define UPDATE_SCHEME_QUEUE			1
#define UPDATE_SCHEME_QUEUE_AND_MERGE		2

#define UPDATE_MODE_PARTIAL			0x0
#define UPDATE_MODE_FULL			0x1

/* Supported waveform modes */
#define WAVEFORM_MODE_INIT			0x0	/* Screen goes to white (clears) */
#define WAVEFORM_MODE_DU			0x1	/* Grey->white/grey->black */
#define WAVEFORM_MODE_GC16			0x2	/* High fidelity (flashing) */
#define WAVEFORM_MODE_GC4			WAVEFORM_MODE_GC16 /* For compatibility */
#define WAVEFORM_MODE_GC16_FAST			0x3	/* Medium fidelity */
#define WAVEFORM_MODE_A2			0x4	/* Faster but even lower fidelity */
#define WAVEFORM_MODE_GL16			0x5	/* High fidelity from white transition */
#define WAVEFORM_MODE_GL16_FAST			0x6	/* Medium fidelity from white transition */

/* FW >= 5.3 */
#define WAVEFORM_MODE_DU4			0x7	/* Medium fidelity 4 level of gray direct update */

/* PW2/KT2/KV */
#define WAVEFORM_MODE_REAGL			0x8	/* Ghost compensation waveform */
#define WAVEFORM_MODE_REAGLD			0x9	/* Ghost compensation waveform with dithering */

/* KT2/KV */
#define WAVEFORM_MODE_GL4			0xA	/* 2-bit from white transition */
#define WAVEFORM_MODE_GL16_INV			0xB	/* High fidelity for black transition */

/* KOA2... Which wonderfully broke backward compatibility. Yay. */
//#define WAVEFORM_MODE_INIT			0x0
//#define WAVEFORM_MODE_DU			0x1
//#define WAVEFORM_MODE_GC16			0x2
#define WAVEFORM_MODE_KOA2_GL16			0x3

#define WAVEFORM_MODE_KOA2_A2			0x6
#define WAVEFORM_MODE_KOA2_DU4			0x7
#define WAVEFORM_MODE_KOA2_LAST			0x7

#define WAVEFORM_MODE_KOA2_REAGL		WAVEFORM_MODE_KOA2_GLR16
#define WAVEFORM_MODE_KOA2_REAGLD		WAVEFORM_MODE_KOA2_GLD16

#define WAVEFORM_MODE_KOA2_GC16_FAST		WAVEFORM_MODE_GC16
#define WAVEFORM_MODE_KOA2_GL16_FAST		WAVEFORM_MODE_KOA2_GL16
#define WAVEFORM_MODE_KOA2_GLR16		4
#define WAVEFORM_MODE_KOA2_GLD16		5
#define WAVEFORM_MODE_KOA2_GCK16		8
#define WAVEFORM_MODE_KOA2_GLKW16		9

/* for backward compatible */
#define WAVEFORM_MODE_KOA2_GL4			WAVEFORM_MODE_KOA2_GL16
#define WAVEFORM_MODE_KOA2_GL16_INV		WAVEFORM_MODE_KOA2_GL16


#define WAVEFORM_MODE_AUTO			257

/* Display temperature */
#define TEMP_USE_AMBIENT			0x1000
/* Gone w/ KOA2 */
#define TEMP_USE_PAPYRUS			0X1001

/* PW2, Gone w/ KOA2 */
#define TEMP_USE_AUTO				0x1001

/* KOA2... Once again breaking backward compat... */
#define TEMP_USE_KOA2_AUTO			TEMP_USE_AMBIENT

/* PXP Operations */
#define EPDC_FLAG_ENABLE_INVERSION		0x01
#define EPDC_FLAG_FORCE_MONOCHROME		0x02
#define EPDC_FLAG_USE_CMAP			0x04
#define EPDC_FLAG_USE_ALT_BUFFER		0x100

/* PW2 */
#define EPDC_FLAG_TEST_COLLISION		0x200
#define EPDC_FLAG_GROUP_UPDATE			0x400

/* Gone w/ KOA2 */
#define EPDC_FLAG_FORCE_Y2			0x800
#define EPDC_FLAG_USE_REAGLD			0x1000

#define EPDC_FLAG_USE_DITHERING_Y1		0x2000

/* Renamed w/ KOA2, see next block */
#define EPDC_FLAG_USE_DITHERING_Y2		0x4000
#define EPDC_FLAG_USE_DITHERING_Y4		0x8000

/* KOA2... Once again breaking backward compat... */
#define EPDC_FLAG_USE_KOA2_DITHERING_Y4		0x4000
#define EPDC_FLAG_USE_KOA2_REGAL		0x8000


/* PW2 */
/* Waveform type as return by MXCFB_GET_WAVEFORM_TYPE ioctl */
/* This indicates to user-space what is supported by the waveform */
#define WAVEFORM_TYPE_4BIT			0x1
#define WAVEFORM_TYPE_5BIT			(WAVEFORM_TYPE_4BIT << 1)

/* KT2/KV */
/* Display material */
#define EPD_MATERIAL_V220			0x00
#define EPD_MATERIAL_V320			0x01

/* KOA2 */
#define EPD_MATERIAL_CARTA_1_2			0x02

/* KOA2 */
enum mxcfb_dithering_mode {
	EPDC_FLAG_USE_DITHERING_PASSTHROUGH = 0x0,
	EPDC_FLAG_USE_DITHERING_FLOYD_STEINBERG,
	EPDC_FLAG_USE_DITHERING_ATKINSON,
	EPDC_FLAG_USE_DITHERING_ORDERED,
	EPDC_FLAG_USE_DITHERING_QUANT_ONLY,
	EPDC_FLAG_USE_DITHERING_MAX,
};

#define FB_POWERDOWN_DISABLE			-1

struct mxcfb_alt_buffer_data {
	__u32 phys_addr;
	__u32 width;	/* width of entire buffer */
	__u32 height;	/* height of entire buffer */
	struct mxcfb_rect alt_update_region;	/* region within buffer to update */
};

struct mxcfb_update_data {
	struct mxcfb_rect update_region;
	__u32 waveform_mode;
	__u32 update_mode;
	__u32 update_marker;
	__u32 hist_bw_waveform_mode;    /*Lab126: Def bw waveform for hist analysis*/
	__u32 hist_gray_waveform_mode;  /*Lab126: Def gray waveform for hist analysis*/
	int temp;
	uint flags;
	struct mxcfb_alt_buffer_data alt_buffer_data;
};

/* KOA2... Once again breaking backward compat. */
struct mxcfb_update_data_koa2 {
	struct mxcfb_rect update_region;
	__u32 waveform_mode;
	__u32 update_mode;
	__u32 update_marker;
	int temp;
	unsigned int flags;
	int dither_mode;
	int quant_bit;
	struct mxcfb_alt_buffer_data alt_buffer_data;
	/* start: lab126 added for backward compatible */
	__u32 hist_bw_waveform_mode;    /*Lab126: Def bw waveform for hist analysis*/
	__u32 hist_gray_waveform_mode;  /*Lab126: Def gray waveform for hist analysis*/
	__u32 ts_pxp;   /*debugging purpose: pxp starting time*/
	__u32 ts_epdc;  /*debugging purpose: EPDC starting time*/
	/* end: lab126 added */
};

/* PW2 */
struct mxcfb_update_marker_data {
	__u32 update_marker;
	__u32 collision_test;
};

/* This is only used in kindle firmware 5.0, later version (5.1) has changed
 * the struct to mxcfb_update_data (see above).
 * We don't actually support this, it's just kept here for shit'n giggles ;) */
struct mxcfb_update_data_50x {
	struct mxcfb_rect update_region;
	__u32 waveform_mode;
	__u32 update_mode;
	__u32 update_marker;
	int temp;
	uint flags;
	struct mxcfb_alt_buffer_data alt_buffer_data;
};

/*
 * Structure used to define waveform modes for driver
 * Needed for driver to perform auto-waveform selection
 */
/* NOTE: Trimmed down w/ KOA2, see next block */
struct mxcfb_waveform_modes {
	int mode_init;
	int mode_du;
	int mode_gc4;
	int mode_gc8;
	int mode_gc16;
	int mode_gc16_fast;
	int mode_gc32;
	int mode_gl16;
	int mode_gl16_fast;
	int mode_a2;
	/* FW >= 5.3 */
	int mode_du4;

	/* PW2 */
	/*
	 * reagl_flow
	 */
	int mode_reagl;
	int mode_reagld;

	/* KT2/KV */
	int mode_gl16_inv;
	int mode_gl4;
};

/* KOA2... Breaking backward compat. */
struct mxcfb_waveform_modes_koa2 {
	int mode_init;
	int mode_du;
	int mode_gc4;
	int mode_gc8;
	int mode_gc16;
	int mode_gc32;
};

/* PW2 */
/*
 * Structure used to define a 5*3 matrix of parameters for
 * setting IPU DP CSC module related to this framebuffer.
 */
struct mxcfb_csc_matrix {
	int param[5][3];
};

#define MXCFB_WAIT_FOR_VSYNC			_IOW('F', 0x20, u_int32_t)
#define MXCFB_SET_GBL_ALPHA			_IOW('F', 0x21, struct mxcfb_gbl_alpha)
#define MXCFB_SET_CLR_KEY			_IOW('F', 0x22, struct mxcfb_color_key)
#define MXCFB_SET_OVERLAY_POS			_IOWR('F', 0x24, struct mxcfb_pos)
#define MXCFB_GET_FB_IPU_CHAN			_IOR('F', 0x25, u_int32_t)
#define MXCFB_SET_LOC_ALPHA			_IOWR('F', 0x26, struct mxcfb_loc_alpha)
#define MXCFB_SET_LOC_ALP_BUF			_IOW('F', 0x27, unsigned long)
#define MXCFB_SET_GAMMA				_IOW('F', 0x28, struct mxcfb_gamma)
#define MXCFB_GET_FB_IPU_DI			_IOR('F', 0x29, u_int32_t)
#define MXCFB_GET_DIFMT				_IOR('F', 0x2A, u_int32_t)
#define MXCFB_GET_FB_BLANK			_IOR('F', 0x2B, u_int32_t)
#define MXCFB_SET_DIFMT				_IOW('F', 0x2C, u_int32_t)

/* PW2 */
#define MXCFB_CSC_UPDATE			_IOW('F', 0x2D, struct mxcfb_csc_matrix)

/* KOA2 */
#define MXCFB_SET_GPU_SPLIT_FMT        _IOW('F', 0x2F, struct mxcfb_gpu_split_fmt)
#define MXCFB_SET_PREFETCH     _IOW('F', 0x30, int)
#define MXCFB_GET_PREFETCH     _IOR('F', 0x31, int)

/* IOCTLs for E-ink panel updates */
#define MXCFB_SET_WAVEFORM_MODES		_IOW('F', 0x2B, struct mxcfb_waveform_modes)
#define MXCFB_SET_TEMPERATURE			_IOW('F', 0x2C, int32_t)
#define MXCFB_SET_AUTO_UPDATE_MODE		_IOW('F', 0x2D, __u32)
#define MXCFB_SEND_UPDATE			_IOW('F', 0x2E, struct mxcfb_update_data)

/* KOA2, because backward compat went kablooey */
#define MXCFB_SET_WAVEFORM_MODES_KOA2		_IOW('F', 0x2B, struct mxcfb_waveform_modes_koa2)
#define MXCFB_SEND_UPDATE_KOA2			_IOW('F', 0x2E, struct mxcfb_update_data_koa2)


/* This evolved on the PW2... Rename the Touch/PW1 constant to differentiate the two. */
#define MXCFB_WAIT_FOR_UPDATE_COMPLETE_PEARL	_IOW('F', 0x2F, __u32)
/* PW2 */
#define MXCFB_WAIT_FOR_UPDATE_COMPLETE		_IOWR('F', 0x2F, struct mxcfb_update_marker_data)

#define MXCFB_SET_PWRDOWN_DELAY			_IOW('F', 0x30, int32_t)
#define MXCFB_GET_PWRDOWN_DELAY			_IOR('F', 0x31, int32_t)
#define MXCFB_SET_UPDATE_SCHEME			_IOW('F', 0x32, __u32)
#define MXCFB_SET_PAUSE				_IOW('F', 0x33, __u32)
#define MXCFB_GET_PAUSE				_IOW('F', 0x34, __u32)
#define MXCFB_SET_RESUME			_IOW('F', 0x35, __u32)

/* KOA2 */
#define MXCFB_GET_WORK_BUFFER_KOA2		_IOWR('F', 0x34, unsigned long)
#define MXCFB_DISABLE_EPDC_ACCESS		_IO('F', 0x35)
#define MXCFB_ENABLE_EPDC_ACCESS		_IO('F', 0x36)

/* Touch/PW1 */
#define MXCFB_CLEAR_UPDATE_QUEUE		_IOW('F', 0x36, __u32)
/* PW2 */
#define MXCFB_GET_WORK_BUFFER			_IOWR('F', 0x36, unsigned long)

#define MXCFB_WAIT_FOR_UPDATE_SUBMISSION	_IOW('F', 0x37, __u32)

/* FW >= 5.3 */
#define MXCFB_GET_TEMPERATURE			_IOR('F', 0x38, int32_t)

/* PW2 */
#define MXCFB_GET_WAVEFORM_TYPE			_IOR('F', 0x39, __u32)

/* KT2/KV */
#define MXCFB_GET_MATERIAL_TYPE			_IOR('F', 0x3A, __u32)

/* Deprecated IOCTL for E-ink panel updates, kindle firmware version == 5.0 */
#define MXCFB_SEND_UPDATE_50X			_IOW('F', 0x2E, struct mxcfb_update_data_50x)

/* KOA2 */
/* before update with gck16, reduce bl to zero and turn back to original after */
#define NIGHTMODE_STRIDE_DEFAULT 16  /*default*/
struct mxcfb_nightmode_ctrl {
	int disable; /*1: disable; 0, enable */
	int start; /* reduced to level for gck16 */
	int stride; /* back to original level gradually: default */
	int current_level; /* current brighness setting */
};

#define MXCFB_SET_NIGHTMODE			_IOR('F', 0x4A, __u32)


#ifdef __KERNEL__

/* PW2 */
#define EHWFAULT 901

extern struct fb_videomode mxcfb_modedb[];
extern int mxcfb_modedb_sz;

/* PW2 */
enum panel_modes {
	PANEL_MODE_E60_PINOT = 0,	// NOTE: Was PANEL_MODE_E60_CELESTE in PW2 kernels, appropriately switched to PINOT in 5.6.0.1
	PANEL_MODE_EN060OC1_3CE_225,
	PANEL_MODE_ED060TC1_3CE,

	/* KT2/KV */
	PANEL_MODE_ED060SCN,
	PANEL_MODE_ED060SCP,

	PANEL_MODE_COUNT,
};

/* PW2 */
enum {
	MXC_DISP_SPEC_DEV = 0,
	MXC_DISP_DDC_DEV = 1,
};

enum {
	MXCFB_REFRESH_OFF,
	MXCFB_REFRESH_AUTO,
	MXCFB_REFRESH_PARTIAL,
};

int mxcfb_set_refresh_mode(struct fb_info *fbi, int mode,
			   struct mxcfb_rect *update_region);
int mxc_elcdif_frame_addr_setup(dma_addr_t phys);

/* PW2 */
void mxcfb_elcdif_register_mode(const struct fb_videomode *modedb,
		int num_modes, int dev_mode);

#endif				/* __KERNEL__ */
#endif
