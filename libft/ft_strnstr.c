/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:32:20 by dimatayi          #+#    #+#             */
/*   Updated: 2024/10/08 20:30:27 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*little)
		return ((char *)big);
	while (big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			if (!little[++j])
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
/* #include <stdio.h>
int main()
{
	char haystack[30] = "A";
//	char needle[10] = "aabc";
//	char * empty = (char*)"";
	if (ft_strnstr(haystack, haystack, ft_strlen(haystack) + 1) == haystack)
		printf("%s\n", "vrai");
	else
		printf("%s\n", "faux");

} */
