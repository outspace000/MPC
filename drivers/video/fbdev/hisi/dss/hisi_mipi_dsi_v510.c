/*
 * hisi_mipi_dsi_v510.c
 *
 * The Kernel driver of the display mipi dsi module
 *
 * Copyright (c) 2012-2019, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 */

#include "hisi_mipi_dsi.h"
#include "hisi_frame_rate_ctrl.h"

#define VFP_TIME_MASK 0x7fff
#define VFP_TIME_OFFSET 10
#define VFP_DEF_TIME 80
#define MILLION_CONVERT 1000000
#define PCTRL_TRY_TIME 10
#define DSI_CLK_BW 1
#define DSI_CLK_BS 0
#define VCO_CLK_MIN_VALUE (2000)

int mipi_dsi_ulps_cfg(struct hisi_fb_data_type *hisifd, int enable);

/*lint -e834 */
static uint32_t get_data_t_hs_prepare(struct hisi_fb_data_type *hisifd,
	uint32_t accuracy, uint32_t ui)
{
	struct hisi_panel_info *pinfo = NULL;
	uint32_t data_t_hs_prepare = 0;
	uint32_t prepare_val1;
	uint32_t prepare_val2;

	pinfo = &(hisifd->panel_info);

	if (pinfo == NULL) {
		HISI_FB_ERR("pinfo is null.\n");
		return 0;
	}

	if (pinfo->mipi.data_t_hs_prepare_adjust == 0)
		pinfo->mipi.data_t_hs_prepare_adjust = 35;

	prepare_val1 = 400 * accuracy + 4 * ui +
		pinfo->mipi.data_t_hs_prepare_adjust * ui;
	prepare_val2 = 850 * accuracy + 6 * ui - 8 * ui;
	data_t_hs_prepare = (prepare_val1 <= prepare_val2) ?
		prepare_val1 : prepare_val2;

	return data_t_hs_prepare;
}

static uint32_t get_data_pre_delay(uint32_t lp11_flag,
	struct mipi_dsi_phy_ctrl *phy_ctrl, uint32_t clk_pre)
{
	uint32_t data_pre_delay = 0;
	// if use 1080 X 2160 resolution panel,need reduce the lp11 time,
	// and disable noncontinue mode
	if (lp11_flag != MIPI_SHORT_LP11)
		data_pre_delay = phy_ctrl->clk_pre_delay + 2 + phy_ctrl->clk_t_lpx +
			phy_ctrl->clk_t_hs_prepare + phy_ctrl->clk_t_hs_zero + 8 + clk_pre;

	return data_pre_delay;
}

static uint32_t get_data_pre_delay_reality(uint32_t lp11_flag,
	struct mipi_dsi_phy_ctrl *phy_ctrl)
{
	uint32_t data_pre_delay_reality = 0;
	// if use 1080 X 2160 resolution panel,need reduce the lp11 time,
	// and disable noncontinue mode
	if (lp11_flag != MIPI_SHORT_LP11)
		data_pre_delay_reality = phy_ctrl->data_pre_delay + 5;
	return data_pre_delay_reality;
}

static uint32_t get_clk_post_delay_reality(uint32_t lp11_flag,
	struct mipi_dsi_phy_ctrl *phy_ctrl)
{
	uint32_t clk_post_delay_reality = 0;
	// if use 1080 X 2160 resolution panel,need reduce the lp11 time,
	// and disable noncontinue mode
	if (lp11_flag != MIPI_SHORT_LP11)
		clk_post_delay_reality = phy_ctrl->clk_post_delay + 4;
	return clk_post_delay_reality;
}
/*lint -e647 */
static uint64_t get_default_lane_byte_clk(struct hisi_fb_data_type *hisifd)
{
	uint64_t lane_clock;
	int rg_pll_posdiv = 0;
	uint64_t vco_clk;
	uint32_t rg_pll_fbkdiv;
	uint32_t post_div[6] = {1, 2, 4, 8, 16, 32};
	struct hisi_panel_info *pinfo = NULL;

	pinfo = &(hisifd->panel_info);

	if (pinfo->mipi.dsi_bit_clk_default == 0) {
		HISI_FB_WARNING("reset dsi_bit_clk_default %llu M -> %llu M\n",
			pinfo->mipi.dsi_bit_clk_default, pinfo->mipi.dsi_bit_clk);
		pinfo->mipi.dsi_bit_clk_default = pinfo->mipi.dsi_bit_clk;
	}

	lane_clock = (uint64_t)(pinfo->mipi.dsi_bit_clk_default);
	if (pinfo->mipi.phy_mode == DPHY_MODE)
		lane_clock = lane_clock * 2;

	HISI_FB_DEBUG("default lane_clock %llu M\n", lane_clock);

	vco_clk = lane_clock * post_div[rg_pll_posdiv];
	// vcc_clk_min and post_div index
	while ((vco_clk <= 2000) && (rg_pll_posdiv < 5)) {
		rg_pll_posdiv++;
		vco_clk = lane_clock * post_div[rg_pll_posdiv];
	}
	vco_clk = vco_clk * 1000000;
	rg_pll_fbkdiv = vco_clk / DEFAULT_MIPI_CLK_RATE;
	lane_clock = rg_pll_fbkdiv * DEFAULT_MIPI_CLK_RATE / post_div[rg_pll_posdiv];

	HISI_FB_DEBUG("vco_clk %llu, rg_pll_fbkdiv %d, rg_pll_posdiv %d, lane_clock %llu\n",
		vco_clk, rg_pll_fbkdiv, rg_pll_posdiv, lane_clock);

	// lanebyte clk formula which is stated in cdphy spec
	if (pinfo->mipi.phy_mode == DPHY_MODE)
		return lane_clock / 8;
	else
		return lane_clock / 7;
}

void get_dsi_dphy_ctrl(struct hisi_fb_data_type *hisifd,
	struct mipi_dsi_phy_ctrl *phy_ctrl)
{
	struct hisi_panel_info *pinfo = NULL;
#if defined(CONFIG_HISI_DISPLAY_DFR)
	struct mipi_panel_info *mipi = NULL;
#endif
	uint32_t dsi_bit_clk;

	uint32_t ui;
	uint32_t m_pll = 0;
	uint32_t n_pll = 0;
	uint64_t lane_clock;
	uint64_t vco_div = 1;

	uint32_t accuracy;
	uint32_t unit_tx_byte_clk_hs;
	uint32_t clk_post;
	uint32_t clk_pre;
	uint32_t clk_t_hs_exit;
	uint32_t clk_pre_delay;
	uint32_t clk_t_hs_prepare;
	uint32_t clk_t_lpx;
	uint32_t clk_t_hs_zero;
	uint32_t clk_t_hs_trial;
	uint32_t data_post_delay;
	uint32_t data_t_hs_prepare;
	uint32_t data_t_hs_zero;
	uint32_t data_t_hs_trial;
	uint32_t data_t_lpx;
	uint32_t post_div[6] = {1, 2, 4, 8, 16, 32};
	int post_div_idx = 0;
	uint64_t vco_clk = 0;

	pinfo = &(hisifd->panel_info);

#if defined(CONFIG_HISI_DISPLAY_DFR)
	mipi = get_mipi_ctrl(hisifd);
	dsi_bit_clk = mipi->dsi_bit_clk_upt;
#else
	dsi_bit_clk = pinfo->mipi.dsi_bit_clk_upt;
#endif

	lane_clock = (uint64_t)(2 * dsi_bit_clk);
	HISI_FB_INFO("Expected : lane_clock = %llu M\n", lane_clock);

	/************************  PLL parameters config  *********************/
	/* chip spec :
	 * If the output data rate is below 320 Mbps, RG_BNAD_SEL should be set to 1.
	 * At this mode a post divider of 1/4 will be applied to VCO.
	 */
	if (g_fpga_flag) {
		if ((lane_clock >= 320) && (lane_clock <= 2500)) {
			phy_ctrl->rg_band_sel = 0;
			vco_div = 1;
		} else if ((lane_clock >= 80) && (lane_clock < 320)) {
			phy_ctrl->rg_band_sel = 1;
			vco_div = 4;
		} else {
			HISI_FB_ERR("80M <= lane_clock< = 2500M, not support "
				"lane_clock = %llu M\n", lane_clock);
		}

		n_pll = 2;
		m_pll = (uint32_t)(lane_clock * vco_div * n_pll * 1000000UL /
			DEFAULT_MIPI_CLK_RATE);

		lane_clock = m_pll * (DEFAULT_MIPI_CLK_RATE / n_pll) / vco_div;
		if (lane_clock > 750000000)
			phy_ctrl->rg_cp = 3;
		else if ((lane_clock >= 80000000) && (lane_clock <= 750000000))
			phy_ctrl->rg_cp = 1;
		else
			HISI_FB_ERR("80M <= lane_clock< = 2500M, not support "
				"lane_clock = %llu M\n", lane_clock);

		phy_ctrl->rg_pre_div = n_pll - 1;
		phy_ctrl->rg_div = m_pll;
	} else {
		phy_ctrl->rg_pll_prediv = 0;
		vco_clk = lane_clock * post_div[post_div_idx];
		// vcc_clk_min and post_div index
		while ((vco_clk <= VCO_CLK_MIN_VALUE) && (post_div_idx < 5)) {
			post_div_idx++;
			vco_clk = lane_clock * post_div[post_div_idx];
		}
		vco_clk = vco_clk * 1000000;
		phy_ctrl->rg_pll_posdiv = post_div_idx;
		phy_ctrl->rg_pll_fbkdiv = vco_clk / DEFAULT_MIPI_CLK_RATE;

		lane_clock = phy_ctrl->rg_pll_fbkdiv * DEFAULT_MIPI_CLK_RATE /
			post_div[phy_ctrl->rg_pll_posdiv];
		HISI_FB_INFO("rg_pll_prediv=%d, rg_pll_posdiv=%d, rg_pll_fbkdiv=%d\n",
			phy_ctrl->rg_pll_prediv, phy_ctrl->rg_pll_posdiv,
			phy_ctrl->rg_pll_fbkdiv);
	}

	phy_ctrl->rg_0p8v = 0;
	phy_ctrl->rg_2p5g = 1;
	phy_ctrl->rg_320m = 0;
	phy_ctrl->rg_lpf_r = 0;

	// TO DO HSTX select VCM VREF
	phy_ctrl->rg_vrefsel_vcm = 0;
	if (pinfo->mipi.rg_vrefsel_vcm_adjust != 0) {
		phy_ctrl->rg_vrefsel_vcm = pinfo->mipi.rg_vrefsel_vcm_adjust;
		HISI_FB_INFO("rg_vrefsel_vcm=0x%x\n", phy_ctrl->rg_vrefsel_vcm);
	}

	/******************  clock/data lane parameters config  ******************/
	accuracy = 10;
	ui =  (uint32_t)(10 * 1000000000UL * accuracy / lane_clock);
	// unit of measurement
	unit_tx_byte_clk_hs = 8 * ui;

	// D-PHY Specification : 60ns + 52*UI <= clk_post
	clk_post = 600 * accuracy + 52 * ui + unit_tx_byte_clk_hs +
		pinfo->mipi.clk_post_adjust * ui;

	// D-PHY Specification : clk_pre >= 8*UI
	clk_pre = 8 * ui + unit_tx_byte_clk_hs + pinfo->mipi.clk_pre_adjust * ui;

	// D-PHY Specification : clk_t_hs_exit >= 100ns
	clk_t_hs_exit = (uint32_t)(1000 * accuracy + 100 * accuracy +
		pinfo->mipi.clk_t_hs_exit_adjust * ui);

	// clocked by TXBYTECLKHS
	clk_pre_delay = 0 + pinfo->mipi.clk_pre_delay_adjust * ui;

	// D-PHY Specification : clk_t_hs_trial >= 60ns
	// clocked by TXBYTECLKHS
	clk_t_hs_trial = 600 * accuracy + 3 * unit_tx_byte_clk_hs +
		pinfo->mipi.clk_t_hs_trial_adjust * ui;

	// D-PHY Specification : 38ns <= clk_t_hs_prepare <= 95ns
	// clocked by TXBYTECLKHS
	clk_t_hs_prepare = 660 * accuracy;

	// clocked by TXBYTECLKHS
	data_post_delay = 0 + pinfo->mipi.data_post_delay_adjust * ui;

	// D-PHY Specification : data_t_hs_trial >= max( n*8*UI, 60ns + n*4*UI ),
	// n = 1. clocked by TXBYTECLKHS
	data_t_hs_trial = ((600 * accuracy + 4 * ui) >= (8 * ui) ?
		(600 * accuracy + 4 * ui) : (8 * ui)) + 8 * ui +
		3 * unit_tx_byte_clk_hs + pinfo->mipi.data_t_hs_trial_adjust * ui;

	// D-PHY Specification : 40ns + 4*UI <= data_t_hs_prepare <= 85ns + 6*UI
	// clocked by TXBYTECLKHS
	data_t_hs_prepare = get_data_t_hs_prepare(hisifd, accuracy, ui);
	// D-PHY chip spec : clk_t_lpx + clk_t_hs_prepare > 200ns
	// D-PHY Specification : clk_t_lpx >= 50ns
	// clocked by TXBYTECLKHS
	clk_t_lpx = (uint32_t)(2000 * accuracy + 10 * accuracy +
		pinfo->mipi.clk_t_lpx_adjust * ui - clk_t_hs_prepare);

	// D-PHY Specification : clk_t_hs_zero + clk_t_hs_prepare >= 300 ns
	// clocked by TXBYTECLKHS
	clk_t_hs_zero = (uint32_t)(3000 * accuracy + 3 * unit_tx_byte_clk_hs +
		pinfo->mipi.clk_t_hs_zero_adjust * ui - clk_t_hs_prepare);

	// D-PHY chip spec : data_t_lpx + data_t_hs_prepare > 200ns
	// D-PHY Specification : data_t_lpx >= 50ns
	// clocked by TXBYTECLKHS
	data_t_lpx = (uint32_t)(2000 * accuracy + 10 * accuracy +
		pinfo->mipi.data_t_lpx_adjust * ui - data_t_hs_prepare);

	// D-PHY Specification : data_t_hs_zero + data_t_hs_prepare >= 145ns + 10*UI
	// clocked by TXBYTECLKHS
	data_t_hs_zero = (uint32_t)(1450 * accuracy + 10 * ui +
		3 * unit_tx_byte_clk_hs + pinfo->mipi.data_t_hs_zero_adjust * ui -
		data_t_hs_prepare);

	phy_ctrl->clk_pre_delay = round1(clk_pre_delay, unit_tx_byte_clk_hs);
	phy_ctrl->clk_t_hs_prepare = round1(clk_t_hs_prepare, unit_tx_byte_clk_hs);
	phy_ctrl->clk_t_lpx = round1(clk_t_lpx, unit_tx_byte_clk_hs);
	phy_ctrl->clk_t_hs_zero = round1(clk_t_hs_zero, unit_tx_byte_clk_hs);
	phy_ctrl->clk_t_hs_trial = round1(clk_t_hs_trial, unit_tx_byte_clk_hs);

	phy_ctrl->data_post_delay = round1(data_post_delay, unit_tx_byte_clk_hs);
	phy_ctrl->data_t_hs_prepare = round1(data_t_hs_prepare, unit_tx_byte_clk_hs);
	phy_ctrl->data_t_lpx = round1(data_t_lpx, unit_tx_byte_clk_hs);
	phy_ctrl->data_t_hs_zero = round1(data_t_hs_zero, unit_tx_byte_clk_hs);
	phy_ctrl->data_t_hs_trial = round1(data_t_hs_trial, unit_tx_byte_clk_hs);

