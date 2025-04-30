# High-Performance Prefix Lookup Extension for InterSystems IRIS

This project is a C-based Trie (prefix tree) extension for [InterSystems IRIS](https://www.intersystems.com/products/intersystems-iris/), designed to perform fast prefix-based string lookups. It allows efficient searching of keys based on their prefixes — ideal for autocomplete systems, prefix matching, and command parsing.

## 🚀 Features

- Fast and efficient prefix lookup using Trie data structure.
- Seamless integration with InterSystems IRIS via its native extension interface.
- Written in pure C for performance-critical applications.

## 📦 Installation

### Prerequisites

- InterSystems IRIS installed
- gcc or compatible C compiler
- IRIS development environment setup

### Build Instructions

1. Clone the repository:

    ```bash
    git clone https://github.com/kunal0297/iris-c-trie.git
    cd iris-c-trie
    ```

2. Compile the extension (update the paths to match your IRIS install if needed):

    ```bash
    gcc -fPIC -shared -o trie.so trie.c
    ```

3. Load the extension into IRIS:

    ```objectscript
    SET status = $ZF(-3, "trie.so")
    ```

🧪 Testing
Coming soon — test scripts to verify lookup speed and correctness.

📝 License
This project is licensed under the MIT License. See the LICENSE file for details.

🌐 Published On
This extension is officially published on the InterSystems Open Exchange.

➡️ App Listing Page

👤 Author
Kunal Pandey
GitHub: @kunal0297
## 🛠️ Usage Example (ObjectScript)
```objectscript
; Example usage of the prefix lookup extension
; Assuming the functions are exposed via $ZF or class methods
SET status = ##class(User.Trie).Init()
DO ##class(User.Trie).Insert("apple")
DO ##class(User.Trie).Insert("application")
DO ##class(User.Trie).Insert("banana")

WRITE ##class(User.Trie).SearchPrefix("app")  ; returns "apple", "application"
