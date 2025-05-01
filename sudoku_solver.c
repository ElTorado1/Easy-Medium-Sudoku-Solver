#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct sudoku {
    char arr[3][3][3][3];
};
struct sudoku * sudoku_solver(struct sudoku * dummy,int row, int column, int inner_row, int inner_column);
int * check_cell(struct sudoku * dummy,int row, int column);
int * check_row(struct sudoku * dummy,int row, int inner_row, int *);
int * check_column(struct sudoku * dummy, int column, int inner_column, int*);
int control(struct sudoku * dummy);
void sudoku_solver_title();
int solve_backtracking(struct sudoku *dummy);
int is_valid(struct sudoku *dummy, int row, int column,int inner_row, int inner_column, char num);
int main(void) {
    struct sudoku sudoku;
    sudoku_solver_title();
    struct sudoku * solved = &sudoku;
    printf("Enter the sudoku numbers(for unknowns enter '-')(seperate every number by space ' ')(when a row is completed press enter for the next row):\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char val;
            scanf(" %c", &val);
            sudoku.arr[i/3][j/3][i%3][j%3] = val;
        }
    }
    do {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    for (int l = 0; l < 3; l++) {
                        if (sudoku.arr[i][j][k][l] == '-') {
                            sudoku_solver(&sudoku,i,j,k,l);
                        }
                    }
                }
            }
        }
    }while (control(&sudoku));

    if (!solve_backtracking(&sudoku)) {
        printf("No solution");
        return 1;
    }
    printf("\nSolved Sudoku:\n\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%c ", sudoku.arr[i/3][j/3][i%3][j%3]);
            if (j % 3 == 2) printf(" ");
        }
        printf("\n");
        if (i % 3 == 2) printf("\n");
    }
}
void sudoku_solver_title(){
    printf("  _____  _    _  _____    ____   _  __ _    _  \n");
    printf(" / ____|| |  | ||  __ \\  / __ \\ | |/ /| |  | | \n");
    printf("| (___  | |  | || |  | || |  | || ' / | |  | | \n");
    printf(" \\___ \\ | |  | || |  | || |  | ||  <  | |  | | \n");
    printf(" ____) || |__| || |__| || |__| || . \\ | |__| | \n");
    printf("|_____/  \\____/ |_____/  \\____/ |_|\\_\\ \\____/  \n");
}
struct sudoku * sudoku_solver(struct sudoku * dummy,int row, int column, int inner_row, int inner_column) {
    int * possibilities = check_cell(dummy,row,column);
    possibilities = check_row(dummy, row, inner_row, possibilities);
    possibilities = check_column(dummy, column, inner_column, possibilities);
    int count_of_more_than_zero = 0;
    int find;
    for (int i = 0; i < 9; i++) {
        if (possibilities[i] != 0) {
            count_of_more_than_zero++;
            find = possibilities[i];
        }
    }
    if (count_of_more_than_zero == 1) {
        dummy->arr[row][column][inner_row][inner_column] = find + '0';
    }
    free(possibilities);
    return dummy;
}
int * check_cell(struct sudoku * dummy, int row, int column) {
    int * possibilities = (int *)malloc(9 * sizeof(int));
    for (int i = 0; i < 9; i++) {
        possibilities[i] = i + 1;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 9; k++) {
                if (dummy->arr[row][column][i][j] != '-' && dummy->arr[row][column][i][j] - '0' == possibilities[k]) possibilities[k] = 0;
            }
        }
    }
    return possibilities;
}
int * check_row(struct sudoku * dummy,int row,int inner_row, int * possibilities) {
    for (int i = 0; i < 3;i ++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 9; k++) {
                if (dummy->arr[row][i][inner_row][j] != '-' && dummy->arr[row][i][inner_row][j] - '0' == possibilities[k]) possibilities[k] = 0;
            }
        }
    }
    return possibilities;
}
int * check_column(struct sudoku * dummy, int column, int inner_column, int * possibilities) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 9; k++) {
                if (dummy->arr[i][column][j][inner_column] != '-' && dummy->arr[i][column][j][inner_column] - '0' == possibilities[k]) possibilities[k] = 0;
            }
        }
    }
    return possibilities;
}
int control(struct sudoku * dummy) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    if (dummy->arr[i][j][k][l] == '-') return 1;
                }
            }
        }
    }
    return 0;
}
int is_valid(struct sudoku * dummy, int row, int column, int inner_row, int inner_column, char num) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (dummy->arr[row][i][inner_row][j] == num) return 0;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (dummy->arr[i][column][j][inner_column] == num) return 0;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (dummy->arr[row][column][i][j] == num) return 0;
        }
    }
    return 1;
}
int solve_backtracking(struct sudoku *dummy) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    if (dummy->arr[i][j][k][l] == '-') {
                        for (char num = '1'; num <= '9'; num++) {
                            if (is_valid(dummy,i,j,k,l,num)) {
                                dummy->arr[i][j][k][l] = num;
                                if (solve_backtracking(dummy)) return 1;
                                dummy->arr[i][j][k][l] = '-';
                            }
                        }
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}
