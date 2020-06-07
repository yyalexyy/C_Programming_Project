#include <stdio.h>

int main()
{
        int num = 1;
        int space = 1;
        int row;
        for(row = 1; row < 20; row++)
        {
                printf("! ");

                int j;
                for(j = 1; j <= row; j++)
                {
                        if(row <= 10)
                        {
                                printf("%3d ", num);
                                num++;
                        }
                        else
                        {
                                if(j <= space)
                                {
                                        printf("    ");
                                }
                                else if(j <= 10)
                                {
                                        printf("%3d ", num);
                                        num++;
                                }
                                else
                                        break;
                        }

                }

                if(row > 10)
                {
                        space++;
                }

                printf("\n");

        }

        return 0;
}
