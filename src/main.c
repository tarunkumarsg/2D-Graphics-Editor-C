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
{
    printf("Draw module selected\n");
    printf("Here user can draw Line, Rectangle, or Circle\n");
    break;
}

case 2:
{
    printf("Delete module selected\n");
    printf("Here user can delete an existing shape\n");
    break;
}

case 3:
{
    printf("Modify module selected\n");
    printf("Here user can update shape coordinates\n");
    break;
}

case 4:
{
    printf("\n===== DISPLAY MENU =====\n");
    printf("Shapes stored in canvas:\n");
    printf("No shapes available currently.\n");
    printf("Add shapes using Draw option.\n");
    break;
}

    case 5:
        printf("Exiting...\n");
        break;

    default:
        printf("Invalid choice\n");
}

    } while(choice != 5);

    return 0;
}