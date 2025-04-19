/*
 * Copyright (c) 2025 thiemok
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_board_status_underglow

#include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <zmk/event_manager.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/keymap.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

static K_SEM_DEFINE(board_status_layer_sem, 1, 1);

struct board_status_underglow_cfg {
    zmk_keymap_layers_state_t active_layers_mask;
};

#define IF_LAYER_BIT(node_id, prop, idx) BIT(DT_PROP_BY_IDX(node_id, prop, idx)) |

static const struct board_status_underglow_cfg BOARD_STATUS_UNDERGLOW_CFG = {
    .active_layers_mask = DT_INST_FOREACH_PROP_ELEM(0, active_layers, IF_LAYER_BIT) 0,
};

static int board_status_layer_change_listener_cb(const zmk_event_t *eh) {
    LOG_INF("Layer change event");
    if (k_sem_take(&board_status_layer_sem, K_NO_WAIT) < 0) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    zmk_keymap_layers_state_t mask = BOARD_STATUS_UNDERGLOW_CFG.active_layers_mask;
    if ((zmk_keymap_layer_state() & mask) == mask) {
        LOG_INF("On active layer");
    }

    k_sem_give(&board_status_layer_sem);
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(board_status_listener, board_status_layer_change_listener_cb);
ZMK_SUBSCRIPTION(board_status_listener, zmk_layer_state_changed);

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */