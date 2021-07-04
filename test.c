#include <stdio.h>
#include <unistd.h>

int	ft_ptr_len(unsigned long long arg)
{
	int	i;

	i = 0;
	while (arg != 0)
	{
		arg = arg / 16;
		i++;
	}
	return (i);
}

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    get_value(unsigned long value)
{
    unsigned long 	hex;
    char            symbol;
    	
	hex = 0;
	if (!value)
		return ;
	else
	{
		hex = value % 16;
		get_value(value / 16);
	}
	if (hex > 9)
	{
        symbol = 'a' + (hex - 10);
        ft_putchar(symbol);
        //printf("%c",'a' + (hex - 10));
    }
	else
    {
        symbol = hex + '0';
        ft_putchar(symbol);
        //printf("%c", hex + '0');
    }
}

int main()
{
	int *a;
    int *remainder = a;
    int result;
	// int b = 0;
    // int *int_pointer;
    // int_pointer = &a;
    // void *void_pointer;
    // char *char_pointer = NULL;
    
    get_value(a);
    printf("\n");
    result = printf("%20p", a);
	//kek = printf("%s", NULL);
    // = printf("%0-5%");
    //printf("\n");
    //printf("%4s", NULL);
    //printf("\n");
    //printf("%d", kek);
    
    // Оработка Pointer
    // result = printf("%.16p", remainder);
    // printf("\n");
    // printf("%d", result);
    // printf("\n");
	// a = printf("%025p", int_pointer);
    // printf("\n");
	// printf("%d", a);
    
    // unsigned long aa = &int_pointer;
	// printf("%p\n", &int_pointer);
    // printf("%ld\n", aa);
    // printf("\n");
	// a = printf("%p", int_pointer);
	// b = ft_ptr_len((unsigned long )a);
    // printf("\n");
	// printf("%d", a);
	// printf("\n");
	// printf("%d", b);

    // Оработка %
    // printf("%%"); // выведет % и вернет 1
    // //Флаг ‘-‘
    // printf("\n");
    // printf("%-%"); // выведет % и вернет 1
    // printf("\n");
    // //Флаг ‘0‘
    // printf("%0%"); // выведет % и вернет 1
    // printf("\n");
    // //Ширина равна 5
    // printf("%5%"); // выведет _ _ _ _ % и вернет 5
    // printf("\n");
    // //Ширина равна 5 и флаг ‘-‘
    // printf("%-5%"); // выведет % _ _ _ _ и вернет 5
    // printf("\n");
    // //Ширина равна 5 и флаг ‘0’
    // printf("%05%"); // выведет 0 0 0 0 % и вернет 5
    // printf("\n");
    // //Ширина равна 5 и флаг ‘0’ и флаг ‘-‘
    // printf("%-05%"); // выведет % _ _ _ _ и вернет 5
    // printf("\n");
    // printf("%0-5%"); // выведет % _ _ _ _ и вернет 5
    // printf("\n");
    // //Точность никак не влияет на вывод
    // printf("%.5%");  //  выведет % и вернет 1
    // printf("\n");
    // printf("%0.5%");  //  выведет % и вернет 1
    // printf("\n");
    // printf("%-.5%");  //  выведет % и вернет 1

return (0);

}