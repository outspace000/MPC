/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2017. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include <product_config.h>
#include <hi_eipf.h>
#include <osl_bio.h>
#include <linux/pm.h>
#include <linux/clk.h>
#include <linux/slab.h>
#include <linux/version.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 14, 0)
#include <linux/interrupt.h>
#endif
#include <linux/platform_device.h>
#include <linux/of_platform.h>
#include <linux/dma-mapping.h>
#include <linux/module.h>
#include <securec.h>
#include <mdrv_sysboot.h>
#include <bsp_reset.h>
#include <bsp_slice.h>
#include <bsp_shared_ddr.h>
#include <bsp_maa.h>
#include "ipf.h"
#include "bsp_eipf.h"

#define INT_SUPPRESS_INTERVAL (10)

struct ipf_ctx_s g_ipf_ap = {0};

struct int_handler eipf_int_table[64] = {
    { "ul_rdq0_rpt_int1", 0, NULL },
    { "ul_rdq0_timeout_int1", 0, NULL },
    { "ul_rdq0_full_int1", 0, NULL },
    { "ul_rdq0_pkt_cnt_of_int1", 0, NULL },
    { "ul_rdq0_wptr_update_int1", 0, NULL },
    { "ul_rdq1_rpt_int1", 0, NULL },
    { "ul_rdq1_timeout_int1", 0, NULL },
    { "ul_rdq1_full_int1", 0, NULL },
    { "ul_rdq1_pkt_cnt_of_int1", 0, NULL },
    { "ul_rdq1_wptr_update_int1", 0, NULL },
    { "ul_bdq0_disable_end_int1", 0, NULL },
    { "ul_bdq0_epty_int1", 0, NULL },
    { "ul_bdq0_rptr_update_int1", 0, NULL },
    { "ul_bdq1_disable_end_int1", 0, NULL },
    { "ul_bdq1_epty_int1", 0, NULL },
    { "ul_bdq1_rptr_update_int1", 0, NULL },
    { "ul_adq0_amst_epty_int1", 0, NULL },
    { "ul_adq1_amst_epty_int1", 0, NULL },
    { "bus_error_w_int1", 0, NULL },
    { "bus_error_r_int1", 0, NULL },
    { "reserved", 0, NULL },
    { "reserved", 0, NULL },
    { "reserved", 0, NULL },
    { "reserved", 0, NULL },
    { "reserved", 0, NULL },
    { "reserved", 0, NULL },
    { "reserved", 0, NULL },
    { "reserved", 0, NULL },
    { "reserved", 0, NULL },
    { "reserved", 0, NULL },
    { "reserved", 0, NULL },
    { "reserved", 0, NULL },
    { "dl_rdq_rpt_int0", 0, NULL },
    { "dl_rdq_timeout_int0", 0, NULL },
    { "dl_rdq_full_int0", 0, NULL },
    { "dl_rdq_pkt_cnt_of_int0", 0, NULL },
    { "dl_rdq_wptr_update_int0", 0, NULL },
    { "dl_bdq0_disable_end_int0", 0, NULL },
    { "dl_bdq0_epty_int0", 0, NULL },
    { "dl_bdq0_rptr_update_int0", 0, NULL },
    { "dl_bdq1_disable_end_int0", 0, NULL },
    { "dl_bdq1_epty_int0", 0, NULL },
    { "dl_bdq1_rptr_update_int0", 0, NULL },
    { "dl_adq0_amst_epty_int0", 0, NULL },
    { "dl_adq1_amst_epty_int0", 0, NULL },
    { "dl_refl_nas_done_int0", 0, NULL },
    { "dl_rnrdq_wptr_update_int0", 0, NULL },
    { "dl_rnrdq_full_int0", 0, NULL },
    { "dl_rnrdq_full_wr_int0", 0, NULL },
    { "dl_refl_as_done_int0", 0, NULL },
    { "dl_rardq_wptr_update_int0", 0, NULL },
    { "dl_rardq_full_int0", 0, NULL },
    { "dl_rardq_full_wr_int0", 0, NULL },
    { "timer_cnt_eq0_int0", 0, NULL },
    { "ipf_gen0_int0", 0, NULL },
    { "ipf_gen1_int0", 0, NULL },
    { "ipf_gen2_int0", 0, NULL },
    { "reserved", 0, NULL },
    { "reserved", 0, NULL },
    { "reserved", 0, NULL },
    { "reserved", 0, NULL },
    { "reserved", 0, NULL },
    { "reserved", 0, NULL },
    { "reserved", 0, NULL },
};
#ifdef IPF_UL_DMA
static void ipf_recyle_bd(void);
#endif
int ipf_register_int_callback(unsigned char *name, void (*callback)(void))
{
    unsigned int i;
    for (i = 0; i < sizeof(eipf_int_table) / sizeof(eipf_int_table[0]); i++) {
        if (!strcmp(name, eipf_int_table[i].name)) {
            eipf_int_table[i].callback = callback;
            return 0;
        }
    }
    return -1;
}

