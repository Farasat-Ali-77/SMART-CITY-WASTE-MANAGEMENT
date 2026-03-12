#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <fstream>
using namespace std;

struct AreaNode {
	string areaName;
	int population;
	double wasteGrowthRate;
	double garbagePerDay;
	AreaNode* left;
	AreaNode* right;
	int height;
};

int height(AreaNode* node) {
	return node ? node->height : 0;
}

int getBalanceFactor(AreaNode* node) {
	return node ? height(node->left) - height(node->right) : 0;
}

AreaNode* createNode(string name, int population, double wasteGrowthRate) {
	AreaNode* node = new AreaNode();
	node->areaName = name;
	node->population = population;
	node->wasteGrowthRate = wasteGrowthRate;
	node->garbagePerDay = population * wasteGrowthRate;
	node->left = node->right = nullptr;
	node->height = 1;
	return node;
}

AreaNode* rightRotate(AreaNode* y) {
	AreaNode* x = y->left;
	AreaNode* T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}

AreaNode* leftRotate(AreaNode* x) {
	AreaNode* y = x->right;
	AreaNode* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}
AreaNode* insertArea(AreaNode* node, string name, int population, double wasteGrowthRate) {
	if (!node)
		return createNode(name, population, wasteGrowthRate);

	if (name < node->areaName)
		node->left = insertArea(node->left, name, population, wasteGrowthRate);
	else if (name > node->areaName)
		node->right = insertArea(node->right, name, population, wasteGrowthRate);
	else
		return node;

	node->height = 1 + max(height(node->left), height(node->right));

	int balance = getBalanceFactor(node);

	if (balance > 1 && name < node->left->areaName)
		return rightRotate(node);

	if (balance < -1 && name > node->right->areaName)
		return leftRotate(node);

	if (balance > 1 && name > node->left->areaName) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && name < node->right->areaName) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

AreaNode* root = nullptr;

void displayAreas(AreaNode* root, double& totalGarbage) {
	if (!root)
		return;

	displayAreas(root->left, totalGarbage);
	cout << left << setw(20) << root->areaName
		<< setw(15) << root->population
		<< setw(20) << fixed << setprecision(2) << root->wasteGrowthRate
		<< setw(20) << root->garbagePerDay << " kg" << endl;
	totalGarbage += root->garbagePerDay;
	displayAreas(root->right, totalGarbage);
}

void mainMenu();
double totalGarbage = 0;
void Areamenu() {

	int choice;

	do {
		cout << "\n\t\t  Area Mangement Potal";
		cout << "\n\t\t========================\n\n";
		cout << "1. Add Area" << endl;
		cout << "2. Display Areas" << endl;
		cout << "3. Display Total City Waste" << endl;
		cout << "4. Main menu" << endl;
		cout << "5. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
		{
			string name;
			int population;
			double wasteGrowthRate;
			cout << "Enter area name: ";
			cin >> name;
			cout << "Enter population: ";
			cin >> population;
			cout << "Enter waste growth rate (kg per person per day): ";
			cin >> wasteGrowthRate;
			root = insertArea(root, name, population, wasteGrowthRate);
			cout << "Area added successfully!\n";
			break;
		}
		case 2:
		{
			totalGarbage = 0;
			cout << "\n\n";
			cout << left << setw(20) << "Area Name"
				<< setw(15) << "Population"
				<< setw(20) << "Waste Growth Rate"
				<< "Garbage per Day" << endl;
			cout << string(75, '-') << endl;
			displayAreas(root, totalGarbage);
			break;
		}
		case 3:
		{
			totalGarbage = 0;
			cout << "\n\n";
			cout << left << setw(20) << "Area Name"
				<< setw(15) << "Population"
				<< setw(20) << "Waste Growth Rate"
				<< "Garbage per Day" << endl;
			cout << string(75, '-') << endl;
			displayAreas(root, totalGarbage);
			cout << "\nTotal City Garbage per Day: " << fixed << setprecision(2) << totalGarbage << " kg  (Tons: " << totalGarbage / 1000 << " )\n\n";
			break;
		}
		case 4:
		{
			cout << "Returning to main menu...\n";
			mainMenu();
			break;
		}
		case 5:
			cout << "Exiting...\n";
			exit(0);
			break;
		default:
			cout << "Invalid choice. Please try again.\n";
		}

	} while (choice != 4);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRUCK MODULE

struct TruckNode {
	string truckID;
	int capacity;
	TruckNode* left;
	TruckNode* right;
	int height;
};

int truckHeight(TruckNode* node) {
	return node ? node->height : 0;
}

int getTruckBalanceFactor(TruckNode* node) {
	return node ? truckHeight(node->left) - truckHeight(node->right) : 0;
}

TruckNode* createTruckNode(string id, int capacity) {
	TruckNode* node = new TruckNode();
	node->truckID = id;
	node->capacity = capacity;
	node->left = node->right = nullptr;
	node->height = 1;
	return node;
}

TruckNode* rightRotateTruck(TruckNode* y) {
	TruckNode* x = y->left;
	TruckNode* T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(truckHeight(y->left), truckHeight(y->right)) + 1;
	x->height = max(truckHeight(x->left), truckHeight(x->right)) + 1;

	return x;
}

TruckNode* leftRotateTruck(TruckNode* x) {
	TruckNode* y = x->right;
	TruckNode* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(truckHeight(x->left), truckHeight(x->right)) + 1;
	y->height = max(truckHeight(y->left), truckHeight(y->right)) + 1;

	return y;
}

TruckNode* insertTruck(TruckNode* node, string id, int capacity) {
	if (!node) {
		cout << "\n--- Inserting truck: " << id << " with capacity " << capacity << " kg. ---\n";
		return createTruckNode(id, capacity);
	}

	if (id < node->truckID)
		node->left = insertTruck(node->left, id, capacity);
	else if (id > node->truckID)
		node->right = insertTruck(node->right, id, capacity);
	else {
		cout << "Duplicate truck ID not allowed: " << id << endl;
		return node;
	}

	node->height = 1 + max(truckHeight(node->left), truckHeight(node->right));

	int balance = getTruckBalanceFactor(node);

	if (balance > 1 && id < node->left->truckID)
		return rightRotateTruck(node);

	if (balance < -1 && id > node->right->truckID)
		return leftRotateTruck(node);

	if (balance > 1 && id > node->left->truckID) {
		node->left = leftRotateTruck(node->left);
		return rightRotateTruck(node);
	}

	if (balance < -1 && id < node->right->truckID) {
		node->right = rightRotateTruck(node->right);
		return leftRotateTruck(node);
	}

	return node;
}

