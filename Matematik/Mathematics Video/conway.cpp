#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <random>
#include <chrono>

using namespace std;

#define grid_size 19

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
	int counting = 0;

	for(int i = 0; i < map.size(); i++) {
		for(int j = 0; j < map.size(); j++) {
			if(map[i][j] == 1) {
				counting++;
				cout << "\033[32m" << map[i][j] << " ";
			} else {
				cout << "\033[39m" << map[i][j] << " ";
			}
		}
		cout << "\033[37m" << endl;
	}
	if(counting == 0) {
		return 1;
	}
	return 0;
}

int countalive(const vector<vector<int>>& map, int point[2]) {
    int alive_count = 0;
    int x = point[0];
    int y = point[1];
    
    for (int k = -1; k <= 1; k++) {
        for (int l = -1; l <= 1; l++) {
            if (k == 0 && l == 0) {
                continue;
            }

            int nx = x + k;
            int ny = y + l;

            if (nx >= 0 && nx < map.size() && ny >= 0 && ny < map[0].size()) {
                alive_count += map[nx][ny];
            }
        }
    }
    
    return (alive_count > 2 && alive_count < 4) ? 1 : 0;
}


vector<vector<int>> newmap(vector<vector<int>> map) {
	vector<vector<int>> new_map(map.size(), vector<int>(map.size()));

	for(int i = 0; i < map.size(); i++) {
		for(int j = 0; j < map.size(); j++) {
			int point[2] = {i, j};
			new_map[i][j] = countalive(map, point);
		}
	}

	return new_map;
}

int main() {
	vector<vector<int>> map = initialize(grid_size);

	printmap(map);

	cout << endl << "Starting grid initialized..." << endl;

	sleep(2);
	
	for(int i = 1; i != 0; i++) {
		map = newmap(map);
		sleep(1);
		if(printmap(map) == 1) {
			cout << endl << "Time: " << i << endl;
			exit(0);
		}
		cout << endl << "Time: " << i << endl;
	}
	return 0;
}