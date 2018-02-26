#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NAME_SIZE	256

// structure for one node in the linked list
typedef struct node_struct {
	int age;
	char name[NAME_SIZE];
	struct node_struct *next;
} Node;

// enumerated type for valid operations
typedef enum operation_enum {
	NEW = 1, FIND, DISPLAY_ASC, DISPLAY_DESC, QUIT
} Operation;

//
// function prototypes for the functions the students need to create
//

void insert_node(Node **head_ptr, Node *node);
Node *find_node(Node *head, const int age);
void display_node(Node *node);
void display_list(Node *head, Operation op);

/*

*/
void insert_node(Node **head_ptr, Node *node) {
    Node *it = *head_ptr;
    if (it==NULL) {
        *head_ptr = node;
        return;
    }
    while(it->next!=NULL) {
        it = it->next;
    }
    it->next = node;
}

/*

*/
Node *find_node(Node *head, const int age) {
    Node *it = head;
    while(it!=NULL) {
        if (it->age==age) {
            return it;
        }
        it = it->next;
    }
    return NULL;
}

/*

*/
void display_node(Node *node) {
    printf("Name: %s\nAge: %d\n", node->name, node->age);
}

/*

*/
void display_list(Node *head, Operation op) {
    Node *it;
    const int MAX_AGE = 200;
    if (op==DISPLAY_ASC) {
        for (int i=0;i<=MAX_AGE;++i) {
            it = head;
            while(it!=NULL) {
                if (it->age==i) {
                    display_node(it);
                }
                it = it->next;
            }
        }
    }
    else {//DISPLAY_DESC
        for (int i=MAX_AGE;i>=0;--i) {
            it = head;
            while(it!=NULL) {
                if (it->age==i) {
                    display_node(it);
                }
                it = it->next;
            }
        }
    }

}


/*
 * Create a new node.  The "next" member is initialized to NULL, other members are
 * set according to the parameters.
 *
 * Parameters:
 *		in: age - the value to store in the age field of the node
 *		in: name - the name to store in the name field of the node
 *
 * Returns a pointer to a Node.  Node.next is intialized to NULL
 */
Node *new_node(const int age, const char *name)
{
	Node *new = (Node *)malloc(sizeof(Node));
	if (!new) {
		fprintf(stderr, "Unable to allocate memory for new node\n");
		return NULL;
	}

	new->age = age;
	strncpy(new->name, name, NAME_SIZE);
	new->next = NULL;
	return new;
}

/*
 * Get user input including an operation and data associated with that operation, if any.
 *
 * Parameters:
 * 		out: operation - the operation the user wants
 *		out: age if the operation was insert or find, else undefined
 *		out: name if the operation was insert or find, else undefined
 *
 * The name parameter must be a pointer to memory sufficiently large to hold NAME_SIZE
 * characters (including null character at the end).
 *
 * Returns: false if success, else true
 */
bool get_operation(Operation *operation, int *age, char *name)
{
	const char prompt[] = "Enter an option:\n\t1) Add node\n\t2) Find node\n\t3) display ascending\n\t4) display descending\n\t5) Quit\n-> ";
	char input[NAME_SIZE];

	bool invalid_operation = true;
	while (invalid_operation) {

		fprintf(stdout, prompt);

		// get the option number from the user's input
		int op;
		if (fgets(input, NAME_SIZE, stdin) && sscanf(input, "%d", &op) == 1) {
			*operation = op;
			switch(op) {
				case NEW:
					// Need both age and name
					fprintf(stdout, "Age: ");
					if (!fgets(input, NAME_SIZE, stdin) || sscanf(input, "%d", age) != 1) {
						fprintf(stdout, "Age must be an integer\n");
						break;
					}
					fprintf(stdout, "Name: ");
					if (!fgets(name, NAME_SIZE, stdin)) {
						fprintf(stderr, "Error reading name from stdin\n");
						break;
					}
                    name[strlen(name)-1] = '\0';
					invalid_operation = false;
					break;

				case FIND:
					// Only need age
					fprintf(stdout, "Age: ");
					if (!fgets(input, NAME_SIZE, stdin) || sscanf(input, "%d", age) != 1) {
						fprintf(stdout, "Age must be an integer\n");
						break;
					}
					invalid_operation = false;
					break;

				case DISPLAY_ASC:
				case DISPLAY_DESC:
					// no additional information needed
					invalid_operation = false;
					break;

				case QUIT:
					return true;

				default:
					fprintf(stdout, "Invalid option\n\n");
					break;
			} // end switch
		} else {
			fprintf(stdout, "Invalid option\n");
		}
	} // end while

	return false;
}

/*
 * Repeatedly prompt the user for an operation and perform the operation.
 *
 * Parameters: n/a
 *
 * Returns:
 *		0 on success, else 1
 */
int main(void)
{
	Node *head = NULL;		// pointer to the first node in the linked list
	Node *node;
	Operation op;
	int age;
	char name[NAME_SIZE];

	while (!get_operation(&op, &age, name)) {

		switch(op) {
			case NEW:
				// Create a new node and insert it into the list
				node = new_node(age, name);
				insert_node(&head, node);
				break;

			case FIND:
				// Display all nodes containing the specified age
				node = find_node(head, age);
				while(node && node->age == age) {
					display_node(node);
					node = node->next;
				}
				break;

			case DISPLAY_ASC:
			case DISPLAY_DESC:
				// Display the entire linked list in the specified order
				display_list(head, op);
				break;

			case QUIT:
				return 0;

			default: break;		// don't need, but here to avoid compiler warning
		} // end switch
	} // end while

	// if we get here, it's because there was an error reading input
	return 1;
}
