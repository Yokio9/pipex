/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strtrim.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: dimatayi <dimatayi@student.42lausanne.c	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/10/08 12:25:54 by dimatayi		  #+#	#+#			 */
/*   Updated: 2024/10/08 12:56:47 by dimatayi		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

static size_t	is_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*trim;
	size_t	i;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	if (*s1 == '\0')
		return (ft_strdup(""));
	i = 0;
	while (s1[i] && is_set(s1[i], set))
		i++;
	start = i;
	while (s1[i])
		i++;
	i--;
	while (i > start && is_set(s1[i], set))
		i--;
	end = i + 1;
	trim = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!trim)
		return (NULL);
	ft_memcpy(trim, s1 + start, end - start);
	trim[end - start] = '\0';
	return (trim);
}