TruckNode* truckRoot = nullptr;

void displayTrucks(TruckNode* root) {
	if (!root)
		return;

	displayTrucks(root->left);
	cout << left << setw(15) << root->truckID
		<< setw(10) << root->capacity << " kg" << endl;
	displayTrucks(root->right);
}
void truckMenu() {
	int truckChoice;
	do {
		cout << "\n\t\t  Trucks Management System";
		cout << "\n\t\t============================\n\n";
		cout << "1. Add Truck" << endl;
		cout << "2. Display Trucks" << endl;
		cout << "3. Exit to Main Menu" << endl;
		cout << "Enter your choice: ";
		cin >> truckChoice;

		switch (truckChoice) {
		case 1:
		{
			string id;
			int capacity;
			cout << "Enter truck ID: ";
			cin >> id;
			cout << "Enter truck capacity (in kg): ";
			cin >> capacity;
			truckRoot = insertTruck(truckRoot, id, capacity);
			cout << "Truck added successfully!\n";
			break;
		}
		case 2:
		{
			cout << left << setw(15) << "Truck ID"
				<< "Capacity" << endl;
			cout << string(25, '-') << endl;
			displayTrucks(truckRoot);
			break;
		}
		case 3:
			cout << "Returning to main menu...\n";
			mainMenu();
			break;
		default:
			cout << "Invalid choice. Please try again.\n";
		}

	} while (truckChoice != 3);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// graph module

const int MAX_AREAS = 100;
const int INF = numeric_limits<int>::max();

struct Edge {
	int destination;
	int distance;
	Edge* next;
};

struct Area {
	string name;
	int garbage;
	Edge* head;
};

struct Graph {
	Area areas[MAX_AREAS];
	int areaCount;
};

void initializeGraph(Graph& graph) {
	graph.areaCount = 0;
	for (int i = 0; i < MAX_AREAS; ++i) {
		graph.areas[i].name = "";
		graph.areas[i].garbage = 0;
		graph.areas[i].head = nullptr;
	}

	graph.areas[graph.areaCount].name = "Dumping Station";
	graph.areas[graph.areaCount].garbage = 0;
	graph.areas[graph.areaCount].head = nullptr;
	graph.areaCount++;
}

int addArea(Graph& graph, string areaName, int garbage) {
	if (graph.areaCount >= MAX_AREAS) {
		cout << "Cannot add more areas. Maximum limit reached.\n";
		return -1;
	}
	graph.areas[graph.areaCount].name = areaName;
	graph.areas[graph.areaCount].garbage = garbage;
	graph.areas[graph.areaCount].head = nullptr;
	return graph.areaCount++;
}

int findAreaIndex(Graph& graph, string areaName) {
	for (int i = 0; i < graph.areaCount; ++i) {
		if (graph.areas[i].name == areaName)
			return i;
	}
	return -1;
}
void addConnection(Graph& graph, string sourceName, string destName, int distance) {
	int srcIndex = findAreaIndex(graph, sourceName);
	int destIndex = findAreaIndex(graph, destName);

	if (srcIndex == -1 || destIndex == -1) {
		cout << "Error: One or both areas not found.\n";
		return;
	}

	Edge* newEdge = new Edge{ destIndex, distance, graph.areas[srcIndex].head };
	graph.areas[srcIndex].head = newEdge;

	newEdge = new Edge{ srcIndex, distance, graph.areas[destIndex].head };
	graph.areas[destIndex].head = newEdge;

	cout << "Connection added between " << sourceName << " and " << destName << " with distance " << distance << " km.\n";
}

void displayGraph(Graph& graph) {
	cout << "\nAreas and their connections:\n";
	for (int i = 0; i < graph.areaCount; ++i) {
		cout << graph.areas[i].name << " (Garbage: " << graph.areas[i].garbage << " kg) -> ";
		Edge* current = graph.areas[i].head;
		while (current) {
			cout << graph.areas[current->destination].name << "(" << current->distance << " km) ";
			current = current->next;
		}
		cout << endl;
	}
}

vector<int> dijkstra(Graph& graph, int start, int target) {
	vector<int> dist(graph.areaCount, INF);
	vector<int> parent(graph.areaCount, -1);
	vector<bool> visited(graph.areaCount, false);

	dist[start] = 0;

	for (int i = 0; i < graph.areaCount - 1; ++i) {
		int u = -1;

		for (int j = 0; j < graph.areaCount; ++j) {
			if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
				u = j;
			}
		}

		if (dist[u] == INF)
			break;

		visited[u] = true;

		for (Edge* edge = graph.areas[u].head; edge != nullptr; edge = edge->next) {
			int v = edge->destination;
			int weight = edge->distance;

			if (dist[u] + weight < dist[v]) {
				dist[v] = dist[u] + weight;
				parent[v] = u;
			}
		}
	}

	vector<int> path;
	for (int at = target; at != -1; at = parent[at]) {
		path.push_back(at);
	}
	reverse(path.begin(), path.end());

	if (path.size() == 1 && path[0] != target) {
		return {};
	}

	return path;
}

string getTruckID(TruckNode* root, int index, int& count) {
	if (!root)
		return "";

	string left = getTruckID(root->left, index, count);
	if (!left.empty())
		return left;

	if (count == index)
		return root->truckID;
	count++;

	return getTruckID(root->right, index, count);
}