	phy_ctrl->clk_post_delay = phy_ctrl->data_t_hs_trial +
		round1(clk_post, unit_tx_byte_clk_hs);
	phy_ctrl->data_pre_delay = get_data_pre_delay(pinfo->mipi.lp11_flag,
		phy_ctrl, round1(clk_pre, unit_tx_byte_clk_hs));

	phy_ctrl->clk_lane_lp2hs_time = phy_ctrl->clk_pre_delay +
		phy_ctrl->clk_t_lpx + phy_ctrl->clk_t_hs_prepare +
		phy_ctrl->clk_t_hs_zero + 5 + 7;
	phy_ctrl->clk_lane_hs2lp_time = phy_ctrl->clk_t_hs_trial +
		phy_ctrl->clk_post_delay + 8 + 4;
	phy_ctrl->data_lane_lp2hs_time =
		get_data_pre_delay_reality(pinfo->mipi.lp11_flag, phy_ctrl) +
		phy_ctrl->data_t_lpx + phy_ctrl->data_t_hs_prepare +
		phy_ctrl->data_t_hs_zero + pinfo->mipi.data_lane_lp2hs_time_adjust + 7;

	phy_ctrl->data_lane_hs2lp_time = phy_ctrl->data_t_hs_trial + 8 + 5;

	phy_ctrl->phy_stop_wait_time =
		get_clk_post_delay_reality(pinfo->mipi.lp11_flag, phy_ctrl) +
		phy_ctrl->clk_t_hs_trial + round1(clk_t_hs_exit, unit_tx_byte_clk_hs) -
		(phy_ctrl->data_post_delay + 4 + phy_ctrl->data_t_hs_trial) + 3;

	phy_ctrl->lane_byte_clk = lane_clock / 8;
	phy_ctrl->clk_division =
		(((phy_ctrl->lane_byte_clk / 2) % pinfo->mipi.max_tx_esc_clk) > 0) ?
		(uint32_t)(phy_ctrl->lane_byte_clk / 2 / pinfo->mipi.max_tx_esc_clk + 1) :
		(uint32_t)(phy_ctrl->lane_byte_clk / 2 / pinfo->mipi.max_tx_esc_clk);

	phy_ctrl->lane_byte_clk_default = get_default_lane_byte_clk(hisifd);

	HISI_FB_INFO("DPHY clock_lane and data_lane config :\n"
		"lane_clock = %llu, n_pll=%u, m_pll=%u\n"
		"rg_cp=%u\n"
		"rg_band_sel=%u\n"
		"rg_vrefsel_vcm=%u\n"
		"clk_pre_delay=%u\n"
		"clk_post_delay=%u\n"
		"clk_t_hs_prepare=%u\n"
		"clk_t_lpx=%u\n"
		"clk_t_hs_zero=%u\n"
		"clk_t_hs_trial=%u\n"
		"data_pre_delay=%u\n"
		"data_post_delay=%u\n"
		"data_t_hs_prepare=%u\n"
		"data_t_lpx=%u\n"
		"data_t_hs_zero=%u\n"
		"data_t_hs_trial=%u\n"
		"clk_lane_lp2hs_time=%u\n"
		"clk_lane_hs2lp_time=%u\n"
		"data_lane_lp2hs_time=%u\n"
		"data_lane_hs2lp_time=%u\n"
		"phy_stop_wait_time=%u\n",
		lane_clock, n_pll, m_pll,
		pinfo->dsi_phy_ctrl.rg_cp,
		pinfo->dsi_phy_ctrl.rg_band_sel,
		phy_ctrl->rg_vrefsel_vcm,
		phy_ctrl->clk_pre_delay,
		phy_ctrl->clk_post_delay,
		phy_ctrl->clk_t_hs_prepare,
		phy_ctrl->clk_t_lpx,
		phy_ctrl->clk_t_hs_zero,
		phy_ctrl->clk_t_hs_trial,
		phy_ctrl->data_pre_delay,
		phy_ctrl->data_post_delay,
		phy_ctrl->data_t_hs_prepare,
		phy_ctrl->data_t_lpx,
		phy_ctrl->data_t_hs_zero,
		phy_ctrl->data_t_hs_trial,
		phy_ctrl->clk_lane_lp2hs_time,
		phy_ctrl->clk_lane_hs2lp_time,
		phy_ctrl->data_lane_lp2hs_time,
		phy_ctrl->data_lane_hs2lp_time,
		phy_ctrl->phy_stop_wait_time);
}
/*lint +e647 */

void get_dsi_cphy_ctrl(struct hisi_fb_data_type *hisifd,
	struct mipi_dsi_phy_ctrl *phy_ctrl)
{
	struct hisi_panel_info *pinfo = NULL;
#if defined(CONFIG_HISI_DISPLAY_DFR)
	struct mipi_panel_info *mipi = NULL;
#endif
	uint32_t ui;
	uint32_t m_pll = 0;
	uint32_t n_pll = 0;
	uint64_t lane_clock;
	uint64_t vco_div = 1;

	uint32_t accuracy;
	uint32_t unit_tx_word_clk_hs;
	uint32_t post_div[6] = {1, 2, 4, 8, 16, 32};
	int post_div_idx = 0;
	uint32_t vco_clk = 0;

	pinfo = &(hisifd->panel_info);
#if defined(CONFIG_HISI_DISPLAY_DFR)
	mipi = get_mipi_ctrl(hisifd);
	lane_clock = mipi->dsi_bit_clk_upt;
#else
	lane_clock = pinfo->mipi.dsi_bit_clk_upt;
#endif
	HISI_FB_INFO("Expected : lane_clock = %llu M\n", lane_clock);

	/************************  PLL parameters config  *********************/
	if (g_fpga_flag) {
		// C PHY Data rate range is from 1500 Mbps to 40 Mbps
		if ((lane_clock >= 320) && (lane_clock <= 1500)) {
			phy_ctrl->rg_cphy_div = 0;
			vco_div = 1;
		} else if ((lane_clock >= 160) && (lane_clock < 320)) {
			phy_ctrl->rg_cphy_div = 1;
			vco_div = 2;
		} else if ((lane_clock >= 80) && (lane_clock < 160)) {
			phy_ctrl->rg_cphy_div = 2;
			vco_div = 4;
		} else if ((lane_clock >= 40) && (lane_clock < 80)) {
			phy_ctrl->rg_cphy_div = 3;
			vco_div = 8;
		} else {
			HISI_FB_ERR("40M <= lane_clock< = 1500M, not support "
				"lane_clock = %llu M\n", lane_clock);
		}

		n_pll = 2;
		m_pll = (uint32_t)(lane_clock * vco_div * n_pll * 1000000UL /
			DEFAULT_MIPI_CLK_RATE);

		lane_clock = m_pll * (DEFAULT_MIPI_CLK_RATE / n_pll) / vco_div;
		if (lane_clock > 750000000)
			phy_ctrl->rg_cp = 3;
		else if ((lane_clock >= 40000000) && (lane_clock <= 750000000))
			phy_ctrl->rg_cp = 1;
		else
			HISI_FB_ERR("40M <= lane_clock< = 1500M, not support "
			"lane_clock = %llu M\n", lane_clock);

		phy_ctrl->rg_pre_div = n_pll - 1;
		phy_ctrl->rg_div = m_pll;
	} else {
		phy_ctrl->rg_pll_prediv = 0;
		vco_clk = lane_clock * post_div[post_div_idx];
		while ((vco_clk <= VCO_CLK_MIN_VALUE) && (post_div_idx < 5)) {
			post_div_idx++;
			vco_clk = lane_clock * post_div[post_div_idx];
		}
		vco_clk = vco_clk * 1000000;
		phy_ctrl->rg_pll_posdiv = post_div_idx;
		phy_ctrl->rg_pll_fbkdiv = vco_clk / DEFAULT_MIPI_CLK_RATE;
		lane_clock = phy_ctrl->rg_pll_fbkdiv * DEFAULT_MIPI_CLK_RATE /
			post_div[phy_ctrl->rg_pll_posdiv];
		HISI_FB_INFO("rg_pll_prediv=%d, rg_pll_posdiv=%d, rg_pll_fbkdiv=%d\n",
			phy_ctrl->rg_pll_prediv, phy_ctrl->rg_pll_posdiv,
			phy_ctrl->rg_pll_fbkdiv);
	}

	phy_ctrl->rg_0p8v = 0;
	phy_ctrl->rg_2p5g = 1;
	phy_ctrl->rg_320m = 0;
	phy_ctrl->rg_lpf_r = 0;

	/* TO DO HSTX select VCM VREF */
	phy_ctrl->rg_vrefsel_vcm = 0x51;

	/********************  data lane parameters config  ******************/
	accuracy = 10;
	ui = (uint32_t)(10 * 1000000000UL * accuracy / lane_clock);
	/* unit of measurement */
	unit_tx_word_clk_hs = 7 * ui;

	if (pinfo->mipi.mininum_phy_timing_flag == 1) {
		/* CPHY Specification: 38ns <= t3_prepare <= 95ns */
		phy_ctrl->t_prepare = MIN_T3_PREPARE_PARAM * accuracy;

		/* CPHY Specification: 50ns <= t_lpx */
		phy_ctrl->t_lpx = MIN_T3_LPX_PARAM * accuracy + 8 * ui - unit_tx_word_clk_hs;

		/* CPHY Specification: 7*UI <= t_prebegin <= 448UI */
		phy_ctrl->t_prebegin = MIN_T3_PREBEGIN_PARAM * ui - unit_tx_word_clk_hs;

		/* CPHY Specification: 7*UI <= t_post <= 224*UI */
		phy_ctrl->t_post = MIN_T3_POST_PARAM * ui - unit_tx_word_clk_hs;
	} else {
		/* CPHY Specification: 38ns <= t3_prepare <= 95ns */
		/* 380 * accuracy - unit_tx_word_clk_hs; */
		phy_ctrl->t_prepare = T3_PREPARE_PARAM * accuracy;

		/* CPHY Specification: 50ns <= t_lpx */
		phy_ctrl->t_lpx =  T3_LPX_PARAM * accuracy + 8 * ui - unit_tx_word_clk_hs;

		/* CPHY Specification: 7*UI <= t_prebegin <= 448UI */
		phy_ctrl->t_prebegin =  T3_PREBEGIN_PARAM * ui - unit_tx_word_clk_hs;

		/* CPHY Specification: 7*UI <= t_post <= 224*UI */
		phy_ctrl->t_post = T3_POST_PARAM * ui - unit_tx_word_clk_hs;
	}

	phy_ctrl->t_prepare = round1(phy_ctrl->t_prepare, unit_tx_word_clk_hs);
	phy_ctrl->t_lpx = round1(phy_ctrl->t_lpx, unit_tx_word_clk_hs);
	phy_ctrl->t_prebegin = round1(phy_ctrl->t_prebegin, unit_tx_word_clk_hs);
	phy_ctrl->t_post = round1(phy_ctrl->t_post, unit_tx_word_clk_hs);

	phy_ctrl->data_lane_lp2hs_time = phy_ctrl->t_lpx + phy_ctrl->t_prepare +
		phy_ctrl->t_prebegin + 5 + 17;
	phy_ctrl->data_lane_hs2lp_time = phy_ctrl->t_post + 8 + 5;

	phy_ctrl->lane_word_clk = lane_clock / 7;
	phy_ctrl->clk_division =
		(((phy_ctrl->lane_word_clk / 2) % pinfo->mipi.max_tx_esc_clk) > 0) ?
		(uint32_t)(phy_ctrl->lane_word_clk / 2 / pinfo->mipi.max_tx_esc_clk + 1) :
		(uint32_t)(phy_ctrl->lane_word_clk / 2 / pinfo->mipi.max_tx_esc_clk);

	phy_ctrl->phy_stop_wait_time = phy_ctrl->t_post + 8 + 5;
	phy_ctrl->lane_byte_clk_default = get_default_lane_byte_clk(hisifd);

	HISI_FB_INFO("CPHY clock_lane and data_lane config :\n"
		"lane_clock=%llu, n_pll=%u, m_pll=%u\n"
		"rg_cphy_div=%u\n"
		"rg_cp=%u\n"
		"rg_vrefsel_vcm=%u\n"
		"t_prepare=%u\n"
		"t_lpx=%u\n"
		"t_prebegin=%u\n"
		"t_post=%u\n"
		"lane_word_clk=%llu\n"
		"data_lane_lp2hs_time=%u\n"
		"data_lane_hs2lp_time=%u\n"
		"clk_division=%u\n"
		"phy_stop_wait_time=%u\n",
		lane_clock, n_pll, m_pll,
		phy_ctrl->rg_cphy_div,
		phy_ctrl->rg_cp,
		phy_ctrl->rg_vrefsel_vcm,
		phy_ctrl->t_prepare,
		phy_ctrl->t_lpx,
		phy_ctrl->t_prebegin,
		phy_ctrl->t_post,
		phy_ctrl->lane_word_clk,
		phy_ctrl->data_lane_lp2hs_time,
		phy_ctrl->data_lane_hs2lp_time,
		phy_ctrl->clk_division,
		phy_ctrl->phy_stop_wait_time);
}
/* lint +e834 */
static uint32_t mipi_pixel_clk(struct hisi_fb_data_type *hisifd)
{
	struct hisi_panel_info *pinfo = NULL;

	pinfo = &(hisifd->panel_info); //lint !e838
	if ((pinfo->pxl_clk_rate_div == 0) || (g_fpga_flag == 1))
		return (uint32_t)pinfo->pxl_clk_rate;

	if ((pinfo->ifbc_type == IFBC_TYPE_NONE) &&
		!is_dual_mipi_panel(hisifd))
		pinfo->pxl_clk_rate_div = 1;

	return (uint32_t)pinfo->pxl_clk_rate / pinfo->pxl_clk_rate_div;
}
/*lint -e715*/
void mipi_config_phy_test_code(char __iomem *mipi_dsi_base,
	uint32_t test_code_addr, uint32_t test_code_parameter)
{
	outp32(mipi_dsi_base + MIPIDSI_PHY_TST_CTRL1_OFFSET, test_code_addr);
	outp32(mipi_dsi_base + MIPIDSI_PHY_TST_CTRL0_OFFSET, 0x00000002);
	outp32(mipi_dsi_base + MIPIDSI_PHY_TST_CTRL0_OFFSET, 0x00000000);
	outp32(mipi_dsi_base + MIPIDSI_PHY_TST_CTRL1_OFFSET, test_code_parameter);
	outp32(mipi_dsi_base + MIPIDSI_PHY_TST_CTRL0_OFFSET, 0x00000002);
	outp32(mipi_dsi_base + MIPIDSI_PHY_TST_CTRL0_OFFSET, 0x00000000);
}
/*lint +e715*/
void mipi_config_cphy_spec1v0_parameter(char __iomem *mipi_dsi_base,
	struct hisi_panel_info *pinfo, const struct mipi_dsi_phy_ctrl *phy_ctrl)
{
	uint32_t i;
	uint32_t addr = 0;

	for (i = 0; i <= pinfo->mipi.lane_nums; i++) {
		if (g_fpga_flag) {
			// Lane Transmission Property
			addr = MIPIDSI_PHY_TST_LANE_TRANSMISSION_PROPERTY + (i << 5);
			mipi_config_phy_test_code(mipi_dsi_base, addr, 0x43);
		}

		// Lane Timing Control - DPHY: THS-PREPARE/CPHY: T3-PREPARE
		addr = MIPIDSI_PHY_TST_DATA_PREPARE + (i << 5);

		mipi_config_phy_test_code(mipi_dsi_base, addr, dss_reduce(phy_ctrl->t_prepare));

		// Lane Timing Control - TLPX
		addr = MIPIDSI_PHY_TST_DATA_TLPX + (i << 5);
		mipi_config_phy_test_code(mipi_dsi_base, addr, dss_reduce(phy_ctrl->t_lpx));
	}
}

