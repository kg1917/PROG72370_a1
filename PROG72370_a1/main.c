#include "queue.h"
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <stdio.h>

// Macro to simplify random number generation
#define RNG(x, y) (rand() % (y - x + 1) + x)

// Acts as a look up between the FACTION enum value and the name of the faction
const char FACTION_NAMES[3][6] = {
	"Red",
	"Blue",
	"Green"
};

char addusers(QUEUE_T *queue, size_t n) {
	for (size_t i = 0; i < n; i++) {
		char name[MAX_USERNAME] = { '\0' };
		for (int r = 0; r < MAX_USERNAME - 1; r++) {
			name[r] = (char)RNG(65, 90);
		}
		if (enqueue(queue, name, RNG(1, 60), (enum faction) RNG(0, 2)))
			return 1;
	}

	return 0;
}

int main(int argc, char *argv[]) {
	// N is eight by default
	size_t n = 8;
	if (argc > 1) {
		n = atoi(argv[1]);
	}

	// Set seed
	srand(time(NULL));

	QUEUE_T *queue = initQueue();

	if (addusers(queue, n) != 0) {
		fprintf(stderr, "An error has occured\n");
		return 1;
	}

	while (!queue_empty(queue)) {
		struct user user = dequeue(queue);
		printf("User \"%s\": Level %i, %s\n", user.username, user.level, FACTION_NAMES[user.faction]);
	}

	destroyQueue(queue);
}