int getTruckCapacity(TruckNode* root, int index, int& count) {
	if (!root)
		return 0;

	int left = getTruckCapacity(root->left, index, count);
	if (left != 0)
		return left;

	if (count == index)
		return root->capacity;
	count++;

	return getTruckCapacity(root->right, index, count);
}
string getTruckID(TruckNode* root, int index) {
	int count = 0;
	return getTruckID(root, index, count);
}

int getTruckCapacity(TruckNode* root, int index) {
	int count = 0;
	return getTruckCapacity(root, index, count);
}

int getTruckCount(TruckNode* root) {
	if (!root)
		return 0;
	return 1 + getTruckCount(root->left) + getTruckCount(root->right);
}
void displayTargetedAreas(Graph& graph) {
	cout << "\nTargeted Areas for Collecting Trash:\n";
	cout << left << setw(20) << "Area Name" << setw(20) << "Garbage (kg)" << endl;
	cout << string(40, '-') << endl;
	for (int i = 1; i < graph.areaCount; ++i) {
		if (graph.areas[i].garbage > 0) {
			cout << left << setw(20) << graph.areas[i].name << setw(20) << graph.areas[i].garbage << endl;
		}
	}
}

void addAreasFromAVL(Graph& graph, AreaNode* root) {
	if (!root)
		return;

	addAreasFromAVL(graph, root->left);
	if (findAreaIndex(graph, root->areaName) == -1) {
		addArea(graph, root->areaName, root->garbagePerDay);
	}
	addAreasFromAVL(graph, root->right);
}

int totalDistanceAllTrucks = 0;
int totalTrips = 0;

void planTruckTrips(Graph& graph) {
	addAreasFromAVL(graph, root);

	vector<int> originalGarbage(graph.areaCount);
	for (int i = 0; i < graph.areaCount; ++i) {
		originalGarbage[i] = graph.areas[i].garbage;
	}

	cout << "\nPlanning truck trips:\n";
	ofstream analyticsFile("analytics.txt", ios::out | ios::trunc);
	if (!analyticsFile) {
		cerr << "Error opening analytics file.\n";
		return;
	}

	int totalAreas = graph.areaCount - 1;
	int truckCount = getTruckCount(truckRoot);
	totalTrips = 0;
	vector<int> truckTrips(truckCount, 0);
	vector<int> truckDistances(truckCount, 0);
	totalDistanceAllTrucks = 0;

	bool garbageLeft = true;

	analyticsFile << "Areas Information:\n";
	analyticsFile << left << setw(20) << "Area Name" << setw(15) << "Population" << setw(20) << "Waste Growth Rate" << "Garbage per Day (kg)\n";
	analyticsFile << string(75, '-') << endl;
	for (int i = 1; i < graph.areaCount; ++i) {
		analyticsFile << left << setw(20) << graph.areas[i].name
			<< setw(15) << graph.areas[i].garbage / root->wasteGrowthRate
			<< setw(20) << root->wasteGrowthRate
			<< setw(20) << graph.areas[i].garbage << " kg\n";
	}
	analyticsFile << endl;

	analyticsFile << "Available Trucks:\n";
	analyticsFile << left << setw(15) << "Truck ID" << "Capacity (kg)\n";
	analyticsFile << string(25, '-') << endl;
	for (int truckIndex = 0; truckIndex < truckCount; ++truckIndex) {
		string truckID = getTruckID(truckRoot, truckIndex);
		int truckCapacity = getTruckCapacity(truckRoot, truckIndex);
		analyticsFile << left << setw(15) << truckID << truckCapacity << " kg" << endl;
	}
	analyticsFile << endl;

	analyticsFile << "Truck Trips:\n";
	analyticsFile << string(75, '-') << endl;

	while (garbageLeft) {
		garbageLeft = false;
		bool allGarbageCollected = true;
		int totalGarbageCollected = 0;

		displayTargetedAreas(graph);
		cout << "\n\n";
		cout << "\tAvailable Trucks" << endl;
		cout << "-----------------------------------\n\n";
		displayTrucks(truckRoot);

		for (int truckIndex = 0; truckIndex < truckCount; ++truckIndex) {
			string truckID = getTruckID(truckRoot, truckIndex);
			int truckCapacity = getTruckCapacity(truckRoot, truckIndex);
			int remainingCapacity = truckCapacity;

			vector<pair<string, int>> route;
			route.push_back({ "Dumping Station", 0 });

			int currentAreaIndex = 0;
			int totalDistance = 0;

			while (remainingCapacity > 0) {
				int nextAreaIndex = -1;
				int minDistance = INF;
				int maxGarbage = 0;

				for (int areaIndex = 1; areaIndex < graph.areaCount; ++areaIndex) {
					if (graph.areas[areaIndex].garbage > 0) {
						vector<int> path = dijkstra(graph, currentAreaIndex, areaIndex);
						int distance = path.size() - 1;
						if (distance < minDistance || (distance == minDistance && graph.areas[areaIndex].garbage > maxGarbage)) {
							minDistance = distance;
							nextAreaIndex = areaIndex;
							maxGarbage = graph.areas[areaIndex].garbage;
						}
					}
				}

				if (nextAreaIndex == -1) {
					break;
				}

				int garbage = graph.areas[nextAreaIndex].garbage;
				int load = min(garbage, remainingCapacity);
				remainingCapacity -= load;
				graph.areas[nextAreaIndex].garbage -= load;
				totalGarbageCollected += load;

				vector<int> pathToNextArea = dijkstra(graph, currentAreaIndex, nextAreaIndex);
				for (int areaIndex : pathToNextArea) {
					if (areaIndex != currentAreaIndex) {
						route.push_back({ graph.areas[areaIndex].name, 0 });
						totalDistance += graph.areas[currentAreaIndex].head->distance;
						currentAreaIndex = areaIndex;
					}
				}

				route.back().second = load;

				if (graph.areas[nextAreaIndex].garbage > 0) {
					garbageLeft = true;
				}
			}

			vector<int> pathToDumpingStation = dijkstra(graph, currentAreaIndex, 0);
			for (int areaIndex : pathToDumpingStation) {
				if (areaIndex != currentAreaIndex) {
					route.push_back({ graph.areas[areaIndex].name, 0 });
					totalDistance += graph.areas[currentAreaIndex].head->distance;
					currentAreaIndex = areaIndex;
				}
			}

			if (route.size() > 1 && route.back().first == "Dumping Station") {
				route.pop_back();
			}

			if (route.size() > 1) {
				truckTrips[truckIndex]++;
				totalTrips++;
				truckDistances[truckIndex] += totalDistance;
				totalDistanceAllTrucks += totalDistance;
				cout << "\nTruck ID: " << truckID << "\nRoute: \n";
				analyticsFile << "\nTruck ID: " << truckID << "\nRoute: \n";
				for (const auto& [area, collected] : route) {
					cout << area << " (" << collected << " kg) -> ";
					analyticsFile << area << " (" << collected << " kg) -> ";
				}
				cout << "Dumping Station (0 kg)\n\n";
				analyticsFile << "Dumping Station (0 kg)\n\n";
				cout << "Total Distance Traveled: " << totalDistance << " km\n";
				analyticsFile << "Total Distance Traveled: " << totalDistance << " km\n";
				cout << "Truck Capacity: " << truckCapacity << " kg, Returning with: " << remainingCapacity << " kg Capacity Left\n\n";
				analyticsFile << "Truck Capacity: " << truckCapacity << " kg, Returning with: " << remainingCapacity << " kg Capacity Left\n\n";
			}
		}
		for (int areaIndex = 1; areaIndex < graph.areaCount; ++areaIndex) {
			if (graph.areas[areaIndex].garbage > 0) {
				allGarbageCollected = false;
				break;
			}
		}

		if (allGarbageCollected || totalGarbageCollected == 0) {
			break;
		}
	}

	cout << "All areas serviced and garbage delivered to the dumping station.\n\n";
	analyticsFile << "All areas serviced and garbage delivered to the dumping station.\n\n";

	for (int truckIndex = 0; truckIndex < truckCount; ++truckIndex) {
		string truckID = getTruckID(truckRoot, truckIndex);
		cout << "Truck ID: " << truckID << " made " << truckTrips[truckIndex] << " trips and traveled " << truckDistances[truckIndex] << " km.\n";
		analyticsFile << "Truck ID: " << truckID << " made " << truckTrips[truckIndex] << " trips and traveled " << truckDistances[truckIndex] << " km.\n";
	}

	cout << "\nTotal number of trips by all trucks: " << totalTrips << "\n";
	cout << "Total distance traveled by all trucks: " << totalDistanceAllTrucks << " km\n";
	analyticsFile << "\nTotal number of trips by all trucks: " << totalTrips << "\n";
	analyticsFile << "Total distance traveled by all trucks: " << totalDistanceAllTrucks << " km\n";

	analyticsFile.close();

	for (int i = 0; i < graph.areaCount; ++i) {
		graph.areas[i].garbage = originalGarbage[i];
	}
}
Graph graph;

