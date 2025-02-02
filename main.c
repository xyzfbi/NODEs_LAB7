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

    node* createNode(int data) {
        node* temp = (node*)malloc(sizeof(node));
        temp->data = data;
        temp->next = NULL;
        return temp;
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
            node *newnode = createNode(num);
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
            fprintf(fo, "%d\n", temp->data);
            temp = temp->next;
        }
        fclose(fo);
    }

    int main() {
        node *head = NULL;
        FullEnter_Part1(&head);
        return 0;
    }