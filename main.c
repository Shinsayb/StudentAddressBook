#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_DATA 100    //�ִ�100��
#define FILE_PATH "/home/iot/CLionProjects/project_adbook.c/student_data.txt"
#define AUTO_FILE_PATH "/home/iot/CLionProjects/project_adbook.c/autosave.txt"
//���������� �Է±�� ����, �����͸���Ʈ ����:��ü�� ������ ���, ���������Ϳ��� �Ż�����:�������������ؼ� ����, �Է¹��� ���������ͷ� �����͸���Ʈ���� �������������ֱ�,
//��ü ������ ���, �̸����� �˻�,  �������Է°��� ���������ƴ��� Ȯ��,
//�����ʿ�:

//�л� ����ü
typedef struct {
    int id;          //�й����� ����մϴ�.
    int grade;      //�г�
    char name[50];  //�̸�
    char cellP[20];  //��ȭ��ȣ
    char major[50]; //�а�

    int isUsed;     // 1�̸� ���簪 ��� �� 0�̸� ����������� ǥ��
} Student;

Student database[MAX_DATA];

void listData(int lang);
void sortDataByIDAsc();
void sortDataByIDDesc();
void insertData(int id, char* name, int grade, char* cellP, char* major, int lang);
void deleteData(int id, int lang);
void updateDataChar(int id, char ans, char* newData, int lang);
void updateDataInt(int id, char ans, int newData, int lang);
void updateData(int id, int lang);
void searchData(int id, int lang);
void saveData(int lang);
void loadData(int lang);
void programSetting(char ans, int* save, int* lang);
void clearConsole();

