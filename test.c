#include <string.h>
#include <stdio.h>
#include <stdlib.h>



size_t	ft_strlen(const char *str)
{	
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] != 0)
	{
		i++;
	}
	return (i);
}


char	*ft_strdup(char *src)
{
	int		i;
	char	*cpy;

	if (!src)
		return (NULL);
	i = 0;
	cpy = (char *)malloc(sizeof(char) * ft_strlen(src)+ 1);
	if (!cpy)
		return (NULL);
	while (src[i])
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*ptr;

	if (!s)
		return (NULL);
	if (ft_strlen(s) == 0 || start >= ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	i = 0;
	if (start < ft_strlen(s))
		while (s[start + i] && i < len)
		i++;
	ptr = (char *)malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
	{
		if (i <= len)
		{
			ptr[i++] = s[start++];
		}
	}
	ptr[i] = '\0';
	return (ptr);
}


int main(int argc, char const *argv[], char **env)
{
    int i;
    int j;

    i = 0;
    while(env[i])
    {
        j = 0;
        while(env[i][j] && env[i][j] != 'P')
            j++;
        if (strncmp(env[i], "PATH", 4) == 0)
           printf("%s\n", (&env[i][5]));
        i++;
    }
    return (0);
}