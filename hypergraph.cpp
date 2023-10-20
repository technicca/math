#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

class Vertex {
  public:
    static int id_counter;
    int id;
    int color;
    Vertex() : id(id_counter++), color(-1) {}
};

int Vertex::id_counter = 0;

class Hyperedge {
  public:
    std::vector<Vertex *> vertices;
    Hyperedge(std::vector<Vertex *> vertices) : vertices(vertices) {}
};

class Hypergraph {
  public:
    std::vector<Vertex *> vertices;
    std::vector<Hyperedge *> hyperedges;

    void add_vertex(Vertex *vertex) { vertices.push_back(vertex); }

    void remove_vertex(Vertex *vertex) {
        vertices.erase(std::remove(vertices.begin(), vertices.end(), vertex), vertices.end());

        for (auto &hyperedge : hyperedges) {
            hyperedge->vertices.erase(
                std::remove(hyperedge->vertices.begin(), hyperedge->vertices.end(), vertex),
                hyperedge->vertices.end());
        }
    }

    void add_hyperedge(Hyperedge *hyperedge) { hyperedges.push_back(hyperedge); }

    void remove_hyperedge(Hyperedge *hyperedge) {
        hyperedges.erase(std::remove(hyperedges.begin(), hyperedges.end(), hyperedge),
                         hyperedges.end());
    }

    int degree(Vertex *vertex) {
        int count = 0;
        for (auto &hyperedge : hyperedges) {
            if (std::find(hyperedge->vertices.begin(), hyperedge->vertices.end(), vertex)
                != hyperedge->vertices.end()) {
                count++;
            }
        }
        return count;
    }

    void print_incidence_matrix() {
        std::cout << "Incidence Matrix: \n";
        for (auto &vertex : vertices) {
            for (auto &hyperedge : hyperedges) {
                if (std::find(hyperedge->vertices.begin(), hyperedge->vertices.end(), vertex)
                    != hyperedge->vertices.end()) {
                    std::cout << "1 ";
                } else {
                    std::cout << "0 ";
                }
            }
            std::cout << "\n";
        }
    }

    void dfs_h(Hyperedge *hyperedge, std::vector<Vertex *> &visited) {
        for (auto &vertex : hyperedge->vertices) {
            if (std::find(visited.begin(), visited.end(), vertex) == visited.end()) {
                visited.push_back(vertex);
                std::cout << "Visited via DFS: " << vertex->id << std::endl;
                for (auto &he : hyperedges) {
                    if (std::find(he->vertices.begin(), he->vertices.end(), vertex)
                        != he->vertices.end()) {
                        dfs_h(he, visited);
                    }
                }
            }
        }
    }

    void bfs_h(std::vector<Vertex *> &visited) {
        std::vector<Hyperedge *> queue;
        if (hyperedges.empty()) {
            return;
        }
        queue.push_back(hyperedges[0]);
        while (!queue.empty()) {
            Hyperedge *hyperedge = queue.front();
            queue.erase(queue.begin());
            for (auto &vertex : hyperedge->vertices) {
                if (std::find(visited.begin(), visited.end(), vertex) == visited.end()) {
                    visited.push_back(vertex);
                    std::cout << "Visited via BFS: " << vertex->id << std::endl;
                    for (auto &he : hyperedges) {
                        if (std::find(he->vertices.begin(), he->vertices.end(), vertex)
                            != he->vertices.end()) {
                            queue.push_back(he);
                        }
                    }
                }
            }
        }
    }

    void coloring() {
        int color = 0;
        for (auto &vertex : vertices) {
            bool valid;
            do {
                valid = true;
                color++;
                for (auto &hyperedge : hyperedges) {
                    if (std::find(hyperedge->vertices.begin(), hyperedge->vertices.end(), vertex)
                        != hyperedge->vertices.end()) {
                        for (auto &v : hyperedge->vertices) {
                            if (v != vertex && v->color == color) {
                                valid = false;
                                break;
                            }
                        }
                    }
                    if (!valid) {
                        break;
                    }
                }
            } while (!valid);
            vertex->color = color;
            std::cout << "Vertex " << vertex->id << " colored with color " << color << std::endl;
        }
    }

