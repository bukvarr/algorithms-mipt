#include <iostream>

struct Node {
    long long key;
    int height;
    Node* left;
    Node* right;

    int BFactor() {
      return ((left == nullptr) ? 0 : left->height) -
             ((right == nullptr) ? 0 : right->height);
    }

    Node(long long key) : key(key), height(1), left(nullptr), right(nullptr) {}
    ~Node() {
      delete left;
      delete right;
    }
};

class AVLTree {
 private:
  Node* root_;
  void HeightUpdate(Node* p);

  Node* LeftRotate(Node* p);

  Node* RightRotate(Node* p);

  Node* Balance(Node* p);

  Node* Insert(Node* p, long long key);

  bool Find(Node* p, long long key);

  long long FindNearestGreaterKey(Node* p, long long key);

 public:
  AVLTree() : root_(nullptr) {}

  void Insert(long long key) { root_ = Insert(root_, key); }

  bool Find(long long key) { return Find(root_, key); }

  long long FindNearestGreaterKey(long long key) {
    return FindNearestGreaterKey(root_, key);
  }

  ~AVLTree() { delete root_; }
};

void AVLTree::HeightUpdate(Node* p) {
  int l_height = (p->left == nullptr) ? 0 : p->left->height;
  int r_height = (p->right == nullptr) ? 0 : p->right->height;
  p->height = std::max(l_height, r_height) + 1;
}

Node* AVLTree::LeftRotate(Node* p) {
  if (p->right == nullptr) {
    return p;
  }
  Node* q = p->right;
  p->right = q->left;
  q->left = p;
  HeightUpdate(p);
  HeightUpdate(q);
  return q;
}

Node* AVLTree::RightRotate(Node* p) {
  if (p->left == nullptr) {
    return p;
  }
  Node* q = p->left;
  p->left = q->right;
  q->right = p;
  HeightUpdate(p);
  HeightUpdate(q);
  return q;
}

Node* AVLTree::Balance(Node* p) {
  HeightUpdate(p);
  if (p->BFactor() == 2) {
    if (p->left->BFactor() < 0) {
      p->left = LeftRotate(p->left);
    }
    p = RightRotate(p);
    return p;
  }
  if (p->BFactor() == -2) {
    if (p->right->BFactor() > 0) {
      p->right = RightRotate(p->right);
    }
    p = LeftRotate(p);
    return p;
  }
  return p;
}

Node* AVLTree::Insert(Node* p, long long key) {
  if (p == nullptr) {
    p = new Node(key);
  }
  if (key == p->key) {
    return Balance(p);
  }
  if (key < p->key) {
    p->left = Insert(p->left, key);
  } else {
    p->right = Insert(p->right, key);
  }
  return Balance(p);
}

bool AVLTree::Find(Node* p, long long key) {
  bool found = false;
  if (p == nullptr) {
    return found;
  }
  if (p->key == key) {
    return true;
  }
  if (p->key > key) {
    found = Find(p->left, key);
  }
  if (p->key < key) {
    found = Find(p->right, key);
  }
  return found;
}

long long AVLTree::FindNearestGreaterKey(Node* p, long long key) {
  long long found_key = -1;
  if (p == nullptr) {
    return found_key;
  }
  if (p->key >= key) {
    found_key = FindNearestGreaterKey(p->left, key);
    if (found_key == -1) {
      found_key = p->key;
    }
  }
  if (p->key < key) {
    found_key = FindNearestGreaterKey(p->right, key);
  }
  return found_key;
}

int main() {
  AVLTree tree;
  int q;
  std::cin >> q;
  bool prev_is_next = false;
  long long prev_key = 0;
  for (int i = 0; i < q; ++i) {
    char c;
    long long key;
    std::cin >> c;
    std::cin >> key;
    if (c == '+') {
      if (prev_is_next) {
        tree.Insert((prev_key + key) % 1'000'000'000);
      } else {
        tree.Insert(key);
      }
      prev_is_next = false;
    }
    if (c == '?') {
      long long t = tree.FindNearestGreaterKey(key);
      std::cout << t << '\n';
      prev_is_next = true;
      prev_key = t;
    }
  }
}
