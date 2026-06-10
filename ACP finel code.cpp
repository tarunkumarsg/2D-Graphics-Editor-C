#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 20
#define COLS 60
#define MAX_OBJECTS 10

// Enumeration for supported shapes
typedef enum { CIRCLE, RECTANGLE, LINE, TRIANGLE } ShapeType;

// Structure to keep track of drawn objects for deletion/modification
typedef struct {
    int id;
    ShapeType type;
    int p1, p2, p3, p4, p5, p6; // Generic parameters for shapes
    int active;                 // 1 if active, 0 if deleted
} GraphicalObject;

// Global variables
char canvas[ROWS][COLS];
GraphicalObject registry[MAX_OBJECTS];
int object_count = 0;

// Function prototypes
void init_canvas();
void display_canvas();
void redraw_all();
void add_circle(int id, int cx, int cy, int r);
void add_rectangle(int id, int x1, int y1, int x2, int y2);
void add_line(int id, int x1, int y1, int x2, int y2);
void add_triangle(int id, int x1, int y1, int x2, int y2, int x3, int y3);

// Initialize canvas with underscores
void init_canvas() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            canvas[i][j] = '_';
        }
    }
}

// Render the 2D character array to console
void display_canvas() {
    printf("\n--- CURRENT DRAWING CANVAS ---\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            putchar(canvas[i][j]);
        }
        putchar('\n');
    }
    printf("------------------------------\n");
}

// Clear canvas and replay active objects (used for delete and modify)
void redraw_all() {
    init_canvas();
    for (int i = 0; i < object_count; i++) {
        if (registry[i].active) {
            switch (registry[i].type) {
                case CIRCLE:
                    add_circle(registry[i].id, registry[i].p1, registry[i].p2, registry[i].p3);
                    break;
                case RECTANGLE:
                    add_rectangle(registry[i].id, registry[i].p1, registry[i].p2, registry[i].p3, registry[i].p4);
                    break;
                case LINE:
                    add_line(registry[i].id, registry[i].p1, registry[i].p2, registry[i].p3, registry[i].p4);
                    break;
                case TRIANGLE:
                    add_triangle(registry[i].id, registry[i].p1, registry[i].p2, registry[i].p3, registry[i].p4, registry[i].p5, registry[i].p6);
                    break;
            }
        }
    }
}

// Plot a circle using standard equation: (x - cx)^2 + (y - cy)^2 approx r^2
void add_circle(int id, int cx, int cy, int r) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            // Using scaling factor because terminal characters are taller than they are wide
            double dist = pow((j - cx) * 0.5, 2) + pow(i - cy, 2);
            double r_squared = r * r;
            if (fabs(dist - r_squared) < (r * 0.8)) {
                if (i >= 0 && i < ROWS && j >= 0 && j < COLS) {
                    canvas[i][j] = '*';
                }
            }
        }
    }
}

// Plot a bounding rectangle outline
void add_rectangle(int id, int x1, int y1, int x2, int y2) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if ((i == y1 || i == y2) && (j >= x1 && j <= x2)) {
                canvas[i][j] = '*';
            }
            if ((j == x1 || j == x2) && (i >= y1 && i <= y2)) {
                canvas[i][j] = '*';
            }
        }
    }
}

// Plot a line using a simplified DDA/Bresenham step logic
void add_line(int id, int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    
    if (steps == 0) {
        if (y1 >= 0 && y1 < ROWS && x1 >= 0 && x1 < COLS) canvas[y1][x1] = '*';
        return;
    }
    
    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;
    
    float x = x1;
    float y = y1;
    
    for (int i = 0; i <= steps; i++) {
        int r_y = (int)(y + 0.5);
        int r_x = (int)(x + 0.5);
        if (r_y >= 0 && r_y < ROWS && r_x >= 0 && r_x < COLS) {
            canvas[r_y][r_x] = '*';
        }
        x += x_inc;
        y += y_inc;
    }
}

// Plot a triangle by connecting its three vertices using the line tool
void add_triangle(int id, int x1, int y1, int x2, int y2, int x3, int y3) {
    add_line(id, x1, y1, x2, y2);
    add_line(id, x2, y2, x3, y3);
    add_line(id, x3, y3, x1, y1);
}