////////////////////////////////////////////////////////////////////////////////////////////////
// COMPLAINT MODULE

struct Complaint {
	int id;
	string category;
	string description;
	int priority;
};

struct MinHeap {
	Complaint complaints[100];
	int size;

	MinHeap() : size(0) {}

	void heapifyUp(int index) {
		while (index > 0) {
			int parent = (index - 1) / 2;
			if (complaints[parent].priority > complaints[index].priority) {
				swap(complaints[parent], complaints[index]);
				index = parent;
			}
			else {
				break;
			}
		}
	}

	void heapifyDown(int index) {
		int smallest = index;
		int left = 2 * index + 1;
		int right = 2 * index + 2;

		if (left < size && complaints[left].priority < complaints[smallest].priority)
			smallest = left;

		if (right < size && complaints[right].priority < complaints[smallest].priority)
			smallest = right;

		if (smallest != index) {
			swap(complaints[index], complaints[smallest]);
			heapifyDown(smallest);
		}
	}

	void insert(const Complaint& complaint) {
		if (size >= 100) {
			cout << "Heap is full. Cannot register more complaints.\n";
			return;
		}
		complaints[size] = complaint;
		heapifyUp(size);
		size++;
	}

	Complaint extractMin() {
		if (size == 0) {
			cout << "No complaints to display.\n";
			return { -1, "", "", -1 };
		}
		Complaint minComplaint = complaints[0];
		complaints[0] = complaints[size - 1];
		size--;
		heapifyDown(0);
		return minComplaint;
	}

	bool isEmpty() const {
		return size == 0;
	}
};

MinHeap complaintHeap;

int getValidatedUrgency() {
	int urgency;
	do {
		cout << "Enter urgency level (1-5): ";
		cin >> urgency;
		if (urgency < 1 || urgency > 5) {
			cout << "Invalid input. Please enter a value between 1 and 5.\n";
		}
	} while (urgency < 1 || urgency > 5);
	return urgency;
}

string getCategory() {
	int categoryChoice;
	string category;
	cout << "\nSelect category:\n";
	cout << "1. Vehicle\n";
	cout << "2. Service\n";
	cout << "3. Waste Collection\n";
	cout << "4. Suggestion\n";
	cout << "Enter your choice: ";
	cin >> categoryChoice;
	switch (categoryChoice) {
	case 1:
		category = "Vehicle";
		break;
	case 2:
		category = "Service";
		break;
	case 3:
		category = "Waste Collection";
		break;
	case 4:
		category = "Suggestion";
		break;
	default:
		cout << "Invalid choice, defaulting to 'General'.\n";
		category = "General";
	}
	return category;
}
void saveToFile(const Complaint& complaint) {
	ofstream outFile("complaints.txt", ios::app);
	if (outFile) {
		outFile << "ID: " << complaint.id << " | Category: " << complaint.category
			<< " | Description: " << complaint.description << " | Priority: " << complaint.priority << endl;
		outFile.close();
	}
	else {
		cout << "Error saving to file.\n";
	}
}

