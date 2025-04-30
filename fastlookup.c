#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 36 // 26 letters + 10 digits

// Trie Node Structure
typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    int is_end_of_word;
} TrieNode;

// Create a new Trie Node
TrieNode* create_node() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->is_end_of_word = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

// Free the Trie
void free_trie(TrieNode* root) {
    if (root) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            free_trie(root->children[i]);
        }
        free(root);
    }
}

// Normalize character to index
int char_to_index(char c) {
    if (isdigit(c)) {
        return c - '0' + 26; // Map '0'-'9' to indices 26-35
    } else if (isalpha(c)) {
        return tolower(c) - 'a'; // Map 'a'-'z' to indices 0-25
    }
    return -1; // Invalid character
}

// Insert a word into the Trie
void insert(TrieNode* root, const char* word) {
    TrieNode* current = root;
    while (*word) {
        int index = char_to_index(*word);
        if (index == -1) return; // Ignore invalid characters
        if (!current->children[index])
            current->children[index] = create_node();
        current = current->children[index];
        word++;
    }
    current->is_end_of_word = 1;
}

// Search for a prefix
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

// Retrieve all words with a given prefix
void find_words_with_prefix(TrieNode* root, char* buffer, int depth) {
    if (root->is_end_of_word) {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            buffer[depth] = (i < 26) ? (i + 'a') : (i - 26 + '0'); // Map back to char
            find_words_with_prefix(root->children[i], buffer, depth + 1);
        }
    }
}

// Exported function for IRIS
__attribute__((visibility("default")))
int lookup_prefix(const char* prefix) {
    static TrieNode* root = NULL;
    if (!root) {
        root = create_node();
        // Example words to insert into the Trie
        insert(root, "diabetes");
        insert(root, "diagnosis");
        insert(root, "dialysis");
        insert(root, "data");
        insert(root, "dare");
        insert(root, "daredevil");
        insert(root, "daring");
        insert(root, "daringly");
    }
    return search(root, prefix);
}

// Function to find and print all words with a given prefix
__attribute__((visibility("default")))
void print_words_with_prefix(const char* prefix) {
    static TrieNode* root = NULL;
    if (!root) {
        root = create_node();
        // Example words to insert into the Trie
        insert(root, "diabetes");
        insert(root, "diagnosis");
        insert(root, "dialysis");
        insert(root, "data");
        insert(root, "dare");
        insert(root, "daredevil");
        insert(root, "daring");
        insert(root, "daringly");
    }

    TrieNode* current = root;
    char buffer[100]; // Buffer to hold words
    int depth = 0;

    // Traverse the Trie to find the prefix
    while (*prefix) {
        int index = char_to_index(*prefix);
        if (index == -1 || !current->children[index]) {
            printf("No words found with prefix '%s'\n", prefix);
            return;
        }
        buffer[depth++] = (index
