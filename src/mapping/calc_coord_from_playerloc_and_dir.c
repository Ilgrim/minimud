int32_t calc_coord_from_playerloc_and_dir (const int32_t coord_type, const int32_t pnum) {
    int32_t x, y, z;
    x = get_player_coord(X_COORD_REQUEST, pnum);
    y = get_player_coord(Y_COORD_REQUEST, pnum);
    z = get_player_coord(Z_COORD_REQUEST, pnum);
    if (player[pnum].store == NULL || player[pnum].store_size == 0) {
        return -1;
    }
    int32_t len = player[pnum].store_size;
    if (len == 1) {
        return EXIT_FAILURE;
    }
    uint8_t tmp[len] = {0};
    strncpy(tmp, player[pnum].store, len);
    for (size_t i = 0; i < strlen(tmp); ++i) {
        if (isalpha(tmp[len]) == 0) {
            tmp[len] = '\0';
        }
    }
    if (coord_type == X_COORD_REQUEST) {
        return (x += x_movement_to_vector(tmp));
    } else if (coord_type == Y_COORD_REQUEST) {
        return (y += y_movement_to_vector(tmp));
    } else if (coord_type == Z_COORD_REQUEST) {
        return (z += z_movement_to_vector(tmp));
    }
    return EXIT_FAILURE;
}
