/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:34:50 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/22 14:01:08 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

size_t				ft_strlen(const char *s);
int					ft_tolower(int c);
int					ft_isspace(char c);
int					ft_strncmp(const char *s1, const char *s2, int n);
int					ft_strncmp_lcase(const char *s1, const char *s2, int n);
void				*ft_memmove(void *dst, const void *src, size_t len);
int					ft_strchr(char const c, char const *set);
int					get_next_line(int fd, char **line);
int					ft_atoi(char **str);
char				*ft_itoa(int n);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
int					ft_lstadd_back(t_list **lst, t_list *new);
int					ft_lstdestroy(t_list **lst, int free_content);
void				puterr(const char *str);

#endif