int main() {
    int choice, sub_choice, obj_id, target_idx, found;
    init_canvas();
    
    while (1) {
        printf("\n===== 2D GRAPHICS EDITOR MENU =====\n");
        printf("1. Add Object\n");
        printf("2. Delete Object\n");
        printf("3. Modify Object\n");
        printf("4. Display Canvas\n");
        printf("5. List Active Objects\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        if (choice == 6) break;
        
        switch (choice) {
            case 1: // Add Object
                if (object_count >= MAX_OBJECTS) {
                    printf("Registry full! Delete some objects first.\n");
                    break;
                }
                printf("\nSelect Shape:\n1. Circle\n2. Rectangle\n3. Line\n4. Triangle\nChoice: ");
                scanf("%d", &sub_choice);
                
                registry[object_count].id = object_count + 1;
                registry[object_count].active = 1;
                
                if (sub_choice == 1) {
                    registry[object_count].type = CIRCLE;
                    printf("Enter Center X, Center Y, and Radius: ");
                    scanf("%d %d %d", &registry[object_count].p1, &registry[object_count].p2, &registry[object_count].p3);
                } else if (sub_choice == 2) {
                    registry[object_count].type = RECTANGLE;
                    printf("Enter Top-Left (X1 Y1) and Bottom-Right (X2 Y2): ");
                    scanf("%d %d %d %d", &registry[object_count].p1, &registry[object_count].p2, &registry[object_count].p3, &registry[object_count].p4);
                } else if (sub_choice == 3) {
                    registry[object_count].type = LINE;
                    printf("Enter Start (X1 Y1) and End (X2 Y2): ");
                    scanf("%d %d %d %d", &registry[object_count].p1, &registry[object_count].p2, &registry[object_count].p3, &registry[object_count].p4);
                } else if (sub_choice == 4) {
                    registry[object_count].type = TRIANGLE;
                    printf("Enter Point 1 (X1 Y1), Point 2 (X2 Y2), Point 3 (X3 Y3): ");
                    scanf("%d %d %d %d %d %d", &registry[object_count].p1, &registry[object_count].p2, &registry[object_count].p3, &registry[object_count].p4, &registry[object_count].p5, &registry[object_count].p6);
                } else {
                    printf("Invalid Shape choice!\n");
                    break;
                }
                
                object_count++;
                redraw_all();
                printf("Object added successfully!\n");
                break;
                
            case 2: // Delete Object
                printf("Enter Object ID to delete: ");
                scanf("%d", &obj_id);
                found = 0;
                for (int i = 0; i < object_count; i++) {
                    if (registry[i].id == obj_id && registry[i].active) {
                        registry[i].active = 0;
                        found = 1;
                        break;
                    }
                }
                if (found) {
                    redraw_all();
                    printf("Object ID %d deleted.\n", obj_id);
                } else {
                    printf("Active Object ID not found.\n");
                }
                break;
                
            case 3: // Modify Object
                printf("Enter Object ID to modify: ");
                scanf("%d", &obj_id);
                target_idx = -1;
                for (int i = 0; i < object_count; i++) {
                    if (registry[i].id == obj_id && registry[i].active) {
                        target_idx = i;
                        break;
                    }
                }
                if (target_idx == -1) {
                    printf("Active Object ID not found.\n");
                    break;
                }
                
                printf("Modifying object of type %d. Enter new configuration parameters:\n", registry[target_idx].type);
                if (registry[target_idx].type == CIRCLE) {
                    printf("Enter new Center X, Center Y, and Radius: ");
                    scanf("%d %d %d", &registry[target_idx].p1, &registry[target_idx].p2, &registry[target_idx].p3);
                } else if (registry[target_idx].type == RECTANGLE || registry[target_idx].type == LINE) {
                    printf("Enter new X1, Y1, X2, Y2: ");
                    scanf("%d %d %d %d", &registry[target_idx].p1, &registry[target_idx].p2, &registry[target_idx].p3, &registry[target_idx].p4);
                } else if (registry[target_idx].type == TRIANGLE) {
                    printf("Enter new X1 Y1 X2 Y2 X3 Y3: ");
                    scanf("%d %d %d %d %d %d", &registry[target_idx].p1, &registry[target_idx].p2, &registry[target_idx].p3, &registry[target_idx].p4, &registry[target_idx].p5, &registry[target_idx].p6);
                }
                
                redraw_all();
                printf("Object updated successfully.\n");
                break;
                
            case 4: // Display Canvas
                display_canvas();
                break;
                
            case 5: // List Active Objects
                printf("\n--- Active Objects Register ---\n");
                for (int i = 0; i < object_count; i++) {
                    if (registry[i].active) {
                        printf("ID: %d | Type: %s\n", registry[i].id, 
                               registry[i].type == CIRCLE ? "Circle" :
                               registry[i].type == RECTANGLE ? "Rectangle" :
                               registry[i].type == LINE ? "Line" : "Triangle");
                    }
                }
                break;
                
            default:
                printf("Invalid selection.\n");
        }
    }
    return 0;
}
