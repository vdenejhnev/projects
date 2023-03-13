#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

 struct data {
 	char id[9];
 	char name[255];
 	char author[255];
 	char year_publication[5];
 	int loaned;
 	char customer[255];
 	int num_loaned;
 };

struct LinearNode {
    struct data *element;
	struct LinearNode *next;
};

struct LinearNode *front = NULL;
struct LinearNode *last = NULL;


void addBook(); //1
void borrowBook(); //2
void returnBook(); //3
void deleteBook(); //4
void viewAllBooks(); //5
void viewSpecificBook(); //6
void renameBook();//7
void exitLibrary(); //8
void enterBookId(char* bookId);
void enterYearPublication(char *yearPublication);
char formatBookId(char id[9], char* bookId);
bool isEmpty();


int main() {
    char c;
    bool new_book = true;
    bool new_field = true;
    int state_book = 0;
    int item = 0;
    char str[255];
    FILE *fdata;
    struct LinearNode *aNode;
	struct data *book_data;

    if ((fdata = fopen("book.dat", "r")) == NULL) {
        printf("Database does not exist, add books");
    } else {
        while (c != EOF) {
            if (new_book) {
                book_data = (struct data *)malloc(sizeof(struct data));
                aNode = (struct LinearNode *)malloc(sizeof(struct LinearNode));
                new_book = false;
            }

            c = fgetc(fdata);

            if (c == '|') {
                switch (state_book) {
                    case 0:
                        for (int j = 0; j < 9; j++) {
                            book_data->id[j] = str[j];
                        }
                        break;
                    case 1:
                        for (int j = 0; j < 255; j++) {
                            book_data->name[j] = str[j];
                        }
                        break;
                    case 2:
                        for (int j = 0; j < 255; j++) {
                            book_data->author[j] = str[j];
                        }
                        break;
                    case 3:
                        for (int j = 0; j < 5; j++) {
                            book_data->year_publication[j] = str[j];
                        }
                        break;
                    case 4:
                        //sscanf(str[0], "%d", book_data->loaned);
                        printf("%s\n", str);
                        break;
                }

                for (int j = 0; j < 255; j++) {
                    str[j] = (char)NULL;
                }

                state_book++;
                item = 0;
            } else if (c == '\n') {
                sscanf("_", "%s", book_data->customer);
                book_data->loaned = 0;
                book_data->num_loaned = 0;

                if (aNode == NULL)
                    printf("Error - no space for the new node\n");
                else {
                    aNode->next = NULL;
                    aNode->element = book_data;
                    if (isEmpty()) {
                        front = aNode;
                        last = aNode;
                    }  else {
                        aNode->next = front;
                        front = aNode;
                    }
                }

                new_book = true;
                state_book = 0;
            } else if (c == EOF) {
                sscanf("_", "%s", book_data->customer);
                book_data->loaned = 0;
                book_data->num_loaned = 0;

                if (aNode == NULL)
                    printf("Error - no space for the new node\n");
                else {
                    aNode->next = NULL;
                    aNode->element = book_data;
                    if (isEmpty()) {
                        front = aNode;
                        last = aNode;
                    }  else {
                        aNode->next = front;
                        front = aNode;
                    }
                }
            } else {
                str[item] = c;
                item++;
            }
        }

        printf("Books uploaded successfully!\n");
    }
    viewAllBooks();
    addBook();
    //addBook();
    //addBook();
    viewAllBooks();
    renameBook();
    viewAllBooks();
    viewSpecificBook();
    borrowBook();
    viewAllBooks();
    returnBook();
    viewAllBooks();
    deleteBook();
    viewAllBooks();
    exitLibrary();
    return 0;
}

bool isEmpty() {
	if (front == NULL)
		return true;
	else
		return false;
}

char formatBookId(char id[9], char* bookId) {
    for (int i = 0; i < (sizeof(id) / sizeof(id[0])); i++) {
        if (i < 4) {
            bookId[i] = id[i];
        } else {
            bookId[i+1] = id[i];
        }
    }

    bookId[4] = '-';
    return bookId;
}

void enterBookId(char* bookId) {
    char id[9];
    bool correct_id = false;
    bool equal_id;
    struct LinearNode *current;
    struct data *book_data;

    while(!correct_id) {
        printf("\nEnter book id: ");
        gets(id);
        current = front;
        correct_id = true;
        for (int i = 0; i < 8; i++) {
            if ((int)id[i] < 48 || (int)id[i] > 57) {
                printf("Incorrect book id value\n");
                correct_id = false;
                break;
            }
        }

        while (correct_id && current != NULL) {
            book_data = current->element;

            equal_id = true;

            for (int i=0; i < 9; i++) {
                if (id[i] != book_data->id[i]) {
                    equal_id = false;
                    break;
                }
            }

            if (equal_id) {
                printf("Book with this id already exists\n");
                correct_id = false;
                break;
            }

            current=current->next;
        }
    }

    for(int i = 0; i < 9; i++) {
        bookId[i] = id[i];
    }
}

