#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 36 // 26 letters + 10 digits
#define MAX_WORD_LENGTH 100

// Trie Node Structure
typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    int is_end_of_word;
} TrieNode;

// Create a new Trie Node
TrieNode* create_node() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->is_end_of_word = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

// Map character to index: a-z → 0-25, 0-9 → 26-35
int char_to_index(char c) {
    if (isdigit(c)) return c - '0' + 26;
    if (isalpha(c)) return tolower(c) - 'a';
    return -1;
}

// Insert word into Trie
void insert(TrieNode* root, const char* word) {
    TrieNode* current = root;
    while (*word) {
        int index = char_to_index(*word);
        if (index == -1) return; // skip invalid characters
        if (!current->children[index])
            current->children[index] = create_node();
        current = current->children[index];
        word++;
    }
    current->is_end_of_word = 1;
}

// Search prefix in Trie
int search(TrieNode* root, const char* prefix) {
    TrieNode* current = root;
    while (*prefix) {
        int index = char_to_index(*prefix);
        if (index == -1 || !current->children[index]) return 0;
        current = current->children[index];
        prefix++;
    }
    return 1;
}

// Recursively find and print all words with a given prefix
void find_words_with_prefix(TrieNode* root, char* buffer, int depth) {
    if (root->is_end_of_word) {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            buffer[depth] = (i < 26) ? ('a' + i) : ('0' + (i - 26));
            find_words_with_prefix(root->children[i], buffer, depth + 1);
        }
    }
}

// Free the Trie
void free_trie(TrieNode* root) {
    if (!root) return;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        free_trie(root->children[i]);
    free(root);
}

// Global root pointer (for simplicity in integration)
static TrieNode* global_root = NULL;

// Initialize Trie (once)
void initialize_trie() {
    if (!global_root) {
        global_root = create_node();
        insert(global_root, "diabetes");
        insert(global_root, "diagnosis");
        insert(global_root, "dialysis");
        insert(global_root, "data");
        insert(global_root, "dare");
        insert(global_root, "daredevil");
        insert(global_root, "daring");
        insert(global_root, "daringly");
        insert(global_root, "dark");
        insert(global_root, "dashboard");
        insert(global_root, "developer");
    }
}

// Exported function to search prefix (1 = found, 0 = not found)
__attribute__((visibility("default")))
int lookup_prefix(const char* prefix) {
    initialize_trie();
    return search(global_root, prefix);
}

// Exported function to print all words with a prefix
__attribute__((visibility("default")))
void print_words_with_prefix(const char* prefix) {
    initialize_trie();
    TrieNode* current = global_root;
    char buffer[MAX_WORD_LENGTH];
    int depth = 0;

    while (*prefix) {
        int index = char_to_index(*prefix);
        if (index == -1 || !current->children[index]) {
            printf("No words found with prefix '%s'\n", prefix);
            return;
        }
        buffer[depth++] = *prefix;
        current = current->children[index];
        prefix++;
    }

    find_words_with_prefix(current, buffer, depth);
}

// Cleanup function (optional call when shutting down)
__attribute__((visibility("default")))
void free_trie_memory() {
    if (global_root) {
        free_trie(global_root);
        global_root = NULL;
    }
}