void mipi_config_dphy_spec1v2_parameter(char __iomem *mipi_dsi_base,
	struct hisi_panel_info *pinfo, const struct mipi_dsi_phy_ctrl *phy_ctrl)
{
	uint32_t i;
	uint32_t addr = 0;

	for (i = 0; i <= (pinfo->mipi.lane_nums + 1); i++) {
		// Lane Transmission Property
		addr = MIPIDSI_PHY_TST_LANE_TRANSMISSION_PROPERTY + (i << 5);
		mipi_config_phy_test_code(mipi_dsi_base, addr, 0x43);
	}

	//pre_delay of clock lane request setting
	mipi_config_phy_test_code(mipi_dsi_base, MIPIDSI_PHY_TST_CLK_PRE_DELAY,
		dss_reduce(phy_ctrl->clk_pre_delay));

	//post_delay of clock lane request setting
	mipi_config_phy_test_code(mipi_dsi_base, MIPIDSI_PHY_TST_CLK_POST_DELAY,
		dss_reduce(phy_ctrl->clk_post_delay));

	//clock lane timing ctrl - t_lpx
	mipi_config_phy_test_code(mipi_dsi_base, MIPIDSI_PHY_TST_CLK_TLPX,
		dss_reduce(phy_ctrl->clk_t_lpx));

	//clock lane timing ctrl - t_hs_prepare
	mipi_config_phy_test_code(mipi_dsi_base, MIPIDSI_PHY_TST_CLK_PREPARE,
		dss_reduce(phy_ctrl->clk_t_hs_prepare));

	//clock lane timing ctrl - t_hs_zero
	mipi_config_phy_test_code(mipi_dsi_base, MIPIDSI_PHY_TST_CLK_ZERO,
		dss_reduce(phy_ctrl->clk_t_hs_zero));

	//clock lane timing ctrl - t_hs_trial
	mipi_config_phy_test_code(mipi_dsi_base, MIPIDSI_PHY_TST_CLK_TRAIL,
		dss_reduce(phy_ctrl->clk_t_hs_trial));

	for (i = 0; i <= (pinfo->mipi.lane_nums + 1); i++) {//lint !e850
		if (i == 2)
			i++; // addr: lane0:0x60; lane1:0x80; lane2:0xC0; lane3:0xE0

		// data lane pre_delay
		addr = MIPIDSI_PHY_TST_DATA_PRE_DELAY + (i << 5);
		mipi_config_phy_test_code(mipi_dsi_base, addr, dss_reduce(phy_ctrl->data_pre_delay));

		// data lane post_delay
		addr = MIPIDSI_PHY_TST_DATA_POST_DELAY + (i << 5);
		mipi_config_phy_test_code(mipi_dsi_base, addr, dss_reduce(phy_ctrl->data_post_delay));

		// data lane timing ctrl - t_lpx
		addr = MIPIDSI_PHY_TST_DATA_TLPX + (i << 5);
		mipi_config_phy_test_code(mipi_dsi_base, addr, dss_reduce(phy_ctrl->data_t_lpx));

		// data lane timing ctrl - t_hs_prepare
		addr = MIPIDSI_PHY_TST_DATA_PREPARE + (i << 5);
		mipi_config_phy_test_code(mipi_dsi_base, addr, dss_reduce(phy_ctrl->data_t_hs_prepare));

		// data lane timing ctrl - t_hs_zero
		addr = MIPIDSI_PHY_TST_DATA_ZERO + (i << 5);
		mipi_config_phy_test_code(mipi_dsi_base, addr, dss_reduce(phy_ctrl->data_t_hs_zero));

		// data lane timing ctrl - t_hs_trial
		addr = MIPIDSI_PHY_TST_DATA_TRAIL + (i << 5);
		mipi_config_phy_test_code(mipi_dsi_base, addr, dss_reduce(phy_ctrl->data_t_hs_trial));


		HISI_FB_INFO("DPHY spec1v2 config :\n"
			"addr=0x%x\n"
			"clk_pre_delay=%u\n"
			"clk_t_hs_trial=%u\n"
			"data_t_hs_zero=%u\n"
			"data_t_lpx=%u\n"
			"data_t_hs_prepare=%u\n",
			addr,
			phy_ctrl->clk_pre_delay,
			phy_ctrl->clk_t_hs_trial,
			phy_ctrl->data_t_hs_zero,
			phy_ctrl->data_t_lpx,
			phy_ctrl->data_t_hs_prepare);
	}
}

static void mipi_cdphy_init_config(
	char __iomem *mipi_dsi_base, struct hisi_panel_info *pinfo)
{
	if (pinfo->mipi.phy_mode == CPHY_MODE) {
		if (pinfo->mipi.mininum_phy_timing_flag == 1) {
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010001, MIN_T3_PREBEGIN_PHY_TIMING); // T3-PREBEGIN
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010002, MIN_T3_POST_PHY_TIMING); // T3-POST
		} else {
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010001, T3_PREBEGIN_PHY_TIMING);// T3-PREBEGIN
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010002, T3_POST_PHY_TIMING);// T3-POST
		}
		mipi_config_phy_test_code(mipi_dsi_base, 0x00010042, 0x21);
		if (g_fpga_flag) {
			// PLL configuration I
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010046,
				pinfo->dsi_phy_ctrl.rg_cp + (pinfo->dsi_phy_ctrl.rg_lpf_r << 4));

			// PLL configuration II
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010048,
				pinfo->dsi_phy_ctrl.rg_0p8v +
				(pinfo->dsi_phy_ctrl.rg_2p5g << 1) +
				(pinfo->dsi_phy_ctrl.rg_320m << 2) +
				(pinfo->dsi_phy_ctrl.rg_band_sel << 3) +
				(pinfo->dsi_phy_ctrl.rg_cphy_div << 4));

			// PLL configuration III
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010049,
				pinfo->dsi_phy_ctrl.rg_pre_div);

			// PLL configuration IV
			mipi_config_phy_test_code(mipi_dsi_base, 0x0001004A,
				pinfo->dsi_phy_ctrl.rg_div);
		} else {
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010049,
				(pinfo->dsi_phy_ctrl.rg_pll_posdiv << 4) |
				pinfo->dsi_phy_ctrl.rg_pll_prediv);
			mipi_config_phy_test_code(mipi_dsi_base, 0x0001004A,
				pinfo->dsi_phy_ctrl.rg_pll_fbkdiv);
		}

		if (g_fpga_flag) {
			mipi_config_phy_test_code(mipi_dsi_base, 0x0001004F, 0xf0);
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010052, 0xa8);
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010053, 0xc2);
		}

		mipi_config_phy_test_code(mipi_dsi_base, 0x00010058,
			(0x4 + pinfo->mipi.lane_nums) << 4 | 0);
		mipi_config_phy_test_code(mipi_dsi_base, 0x0001005B, 0x19);
		// PLL update control
		mipi_config_phy_test_code(mipi_dsi_base, 0x0001004B, 0x1);

		//set cphy spec parameter
		mipi_config_cphy_spec1v0_parameter(mipi_dsi_base, pinfo, &pinfo->dsi_phy_ctrl);
	} else {
		mipi_config_phy_test_code(mipi_dsi_base, 0x00010042, 0x21);
		if (g_fpga_flag) {
			// PLL configuration I
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010046,
				pinfo->dsi_phy_ctrl.rg_cp + (pinfo->dsi_phy_ctrl.rg_lpf_r << 4));
			// PLL configuration II
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010048,
				pinfo->dsi_phy_ctrl.rg_0p8v +
				(pinfo->dsi_phy_ctrl.rg_2p5g << 1) +
				(pinfo->dsi_phy_ctrl.rg_320m << 2) +
				(pinfo->dsi_phy_ctrl.rg_band_sel << 3));
			// PLL configuration III
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010049,
				pinfo->dsi_phy_ctrl.rg_pre_div);
			// PLL configuration IV
			mipi_config_phy_test_code(mipi_dsi_base, 0x0001004A,
				pinfo->dsi_phy_ctrl.rg_div);
		} else {
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010049,
				(pinfo->dsi_phy_ctrl.rg_pll_posdiv << 4) |
				pinfo->dsi_phy_ctrl.rg_pll_prediv);
			mipi_config_phy_test_code(mipi_dsi_base, 0x0001004A,
				pinfo->dsi_phy_ctrl.rg_pll_fbkdiv);
		}

		if (g_fpga_flag) {
			mipi_config_phy_test_code(mipi_dsi_base, 0x0001004F, 0xf0);
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010050, 0xc0);
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010051, 0x22);
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010053,
				pinfo->dsi_phy_ctrl.rg_vrefsel_vcm);
		}
		mipi_config_phy_test_code(mipi_dsi_base, 0x0001005B,
			pinfo->dsi_phy_ctrl.rg_vrefsel_vcm);
		// PLL update control
		mipi_config_phy_test_code(mipi_dsi_base, 0x0001004B, 0x1);

		//set dphy spec parameter
		mipi_config_dphy_spec1v2_parameter(mipi_dsi_base, pinfo, &pinfo->dsi_phy_ctrl);
	}

}

static uint32_t mipi_get_cmp_stopstate_value(
	struct hisi_panel_info *pinfo)
{
	uint32_t cmp_stopstate_val = 0;

	if (pinfo->mipi.lane_nums >= DSI_4_LANES)
		cmp_stopstate_val = (BIT(4) | BIT(7) | BIT(9) | BIT(11));
	else if (pinfo->mipi.lane_nums >= DSI_3_LANES)
		cmp_stopstate_val = (BIT(4) | BIT(7) | BIT(9));
	else if (pinfo->mipi.lane_nums >= DSI_2_LANES)
		cmp_stopstate_val = (BIT(4) | BIT(7));
	else
		cmp_stopstate_val = (BIT(4));

	return cmp_stopstate_val;
}

static bool mipi_phy_status_check(const char __iomem *mipi_dsi_base,
	uint32_t expected_value)
{
	bool is_ready = false;
	unsigned long dw_jiffies = 0;
	uint32_t tmp = 0;

	dw_jiffies = jiffies + HZ / 2;
	do {
		tmp = inp32(mipi_dsi_base + MIPIDSI_PHY_STATUS_OFFSET);
		if ((tmp & expected_value) == expected_value) {
			is_ready = true;
			break;
		}
	} while (time_after(dw_jiffies, jiffies));

	HISI_FB_DEBUG("MIPIDSI_PHY_STATUS_OFFSET=0x%x.\n", tmp);
	return is_ready;
}

static void get_mipi_dsi_timing(struct hisi_fb_data_type *hisifd)
{
	dss_rect_t rect;
	uint64_t pixel_clk;
	uint64_t lane_byte_clk;
	struct hisi_panel_info *pinfo = NULL;

	pinfo = &(hisifd->panel_info); //lint !e838

	rect.x = 0;
	rect.y = 0;
	rect.w = pinfo->xres; //lint !e713
	rect.h = pinfo->yres; //lint !e713
	mipi_ifbc_get_rect(hisifd, &rect);
#ifdef SUPPORT_SPR_DSC
	rect.w = get_hsize_after_spr_dsc(hisifd, rect.w);
#endif

	pinfo->mipi.width = rect.w;
	pinfo->mipi.vactive_line = pinfo->yres;

	if (pinfo->mipi.dsi_timing_support)
		return;

	pixel_clk = mipi_pixel_clk(hisifd);
	if (pixel_clk == 0)
		return;

	lane_byte_clk = (pinfo->mipi.phy_mode == DPHY_MODE) ?
		pinfo->dsi_phy_ctrl.lane_byte_clk : pinfo->dsi_phy_ctrl.lane_word_clk;
	/*lint -e737 -e776 -e712*/
	pinfo->mipi.hsa = round1(pinfo->ldi.h_pulse_width * lane_byte_clk,
		pixel_clk);
	pinfo->mipi.hbp = round1(pinfo->ldi.h_back_porch * lane_byte_clk,
		pixel_clk);
	pinfo->mipi.hline_time = round1((pinfo->ldi.h_pulse_width +
		pinfo->ldi.h_back_porch + pinfo->mipi.width +
		pinfo->ldi.h_front_porch) * lane_byte_clk,
		pixel_clk);
	pinfo->mipi.dpi_hsize = round1(pinfo->mipi.width * lane_byte_clk,
		pixel_clk);
	/*lint +e737 +e776 +e712*/

	pinfo->mipi.vsa = pinfo->ldi.v_pulse_width;
	pinfo->mipi.vbp = pinfo->ldi.v_back_porch;
	pinfo->mipi.vfp = pinfo->ldi.v_front_porch;

	HISI_FB_DEBUG("lane_byte_clk_default %llu M, htiming: %d, %d, %d, %d\n",
		pinfo->dsi_phy_ctrl.lane_byte_clk_default, pinfo->mipi.hsa,
		pinfo->mipi.hbp, pinfo->mipi.hline_time, pinfo->mipi.dpi_hsize);
}

uint32_t get_mipi_timing_hline_time(
	struct hisi_fb_data_type *hisifd, uint32_t object_hline_time)
{
	uint64_t lane_byte_clk;
	uint32_t tmp_hline_time;
	struct hisi_panel_info *pinfo = &(hisifd->panel_info);

	lane_byte_clk = (pinfo->mipi.phy_mode == DPHY_MODE) ?
		pinfo->dsi_phy_ctrl.lane_byte_clk : pinfo->dsi_phy_ctrl.lane_word_clk;
	if (lane_byte_clk == pinfo->dsi_phy_ctrl.lane_byte_clk_default) {
		tmp_hline_time = object_hline_time;//pinfo->mipi.hline_time;
	} else {
		if (pinfo->dsi_phy_ctrl.lane_byte_clk_default == 0) {
			pinfo->dsi_phy_ctrl.lane_byte_clk_default =
				get_default_lane_byte_clk(hisifd);
			HISI_FB_ERR("change lane_byte_clk_default to %llu M\n",
				pinfo->dsi_phy_ctrl.lane_byte_clk_default);
		}

		tmp_hline_time = (uint32_t)round1(object_hline_time * lane_byte_clk,
			pinfo->dsi_phy_ctrl.lane_byte_clk_default);
	}

	HISI_FB_INFO("hline_time = %d", tmp_hline_time);
	return tmp_hline_time;
}

static void get_mipi_dsi_timing_config_para(
	struct hisi_fb_data_type *hisifd, struct mipi_dsi_phy_ctrl *phy_ctrl,
	struct mipi_dsi_timing *timing)
{
	uint64_t lane_byte_clk;
	struct hisi_panel_info *pinfo;
	uint32_t tmp_hline_time;

	pinfo = &(hisifd->panel_info);//lint !e838

	if (timing == NULL || pinfo == NULL) {
		HISI_FB_ERR("timing or pinfo is null\n");
		return;
	}

	if (pinfo->dfr_support) {
		if (hisifd->panel_info.fps == FPS_60HZ) {
			tmp_hline_time = pinfo->mipi.hline_time;
		} else {
			tmp_hline_time = hisifd->panel_info.mipi_updt.hline_time;
		}
	} else {
		tmp_hline_time = pinfo->mipi.hline_time;
	}

	lane_byte_clk = (pinfo->mipi.phy_mode == DPHY_MODE) ?
		phy_ctrl->lane_byte_clk : phy_ctrl->lane_word_clk;