    void partition(int parts) {
        int part_size = vertices.size() / parts;
        if (vertices.size() % parts != 0) {
            part_size++;
        }
        std::vector<std::vector<Vertex *>> partitions(parts);
        for (int i = 0; i < vertices.size(); ++i) {
            partitions[i / part_size].push_back(vertices[i]);
        }
        for (int i = 0; i < partitions.size(); ++i) {
            std::cout << "Partition " << i << " contains vertices: ";
            for (auto &vertex : partitions[i]) {
                std::cout << vertex->id << ' ';
            }
            std::cout << std::endl;
        }
    }

    Hypergraph sub_hypergraph(const std::vector<Vertex *> &vertices_to_remove) {
        Hypergraph sub_hypergraph(*this);
        for (auto &vertex : vertices_to_remove) sub_hypergraph.remove_vertex(vertex);
        return sub_hypergraph;
    }

    Hypergraph dual() {
        Hypergraph dual_graph;
        for (auto &vertex : this->vertices) {
            std::vector<Vertex *> vertices = {new Vertex()};
            dual_graph.add_hyperedge(new Hyperedge(vertices));
        }
        for (auto &hyperedge : this->hyperedges) {
            Vertex *vertex = new Vertex();
            for (auto &vertex_e : hyperedge->vertices) {
                dual_graph.hyperedges[vertex_e->id]->vertices.push_back(vertex);
            }
            dual_graph.add_vertex(vertex);
        }
        return dual_graph;
    }

    bool is_Berge_acyclic() {
        for (auto &vertex : vertices) {
            if (degree(vertex) > 1) return false;
        }
        return true;
    }
};

// Generate random hypergraph
Hypergraph generate_random_hypergraph(int vertex_count, int edge_count) {
    Hypergraph hypergraph;
    for (int i = 0; i < vertex_count; ++i) {
        hypergraph.add_vertex(new Vertex());
    }

    for (int i = 0; i < edge_count; ++i) {
        int edge_size = std::max(2, rand() % vertex_count);  // At least two vertices in edge
        std::vector<Vertex *> vertices;
        for (int j = 0; j < edge_size; ++j) {
            vertices.push_back(hypergraph.vertices[rand() % vertex_count]);
        }
        hypergraph.add_hyperedge(new Hyperedge(vertices));
    }

    return hypergraph;
}

int main() {
    Hypergraph hypergraph = generate_random_hypergraph(10, 5);

    std::cout << "\n================== Hypergraph Structure ================== \n";
    std::cout << "Vertices: ";
    for (auto &v : hypergraph.vertices) std::cout << v->id << " ";
    std::cout << "\nHyperedges: ";
    for (auto &h : hypergraph.hyperedges) {
        std::cout << "{ ";
        for (auto &v : h->vertices) std::cout << v->id << " ";
        std::cout << "} ";
    }
    std::cout << "\n\n================== Incidence Matrix ================== \n";
    hypergraph.print_incidence_matrix();

    std::cout << "\n================== DFS Traversal ================== \n";
    std::vector<Vertex *> visited;
    hypergraph.dfs_h(hypergraph.hyperedges[0], visited);
    visited.clear();

    std::cout << "\n================== BFS Traversal ================== \n";
    hypergraph.bfs_h(visited);
    visited.clear();

    std::cout << "\n================== Coloring ================== \n";
    hypergraph.coloring();

    std::cout << "\n================== Partitioning ================== \n";
    hypergraph.partition(3);

    std::cout << "\n================== Sub-Hypergraph ================== \n";
    std::vector<Vertex *> vertices_to_remove = {hypergraph.vertices[0], hypergraph.vertices[1]};
    Hypergraph sub_hypergraph = hypergraph.sub_hypergraph(vertices_to_remove);

    std::cout << "Sub-Hypergraph Vertices: ";
    for (auto &vertex : sub_hypergraph.vertices) {
        std::cout << vertex->id << " ";
    }
    std::cout << "\n";

    std::cout << "\n================== Dual Hypergraph ================== \n";
    Hypergraph dual_hypergraph = hypergraph.dual();

    std::cout << "Dual Hypergraph Vertices: ";
    for (auto &vertex : dual_hypergraph.vertices) {
        std::cout << vertex->id << " ";
    }
    std::cout << "\n";

    std::cout << "\n================== Berge Acyclicity Check ================== \n";
    if (hypergraph.is_Berge_acyclic())
        std::cout << "The hypergraph is Berge acyclic.\n" << std::endl;
    else
        std::cout << "The hypergraph is not Berge acyclic.\n" << std::endl;

    return 0;
}
