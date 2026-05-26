// 134. Gas Station
// Base case / ³Ì¤p¿é¤J¡GO(1)
// Best case¡GO(n)
// Worst case¡GO(n)
// Space¡GO(1)

int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    int total_surplus = 0; // Tracks if a solution exists at all
    int current_tank = 0;  // Tracks gas in the tank for the current starting point
    int start_index = 0;   // The potential starting station

    for (int i = 0; i < gasSize; i++) {
        int diff = gas[i] - cost[i];
        total_surplus += diff;
        current_tank += diff;

        // If current_tank drops below 0, the current start_index is invalid
        if (current_tank < 0) {
            // Pick the next station as the new potential start
            start_index = i + 1;
            // Reset the tank for the new start
            current_tank = 0;
        }
    }

    // If total_surplus is negative, the trip is impossible
    if (total_surplus < 0) {
        return -1;
    }

    return start_index;
}