	if (lane_byte_clk == pinfo->dsi_phy_ctrl.lane_byte_clk_default) {
		timing->hsa = pinfo->mipi.hsa;
		timing->hbp = pinfo->mipi.hbp;
		timing->hline_time = tmp_hline_time;
	} else {
		if (pinfo->dsi_phy_ctrl.lane_byte_clk_default == 0) {
			pinfo->dsi_phy_ctrl.lane_byte_clk_default =
				get_default_lane_byte_clk(hisifd);
			HISI_FB_ERR("change lane_byte_clk_default to %llu M\n",
				pinfo->dsi_phy_ctrl.lane_byte_clk_default);
		}

		timing->hsa = (uint32_t)round1(pinfo->mipi.hsa * lane_byte_clk,
			pinfo->dsi_phy_ctrl.lane_byte_clk_default);
		timing->hbp = (uint32_t)round1(pinfo->mipi.hbp * lane_byte_clk,
			pinfo->dsi_phy_ctrl.lane_byte_clk_default);
		timing->hline_time = (uint32_t)round1(tmp_hline_time * lane_byte_clk,
			pinfo->dsi_phy_ctrl.lane_byte_clk_default);
	}

	timing->dpi_hsize = pinfo->mipi.dpi_hsize;
	timing->width = pinfo->mipi.width;
	timing->vsa = pinfo->mipi.vsa;
	timing->vbp = pinfo->mipi.vbp;
	timing->vfp = pinfo->mipi.vfp;
	timing->vactive_line = pinfo->mipi.vactive_line;

	if (pinfo->dfr_support)
		pinfo->frm_rate_ctrl.current_hline_time = timing->hline_time;

	HISI_FB_DEBUG("lanebyteclk: %llu M, %llu M, htiming: %d, %d, %d, %d. "
		"new: %d, %d, %d, %d\n",
		lane_byte_clk, pinfo->dsi_phy_ctrl.lane_byte_clk_default,
		pinfo->mipi.hsa, pinfo->mipi.hbp, tmp_hline_time,
		pinfo->mipi.dpi_hsize, timing->hsa, timing->hbp, timing->hline_time,
		timing->dpi_hsize);
}

/*lint -e712 -e737*/
static void mipi_ldi_init(struct hisi_fb_data_type *hisifd,
	char __iomem *mipi_dsi_base)
{
	uint64_t lane_byte_clk;
	struct hisi_panel_info *pinfo = NULL;
	struct mipi_dsi_timing timing;

	pinfo = &(hisifd->panel_info);
	if (pinfo->mipi.phy_mode == CPHY_MODE)
		lane_byte_clk = pinfo->dsi_phy_ctrl.lane_word_clk;
	else
		lane_byte_clk = pinfo->dsi_phy_ctrl.lane_byte_clk;

	memset(&timing, 0, sizeof(timing));
	get_mipi_dsi_timing_config_para(hisifd, &(pinfo->dsi_phy_ctrl), &timing);

	set_reg(mipi_dsi_base + MIPI_LDI_DPI0_HRZ_CTRL3,
		dss_reduce(timing.dpi_hsize), 12, 0);
	set_reg(mipi_dsi_base + MIPI_LDI_DPI0_HRZ_CTRL2,
		dss_reduce(timing.width), 12, 0);
	set_reg(mipi_dsi_base + MIPI_LDI_VRT_CTRL2,
		dss_reduce(timing.vactive_line), 12, 0);

	disable_ldi(hisifd);
	if (is_mipi_video_panel(hisifd)) {
		set_reg(mipi_dsi_base + MIPI_LDI_FRM_MSK, 0x0, 1, 0);
		set_reg(mipi_dsi_base + DSI_CMD_MOD_CTRL, 0x1, 1, 1);
	}

	if (is_dual_mipi_panel(hisifd))
		set_reg(mipi_dsi_base + MIPI_LDI_CTRL,
			((mipi_dsi_base == hisifd->mipi_dsi0_base) ? 0 : 1), 1, 13);

	if (is_mipi_cmd_panel(hisifd)) {
		if (is_dual_mipi_panel(hisifd)) {
			if (mipi_dsi_base == hisifd->mipi_dsi0_base)
				set_reg(mipi_dsi_base + MIPI_DSI_TE_CTRL,
					(0x1 << 17) | (0x1 << 6) | 0x1, 18, 0);
		} else {
				set_reg(mipi_dsi_base + MIPI_DSI_TE_CTRL,
						(0x1 << 17) | (0x1 << 6) | 0x1, 18, 0);
		}
		set_reg(mipi_dsi_base + MIPI_DSI_TE_HS_NUM, 0x0, 32, 0);
		set_reg(mipi_dsi_base + MIPI_DSI_TE_HS_WD, 0x24024, 32, 0);
		set_reg(mipi_dsi_base + MIPI_DSI_TE_VS_WD,
			(0x3FC << 12) | (2  * lane_byte_clk / 1000000), 32, 0);
		set_reg(mipi_dsi_base + VID_SHADOW_CTRL, 0x1, 1, 0);
		/* enable vsync delay when dirty region update */
		set_reg(mipi_dsi_base + MIPI_VSYNC_DELAY_CTRL, 0x2, 2, 0);
		set_reg(mipi_dsi_base + MIPI_VSYNC_DELAY_TIME, 0x0, 32, 0);
		/* enable single frame update */
		set_reg(mipi_dsi_base + MIPI_LDI_FRM_MSK,
			(hisifd->frame_update_flag == 1) ? 0x0 : 0x1, 1, 0);
	}
}
/*lint +e712 +e737*/

/*lint -e568 -e685 -e732*/
void mipi_init(struct hisi_fb_data_type *hisifd, char __iomem *mipi_dsi_base)
{
	bool is_ready = false;
	struct hisi_panel_info *pinfo = NULL;
	uint32_t auto_ulps_enter_delay;
	uint32_t twakeup_cnt;
	uint32_t twakeup_clk_div;
	struct mipi_dsi_timing timing;
	uint32_t ldi_vrt_ctrl0;
	uint32_t vsync_delay_cnt;

	pinfo = &(hisifd->panel_info);//lint !e838

	if (pinfo->mipi.max_tx_esc_clk == 0) {
		HISI_FB_ERR("fb%d, max_tx_esc_clk is invalid!", hisifd->index);
		pinfo->mipi.max_tx_esc_clk = DEFAULT_MAX_TX_ESC_CLK;
	}

	memset(&(pinfo->dsi_phy_ctrl), 0, sizeof(struct mipi_dsi_phy_ctrl));

	if (pinfo->mipi.phy_mode == CPHY_MODE)
		get_dsi_cphy_ctrl(hisifd, &(pinfo->dsi_phy_ctrl));
	else
		get_dsi_dphy_ctrl(hisifd, &(pinfo->dsi_phy_ctrl));

	get_mipi_dsi_timing(hisifd);
	memset(&timing, 0, sizeof(timing));
	get_mipi_dsi_timing_config_para(hisifd, &(pinfo->dsi_phy_ctrl), &timing);

	/*************************Configure the PHY start*************************/

	set_reg(mipi_dsi_base + MIPIDSI_PHY_IF_CFG_OFFSET,
		pinfo->mipi.lane_nums, 2, 0);
	set_reg(mipi_dsi_base + MIPIDSI_CLKMGR_CFG_OFFSET,
		pinfo->dsi_phy_ctrl.clk_division, 8, 0);
	set_reg(mipi_dsi_base + MIPIDSI_CLKMGR_CFG_OFFSET,
		pinfo->dsi_phy_ctrl.clk_division, 8, 8);

	outp32(mipi_dsi_base + MIPIDSI_PHY_RSTZ_OFFSET, 0x00000000);

	outp32(mipi_dsi_base + MIPIDSI_PHY_TST_CTRL0_OFFSET, 0x00000000);
	outp32(mipi_dsi_base + MIPIDSI_PHY_TST_CTRL0_OFFSET, 0x00000001);
	outp32(mipi_dsi_base + MIPIDSI_PHY_TST_CTRL0_OFFSET, 0x00000000);

	mipi_cdphy_init_config(mipi_dsi_base, pinfo);

	outp32(mipi_dsi_base + MIPIDSI_PHY_RSTZ_OFFSET, 0x0000000F);

	is_ready = mipi_phy_status_check(mipi_dsi_base, 0x01);
	if (!is_ready)
		HISI_FB_INFO("fb%d, phylock is not ready!\n", hisifd->index);

	is_ready = mipi_phy_status_check(mipi_dsi_base,
		mipi_get_cmp_stopstate_value(pinfo));
	if (!is_ready)
		HISI_FB_INFO("fb%d, phystopstateclklane is not ready!\n", hisifd->index);

	/*************************Configure the PHY end*************************/

	set_reg(mipi_dsi_base + MIPIDSI_MODE_CFG_OFFSET, 0x1, 1, 1);
	if (is_mipi_cmd_panel(hisifd)) {
		set_reg(mipi_dsi_base + MIPIDSI_MODE_CFG_OFFSET, 0x1, 1, 0);
		set_reg(mipi_dsi_base + MIPIDSI_EDPI_CMD_SIZE_OFFSET,
			timing.width, 16, 0);

		// cnt=2 in update-patial scene, cnt nees to be checked for different panels
		if (pinfo->mipi.hs_wr_to_time == 0) {
			set_reg(mipi_dsi_base + MIPIDSI_HS_WR_TO_CNT_OFFSET,
				0x1000002, 25, 0);
		} else {
			set_reg(mipi_dsi_base + MIPIDSI_HS_WR_TO_CNT_OFFSET,
				(0x1 << 24) | (pinfo->mipi.hs_wr_to_time *
				pinfo->dsi_phy_ctrl.lane_byte_clk / 1000000000UL), 25, 0); //lint !e712
		}

		// FIXME: test tearing effect, if use gpio, no need
		// set_reg(mipi_dsi_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x1, 1, 0);
	}

	// phy_stop_wait_time
	set_reg(mipi_dsi_base + MIPIDSI_PHY_IF_CFG_OFFSET,
		pinfo->dsi_phy_ctrl.phy_stop_wait_time, 8, 8);

	//--------------configuring the DPI packet transmission----------------
	/*
	 * 2. Configure the DPI Interface:
	 * This defines how the DPI interface interacts with the controller.
	 */
	set_reg(mipi_dsi_base + MIPIDSI_DPI_VCID_OFFSET, pinfo->mipi.vc, 2, 0);
	set_reg(mipi_dsi_base + MIPIDSI_DPI_COLOR_CODING_OFFSET,
		pinfo->mipi.color_mode, 4, 0);

	set_reg(mipi_dsi_base + MIPIDSI_DPI_CFG_POL_OFFSET,
		pinfo->ldi.data_en_plr, 1, 0);
	set_reg(mipi_dsi_base + MIPIDSI_DPI_CFG_POL_OFFSET,
		pinfo->ldi.vsync_plr, 1, 1);
	set_reg(mipi_dsi_base + MIPIDSI_DPI_CFG_POL_OFFSET,
		pinfo->ldi.hsync_plr, 1, 2);
	set_reg(mipi_dsi_base + MIPIDSI_DPI_CFG_POL_OFFSET, 0x0, 1, 3);
	set_reg(mipi_dsi_base + MIPIDSI_DPI_CFG_POL_OFFSET, 0x0, 1, 4);


	/*
	 * 3. Select the Video Transmission Mode:
	 * This defines how the processor requires the video line to be
	 * transported through the DSI link.
	 */
	// video mode: low power mode
	if (pinfo->mipi.lp11_flag == MIPI_DISABLE_LP11)
		set_reg(mipi_dsi_base + MIPIDSI_VID_MODE_CFG_OFFSET, 0x0f, 6, 8);
	else
		set_reg(mipi_dsi_base + MIPIDSI_VID_MODE_CFG_OFFSET, 0x3f, 6, 8);

	/* set_reg(mipi_dsi_base + MIPIDSI_VID_MODE_CFG_OFFSET, 0x0, 1, 14); */
	if (is_mipi_video_panel(hisifd)) {
		// TODO: fix blank display bug when set backlight
		set_reg(mipi_dsi_base + MIPIDSI_DPI_LP_CMD_TIM_OFFSET, 0x4, 8, 16);
		// video mode: send read cmd by lp mode
		set_reg(mipi_dsi_base + MIPIDSI_VID_MODE_CFG_OFFSET, 0x1, 1, 15);
	}

	if ((pinfo->mipi.dsi_version == DSI_1_2_VERSION)
		&& (is_mipi_video_panel(hisifd))
		&& ((pinfo->ifbc_type == IFBC_TYPE_VESA3X_SINGLE)
			|| (pinfo->ifbc_type == IFBC_TYPE_VESA3X_DUAL))) {

		set_reg(mipi_dsi_base + MIPIDSI_VID_PKT_SIZE_OFFSET,
			timing.width * pinfo->pxl_clk_rate_div, 14, 0); //lint !e737
		// video vase3x must be set BURST mode
		if (pinfo->mipi.burst_mode < DSI_BURST_SYNC_PULSES_1) {
			HISI_FB_INFO("pinfo->mipi.burst_mode = %d. video need config "
				"BURST mode\n", pinfo->mipi.burst_mode);
			pinfo->mipi.burst_mode = DSI_BURST_SYNC_PULSES_1;
		}
	} else {
		set_reg(mipi_dsi_base + MIPIDSI_VID_PKT_SIZE_OFFSET,
			timing.width, 14, 0);
	}

	// burst mode
	set_reg(mipi_dsi_base + MIPIDSI_VID_MODE_CFG_OFFSET,
		pinfo->mipi.burst_mode, 2, 0);
	// for dsi read, BTA enable
	set_reg(mipi_dsi_base + MIPIDSI_PCKHDL_CFG_OFFSET, 0x1, 1, 2);

	/*
	 * 4. Define the DPI Horizontal timing configuration:
	 *
	 * Hsa_time = HSA*(PCLK period/Clk Lane Byte Period);
	 * Hbp_time = HBP*(PCLK period/Clk Lane Byte Period);
	 * Hline_time = (HSA+HBP+HACT+HFP)*(PCLK period/Clk Lane Byte Period);
	 */
	if (timing.hline_time < (timing.hsa + timing.hbp + timing.dpi_hsize))
		HISI_FB_ERR("wrong hfp\n");

	set_reg(mipi_dsi_base + MIPIDSI_VID_HSA_TIME_OFFSET, timing.hsa, 12, 0);
	set_reg(mipi_dsi_base + MIPIDSI_VID_HBP_TIME_OFFSET, timing.hbp, 12, 0);
	set_reg(mipi_dsi_base + MIPIDSI_VID_HLINE_TIME_OFFSET,
		timing.hline_time, 15, 0);

	set_reg(mipi_dsi_base + MIPIDSI_VID_VSA_LINES_OFFSET, timing.vsa, 10, 0);
	set_reg(mipi_dsi_base + MIPIDSI_VID_VBP_LINES_OFFSET, timing.vbp, 10, 0);

	if (timing.vfp > V_FRONT_PORCH_MAX) {
		ldi_vrt_ctrl0 = V_FRONT_PORCH_MAX;
		vsync_delay_cnt = (timing.vfp - V_FRONT_PORCH_MAX) * timing.hline_time;
		HISI_FB_WARNING("vfp %d > 1023", timing.vfp);
	} else {
		ldi_vrt_ctrl0 = timing.vfp;
		vsync_delay_cnt = 0;
	}
	set_reg(mipi_dsi_base + MIPIDSI_VID_VFP_LINES_OFFSET, ldi_vrt_ctrl0, 10, 0);
	set_reg(mipi_dsi_base + MIPI_VSYNC_DELAY_TIME, vsync_delay_cnt, 32, 0);

	set_reg(mipi_dsi_base + MIPIDSI_VID_VACTIVE_LINES_OFFSET, timing.vactive_line, 14, 0);

	set_reg(mipi_dsi_base + MIPIDSI_TO_CNT_CFG_OFFSET, 0x7FF, 16, 0);

	// Configure core's phy parameters
	set_reg(mipi_dsi_base + MIPIDSI_PHY_TMR_LPCLK_CFG_OFFSET,
		pinfo->dsi_phy_ctrl.clk_lane_lp2hs_time, 10, 0);
	set_reg(mipi_dsi_base + MIPIDSI_PHY_TMR_LPCLK_CFG_OFFSET,
		pinfo->dsi_phy_ctrl.clk_lane_hs2lp_time, 10, 16);

	set_reg(mipi_dsi_base + MIPIDSI_PHY_TMR_RD_CFG_OFFSET, 0x7FFF, 15, 0);
	set_reg(mipi_dsi_base + MIPIDSI_PHY_TMR_CFG_OFFSET,
		pinfo->dsi_phy_ctrl.data_lane_lp2hs_time, 10, 0);
	set_reg(mipi_dsi_base + MIPIDSI_PHY_TMR_CFG_OFFSET,
		pinfo->dsi_phy_ctrl.data_lane_hs2lp_time, 10, 16);

/*lint -e712*/
	// 16~19bit:pclk_en, pclk_sel, dpipclk_en, dpipclk_sel
	set_reg(mipi_dsi_base + MIPIDSI_CLKMGR_CFG_OFFSET, 0x5, 4, 16);
	if (is_mipi_cmd_panel(hisifd)) {
		/* pll_off_ulps = pinfo->mipi.non_continue_en ? 1 : 0; */
		auto_ulps_enter_delay = timing.hline_time * 3 / 2;
		twakeup_clk_div = 8;
		//twakeup_cnt*twakeup_clk_div*t_lanebyteclk>1ms
		if (pinfo->mipi.phy_mode == CPHY_MODE)
			twakeup_cnt = pinfo->dsi_phy_ctrl.lane_word_clk;
		else
			twakeup_cnt = pinfo->dsi_phy_ctrl.lane_byte_clk;
		twakeup_cnt = twakeup_cnt / 1000 * 3 / 2 / twakeup_clk_div;

		// set_reg(mipi_dsi_base + AUTO_ULPS_MODE, pll_off_ulps, 1, 16);
		set_reg(mipi_dsi_base + AUTO_ULPS_ENTER_DELAY,
			auto_ulps_enter_delay, 32, 0);
		set_reg(mipi_dsi_base + AUTO_ULPS_WAKEUP_TIME, twakeup_clk_div, 16, 0);
		set_reg(mipi_dsi_base + AUTO_ULPS_WAKEUP_TIME, twakeup_cnt, 16, 16);
	}

	if (pinfo->mipi.phy_mode == CPHY_MODE)
		set_reg(mipi_dsi_base + PHY_MODE, 0x1, 1, 0);
	else
		set_reg(mipi_dsi_base + PHY_MODE, 0x0, 1, 0);

	mipi_ldi_init(hisifd, mipi_dsi_base);
/*lint +e712*/
	// Waking up Core
	set_reg(mipi_dsi_base + MIPIDSI_PWR_UP_OFFSET, 0x1, 1, 0);
}
/*lint +e568 +e685 +e732*/

