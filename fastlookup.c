#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 36
#define MAX_WORD_LENGTH 100

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    int is_end_of_word;
} TrieNode;

static TrieNode* global_root = NULL;

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

int char_to_index(char c) {
    if (isdigit(c)) return c - '0' + 26;
    if (isalpha(c)) return tolower(c) - 'a';
    return -1;
}

void insert(TrieNode* root, const char* word) {
    TrieNode* current = root;
    while (*word) {
        int index = char_to_index(*word);
        if (index == -1) return;
        if (!current->children[index])
            current->children[index] = create_node();
        current = current->children[index];
        word++;
    }
    current->is_end_of_word = 1;
}

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

void find_words_with_prefix(TrieNode* root, char* buffer, int depth, FILE* out) {
    if (root->is_end_of_word) {
        buffer[depth] = '\0';
        fprintf(out, "%s\n", buffer);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            buffer[depth] = (i < 26) ? ('a' + i) : ('0' + (i - 26));
            find_words_with_prefix(root->children[i], buffer, depth + 1, out);
        }
    }
}

void free_trie(TrieNode* root) {
    if (!root) return;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        free_trie(root->children[i]);
    free(root);
}

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

__attribute__((visibility("default")))
void free_trie_memory() {
    if (global_root) {
        free_trie(global_root);
        global_root = NULL;
    }
}

///////////////////////
// ZF Integration
///////////////////////

typedef int (*ZFFUNC)(int argc, char *argv[], char *result, int maxlen);

typedef struct {
    char *name;
    ZFFUNC func;
} ZFTABLE;

// Function to insert a word
int zf_insert_word(int argc, char *argv[], char *result, int maxlen) {
    initialize_trie();
    if (argc < 1) {
        strncpy(result, "ERR: Missing word", maxlen - 1);
        result[maxlen - 1] = '\0';
        return 1;
    }
    insert(global_root, argv[0]);
    snprintf(result, maxlen, "Inserted: %s", argv[0]);
    return 0;
}

// Function to search a prefix
int zf_search_prefix(int argc, char *argv[], char *result, int maxlen) {
    initialize_trie();
    if (argc < 1) {
        strncpy(result, "ERR: Missing prefix", maxlen - 1);
        result[maxlen - 1] = '\0';
        return 1;
    }

    TrieNode* current = global_root;
    char buffer[MAX_WORD_LENGTH];
    int depth = 0;
    const char *prefix = argv[0];

    while (*prefix) {
        int index = char_to_index(*prefix);
        if (index == -1 || !current->children[index]) {
            snprintf(result, maxlen, "No match for prefix: %s", argv[0]);
            return 0;
        }
        buffer[depth++] = *prefix;
        current = current->children[index];
        prefix++;
    }

    FILE* temp = tmpfile();
    if (!temp) {
        strncpy(result, "ERR: Temp file error", maxlen - 1);
        result[maxlen - 1] = '\0';
        return 1;
    }

    find_words_with_prefix(current, buffer, depth, temp);
    rewind(temp);
    if (!fgets(result, maxlen, temp)) {
        strncpy(result, "No matches found", maxlen - 1);
        result[maxlen - 1] = '\0';
    } else {
        result[strcspn(result, "\n")] = '\0'; // Remove newline
    }
    fclose(temp);
    return 0;
}

ZFTABLE zfTable[] = {
    { "insert", zf_insert_word },
    { "search", zf_search_prefix },
    { NULL, NULL }
};

__attribute__((visibility("default")))
ZFTABLE* GetZFTable() {
    return zfTable;
}