static inline void phy_addr_write(u64 phy_addr, void *reg_h, void *reg_l)
{
    union phy_addr_u pa;

    pa.addr = phy_addr;

    writel(pa.u32_t.addr_h, reg_h);
    writel(pa.u32_t.addr_l, reg_l);
}

static inline u64 phy_addr_read(const void *reg_h, const void *reg_l)
{
    union phy_addr_u pa;

    pa.u32_t.addr_h = readl(reg_h);
    pa.u32_t.addr_l = readl(reg_l);

    return pa.addr;
}

static int ipf_pm_prepare(struct device *pdev)
{
    unsigned int val;

    val = ipf_read(IPF_CH0_STATE_REG);
    if (UFIELD(U_IPF_CH1_STATE, &val).dl_bdq0_busy) {
        g_ipf_ap.dl_bdq0_busy++;
        return -1;
    }

    if (UFIELD(U_IPF_CH1_STATE, &val).dl_bdq1_busy) {
        g_ipf_ap.dl_bdq1_busy++;
        return -1;
    }

    val = ipf_read(IPF_CH1_RDQ_DEPTH_REG);
    if (UFIELD(U_IPF_CH1_RDQ_DEPTH, &val).dl_rdq_depth) {
        g_ipf_ap.dl_rdq_depth++;
        return -1;
    }

    val = ipf_read(IPF_CH0_BDQ0_DEPTH_REG);
    if (UFIELD(U_IPF_CH0_BDQ0_DEPTH, &val).ul_bdq0_depth) {
        g_ipf_ap.ul_bdq0_depth++;
        return -1;
    }

    g_ipf_ap.prepare_done++;
    return 0;
}

static int ipf_pm_suspend(struct device *pdev)
{
#ifdef IPF_UL_DMA
    unsigned long flags;
#endif
    unsigned int reg;
    UPDATE1(reg, IPF_INT2_EN_DL, dl_rdq_wptr_update_en2, 1);
#ifdef IPF_UL_DMA
    spin_lock_irqsave(&g_ipf_ap.bd_lock, flags);
    ipf_recyle_bd();
    spin_unlock_irqrestore(&g_ipf_ap.bd_lock, flags);
#endif
    g_ipf_ap.suspend_done++;
    return 0;
}

static int ipf_pm_resume(struct device *pdev)
{
    g_ipf_ap.bdq0_rptr_old = ipf_read(IPF_CH0_BDQ_RPTR_REG(0));
    g_ipf_ap.resume_done++;

    return 0;
}

static struct dev_pm_ops ipf_dev_pm_ops = {
    .prepare = ipf_pm_prepare,
    .suspend_noirq = ipf_pm_suspend,
    .resume_noirq = ipf_pm_resume,
};

static irqreturn_t ipf_interrupt(int x, void *arg)
{
    unsigned long bit;
    unsigned int reg[2];

    reg[0] = ipf_read(IPF_INT2_UL_REG);
    ipf_write(reg[0], IPF_INT_STATE_UL_REG);
    reg[1] = ipf_read(IPF_INT2_DL_REG);
    ipf_write(reg[1], IPF_INT_STATE_DL_REG);

    for_each_set_bit(bit, (unsigned long *)reg, INT_REG_SCALE) {
        eipf_int_table[bit].cnt++;
        if (eipf_int_table[bit].callback) {
            eipf_int_table[bit].callback();
        }
    }

    return IRQ_HANDLED;
}