int main() {
    int id, grade, save, lang;
    char ans, choice;
    char name[50], cellP[20], major[50], path[100];

    //���� ���� �ҷ�����
    printf("1");
    FILE *fp = fopen("setting.txt", "r");
    printf("1");
    fscanf(fp, "%d, %d", &lang, &save);
    printf("2");
    fclose(fp);
    printf("3");

    while (1) {
        printf("4");
        if(lang == 2){
            printf("\n---- �޴� ----\n");
            printf("1. ������ ���\n");
            printf("2. ������ ����\n");
            printf("3. ������ ����\n");
            printf("4. ������ ����\n");
            printf("5. ������ �˻�\n");
            printf("7. ������ ����\n");
            printf("8. ������ �ҷ�����\n");
            printf("9. ���α׷� ����\n");
            printf("C. �ܼ� Ŭ����(WIP)\n");
            printf("Q. ����\n");
        } else{
            printf("\n---- Menu ----\n");
            printf("1. Data List\n");
            printf("2. Data Insert\n");
            printf("3. Data Edit\n");
            printf("4. Data Delete\n");
            printf("5. Data Search\n");
            printf("7. Data Save\n");
            printf("8. Data Load\n");
            printf("9. Program Setting\n");
            printf("C. Clear Console(WIP)\n");
            printf("Q. Exit\n");
        }
        printf("\n-> ");
        scanf("%c", &choice);
        getchar(); // ���ۿ� ���� ���� ���� ���� ��, �������� ȿ���� ���� ���

        switch (choice) {
            case '1':
                listData(lang);
                break;
            case '2':
                if(lang == 2){
                    printf("\n�߰��� ����� �й��� �Է����ּ���.\n");
                    printf("\n-> ");
                } else{
                    printf("\nEnter the ID to insert.\n");
                    printf("\n-> ");
                }
                scanf("%d", &id);
                getchar(); // ���ۿ� ���� ���� ���� ����
                if(lang == 2){
                    printf("\n�̸� : ");
                } else{
                    printf("Name : ");
                }
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // ���� ���� ����
                if(lang == 2){
                    printf("�г� : ");
                } else{
                    printf("Grade : ");
                }
                scanf("%d", &grade);
                getchar(); // ���ۿ� ���� ���� ���� ����
                if(lang == 2){
                    printf("��ȭ��ȣ : ");
                } else{
                    printf("Cellphone Number : ");
                }
                fgets(cellP, sizeof(cellP), stdin);
                cellP[strcspn(cellP, "\n")] = 0; // ���� ���� ����
                if(lang == 2){
                    printf("�а� : ");
                } else{
                    printf("Major : ");
                }
                fgets(major, sizeof(major), stdin);
                major[strcspn(major, "\n")] = 0; // ���� ���� ����
                insertData(id, name, grade, cellP, major, lang);
                break;
            case '3':
                if(lang == 2){
                    printf("\n������ ����� �й��� �Է����ּ���.\n");
                    printf("\n-> ");
                } else{
                    printf("\nEnter the ID to edit.\n");
                    printf("\n-> ");
                }
                scanf("%d", &id);
                getchar(); // ���ۿ� ���� ���� ���� ����
                updateData(id, lang);
                break;
            case '4':
                if(lang == 2){
                    printf("\n������ ����� �й��� �Է����ּ���.\n");
                    printf("\n-> ");
                } else{
                    printf("\nEnter the ID to delete.\n");
                    printf("\n-> ");
                }
                scanf("%d", &id);
                getchar(); // ���ۿ� ���� ���� ���� ����
                deleteData(id, lang);
                break;
            case '5':
                if(lang == 2){
                    printf("\n�˻��� ����� �й��� �Է����ּ���.\n");
                    printf("\n-> ");
                } else{
                    printf("\nEnter the ID to search.\n");
                    printf("\n-> ");
                }
                scanf("%d", &id);
                getchar(); // ���ۿ� ���� ���� ���� ����
                searchData(id, lang);
                break;
            case '7':
                if(lang == 2){
                    printf("\n�����͸� �����Ͻðڽ��ϱ�?\n");
                } else{
                    printf("\nDo you want to save the data?\n");
                }
                printf("\nY/N -> ");
                scanf("%c", &ans);
                getchar(); // ���ۿ� ���� ���� ���� ����
                if(ans == 'Y' || ans == 'y'){
                    saveData(lang);
                }
                break;
            case '8':
                if(lang == 2){
                    printf("\n�����͸� �ҷ����ðڽ��ϱ�?\n");
                    printf("�����͸� �ҷ����� ������� ���� �����ʹ� ������ϴ�.\n");
                    printf("�Ͻðڽ��ϱ�?\n");
                } else{
                    printf("\nDo you want to load the data?\n");
                    printf("Loading data will overwrite unsaved changes\n");
                    printf("Are you sure?\n");
                }
                printf("\nY/N -> ");
                scanf("%c", &ans);
                getchar(); // ���ۿ� ���� ���� ���� ����
                if(ans == 'Y' || ans == 'y'){
                    loadData(lang);
                }
                break;
            case '9':
                if(lang == 2) {
                    printf("\n---- ���α׷� ���� ----\n");
                    printf("1. ������ ���� ��� ����\n");
                    printf("2. ���(Language)\n");
                    printf("3. �ڵ�����\n");
                    printf("Q. �޴��� ���ư���\n");
                }
                else{
                    printf("\n---- Program Setting ----\n");
                    printf("1. Set data sorting method\n");
                    printf("2. Language\n");
                    printf("3. Auto Save\n");
                    printf("Q. Back to main menu\n");
                }

                printf("\n-> ");
                scanf("%c", &ans);
                getchar(); // ���ۿ� ���� ���� ���� ����
                programSetting(ans, &save, &lang);
                break;

            case 'c':
                if(lang == 2){
                    printf("\n�ܼ��� ����ðڽ��ϱ�?\n");
                }
                else{
                    printf("\nDo you want to clear the console?\n");
                }

                printf("\nY/N -> ");
                scanf("%c", &ans);
                getchar(); // ���ۿ� ���� ���� ���� ����
                if(ans == 'Y' || ans == 'y'){
                    clearConsole();
                }
                break;
            case 'q':
                if(lang == 2){
                    printf("\n���α׷��� �����մϴ�.\n������� ���� �����ʹ� ������ϴ�.\n�Ͻðڽ��ϱ�?\n");
                } else{
                    printf("\nExiting the program.\nUnsaved data will be lost.\nAre you sure?\n");
                }
                printf("\nY/N -> ");
                scanf("%c", &ans);
                if(ans == 'Y' || ans == 'y'){
                    if(lang == 2){
                        printf("\n�ȳ��� ������!\n");
                    } else{
                        printf("\nGood Bye!\n");
                    }
// ������ ����
                    // ���� ���� ����
                    FILE *fp = fopen("setting.txt", "w");
                    fprintf(fp, "%d, %d\n", lang, save); // lang: ��� ���� (0: ����, 1: �ѱ���)
                    fclose(fp);
                    if(save == 1){
                        strcpy(path, AUTO_FILE_PATH);
                        FILE *fp = fopen(path, "w"); // write mode
                        for (int i = 0; i < MAX_DATA; i++) {
                            if (database[i].isUsed) { // using data save
                                fprintf(fp, "%d,%s,%d,%s,%s\n", database[i].id, database[i].name, database[i].grade, database[i].cellP, database[i].major);
                            }
                        }
                        fclose(fp); //close file.
                    }
                    return 0;
                }
                else{
                    if(lang == 2){
                        printf("\n������ ��ҵ�.\n");
                    } else{
                        printf("\nExit cancelled.\n");
                    }
                    break;
                }
            default:
                if(lang == 2){
                    printf("\n�߸��� �Է��Դϴ�. �ٽ� �õ��Ͻʽÿ�.\n");
                } else{
                    printf("\nInvalid input. Please try again.\n");
                }

        }
    }

    return 0;
}

