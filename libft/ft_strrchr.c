/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:32:27 by dimatayi          #+#    #+#             */
/*   Updated: 2024/10/07 20:19:34 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
/*
#include <stdio.h>
int main(void)
{
	char s[] = "teste";
	printf("Address of s: %p\n", s);
	if (ft_strrchr(s, 1024 + 'e') == s + 4)
		printf("vrai\n");
	else
		printf("faux\n");
	printf("Address of result: %p\n", ft_strrchr(s, 't'));

	if (ft_strrchr(s, 1024) == s + 5)
		printf("vrai\n");
	else
		printf("faux\n");
	printf("Address of result: %p\n", ft_strrchr(s, 1024 + 'e'));
}
 */
