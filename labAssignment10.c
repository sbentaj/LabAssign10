#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Trie node definition
struct Trie {
    struct Trie* children[ALPHABET_SIZE];
    int count;
};

// Initialize a new trie node
struct Trie* newTrieNode() {
    struct Trie* trieNode = (struct Trie*)malloc(sizeof(struct Trie));
    trieNode->count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        trieNode->children[i] = NULL;
    }
    return trieNode;
}

// Insert a new word into the trie
void insert(struct Trie** ppTrie, char* word) {
    struct Trie* trieNode = *ppTrie;
    if (trieNode == NULL) {
        trieNode = newTrieNode();
        *ppTrie = trieNode;
    }
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        char c = tolower(word[i]);
        if (c >= 'a' && c <= 'z') {
            if (trieNode->children[c - 'a'] == NULL) {
                trieNode->children[c - 'a'] = newTrieNode();
            }
            trieNode = trieNode->children[c - 'a'];
        }
    }
    trieNode->count++;
}

// Count the number of occurrences of a word in the trie
int numberOfOccurrences(struct Trie* pTrie, char* word) {
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        char c = tolower(word[i]);
        if (c >= 'a' && c <= 'z') {
            if (pTrie->children[c - 'a'] == NULL) {
                return 0;
            }
            pTrie = pTrie->children[c - 'a'];
        }
    }
    return pTrie->count;
}

// Deallocate the trie data structure
struct Trie* deallocateTrie(struct Trie* pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

int main(void) {
    // Initialize the trie
    struct Trie* trie = NULL;
    
    // Read the number of words in the dictionary
    int n;
    scanf("%d", &n);
    
    // Parse each word and insert into the trie
    char word[100];
    for (int i = 0; i < n; i++) {
        scanf("%s", word);
        insert(&trie, word);
    }

    // Check the number of occurrences of each word
    char* pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("%s : %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }

    // Deallocate the trie
    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}