void registerComplaint(int& idCounter) {
	Complaint c;
	c.id = idCounter++;
	c.category = getCategory();
	cout << "Enter description: ";
	cin.ignore();
	getline(cin, c.description);
	c.priority = getValidatedUrgency();

	complaintHeap.insert(c);
	saveToFile(c);

	cout << "Complaint registered successfully!\n";
}
void displayComplaints() {
	ifstream inFile("complaints.txt");
	if (!inFile) {
		cout << "No complaints registered yet.\n";
		return;
	}

	complaintHeap.size = 0; 

	cout << "\n--- Complaints (From File) ---\n";
	string line;
	while (getline(inFile, line)) {
		Complaint c;
		size_t idPos = line.find("ID: ") + 4;
		size_t catPos = line.find(" | Category: ");
		size_t descPos = line.find(" | Description: ");
		size_t priPos = line.find(" | Priority: ");

		c.id = stoi(line.substr(idPos, catPos - idPos));
		c.category = line.substr(catPos + 13, descPos - (catPos + 13));
		c.description = line.substr(descPos + 16, priPos - (descPos + 16));
		c.priority = stoi(line.substr(priPos + 12));

		complaintHeap.insert(c);
	}
	inFile.close();

	while (!complaintHeap.isEmpty()) {
		Complaint c = complaintHeap.extractMin();
		cout << "ID: " << c.id << " | Category: " << c.category
			<< " | Description: " << c.description << " | Priority: " << c.priority << endl;
	}
}
void processComplaint() {
	ifstream inFile("complaints.txt");
	if (!inFile) {
		cout << "No complaints registered yet.\n";
		return;
	}

	complaintHeap.size = 0; 

	string line;
	while (getline(inFile, line)) {
		Complaint c;
		size_t idPos = line.find("ID: ") + 4;
		size_t catPos = line.find(" | Category: ");
		size_t descPos = line.find(" | Description: ");
		size_t priPos = line.find(" | Priority: ");

		c.id = stoi(line.substr(idPos, catPos - idPos));
		c.category = line.substr(catPos + 13, descPos - (catPos + 13));
		c.description = line.substr(descPos + 16, priPos - (descPos + 16));
		c.priority = stoi(line.substr(priPos + 12));

		complaintHeap.insert(c);
	}
	inFile.close();

	if (complaintHeap.isEmpty()) {
		cout << "No complaints to process.\n";
		return;
	}
	Complaint top = complaintHeap.extractMin();
	cout << "Processing Complaint ID: " << top.id
		<< " | Category: " << top.category
		<< " | Description: " << top.description
		<< " | Priority: " << top.priority << endl;

	// Save the remaining complaints back to the file
	ofstream outFile("complaints.txt", ios::trunc);
	if (outFile) {
		while (!complaintHeap.isEmpty()) {
			Complaint c = complaintHeap.extractMin();
			outFile << "ID: " << c.id << " | Category: " << c.category
				<< " | Description: " << c.description << " | Priority: " << c.priority << endl;
		}
		outFile.close();
	}
	else {
		cout << "Error saving remaining complaints to file.\n";
	}
}



void Complainmenu() {
	int choice;
	int idCounter = 1;

	// Load existing complaints to determine the next ID
	ifstream inFile("complaints.txt");
	if (inFile) {
		string line;
		while (getline(inFile, line)) {
			size_t idPos = line.find("ID: ") + 4;
			size_t catPos = line.find(" | Category: ");
			int id = stoi(line.substr(idPos, catPos - idPos));
			if (id >= idCounter) {
				idCounter = id + 1;
			}
		}
		inFile.close();
	}

	do {
		cout << "\n\t\t  Complaint Management System";
		cout << "\n\t\t===============================\n\n";
		cout << "1. Register Complaint\n";
		cout << "2. Display Complaints\n";
		cout << "3. Process Complaint\n";
		cout << "4. Main Menu\n";
		cout << "5. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			registerComplaint(idCounter);
			break;
		case 2:
			displayComplaints();
			break;
		case 3:
			processComplaint();
			break;
		case 4:
			cout << "Returning to main menu...\n";
			break;
		case 5:
			cout << "Exiting...\n";
			exit(0);
			break;
		default:
			cout << "Invalid choice, please try again.\n";
		}
	} while (choice != 4);
}


///////////////////////////////////////////////////////////////////////////////////////////
// RESOURSE MODULE

