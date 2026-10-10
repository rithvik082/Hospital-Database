
#include <stdio.h>
#include <string.h>

struct Complaint {
    int id, priority;
    char category[25], problem[60], location[40], status[20];
} c[50], t;

int main(void) {
    int n = 0, ch, i, j, id, found;

    do {
        printf("\n--- CAMPUS COMPLAINT SYSTEM ---\n");
        printf("1.Add 2.Display 3.Search 4.Update\n");
        printf("5.Pending 6.Summary 0.Exit\nChoice: ");
        if (scanf("%d", &ch) != 1) return 0;

        if (ch == 1) {
            if (n == 50) { printf("Storage full!\n"); continue; }

            printf("ID: ");
            scanf("%d", &id);
            found = 0;
            for (i = 0; i < n; i++)
                if (c[i].id == id) found = 1;
            if (found) { printf("Duplicate ID!\n"); continue; }
            c[n].id = id;

            printf("Category: ");
            scanf(" %24[^\n]", c[n].category);
            printf("Problem: ");
            scanf(" %59[^\n]", c[n].problem);
            printf("Location: ");
            scanf(" %39[^\n]", c[n].location);
            printf("Priority (1=High, 2=Medium, 3=Low): ");
            scanf("%d", &c[n].priority);

            if (c[n].priority < 1 || c[n].priority > 3) {
                printf("Invalid priority!\n"); continue;
            }
            strcpy(c[n].status, "Pending");
            n++;
            printf("Complaint registered!\n");
        }
        else if (ch == 2 || ch == 5) {
            for (i = 0; i < n - 1; i++)
                for (j = 0; j < n - i - 1; j++)
                    if (c[j].priority > c[j+1].priority) {
                        t = c[j]; c[j] = c[j+1]; c[j+1] = t;
                    }

            found = 0;
            for (i = 0; i < n; i++)
                if (ch == 2 || !strcmp(c[i].status, "Pending")) {
                    printf("%d | %s | %s | P%d | %s\n",
                        c[i].id, c[i].category, c[i].location,
                        c[i].priority, c[i].status);
                    found = 1;
                }
            if (!found) printf("No complaints found.\n");
        }
        else if (ch == 3 || ch == 4) {
            printf("Complaint ID: ");
            scanf("%d", &id);
            found = 0;
            for (i = 0; i < n; i++)
                if (c[i].id == id) {
                    found = 1;
                    if (ch == 3)
                        printf("%d | %s | %s | %s | P%d | %s\n",
                            c[i].id, c[i].category, c[i].problem,
                            c[i].location, c[i].priority, c[i].status);
                    else {
                        printf("Status (Pending/Progress/Resolved): ");
                        scanf(" %19s", c[i].status);
                        if (strcmp(c[i].status, "Pending") &&
                            strcmp(c[i].status, "Progress") &&
                            strcmp(c[i].status, "Resolved"))
                            strcpy(c[i].status, "Pending");
                        printf("Status: %s\n", c[i].status);
                    }
                    break;
                }
            if (!found) printf("Complaint not found!\n");
        }
        else if (ch == 6) {
            int pending = 0, progress = 0, resolved = 0;
            for (i = 0; i < n; i++) {
                if (!strcmp(c[i].status, "Pending")) pending++;
                else if (!strcmp(c[i].status, "Progress")) progress++;
                else resolved++;
            }
            printf("Total:%d Pending:%d Progress:%d Resolved:%d\n",
                n, pending, progress, resolved);
        }
        else if (ch != 0) printf("Invalid choice!\n");

    } while (ch != 0);

    return 0;
}
