// Mohammed Yousef Salem - 1203022 - Section 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10007 // A prime number for better distribution

// AVL Tree Node
typedef struct AVLnode {
    char* word;
    int frequency;
    struct AVLnode* left;
    struct AVLnode* right;
    int height;
} *AVLNode;

// Hash Table Node
typedef struct HashNode {
    char* word;
    int frequency;
    struct HashNode* next;
} *HashNode;

HashNode hashTable[TABLE_SIZE];

// Function prototypes
void menu();
int height(AVLNode N);
int max(int a, int b);
AVLNode newNode(char* word);
AVLNode rightRotate(AVLNode y);
AVLNode leftRotate(AVLNode x);
int getBalance(AVLNode N);
AVLNode insertAVL(AVLNode node, char* word);
AVLNode minValueNode(AVLNode node);
AVLNode deleteNode(AVLNode root, char* word);
void printInOrder(AVLNode root);
int hash(const char* word);
HashNode newHashNode(char* word, int freq);
void insertHashTable(char *word);
int getFrequency(char* word);
void deleteWordFromHashTable(char* word);
void readFileAndBuildTree(const char* filename, AVLNode* root) ;
void insertAVLToHashTable(AVLNode root);
void printWordStatistics();
void freeAVL(AVLNode root);
void freeHashTable();





// Main function with menu system
int main() {
    int choice;
    char word[256];
    AVLNode root = NULL;

    do {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                readFileAndBuildTree("C:\\Users\\Tech Zone\\CLionProjects\\ProjectThree\\data.txt", &root);
                break;
            case 2:
                printf("AVL Tree already created from loaded data.\n");
                break;
            case 3:
                printf("Enter a word to insert into the AVL Tree: ");
                scanf("%s", word);
                root = insertAVL(root, word);
                printf("Word '%s' inserted.\n", word);
                break;
            case 4:
                printf("Enter a word to delete from the AVL Tree: ");
                scanf("%s", word);
                root = deleteNode(root, word);
                printf("Word '%s' deleted if it existed.\n", word);
                break;
            case 5:
                printf("Words in AVL Tree (In-order):\n");
                printInOrder(root);
                break;
            case 6:
                printf("Creating Hash Table from AVL Tree...\n");
                insertAVLToHashTable(root);
                printf("Hash Table created.\n");
                break;
            case 7:
                printf("Enter a word to insert into the Hash Table: ");
                scanf("%s", word);
                insertHashTable(word);
                printf("Word '%s' inserted .\n", word);
                break;
            case 8:
                printf("Enter a word to delete from the Hash Table: ");
                scanf("%s", word);
                deleteWordFromHashTable(word);
                printf("Word '%s' deleted if it existed.\n", word);
                break;
            case 9:
                printf("Enter a word to search in the Hash Table: ");
                scanf("%s", word);
                int freq = getFrequency(word);
                printf("Frequency of '%s': %d\n", word, freq);
                break;
            case 10:
                printWordStatistics();
                break;
            case 11:
                printf("Exiting the application.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 11);

    freeAVL(root);
    freeHashTable();
    return 0;
}


void menu() {
    printf("\nMenu\n");
    printf("1. Load data from the file.\n");
    printf("2. Create the AVL tree.\n");
    printf("3. Insert a word to the AVL tree.\n");
    printf("4. Delete a word from the AVL tree.\n");
    printf("5. Print the words as sorted in the AVL tree.\n");
    printf("6. Create the Hash Table.\n");
    printf("7. Insert a word to the Hash table.\n");
    printf("8. Delete a word from the hash table.\n");
    printf("9. Search for a word in the hash table and print its frequency.\n");
    printf("10. Print words statistics.\n");
    printf("11. Exit the application.\n");
}


// Utility function to get the height of the tree
int height(AVLNode N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}


//  function to create a new node
AVLNode newNode(char* word) {
    AVLNode node = (AVLNode) malloc(sizeof(struct AVLnode));
    node->word = strdup(word); // Duplicate the word for storage
    node->frequency = 1;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // New node is initially added at leaf
    return node;
}

// utility function to right rotate subtree rooted with y
AVLNode rightRotate(AVLNode y) {
    AVLNode x = y->left;
    AVLNode T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// utility function to left rotate subtree rooted with x
AVLNode leftRotate(AVLNode x) {
    AVLNode y = x->right;
    AVLNode T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(AVLNode N) {
    if (N == NULL)
        return 0;
    return
        height(N->left) - height(N->right);
}

// Recursive function to insert a word in the subtree rooted
// with node and updates the height of the ancestor nodes
AVLNode insertAVL(AVLNode node, char* word) {
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(word));

    if (strcmp(word, node->word) < 0)
        node->left  = insertAVL(node->left, word);
    else if (strcmp(word, node->word) > 0)
        node->right = insertAVL(node->right, word);
    else { // Duplicate word found, increase frequency
        (node->frequency)++;
        return node;
    }

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), height(node->right));

    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && strcmp(word, node->left->word) < 0)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && strcmp(word, node->right->word) > 0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && strcmp(word, node->left->word) > 0) {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && strcmp(word, node->right->word) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

// Utility function to get the minimum value node of the subtree rooted at given node
AVLNode minValueNode(AVLNode node) {
    AVLNode current = node;
    // Loop to find the leftmost leaf
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Recursive function to delete a node with given word from subtree with given root.
// It returns root of the modified subtree.
AVLNode deleteNode(AVLNode root, char* word) {
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;

    // If the word to be deleted is smaller than the root's word, then it lies in left subtree
    if (strcmp(word, root->word) < 0)
        root->left = deleteNode(root->left, word);

        // If the word to be deleted is greater than the root's word, then it lies in right subtree
    else if(strcmp(word, root->word) > 0)
        root->right = deleteNode(root->right, word);

        // If this is the word to be deleted
    else {
        // node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else // One child case
                *root = *temp; // Copy the contents of the non-empty child
            free(temp);
        }
        else {
            // node with two children: Get the inorder successor (smallest in the right subtree)
            AVLNode temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->word = strdup(temp->word);
            root->frequency = temp->frequency;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->word);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left), height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// A utility function to do inorder traversal of the tree
void printInOrder(AVLNode root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%s (%d)\n", root->word, root->frequency);
        printInOrder(root->right);
    }
}

// Function to create a new hash node
HashNode newHashNode(char* word, int freq) {
    HashNode node = (HashNode) malloc(sizeof(struct HashNode));
    node->word = strdup(word); // Duplicate the word for storage
    node->frequency = freq;
    node->next = NULL;
    return node;
}

// Hash function to calculate hash index
int hash(const char* word) {
    long hash = 5381;
    int c;

    while (c = *word++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % TABLE_SIZE;
}


// Function to insert a node into the hash table
void insertHashTable(char* word) {
    int index = hash(word);
    HashNode current = hashTable[index];

    // Check if the word already exists in the hash table
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            // Word found, increment the frequency
            current->frequency++;
            return;
        }
        current = current->next;
    }

    // Word not found, insert as a new node
    HashNode node = newHashNode(word, 1);
    node->next = hashTable[index];
    hashTable[index] = node;
}