void enterYearPublication(char* yearPublication) {
    char year[5];
    int year_publication;
    bool correct_year = false;

    while(!correct_year) {
        printf("Enter book year publication: ");
        gets(year);
        correct_year = true;

        for (int i = 0; i < 4; i++) {
            if ((int)year[i] < 48 || (int)year[i] > 57) {
                printf("Incorrect book year publication value\n");
                correct_year = false;
                break;
            }
        }

        if (correct_year) {
            sscanf(year, "%d", &year_publication);

            if (year_publication > 2017) {
                printf("The publication year of the book cannot be older than 2017\n");
                correct_year = false;
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        yearPublication[i] = year[i];
    }
}

void addBook() {
	int i;
	char value;
	struct LinearNode *aNode;
	struct data *book_data;

	book_data = (struct data *)malloc(sizeof(struct data));

    aNode = (struct LinearNode *)malloc(sizeof(struct LinearNode));

    enterBookId(book_data->id);
    printf("Enter book name: ");
    gets(book_data->name);
    printf("Enter book author: ");
    gets(book_data->author);
    enterYearPublication(book_data->year_publication);
    sscanf("not_specified", "%s", book_data->customer);
    book_data->loaned = 0;
    book_data->num_loaned = 0;
    if (aNode == NULL)
        printf("Error - no space for the new node\n");
    else {
        aNode->next = NULL;
        aNode->element = book_data;
        if (isEmpty())
        {
            front = aNode;
            last = aNode;
        }
        else {
            aNode->next = front;
            front = aNode;
        }

        printf("\nBook added successfully!\n");
    }
}

void viewAllBooks() {
    int item_book = 1;
    char book_loaned[5];
    char bookId[10];
	struct LinearNode *current;
	struct data *book_data;

	if (isEmpty())
		printf("\nError - there are no books in the list\n");
	else {
        printf("N| ID | NAME |  AUTHOR | YEAR PUBLICATION | LOANED | CUSTOMER | NUMBER LOANED \n");
        current = front;
        while (current != NULL) {
            book_data = current->element;

            if (book_data->loaned == 0) {
                sscanf("free", "%s", book_loaned );
            } else {
                sscanf("loan", "%s", book_loaned );
            }

            formatBookId(book_data->id, &bookId);
            printf("%d| %s | %s |  %s | %s | %s | %s | %d \n", item_book, bookId, book_data->name, book_data->author, book_data->year_publication, book_loaned, book_data->customer, book_data->num_loaned);
            current=current->next;
            item_book++;
        }
    }
}

void viewSpecificBook() {
    char book_id[9];
    char book_loaned[5];
    char bookId[10];
    struct LinearNode *current;
	struct data *book_data;

	if (isEmpty()) {
		printf("\nError - there are no books in the list\n");
	} else {
	    printf("\nEnter book id:");
	    gets(book_id);

        current = front;
        while (current != NULL) {
            book_data = current->element;

            if (strcmp(book_data->id, book_id) == 0) {
                break;
            }

            current=current->next;
        }

        if (current == NULL) {
            printf("\nBook not find\n");
        } else {
            if (book_data->loaned == 0) {
                sscanf("free", "%s", book_loaned );
            } else {
                sscanf("loan", "%s", book_loaned );
            }

            formatBookId(book_data->id, &bookId);

            printf("%s | %s |  %s | %s | %s | %s | %d \n", bookId, book_data->name, book_data->author, book_data->year_publication, book_loaned, book_data->customer, book_data->num_loaned);
        }
	}
}

void deleteBook() {
	struct LinearNode *current, *previous;
	struct data *book_data;
	char book_id[9];

	if (isEmpty()) {
		printf("\nError - there are no nodes in the list\n");
	} else {
        printf("\nEnter book id:");
	    gets(book_id);

        current = previous = front;

        while (current != NULL) {
            book_data = current->element;

            if (strcmp(book_data->id, book_id) == 0) {
                previous = current;
                break;
            }
            current=current->next;
        }

        if (current == NULL) {
            printf("\nBook not find\n");
        } else {
            if (current == front) {
                front = front->next;
                free(current);
            } else if (current == last){
                last = previous;
                last->next=NULL;
                free(current);
            } else {
                previous->next=current->next;
                free(current);
            }

            printf("\nBook deleted successfully!\n");
        }
	}
}

void borrowBook() {
    struct LinearNode *current;
	struct data *book_data;
	char book_id[9];

	if (isEmpty()) {
		printf("\nError - there are no books in the list\n");
	} else {
	    printf("Enter book id: ");
	    gets(book_id);

        current = front;
        while (current != NULL) {
            book_data = current->element;

            if (strcmp(book_data->id, book_id) == 0) {
                break;
            }

            current=current->next;
        }

        if (current == NULL) {
            printf("\nBook not find\n");
        } else {
            printf("Enter book customer: ");
            gets(book_data->customer);
            book_data->loaned = 1;
            book_data->num_loaned = book_data->num_loaned + 1;
            printf("\nThe book was successfully taken!\n");
        }
	}
}

void returnBook() {
    struct LinearNode *current;
	struct data *book_data;
	char book_id[9];

	if (isEmpty()) {
		printf("\nError - there are no books in the list\n");
	} else {
	    printf("Enter book id: ");
	    gets(book_id);

        current = front;
        while (current != NULL) {
            book_data = current->element;

            if (strcmp(book_data->id, book_id) == 0) {
                break;
            }

            current=current->next;
        }

        if (current == NULL) {
            printf("\nBook not find\n");
        } else {
            sscanf("not_specified", "%s", book_data->customer);
            book_data->loaned = 0;
            printf("\nBook successfully returned!\n");
        }
	}
}

void renameBook(){
    struct LinearNode *current;
	struct data *book_data;
	char book_id[9];

	if (isEmpty()) {
		printf("\nError - there are no books in the list\n");
	} else {
	    printf("Enter book id: ");
	    gets(book_id);

        current = front;
        while (current != NULL) {
            book_data = current->element;

            if (strcmp(book_data->id, book_id) == 0) {
                break;
            }

            current=current->next;
        }

        if (current == NULL) {
            printf("\nBook not find\n");
        } else {
            printf("Enter a new book name : ");
            gets(book_data->name);
            printf("\nBook successfully renamed!\n");
        }
	}
}

void exitLibrary() {
    exit(0);
}
