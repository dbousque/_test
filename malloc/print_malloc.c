

#include "malloc.h"




#   include <stdio.h>

void    print_small_block(t_small_block *block)
{
    char    *tmp_str;

    tmp_str = "  - small block of size ";
    write(1, tmp_str, ft_strlen(tmp_str));
    print_number(block->size);
    printf("  : %p", block);
    fflush(stdout);
    write(1, "\n", 1);
    tmp_str = "  - free : ";
    write(1, tmp_str, ft_strlen(tmp_str));
    if (block->free)
        tmp_str = "Yes\n";
    else
        tmp_str = "No\n";
    write(1, tmp_str, ft_strlen(tmp_str));
}

void    print_tiny_block(t_tiny_block *block)
{
    char    *tmp_str;

    tmp_str = "  - tiny block of size ";
    write(1, tmp_str, ft_strlen(tmp_str));
    print_number(block->size);
    printf("  : %p", block);
    fflush(stdout);
    write(1, "\n", 1);
    tmp_str = "  - free : ";
    write(1, tmp_str, ft_strlen(tmp_str));
    if (block->free)
        tmp_str = "Yes\n";
    else
        tmp_str = "No\n";
    write(1, tmp_str, ft_strlen(tmp_str));
}

void    print_free_small_blocks(t_linked_list *free_small_blocks)
{
    size_t  i;
    char    *tmp_str;

    tmp_str = "Printing free blocks :\n";
    write(1, tmp_str, ft_strlen(tmp_str));
    i = 0;
    while (i < free_small_blocks->len)
    {
        print_number(i + 1);
        write(1, " :\n", 3);
        print_small_block(free_small_blocks->elts[i]);
        i++;
    }
}

void    print_zone_info(t_zone *zone)
{
    char    *tmp_str;

    tmp_str = "  - number of allocated blocks : ";
    write(1, tmp_str, ft_strlen(tmp_str));
    write(1, "\n", 1);
    tmp_str = "  - type of zone : ";
    write(1, tmp_str, ft_strlen(tmp_str));
    if (zone->type == TINY)
        tmp_str = "TINY";
    else if (zone->type == SMALL)
        tmp_str = "SMALL";
    else if (zone->type == LARGE)
        tmp_str = "LARGE";
    else
        tmp_str = "UNKNOWN TYPE!";
    write(1, tmp_str, ft_strlen(tmp_str));
    write(1, "\n", 1);
}

void    print_zone_content(t_malloc_data *data, t_zone *zone)
{
    void    *block;
    void    *end;

    end = NULL;
    if (zone->type == SMALL)
        end = (void*)zone + get_small_zone_size(data);
    else if (zone->type == TINY)
        end = (void*)zone + get_tiny_zone_size(data);
    block = (void*)zone + sizeof(t_zone);
    while (block < end)
    {
        if (zone->type == SMALL)
            print_small_block(block);
        else if (zone->type == TINY)
            print_tiny_block(block);
        if (zone->type == SMALL)
            block += ((t_small_block*)block)->size + sizeof(t_small_block);
        else if (zone->type == TINY)
            block += ((t_tiny_block*)block)->size + sizeof(t_tiny_block);
        else
        {
            write(1, "UNIMPLEMENTED\n", 14);
        }
    }
}

void    print_zone(t_malloc_data *data, t_zone *zone)
{
    print_zone_info(zone);
    print_zone_content(data, zone);
}

void    print_zones(t_malloc_data *data)
{
    size_t  i;
    char    *tmp_str;

    tmp_str = "Printing zones : \n";
    write(1, tmp_str, ft_strlen(tmp_str));
    i = 0;
    while (i < data->zones.len)
    {
        print_number(i + 1);
        write(1, " :\n", 3);
        print_zone(data, data->zones.elts[i]);
        i++;
    }
}

void    print_raw_blocks(t_malloc_data *data)
{
    size_t  i;
    char    *tmp_str;

    if (!data->raw_blocks.size)
        return ;
    tmp_str = "Printing large blocks : \n";
    write(1, tmp_str, ft_strlen(tmp_str));
    i = 0;
    while (i < data->raw_blocks.len)
    {
        print_number(i + 1);
        tmp_str = " : \n  - block of size ";
        write(1, tmp_str, ft_strlen(tmp_str));
        print_number(*((size_t*)(data->raw_blocks.elts[i] + sizeof(size_t))));
        write(1, "\n", 1);
        i++;
    }
}

void    print_mem(t_malloc_data *data)
{
    print_free_small_blocks(&(data->free_small_blocks));
    print_zones(data);
    print_raw_blocks(data);
}