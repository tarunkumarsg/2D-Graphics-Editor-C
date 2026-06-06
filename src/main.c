#include <stdio.h>

int main()
{
    int choice;

    do
    {
        printf("\n1.Draw 2.Delete 3.Modify 4.Display 5.Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

    } while(choice != 5);

    return 0;
}