int mipi_dsi_clk_enable(struct hisi_fb_data_type *hisifd)
{
	int ret = 0;
	struct clk *clk_tmp = NULL;

	if (hisifd == NULL) {
		HISI_FB_ERR("hisifd is NULL");
		return -EINVAL;
	}

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		clk_tmp = hisifd->dss_dphy0_ref_clk;
		if (clk_tmp != NULL) {
			ret = clk_prepare(clk_tmp);
			if (ret) {
				HISI_FB_ERR("fb%d dss_dphy0_ref_clk clk_prepare failed, "
					"error=%d!\n", hisifd->index, ret);
				return -EINVAL;
			}

			ret = clk_enable(clk_tmp);
			if (ret) {
				HISI_FB_ERR("fb%d dss_dphy0_ref_clk clk_enable failed, "
					"error=%d!\n", hisifd->index, ret);
				return -EINVAL;
			}
		}

		clk_tmp = hisifd->dss_dphy0_cfg_clk;
		if (clk_tmp != NULL) {
			ret = clk_prepare(clk_tmp);
			if (ret) {
				HISI_FB_ERR("fb%d dss_dphy0_cfg_clk clk_prepare failed, "
					"error=%d!\n", hisifd->index, ret);
				return -EINVAL;
			}

			ret = clk_enable(clk_tmp);
			if (ret) {
				HISI_FB_ERR("fb%d dss_dphy0_cfg_clk clk_enable failed, "
					"error=%d!\n", hisifd->index, ret);
				return -EINVAL;
			}
		}
	}


	if (is_dual_mipi_panel(hisifd) || (hisifd->index == EXTERNAL_PANEL_IDX)) {
		clk_tmp = hisifd->dss_dphy1_ref_clk;
		if (clk_tmp != NULL) {
			ret = clk_prepare(clk_tmp);
			if (ret) {
				HISI_FB_ERR("fb%d dss_dphy1_ref_clk clk_prepare failed, "
					"error=%d!\n", hisifd->index, ret);
				return -EINVAL;
			}

			ret = clk_enable(clk_tmp);
			if (ret) {
				HISI_FB_ERR("fb%d dss_dphy1_ref_clk clk_enable failed, "
					"error=%d!\n", hisifd->index, ret);
				return -EINVAL;
			}
		}

		clk_tmp = hisifd->dss_dphy1_cfg_clk;
		if (clk_tmp != NULL) {
			ret = clk_prepare(clk_tmp);
			if (ret) {
				HISI_FB_ERR("fb%d dss_dphy1_cfg_clk clk_prepare failed, "
					"error=%d!\n", hisifd->index, ret);
				return -EINVAL;
			}

			ret = clk_enable(clk_tmp);
			if (ret) {
				HISI_FB_ERR("fb%d dss_dphy1_cfg_clk clk_enable failed, "
					"error=%d!\n", hisifd->index, ret);
				return -EINVAL;
			}
		}
	}

	return 0;
}

int mipi_dsi_clk_disable(struct hisi_fb_data_type *hisifd)
{
	struct clk *clk_tmp = NULL;

	if (hisifd == NULL) {
		HISI_FB_ERR("hisifd is NULL");
		return -EINVAL;
	}

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		clk_tmp = hisifd->dss_dphy0_ref_clk;
		if (clk_tmp != NULL) {
			clk_disable(clk_tmp);
			clk_unprepare(clk_tmp);
		}

		clk_tmp = hisifd->dss_dphy0_cfg_clk;
		if (clk_tmp != NULL) {
			clk_disable(clk_tmp);
			clk_unprepare(clk_tmp);
		}
	}


	if (is_dual_mipi_panel(hisifd) || (hisifd->index == EXTERNAL_PANEL_IDX)) {
		clk_tmp = hisifd->dss_dphy1_ref_clk;
		if (clk_tmp != NULL) {
			clk_disable(clk_tmp);
			clk_unprepare(clk_tmp);
		}

		clk_tmp = hisifd->dss_dphy1_cfg_clk;
		if (clk_tmp != NULL) {
			clk_disable(clk_tmp);
			clk_unprepare(clk_tmp);
		}
	}

	return 0;
}


/*******************************************************************************
 *
 */
/*lint -e776 -e715 -e712 -e737 -e776 -e838*/
static int mipi_dsi_on_sub1(struct hisi_fb_data_type *hisifd,
	char __iomem *mipi_dsi_base)
{
	/* mipi init */
	mipi_init(hisifd, mipi_dsi_base);

	/* switch to cmd mode */
	set_reg(mipi_dsi_base + MIPIDSI_MODE_CFG_OFFSET, 0x1, 1, 0);
	/* cmd mode: low power mode */
	set_reg(mipi_dsi_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x7f, 7, 8);
	set_reg(mipi_dsi_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0xf, 4, 16);
	set_reg(mipi_dsi_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x1, 1, 24);
	/* disable generate High Speed clock */
	/* delete? */
	set_reg(mipi_dsi_base + MIPIDSI_LPCLK_CTRL_OFFSET, 0x0, 1, 0);

	return 0;
}

static void pctrl_dphytx_stopcnt_config(
	struct hisi_fb_data_type *hisifd)
{
	struct hisi_panel_info *pinfo = NULL;
	uint64_t pctrl_dphytx_stopcnt = 0;
	uint32_t stopcnt_div;
	uint64_t lane_byte_clk;
	struct mipi_dsi_timing timing;

	pinfo = &(hisifd->panel_info);

	memset(&timing, 0, sizeof(timing));
	get_mipi_dsi_timing_config_para(hisifd, &(pinfo->dsi_phy_ctrl), &timing);

	stopcnt_div = is_dual_mipi_panel(hisifd) ? 2 : 1;
	/* init: wait DPHY 4 data lane stopstate */
	if (is_mipi_video_panel(hisifd)) {
		pctrl_dphytx_stopcnt = (uint64_t)(pinfo->ldi.h_back_porch +
			pinfo->ldi.h_front_porch + pinfo->ldi.h_pulse_width +
			pinfo->xres / stopcnt_div + 5) *
			hisifd->dss_vote_cmd.dss_pclk_dss_rate /
			(pinfo->pxl_clk_rate / stopcnt_div);
	} else {
		pctrl_dphytx_stopcnt = (uint64_t)(pinfo->ldi.h_back_porch +
			pinfo->ldi.h_front_porch + pinfo->ldi.h_pulse_width + 5) *
			hisifd->dss_vote_cmd.dss_pclk_dss_rate /
			(pinfo->pxl_clk_rate / stopcnt_div);
	}

	if (pinfo->mipi.dsi_timing_support) {
		lane_byte_clk = (pinfo->mipi.phy_mode == DPHY_MODE) ?
			pinfo->dsi_phy_ctrl.lane_byte_clk :
			pinfo->dsi_phy_ctrl.lane_word_clk;
		pctrl_dphytx_stopcnt = round1(((uint64_t)timing.hline_time *
			hisifd->dss_vote_cmd.dss_pclk_dss_rate), lane_byte_clk);
		HISI_FB_INFO("pctrl_dphytx_stopcnt = %d, pclk = %lu\n",
			pctrl_dphytx_stopcnt, hisifd->dss_vote_cmd.dss_pclk_dss_rate); //lint !e559
	}

	outp32(hisifd->mipi_dsi0_base + MIPIDSI_DPHYTX_STOPSNT_OFFSET,
		(uint32_t)pctrl_dphytx_stopcnt);
	if (is_dual_mipi_panel(hisifd))
		outp32(hisifd->mipi_dsi1_base + MIPIDSI_DPHYTX_STOPSNT_OFFSET,
			(uint32_t)pctrl_dphytx_stopcnt);
}

static int mipi_dsi_on_sub2(struct hisi_fb_data_type *hisifd,
	char __iomem *mipi_dsi_base)
{
	struct hisi_panel_info *pinfo = NULL;

	if (NULL == hisifd || NULL == mipi_dsi_base) {
		HISI_FB_ERR("hisifd or mipi_dsi_base is null.\n");
		return 0;
	}

	pinfo = &(hisifd->panel_info);

	if (is_mipi_video_panel(hisifd)) {
		/* switch to video mode */
		set_reg(mipi_dsi_base + MIPIDSI_MODE_CFG_OFFSET, 0x0, 1, 0);
	}

	if (is_mipi_cmd_panel(hisifd)) {
		/* cmd mode: high speed mode */
		set_reg(mipi_dsi_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x0, 7, 8);
		set_reg(mipi_dsi_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x0, 4, 16);
		set_reg(mipi_dsi_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x0, 1, 24);
	}

	/* enable EOTP TX */
	if (pinfo->mipi.phy_mode == DPHY_MODE) {
		/* Some vendors don't need eotp check.*/
		if (pinfo->mipi.eotp_disable_flag == 1)
			set_reg(mipi_dsi_base + MIPIDSI_PCKHDL_CFG_OFFSET, 0x0, 1, 0);
		else
			set_reg(mipi_dsi_base + MIPIDSI_PCKHDL_CFG_OFFSET, 0x1, 1, 0);
	}

	/* enable generate High Speed clock, non continue */
	if (pinfo->mipi.non_continue_en)
		set_reg(mipi_dsi_base + MIPIDSI_LPCLK_CTRL_OFFSET, 0x3, 2, 0);
	else
		set_reg(mipi_dsi_base + MIPIDSI_LPCLK_CTRL_OFFSET, 0x1, 2, 0);

	if ((pinfo->mipi.dsi_version == DSI_1_2_VERSION)
		&& is_ifbc_vesa_panel(hisifd))
		set_reg(mipi_dsi_base + MIPIDSI_DSC_PARAMETER_OFFSET, 0x01, 32, 0);


	pctrl_dphytx_stopcnt_config(hisifd);
	return 0;
}

static void mipi_check_itf_status(struct hisi_fb_data_type *hisifd)
{
	uint32_t tmp;
	int delay_count = 0;
	bool is_timeout = true;
	char __iomem *mctl_sys_base = NULL;
	int max_delay_count = 100;

	if (hisifd == NULL) {
		HISI_FB_ERR("NULL ptr\n");
		return;
	}

	if (hisifd->index != PRIMARY_PANEL_IDX)
		return;

	mctl_sys_base =  hisifd->dss_base + DSS_MCTRL_SYS_OFFSET;

	while (1) {
		tmp = inp32(mctl_sys_base + MCTL_MOD17_STATUS);
		if (((tmp & 0x10) == 0x10) || (delay_count > max_delay_count)) {
			is_timeout = (delay_count > max_delay_count) ? true : false;
			break;
		} else {
			mdelay(1);
			++delay_count;
		}
	}

	if (is_timeout)
		HISI_FB_INFO("mctl_itf%d not in idle status, ints=0x%x\n", hisifd->index, tmp);
}

static int mipi_dsi_off_sub(struct hisi_fb_data_type *hisifd, char __iomem *mipi_dsi_base)
{
	/* switch to cmd mode */
	set_reg(mipi_dsi_base + MIPIDSI_MODE_CFG_OFFSET, 0x1, 1, 0);
	/* cmd mode: low power mode */
	set_reg(mipi_dsi_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x7f, 7, 8);
	set_reg(mipi_dsi_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0xf, 4, 16);
	set_reg(mipi_dsi_base + MIPIDSI_CMD_MODE_CFG_OFFSET, 0x1, 1, 24);

	/* disable generate High Speed clock */
	set_reg(mipi_dsi_base + MIPIDSI_LPCLK_CTRL_OFFSET, 0x0, 1, 0);
	udelay(10);

	/* shutdown d_phy */
	set_reg(mipi_dsi_base +  MIPIDSI_PHY_RSTZ_OFFSET, 0x0, 3, 0);

	return 0;
}

void mipi_dsi_reset(struct hisi_fb_data_type *hisifd)
{
	if (hisifd == NULL) {
		HISI_FB_ERR("hisifd is NULL");
		return;
	}
	set_reg(hisifd->mipi_dsi0_base + MIPIDSI_PWR_UP_OFFSET, 0x0, 1, 0);
	msleep(2);
	set_reg(hisifd->mipi_dsi0_base + MIPIDSI_PWR_UP_OFFSET, 0x1, 1, 0);
}

/*******************************************************************************
 * MIPI DPHY GPIO for FPGA
 */
#define GPIO_MIPI_DPHY_PG_SEL_A_NAME	"pg_sel_a"
#define GPIO_MIPI_DPHY_PG_SEL_B_NAME	"pg_sel_b"
#define GPIO_MIPI_DPHY_TX_RX_A_NAME	"tx_rx_a"
#define GPIO_MIPI_DPHY_TX_RX_B_NAME	"tx_rx_b"

static uint32_t gpio_pg_sel_a = GPIO_PG_SEL_A;
static uint32_t gpio_tx_rx_a = GPIO_TX_RX_A;
static uint32_t gpio_pg_sel_b = GPIO_PG_SEL_B;
static uint32_t gpio_tx_rx_b = GPIO_TX_RX_B;