void checkResources() {
	cout << "\nAvailable Trucks:\n";
	cout << left << setw(15) << "Truck ID" << "Capacity (kg)\n";
	cout << string(25, '-') << endl;
	displayTrucks(truckRoot);
}
void planTruckTripsWithAssumedTrucks(Graph& graph, int additionalTrucks, int capacity) {
	cout << "\nPlanning truck trips with assumed additional trucks:\n";

	TruckNode* originalTruckRoot = truckRoot;

	vector<int> originalGarbage(graph.areaCount);
	for (int i = 0; i < graph.areaCount; ++i) {
		originalGarbage[i] = graph.areas[i].garbage;
	}
	truckRoot = nullptr;

	for (int i = 0; i < additionalTrucks; ++i) {
		string truckID = "T" + to_string(i + 1);
		truckRoot = insertTruck(truckRoot, truckID, capacity);
	}

	int totalAreas = graph.areaCount - 1;
	int totalTrips = 0;
	vector<int> truckTrips(additionalTrucks, 0);
	vector<int> truckDistances(additionalTrucks, 0);
	int totalDistanceAllAssumedTrucks = 0;

	bool garbageLeft = true;

	while (garbageLeft) {
		garbageLeft = false;
		bool allGarbageCollected = true;
		int totalGarbageCollected = 0;

		displayTargetedAreas(graph);
		cout << "\n\n";
		cout << "\tAvailable Trucks" << endl;
		cout << "-----------------------------------\n\n";
		displayTrucks(truckRoot);

		for (int truckIndex = 0; truckIndex < additionalTrucks; ++truckIndex) {
			string truckID = getTruckID(truckRoot, truckIndex);
			int truckCapacity = getTruckCapacity(truckRoot, truckIndex);
			int remainingCapacity = truckCapacity;

			vector<pair<string, int>> route;
			route.push_back({ "Dumping Station", 0 });

			int currentAreaIndex = 0;
			int totalDistance = 0;

			while (remainingCapacity > 0) {
				int nextAreaIndex = -1;
				int minDistance = INF;
				int maxGarbage = 0;

				for (int areaIndex = 1; areaIndex < graph.areaCount; ++areaIndex) {
					if (graph.areas[areaIndex].garbage > 0) {
						vector<int> path = dijkstra(graph, currentAreaIndex, areaIndex);
						int distance = path.size() - 1;
						if (distance < minDistance || (distance == minDistance && graph.areas[areaIndex].garbage > maxGarbage)) {
							minDistance = distance;
							nextAreaIndex = areaIndex;
							maxGarbage = graph.areas[areaIndex].garbage;
						}
					}
				}

				if (nextAreaIndex == -1) {
					break;
				}
				int garbage = graph.areas[nextAreaIndex].garbage;
				int load = min(garbage, remainingCapacity);
				remainingCapacity -= load;
				graph.areas[nextAreaIndex].garbage -= load;
				totalGarbageCollected += load;

				vector<int> pathToNextArea = dijkstra(graph, currentAreaIndex, nextAreaIndex);
				for (int areaIndex : pathToNextArea) {
					if (areaIndex != currentAreaIndex) {
						route.push_back({ graph.areas[areaIndex].name, 0 });
						totalDistance += graph.areas[currentAreaIndex].head->distance;
						currentAreaIndex = areaIndex;
					}
				}

				route.back().second = load;

				if (graph.areas[nextAreaIndex].garbage > 0) {
					garbageLeft = true;
				}
			}
			vector<int> pathToDumpingStation = dijkstra(graph, currentAreaIndex, 0);
			for (int areaIndex : pathToDumpingStation) {
				if (areaIndex != currentAreaIndex) {
					route.push_back({ graph.areas[areaIndex].name, 0 });
					totalDistance += graph.areas[currentAreaIndex].head->distance;
					currentAreaIndex = areaIndex;
				}
			}
			if (route.size() > 1 && route.back().first == "Dumping Station") {
				route.pop_back();
			}
			if (route.size() > 1) {
				truckTrips[truckIndex]++;
				totalTrips++;
				truckDistances[truckIndex] += totalDistance;
				totalDistanceAllAssumedTrucks += totalDistance;
				cout << "\nTruck ID: " << truckID << "\nRoute: \n";
				for (const auto& [area, collected] : route) {
					cout << area << " (" << collected << " kg) -> ";
				}
				cout << "Dumping Station (0 kg)\n\n";
				cout << "Total Distance Traveled: " << totalDistance << " km\n";
				cout << "Truck Capacity: " << truckCapacity << " kg, Returning with: " << remainingCapacity << " kg Capacity Left\n\n";
			}
		}
		for (int areaIndex = 1; areaIndex < graph.areaCount; ++areaIndex) {
			if (graph.areas[areaIndex].garbage > 0) {
				allGarbageCollected = false;
				break;
			}
		}

		if (allGarbageCollected || totalGarbageCollected == 0) {
			break;
		}
	}
	cout << "All areas serviced and garbage delivered to the dumping station.\n\n";

	vector<pair<int, pair<int, int>>> truckData;
	for (int truckIndex = 0; truckIndex < additionalTrucks; ++truckIndex) {
		string truckID = getTruckID(truckRoot, truckIndex);
		int truckIDNum = stoi(truckID.substr(1));
		truckData.push_back({ truckIDNum, { truckTrips[truckIndex], truckDistances[truckIndex] } });
	}

	sort(truckData.begin(), truckData.end());

	for (const auto& [truckIDNum, tripsAndDistance] : truckData) {
		cout << "Truck ID: T" << truckIDNum << " made " << tripsAndDistance.first << " trips and traveled " << tripsAndDistance.second << " km.\n";
	}
	cout << "\nTotal number of trips by all trucks: " << totalTrips << "\n";
	cout << "Total distance traveled by all assumed trucks: " << totalDistanceAllAssumedTrucks << " km\n";

	truckRoot = originalTruckRoot;

	for (int i = 0; i < graph.areaCount; ++i) {
		graph.areas[i].garbage = originalGarbage[i];
	}
}

void assumeMoreResources() {
	int additionalTrucks, capacity;
	cout << "Enter the number of additional trucks to assume: ";
	cin >> additionalTrucks;
	cout << "Enter the capacity of the truck: ";
	cin >> capacity;

	planTruckTripsWithAssumedTrucks(graph, additionalTrucks, capacity);
}

