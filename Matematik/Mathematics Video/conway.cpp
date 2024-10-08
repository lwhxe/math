#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <random>
#include <chrono>

using namespace std;

#define grid_size 10000

int generate_random_number() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);
    return dist(gen);
}

vector<vector<int>> initialize(int size) {
	vector<vector<int>> map(size, vector<int>(size));

	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			map[i][j] = generate_random_number();
		}
	}

	return map;
}

int printmap(vector<vector<int>> map) {
	cout << "\033[H\033[J";

	for(int i = 0; i < map.size(); i++) {
		for(int j = 0; j < map.size(); j++) {
			if(map[i][j] == 1) {
				cout << "\033[32m" << map[i][j] << " ";
			} else {
				cout << "\033[39m" << map[i][j] << " ";
			}
		}
		cout << "\033[37m" << endl;
	}
	return 0;
}

int countalive(const vector<vector<int>>& map, int point[2]) {
    int alive_count = 0;
    int x = point[0];
    int y = point[1];
    int point_value;

    for (int k = -1; k <= 1; k++) {
        for (int l = -1; l <= 1; l++) {
            if (k == 0 && l == 0) {
                point_value = map[x][y];
                continue;
            }

            int nx = x + k;
            int ny = y + l;

            if (nx >= 0 && nx < map.size() && ny >= 0 && ny < map[0].size()) {
                alive_count += map[nx][ny];
            }
        }
    }

    return point_value ? ((alive_count > 1 && alive_count < 4) ? 1 : 0) : ((alive_count == 3) ? 1 : 0);
}


vector<vector<int>> newmap(vector<vector<int>> map, int time) {
	vector<vector<int>> new_map(map.size(), vector<int>(map.size()));
    int alive_points = 0;

	for(int i = 0; i < map.size(); i++) {
		for(int j = 0; j < map.size(); j++) {
			int point[2] = {i, j};
			new_map[i][j] = countalive(map, point);
            alive_points += new_map[i][j];
		}
	}

    if(alive_points == 0 || map == new_map) {
        printmap(new_map);
		cout << endl << "Time: " << time << endl;
		exit(0);
	}

	return new_map;
}

int main() {
	vector<vector<int>> map = initialize(grid_size);

	printmap(map);

	cout << endl << "Starting grid initialized..." << endl;
    
	// sleep(2);
	
	for(int i = 1; i <= 100; i++) {
		map = newmap(map, i);
		// sleep(1);
	}
	return 0;
}