static void ipf_coop_maa(void)
{
    unsigned int reg;
    unsigned int offset;
    dma_addr_t push_target;

    phy_addr_write(g_ipf_ap.adq0_dma, (unsigned char *)g_ipf_ap.regs + IPF_CH1_ADQ0_BASE_H_REG,
                   (unsigned char *)g_ipf_ap.regs + IPF_CH1_ADQ0_BASE_L_REG);

    phy_addr_write(g_ipf_ap.adq1_dma, (unsigned char *)g_ipf_ap.regs + IPF_CH1_ADQ1_BASE_H_REG,
                   (unsigned char *)g_ipf_ap.regs + IPF_CH1_ADQ1_BASE_L_REG);

    UPDATE4(reg, IPF_CH1_ADQ_SIZE_CTRL, dl_adq_plen_th, MAA_OPIPE_LEVEL_0_SIZE, dl_adq_empty_th,
            IPF_DLAD0_DESC_SIZE - 32, dl_adq1_size_sel, IPF_DL_ADQ_LEN_EXP, dl_adq0_size_sel, IPF_DL_ADQ_LEN_EXP);

    if (g_ipf_ap.soft_push) {
        push_target = g_ipf_ap.adq0_wptr;
    }
    else {
        push_target = g_ipf_ap.res->start + IPF_CH1_ADQ0_WPTR_REG;
    }
    offset = bsp_maa_set_adqbase(g_ipf_ap.adq0_dma, push_target, g_ipf_ap.adq0_size,
                                 MAA_IPIPE_FOR_IPF_512);

    ipf_write(offset, IPF_CH1_ADQ0_RPTR_UPDATE_ADDR_L_REG);
    ipf_write(0, IPF_CH1_ADQ0_RPTR_UPDATE_ADDR_H_REG);

    if (g_ipf_ap.soft_push) {
        push_target = g_ipf_ap.adq1_wptr;
    }
    else {
        push_target = g_ipf_ap.res->start + IPF_CH1_ADQ1_WPTR_REG;
    }
    offset = bsp_maa_set_adqbase(g_ipf_ap.adq1_dma, push_target, g_ipf_ap.adq1_size,
                                 MAA_IPIPE_FOR_IPF_2K);

    ipf_write(offset, IPF_CH1_ADQ1_RPTR_UPDATE_ADDR_L_REG);
    ipf_write(0, IPF_CH1_ADQ1_RPTR_UPDATE_ADDR_H_REG);

    UPDATE1(reg, IPF_CH1_ADQ_EN_CTRL, dl_adq_en, 2);
}

#if (defined(CONFIG_BALONG_ESPE))
void ipf_pm_check_bd(void)
{
    unsigned int ipf_ch0_int0;
    unsigned int ipf_ch0_int1;
    unsigned int ipf_ch0_stat;
    unsigned int ipf_bd_wp;
    unsigned int ipf_bd_rp;

    ipf_bd_rp = ipf_read(IPF_CH0_BDQ0_RPTR_REG);
    ipf_ch0_int0 = ipf_read(IPF_INT0_UL_REG);
    ipf_ch0_int1 = ipf_read(IPF_INT1_UL_REG);
    ipf_ch0_stat = ipf_read(IPF_CH0_STATE_REG);
    ipf_bd_wp = ipf_read(IPF_CH0_BDQ0_WPTR_REG);

    bsp_err("ipf_ch0_int0 = 0x%x ipf_ch0_int1 = 0x%x ipf_ch0_stat = 0x%x ipf_bd_wp = 0x%x ipf_bd_rp = 0x%x\n", ipf_ch0_int0, ipf_ch0_int1, 
        ipf_ch0_stat, ipf_bd_wp, ipf_bd_rp);
}

