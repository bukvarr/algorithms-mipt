#include <iostream>

#include <string>

struct Node {
    std::string key;
    std::string value;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    bool is_left = false;

    Node(const std::string& key, const std::string& value)
            : key(key), value(value) {}

    ~Node() {
      delete left;
      delete right;
    }
};

class SplayTree {
 public:
  SplayTree() : root_(nullptr) {}

  void Insert(const std::string& key, const std::string& value);

  std::string ReturnKeyValue(const std::string& key);

  ~SplayTree() { delete root_; }

 private:
  Node* root_;

  Node* LeftRotate(Node* y);
  Node* RightRotate(Node* y);
  Node* ZigZag(Node* x);
  Node* ZigZig(Node* x);
  Node* Zig(Node* x);
  Node* Splay(Node* x);
};

Node* SplayTree::LeftRotate(Node* y) {
  Node* x = y->right;
  y->right = x->left;
  x->left = y;
  x->parent = y->parent;
  y->parent = x;
  x->is_left = y->is_left;
  y->is_left = true;
  if (y->right != nullptr) {
    y->right->is_left = false;
    y->right->parent = y;
  }
  return x;
}

Node* SplayTree::RightRotate(Node* y) {
  Node* x = y->left;
  y->left = x->right;
  x->right = y;
  x->parent = y->parent;
  y->parent = x;
  x->is_left = y->is_left;
  y->is_left = false;
  if (y->left != nullptr) {
    y->left->is_left = true;
    y->left->parent = y;
  }
  return x;
}

Node* SplayTree::ZigZag(Node* x) {
  Node* z = x->parent;
  Node* y = z->parent;
  if (!x->is_left && z->is_left) {
    y->left = LeftRotate(y->left);
    y = RightRotate(y);
    return y;
  }
  if (x->is_left && !z->is_left) {
    y->right = RightRotate(y->right);
    y = LeftRotate(y);
    return y;
  }
  return x;
}

Node* SplayTree::ZigZig(Node* x) {
  Node* z = x->parent;
  Node* y = z->parent;
  if (x->is_left && z->is_left) {
    y = RightRotate(y);
    y = RightRotate(y);
    return y;
  }
  if (!x->is_left && !z->is_left) {
    y = LeftRotate(y);
    y = LeftRotate(y);
    return y;
  }
  return x;
}

Node* SplayTree::Zig(Node* x) {
  Node* z = x->parent;
  if (x->is_left) {
    z = RightRotate(z);
    return z;
  }
  if (!x->is_left) {
    z = LeftRotate(z);
    return z;
  }
  return x;
}

Node* SplayTree::Splay(Node* x) {
  while (x->parent != nullptr) {
    if (x->is_left) {
      x->parent->left = x;
    } else {
      x->parent->right = x;
    }
    Node* z = x->parent;
    if (z->parent == nullptr) {
      z = Zig(x);
      x = z;
      break;
    }
    if (z->is_left ^ x->is_left) {
      z->parent = ZigZag(x);
      x = z->parent;
    } else {
      z->parent = ZigZig(x);
      x = z->parent;
    }
  }
  return x;
}

void SplayTree::Insert(const std::string& key, const std::string& value) {
  Node* t = new Node(key, value);
  if (root_ == nullptr) {
    root_ = t;
    return;
  }
  Node* current_node = root_;
  while (true) {
    t->parent = current_node;
    if (key == current_node->key) {
      root_ = Splay(current_node);
      return;
    }
    if (key < current_node->key) {
      if (current_node->left == nullptr) {
        t->is_left = true;
        current_node->left = t;
        root_ = Splay(current_node->left);
        return;
      }
      current_node = current_node->left;
    } else {
      if (current_node->right == nullptr) {
        t->is_left = false;
        current_node->right = t;
        root_ = Splay(current_node->right);
        return;
      }
      current_node = current_node->right;
    }
  }
}

std::string SplayTree::ReturnKeyValue(const std::string& key) {
  Node* current_node = root_;
  while (true) {
    if (current_node == nullptr) {
      return "";
    }
    if (current_node->key == key) {
      root_ = Splay(current_node);
      return current_node->value;
    }
    if (current_node->key > key) {
      current_node = current_node->left;
    } else {
      current_node = current_node->right;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::basic_ostream<char, std::char_traits<char> >* aboba = 0;
  std::cin.tie(aboba);
  SplayTree tree_1;
  SplayTree tree_2;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::string key, value;
    std::cin >> key >> value;
    tree_1.Insert(key, value);
    tree_2.Insert(value, key);
  }
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    std::string key;
    std::cin >> key;
    std::string result = tree_1.ReturnKeyValue(key);
    if (result.empty()) {
      result = tree_2.ReturnKeyValue(key);
    }
    std::cout << result << '\n';
  }
}