void listData(int lang) {
    char ans;
    if(lang == 2){
        printf("\n1. ���� ���\n2. �� ���\nQ. ���\n");
    } else{
        printf("\n1. Basic List\n2. Detailed List\nQ. Cancel\n");
    }
    printf("\n-> ");
    scanf("%c", &ans);
    getchar(); // ���ۿ� ���� ���� ���� ����
    while (1) {
        switch (ans) {
            case '1':
                if(lang == 2){
                    printf("\n---- ������ ��� (����) ----\n");
                } else{
                    printf("\n---- Data List (Basic) ----\n");
                }
                for (int i = 0; i < MAX_DATA; i++) {
                    if (database[i].isUsed && database[i].id != 0) {
                        if(lang == 2){
                            printf("- �й� : %d  |  �̸� : %s  | �г� : %d\n", database[i].id, database[i].name,
                                   database[i].grade);
                            printf("------------------------------------------------\n");
                        } else{
                            printf("- ID : %d  |  NAME : %s  | GRADE : %d\n", database[i].id, database[i].name,
                                   database[i].grade);
                            printf("------------------------------------------------\n");
                        }
                    }
                }
                if(lang == 2){
                    printf("\n���͸� ���� �����ϼ���.");
                } else{
                    printf("\nPress ENTER to continue.");
                }
                getchar();
                return;
            case '2':
                if(lang == 2){
                    printf("\n---- ������ ��� (��) ----\n");
                } else{
                    printf("\n---- Data List (Detailed) ----\n");
                }
                for (int i = 0; i < MAX_DATA; i++) {
                    if (database[i].isUsed && database[i].id != 0) {
                        if(lang == 2){
                            printf("- �й� : %d  |  �̸� : %s  | �г� : %d\n", database[i].id, database[i].name,
                                   database[i].grade);
                            printf("- ��ȭ��ȣ : %s  |  �а� : %s\n", database[i].cellP, database[i].major);
                            printf("------------------------------------------------\n");
                        } else{
                            printf("- ID : %d  |  NAME : %s  | GRADE : %d\n", database[i].id, database[i].name,
                                   database[i].grade);
                            printf("- CELL : %s  |  MAJOR : %s\n", database[i].cellP, database[i].major);
                            printf("------------------------------------------------\n");
                        }
                    }
                }
                if(lang == 2){
                    printf("\n���͸� ���� �����ϼ���.");
                } else{
                    printf("\nPress ENTER to Continue.");
                }

                getchar();
                return;
            case 'q':
                return;
            default:
                if(lang == 2){
                    printf("\n�߸��� �Է��Դϴ�. �ٽ� �õ��Ͻʽÿ�.\n");
                } else{
                    printf("\nInvalid input. Please try again.\n");
                }
                return;
        }

    }
}

void sortDataByIDAsc() {
    for (int i = 0; i < MAX_DATA - 1; i++) {
        for (int j = 0; j < MAX_DATA - i - 1; j++) {
            if (database[j].isUsed && database[j + 1].isUsed && database[j].id > database[j + 1].id) {
                Student tmp = database[j];
                database[j] = database[j + 1];
                database[j + 1] = tmp;
            }
        }
    }
}

