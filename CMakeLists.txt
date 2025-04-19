if ((NOT CONFIG_ZMK_SPLIT) OR CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
    target_sources_ifdef(CONFIG_BOARD_STATUS_UNDERGLOW app PRIVATE src/board_status_underglow.c)
endif()