static struct gpio_desc mipi_dphy_gpio_request_cmds[] = {
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_MIPI_DPHY_PG_SEL_A_NAME, &gpio_pg_sel_a, 0},
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_MIPI_DPHY_PG_SEL_B_NAME, &gpio_pg_sel_b, 0},
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_MIPI_DPHY_TX_RX_A_NAME, &gpio_tx_rx_a, 0},
	{DTYPE_GPIO_REQUEST, WAIT_TYPE_MS, 0,
		GPIO_MIPI_DPHY_TX_RX_B_NAME, &gpio_tx_rx_b, 0},
};

static struct gpio_desc mipi_dphy_gpio_free_cmds[] = {
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_MIPI_DPHY_PG_SEL_A_NAME, &gpio_pg_sel_a, 0},
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_MIPI_DPHY_PG_SEL_B_NAME, &gpio_pg_sel_b, 0},
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_MIPI_DPHY_TX_RX_A_NAME, &gpio_tx_rx_a, 0},
	{DTYPE_GPIO_FREE, WAIT_TYPE_MS, 0,
		GPIO_MIPI_DPHY_TX_RX_B_NAME, &gpio_tx_rx_b, 0},

};

static struct gpio_desc mipi_dphy_gpio_normal_cmds[] = {
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_MIPI_DPHY_PG_SEL_A_NAME, &gpio_pg_sel_a, 0},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_MIPI_DPHY_TX_RX_A_NAME, &gpio_tx_rx_a, 1},

	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_MIPI_DPHY_PG_SEL_B_NAME, &gpio_pg_sel_b, 0},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_MIPI_DPHY_TX_RX_B_NAME, &gpio_tx_rx_b, 1},
};

static struct gpio_desc mipi_dphy_gpio_lowpower_cmds[] = {
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_MIPI_DPHY_PG_SEL_A_NAME, &gpio_pg_sel_a, 0},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_MIPI_DPHY_TX_RX_A_NAME, &gpio_tx_rx_a, 0},

	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_MIPI_DPHY_PG_SEL_B_NAME, &gpio_pg_sel_b, 0},
	{DTYPE_GPIO_OUTPUT, WAIT_TYPE_MS, 0,
		GPIO_MIPI_DPHY_TX_RX_B_NAME, &gpio_tx_rx_b, 0},
};

static int mipi_dsi_dphy_fastboot_fpga(
	struct hisi_fb_data_type *hisifd)
{
	if (g_fpga_flag == 1)
		/* mpi dphy gpio request */
		gpio_cmds_tx(mipi_dphy_gpio_request_cmds,
			ARRAY_SIZE(mipi_dphy_gpio_request_cmds));

	return 0;
}

static int mipi_dsi_dphy_on_fpga(struct hisi_fb_data_type *hisifd)
{
	if (hisifd->index == EXTERNAL_PANEL_IDX)
		return 0;

	if (g_fpga_flag == 1) {
		/* mipi dphy gpio request */
		gpio_cmds_tx(mipi_dphy_gpio_request_cmds,
			ARRAY_SIZE(mipi_dphy_gpio_request_cmds));

		/* mipi dphy gpio normal */
		gpio_cmds_tx(mipi_dphy_gpio_normal_cmds,
			ARRAY_SIZE(mipi_dphy_gpio_normal_cmds));
	}

	return 0;
}

static int mipi_dsi_dphy_off_fpga(struct hisi_fb_data_type *hisifd)
{
	if (hisifd->index == EXTERNAL_PANEL_IDX)
		return 0;

	if (g_fpga_flag == 1) {
		/* mipi dphy gpio lowpower */
		gpio_cmds_tx(mipi_dphy_gpio_lowpower_cmds,
			ARRAY_SIZE(mipi_dphy_gpio_lowpower_cmds));
		/* mipi dphy gpio free */
		gpio_cmds_tx(mipi_dphy_gpio_free_cmds,
			ARRAY_SIZE(mipi_dphy_gpio_free_cmds));
	}

	return 0;
}


/*******************************************************************************
 *
 */