void sortDataByIDDesc() {
    for (int i = 0; i < MAX_DATA - 1; i++) {
        for (int j = 0; j < MAX_DATA - i - 1; j++) {
            if (database[j].isUsed && database[j + 1].isUsed && database[j].id < database[j + 1].id) {
                Student tmp = database[j];
                database[j] = database[j + 1];
                database[j + 1] = tmp;
            }
        }
    }
}

void insertData(int id, char* name, int grade, char* cellP, char* major, int lang) {
    for (int i = 0; i < MAX_DATA; i++) {
        if (!database[i].isUsed) {
            database[i].id = id;
            strcpy(database[i].name, name);
            database[i].grade = grade;
            strcpy(database[i].cellP, cellP);
            strcpy(database[i].major, major);
            database[i].isUsed = 1;
            if(lang == 2){
                printf("������ ���Ե� : %d, %s, %d, %s, %s\n", id, name, grade, cellP, major);
            } else{
                printf("Data Inserted : %d, %s, %d, %s, %s\n", id, name, grade, cellP, major);
            }

            return;
        }
    }
    if(lang == 2){
        printf("\"�����ͺ��̽��� ���� á���ϴ�.\n");
    } else{
        printf("\"The database is full.\n");
    }

}

void deleteData(int id, int lang) {
    for (int i = 0; i < MAX_DATA; i++) {
        if (database[i].isUsed && database[i].id == id) {
            database[i].isUsed = 0;
            if(lang == 2){
                printf("������ ������ : %s (%d)\n", database[i].name, id);
            } else{
                printf("Data Deleted : %s (%d)\n", database[i].name, id);
            }

            return;
        }
    }
    if(lang == 2){
        printf("�����͸� ã�� �� �����ϴ�.\n");
    } else{
        printf("Data not found.\n");
    }
}

void updateDataChar(int id, char ans, char* newData, int lang) {
    for (int i = 0; i < MAX_DATA; i++) {
        if (database[i].isUsed && database[i].id == id) {
            switch (ans) {
                case '1':
                    strcpy(database[i].name, newData);
                    if(lang == 2){
                        printf("������ ������ : %d -> %s\n", id, newData);
                    } else{
                        printf("Data Edited : %d -> %s\n", id, newData);
                    }
                    break;
                case '3':
                    strcpy(database[i].cellP, newData);
                    if(lang == 2){
                        printf("������ ������ : %d -> %s\n", id, newData);
                    } else{
                        printf("Data Edited : %d -> %s\n", id, newData);
                    }
                    break;
                case '4':
                    strcpy(database[i].major, newData);
                    if(lang == 2){
                        printf("������ ������ : %d -> %s\n", id, newData);
                    } else{
                        printf("Data Edited : %d -> %s\n", id, newData);
                    }
                    break;
            }
            return;
        }
    }
    if(lang == 2){
        printf("�����͸� ã�� �� �����ϴ�.\n");
    } else{
        printf("Data not found.\n");
    }
}

void updateDataInt(int id, char ans, int newData, int lang) {
    for (int i = 0; i < MAX_DATA; i++) {
        if (database[i].isUsed && database[i].id == id) {
            switch (ans) {
                case '2':
                    database[i].grade = newData;
                    if(lang == 2){
                        printf("������ ������ : %d -> %d\n", id, newData);
                    } else{
                        printf("Data Edited : %d -> %d\n", id, newData);
                    }

                    break;
            }
            return;
        }
    }
    if(lang == 2){
        printf("�����͸� ã�� �� �����ϴ�.\n");
    } else{
        printf("Data not found.\n");
    }
}