// Function to get frequency of a word from the hash table
int getFrequency(char* word) {
    int index = hash(word);
    HashNode current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->word, word) == 0)
            return current->frequency;
        current = current->next;
    }
    return 0; // Word not found
}


void readFileAndBuildTree(const char* filename, AVLNode* root) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("File could not be opened.\n");
        return;
    }

    char buffer[256];
    while (fscanf(file, "%s", buffer) == 1) {
        char* word = strtok(buffer, " ,.!?\n\r\t");
        while (word != NULL) {
            // Convert word to lowercase manually without using tolower
            for (int i = 0; word[i] != '\0'; i++) {
                if (word[i] >= 'A' && word[i] <= 'Z') {
                    word[i] = word[i] +32;
                }
            }
            *root = insertAVL(*root, word);
            word = strtok(NULL, " ,.!?\n\r\t");
        }
    }
    fclose(file);
}




// Function to insert the words from the AVL tree into the hash table
void insertAVLToHashTable(AVLNode root) {
    if (root != NULL) {
        insertAVLToHashTable(root->left);
        for (int i = 0; i < root->frequency; i++) {
            insertHashTable(root->word);
        }
        insertAVLToHashTable(root->right);
    }
}


// Function to delete a word from the hash table
void deleteWordFromHashTable(char* word) {
    int index = hash(word);
    HashNode current = hashTable[index], prev = NULL;
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            if (prev == NULL) {
                hashTable[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->word);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Function to print word statistics from the hash table
void printWordStatistics() {
    int totalWords = 0;
    char* mostFrequentWord = NULL;
    int highestFrequency = 0;

    printf("Word Count Statistics:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode temp = hashTable[i];
        while (temp != NULL) {
            totalWords++;
            if (temp->frequency > highestFrequency) {
                highestFrequency = temp->frequency;
                mostFrequentWord = temp->word;
            }
            printf("%s (%d)\n", temp->word, temp->frequency);
            temp = temp->next;
        }
    }

    printf("\nTotal number of  words: %d\n", totalWords);
    if (mostFrequentWord != NULL) {
        printf("Most frequent word: %s (%d)\n", mostFrequentWord, highestFrequency);
    }
}


// Function to free AVL Tree
void freeAVL(AVLNode root) {
    if (root != NULL) {
        freeAVL(root->left);
        freeAVL(root->right);
        free(root->word);
        free(root);
    }
}

// Function to free hash table
void freeHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode current = hashTable[i];
        while (current != NULL) {
            HashNode temp = current;
            current = current->next;
            free(temp->word);
            free(temp);
        }
    }
}


