#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

struct Node {
    int data;
    struct Node *next;
};

typedef struct Node node;

node *createNode(int data) {
    node *temp = (node *) malloc(sizeof(node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}
void Part3_SelectionSort(node **head) {
    node  *min, *prev_min, *temp;
    node  *curr = *head;
    while (curr != NULL) {
        min = curr;
        prev_min = NULL;

        node *next = curr->next;
        node *prev_next = curr;
        while (next != NULL) {
            if (next->data < min->data) {
                min = next;
                prev_min = prev_next;
            }
            prev_next = next;
            next = next->next;
        }
        if (min != curr) {
            if (prev_min != NULL) {
                prev_min->next = min->next;
            }
            temp = min->next;
            min->next = curr->next;
            curr->next = temp;
        }
        curr = curr->next;
    }
    printf("Selection sort completed successfully!\n");
}

void Part2_DeleteNegatives(node **head) {
    node *current = *head;
    node *prev = NULL;

    while (current != NULL) {
        if (current->data < 0) {
            if (prev == NULL) {
                *head = current->next; //если первый то меняем голову
            }
            else {
                prev->next = current->next; // вдругом случае обновляем ущзлы
            }
            node *temp = current; // для удаления
            current = current->next;
            free(temp);
        }
        else {
            prev = current; //если не отрицательный то обновляем предыдущий и продолжаем
            current = current->next;
        }
    }
    printf("All negatives numbers deleted!\n");
}


void FullEnter_Part1(node **head) {
    char InputFileName[MAX_LENGTH];
    char InputFile_path[MAX_LENGTH] = "/home/layk1i/Рабочий стол/";
    char OutputFileName[MAX_LENGTH];
    char OutputFile_path[MAX_LENGTH] = "/home/layk1i/Рабочий стол/";

    printf("Enter input filename:\n");
    scanf("%s", InputFileName);
    strcat(InputFile_path, InputFileName);
    strcat(InputFile_path, ".txt");

    FILE *fi = fopen(InputFile_path, "w");
    if (fi == NULL) {
        printf("File cannot be opened\n");
        return;
    }

    printf("Enter the integers nums to file you want:\n");
    printf("To stop enter 'q':\n");
    while (true) {
        char input[MAX_LENGTH];
        scanf("%s", input);
        if (strcmp(input, "q") == 0) {
            break;
        }
        int num = atoi(input);
        fprintf(fi, "%d\n", num);
    }
    fclose(fi);


    fi = fopen(InputFile_path, "r");
    if (fi == NULL) {
        printf("File cannot be opened\n");
        return;
    }


    int num;
    while (fscanf(fi, "%d", &num) != EOF) {
        node *newnode = createNode(num); //queue
        if (*head == NULL) {
            *head = newnode;
        } else {
            node *temp = *head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newnode;
        }
    }
    fclose(fi);

    printf("Part 2. Delete all negative numbers: \n");
    Part2_DeleteNegatives(head);

    printf("Part 3. Selection sort: \n");
    Part3_SelectionSort(head);

    printf("Enter output filename:\n");
    scanf("%s", OutputFileName);
    strcat(OutputFile_path, OutputFileName);
    strcat(OutputFile_path, ".txt");


    FILE *fo = fopen(OutputFile_path, "w");
    if (fo == NULL) {
        printf("File cannot be created\n");
        return;
    }
    node *temp = *head;
    while (temp != NULL) {
        fprintf(fo, "%d\n", temp->data); //
        temp = temp->next;
    }
    fclose(fo);
}

int main() {
    node *head = NULL;
    FullEnter_Part1(&head);
    return 0;
}
