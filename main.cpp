#include <iostream>

struct Node {
    int key;
    int priority;
    Node* left = nullptr;
    Node* right = nullptr;
    int size = 1;

    Node(int key) : key(key), priority(std::rand() % 1'000'000) {}
    ~Node() {
      delete left;
      delete right;
    }
};

class CartesianTree {
 public:
  CartesianTree() = default;

  void Insert(int key) { root_ = Insert(root_, key); }
  void Remove(int key) { root_ = Remove(root_, key); }
  bool Find(int key) { return Find(root_, key); }
  int Next(int key) { return Next(root_, key); }
  int Prev(int key) { return Prev(root_, key); }
  int FindKTH(int k) { return FindKTH(root_, k + 1); }

  ~CartesianTree() { delete root_; }

 private:
  Node* root_ = nullptr;

  Node* Merge(Node* l, Node* r);
  std::pair<Node*, Node*> Split(Node* p, int key);
  Node* Insert(Node* p, int key);
  Node* Remove(Node* p, int key);
  bool Find(Node* p, int key);
  int Next(Node* p, int key);
  int Prev(Node* p, int key);
  int FindKTH(Node* p, int k);
  Node* FixNode(Node* p);
  int Size(Node* p) { return (p == nullptr) ? 0 : p->size; }
};

Node* CartesianTree::Merge(Node* l, Node* r) {
  if (l == nullptr || r == nullptr) {
    return ((l == nullptr) ? r : l);
  }
  if (l->priority >= r->priority) {
    l->right = Merge(l->right, r);
    return FixNode(l);
  }
  r->left = Merge(l, r->left);
  return FixNode(r);
}

std::pair<Node*, Node*> CartesianTree::Split(Node* p, int key) {
  if (p == nullptr) {
    return std::make_pair(nullptr, nullptr);
  }
  if (p->key < key) {
    std::pair<Node*, Node*> t = Split(p->right, key);
    p->right = t.first;
    return std::make_pair(FixNode(p), t.second);
  }
  std::pair<Node*, Node*> t = Split(p->left, key);
  p->left = t.second;
  return std::make_pair(t.first, FixNode(p));
}

Node* CartesianTree::Insert(Node* p, int key) {
  if (p == nullptr) {
    p = new Node(key);
    return p;
  }
  if (Find(p, key)) {
    return p;
  }
  std::pair<Node*, Node*> t = Split(p, key);
  t.first = Merge(t.first, new Node(key));
  t.second = Merge(t.first, t.second);
  return t.second;
}

Node* CartesianTree::Remove(Node* p, int key) {
  if (!Find(key)) {
    return p;
  }
  std::pair<Node*, Node*> t1 = Split(p, key + 1);
  std::pair<Node*, Node*> t2 = Split(t1.first, key);
  delete t2.second;
  return Merge(t2.first, t1.second);
}

bool CartesianTree::Find(Node* p, int key) {
  if (p == nullptr) {
    return false;
  }
  if (p->key == key) {
    return true;
  }
  if (p->key <= key) {
    return Find(p->right, key);
  }
  return Find(p->left, key);
}

int CartesianTree::Next(Node* p, int key) {
  if (p == nullptr) {
    return key;
  }
  if (p->key > key && (p->left == nullptr || p->left->key <= key)) {
    return p->key;
  }
  if (p->key > key) {
    return Next(p->left, key);
  }
  return Next(p->right, key);
}

int CartesianTree::Prev(Node* p, int key) {
  if (p == nullptr) {
    return key;
  }
  if (p->key < key && (p->right == nullptr || p->right->key >= key)) {
    return p->key;
  }
  if (p->key < key) {
    return Prev(p->right, key);
  }
  return Prev(p->left, key);
}

int CartesianTree::FindKTH(Node* p, int k) {
  if (p == nullptr) {
    return std::numeric_limits<int>::min();
  }
  if (Size(p) < k) {
    return std::numeric_limits<int>::min();
  }
  if (Size(p->left) + 1 == k) {
    return p->key;
  }
  if (Size(p->left) >= k) {
    if (p->left == nullptr) {
      return std::numeric_limits<int>::min();
    }
    return FindKTH(p->left, k);
  }
  if (p->right == nullptr) {
    return std::numeric_limits<int>::min();
  }
  return FindKTH(p->right, k - Size(p->left) - 1);
}

Node* CartesianTree::FixNode(Node* p) {
  if (p == nullptr) {
    return p;
  }
  p->size = Size(p->left) + Size(p->right) + 1;
  return p;
}

int main() {
  CartesianTree tree;
  std::string s;
  int x;
  while (std::cin >> s >> x) {
    if (s == "insert") {
      tree.Insert(x);
      continue;
    }
    if (s == "delete") {
      tree.Remove(x);
      continue;
    }
    if (s == "exists") {
      if (tree.Find(x)) {
        std::cout << "true" << '\n';
      } else {
        std::cout << "false" << '\n';
      }
      continue;
    }
    if (s == "next") {
      int t = tree.Next(x);
      if (x != t) {
        std::cout << t << '\n';
      } else {
        std::cout << "none" << '\n';
      }
      continue;
    }
    if (s == "prev") {
      int t = tree.Prev(x);
      if (x != t) {
        std::cout << t << '\n';
      } else {
        std::cout << "none" << '\n';
      }
      continue;
    }
    if (s == "kth") {
      int t = tree.FindKTH(x);
      if (t != std::numeric_limits<int>::min()) {
        std::cout << t << '\n';
      } else {
        std::cout << "none" << '\n';
      }
    }
  }
}