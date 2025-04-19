/*
 * Copyright (c) 2025 thiemok
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_board_status_underglow

#include <zephyr/device.h>
#include <zephyr/logging/log.h>
#include <zmk/event_manager.h>
#include <zmk/events/layer_state_changed.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

static int board_status_layer_change_listener_cb(const zmk_event_t *eh) {
    ARG_UNUSED(eh);
    LOG_INF("Layer change event");
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(board_status_listener, board_status_layer_change_listener_cb);
ZMK_SUBSCRIPTION(board_status_listener, zmk_layer_state_changed);

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */