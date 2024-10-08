#pragma once
#include "kdbnode.h"
#include <array>
#include <filesystem>
#include <vector>
#include <queue>

// Implementation of a KD-Tree and a B+ Tree combined
class KDBTree
{
private:
  KDBNode *_root;
  size_t _vector_count;
  size_t _layers_count;
  u_int _dim;
  std::string _folderpath;

  std::queue<KDBNode *> _loaded_embeddings;
  u_int _max_loaded_embeddings;

  KDBNode *__generate_until_n_layers(KDBNode *curr, u_int layers);
  int __get_node_id_from_filepath(std::__fs::filesystem::path file_path) const;
  bool __inorder_traversal_equality(KDBNode *a, KDBNode *b);
  std::vector<Embedding *> __inorder_traversal_query(Embedding &queryEmbedding);
  void __inorder_traversal_delete(KDBNode *curr);
  void __cycle_cache(KDBNode *toInsert);
  KDBNode *__load_node(const std::string &folderpath, int fileIndex);
  // NOTE: LRU CACHE
  void __increase_layer_n(int layerIncrease);
  void __increase_layer_one_helper(KDBNode *curr);
  void __increase_layer_one();
  void __increase_node_one(KDBNode *curr, int splitIndex);

public:
  size_t node_count;
  std::vector<std::__fs::filesystem::path> __get_folder_files(const std::string &folderpath) const;

  KDBTree() = delete;
  explicit KDBTree(const std::string &folderpath);
  KDBTree(u_int dim, const std::string &folderpath);
  KDBTree(u_int dim, const std::string &folderpath, u_int starting_layers_count);
  KDBTree(KDBNode *root, size_t vectorCount, int layers, const std::string &folderpath, int nodeCount);
  KDBTree(KDBTree &&other) noexcept;
  KDBTree &operator=(KDBTree &&other) noexcept;
  ~KDBTree();

  bool operator==(KDBTree &other);

  bool insertEmbedding(Embedding &embedding);
  void setRoot(KDBNode *root);
  void folderpath(const std::string &folderpath);
  void dimensions(u_int dim);
  u_int dimensions() const;
  void layers(size_t layers);
  size_t layers() const;
  size_t vectors() const;
  KDBNode *root();

  KDBNode *__read_files_left_to_right(std::vector<std::__fs::filesystem::path> &files, int &fileIndex, int &nodeCount, int &dimensions, int layer, size_t &vectorCount);
  std::pair<Embedding *, float> query(const std::string &folderpath, const Embedding &queryEmbedding);

  friend std::ostream &operator<<(std::ostream &os, KDBTree &obj);
};
