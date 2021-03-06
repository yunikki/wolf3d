/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 17:44:04 by mpinson           #+#    #+#             */
/*   Updated: 2017/09/10 17:44:08 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	save(t_gen *g)
{
	int fd;

	fd = open(g->path_save, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRWXU | S_IRWXG | S_IRWXO);
	ft_putnbr_fd(g->posx, fd);
	ft_putchar_fd('\n', fd);
	ft_putnbr_fd(g->posy, fd);
	close(fd);
}

void	recadre(t_gen *g, int x, int y)
{
	if (g->larg_x / 2 > x)
		g->posx = x + 0.5;
	else
		g->posx = x - 0.5;
	if (g->larg_y / 2 > y)
		g->posy = y + 0.5;
	else
		g->posy = y - 0.5;
}

void	load(t_gen *g)
{
	char	str[10];
	char	**t;
	int		x;
	int		y;
	int		fd;

	if ((fd = open(g->path_save, O_RDONLY)) == -1)
		return ;
	read(fd, str, 10);
	t = ft_strsplit(str, '\n');
	if (ft_strlen_tab(t) != 2)
		return ;
	if (ft_strlen(t[0]) > 11 || ft_atol(t[0]) >= g->larg_x || ft_atol(t[0]) < 0)
		return ;
	x = ft_atoi(t[0]);
	if (ft_strlen(t[1]) > 11 || ft_atol(t[1]) >= g->larg_y || ft_atol(t[1]) < 0)
		return ;
	y = ft_atoi(t[1]);
	recadre(g, x, y);
	close(fd);
	ft_free_tab(t);
}

int		key_menu2(int kc, t_gen *g)
{
	if (kc == 36 && g->menu_mod == 0)
	{
		g->menu_mod = 1;
		ft_start_algo(g);
		return (0);
	}
	else if (kc == 36 && g->menu_mod == 1)
	{
		g->pos_curseur == 4 ? system("killall afplay") : 0;
		g->pos_curseur == 4 ? exit(0) : 0;
		g->pos_curseur == 2 ? ft_init_str(g) : 0;
		g->pos_curseur == 1 ? save(g) : 0;
		g->pos_curseur == 3 ? load(g) : 0;
		g->menu_mod = 0;
		g->pos_curseur = 0;
		ft_start_algo(g);
		return (0);
	}
	if (g->menu_mod)
	{
		ft_start_algo(g);
		return (0);
	}
	return (1);
}

int		key_menu1(int kc, t_gen *g)
{
	kc == 53 ? system("killall afplay") : 0;
	kc == 53 ? exit(0) : 0;
	kc == 53 && g->menu_mod == 1 ? g->menu_mod = 0 : 0;
	if (kc == 126 && g->menu_mod == 1)
	{
		g->pos_curseur--;
		g->pos_curseur < 0 ? g->pos_curseur = 4 : 0;
	}
	if (kc == 125 && g->menu_mod == 1)
	{
		g->pos_curseur++;
		g->pos_curseur > 4 ? g->pos_curseur = 0 : 0;
	}
	if (key_menu2(kc, g) == 0)
		return (0);
	key_pressed_deplace(kc, g, 0, 0);
	key_pressed_color(kc, g);
	if (kc == 18 && g->hidd_menu == 0)
		g->hidd_menu = 1;
	else if (kc == 18 && g->hidd_menu == 1)
		g->hidd_menu = 0;
	return (1);
}
