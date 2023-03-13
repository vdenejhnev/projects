#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left, *right;
};
//1
int create(char*, int);  // ������� �������� ���� �� ������������������� �����
//2, 4
char* createName(char*);  // ������� ��� ���������� �����
void createT(char*, char*);  // ������������ �������� ���� � ���������
//3
void sort_file(char*);  // ��������� �������� ���� � ������� ��������� �� �����
FILE* sort_sequence(FILE* fp);  // ���������� ����� ������������������ � �����
FILE* print(FILE*, struct node *);  // ������ ������ � ���� � �� �����
struct node* add(struct node*, int);  // ���������� �������� � ������
void clear(struct node*);  // ������������ ������

int main(int argc, char** argv) {
    if (argc > 1) {  // �������� �� ���������� ����� ����� � ��������� ������
        int N;
        char* name, * nameT;
        name = argv[1];
        nameT = createName(name);  // �������� ���� ��� ��������� � ��������� ������

        if (scanf("%d", &N) == 1 && N >= 0 && create(name, N)) {  // �������� ���������� ������������������� �� ������������ � �������� ��������� �����
            createT(name, nameT);  // �������� ���������� �����
            sort_file(name);  // ���������� ��������� ����� � ����� ��������������� ������������������� �� �����
            createT(name, nameT);  // �������� ���������� ����� �� ��������������� �������������������
        } else {
            fprintf(stderr, "Incorrect input data\n");  // ����� ������ � ������ ���� ����� ������������������ ������� �������
        }
        free(nameT);  // �������� ������ ��� ����� ���������� �����
    } else {
        fprintf(stderr, "file name not specified\n");  // ����� ������ � ������, ���� ��� ����� �� �������
    }
}

int create(char* name, int N) {  // �������� ��������� �����. ���������� 1, ���� ������ ������ �������, 0 - �����
    FILE* fp = fopen(name, "w");  // ������� � ��������� �������� ���� �� ������
    int i;
    for (i = 0; i < N; ++i) {  // ������� ��� �������������������
        int k, p;

        while ((p = scanf("%d", &k)) == 1 && k)  // �������� �� ������������ �������� ������ � �������� �� ����� �����
            fwrite(&k, sizeof(int), 1, fp);  // ������ ����� � �������� ����

        if (p != 1 && i != N - 1) { // ��������� ������ ��������� ����� �� �����, ���� p != 1, �� ����� ��������� ������ ��� ��� ��������� ����� �����, � ���� ��� ���������, ���� ���� ������� �� �����
            fclose(fp);
            fp = fopen(name, "w");  // ������� ���� �� ����������� ������, ��� ��� ��������� �����������
            return 0;
        } else {
            if (i != N - 1 || !k)
                fwrite(&k, sizeof(int), 1, fp);  // ���� ���������� ��������� ���������, �� ��������� 0 � �������� ���� � ��������� � ��������� ������������������
        }
    }
    fclose(fp);  // ��������� ����
    return 1;
}

char* createName(char* name) {  // �������� ����� ��� ���������� �����
    char* s = name, *nameT;
    int n = 0;  // ������� �������� � ����� �����
    while (*s) {
        n++;
        s++;
    }
    n += 2;  // �������� ��� ������ ����� � ������ ������������ ������� 'T' � '\0'
    nameT = malloc(sizeof(char) * n);  // ��������� ������ ��� ����� ������
    s = nameT;
    while (*name) {  // ����������� ����� ��������� ����� � ��� ����������
        *nameT = *name;
        nameT++;
        name++;
    }
    *nameT = 'T';  // ���������� ������� 'T' � ��� ���������� �����
    nameT++;
    *nameT = '\0';  // � ��������� ����� ������
    return s;
}

