/*
 * hisi-kirin-ppll.h
 *
 * Hisilicon clock driver
 *
 * Copyright (c) 2018-2019 Huawei Technologies Co., Ltd.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */
#ifndef __LINUX_HISI_KIRIN_PPLL_H_
#define __LINUX_HISI_KIRIN_PPLL_H_

#include <soc_crgperiph_interface.h>
#include <soc_pmctrl_interface.h>
#include <soc_sctrl_interface.h>
#include <soc_acpu_baseaddr_interface.h>

#include "clk-kirin-common.h"
#if defined(SOC_ACPU_HSDT_CRG_BASE_ADDR)
#include <soc_hsdt_crg_interface.h>
#endif


enum {
	PPLL0 = 0,
	PPLL1,
	PPLL2,
	PPLL3,
	PPLL4,
	PPLL5,
	PPLL6 = 0x6,
	PPLL7 = 0x7,
	SCPLL = 0x8,
	PPLL2_B = 0x9,
	FNPLL1 = 0xA,
	FNPLL4 = 0xB,
	AUPLL = 0xC,
	PPLLMAX,
};

/*
 * Adapt to hi3xxx_ppll_setup func
 */
#ifdef SOC_CRGPERIPH_PEREN0_ppll3_en_cpu_START
#define PPLL3_EN_ACPU				SOC_CRGPERIPH_PEREN0_ppll3_en_cpu_START
#define PPLL3_EN_ACPU_ADDR(ADDR)		SOC_CRGPERIPH_PEREN0_ADDR(ADDR)
#define PPLL3_DIS_ACPU_ADDR(ADDR)		SOC_CRGPERIPH_PERDIS0_ADDR(ADDR)
#define PPLL3_GT_ACPU				SOC_CRGPERIPH_PEREN11_ppll3_gt_cpu_START
#define PPLL3_GT_ACPU_ADDR(ADDR)		SOC_CRGPERIPH_PEREN11_ADDR(ADDR)
#define PPLL3_DISGT_ACPU(ADDR)			SOC_CRGPERIPH_PERDIS11_ADDR(ADDR)
#else
#define PPLL3_EN_ACPU				SOC_CRGPERIPH_PLL_EN_VOTE_CTRL0_ppll3_en_vote_START
#define PPLL3_EN_ACPU_ADDR(ADDR)		SOC_CRGPERIPH_PLL_EN_VOTE_CTRL0_ADDR(ADDR)
#define PPLL3_DIS_ACPU_ADDR(ADDR)		SOC_CRGPERIPH_PLL_EN_VOTE_CTRL0_ADDR(ADDR)
#define PPLL3_GT_ACPU				SOC_CRGPERIPH_PLL_GT_VOTE_CTRL0_ppll3_gt_vote_START
#define PPLL3_GT_ACPU_ADDR(ADDR)		SOC_CRGPERIPH_PLL_GT_VOTE_CTRL0_ADDR(ADDR)
#define PPLL3_DISGT_ACPU(ADDR)			SOC_CRGPERIPH_PLL_GT_VOTE_CTRL0_ADDR(ADDR)
#endif

#ifdef SOC_CRGPERIPH_PEREN0_ppll2_en_cpu_START
#define PPLL2_EN_ACPU				SOC_CRGPERIPH_PEREN0_ppll2_en_cpu_START
#define PPLL2_EN_ACPU_ADDR(ADDR)		SOC_CRGPERIPH_PEREN0_ADDR(ADDR)
#define PPLL2_DIS_ACPU_ADDR(ADDR)		SOC_CRGPERIPH_PERDIS0_ADDR(ADDR)
#define PPLL2_GT_ACPU				SOC_CRGPERIPH_PEREN11_ppll2_gt_cpu_START
#define PPLL2_GT_ACPU_ADDR(ADDR)		SOC_CRGPERIPH_PEREN11_ADDR(ADDR)
#define PPLL2_DISGT_ACPU_ADDR(ADDR)		SOC_CRGPERIPH_PERDIS11_ADDR(ADDR)
#else
#define PPLL2_EN_ACPU				SOC_CRGPERIPH_PLL_EN_VOTE_CTRL0_ppll2_en_vote_START
#define PPLL2_EN_ACPU_ADDR(ADDR)		SOC_CRGPERIPH_PLL_EN_VOTE_CTRL0_ADDR(ADDR)
#define PPLL2_DIS_ACPU_ADDR(ADDR)		SOC_CRGPERIPH_PLL_EN_VOTE_CTRL0_ADDR(ADDR)
#define PPLL2_GT_ACPU				SOC_CRGPERIPH_PLL_GT_VOTE_CTRL0_ppll2_gt_vote_START
#define PPLL2_GT_ACPU_ADDR(ADDR)		SOC_CRGPERIPH_PLL_GT_VOTE_CTRL0_ADDR(ADDR)
#define PPLL2_DISGT_ACPU_ADDR(ADDR)		SOC_CRGPERIPH_PLL_GT_VOTE_CTRL0_ADDR(ADDR)
#endif

#ifdef SOC_PMCTRL_PPLL4CTRL0_ppll4_en_START
#define PPLL4_EN				SOC_PMCTRL_PPLL4CTRL0_ppll4_en_START
#define PPLL4_EN_ACPU_ADDR(ADDR)		SOC_PMCTRL_PPLL4CTRL0_ADDR(ADDR)
#define PPLL4_GT				SOC_PMCTRL_PPLL4CTRL1_gt_clk_ppll4_START
#define PPLL4_GT_ACPU_ADDR(ADDR)		SOC_PMCTRL_PPLL4CTRL1_ADDR(ADDR)
#define PPLL4CTRL0(ADDR)			SOC_PMCTRL_PPLL4CTRL0_ADDR(ADDR)
#else
#define PPLL4_EN				0
#define PPLL4_EN_ACPU_ADDR(ADDR)		NULL
#define PPLL4_GT				0
#define PPLL4_GT_ACPU_ADDR(ADDR)		NULL
#define PPLL4CTRL0(ADDR)			NULL
#endif

