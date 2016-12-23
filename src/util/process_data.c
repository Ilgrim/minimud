int32_t process_data (const int32_t socket_num) {
    uint8_t *extra;
    int32_t retval;
    int32_t pnum = getplayernum(socket_num);
    int32_t incoming_data_len = 0;
    ioctl (socket_num, FIONREAD, &incoming_data_len);
    if (incoming_data_len > BUFFER_LENGTH) {
        extra = malloc(incoming_data_len - BUFFER_LENGTH); 
    }
    if (player[pnum].in_use != 1) {
        extra = realloc(extra, incoming_data_len);
        retval = recv(socket_num, extra, incoming_data_len, 0);
        memset(extra, '\0', incoming_data_len);
        free(extra);
        extra = NULL;
        return EXIT_SUCCESS;
    }
    retval = recv(socket_num, player[pnum].buffer, sizeof(player[pnum].buffer), 0);
    if (retval == 0) {
        shutdown_socket(pnum); 
        return EXIT_SUCCESS;
    } else if (retval == -1) {
        log_issue((uint8_t*)"Problem receiving data.");
        return EXIT_FAILURE;
    } else if (retval > 0) { // receive waiting data, process
        retval = recv(socket_num, extra, incoming_data_len - BUFFER_LENGTH, 0);
        memset(extra, '\0', incoming_data_len - BUFFER_LENGTH);
        free(extra);
        extra = NULL;
    }
    interpret_command(socket_num);
    return EXIT_SUCCESS;
}