void updateData(int id, int lang) {
    int grade, nomatch;
    char name[50], cellP[20], major[50];
    char ans;
    while (1){//���ϰ� �ݺ����� �� �� �ְ� ����
        for (int i = 0; i < MAX_DATA; i++) {
            if (database[i].isUsed && database[i].id == id) {
                if(lang == 2){
                    printf("\n---- %s (%d)�� ������ ���� ----\n", database[i].name, database[i].id);
                    printf("1. ������������\n2. ������������(WIP)\nQ. ���\n");
                } else{
                    printf("\n---- Edit Data of %s (%d) ----\n", database[i].name, database[i].id);
                    printf("1. Edit Personal Data\n2. Edit Grade Data(WIP)\nQ. Cancel\n");
                }
                printf("\n-> ");
                scanf("%c", &ans);
                getchar(); // ���ۿ� ���� ���� ���� ����
                if(ans == '1'){//������������ ����. while�� �������� �����͸� �̾ ����.
                    if(lang == 2){
                        printf("\n---- ������������ ----\n");
                        printf("1. �̸� ����\n2. �г� ����\n3. ��ȭ��ȣ ����\n4. �а� ����\nQ. ���\n");
                    } else{
                        printf("\n---- Edit Personal Data ----\n");
                        printf("1. Edit Name\n2. Edit Grade\n3. Edit CellPhone Number\n4. Edit Major\nQ. Cancel\n");
                    }
                    printf("\n-> ");
                    scanf("%c", &ans);
                    getchar(); // ���ۿ� ���� ���� ���� ����
                    switch (ans) {
                        case '1':
                            if(lang == 2){
                                printf("\n���� : %s", database[i].name);
                                printf("\n���ο� �̸��� �Է��� �ּ���. : ");
                            } else{
                                printf("\nCurrent : %s", database[i].name);
                                printf("\nPlease enter a new Name. : ");
                            }
                            fgets(name, sizeof(name), stdin);
                            name[strcspn(name, "\n")] = 0; // ���� ���� ����
                            updateDataChar(id, ans, name, lang);
                            break;
                        case '2':
                            if(lang == 2){
                                printf("\n���� : %d", database[i].grade);
                                printf("\n���ο� �г��� �Է��� �ּ���. : ");
                            } else{
                                printf("\nCurrent : %d", database[i].grade);
                                printf("\nPlease enter a new Grade. : ");
                            }
                            scanf("%d", &grade);
                            getchar(); // ���ۿ� ���� ���� ���� ����
                            updateDataInt(id, ans, grade, lang);
                            break;
                        case '3':
                            if(lang == 2){
                                printf("\n���� : %s", database[i].cellP);
                                printf("\n���ο� ��ȭ��ȣ�� �Է��� �ּ���. : ");
                            } else{
                                printf("\nCurrent : %s", database[i].cellP);
                                printf("\nPlease enter a new CellPhone Number. : ");
                            }
                            fgets(cellP, sizeof(cellP), stdin);
                            cellP[strcspn(cellP, "\n")] = 0; // ���� ���� ����
                            updateDataChar(id, ans, cellP, lang);
                            break;
                        case '4':
                            if(lang == 2){
                                printf("\n���� : %s", database[i].major);
                                printf("\n���ο� �а��� �Է��� �ּ���. : ");
                            } else{
                                printf("\nCurrent : %s", database[i].major);
                                printf("\nPlease enter a new Major. : ");
                            }
                            fgets(major, sizeof(major), stdin);
                            major[strcspn(major, "\n")] = 0; // ���� ���� ����
                            updateDataChar(id, ans, major, lang);
                            break;
                        case 'q':
                            continue;
                        default:
                            if(lang == 2){
                                printf("\n�߸��� �Է��Դϴ�. �ٽ� �õ��Ͻʽÿ�.\n");
                            } else{
                                printf("\nInvalid input. Please try again.\n");
                            }
                    }
                }
                else if(ans == '2'){//���� ������ ����

                }
                else if(ans == 'q'){
                    return;
                }
                return;
            }
        }

    }

}

void searchData(int id, int lang) {
    for (int i = 0; i < MAX_DATA; i++) {
        if (database[i].isUsed && database[i].id == id) {
            if(lang == 2){
                printf("������ ã�� : %d, %s\n", id, database[i].name);
            } else{
                printf("Data Found : %d, %s\n", id, database[i].name);
            }
            return;
        }
    }
    if(lang == 2){
        printf("�����͸� ã�� �� �����ϴ�.\n");
    } else{
        printf("Data not found.\n");
    }
}