int mipi_dsi_set_fastboot(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisi_panel_info *pinfo = NULL;

	if (pdev == NULL) {
		HISI_FB_ERR("pdev is NULL");
		return -EINVAL;
	}
	hisifd = platform_get_drvdata(pdev);
	if (hisifd == NULL) {
		HISI_FB_ERR("hisifd is NULL");
		return -EINVAL;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	mipi_dsi_dphy_fastboot_fpga(hisifd);

	mipi_dsi_clk_enable(hisifd);
	/* bugfix for access dsi reg noc before apb clock enable */
	if (hisifd->index == PRIMARY_PANEL_IDX) {
		// disp core dsi0 clk
		set_reg(hisifd->dss_base + DSS_DISP_GLB_OFFSET + MODULE_CORE_CLK_SEL,
			0x1, 1, 16);
		set_reg(hisifd->dss_base + GLB_MODULE_CLK_SEL, 0x1, 1, 23);
		set_reg(hisifd->dss_base + GLB_MODULE_CLK_EN, 0x1, 1, 23);
		if (is_dual_mipi_panel(hisifd)) {
			// disp core dsi1 clk
			set_reg(hisifd->dss_base + DSS_DISP_GLB_OFFSET + MODULE_CORE_CLK_SEL,
				0x1, 1, 17);
			set_reg(hisifd->dss_base + GLB_MODULE_CLK_SEL, 0x1, 1, 24);
			set_reg(hisifd->dss_base + GLB_MODULE_CLK_EN, 0x1, 1, 24);
		}
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		// disp core dsi1 clk
		set_reg(hisifd->dss_base + DSS_DISP_GLB_OFFSET + MODULE_CORE_CLK_SEL,
			0x1, 1, 17);
		set_reg(hisifd->dss_base + GLB_MODULE_CLK_SEL, 0x1, 1, 24);
		set_reg(hisifd->dss_base + GLB_MODULE_CLK_EN, 0x1, 1, 24);
	}

	pinfo = &(hisifd->panel_info);//lint !e838
	memset(&(pinfo->dsi_phy_ctrl), 0, sizeof(struct mipi_dsi_phy_ctrl));
	if (pinfo->mipi.phy_mode == CPHY_MODE)
		get_dsi_cphy_ctrl(hisifd, &(pinfo->dsi_phy_ctrl));
	else
		get_dsi_dphy_ctrl(hisifd, &(pinfo->dsi_phy_ctrl));

	get_mipi_dsi_timing(hisifd);

	ret = panel_next_set_fastboot(pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

int mipi_dsi_on(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;

	if (pdev == NULL) {
		HISI_FB_ERR("pdev is NULL");
		return -EINVAL;
	}
	hisifd = platform_get_drvdata(pdev);
	if (hisifd == NULL) {
		HISI_FB_ERR("hisifd is NULL");
		return -EINVAL;
	}

	HISI_FB_INFO("fb%d, +\n", hisifd->index);

	mipi_dsi_dphy_on_fpga(hisifd);

	/* set LCD init step before LCD on*/
	hisifd->panel_info.lcd_init_step = LCD_INIT_POWER_ON;
	panel_next_on(pdev);

	// dis-reset
	// ip_reset_dis_dsi0, ip_reset_dis_dsi1
	if (hisifd->index == PRIMARY_PANEL_IDX) {
		if (is_dual_mipi_panel(hisifd))
			outp32(hisifd->peri_crg_base + PERRSTDIS3, 0x30000000);
		else
			outp32(hisifd->peri_crg_base + PERRSTDIS3, 0x10000000);
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		outp32(hisifd->peri_crg_base + PERRSTDIS3, 0x20000000);
	} else {
		HISI_FB_ERR("fb%d, not supported!\n", hisifd->index);
	}
	mipi_dsi_clk_enable(hisifd);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		// disp core dsi0 clk
		set_reg(hisifd->dss_base + DSS_DISP_GLB_OFFSET + MODULE_CORE_CLK_SEL,
			0x1, 1, 16);
		set_reg(hisifd->dss_base + GLB_MODULE_CLK_SEL, 0x1, 1, 23);
		set_reg(hisifd->dss_base + GLB_MODULE_CLK_EN, 0x1, 1, 23);
		udelay(10);
		mipi_dsi_on_sub1(hisifd, hisifd->mipi_dsi0_base);
		if (is_dual_mipi_panel(hisifd)) {
			// disp core dsi1 clk
			set_reg(hisifd->dss_base + DSS_DISP_GLB_OFFSET + MODULE_CORE_CLK_SEL,
				0x1, 1, 17);
			set_reg(hisifd->dss_base + GLB_MODULE_CLK_SEL, 0x1, 1, 24);
			set_reg(hisifd->dss_base + GLB_MODULE_CLK_EN, 0x1, 1, 24);
			udelay(10);
			mipi_dsi_on_sub1(hisifd, hisifd->mipi_dsi1_base);
		}
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		// disp core dsi1 clk
		set_reg(hisifd->dss_base + DSS_DISP_GLB_OFFSET + MODULE_CORE_CLK_SEL,
			0x1, 1, 17);
		set_reg(hisifd->dss_base + GLB_MODULE_CLK_SEL, 0x1, 1, 24);
		set_reg(hisifd->dss_base + GLB_MODULE_CLK_EN, 0x1, 1, 24);
		udelay(10);
		mipi_dsi_on_sub1(hisifd, hisifd->mipi_dsi1_base);
	} else {
		HISI_FB_ERR("fb%d, not supported!\n", hisifd->index);
	}

	panel_next_on(pdev);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		mipi_dsi_on_sub2(hisifd, hisifd->mipi_dsi0_base);
		if (is_dual_mipi_panel(hisifd))
			mipi_dsi_on_sub2(hisifd, hisifd->mipi_dsi1_base);
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		mipi_dsi_on_sub2(hisifd, hisifd->mipi_dsi1_base);
	} else {
		HISI_FB_ERR("fb%d, not supported!\n", hisifd->index);
	}

	/* mipi hs video/command mode */
	panel_next_on(pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return 0;
}

static void mipi_tx_off_rx_ulps_config(
	struct hisi_fb_data_type *hisifd, struct platform_device *pdev)
{
	int delay_count = 0;
	int delay_count_max = 16;

	if (!panel_next_bypass_powerdown_ulps_support(pdev))
		return;

	disable_ldi(hisifd);
	/* Read register status, maximum waiting time is 16ms */
	/* 0x7FF--The lower 11 bits of the register 0x1--Register value */
	while ((((uint32_t)inp32(hisifd->mipi_dsi0_base + MIPI_LDI_VSTATE)) &
		0x7FF) != 0x1) {
		if (++delay_count > delay_count_max) {
			HISI_FB_ERR("wait ldi vstate idle timeout\n");
			break;
		}
		msleep(1);
	}
	/* 0--enable 1--not enabled */
	mipi_dsi_ulps_cfg(hisifd, 0);
}

int mipi_dsi_off(struct platform_device *pdev)
{
	int ret = 0;
	struct hisi_fb_data_type *hisifd = NULL;

	if (pdev == NULL) {
		HISI_FB_ERR("pdev is NULL");
		return -EINVAL;
	}
	hisifd = platform_get_drvdata(pdev);
	if (hisifd == NULL) {
		HISI_FB_ERR("hisifd is NULL");
		return -EINVAL;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	/* set LCD uninit step before LCD off*/
	hisifd->panel_info.lcd_uninit_step = LCD_UNINIT_MIPI_HS_SEND_SEQUENCE;
	ret = panel_next_off(pdev);

	if (hisifd->panel_info.lcd_uninit_step_support)
		/* TODO: add MIPI LP mode here if necessary */
		/* MIPI LP mode end */
		ret = panel_next_off(pdev);

	disable_ldi(hisifd);

	if (hisifd->index == PRIMARY_PANEL_IDX) {
		/* Here need to enter ulps when panel off bypass ddic power down */
		mipi_tx_off_rx_ulps_config(hisifd, pdev);
		mipi_check_itf_status(hisifd);
		mipi_dsi_off_sub(hisifd, hisifd->mipi_dsi0_base);
		if (is_dual_mipi_panel(hisifd))
			mipi_dsi_off_sub(hisifd, hisifd->mipi_dsi1_base);
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		mipi_dsi_off_sub(hisifd, hisifd->mipi_dsi1_base);
	} else {
		HISI_FB_ERR("fb%d, not supported!\n", hisifd->index);
	}

	mipi_dsi_clk_disable(hisifd);

	mipi_dsi_dphy_off_fpga(hisifd);

	// reset DSI
	if (hisifd->index == PRIMARY_PANEL_IDX) {
		if (is_dual_mipi_panel(hisifd))
			outp32(hisifd->peri_crg_base + PERRSTEN3, 0x30000000);
		else
			outp32(hisifd->peri_crg_base + PERRSTEN3, 0x10000000);
	} else if (hisifd->index == EXTERNAL_PANEL_IDX) {
		outp32(hisifd->peri_crg_base + PERRSTEN3, 0x20000000);
	} else {
		HISI_FB_ERR("fb%d, not supported!\n", hisifd->index);
	}

	if (hisifd->panel_info.lcd_uninit_step_support)
		ret = panel_next_off(pdev);

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}


static int mipi_dsi_ulps_enter(struct hisi_fb_data_type *hisifd,
	char __iomem *mipi_dsi_base, uint32_t mipi_idx)
{
	uint32_t tmp;
	uint32_t cmp_ulpsactivenot_val = 0;
	uint32_t cmp_stopstate_val = 0;
	uint32_t try_times;
	bool is_ready = false;

	HISI_FB_DEBUG("fb%d, mipi_idx=%d, +!\n", hisifd->index, mipi_idx);

	if (hisifd->panel_info.mipi.lane_nums >= DSI_4_LANES) {
		cmp_ulpsactivenot_val = (BIT(5) | BIT(8) | BIT(10) | BIT(12));
		cmp_stopstate_val = (BIT(4) | BIT(7) | BIT(9) | BIT(11));
	} else if (hisifd->panel_info.mipi.lane_nums >= DSI_3_LANES) {
		cmp_ulpsactivenot_val = (BIT(5) | BIT(8) | BIT(10));
		cmp_stopstate_val = (BIT(4) | BIT(7) | BIT(9));
	} else if (hisifd->panel_info.mipi.lane_nums >= DSI_2_LANES) {
		cmp_ulpsactivenot_val = (BIT(5) | BIT(8));
		cmp_stopstate_val = (BIT(4) | BIT(7));
	} else {
		cmp_ulpsactivenot_val = (BIT(5));
		cmp_stopstate_val = (BIT(4));
	}

	tmp = (uint32_t)inp32(mipi_dsi_base + MIPIDSI_LPCLK_CTRL_OFFSET) & BIT(1);
	if (tmp && (hisifd->panel_info.mipi.phy_mode == DPHY_MODE))
		cmp_stopstate_val |= (BIT(2));


	// check DPHY data and clock lane stopstate
	try_times = 0;
	tmp = inp32(mipi_dsi_base + MIPIDSI_PHY_STATUS_OFFSET);
	while ((tmp & cmp_stopstate_val) != cmp_stopstate_val) {
		udelay(10);
		if (++try_times > 100) {
			HISI_FB_ERR("fb%d, check phy data and clk lane stop state failed! "
				"PHY_STATUS=0x%x\n", hisifd->index, tmp);
			return 0;
		}
		if ((tmp & cmp_stopstate_val) == (cmp_stopstate_val & ~(BIT(2)))) {
			HISI_FB_INFO("fb%d, datalanes are in stop state, pull down "
				"phy_txrequestclkhs.\n", hisifd->index);
			set_reg(mipi_dsi_base + MIPIDSI_LPCLK_CTRL_OFFSET, 0x0, 1, 1);
			set_reg(mipi_dsi_base + MIPIDSI_LPCLK_CTRL_OFFSET, 0x0, 1, 0);
		}

		tmp = inp32(mipi_dsi_base + MIPIDSI_PHY_STATUS_OFFSET);
	}

	// disable DPHY clock lane's Hight Speed Clock
	set_reg(mipi_dsi_base + MIPIDSI_LPCLK_CTRL_OFFSET, 0x0, 1, 0);

	// force_pll = 0
	set_reg(mipi_dsi_base + MIPIDSI_PHY_RSTZ_OFFSET, 0x0, 1, 3);

	// request that data lane enter ULPS
	set_reg(mipi_dsi_base + MIPIDSI_PHY_ULPS_CTRL_OFFSET, 0x4, 4, 0);

	// check DPHY data lane ulpsactivenot_status
	try_times = 0;
	tmp = inp32(mipi_dsi_base + MIPIDSI_PHY_STATUS_OFFSET);
	while ((tmp & cmp_ulpsactivenot_val) != 0) {
		udelay(10);
		if (++try_times > 100) {
			HISI_FB_ERR("fb%d, request phy data lane enter ulps failed! "
				"PHY_STATUS=0x%x.\n", hisifd->index, tmp);
			break;
		}

		tmp = inp32(mipi_dsi_base + MIPIDSI_PHY_STATUS_OFFSET);
	}

	// request that clock lane enter ULPS
	if (hisifd->panel_info.mipi.phy_mode == DPHY_MODE) {
		set_reg(mipi_dsi_base + MIPIDSI_PHY_ULPS_CTRL_OFFSET, 0x5, 4, 0);

		// check DPHY clock lane ulpsactivenot_status
		try_times = 0;
		tmp = inp32(mipi_dsi_base + MIPIDSI_PHY_STATUS_OFFSET);
		while ((tmp & BIT(3)) != 0) {
			udelay(10);
			if (++try_times > 100) {
				HISI_FB_ERR("fb%d, request phy clk lane enter ulps failed! "
					"PHY_STATUS=0x%x\n", hisifd->index, tmp);
				break;
			}

			tmp = inp32(mipi_dsi_base + MIPIDSI_PHY_STATUS_OFFSET);
		}
	}

	// check phy lock == 0?
	is_ready = mipi_phy_status_check(mipi_dsi_base, 0x0);
	if (!is_ready)
		HISI_FB_DEBUG("fb%d, phylock== 1!\n", hisifd->index);

	// bit13 lock sel enable (dual_mipi_panel mipi_dsi1_base+bit13 set 1),
	// colse clock gate
	set_reg(mipi_dsi_base + MIPIDSI_DPHYTX_CTRL_OFFSET, 0x1, 1, 13);
	set_reg(hisifd->peri_crg_base + PERDIS3, 0x3, 4, 28);
	if (mipi_idx == 1) {
		set_reg(hisifd->mipi_dsi1_base + MIPIDSI_DPHYTX_CTRL_OFFSET, 0x1, 1, 13);
		set_reg(hisifd->peri_crg_base + PERDIS3, 0xf, 4, 28);
	}

	HISI_FB_DEBUG("fb%d, mipi_idx=%d, -!\n", hisifd->index, mipi_idx);

	return 0;
}

static int mipi_dsi_ulps_exit(struct hisi_fb_data_type *hisifd,
	char __iomem *mipi_dsi_base, uint32_t mipi_idx)
{
	uint32_t tmp = 0;
	uint32_t cmp_ulpsactivenot_val = 0;
	uint32_t cmp_stopstate_val = 0;
	uint32_t try_times = 0;
	uint32_t need_pll_retry = 0;
	bool is_ready = false;

	HISI_FB_DEBUG("fb%d, mipi_idx=%d, +!\n", hisifd->index, mipi_idx);

	if (hisifd->panel_info.mipi.lane_nums >= DSI_4_LANES) {
		cmp_ulpsactivenot_val = (BIT(3) | BIT(5) | BIT(8) | BIT(10) | BIT(12));
		cmp_stopstate_val = (BIT(2) | BIT(4) | BIT(7) | BIT(9) | BIT(11));
	} else if (hisifd->panel_info.mipi.lane_nums >= DSI_3_LANES) {
		cmp_ulpsactivenot_val = (BIT(3) | BIT(5) | BIT(8) | BIT(10));
		cmp_stopstate_val = (BIT(2) | BIT(4) | BIT(7) | BIT(9));
	} else if (hisifd->panel_info.mipi.lane_nums >= DSI_2_LANES) {
		cmp_ulpsactivenot_val = (BIT(3) | BIT(5) | BIT(8));
		cmp_stopstate_val = (BIT(2) | BIT(4) | BIT(7));
	} else {
		cmp_ulpsactivenot_val = (BIT(3) | BIT(5));
		cmp_stopstate_val = (BIT(2) | BIT(4));
	}
	if (hisifd->panel_info.mipi.phy_mode == CPHY_MODE) {
		cmp_ulpsactivenot_val &= ~(BIT(3));
		cmp_stopstate_val &= ~(BIT(2));
	}

	if (is_dual_mipi_panel(hisifd))
		set_reg(hisifd->peri_crg_base + PEREN3, 0xf, 4, 28);
	else
		set_reg(hisifd->peri_crg_base + PEREN3, 0x3, 4, 28);

	udelay(10);
	// force pll = 1
	set_reg(mipi_dsi_base + MIPIDSI_PHY_RSTZ_OFFSET, 0x1, 1, 3);

	udelay(100); // wait pll clk

	// check phy lock == 1?
	is_ready = mipi_phy_status_check(mipi_dsi_base, 0x1);
	if (!is_ready)
		HISI_FB_DEBUG("fb%d, phylock== 0, phylock is not ready!\n", hisifd->index);

	// bit13 lock sel enable (dual_mipi_panel mipi_dsi1_base+bit13 set 1),
	// colse clock gate
	set_reg(mipi_dsi_base + MIPIDSI_DPHYTX_CTRL_OFFSET, 0x0, 1, 13);
	if (is_dual_mipi_panel(hisifd))
		set_reg(hisifd->mipi_dsi1_base + MIPIDSI_DPHYTX_CTRL_OFFSET, 0x0, 1, 13);

	// request that data lane and clock lane exit ULPS
	outp32(mipi_dsi_base + MIPIDSI_PHY_ULPS_CTRL_OFFSET, 0xF);
	try_times = 0;
	tmp = inp32(mipi_dsi_base + MIPIDSI_PHY_STATUS_OFFSET);
	while ((tmp & cmp_ulpsactivenot_val) != cmp_ulpsactivenot_val) {
		udelay(10);
		if (++try_times > 100) {
			HISI_FB_ERR("fb%d, request data clock lane exit ulps fail! "
				"PHY_STATUS=0x%x\n", hisifd->index, tmp);
			need_pll_retry = BIT(0);
			break;
		}

		tmp = inp32(mipi_dsi_base + MIPIDSI_PHY_STATUS_OFFSET);
	}

	// mipi spec
	mdelay(1);

	// clear PHY_ULPS_CTRL
	outp32(mipi_dsi_base + MIPIDSI_PHY_ULPS_CTRL_OFFSET, 0x0);

	//check DPHY data lane cmp_stopstate_val
	try_times = 0;
	tmp = inp32(mipi_dsi_base + MIPIDSI_PHY_STATUS_OFFSET);
	while ((tmp & cmp_stopstate_val) != cmp_stopstate_val) {
		udelay(10);
		if (++try_times > 100) {
			HISI_FB_ERR("fb%d, check phy data clk lane stop state failed! "
				"PHY_STATUS=0x%x\n", hisifd->index, tmp);
			need_pll_retry |= BIT(1);
			break;
		}

		tmp = inp32(mipi_dsi_base + MIPIDSI_PHY_STATUS_OFFSET);
	}
	// enable DPHY clock lane's Hight Speed Clock
	set_reg(mipi_dsi_base + MIPIDSI_LPCLK_CTRL_OFFSET, 0x1, 1, 0);
	if (hisifd->panel_info.mipi.non_continue_en)
		set_reg(mipi_dsi_base + MIPIDSI_LPCLK_CTRL_OFFSET, 0x1, 1, 1);

	// reset dsi
	outp32(mipi_dsi_base + MIPIDSI_PWR_UP_OFFSET, 0x0);
	udelay(5);
	// Power_up dsi
	outp32(mipi_dsi_base + MIPIDSI_PWR_UP_OFFSET, 0x1);

	HISI_FB_DEBUG("fb%d, mipi_idx=%d, -!\n", hisifd->index, mipi_idx);
	return 0;
}
//lint -restore

int mipi_dsi_ulps_cfg(struct hisi_fb_data_type *hisifd, int enable)
{
	int ret = 0;

	if (hisifd == NULL) {
		HISI_FB_ERR("hisifd is NULL");
		return -EINVAL;
	}

	HISI_FB_DEBUG("fb%d, +.\n", hisifd->index);

	if (enable) {
		mipi_dsi_ulps_exit(hisifd, hisifd->mipi_dsi0_base, 0);
		if (is_dual_mipi_panel(hisifd))
			mipi_dsi_ulps_exit(hisifd, hisifd->mipi_dsi1_base, 1);
	} else {
		mipi_dsi_ulps_enter(hisifd, hisifd->mipi_dsi0_base, 0);
		if (is_dual_mipi_panel(hisifd))
			mipi_dsi_ulps_enter(hisifd, hisifd->mipi_dsi1_base, 1);
	}

	HISI_FB_DEBUG("fb%d, -.\n", hisifd->index);

	return ret;
}

static void mipi_dsi_set_cdphy_bit_clk_upt_cmd(
	struct hisi_fb_data_type *hisifd, char __iomem *mipi_dsi_base,
	struct mipi_dsi_phy_ctrl *phy_ctrl)
{
	struct hisi_panel_info *pinfo = NULL;
	unsigned long dw_jiffies;
	bool is_ready = false;
	uint32_t tmp = 0;

	HISI_FB_INFO("fb%d +\n", hisifd->index);
	pinfo = &(hisifd->panel_info);

	if (g_fpga_flag) {
		if (pinfo->mipi.phy_mode == CPHY_MODE) {
			/* PLL configuration I */
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010046,
				phy_ctrl->rg_cp + (phy_ctrl->rg_lpf_r << 4));
			/* PLL configuration II */
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010048,
				phy_ctrl->rg_0p8v + (phy_ctrl->rg_2p5g << 1) +
				(pinfo->dsi_phy_ctrl.rg_320m << 2) +
				(phy_ctrl->rg_band_sel << 3) + (phy_ctrl->rg_cphy_div << 4));
			/* PLL configuration III */
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010049,
				phy_ctrl->rg_pre_div);
			/* PLL configuration IV */
			mipi_config_phy_test_code(mipi_dsi_base, 0x0001004A,
				phy_ctrl->rg_div);
		} else {
			/* PLL configuration I */
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010046,
				phy_ctrl->rg_cp + (phy_ctrl->rg_lpf_r << 4));
			/* PLL configuration II */
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010048,
				phy_ctrl->rg_0p8v + (phy_ctrl->rg_2p5g << 1) +
				(phy_ctrl->rg_320m << 2) + (phy_ctrl->rg_band_sel << 3));
			/* PLL configuration III */
			mipi_config_phy_test_code(mipi_dsi_base, 0x00010049,
				phy_ctrl->rg_pre_div);
			/* PLL configuration IV */
			mipi_config_phy_test_code(mipi_dsi_base, 0x0001004A,
				phy_ctrl->rg_div);
		}
	} else {
		/* PLL configuration III */
		mipi_config_phy_test_code(mipi_dsi_base, 0x00010049,
			(phy_ctrl->rg_pll_posdiv << 4) | phy_ctrl->rg_pll_prediv);
		/* PLL configuration IV */
		mipi_config_phy_test_code(mipi_dsi_base, 0x0001004A,
			phy_ctrl->rg_pll_fbkdiv);
	}

	/* PLL update control */
	mipi_config_phy_test_code(mipi_dsi_base, 0x0001004B, 0x1);

	/* clk lane HS2LP/LP2HS */
	outp32(mipi_dsi_base + MIPIDSI_PHY_TMR_LPCLK_CFG_OFFSET,
		(phy_ctrl->clk_lane_lp2hs_time + (phy_ctrl->clk_lane_hs2lp_time << 16)));
	/* data lane HS2LP/ LP2HS */
	outp32(mipi_dsi_base + MIPIDSI_PHY_TMR_CFG_OFFSET,
		(phy_ctrl->data_lane_lp2hs_time + (phy_ctrl->data_lane_hs2lp_time << 16)));

	/* escape clock dividor */
	set_reg(mipi_dsi_base + MIPIDSI_CLKMGR_CFG_OFFSET,
		(phy_ctrl->clk_division + (phy_ctrl->clk_division << 8)), 16, 0);
	/*lint -e550 -e732*/
	is_ready = false;
	/* 500ms */
	dw_jiffies = jiffies + HZ / 2;
	do {
		tmp = inp32(mipi_dsi_base + MIPIDSI_PHY_STATUS_OFFSET);
		if ((tmp & 0x00000001) == 0x00000001) {
			is_ready = true;
			break;
		}
	} while (time_after(dw_jiffies, jiffies));
	if (!is_ready) {
		HISI_FB_INFO("fb%d, phylock is not ready!MIPIDSI_PHY_STATUS = 0x%x\n",
			hisifd->index, tmp);
	}
	/*lint +e550 +e732*/

	HISI_FB_DEBUG("fb%d -\n", hisifd->index);
}

static void mipi_dsi_set_cdphy_bit_clk_upt_video(
	struct hisi_fb_data_type *hisifd, char __iomem *mipi_dsi_base,
	struct mipi_dsi_phy_ctrl *phy_ctrl)
{
	struct hisi_panel_info *pinfo = NULL;
	dss_rect_t rect;
	unsigned long dw_jiffies;
	uint32_t tmp;
	bool is_ready = false;
	struct mipi_dsi_timing timing;

	HISI_FB_DEBUG("fb%d +\n", hisifd->index);

	pinfo = &(hisifd->panel_info);
	pinfo->dsi_phy_ctrl = *phy_ctrl;

	rect.x = 0;
	rect.y = 0;
	rect.w = pinfo->xres;//lint !e713
	rect.h = pinfo->yres;//lint !e713

	mipi_ifbc_get_rect(hisifd, &rect);

	/* PLL configuration III */
	mipi_config_phy_test_code(mipi_dsi_base, 0x00010049,
		(phy_ctrl->rg_pll_posdiv << 4) | phy_ctrl->rg_pll_prediv);
	/* PLL configuration IV */
	mipi_config_phy_test_code(mipi_dsi_base, 0x0001004A,
		phy_ctrl->rg_pll_fbkdiv);

	/* PLL update control */
	mipi_config_phy_test_code(mipi_dsi_base, 0x0001004B, 0x1);

	if (pinfo->mipi.phy_mode == CPHY_MODE)
		mipi_config_cphy_spec1v0_parameter(mipi_dsi_base, pinfo, &pinfo->dsi_phy_ctrl);
	else
		mipi_config_dphy_spec1v2_parameter(mipi_dsi_base, pinfo, &pinfo->dsi_phy_ctrl);

	/*lint -e550 -e732*/
	dw_jiffies = jiffies + HZ / 2;
	do {
		tmp = inp32(mipi_dsi_base + MIPIDSI_PHY_STATUS_OFFSET);
		if ((tmp & 0x00000001) == 0x00000001) {
			is_ready = true;
			break;
		}
	} while (time_after(dw_jiffies, jiffies));

	if (!is_ready) {
		HISI_FB_ERR("fb%d, phylock is not ready! MIPIDSI_PHY_STATUS_OFFSET="
			"0x%x.\n", hisifd->index, tmp);
	}
	/*lint +e550 +e732*/
	// phy_stop_wait_time
	set_reg(mipi_dsi_base + MIPIDSI_PHY_IF_CFG_OFFSET,
		phy_ctrl->phy_stop_wait_time, 8, 8);

