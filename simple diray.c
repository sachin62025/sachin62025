#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 100
#define MAX_ENTRY_LENGTH 1000

struct DiaryEntry {
    char date[20];
    char entry[MAX_ENTRY_LENGTH];
};

struct Diary {
    struct DiaryEntry entries[MAX_ENTRIES];
    int numEntries;
};

void saveDiaryToFile(struct Diary diary, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fwrite(&diary, sizeof(struct Diary), 1, file);
    fclose(file);
}

void loadDiaryFromFile(struct Diary* diary, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    fread(diary, sizeof(struct Diary), 1, file);
    fclose(file);
}

void addEntry(struct Diary* diary, const char* date, const char* entry) {
    if (diary->numEntries >= MAX_ENTRIES) {
        printf("Diary is full. Cannot add more entries.\n");
        return;
    }

    strcpy(diary->entries[diary->numEntries].date, date);
    strcpy(diary->entries[diary->numEntries].entry, entry);
    diary->numEntries++;
}

void viewEntries(struct Diary diary) {
    printf("Diary Entries:\n");
    for (int i = 0; i < diary.numEntries; i++) {
        printf("Date: %s\n", diary.entries[i].date);
        printf("Entry: %s\n", diary.entries[i].entry);
        printf("------------------------------\n");
    }
}

int main() {
    struct Diary diary;
    diary.numEntries = 0;

    loadDiaryFromFile(&diary, "diary.dat");

    int choice;
    char date[20];
    char entry[MAX_ENTRY_LENGTH];

    while (1) {
        printf("\n1. Add entry\n");
        printf("2. View entries\n");
        printf("3. Save and quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter date (DD-MM-YYYY): ");
                scanf("%s", date);
                getchar(); // Clear the newline character from the buffer
                printf("Enter entry:\n");
                fgets(entry, MAX_ENTRY_LENGTH, stdin);
                addEntry(&diary, date, entry);
                break;
            case 2:
                viewEntries(diary);
                break;
            case 3:
                saveDiaryToFile(diary, "diary.dat");
                printf("Diary saved. Quitting.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}