static int ipf_coop_spe(void)
{
    unsigned int reg;
    unsigned int dl_rdq0_amst_full_th;

    if (memset_s(&g_ipf_ap.attr, sizeof(g_ipf_ap.attr), 0, sizeof(struct espe_port_comm_attr))) {
        bsp_err("memset_s failed\n");
    }
    g_ipf_ap.attr.enc_type = SPE_ENC_IPF;
    g_ipf_ap.attr.td_depth = IPF_DL_DESC_LEN;
    g_ipf_ap.attr.rd_depth = IPF_UL_DESC_LEN;
    g_ipf_ap.spe_portno = bsp_espe_alloc_port(&g_ipf_ap.attr);
    if (g_ipf_ap.spe_portno < 0) {
        bsp_err("bsp_espe_alloc_port error\n");
        return -1;
    }

    g_ipf_ap.ipf_attr.check_ipf_bd = ipf_pm_check_bd;

    g_ipf_ap.ipf_attr.ipf_addr.dltd_rptr_addr =
        (dma_addr_t)(uintptr_t)((unsigned char *)g_ipf_ap.regs + IPF_CH1_RDQ_RPTR_REG);
    g_ipf_ap.ipf_attr.ipf_addr.ulrd_wptr_addr = g_ipf_ap.res->start + IPF_CH0_BDQ0_WPTR_REG;

    if (bsp_espe_set_ipfproperty(&g_ipf_ap.ipf_attr)) {
        bsp_err("[%s]wan_eipfport_reg_get failed@line:%x!\n", __func__, __LINE__);
        return -1;
    }

    g_ipf_ap.rdq_size = g_ipf_ap.attr.td_depth;
    g_ipf_ap.bdq0_size = g_ipf_ap.attr.rd_depth;
    g_ipf_ap.rdq_base = g_ipf_ap.ipf_attr.spe_addr.dltd_base_addr_v;
    g_ipf_ap.bdq0_base = g_ipf_ap.ipf_attr.spe_addr.ulrd_base_addr_v;
    g_ipf_ap.ulrd_rptr_virt = g_ipf_ap.ipf_attr.spe_addr.ulrd_rptr_addr_v;

    if (g_ipf_ap.ipf_attr.ext_desc_en) {
        UPDATE2(reg, IPF_CTRL, dl_rdq_with_head, 1, ul_bdq_with_head, 1);
    } else {
        UPDATE2(reg, IPF_CTRL, dl_rdq_with_head, 0, ul_bdq_with_head, 0);
    }

    dl_rdq0_amst_full_th = ipf_read(IPF_CH1_RDQ_SIZE_REG);
    ipf_write(((g_ipf_ap.rdq_size - 1) | dl_rdq0_amst_full_th), IPF_CH1_RDQ_SIZE_REG);
    ipf_write(g_ipf_ap.bdq0_size - 1, IPF_CH0_BDQ0_SIZE_REG);

    phy_addr_write(g_ipf_ap.ipf_attr.spe_addr.ulrd_base_addr, (unsigned char *)g_ipf_ap.regs + IPF_CH0_BDQ0_BADDR_H_REG,
                   (unsigned char *)g_ipf_ap.regs + IPF_CH0_BDQ0_BADDR_L_REG);

    phy_addr_write(g_ipf_ap.ipf_attr.spe_addr.ulrd_rptr_addr,
                   (unsigned char *)g_ipf_ap.regs + IPF_CH0_BDQ0_RPTR_UPDATE_ADDR_H_REG,
                   (unsigned char *)g_ipf_ap.regs + IPF_CH0_BDQ0_RPTR_UPDATE_ADDR_L_REG);

    phy_addr_write(g_ipf_ap.ipf_attr.spe_addr.dltd_base_addr, (unsigned char *)g_ipf_ap.regs + IPF_CH1_RDQ_BADDR_H_REG,
                   (unsigned char *)g_ipf_ap.regs + IPF_CH1_RDQ_BADDR_L_REG);

    phy_addr_write(g_ipf_ap.ipf_attr.spe_addr.dltd_wptr_addr,
                   (unsigned char *)g_ipf_ap.regs + IPF_CH1_RDQ_WPTR_UPDATE_ADDR_H_REG,
                   (unsigned char *)g_ipf_ap.regs + IPF_CH1_RDQ_WPTR_UPDATE_ADDR_L_REG);

    return bsp_espe_enable_port(g_ipf_ap.spe_portno);
}
#else
static int ipf_dl_init_standalone(void)
{
    ipf_write(g_ipf_ap.rdq_size - 1, IPF_CH1_RDQ_SIZE_REG);
    phy_addr_write(g_ipf_ap.rdq_dma, (unsigned char *)g_ipf_ap.regs + IPF_CH1_RDQ_BADDR_H_REG,
                   (unsigned char *)g_ipf_ap.regs + IPF_CH1_RDQ_BADDR_L_REG);

    ipf_write(g_ipf_ap.bdq0_size - 1, IPF_CH0_BDQ0_SIZE_REG);
    phy_addr_write(g_ipf_ap.bdq0_dma, (unsigned char *)g_ipf_ap.regs + IPF_CH0_BDQ0_BADDR_H_REG,
                   (unsigned char *)g_ipf_ap.regs + IPF_CH0_BDQ0_BADDR_L_REG);

    ipf_write(IPF_UL_INT_MASK, IPF_INT2_EN_UL_REG);
    ipf_write(IPF_DL_INT_MASK, IPF_INT2_EN_DL_REG);

    return 0;
}
#endif
#ifdef IPF_UL_DMA
static void ipf_free_pkt(unsigned long long rd_addr)
{
    struct sk_buff *skb = NULL;

    if (MAA_SKB_FROM_TCP_IP == bsp_maa_get_addr_type(rd_addr)) {
        skb = bsp_maa_skb_unmap(rd_addr);
        dev_kfree_skb_any(skb);
    } else {
        bsp_maa_free(rd_addr + ETH_HLEN);
    }
}