void saveData(int lang) {
    char ans;
    char path[150];
    if(lang == 2){
        printf("\n���� ���� ���\n");
        printf("1. �⺻ ��� ��� (/home/iot/CLionProjects/project_adbook.c/student_data.txt)\n");
        printf("2. ��� ����\n");
        printf("Q. ���\n");
    } else{
        printf("\nFile Save Path\n");
        printf("1. Use Default Path (/home/iot/CLionProjects/project_adbook.c/student_data.txt)\n");
        printf("2. Modify Path\n");
        printf("Q. Cancel\n");
    }
    printf("\n-> ");
    scanf("%c", &ans);
    getchar(); // ���ۿ� ���� ���� ���� ����8
    switch (ans) {
        case '1':
            strcpy(path, FILE_PATH);
            break;
        case '2':
            if(lang == 2){
                printf("���ο� ��θ� �Է��� �ּ���.\n");
            } else{
                printf("Please enter the new path.\n");
            }
            printf("\n-> ");
            fgets(path, sizeof(path), stdin);
            path[strcspn(path, "\n")] = 0; // ���� ���� ����
            break;
        case 'q':
            return;
        default:
            if(lang == 2){
                printf("\n�߸��� �Է��Դϴ�. �ٽ� �õ��Ͻʽÿ�.\n");
            } else{
                printf("\nInvalid input. Please try again.\n");
            }
            return;

    }
    FILE *fp = fopen(path, "w"); // write mode
    if (fp == NULL) {
        if(lang == 2){
            printf("������ �� �� �����ϴ�.\n");
        } else{
            printf("Can not open this File.\n");
        }
        return;
    }

    for (int i = 0; i < MAX_DATA; i++) {
        if (database[i].isUsed) { // using data save
            fprintf(fp, "%d,%s,%d,%s,%s\n", database[i].id, database[i].name, database[i].grade, database[i].cellP, database[i].major);
        }
    }

    fclose(fp); //close file.
    if(lang == 2){
        printf("������ �����\n");
        printf("\n���͸� ���� �����ϼ���.");
    } else{
        printf("Data Saved.\n");
        printf("\nPress ENTER to continue.");
    }

    getchar();
    return;
}

void loadData(int lang) {
    char ans;
    char path[150];
    int id, grade;
    char name[50], cellP[20], major[50];
    if(lang == 2){
        printf("\n���� �ҷ����� ���\n");
        printf("1. �⺻ ��� ��� (/home/iot/CLionProjects/project_adbook.c/student_data.txt)\n");
        printf("2. ��� ����\n");
        printf("3. �ڵ�����\n");
        printf("Q. ���\n");
    } else{
        printf("\nFile Load Path\n");
        printf("1. Use Default Path (/home/iot/CLionProjects/project_adbook.c/student_data.txt)\n");
        printf("2. Modify Path\n");
        printf("3. Auto Save\n");
        printf("Q. Cancel\n");
    }
    printf("\n-> ");
    scanf("%c", &ans);
    getchar(); // ���ۿ� ���� ���� ���� ����
    switch (ans) {
        case '1':
            strcpy(path, FILE_PATH);
            break;
        case '2':
            if(lang == 2){
                printf("���ο� ��θ� �Է��� �ּ���.\n");
            } else{
                printf("Please enter the new path.\n");
            }
            printf("\n-> ");
            fgets(path, sizeof(path), stdin);
            path[strcspn(path, "\n")] = 0; // ���� ���� ����
            break;
        case '3':
            strcpy(path, AUTO_FILE_PATH);
            break;
        case 'q':
            return;
        default:
            if(lang == 2){
                printf("\n�߸��� �Է��Դϴ�. �ٽ� �õ��Ͻʽÿ�.\n");
            } else{
                printf("\nInvalid input. Please try again.\n");
            }
            return;
    }
    FILE *fp = fopen(path, "r"); //read mode open
    if (fp == NULL) {
        if(lang == 2){
            printf("������ �� �� �����ϴ�.\n");
        } else{
            printf("Can not open this File.\n");
        }
        return;
    }

    memset(database, 0, sizeof(database)); //data reset

    while (fscanf(fp, "%d,%49[^,],%d,%19[^,],%49[^\n]\n", &id, name, &grade, cellP, major) == 5) {
        // ���Ͽ��� ���� �����͸� �����ͺ��̽��� �����մϴ�.
        insertData(id, name, grade, cellP, major, lang);
    }

    fclose(fp); //close file
    if(lang == 2){
        printf("������ �ҷ���\n");
        printf("\n���͸� ���� �����ϼ���.");
    } else{
        printf("Data loaded.\n");
        printf("\nPress ENTER to continue.");
    }
    getchar();
    return;
}

