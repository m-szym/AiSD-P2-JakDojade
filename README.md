# JakDojade? 
### Algorithms and Data Structures project
## Author: Marek Szymański

## Project description
The project is a simple program that finds the shortest path between two cities on a map. The map is represented as a directed graph, where each vertice represents a city and each edge represents a road or a flight connection between two cities. The edges are weighted with the time of travel between the two cities. The program uses Dijkstra's algorithm to find the shortest path between two given cities.

### Map format
This is an example of a map in format used by the program:
```
.........GDANSK.....
........*...........
........#...........
........#...........
*##################.
#SZCZECIN.........#.
#.................#.
##................#.
.############*#####.
.#...WARSZAWA.......
.#..................
.#############......
.#...........#......
.#..WROCLAW.##......
.#..*.......*.......
.####.......#KIELCE.
......*##.#########.
.OPOLE..#.*.......#.
........#.KRAKOW..#.
........###########.
```
> Legend:
> - `.` - empty space
> - `#` - road
> - `*` - city
> - `GDANSK` - name of the closest city (`*` symbol)

### Goals
Main goals of the project were:
- implementing Dijkstra's algorithm to find the shortest path between two vertices in a graph
- personally implementing all the neccessary data structures (list, map, queue etc.) - no STL and no `string`

### How does it work?
The program first reads the map (see Map format for details) from standard input, parses it using BFS and creates a graph. 
Then it reads additional information about flight connections between cities, which are not marked on the map, which are then also added to the graph.

On the graph each vertice represents a city and directed edges represent either roads between cities or flight connections, the edges are weighted with the time of travel.

Afterwards the program reads queries from standard input, each query consisting of two city names and, using Dijkstra's algorithm, finds the shortest path between the two given cities.