static void ipf_recyle_bd(void)
{
    unsigned int i;
    unsigned int bd_total_num = 0;
    unsigned int rptr = ipf_read(IPF_CH0_BDQ_RPTR_REG(0));
    struct ipf_ulbd_s *bd = (struct ipf_ulbd_s *)g_ipf_ap.bdq0_base;

    if (rptr == g_ipf_ap.bdq0_rptr_old) {
        return;
    }
    if (g_ipf_ap.bdq0_rptr_old <= rptr) {
        for (i = g_ipf_ap.bdq0_rptr_old; i < rptr; i++) {
            ipf_free_pkt(((unsigned long long)bd[i].input_pointer_h << 32) + bd[i].input_pointer_l);
            bd_total_num++;
        }

    } else {
        for (i = g_ipf_ap.bdq0_rptr_old; i != g_ipf_ap.bdq0_size; i++) {
            ipf_free_pkt(((unsigned long long)bd[i].input_pointer_h << 32) + bd[i].input_pointer_l);
            g_ipf_ap.bdq_recyle_cnt++;
            bd_total_num++;

        }

        for (i = 0; i < rptr; i++) {
            ipf_free_pkt(((unsigned long long)bd[i].input_pointer_h << 32) + bd[i].input_pointer_l);
            g_ipf_ap.bdq_recyle_cnt++;
            bd_total_num++;
        }
    }
    g_ipf_ap.bdq0_rptr_old = rptr;
    writel(rptr, g_ipf_ap.ulrd_rptr_virt);

    if (bd_total_num <= 1) {
        g_ipf_ap.release_num_per_interval[IPF_NUM_1]++;
        return;
    }
    
    if (bd_total_num <= 64) {
        g_ipf_ap.release_num_per_interval[IPF_NUM_64]++;
        return;
    }

    if (bd_total_num <= 128) {
        g_ipf_ap.release_num_per_interval[IPF_NUM_128]++;
        return;
    }
    
    if (bd_total_num <= 256) {
        g_ipf_ap.release_num_per_interval[IPF_NUM_256]++;
        return;
    }
    
    if (bd_total_num <= 512) {
        g_ipf_ap.release_num_per_interval[IPF_NUM_512]++;
        return;
    }
    
    g_ipf_ap.release_num_per_interval[IPF_NUM_TOOLARGE]++;
    
}

void ipf_recyle_init_hw(void)
{
    unsigned int reg;
    phy_addr_write(g_ipf_ap.bdq0_rptr_dma, (unsigned char *)g_ipf_ap.regs + IPF_CH0_BDQ0_RPTR_UPDATE_ADDR_H_REG,
                   (unsigned char *)g_ipf_ap.regs + IPF_CH0_BDQ0_RPTR_UPDATE_ADDR_L_REG);

    UPDATE1(reg, IPF_INT2_EN_UL, ul_bdq0_rptr_update_en2, 1);
    UPDATE1(reg, IPF_INT2_SUP_TIME, int2_supress_time, INT_SUPPRESS_INTERVAL);
}

int ipf_recyle_init(void)
{
    g_ipf_ap.bdq0_rptr = dma_alloc_coherent(g_ipf_ap.dev, sizeof(unsigned int), &g_ipf_ap.bdq0_rptr_dma, GFP_KERNEL);
    if (!g_ipf_ap.bdq0_rptr) {
        bsp_err("[init]dma_alloc_coherent failed, bdq0_rptr invalid\n");
        return -ENOMEM;
    }

    ipf_recyle_init_hw();

    ipf_register_int_callback("ul_bdq0_rptr_update_int1", ipf_recyle_bd);

    return 0;
}
#endif
static int ipf_resource_alloc(void)
{
    dma_set_mask_and_coherent(g_ipf_ap.dev, g_ipf_ap.dma_mask);
    of_dma_configure(g_ipf_ap.dev, 0);

    g_ipf_ap.adq0_base = 0;
    g_ipf_ap.adq1_base = 0;
    g_ipf_ap.rdq_base = 0;
    g_ipf_ap.bdq0_base = 0;

    g_ipf_ap.adq0_size = IPF_DLAD0_MEM_SIZE;
    g_ipf_ap.adq0_base = dma_alloc_coherent(g_ipf_ap.dev, (g_ipf_ap.adq0_size * sizeof(struct ipf64_ad_s)),
                                            &g_ipf_ap.adq0_dma, GFP_KERNEL);

    if (g_ipf_ap.adq0_base == NULL) {
        bsp_err("[init]dma_alloc_coherent failed, adq0_base invalid\n");
        return -ENOMEM;
    }

    if (!dma_alloc_coherent(g_ipf_ap.dev, sizeof(unsigned int),
                                            &g_ipf_ap.adq0_wptr, GFP_KERNEL)) {
        bsp_err("[init]dma_alloc_coherent failed, adq0_wptr invalid\n");
        return -ENOMEM;
    }
    g_ipf_ap.adq1_size = IPF_DLAD1_MEM_SIZE;
    g_ipf_ap.adq1_base = dma_alloc_coherent(g_ipf_ap.dev, (g_ipf_ap.adq1_size * sizeof(struct ipf64_ad_s)),
                                            &g_ipf_ap.adq1_dma, GFP_KERNEL);

    if (g_ipf_ap.adq1_base == NULL) {
        bsp_err("[init]dma_alloc_coherent failed, adq1_base invalid\n");
        return -ENOMEM;
    }
    if (!dma_alloc_coherent(g_ipf_ap.dev, sizeof(unsigned int),
                                            &g_ipf_ap.adq1_wptr, GFP_KERNEL)) {
        bsp_err("[init]dma_alloc_coherent failed, adq1_wptr invalid\n");
        return -ENOMEM;
    }
#if (defined(CONFIG_BALONG_ESPE))
#else
    g_ipf_ap.rdq_size = IPF_DL_DESC_LEN;
    g_ipf_ap.rdq_base = dma_alloc_coherent(g_ipf_ap.dev, sizeof(struct ipf_dlrd_s) * g_ipf_ap.rdq_size,
                                           &g_ipf_ap.rdq_dma, GFP_KERNEL);
    if (g_ipf_ap.rdq_base == NULL) {
        bsp_err("dma_alloc_coherent for rdq failed\n");
        return -ENOMEM;
    }

    g_ipf_ap.bdq0_size = IPF_UL_DESC_LEN;
    g_ipf_ap.bdq0_base = dma_alloc_coherent(g_ipf_ap.dev, sizeof(struct ipf_ulbd_s) * g_ipf_ap.bdq0_size,
                                            &g_ipf_ap.bdq0_dma, GFP_KERNEL);
    if (g_ipf_ap.bdq0_base == NULL) {
        bsp_err("dma_alloc_coherent for rdq failed\n");
        dma_free_coherent(g_ipf_ap.dev, sizeof(struct ipf_dlrd_s) * g_ipf_ap.rdq_size, g_ipf_ap.bdq0_base,
                          g_ipf_ap.bdq0_dma);
        return -ENOMEM;
    }
#endif
    return 0;
}

