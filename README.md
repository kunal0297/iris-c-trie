# 🔍 IRIS C-Trie: High-Performance Prefix Lookup Extension for InterSystems IRIS

IRIS C-Trie is a native C extension for [InterSystems IRIS](https://www.intersystems.com/products/intersystems-iris/) that implements a **compressed trie (radix tree)** to support **fast and memory-efficient prefix-based lookups**. It's designed for applications where speed and scalability in string searches are critical — such as **auto-completion, routing, and command matching**.

---

## 🚀 Features

- ✅ High-performance prefix search using a C-implemented compressed trie
- ✅ Simple ObjectScript interface for easy integration with IRIS
- ✅ Optimized for minimal memory usage
- ✅ Designed for scalability and real-time use cases

---

## 🧰 Use Cases

- Command-line interface matching (e.g., finding all commands starting with a prefix)
- Auto-complete in large datasets
- Hierarchical key-value stores or routing tables
- Efficient search in metadata-heavy environments

---

## 📦 Installation

### 🔧 Prerequisites

- InterSystems IRIS (2021.1+ recommended)
- GCC or Clang
- Make
- Linux (tested on Ubuntu)

### 📥 Clone and Build

```bash
git clone https://github.com/kunal0297/iris-c-trie.git
cd iris-c-trie
make