void recommendTrucks() {
	int totalGarbage = 0;
	for (int i = 1; i < graph.areaCount; ++i) {
		totalGarbage += graph.areas[i].garbage;
	}

	int truckCapacity = 2000;
	int recommendedTrucks = ceil(static_cast<double>(totalGarbage) / truckCapacity);

	cout << "\nRecommended number of trucks: " << recommendedTrucks << endl;
	cout << "It is recommended to have trucks with capacity of 2000 kg.\n";
}
void generateReport() {
	ofstream reportFile("report.txt", ios::out | ios::trunc);
	if (!reportFile) {
		cerr << "Error opening report file.\n";
		return;
	}
	cout << "Generating report...\n\n";
	cout << "\t\t\t\t\t   REPORT\n";
	cout << "\t\t\t\t\t============\n\n";

	double totalGarbage = 0;
	double totalFuelCost = 0;
	double fuelPricePerKm = 190;

	for (int i = 1; i < graph.areaCount; ++i) {
		totalGarbage += graph.areas[i].garbage;
	}

	totalFuelCost = totalDistanceAllTrucks * fuelPricePerKm;

	double averageDistancePerTruck = totalDistanceAllTrucks / getTruckCount(truckRoot);
	double dailyFuelCost = totalFuelCost;
	double monthlyFuelCost = dailyFuelCost * 30;

	double annualTrashInTons = (totalGarbage * 365) / 1000;

	reportFile << "==================================================================================================================================" << endl;
	reportFile << "\nAnnual Trash Collected: " << totalGarbage * 365 << " kg (" << annualTrashInTons << " tons)\n";
	reportFile << "Monthly Trash Collected: " << totalGarbage * 30 << " kg\n";
	reportFile << "Daily Trash Collected: " << totalGarbage << " kg\n";
	reportFile << "Total Fuel Cost: Rs. " << totalFuelCost << "\n";
	reportFile << "\nTotal Distance Traveled in a Day: " << totalDistanceAllTrucks << " km\n";
	reportFile << "Total Distance Traveled in a Month: " << totalDistanceAllTrucks * 30 << " km\n";
	reportFile << "Average Distance Traveled per Truck: " << averageDistancePerTruck << " km\n";
	reportFile << "\nDaily Fuel Cost: Rs. " << dailyFuelCost << "\n";
	reportFile << "Monthly Fuel Cost: Rs." << monthlyFuelCost << "\n";
	reportFile << "Total Trips: " << totalTrips << "\n";
	reportFile << "==================================================================================================================================" << endl;

	ifstream complaintFile("complaints.txt");
	if (complaintFile) {
		string line;
		reportFile << "\nComplaints:\n";
		while (getline(complaintFile, line)) {
			reportFile << line << endl;
		}
		complaintFile.close();
	}

	reportFile.close();

	cout << "==================================================================================================================================" << endl;
	cout << "\n\nAnnual Trash Collected: " << totalGarbage * 365 << " kg (" << annualTrashInTons << " tons)\n";
	cout << "Monthly Trash Collected: " << totalGarbage * 30 << " kg\n";
	cout << "Daily Trash Collected: " << totalGarbage << " kg\n";
	cout << "\nTotal Fuel Cost: Rs. " << totalFuelCost << "\n";
	cout << "Total Distance Traveled in a Day: " << totalDistanceAllTrucks << " km\n";
	cout << "Total Distance Traveled in a Month: " << totalDistanceAllTrucks * 30 << " km\n";
	cout << "Average Distance Traveled per Truck: " << averageDistancePerTruck << " km\n";
	cout << "\n\nDaily Fuel Cost: Rs. " << dailyFuelCost << "\n";
	cout << "Monthly Fuel Cost: Rs. " << monthlyFuelCost << "\n";
	cout << "Total Trips: " << totalTrips << "\n";

	cout << "==================================================================================================================================" << endl;

	ifstream displayComplaintFile("complaints.txt");
	if (displayComplaintFile) {
		string line;

		cout << "\n                                                        Complaints\n\n";
		while (getline(displayComplaintFile, line)) {
			cout << line << endl;
		}
		displayComplaintFile.close();
	}
	cout << "==================================================================================================================================" << endl;

	cout << "Report generated successfully.\n";
}
void resourceManagementMenu() {
	int choice;
	do {
		cout << "\n\t\t  Resource Management Portal";
		cout << "\n\t\t==============================\n\n";
		cout << "1. Check resources\n";
		cout << "2. Assume more resources\n";
		cout << "3. Recommend number of trucks\n";
		cout << "4. Exit to Main Menu\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			checkResources();
			break;
		case 2:
			
			addAreasFromAVL(graph, root);
			assumeMoreResources();

			break;
		case 3:
			recommendTrucks();
			break;
		
		case 4:
			cout << "Exiting to main menu...\n";
			mainMenu();
			break;
		default:
			cout << "Invalid choice. Please try again.\n";
		}
	} while (choice != 4);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// maim menu