static void ipf_resource_free(void)
{
    if (g_ipf_ap.adq0_base != NULL) {
        dma_free_coherent(g_ipf_ap.dev, (g_ipf_ap.adq0_size * sizeof(struct ipf64_ad_s)), g_ipf_ap.adq0_base,
                          g_ipf_ap.adq0_dma);
    }

    if (g_ipf_ap.adq1_base != NULL) {
        dma_free_coherent(g_ipf_ap.dev, (g_ipf_ap.adq1_size * sizeof(struct ipf64_ad_s)), g_ipf_ap.adq1_base,
                          g_ipf_ap.adq1_dma);
    }

    if (g_ipf_ap.rdq_base != NULL) {
        dma_free_coherent(g_ipf_ap.dev, (g_ipf_ap.rdq_size * sizeof(struct ipf_dlrd_s)), g_ipf_ap.rdq_base,
                          g_ipf_ap.rdq_dma);
    }

    if (g_ipf_ap.bdq0_base != NULL) {
        dma_free_coherent(g_ipf_ap.dev, (g_ipf_ap.bdq0_size * sizeof(struct ipf_ulbd_s)), g_ipf_ap.bdq0_base,
                          g_ipf_ap.bdq0_dma);
    }
}

static void ipf_rd_intr(void)
{
    unsigned int reg;
    UPDATE1(reg, IPF_INT_STATE_DL, dl_rdq_wptr_update, 1);
    UPDATE1(reg, IPF_INT2_EN_DL, dl_rdq_wptr_update_en2, 0);
}

int ipf_dl_wake_init(void)
{
    if (ipf_register_int_callback("dl_rdq_wptr_update_int0", ipf_rd_intr)) {
        bsp_err("ipf_register_int_callback failed!\n");
        return -EIO;
    }

    return 0;
}

void ipf_reset(void)
{
    writel_relaxed(g_ipf_ap.reset_peri_crg[4], (void *)(g_ipf_ap.reset_reg + g_ipf_ap.reset_peri_crg[1]));
    writel_relaxed(g_ipf_ap.reset_peri_crg[4], (void *)(g_ipf_ap.reset_reg + g_ipf_ap.reset_peri_crg[2]));
}

void ipf_deinit(void)
{
    phy_addr_write(0, (unsigned char *)g_ipf_ap.regs + IPF_CH0_BDQ0_RPTR_UPDATE_ADDR_H_REG,
                   (unsigned char *)g_ipf_ap.regs + IPF_CH0_BDQ0_RPTR_UPDATE_ADDR_L_REG);
    phy_addr_write(0, (unsigned char *)g_ipf_ap.regs + IPF_CH1_RDQ_WPTR_UPDATE_ADDR_H_REG,
                   (unsigned char *)g_ipf_ap.regs + IPF_CH1_RDQ_WPTR_UPDATE_ADDR_L_REG);

    ipf_write(0, IPF_CH1_ADQ0_RPTR_UPDATE_ADDR_L_REG);
    ipf_write(0, IPF_CH1_ADQ0_RPTR_UPDATE_ADDR_H_REG);
    ipf_write(0, IPF_CH1_ADQ1_RPTR_UPDATE_ADDR_L_REG);
    ipf_write(0, IPF_CH1_ADQ1_RPTR_UPDATE_ADDR_H_REG);
}