void programSetting(char ans, int* save, int* lang) {
    switch (ans) {
        case '1': {
            if(*lang == 2){
                printf("\n���� ��� ����:\n");
                printf("1. �������� ����\n");
                printf("2. �������� ����\n");
                printf("3. ���\n");
            } else{
                printf("\nChoose sorting method:\n");
                printf("1. Ascending order\n");
                printf("2. Descending order\n");
                printf("3. Cancel\n");
            }
            printf("\n-> ");
            scanf("%c", &ans);
            getchar(); // ���ۿ� ���� ���� ���� ����
            switch (ans) {
                case '1':
                    sortDataByIDAsc(); // ������������ ������ ����
                    if(*lang == 2){
                        printf("������������ ���ĵǾ����ϴ�.\n");
                    } else{
                        printf("Sorted by ascending order.\n");
                    }
                    break;
                case '2':
                    sortDataByIDDesc(); // ������������ ������ ����
                    if(*lang == 2){
                        printf("������������ ���ĵǾ����ϴ�.\n");
                    } else{
                        printf("Sorted in descending order.\n");
                    }
                    break;
                case 'q':
                    break;
                default:
                    if(*lang == 2){
                        printf("\n�߸��� �Է��Դϴ�. �ٽ� �õ��Ͻʽÿ�.\n");
                    } else{
                        printf("\nInvalid input. Please try again.\n");
                    }
            }
            break;
        }
        case '2':
            if(*lang == 2){
                printf("\n��� ����\n");
                printf("1. English\n");
                printf("2. �ѱ���\n");
            } else{
                printf("\nChoose language\n");
                printf("1. English\n");
                printf("2. �ѱ���\n");
            }
            printf("\n-> ");
            scanf("%c", &ans);
            getchar(); // ���ۿ� ���� ���� ���� ����
            switch (ans) {
                case '1':
                    *lang = 1;
                    break;
                case '2':
                    *lang = 2;
                    break;
                default:
                    if(*lang == 2){
                        printf("\n�߸��� �Է��Դϴ�. �ٽ� �õ��Ͻʽÿ�.\n");
                    } else{
                        printf("\nInvalid input. Please try again.\n");
                    }
                    break;
            }
            break;
        case '3':
            if(*lang == 2){
                printf("\n�ڵ�����\n");
                if(*save == 0){
                    printf("���� : ����\n");
                    printf("�ڵ� ���� ����� �ѽðڽ��ϱ�?\n");
                    printf("\nY/N -> ");
                    scanf("%c", &ans);
                    getchar(); // ���ۿ� ���� ���� ���� ����
                    if(ans == 'Y' || ans == 'y'){
                        *save = 1;
                    }
                }
                else if(*save == 1){
                    printf("���� : ����\n");
                    printf("�ڵ� ���� ����� ���ðڽ��ϱ�?\n");
                    printf("\nY/N -> ");
                    scanf("%c", &ans);
                    getchar(); // ���ۿ� ���� ���� ���� ����
                    if(ans == 'Y' || ans == 'y'){
                        *save = 0;
                    }
                }
            } else{
                printf("\nAuto Save\n");
                if(*save == 0){
                    printf("Current : OFF\n");
                    printf("Do you want to turn on the auto save?\n");
                    printf("\nY/N -> ");
                    scanf("%c", &ans);
                    getchar(); // ���ۿ� ���� ���� ���� ����
                    if(ans == 'Y' || ans == 'y'){
                        *save = 1;
                    }
                }
                else if(*save == 1){
                    printf("Current : ON\n");
                    printf("Do you want to turn off the auto save?\n");
                    printf("\nY/N -> ");
                    scanf("%c", &ans);
                    getchar(); // ���ۿ� ���� ���� ���� ����
                    if(ans == 'Y' || ans == 'y'){
                        *save = 0;
                    }
                }
            }
            break;
        case 'q':
            return;
        default:
            if(*lang == 2){
                printf("\n�߸��� �Է��Դϴ�. �ٽ� �õ��Ͻʽÿ�.\n");
            } else{
                printf("\nInvalid input. Please try again.\n");
            }
            break;
    }
}

void clearConsole() {
    printf("\033[2J");
    printf("\033[H");
}