void mainMenu() {
	int choice;
	do {
		cout << "\n\t\t\t  SMART CITY MANGEMENT SYSTEM";
		cout << "\n\t\t\t===============================\n\n";

		cout << "1. Manage Areas" << endl;
		cout << "2. Manage Trucks" << endl;
		cout << "3. Add Connections Between Areas" << endl;
		cout << "4. Display Areas Connection" << endl;
		cout << "5. Explore City Map" << endl;
		cout << "6. Plan Truck Trips" << endl;
		cout << "7. Complain Mangement\n";
		cout << "8. Resource Management\n";
		cout << "9. Generate report\n";
		cout << "10. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			Areamenu();
			break;
		case 2:
			truckMenu();
			break;
		case 3:
		{
			totalGarbage = 0;
			cout << "\n\n";
			cout << left << setw(20) << "Area Name"
				<< setw(15) << "Population"
				<< setw(20) << "Waste Growth Rate"
				<< "Garbage per Day" << endl;
			cout << string(75, '-') << endl;
			displayAreas(root, totalGarbage);

			cout << "\nTotal City Garbage per Day: " << fixed << setprecision(2) << totalGarbage << " kg  (Tons: " << totalGarbage / 1000 << " )\n\n";
			addAreasFromAVL(graph, root);
			string source, destination;
			int distance;
			cout << "Enter source area name: ";
			cin >> source;
			cout << "Enter destination area name: ";
			cin >> destination;
			cout << "Enter distance between areas (in km): ";
			cin >> distance;
			addConnection(graph, source, destination, distance);
			break;
		}
		case 4:
			displayGraph(graph);
			break;
		case 6:

			addAreasFromAVL(graph, root);
			planTruckTrips(graph);
			break;
		case 5: {
			cout << "   --------------------------------------------------------------------------------------------------------------------------------\n";
			cout << "  |                                                        EXPLORE YOUR CITY                                                       | \n";
			cout << "  |                                                                                                                                | \n";
			cout << "  |      -------------------------------------------------------------------------------------------------------                   |\n";
			cout << "  |  [DUMPING STATION] - - 6KM - - [NAZIMABAD]- 2KM  - -[5-STAR] - - - - - - - - - 5 KM - - - - - - - - [NAGAN]-                   |\n";
			cout << "  |      _______________________________     __________    ________*__________*_____________     _______________                   |\n";
			cout << "  |                                     | | |         / / /        | Fuel #6  |             | | |                                  |\n";
			cout << "  |                                     |   |        /   /         *----------*             |   |                                  |\n";
			cout << "  |                                     |   |       /   /                                   |   |                                  |\n";
			cout << "  |                                     |5KM|      /4KM/                                    |4KM|                                  |\n";
			cout << "  |                                     |   |     /   /                                     |   |                                  |\n";
			cout << "  |                                     |   |    /   /                                      |   |                                  |\n";
			cout << "  |                                     | | |   / / /                                       | | |                                  |\n";
			cout << "  |           *__________*              |   |  /   /                                        |   |                                  |\n";
			cout << "  |           | Fuel #1  |              |   | /   /                                         |   |                                  |\n";
			cout << "  |      -----*----------*--------------| | |/ / /------------------------------------------| | |---------------------------       |\n";
			cout << "  |      |8KM - - - - - - - - - - - - [LIAQATABAD] - - - - - - 7 KM - - - - - - - - - - - [HIGHWAY] - - - -  13 KM - - - -         |\n";
			cout << "  |      |    __________________________|   |_______________________________________________|   |_________________     _____       |\n";
			cout << "  |      | | |                          | | |                                               | | |                 |   |            |\n";
			cout << "  |      |   |                          |   |                                               |5KM|             *---* | |            |\n";
			cout << "  |      |   |                          |7 KM          *__________*                         |   |             | F |   |            |\n";
			cout << "  |      | | |                          | | |          | Fuel  #2 |                         | | |             | U |   |            |\n";
			cout << "  | -----     ---------------------------    ----------*----------*-------------------------|     ------      | E | | |            |\n";
			cout << "  |  [MAZAR-E-QUAID] - - 6 KM - - - - [GULSHAN] - - - - - - - - - - 8 KM - - - - - - - -  [SAFOORA] - -       | L |   |            |\n";
			cout << "  | _____________________________________   ________________________________________________     _______      | 5 |   |            |\n";
			cout << "  |      |   |                          |   |                                               | | |             *---* | |            |\n";
			cout << "  |      | | |                          | | |     ---------------------------------------.  |   |                 |   |            |\n";
			cout << "  |      |3KM|                          |2KM|   /   - 6 KM - - - - [AIRPORT] - 3 KM - -  |  |6KM|                 |   |            | \n";
			cout << "  |      |   |                          |   |  / /  ---------------------------------. | |  | | |                 | | |            |\n";
			cout << "  |      | | |      *__________*        | | | /   /                                  |   |  |   |   *__________*  |   |            |\n";
			cout << "  |      |   |      | Fuel #3  |        |   |/ / /                                   | | |  |   |   | Fuel #4  |  |   |            |\n";
			cout << "  | -----     ------*----------*--------|   |   /------------------------------------|   |__| | |---*----------*--| | |----        |\n";
			cout << "  |  - [SADDAR] - - - 10 KM - - - - - - [KARSAZ] - - - - - - - - - 9 KM - - - - - - - -  [MALIR] - - - 3KM  - -  [HADEED] - -      |\n";
			cout << "  | ________________________________________________________________________________________________________________________       |\n";
			cout << "   ________________________________________________________________________________________________________________________________|\n";
			break;
		}
		case 7:
			Complainmenu();
			break;

		case 8:
			resourceManagementMenu();
			break;

		case 9:
			generateReport();
			exit(0);
			break;
		case 10:
			cout << "Exiting system...\n";
			exit(0);
			break;
		default:
			cout << "Invalid choice. Please try again.\n";
		}

	} while (choice != 10);
}

int main() {
	root = insertArea(root, "NAZIMABAD", 1000, 0.5);
	root = insertArea(root, "5-STAR", 2000, 0.6);
	root = insertArea(root, "NAGAN", 2000, 0.6);
	root = insertArea(root, "LIAQATABAD", 1500, 1.5);
	root = insertArea(root, "HIGHWAY", 2000, 0.6);
	root = insertArea(root, "GULSHAN", 2000, 0.8);
	root = insertArea(root, "SAFOORA", 3000, 0.7);
	root = insertArea(root, "MALIR", 2500, 0.9);
	root = insertArea(root, "HADEED", 1500, 0.6);
	root = insertArea(root, "KARSAZ", 2000, 0.8);
	root = insertArea(root, "SADDAR", 1000, 0.5);
	root = insertArea(root, "AIRPORT", 2000, 0.6);
	root = insertArea(root, "MAZAR-E-QUAID", 1500, 1.5);

	truckRoot = insertTruck(truckRoot, "T1", 1000);
	truckRoot = insertTruck(truckRoot, "T2", 2000);
	truckRoot = insertTruck(truckRoot, "T3", 4500);
	truckRoot = insertTruck(truckRoot, "T4", 1000);
	initializeGraph(graph);
	addAreasFromAVL(graph, root);

	addConnection(graph, "Dumping Station", "NAZIMABAD", 6);
	addConnection(graph, "5-STAR", "NAGAN", 5);
	addConnection(graph, "5-STAR", "NAZIMABAD", 2);
	addConnection(graph, "NAGAN", "HIGHWAY", 4);
	addConnection(graph, "HIGHWAY", "LIAQATABAD", 7);
	addConnection(graph, "HIGHWAY", "HADEED", 13);
	addConnection(graph, "LIAQATABAD", "5-STAR", 4);
	addConnection(graph, "LIAQATABAD", "NAZIMABAD", 5);
	addConnection(graph, "LIAQATABAD", "MAZAR-E-QUAID", 8);
	addConnection(graph, "LIAQATABAD", "GULSHAN", 7);
	addConnection(graph, "KARSAZ", "GULSHAN", 2);
	addConnection(graph, "GULSHAN", "SAFOORA", 8);
	addConnection(graph, "SAFOORA", "MALIR", 6);
	addConnection(graph, "HADEED", "MALIR", 3);
	addConnection(graph, "MALIR", "KARSAZ", 9);
	addConnection(graph, "KARSAZ", "SADDAR", 10);
	addConnection(graph, "SADDAR", "MAZAR-E-QUAID", 3);
	addConnection(graph, "GULSHAN", "MAZAR-E-QUAID", 6);
	addConnection(graph, "AIRPORT", "KARSAZ", 6);
	addConnection(graph, "AIRPORT", "MALIR", 3);
	system("cls");
	mainMenu();
	return 0;
}