void bsp_ipf_reinit(void)
{
#if (defined(CONFIG_BALONG_ESPE))
    unsigned int reg;
#endif

    bsp_err("ipf_reset++\n");
    ipf_reset();
    bsp_err("ipf_reset--\n");
    g_ipf_ap.bdq0_rptr_old = 0;

    ipf_coop_maa();
#if (defined(CONFIG_BALONG_ESPE))
    if (g_ipf_ap.ipf_attr.ext_desc_en) {
        UPDATE2(reg, IPF_CTRL, dl_rdq_with_head, 1, ul_bdq_with_head, 1);
    } else {
        UPDATE2(reg, IPF_CTRL, dl_rdq_with_head, 0, ul_bdq_with_head, 0);
    }

    ipf_write(g_ipf_ap.rdq_size - 1, IPF_CH1_RDQ_SIZE_REG);
    ipf_write(g_ipf_ap.bdq0_size - 1, IPF_CH0_BDQ0_SIZE_REG);

    phy_addr_write(g_ipf_ap.ipf_attr.spe_addr.ulrd_base_addr, (unsigned char *)g_ipf_ap.regs + IPF_CH0_BDQ0_BADDR_H_REG,
                   (unsigned char *)g_ipf_ap.regs + IPF_CH0_BDQ0_BADDR_L_REG);

    phy_addr_write(g_ipf_ap.ipf_attr.spe_addr.ulrd_rptr_addr,
                   (unsigned char *)g_ipf_ap.regs + IPF_CH0_BDQ0_RPTR_UPDATE_ADDR_H_REG,
                   (unsigned char *)g_ipf_ap.regs + IPF_CH0_BDQ0_RPTR_UPDATE_ADDR_L_REG);

    phy_addr_write(g_ipf_ap.ipf_attr.spe_addr.dltd_base_addr, (unsigned char *)g_ipf_ap.regs + IPF_CH1_RDQ_BADDR_H_REG,
                   (unsigned char *)g_ipf_ap.regs + IPF_CH1_RDQ_BADDR_L_REG);

    phy_addr_write(g_ipf_ap.ipf_attr.spe_addr.dltd_wptr_addr,
                   (unsigned char *)g_ipf_ap.regs + IPF_CH1_RDQ_WPTR_UPDATE_ADDR_H_REG,
                   (unsigned char *)g_ipf_ap.regs + IPF_CH1_RDQ_WPTR_UPDATE_ADDR_L_REG);
#endif
#ifdef IPF_UL_DMA
    ipf_recyle_init_hw();
#endif
}

int ipf_mdmreset_cb(drv_reset_cb_moment_e eparam, int userdata)
{
    if (MDRV_RESET_CB_BEFORE == eparam) {
        ipf_deinit();
    }

    return 0;
}

static int ipf_probe(struct platform_device *pdev)
{
    g_ipf_ap.dev = &pdev->dev;
    g_ipf_ap.dma_mask = 0xffffffffffffffff;

    bsp_err("[init]ipf_probe:\n");
    g_ipf_ap.res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    if (g_ipf_ap.res == NULL) {
        bsp_err("[init]platform_get_resource failed:\n");
        return -ENXIO;
    }

    g_ipf_ap.regs = devm_ioremap_resource(&pdev->dev, g_ipf_ap.res);
    if (IS_ERR(g_ipf_ap.regs)) {
        bsp_err("[init]devm_ioremap_resource failed:\n");
        return PTR_ERR(g_ipf_ap.regs);
    }

    g_ipf_ap.irq = platform_get_irq(pdev, 0);
    if (unlikely(g_ipf_ap.irq == 0)) {
        bsp_err("[init]platform_get_irq failed\n");
        return -ENXIO;
    }

    g_ipf_ap.dev = &pdev->dev;

    spin_lock_init(&g_ipf_ap.bd_lock);
    g_ipf_ap.clk = devm_clk_get(g_ipf_ap.dev, "ipf_clk");
    if (IS_ERR(g_ipf_ap.clk)) {
        bsp_err("[init]ipf clock not available\n");
        return -ENXIO;
    }

    if (clk_prepare_enable(g_ipf_ap.clk)) {
        bsp_err("[init]clk_prepare_enable failed\n");
        return -ENXIO;
    }

    if (of_property_read_u32_array(pdev->dev.of_node, "rst_crg", g_ipf_ap.reset_peri_crg, IPF_RESET_DTS_ARRAY)) {
        bsp_err("rst_crg dts parsed failed\n");
    }
    
    g_ipf_ap.reset_reg = (unsigned char *)ioremap(g_ipf_ap.reset_peri_crg[0], 0x100);
    if (g_ipf_ap.reset_reg == NULL) {
        return -ENXIO;
    }

    if (of_property_read_u32_array(pdev->dev.of_node, "soft_push", &g_ipf_ap.soft_push, 1)) {
        g_ipf_ap.soft_push = 0;
        bsp_err("IPF-MAA ADQ pushed by hardware.\n");
    }
    else {
        if (g_ipf_ap.soft_push) {
            bsp_err("IPF-MAA ADQ pushed by driver.\n");
        }
        else {
            bsp_err("IPF-MAA ADQ pushed by hardware.\n");
        }
    }

    if (ipf_resource_alloc()) {
        ipf_resource_free();
        return -ENOMEM;
    }

    ipf_coop_maa();

#if (defined(CONFIG_BALONG_ESPE))
    if (ipf_coop_spe()) {
        bsp_err("ipf_coop_spe failed!\n");
    }
#else
    if (ipf_dl_init_standalone()) {
        bsp_err("ipf_dl_init_standalone failed!\n");
    }
#endif
#ifdef IPF_UL_DMA
    ipf_recyle_init();
#endif
    if (ipf_dl_wake_init()) {
        bsp_err("ipf_dl_wake_init failed!\n");
    }

    if (request_irq(g_ipf_ap.irq, ipf_interrupt, IRQF_SHARED, "ipf", g_ipf_ap.dev)) {
        bsp_err("[init]dma_alloc_coherent failed, adq0_base invalid\n");
    }

    if (bsp_reset_cb_func_register("IPF_BALONG", ipf_mdmreset_cb, 0, DRV_RESET_CB_PIOR_IPF)) {
        bsp_err("set modem reset call back func failed\n");
    }

    g_ipf_ap.pm = &ipf_dev_pm_ops;

    bsp_err("ipf_probe done\n");
    return 0;
}

