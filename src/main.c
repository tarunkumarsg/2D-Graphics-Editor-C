#include <stdio.h>

int main()
{
    int choice;

    do
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
printf("1.Draw 2.Delete 3.Modify 4.Display 5.Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        switch(choice)
{
    case 1:
        printf("Draw operation selected\n");
        break;

    case 2:
        printf("Delete operation selected\n");
        break;

    case 3:
        printf("Modify operation selected\n");
        break;

    case 4:
        printf("Display operation selected\n");
        break;

    case 5:
        printf("Exiting...\n");
        break;

    default:
        printf("Invalid choice\n");
}

    } while(choice != 5);

    return 0;
}