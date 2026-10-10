
#include <stdio.h>
#include <string.h>

struct Patient {
    int id, age, priority;
    char name[30], condition[40], status[20];
} p[50], t;

int main(void) {
    int n = 0, ch, i, j, id, found;

    do {
        printf("\n--- HOSPITAL QUEUE ---\n");
        printf("1.Register  2.Display Queue  3.Next Patient\n");
        printf("4.Update Status  5.Search  6.Summary  0.Exit\nChoice: ");
        if (scanf("%d", &ch) != 1) return 0;

        if (ch == 1 && n < 50) {
            printf("ID Age Priority(1=Critical,2=Urgent,3=Normal): ");
            if (scanf("%d%d%d", &p[n].id, &p[n].age,
                      &p[n].priority) != 3) return 0;

            found = 0;
            for (i = 0; i < n; i++)
                if (p[i].id == p[n].id) found = 1;

            if (found || p[n].age < 0 ||
                p[n].priority < 1 || p[n].priority > 3) {
                printf("Invalid or duplicate record!\n");
                continue;
            }

            printf("Name: ");
            scanf(" %29[^\n]", p[n].name);
            printf("Condition: ");
            scanf(" %39[^\n]", p[n].condition);
            strcpy(p[n].status, "Waiting");
            n++;
            printf("Patient registered!\n");
        }
        else if (ch == 2 || ch == 3) {
            for (i = 0; i < n - 1; i++)
                for (j = 0; j < n - i - 1; j++)
                    if (p[j].priority > p[j+1].priority) {
                        t = p[j];
                        p[j] = p[j+1];
                        p[j+1] = t;
                    }

            found = 0;
            for (i = 0; i < n; i++)
                if (!strcmp(p[i].status, "Waiting")) {
                    if (ch == 3) {
                        printf("Next: %s (ID %d)\n",
                            p[i].name, p[i].id);
                        found = 1;
                        break;
                    }
                    printf("%d %s Priority:%d Status:%s\n",
                        p[i].id, p[i].name,
                        p[i].priority, p[i].status);
                    found = 1;
                }
            if (!found) printf("No waiting patients.\n");
        }
        else if (ch == 4 || ch == 5) {
            printf("Patient ID: ");
            if (scanf("%d", &id) != 1) return 0;
            found = 0;

            for (i = 0; i < n; i++)
                if (p[i].id == id) {
                    found = 1;
                    if (ch == 5)
                        printf("%s | %s | Priority:%d | %s\n",
                            p[i].name, p[i].condition,
                            p[i].priority, p[i].status);
                    else {
                        printf("Status (Waiting/Treating/Discharged): ");
                        scanf(" %19s", p[i].status);
                        if (strcmp(p[i].status, "Waiting") &&
                            strcmp(p[i].status, "Treating") &&
                            strcmp(p[i].status, "Discharged"))
                            strcpy(p[i].status, "Waiting");
                        else
                            printf("Status updated.\n");
                    }
                    break;
                }
            if (!found) printf("Patient not found.\n");
        }
        else if (ch == 6) {
            int w = 0, tr = 0, d = 0;
            for (i = 0; i < n; i++) {
                if (!strcmp(p[i].status, "Waiting")) w++;
                else if (!strcmp(p[i].status, "Treating")) tr++;
                else d++;
            }
            printf("Total:%d Waiting:%d Treating:%d Discharged:%d\n",
                n, w, tr, d);
        }
        else if (ch != 0 && ch != 1)
            printf("Invalid choice or storage full.\n");

    } while (ch != 0);

    return 0;
}