static const struct of_device_id ipf_match[] = {
    { .compatible = "hisilicon,eipf_balong_app" },
    {},
};

static struct platform_driver ipf_pltfm_driver = {
    .probe  = ipf_probe,
    .driver = {
        .name   = "ipf",
        .of_match_table = ipf_match,
        .pm = &ipf_dev_pm_ops,
        .probe_type = PROBE_FORCE_SYNCHRONOUS,
    },
};

void ipf_stat_show(void)
{
    bsp_err("bdq_recyle_cnt: %llu\n", g_ipf_ap.bdq_recyle_cnt);
    bsp_err("IPF_NUM_0_1: %d\n", g_ipf_ap.release_num_per_interval[IPF_NUM_1]);
    bsp_err("IPF_NUM_128: %d\n", g_ipf_ap.release_num_per_interval[IPF_NUM_128]);
    bsp_err("IPF_NUM_256: %d\n", g_ipf_ap.release_num_per_interval[IPF_NUM_256]);
    bsp_err("IPF_NUM_512: %d\n", g_ipf_ap.release_num_per_interval[IPF_NUM_512]);
    bsp_err("IPF_NUM_TOOLARGE: %d\n", g_ipf_ap.release_num_per_interval[IPF_NUM_TOOLARGE]);
}

void ipf_dl_cnt(void)
{
    unsigned int reg;
    unsigned int time;

    static unsigned int ipf_last_timestamp = 0;
    static unsigned int ul0_cnt = 0;
    static unsigned int ul1_cnt = 0;
    static unsigned int dl_cnt = 0;

    time = bsp_get_slice_value();

    reg = ipf_read(IPF_CH1_PKT_CNT_REG);
    bsp_err("dl total cnt:%u Mbyte\n", reg);
    bsp_err("dl speed during last sample:%u Mb/s\n", (reg - dl_cnt) * 8 * 32768 / (time - ipf_last_timestamp));
    dl_cnt = reg;

    reg = ipf_read(IPF_CH0_PKT_CNT0_REG);
    bsp_err("ul_lr total cnt:%u Mbyte\n", reg);
    bsp_err("dl speed during last sample:%u Mb/s\n", (reg - ul0_cnt) * 8 * 32768 / (time - ipf_last_timestamp));
    ul0_cnt = reg;

    reg = ipf_read(IPF_CH0_PKT_CNT1_REG);
    bsp_err("ul_nr total cnt:%u Mbyte\n", reg);
    bsp_err("dl speed during last sample:%u Mb/s\n", (reg - ul1_cnt) * 8 * 32768 / (time - ipf_last_timestamp));
    ul1_cnt = reg;

    ipf_last_timestamp = time;
}

int ipf_pltfm_driver_init(void)
{
    return platform_driver_register(&ipf_pltfm_driver);
}
#ifndef CONFIG_HISI_BALONG_MODEM_MODULE
module_init(ipf_pltfm_driver_init);
#endif
