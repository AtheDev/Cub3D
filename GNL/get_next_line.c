/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 18:37:10 by adupuy            #+#    #+#             */
/*   Updated: 2020/12/30 13:18:39 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_next_line(int fd, char **line)
{
	int			ret;
	char		buf[101];
	static char	*str;
	int			count;

	if (fd < 0 || !line || read(fd, 0, 0) == -1)
		return (-1);
	ret = 1;
	while ((ret > 0) && ((count = ft_is_end_line(str)) == 0))
	{
		ret = read(fd, buf, 100);
		buf[ret] = '\0';
		if (!(str = ft_my_strjoin(str, buf)))
			return (-1);
	}
	ret = ft_new_line(&str, line, ret, count);
	return (ret);
}
