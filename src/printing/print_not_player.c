#include "print_not_player.h"

int32_t print_not_player(const int32_t socket, const uint8_t *buffer, const int32_t location)
{
	struct Coordinates coords = get_player_coords(socket);

	for (size_t i = 0; i < get_num_of_players(); ++i) {
		struct Coordinates this_player = get_player_coords(i);

		if (location == ROOM_ONLY) {
			if (this_player.x == coords.x && 
				this_player.y == coords.y && 
				this_player.z == coords.z) {
				set_player_buffer_replace(i, buffer);
				assert(outgoing_handler(i) == EXIT_SUCCESS);
			}
		} else if (location == ALL_PLAYERS) {
			set_player_buffer_replace(i, buffer);
			assert(outgoing_handler(i) == EXIT_SUCCESS);
		}
	}

	return EXIT_SUCCESS;
}

int32_t print_player_speech_to_others(const int32_t socket, const uint8_t *say)
{
	#define TOKEN_SAY_CMD_LEN 4 // length req'd for the actual say command + the space after that
	#define TOKEN_YOU_SAY_LEN 9 // length req'd for player to see You say: 
	uint8_t *buffer = calloc(BUFFER_LENGTH, sizeof(uint8_t));
	void *loc_in_buf = NULL; 

	loc_in_buf = mempcpy(buffer, get_player_name(socket), strlen((char *)get_player_name(socket)));
	loc_in_buf = mempcpy(loc_in_buf, " says: ", BUFFER_LENGTH - strlen((char *)buffer));
	loc_in_buf = mempcpy(loc_in_buf, &say[TOKEN_SAY_CMD_LEN], BUFFER_LENGTH - strlen((char *)buffer));

	print_not_player(socket, buffer, ROOM_ONLY);
	#ifdef DEBUG
	printf("print_player_speech: %s\n", buffer);
	#endif

	free(buffer);

	set_player_buffer_replace(socket, (uint8_t*)"You say: ");
	set_player_buffer_append(socket, &say[TOKEN_SAY_CMD_LEN]);

	assert(outgoing_handler(socket) == EXIT_SUCCESS);

	return EXIT_SUCCESS;
}
