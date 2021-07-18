#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#define clear() printf("\033[H\033[J")
#define INPUT_SIZE 64

uint8_t choose;
uint16_t size = 0;
char str[INPUT_SIZE];

struct Date {
    uint16_t day;
    uint16_t month;
    uint16_t year;
};

struct Human {
    char name[79];
    uint16_t room;
    struct Date date_in;
    struct Date date_out;
};

void display(struct Human human) {
    printf("name: %s, date in: %d/%d/%d, date out: %d/%d/%d, room: %d\n",
           human.name, human.date_in.day, human.date_in.month, human.date_in.year,
           human.date_out.day, human.date_out.month, human.date_out.year,
           human.room);
}

int comparator(const void *p, const void *q) {
    return strcmp(((struct Human *) p)->name,
                  ((struct Human *) q)->name);
}

void search(struct Human *human) {
    char name[79];
    struct Date temp;
    uint16_t room;

    printf("how do you want to find\n");
    printf("1. by name\n");
    printf("2. date in\n");
    printf("3. room\n");
    printf("4. date out\n");
    fgets(str, INPUT_SIZE, stdin);
    choose = strtol(str, NULL, 10);

    switch (choose) {
        case 1:
            printf("set name:\n");
            scanf("%s", name);
            for (int i = 0; i < size; ++i)
                if (strcmp(human[i].name, name) == 0)
                    display(human[i]);
            break;

        case 2:
            printf("set date in:\n");
            scanf("%hd %hd %hd", &temp.day, &temp.month, &temp.year);
            for (int i = 0; i < size; ++i)
                if (temp.day == human[i].date_in.day && temp.month == human[i].date_in.month &&
                    temp.year == human[i].date_in.year)
                    display(human[i]);
            break;

        case 3:
            printf("set room:\n");
            scanf("%hd", &room);
            for (int i = 0; i < size; ++i)
                if (room == human[i].room)
                    display(human[i]);
            break;

        case 4:
            printf("set date out:\n");
            scanf("%hd %hd %hd", &temp.day, &temp.month, &temp.year);
            for (int i = 0; i < size; ++i)
                if (temp.day == human[i].date_out.day && temp.month == human[i].date_out.month &&
                    temp.year == human[i].date_out.year)
                    display(human[i]);
            break;

        default:
            break;
    }
}

struct Human *sort(struct Human *current) {
    struct Human temp;

    printf("how do you want to find\n");
    printf("1. by name\n");
    printf("2. date in\n");
    printf("3. room\n");
    printf("4. date out\n");
    fgets(str, INPUT_SIZE, stdin);
    choose = strtol(str, NULL, 10);

    switch (choose) {
        case 1:
            qsort(current, size, sizeof(struct Human), comparator);
            break;

        case 2:
            for (int i = 0; i < size - 1; ++i)
                for (int j = 0; j < size - 1 - i; ++j) {
                    if ((current[j].date_in.year > current[j + 1].date_in.year) ||
                        (current[j].date_in.year == current[j + 1].date_in.year &&
                         current[j].date_in.month > current[j + 1].date_in.month) ||
                        (current[j].date_in.year == current[j + 1].date_in.year &&
                         current[j].date_in.month == current[j + 1].date_in.month &&
                         current[j].date_in.day > current[j + 1].date_in.day)) {
                        temp = current[j];
                        current[j] = current[j + 1];
                        current[j + 1] = temp;
                    }
                }
            break;

        case 3:
            for (int i = 0; i < size - 1; ++i)
                for (int j = 0; j < size - 1 - i; ++j) {
                    if(current[j].room > current[j + 1].room) {
                        temp = current[j];
                        current[j] = current[j + 1];
                        current[j + 1] = temp;
                    }
                }
            break;

        case 4:
            for (int i = 0; i < size - 1; ++i)
                for (int j = 0; j < size - 1 - i; ++j) {
                    if ((current[j].date_out.year > current[j + 1].date_out.year) ||
                        (current[j].date_out.year == current[j + 1].date_out.year &&
                         current[j].date_out.month > current[j + 1].date_out.month) ||
                        (current[j].date_out.year == current[j + 1].date_out.year &&
                         current[j].date_out.month == current[j + 1].date_out.month &&
                         current[j].date_out.day > current[j + 1].date_out.day)) {
                        temp = current[j];
                        current[j] = current[j + 1];
                        current[j + 1] = temp;
                    }
                }
            break;

        default:
            break;
    }

    return current;
}

struct Human *remove_element(struct Human *current, uint16_t element) {
    struct Human *temp = malloc((size - 1) * sizeof(struct Human));
    memcpy(temp, current, element * sizeof(struct Human));
    memcpy(temp + element, current + element + 1, (size - element - 1) * sizeof(struct Human));
    return temp;
}

struct Human add_entries(void) {
    struct Human human;

    printf("set name:\n");
    scanf("%s", human.name);

    printf("set date in:\n");
    scanf("%hd %hd %hd", &human.date_in.day, &human.date_in.month, &human.date_in.year);

    printf("set room:\n");
    scanf("%hd", &human.room);

    printf("set date out:\n");
    scanf("%hd %hd %hd", &human.date_out.day, &human.date_out.month, &human.date_out.year);

    return human;
}

int main(void) {
    struct Human *human = malloc((size + 1) * sizeof(struct Human));

    do {
        printf("1. add contact\n");
        printf("2. display all entries\n");
        printf("3. search\n");
        printf("4. delete record by sequential number\n");
        printf("5. sort\n");
        printf("6. exit\n");
        fgets(str, INPUT_SIZE, stdin);
        choose = strtol(str, NULL, 10);
        clear();

        switch (choose) {
            case 1:
                printf("how many contacts do you want to add\n");
                fgets(str, INPUT_SIZE, stdin);
                choose = strtol(str, NULL, 10);
                for (int i = 0; i < choose; ++i) {
                    human[i] = add_entries();
                    ++size;
                    human = realloc(human, (size + 1) * sizeof(struct Human));
                }
                break;

            case 2:
                for (int i = 0; i < size; ++i)
                    display(human[i]);
                break;

            case 3:
                search(human);
                break;

            case 4:
                printf("Enter the item number\n");
                scanf("%hd", &choose);
                human = remove_element(human, choose);
                break;

            case 5:
                sort(human);

            default:
                break;
        }
    } while (choose != 6);

    free(human);
    human = NULL;

    return 0;
}