void createT(char* name, char* nameT) {  // ������������ ���������� ����� �� ���������
    FILE* fp = fopen(name, "r");  // ��������� �������� ���� �� ������
    if (fp) {  // �������� �� ������������� �����
        FILE* fpT = fopen(nameT, "w");  // ������� � ��������� ��������� ���� �� ������
        int k;

        while (fread(&k, sizeof(int), 1, fp)) {  // ���� ���� ��� ������� �� ��������� ����� ����� ���������
            if (k)  // ���� k �� 0
                fprintf(fpT, "%d ", k);  // ���������� k � ��������� ����
            else
                fprintf(fpT, "%d\n", k); // ����� ���������� 0 � ������ ������� ������
        }
        fclose(fp);
        fclose(fpT);
    } else {
        fprintf(stderr, "no file \'%s\'\n", name);
    }
}

void sort_file(char * name) {  // ���������� ������������������� � �������� �����
    FILE *fp = fopen(name, "r+");  // ��������� �������� ���� �� ������
    if (fp) {  // �������� �� ������������� �����
        long p;
        fseek(fp, 0, SEEK_END);
        p = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        while (p - 1 > ftell(fp))
            fp = sort_sequence(fp);  // ��������� ������ ������������������, ������� ������ �������� ��������� �� ��������� ������������������
        fclose(fp);  // ��������� �������� ����
    } else {
        fprintf(stderr, "no file \'%s\'\n", name);
    }
}

FILE* sort_sequence(FILE* fp) {  // ���������� ����� ������������������ ��������� ����� � ������� ��������� �� ���� ������������������
    struct node* tree = NULL;  // ������� ������ ������
    int n = 1, k;  // n - ���������� ����� � ������������������, k - �������� ������ �� ��������� �����

    while (fread(&k, sizeof(int), 1, fp) && k) {  // ���� ���� ������ �� ����� � k �� ����� ���� (�� ��������� ����� ������������������)
        tree = add(tree, k);  // ��������� � ������ ����� k
        n++;  // ����������� ���������� ����� � ������������������, ����� ����� ���������� �� ������ ����������������� ��� �� ���������� � ��������������� ����
    }

    if (feof(fp))  // �������� �� ��������� ������������������, ���� ��� �� �������� 0 �� �����
        n -= 1;  // �� ����� ���������� �� n - 1

    fseek(fp, -sizeof(int) * n, SEEK_CUR);  // ��������� �� ������ ������������������
    fp = print(fp, tree);  // ���������� ���� ������, �������� ��������� ����� ������������������ (�� 0)
    printf("\n");
    fseek(fp, sizeof(int), SEEK_CUR); // ��������� ��� �� ���� ������� ����� fp �������� �� ��������� ������������������
    clear(tree);  // ����������� ������ ��� ���������� ������
    return fp;
}

FILE* print(FILE* fp, struct node *tree) {  // ������ ������ � ���� � �� �����. ������� ���������� ��������� �� ����� ������������������ (�� 0)
    if (tree) {  // ���� ������ ���������
        if (tree->left)  // �������� ������� ����� ���������
            fp = print(fp, tree->left);
        printf("%d ", tree->data);  // ������� �� ������� ��������� ������
        fwrite(&(tree->data), sizeof(int), 1, fp);
        if (tree->right)  // �������� ������ ���������
            fp = print(fp, tree->right);
    }
    return fp;
}

struct node* add(struct node* tree, int k) {  // ���������� �������� � ������, ���������� ��������� �� ���������� ������
    if (tree) {  // ���� ������ �� �����
        if (k >= tree->data)
            tree->right = add(tree->right, k);  // ��������� � ������ ���������, ���� k ������ �����
        else
            tree->left = add(tree->left, k);  // ��������� � ����� ���������, ���� k ������ �����
    } else {
        tree = malloc(sizeof(struct node));  // � ������ ������� ������ ������� ���
        tree->data = k;
        tree->left = NULL;
        tree->right = NULL;
    }
    return tree;
}

void clear(struct node* tree) {  // ������������ ������
    if (tree) {
        clear(tree->left);  // ������������ ������ ���������
        clear(tree->right);  // ������������ ������� ���������
        free(tree);  // ������������ �����
    }
}
