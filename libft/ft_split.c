/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbraune <fbraune@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:32:36 by fbraune           #+#    #+#             */
/*   Updated: 2025/03/17 15:13:41 by fbraune          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countword(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*ft_wordduplicate(char const *s, int start, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int	ft_wordprocess(char **result, char const *s, char c)
{
	int	i;
	int	j;
	int	begin;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			begin = i;
			while (s[i] != '\0' && s[i] != c)
				i++;
			result[j] = ft_wordduplicate(s, begin, i - begin);
			if (!result[j])
				return (1);
			j++;
		}
	}
	result[j] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	word_count = ft_countword(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (ft_wordprocess(result, s, c))
	{
		i = 0;
		while (result[i] != NULL)
		{
			free(result[i]);
			i++;
		}
		free(result);
		return (NULL);
	}
	return (result);
}

// int main()
// {
// 	char const *str = "TEST 123 ,c sdasd  r3ewd";
// 	char **res = ft_split(str, ' ');
// 	int i;

// 	i = 0;
// 	while(res[i] != NULL)
// 	{
// 		printf ("%s\n", res[i]);
// 		free (res[i]);
// 		i++;
// 	}
// 	free (res);
// }
