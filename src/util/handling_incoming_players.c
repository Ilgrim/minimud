int32_t find_and_set_new_player_struct (const int32_t wfd) {
    int32_t set = 0;
    for (size_t j = 0;; ++j) {
        if (player[j].in_use != 0) {
            continue;
        }
        player[j].in_use = 1;
        player[j].hold_for_input = 1;
        player[j].socket_num = wfd;
        player[j].wait_state = THEIR_NAME;
        FD_SET(wfd, &rfds);
        if (wfd > fdmax) {
            fdmax = wfd;
        }
        set = 1;
        set_active_connections();

        /* this doesn't actually do anything productive right now
         * returns a local address. maybe because telnet to localhost
         * or maybe because doing it wrong. to come back to later. 
         * might be useful if working in future to pass a single IP
         * to bind instead of 0.0.0.0 */
        struct sockaddr_in addr;
        //socklen_t addr_size = sizeof(struct sockaddr_in); 
        struct ifaddrs *ifap;
        //status = getifaddrs(&ifap);
        //status = getpeername(wfd, player[i].address, &player[i].address_len);
        strncpy(player[j].holder, inet_ntoa(addr.sin_addr), NAMES_MAX);
        break;
    }
    return set;
}

int32_t ensure_player_moving_valid_dir (const int32_t socket_num, const uint8_t *command) {
    if (is_direction(command) == EXIT_FAILURE) {
        print_output(socket_num, INVALDIR);\
        print_output(socket_num, PRINT_EXITING_CMD_WAIT);\
        player[pnum].wait_state = NO_WAIT_STATE;\
        player[pnum].hold_for_input = 0;\
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
