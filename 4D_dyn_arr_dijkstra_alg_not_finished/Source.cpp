#include <iostream>
using namespace std;
#include <limits>
#include <format>

int**** fourD_graph(const int& size);
void populate_arr(int**** arr, const int& size_arr);
void print(int**** arr, const int& size_arr);
void Dijkstra(int**** graph, const int& start, const int& size_graph);
int minimum_dist(int distance[], bool is_checked[], const int& size);
void print_distance(int* dist, const int& size);

int main() {
	int w{};
	cin >> w;

	Dijkstra(fourD_graph(w), 0, w);
	return 0;
}

int**** fourD_graph(const int& size)
{
	int**** graph = new int*** [size];

	for (int i{}; i < size; i++) {
		graph[i] = new int** [size];
		for (int j{}; j < size; j++) {
			graph[i][j] = new int* [size];

			for (int b{}; b < size; b++) {
				graph[i][j][b] = new int[size];
			}
		}
	}

	populate_arr(graph, size);
	print(graph, size);

	return graph;
}

void populate_arr(int**** arr, const int& size_arr)
{
	int value{};
	for (int i{}; i < size_arr; i++) {
		for (int j{}; j < size_arr; j++) {
			for (int c{}; c < size_arr; c++) {
				for (int v{}; v < size_arr; v++) {
					cout << "put value: "; cin >> value;
					arr[i][j][c][v] = value;
				}
			}
		}
		cout << endl;
	}
}

void print(int**** arr, const int& size_arr)
{
	for (int i{}; i < size_arr; i++) {
		for (int j{}; j < size_arr; j++) {
			for (int c{}; c < size_arr; c++) {
				for (int v{}; v < size_arr; v++) {
					cout << arr[i][j][c][v] << " ";
				}
				cout << endl;
			}
		}
		cout << endl;
	}
}

void Dijkstra(int**** graph, const int& start, const int& size_graph)
{
	int* distance = new int[size_graph]; //distance for each vertex
	bool* is_checked = new bool[size_graph]; //is the vertex checked?

	for (int i{}; i < size_graph; i++) {
		distance[i] = INT_MAX;
		is_checked[i] = false;
	}

	distance[start] = 0; //the distance of the start is always 0

	for (int i{}; i < size_graph; i++) {
		int the_min_dist = minimum_dist(distance, is_checked, size_graph);
		is_checked[i] = true;

		for (int j{}; j < size_graph; j++) {
			for (int c{}; c < size_graph; c++) {
				for (int b{}; b < size_graph; b++) {
					if (!is_checked[j] && graph[the_min_dist][j][c][b] && distance[the_min_dist] != INT_MAX && distance[the_min_dist] + graph[the_min_dist][j][c][b] < distance[j]) {
						distance[b] = distance[the_min_dist] + graph[the_min_dist][j][c][b];
					}
				}
			}
		}
	}
	print_distance(distance, size_graph);
}

int minimum_dist(int distance[], bool is_checked[], const int& size)
{
	int minimum = INT_MAX;
	int at_pos{};

	for (int i{}; i < size; i++) {
		if (is_checked[i] != true && distance[i] < minimum) {
			minimum = distance[i];
			at_pos = i;
		}
	}
	return at_pos;
}

void print_distance(int* dist, const int& size)
{
	cout << format("{:8}| {:8}", "Vertex", "Distance") << endl;
	cout << "______________________" << endl;
	for (int i{}; i < size; i++)
		cout << format("{:8}| {:8}", static_cast<char>('A' + i), dist[i]) << endl;
}