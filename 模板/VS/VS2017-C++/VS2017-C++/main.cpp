

int main()
{
	char str[20];
	char *flag;
	strcpy_s(str, "hello");
	 
	if (strstr((&str[3]) - 2, "le") == NULL)
	{
		puts("null");
	}
	system("pause");
	return 0;
}