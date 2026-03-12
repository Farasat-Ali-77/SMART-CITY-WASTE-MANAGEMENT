# 🏙️ CityWaste - Smart City Waste Management System

A comprehensive C++ console application for managing urban waste collection operations. This system optimizes garbage truck routes, manages city areas, handles citizen complaints, and generates analytical reports for efficient municipal waste management.

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)

## 📋 Table of Contents

- [Features](#-features)
- [Data Structures & Algorithms](#-data-structures--algorithms)
- [System Architecture](#-system-architecture)
- [Installation](#-installation)
- [Usage](#-usage)
- [Modules](#-modules)
- [Sample Output](#-sample-output)
- [Contributing](#-contributing)

## ✨ Features

### 🗺️ Area Management
- Add and manage city areas with population and waste generation rates
- Calculate daily garbage output per area
- Track total city waste generation

### 🚛 Fleet Management
- Register garbage trucks with unique IDs and capacities
- View entire truck fleet inventory
- Efficient truck allocation for routes

### 🛣️ Intelligent Route Planning
- Optimal route calculation using shortest path algorithms
- Multi-stop trip planning based on garbage load
- Automatic return-to-dump-station routing
- Distance and fuel cost optimization

### 📢 Complaint Management
- Priority-based complaint processing
- Categorized complaints (Vehicle, Service, Waste Collection, Suggestions)
- Urgency levels (1-5) for prioritization
- Persistent storage in file system

### 📊 Resource Management & Analytics
- Check available resources
- Simulate scenarios with additional trucks
- Smart truck recommendations based on waste volume
- Comprehensive report generation with:
  - Daily/Monthly/Annual waste collection statistics
  - Fuel cost calculations
  - Trip analytics
  - Distance metrics

### 🗺️ Interactive City Map
- Visual ASCII representation of the city layout
- Shows areas, distances, and fuel stations

## 🔧 Data Structures & Algorithms

### Data Structures Used

| Data Structure | Usage | Time Complexity |
|----------------|-------|-----------------|
| **AVL Tree** | Area & Truck Management | O(log n) insert/search |
| **Graph (Adjacency List)** | City Map Representation | O(V + E) traversal |
| **Min-Heap** | Complaint Priority Queue | O(log n) insert/extract |
| **Vector** | Dynamic Route Storage | O(1) amortized append |
| **Linked List** | Graph Edge Storage | O(1) insertion |

### Algorithms Implemented

#### 1. AVL Tree Operations
```
- Insertion with self-balancing
- Left Rotation (LL case)
- Right Rotation (RR case)
- Left-Right Rotation (LR case)
- Right-Left Rotation (RL case)
- In-order Traversal for sorted display
```

#### 2. Dijkstra's Shortest Path Algorithm
```cpp
// Used for finding optimal routes between areas
vector<int> dijkstra(Graph& graph, int start, int target);
```
- **Purpose**: Calculate shortest path between dump station and collection areas
- **Complexity**: O(V²) with adjacency list implementation
- **Application**: Route optimization for garbage trucks

#### 3. Heap Operations (Priority Queue)
```cpp
// Min-Heap for complaint prioritization
void heapifyUp(int index);    // O(log n) - Bubble up after insertion
void heapifyDown(int index);  // O(log n) - Sink down after extraction
```

#### 4. Graph Traversal
- BFS/DFS concepts for area connectivity
- Edge weight management for distance calculations

### Algorithm Flow

```
┌─────────────────┐
│   Add Areas     │ ──► AVL Tree Insertion with Balancing
└─────────────────┘
         │
         ▼
┌─────────────────┐
│ Build City Map  │ ──► Graph Construction (Adjacency List)
└─────────────────┘
         │
         ▼
┌─────────────────┐
│  Plan Routes    │ ──► Dijkstra's Algorithm
└─────────────────┘
         │
         ▼
┌─────────────────┐
│ Handle Requests │ ──► Min-Heap Priority Queue
└─────────────────┘
```

## 🏗️ System Architecture

```
CityWaste/
├── CityWaste.cpp          # Main source file (all modules)
├── CityWaste.sln          # Visual Studio solution
├── CityWaste.vcxproj      # Project configuration
├── complaints.txt         # Persistent complaint storage
├── analytics.txt          # Trip analytics data
├── report.txt             # Generated reports
└── README.md              # Documentation
```

### Module Structure

```
┌────────────────────────────────────────────────────────────┐
│                    MAIN MENU                               │
├────────────┬────────────┬────────────┬────────────────────┤
│   Area     │   Truck    │   Graph    │    Complaint       │
│  Module    │   Module   │   Module   │     Module         │
│  (AVL)     │   (AVL)    │ (Dijkstra) │    (Min-Heap)      │
├────────────┴────────────┴────────────┴────────────────────┤
│              Resource Management & Reporting               │
└────────────────────────────────────────────────────────────┘
```

## 💻 Installation

### Prerequisites
- C++ Compiler (C++17 or later)
- Visual Studio 2019/2022 (recommended) or any C++ IDE
- Windows OS

### Build Steps

#### Using Visual Studio
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/CityWaste.git
   ```
2. Open `CityWaste.sln` in Visual Studio
3. Build the solution (Ctrl + Shift + B)
4. Run the program (F5)

#### Using Command Line (g++)
```bash
g++ -std=c++17 CityWaste.cpp -o CityWaste.exe
./CityWaste.exe
```

## 🚀 Usage

### Main Menu Options

```
╔═══════════════════════════════════════╗
║     SMART CITY MANAGEMENT SYSTEM      ║
╠═══════════════════════════════════════╣
║  1. Manage Areas                      ║
║  2. Manage Trucks                     ║
║  3. Add Connections Between Areas     ║
║  4. Display Areas Connection          ║
║  5. Explore City Map                  ║
║  6. Plan Truck Trips                  ║
║  7. Complaint Management              ║
║  8. Resource Management               ║
║  9. Generate Report                   ║
║ 10. Exit                              ║
╚═══════════════════════════════════════╝
```

### Quick Start Guide

1. **Add Areas**: Register city zones with population data
2. **Add Trucks**: Register garbage trucks with capacities
3. **Connect Areas**: Define roads/distances between areas
4. **Plan Trips**: Let the system optimize collection routes
5. **Generate Reports**: View analytics and statistics

## 📦 Modules

### Area Management Module
- Uses **AVL Tree** for O(log n) operations
- Stores: Area name, Population, Waste growth rate, Daily garbage
- Automatic garbage calculation: `garbage = population × wasteGrowthRate`

### Truck Management Module
- **AVL Tree** based fleet management
- Stores: Truck ID, Capacity (kg)
- Prevents duplicate truck IDs

### Graph Module
- **Adjacency List** representation
- Bidirectional edges (roads)
- Weighted edges (distances in km)
- **Dijkstra's Algorithm** for shortest paths

### Complaint Module
- **Min-Heap** based priority queue
- Categories: Vehicle, Service, Waste Collection, Suggestions
- Priority levels: 1 (highest) to 5 (lowest)
- File-based persistence

### Reporting Module
- Generates comprehensive analytics
- Calculates fuel costs (Rs. 190/km)
- Trip statistics and distance metrics

## 📈 Sample Output

### Route Planning
```
Truck ID: T3
Route: 
Dumping Station (0 kg) -> NAZIMABAD (0 kg) -> 5-STAR (1200 kg) -> 
NAGAN (1200 kg) -> HIGHWAY (1200 kg) -> HADEED (900 kg) -> 
Dumping Station (0 kg)

Total Distance Traveled: 61 km
Truck Capacity: 4500 kg, Returning with: 0 kg Capacity Left
```

### Report Summary
```
═══════════════════════════════════════════════════════════
Annual Trash Collected: 6,843,750 kg (6843.75 tons)
Monthly Trash Collected: 562,500 kg
Daily Trash Collected: 18,750 kg
Total Fuel Cost: Rs. 76,950

Total Distance Traveled in a Day: 405 km
Average Distance Traveled per Truck: 81 km
Total Trips: 9
═══════════════════════════════════════════════════════════
```

## 🎯 Key Highlights

- **Efficient Data Management**: AVL trees ensure O(log n) operations
- **Optimal Routing**: Dijkstra's algorithm minimizes travel distance
- **Priority Processing**: Min-heap ensures urgent complaints are handled first
- **Scalable Architecture**: Modular design allows easy feature additions
- **Real-world Application**: Simulates actual municipal waste management

## 🤝 Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 👨‍💻 Author

Developed as a Data Structures & Algorithms project demonstrating practical applications of:
- AVL Trees
- Graph Algorithms (Dijkstra)
- Priority Queues (Min-Heap)
- File I/O Operations

---