	/*
	 * 4. Define the DPI Horizontal timing configuration:
	 *
	 * Hsa_time = HSA*(PCLK period/Clk Lane Byte Period);
	 * Hbp_time = HBP*(PCLK period/Clk Lane Byte Period);
	 * Hline_time = (HSA+HBP+HACT+HFP)*(PCLK period/Clk Lane Byte Period);
	 */

	memset(&timing, 0, sizeof(timing));
	get_mipi_dsi_timing_config_para(hisifd, phy_ctrl, &timing);

	if (timing.hline_time < (timing.hsa + timing.hbp + timing.dpi_hsize))
		HISI_FB_ERR("wrong hfp\n");

	set_reg(mipi_dsi_base + MIPIDSI_VID_HSA_TIME_OFFSET, timing.hsa, 12, 0);
	set_reg(mipi_dsi_base + MIPIDSI_VID_HBP_TIME_OFFSET, timing.hbp, 12, 0);
	set_reg(mipi_dsi_base + MIPI_LDI_DPI0_HRZ_CTRL3,
		dss_reduce(timing.dpi_hsize), 12, 0);
	set_reg(mipi_dsi_base + MIPIDSI_VID_HLINE_TIME_OFFSET,
		timing.hline_time, 15, 0);


	/* Configure core's phy parameters */
	set_reg(mipi_dsi_base + MIPIDSI_PHY_TMR_LPCLK_CFG_OFFSET,
		phy_ctrl->clk_lane_lp2hs_time, 10, 0);
	set_reg(mipi_dsi_base + MIPIDSI_PHY_TMR_LPCLK_CFG_OFFSET,
		phy_ctrl->clk_lane_hs2lp_time, 10, 16);

	outp32(mipi_dsi_base + MIPIDSI_PHY_TMR_CFG_OFFSET,
		(phy_ctrl->data_lane_lp2hs_time +
		(phy_ctrl->data_lane_hs2lp_time << 16)));

	HISI_FB_DEBUG("fb%d -\n", hisifd->index);
}

static bool check_pctrl_trstop_flag(
	struct hisi_fb_data_type *hisifd, int time_count)
{
	bool is_ready = false;
	int count;
	uint32_t tmp = 0;
	uint32_t tmp1 = 0;

	if (is_dual_mipi_panel(hisifd)) {
		for (count = 0; count < time_count; count++) {
			tmp = inp32(hisifd->mipi_dsi0_base +
					MIPIDSI_DPHYTX_TRSTOP_FLAG_OFFSET);
			tmp1 = inp32(hisifd->mipi_dsi1_base +
					MIPIDSI_DPHYTX_TRSTOP_FLAG_OFFSET);
			if ((tmp & tmp1 & 0x1) == 0x1) {
				is_ready = true;
				break;
			}
			udelay(2);
		}
	} else {
		for (count = 0; count < time_count; count++) {
			tmp = inp32(hisifd->mipi_dsi0_base +
					MIPIDSI_DPHYTX_TRSTOP_FLAG_OFFSET);
			if ((tmp & 0x1) == 0x1) {
				is_ready = true;
				break;
			}
			udelay(2);
		}
	}

	return is_ready;
}

static uint32_t get_stopstate_msk_value(uint8_t lane_nums)
{
	uint32_t stopstate_msk = 0;

	if (lane_nums == DSI_4_LANES)
		stopstate_msk = BIT(0);
	else if (lane_nums == DSI_3_LANES)
		stopstate_msk = BIT(0) | BIT(4);
	else if (lane_nums == DSI_2_LANES)
		stopstate_msk = BIT(0) | BIT(3) | BIT(4);
	else
		stopstate_msk = BIT(0) | BIT(2) | BIT(3) | BIT(4);

	return stopstate_msk;
}

bool mipi_dsi_wait_vfp_end(struct hisi_fb_data_type *hisifd,
	uint64_t lane_byte_clk, struct timeval *tv0)
{
	uint32_t hline_time;
	uint32_t vfp_line;
	uint32_t vfp_time;
	uint32_t stopstate_msk = 0;
	struct timeval tv1;
	uint32_t timediff = 0;
	bool is_ready = false;

	hline_time = (uint32_t)inp32(hisifd->mipi_dsi0_base +
		MIPIDSI_VID_HLINE_TIME_OFFSET) & VFP_TIME_MASK;

	vfp_line = (uint32_t)inp32(hisifd->mipi_dsi0_base +
		MIPIDSI_VID_VFP_LINES_OFFSET) & 0x3FF;

	if (lane_byte_clk != 0) {
		vfp_time = (vfp_line + VFP_TIME_OFFSET) * hline_time /
			((uint32_t)(lane_byte_clk / MILLION_CONVERT));
	} else {
		HISI_FB_ERR("vfp_time == 0\n");
		vfp_time = VFP_DEF_TIME;
	}

	HISI_FB_DEBUG("hisifd->mipi_dsi0_base = %x, hline_time = %d, vfp_line = %d, lane_byte_clk = %d\n",\
		hisifd->mipi_dsi0_base, hline_time, vfp_line, lane_byte_clk);

	stopstate_msk = get_stopstate_msk_value(hisifd->panel_info.mipi.lane_nums);

	set_reg(hisifd->mipi_dsi0_base + MIPIDSI_DPHYTX_CTRL_OFFSET, 1, 1, 0);
	set_reg(hisifd->mipi_dsi0_base + MIPIDSI_DPHYTX_CTRL_OFFSET,
		stopstate_msk, 5, 3);
	if (is_dual_mipi_panel(hisifd)) {
		set_reg(hisifd->mipi_dsi1_base + MIPIDSI_DPHYTX_CTRL_OFFSET, 1, 1, 0);
		set_reg(hisifd->mipi_dsi1_base + MIPIDSI_DPHYTX_CTRL_OFFSET,
			stopstate_msk, 5, 3);
	}
	HISI_FB_DEBUG("is_ready == %d, timediff = %d , vfp_time = %d\n", is_ready, timediff, vfp_time);
	while ((!is_ready) && (timediff < vfp_time)) {
		is_ready = check_pctrl_trstop_flag(hisifd, PCTRL_TRY_TIME);
		HISI_FB_INFO("is_ready == %d\n", is_ready);
		hisifb_get_timestamp(&tv1);
		timediff = hisifb_timestamp_diff(tv0, &tv1);
	}
	HISI_FB_INFO("timediff = %d us, vfp_time = %d us\n", timediff, vfp_time);
	set_reg(hisifd->mipi_dsi0_base + MIPIDSI_DPHYTX_CTRL_OFFSET, 0, 1, 0);
	if (is_dual_mipi_panel(hisifd))
		set_reg(hisifd->mipi_dsi1_base + MIPIDSI_DPHYTX_CTRL_OFFSET, 0, 1, 0);
	return is_ready;
}

int mipi_dsi_reset_underflow_clear(struct hisi_fb_data_type *hisifd)
{
	uint32_t vfp_time = 0;
	char __iomem *mipi_dsi_base;
	uint64_t lane_byte_clk;
	bool is_ready = false;
	struct timeval tv0;
	uint32_t timediff = 0;

	if (is_dp_panel(hisifd))
		goto reset_exit;

	if (hisifd->index == PRIMARY_PANEL_IDX)
		mipi_dsi_base = hisifd->mipi_dsi0_base;
	else if (hisifd->index == EXTERNAL_PANEL_IDX)
		mipi_dsi_base = hisifd->mipi_dsi1_base;
	else
		goto reset_exit;

	if (is_mipi_video_panel(hisifd)) {
		enable_ldi(hisifd);
		HISI_FB_INFO("without dsi reset,CMD_PKT_STATUS[0x%x],PHY_STATUS[0x%x],INT_ST0[0x%x],INT_ST1[0x%x] \n",
			inp32(mipi_dsi_base + MIPIDSI_CMD_PKT_STATUS_OFFSET), inp32(mipi_dsi_base + MIPIDSI_PHY_STATUS_OFFSET),
			inp32(mipi_dsi_base + MIPIDSI_INT_ST0_OFFSET), inp32(mipi_dsi_base + MIPIDSI_INT_ST1_OFFSET));

		goto reset_exit;
	}

	hisifb_get_timestamp(&tv0);

	lane_byte_clk = (hisifd->panel_info.mipi.phy_mode == DPHY_MODE) ?
		hisifd->panel_info.dsi_phy_ctrl.lane_byte_clk :
		hisifd->panel_info.dsi_phy_ctrl.lane_word_clk;

	is_ready = mipi_dsi_wait_vfp_end(hisifd, lane_byte_clk, &tv0);
	if (!is_ready)
		HISI_FB_ERR("check_pctrl_trstop_flag fail, vstate = 0x%x\n",
			inp32(mipi_dsi_base + MIPI_LDI_VSTATE));

	HISI_FB_INFO("timediff=%d us, vfp_time=%d us\n", timediff, vfp_time);

	set_reg(mipi_dsi_base + MIPIDSI_PWR_UP_OFFSET, 0x0, 1, 0);
	if (is_dual_mipi_panel(hisifd))
		set_reg(hisifd->mipi_dsi1_base + MIPIDSI_PWR_UP_OFFSET, 0x0, 1, 0);
	udelay(5); /* timing constraint */
	set_reg(mipi_dsi_base + MIPIDSI_PWR_UP_OFFSET, 0x1, 1, 0);
	if (is_dual_mipi_panel(hisifd))
		set_reg(hisifd->mipi_dsi1_base + MIPIDSI_PWR_UP_OFFSET, 0x1, 1, 0);

	ldi_data_gate(hisifd, true);
	enable_ldi(hisifd);

reset_exit:
	hisifd->underflow_flag = 0;
	return 0;
}

int mipi_dsi_bit_clk_upt_isr_handler(
	struct hisi_fb_data_type *hisifd)
{
	struct mipi_dsi_phy_ctrl phy_ctrl = {0};
	struct hisi_panel_info *pinfo = NULL;
	uint32_t dsi_bit_clk_upt;
	bool is_ready = false;
	uint8_t esd_enable;

	struct timeval tv0;
	uint64_t lane_byte_clk;
	uint32_t ldi_vstate;

	if (hisifd == NULL) {
		HISI_FB_ERR("hisifd is null!\n");
		return 0;
	}
	HISI_FB_DEBUG("fb%d +\n", hisifd->index);

	pinfo = &(hisifd->panel_info);
	dsi_bit_clk_upt = pinfo->mipi.dsi_bit_clk_upt;

	if (hisifd->index != PRIMARY_PANEL_IDX) {
		HISI_FB_ERR("fb%d, not support!\n", hisifd->index);
		return 0;
	}

	if (!spin_trylock(&hisifd->mipi_resource_lock)) {
		HISI_FB_INFO("dsi_bit_clk %u will update in next frame\n",
			dsi_bit_clk_upt);
		return 0;
	}

	hisifd->mipi_dsi_bit_clk_update = 1;
	esd_enable = pinfo->esd_enable;
	if (is_mipi_video_panel(hisifd)) {
		pinfo->esd_enable = 0;
		disable_ldi(hisifd);
	}

	spin_unlock(&hisifd->mipi_resource_lock);

	if (dsi_bit_clk_upt == pinfo->mipi.dsi_bit_clk) {
		hisifd->mipi_dsi_bit_clk_update = 0;
		return 0;
	}

	hisifb_get_timestamp(&tv0);

	if (pinfo->mipi.phy_mode == CPHY_MODE)
		get_dsi_cphy_ctrl(hisifd, &phy_ctrl);
	else
		get_dsi_dphy_ctrl(hisifd, &phy_ctrl);


	lane_byte_clk = hisifd->panel_info.dsi_phy_ctrl.lane_byte_clk;
	if (hisifd->panel_info.mipi.phy_mode == CPHY_MODE)
		lane_byte_clk = hisifd->panel_info.dsi_phy_ctrl.lane_word_clk;

	is_ready = mipi_dsi_wait_vfp_end(hisifd, lane_byte_clk, &tv0);
	ldi_vstate = inp32(hisifd->mipi_dsi0_base + MIPI_LDI_VSTATE) & 0xFFFF;
	if ((!is_ready) || (ldi_vstate != 0x1)) {
		if (is_mipi_video_panel(hisifd)) {
			pinfo->esd_enable = esd_enable;
			enable_ldi(hisifd);
		}
		hisifd->mipi_dsi_bit_clk_update = 0;
		HISI_FB_INFO("PERI_STAT0 is not ready or ldi_vstate=0x%x not in idle\n",
			ldi_vstate);
		return 0;
	}

	HISI_FB_DEBUG("start, phy status: 0x%x,0x%x, vstate: 0x%x,0x%x\n",
		inp32(hisifd->mipi_dsi0_base + MIPIDSI_PHY_STATUS_OFFSET),
		inp32(hisifd->mipi_dsi1_base + MIPIDSI_PHY_STATUS_OFFSET),
		inp32(hisifd->mipi_dsi0_base + MIPI_LDI_VSTATE),
		inp32(hisifd->mipi_dsi1_base + MIPI_LDI_VSTATE));

	if (is_mipi_cmd_panel(hisifd)) {
		mipi_dsi_set_cdphy_bit_clk_upt_cmd(hisifd, hisifd->mipi_dsi0_base,
			&phy_ctrl);
		if (is_dual_mipi_panel(hisifd))
			mipi_dsi_set_cdphy_bit_clk_upt_cmd(hisifd, hisifd->mipi_dsi1_base,
				&phy_ctrl);
	} else {
		set_reg(hisifd->mipi_dsi0_base + MIPIDSI_LPCLK_CTRL_OFFSET,
			0x0, DSI_CLK_BW, DSI_CLK_BS);
		mipi_dsi_set_cdphy_bit_clk_upt_video(hisifd, hisifd->mipi_dsi0_base,
			&phy_ctrl);
		set_reg(hisifd->mipi_dsi0_base + MIPIDSI_LPCLK_CTRL_OFFSET,
			0x1, DSI_CLK_BW, DSI_CLK_BS);
		if (is_dual_mipi_panel(hisifd)) {
			set_reg(hisifd->mipi_dsi1_base + MIPIDSI_LPCLK_CTRL_OFFSET,
				0x0, DSI_CLK_BW, DSI_CLK_BS);
			mipi_dsi_set_cdphy_bit_clk_upt_video(hisifd, hisifd->mipi_dsi1_base,
				&phy_ctrl);
			set_reg(hisifd->mipi_dsi1_base + MIPIDSI_LPCLK_CTRL_OFFSET,
				0x1, DSI_CLK_BW, DSI_CLK_BS);
		}

		HISI_FB_DEBUG("end, phy status: 0x%x,0x%x, vstate: 0x%x,0x%x\n",
			inp32(hisifd->mipi_dsi0_base + MIPIDSI_PHY_STATUS_OFFSET),
			inp32(hisifd->mipi_dsi1_base + MIPIDSI_PHY_STATUS_OFFSET),
			inp32(hisifd->mipi_dsi0_base + MIPI_LDI_VSTATE),
			inp32(hisifd->mipi_dsi1_base + MIPI_LDI_VSTATE));

		pinfo->esd_enable = esd_enable;
		enable_ldi(hisifd);
	}

	hisifd->mipi_dsi_bit_clk_update = 0;

	HISI_FB_INFO("Mipi clk successfully changed from %d M switch to %d M\n",
		pinfo->mipi.dsi_bit_clk, dsi_bit_clk_upt);

	pinfo->dsi_phy_ctrl = phy_ctrl;
	pinfo->mipi.dsi_bit_clk = dsi_bit_clk_upt;

	HISI_FB_DEBUG("fb%d -\n", hisifd->index);

	return 0;
}