#ifdef SOC_PMCTRL_PPLL7CTRL0_ppll7_en_START
#define PPLL7_EN				SOC_PMCTRL_PPLL7CTRL0_ppll7_en_START
#define PPLL7_EN_ACPU_ADDR(ADDR)		SOC_PMCTRL_PPLL7CTRL0_ADDR(ADDR)
#define PPLL7_GT				SOC_PMCTRL_PPLL7CTRL1_gt_clk_ppll7_START
#define PPLL7_GT_ACPU_ADDR(ADDR)		SOC_PMCTRL_PPLL7CTRL1_ADDR(ADDR)
#define PPLL7CTRL0(ADDR)			SOC_PMCTRL_PPLL7CTRL0_ADDR(ADDR)
#else
#define PPLL7_EN				0
#define PPLL7_EN_ACPU_ADDR(ADDR)		NULL
#define PPLL7_GT				0
#define PPLL7_GT_ACPU_ADDR(ADDR)		NULL
#define PPLL7CTRL0(ADDR)			NULL
#endif

#ifdef SOC_PMCTRL_PPLL6CTRL0_ppll6_en_START
#define PPLL6_EN				SOC_PMCTRL_PPLL6CTRL0_ppll6_en_START
#define PPLL6_EN_ACPU_ADDR(ADDR)		SOC_PMCTRL_PPLL6CTRL0_ADDR(ADDR)
#define PPLL6_GT				SOC_PMCTRL_PPLL6CTRL1_gt_clk_ppll6_START
#define PPLL6_GT_ACPU_ADDR(ADDR)		SOC_PMCTRL_PPLL6CTRL1_ADDR(ADDR)
#define PPLL6CTRL0(ADDR)			SOC_PMCTRL_PPLL6CTRL0_ADDR(ADDR)
#else
#define PPLL6_EN				0
#define PPLL6_EN_ACPU_ADDR(ADDR)		NULL
#define PPLL6_GT				0
#define PPLL6_GT_ACPU_ADDR(ADDR)		NULL
#define PPLL6CTRL0(ADDR)			NULL
#endif

#if defined(SOC_HSDT_CRG_PCIEPLL_CTRL0_pciepll_en_START)
#define SCPLL_EN				SOC_HSDT_CRG_PCIEPLL_CTRL0_pciepll_en_START
#define SCPLL_EN_ACPU_ADDR(ADDR)		SOC_HSDT_CRG_PCIEPLL_CTRL0_ADDR(ADDR)
#define SCPLL_GT				SOC_HSDT_CRG_PCIEPLL_CTRL1_gt_clk_pciepll_START
#define SCPLL_GT_ACPU_ADDR(ADDR)		SOC_HSDT_CRG_PCIEPLL_CTRL1_ADDR(ADDR)
#define SCPLL_BP				SOC_HSDT_CRG_PCIEPLL_CTRL0_pciepll_bp_START
#define SCPLL_BP_ACPU_ADDR(ADDR)		SOC_HSDT_CRG_PCIEPLL_CTRL0_ADDR(ADDR)
#define SCPLL_LOCK_STAT(ADDR)			SOC_HSDT_CRG_PCIEPLL_STAT_ADDR(ADDR)
#define SCPLL_LOCK_BIT				SOC_HSDT_CRG_PCIEPLL_STAT_pciepll_sc_lock_START
#else
#define SCPLL_EN				0
#define SCPLL_EN_ACPU_ADDR(ADDR)		NULL
#define SCPLL_GT				0
#define SCPLL_GT_ACPU_ADDR(ADDR)		NULL
#define SCPLL_BP				0
#define SCPLL_BP_ACPU_ADDR(ADDR)		NULL
#define SCPLL_LOCK_STAT(ADDR)			NULL
#define SCPLL_LOCK_BIT				0
#endif

#if defined(SOC_SCTRL_SC_AO_CRG_STA_SEP0_aupll_lock_START)
#define AUPLL_LOCK				SOC_SCTRL_SC_AO_CRG_STA_SEP0_aupll_lock_START
#define AUPLL_LOCK_ADDR(ADDR)			SOC_SCTRL_SC_AO_CRG_STA_SEP0_ADDR(ADDR)
#else
#define AUPLL_LOCK				0
#define AUPLL_LOCK_ADDR(ADDR)			NULL
#endif
/* ******************* END ********************** */

#define PLL_REG_NUM				2
#define PPLLCTRL0(n)				(0x030 + ((n) << 3))
/* ********** PLL DEFINE **************** */
#define PPLLCTRL0_LOCK				26
#define AP_PPLL_STABLE_TIME			1000
#define PLL_MASK_OFFSET				16

/* PPLL */
struct hi3xxx_ppll_clk {
	struct clk_hw	hw;
	u32		ref_cnt; /* reference count */
	u32		en_cmd[LPM3_CMD_LEN];
	u32		dis_cmd[LPM3_CMD_LEN];
	u32		en_ctrl[PLL_REG_NUM];
	u32		gt_ctrl[PLL_REG_NUM];
	u32		bypass_ctrl[PLL_REG_NUM];
	u32		pll_ctrl0;
	void __iomem	*addr;   /* base addr */
	void __iomem	*endisable_addr;
	void __iomem	*sctrl;  /* sysctrl addr */
	u32		flags;
	spinlock_t	*lock;
};

#endif
